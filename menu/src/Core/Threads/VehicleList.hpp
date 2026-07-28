#pragma once
#include <Includes/Includes.hpp>
#include <Includes/Utils.hpp>
#include <Core/Offsets.hpp>
#include <Core/Core.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>


namespace Core
{
    namespace Threads
    {
        class cVehicleList {
        private:
            CVehInterFace * VehInterface = nullptr;
            CVehicleList * VehList = nullptr;
            int MaxVehicles = 0;
            
            // Cache para evitar ler strings repetidamente do jogo a cada frame
            std::unordered_map<CVehicle*, std::string> VehicleNameCache;
        public:
            std::mutex vehicleListMutex;
        public:
            void Update( )
            {
                while ( true )
                {
                    std::this_thread::sleep_for( std::chrono::milliseconds( 60 ) ); 

                    if ( !Core::SDK::Pointers::pReplayInterFace )
                        continue;

                    if ( !VehInterface || !VehList )
                    {
                        VehInterface = Core::SDK::Pointers::pReplayInterFace->InterfaceVeh( );
                        if ( !VehInterface )
                            continue; 

                        VehList = VehInterface->VehicleList( );
                        if ( !VehList )
                            continue; 
                    };

                    if ( !MaxVehicles )
                        MaxVehicles = VehInterface->MaxVehicles( );

                    size_t Size = Core::SDK::Game::VehicleList.size( );
                    size_t Index = 0;

                    std::vector<Core::SDK::Game::VehicleStructure> updatedVehicleList;
                    updatedVehicleList.reserve(MaxVehicles); // OPT: pré-alocar memória

                    CPed* pLocal = Core::SDK::Pointers::pLocalPlayer;
                    if (!pLocal) continue;
                    
                    D3DXVECTOR3 LocalPos = pLocal->GetPos();

                    for ( int i = 0; i < MaxVehicles; i++ )
                    {
                        CVehicle * CurrentVeh = VehList->Vehicle( i );
                        if (!CurrentVeh) continue;

                        // OPT: Uso de Cache para a string do modelo
                        std::string& vehicleName = VehicleNameCache[CurrentVeh];
                        if (vehicleName.empty()) {
                            uintptr_t vehicleModelInfo = Mem.Read<uintptr_t>( ( uintptr_t ) CurrentVeh + 0x20 );
                            if (vehicleModelInfo) {
                                vehicleName = Mem.ReadString( vehicleModelInfo + 0x298 );
                            }
                        }

                        if ( vehicleName.empty( ) )
                            continue;

                        D3DXVECTOR3 DistanceCalculation = CurrentVeh->GetPos( ) - LocalPos;
                        float Distance = sqrtf( DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z );

                        Core::SDK::Game::VehicleStructure Vehicle;
                        Vehicle.Pointer = CurrentVeh;
                        Vehicle.Name = Utils::StringToFirstUpperCase( vehicleName );
                        Vehicle.Dist = Distance;
                        Vehicle.IsLocked = CurrentVeh->IsLocked( );
                        Vehicle.Driver = CurrentVeh->GetDriver( );
                        Vehicle.Pos = CurrentVeh->GetPos( );

                        updatedVehicleList.push_back( std::move(Vehicle) );
                    }

                    // Limpa do cache veículos que não existem mais para evitar vazamento de memória
                    if (VehicleNameCache.size() > 500) {
                        VehicleNameCache.clear();
                    }

                    std::sort( updatedVehicleList.begin( ), updatedVehicleList.end( ), [ ] ( const auto & lhs, const auto & rhs ) { return lhs.Dist < rhs.Dist; } );

                    {
                        std::lock_guard<std::mutex> lock( vehicleListMutex );
                        Core::SDK::Game::VehicleList = std::move( updatedVehicleList );
                    }
                }
            }
        };

        inline cVehicleList g_VehicleList;
    }
}