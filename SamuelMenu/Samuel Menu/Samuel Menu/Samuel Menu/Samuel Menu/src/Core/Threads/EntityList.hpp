#pragma once
#include <Includes/Includes.hpp>
#include <Includes/Utils.hpp>
#include <Core/Offsets.hpp>
#include <Core/Core.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

namespace Core
{
    namespace Threads
    {
        class cEntityList
        {
        private:
            std::mutex EntityListMutex;
        private:
            CPedInterFace* CPedInterFace = nullptr;
            CPedList* CPedList = nullptr;
            int PedCount = 0; // OPT: Não usar static dentro do loop; guardar como membro
        public:
            static bool IsValidName(const std::string& n) {
                if (n.empty() || n.length() < 2 || n.length() > 32)
                    return false;
                if (n.find(xorstr("Invalid")) != std::string::npos)
                    return false;
                for (unsigned char c : n) {
                    if (c < 32 || c > 126)
                        return false;
                }
                return true;
            }
            std::unordered_map<CPed*, Core::SDK::Game::EntityStruct> CachedEntities;
        public:
            void Update()
            {
                while (true)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Increased sleep to lower CPU Usage

                    if (!g_MenuInfo.IsLogged && !g_Variables.g_bPassedByThisVerify)
                        continue;

                    if (!Core::SDK::Pointers::pReplayInterFace)
                        continue;

                    CPedInterFace = Core::SDK::Pointers::pReplayInterFace->InterfacePed();
                    CPedList = CPedInterFace->PedList();

                    if (!CPedInterFace || !CPedList)
                        continue;

                    // OPT: Atualizar PedCount uma vez por ciclo (não é estático incorretamente)
                    if (PedCount == 0)
                        PedCount = CPedInterFace->MaxPed();

                    // OPT: Pré-obter o ponteiro do local player uma vez por ciclo
                    CPed* pLocal = Core::SDK::Pointers::pLocalPlayer;
                    D3DXVECTOR3 LocalPos = pLocal ? pLocal->GetPos() : D3DXVECTOR3(0, 0, 0);

                    size_t Size = Core::SDK::Game::EntityList.size();
                    size_t Index = 0;

                    {
                        std::lock_guard<std::mutex> Guard(EntityListMutex);

                        for (int i = 0; i < PedCount; i++)
                        {
                            CPed* CurrentPed = CPedList->Ped(i);

                            if (!CurrentPed)
                                continue;

                            int currentId = CurrentPed->GetID();
                            int currentPedType = CurrentPed->GetPedType();

                            // OPT: Usar try_emplace para evitar dupla busca (find + operator[])
                            auto [it, inserted] = CachedEntities.try_emplace(CurrentPed);
                            Core::SDK::Game::EntityStruct& CachedEntityRef = it->second;

							if (inserted)
							{
								CachedEntityRef.Index = i;
								CachedEntityRef.MaxHealth = CurrentPed->GetMaxHealth();
							}

							// OPT: Sempre atualizar campos que mudam frequentemente
							CachedEntityRef.Id = currentId;
							CachedEntityRef.PedType = currentPedType;
							CachedEntityRef.Health = CurrentPed->GetHealth();
							CachedEntityRef.Armor = CurrentPed->GetArmor();
							CachedEntityRef.Pos = CurrentPed->GetPos();
							CachedEntityRef.IsFriend = Core::SDK::Game::FriendMap[CurrentPed];
							CachedEntityRef.Distance = CurrentPed->GetDistance(LocalPos, CachedEntityRef.Pos);

                            if (g_Offsets.m_WeaponManager != 0 && (CachedEntityRef.Distance < 300.f || CurrentPed == pLocal)) {
                                CachedEntityRef.WeaponName = CurrentPed->GetWeaponManager()->GetWeaponInfo()->GetName();
                            }
                            else {
                                CachedEntityRef.WeaponName = "";
                            }

                            // OPT: Construir Entity direto para o slot do vector, evitando cópia extra
                            Core::SDK::Game::EntityStruct Entity;
                            Entity.Ped = CurrentPed;
                            Entity.Id = currentId;
                            Entity.Index = CachedEntityRef.Index;
                            Entity.Pos = CachedEntityRef.Pos;
                            Entity.IsFriend = CachedEntityRef.IsFriend;
                            Entity.MaxHealth = CachedEntityRef.MaxHealth;
                            Entity.Health = CachedEntityRef.Health;
                            Entity.Armor = CachedEntityRef.Armor;
                            Entity.PedType = currentPedType;
                            Entity.Distance = CachedEntityRef.Distance;
                            Entity.WeaponName = CachedEntityRef.WeaponName;

                            if (currentId == -1) {
                                Entity.NetworkInfo.UserName = xorstr("NPC");
                            }
                            else {
                                bool hasApiName = false;
                                auto itName = Core::Threads::g_UpdateNames.NetworkMap.find(currentId);
                                if (itName != Core::Threads::g_UpdateNames.NetworkMap.end()) {
                                    auto& NetworkInfo = itName->second;
                                    if (!NetworkInfo.UserName.empty()) {
                                        Entity.NetworkInfo.UserName = Utils::StringToFirstUpperCase(NetworkInfo.UserName);
                                        hasApiName = true;
                                    }
                                    Entity.NetworkInfo.SteamId = NetworkInfo.SteamId;
                                    Entity.NetworkInfo.DiscordId = NetworkInfo.DiscordId;
                                }

                                if (!hasApiName && !CachedEntityRef.GeneratedName.empty()) {
                                    Entity.NetworkInfo.UserName = CachedEntityRef.GeneratedName;
                                    hasApiName = true;
                                }

                                if (!hasApiName) {
                                    std::string nameFound;
                                    CPlayerInfo* pInfo = CurrentPed->GetPlayerInfo();
                                    if (pInfo) {
                                        uintptr_t pInfoAddr = reinterpret_cast<uintptr_t>(pInfo);
                                        uintptr_t nameOffsets[] = { 0x7C, 0x88, 0x8C, 0x90, 0x94, 0x9C, 0xA0, 0xD8, 0xE0, 0xE8, 0x1A0, 0x1A8, 0x1B0 };
                                        for (auto off : nameOffsets) {
                                            std::string n = Mem.ReadString(pInfoAddr + off);
                                            if (IsValidName(n)) { nameFound = n; break; }
                                        }
                                        if (nameFound.empty()) {
                                            for (auto off : nameOffsets) {
                                                std::string n = Mem.ReadStdString(pInfoAddr + off);
                                                if (IsValidName(n)) { nameFound = n; break; }
                                            }
                                        }
                                    }

                                    if (nameFound.empty() && g_Offsets.m_PlayerNamePtr) {
                                        uintptr_t base = g_Offsets.m_PlayerNamePtr;
                                        for (int stride : {32, 24, 48, 64, 128, 16, 8}) {
                                            std::string n = Mem.ReadStdString(base + currentId * stride);
                                            if (IsValidName(n)) { nameFound = n; break; }
                                        }
                                        if (nameFound.empty()) {
                                            for (int stride : {32, 24, 48, 64, 128, 16, 8}) {
                                                uintptr_t strPtr = Mem.Read<uintptr_t>(base + currentId * stride);
                                                if (strPtr) {
                                                    std::string n = Mem.ReadString(strPtr);
                                                    if (IsValidName(n)) { nameFound = n; break; }
                                                }
                                            }
                                        }
                                    }

                                    if (!nameFound.empty()) {
                                        Entity.NetworkInfo.UserName = Utils::StringToFirstUpperCase(nameFound);
                                        CachedEntityRef.GeneratedName = Entity.NetworkInfo.UserName;
                                    }
                                }

                                if (Entity.NetworkInfo.UserName.empty()) {
                                    Entity.NetworkInfo.UserName = xorstr("Player");
                                }
                            }

                            if (Index < Size)
                                Core::SDK::Game::EntityList[Index] = std::move(Entity);
                            else
                                Core::SDK::Game::EntityList.push_back(std::move(Entity));

                            Index++;
                        }
                    }

                    if (Index < Size)
                        Core::SDK::Game::EntityList.resize(Index);

                }
            }
        };

        inline cEntityList g_EntityList;
    }
}