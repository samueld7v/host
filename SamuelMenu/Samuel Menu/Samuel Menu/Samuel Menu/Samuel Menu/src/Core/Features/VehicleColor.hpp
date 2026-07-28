#pragma once 
 #include <Includes/Includes.hpp> 
 #include <Core/Offsets.hpp> 
 #include <Core/SDK/SDK.hpp> 
 
 namespace Core 
 { 
     namespace Features 
     { 
         class cVehicleColor 
        { 
        private: 
            bool IsRunning = false; 
            CVehicle* MyVehicle = nullptr; 
            float currentHue = 0.0f;

            ImColor HSVtoRGB(float H, float S, float V) {
                float r, g, b;
                ImGui::ColorConvertHSVtoRGB(H, S, V, r, g, b);
                return ImColor(r, g, b, 1.0f);
            }

        public: 
            void Start() { 
                if (IsRunning) return; 

                IsRunning = true; 
                MyVehicle = nullptr; 

                std::thread([this]() { 
                    while (this->IsRunning) { 
                        this->Update(); 
                        std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
                    } 
                    }).detach(); 
            } 

            void Stop() { 
                IsRunning = false; 
                ResetMyVehicle(); 
            } 

            void Update() { 
                if (!Core::g_Config.Player.ChangeVehicleColor && !Core::g_Config.Player.RainbowCar) { 
                    ResetMyVehicle(); 
                    return; 
                } 
                if (!SDK::Pointers::pLocalPlayer) { 
                    ResetMyVehicle(); 
                    return; 
                } 

                bool isInVehicle = SDK::Pointers::pLocalPlayer->IsInVehicle(); 

                if (!isInVehicle) { 
                    ResetMyVehicle(); 
                    return; 
                } 

                CVehicle* currentVehicle = SDK::Pointers::pLocalPlayer->GetLastVehicle(); 

                if (!currentVehicle) { 
                    ResetMyVehicle(); 
                    return; 
                } 
                if (currentVehicle != MyVehicle) { 
                    if (MyVehicle) { 
                        MyVehicle->ResetVehicleColors(); 
                    } 
                    MyVehicle = currentVehicle; 
                } 
                if (MyVehicle) { 
                    if (Core::g_Config.Player.RainbowCar) {
                        currentHue += 0.005f * Core::g_Config.Player.RainbowCarSpeed;
                        if (currentHue > 1.0f) currentHue = 0.0f;
                        
                        ImColor rainbowColor = HSVtoRGB(currentHue, 1.0f, 1.0f);
                        MyVehicle->SetVehicleColors(rainbowColor, rainbowColor);
                    } else {
                        MyVehicle->SetVehicleColors( 
                            Core::g_Config.Player.VehicleColor, 
                            Core::g_Config.Player.VehicleColor 
                        ); 
                    }
                } 
            } 
            void ResetMyVehicle() { 
                if (MyVehicle) { 
                    MyVehicle->ResetVehicleColors(); 
                    MyVehicle = nullptr; 
                } 
            } 
            void ResetAllColors() { 
                ResetMyVehicle(); 
            } 
            void ForceUpdate() { 
                if (!Core::g_Config.Player.ChangeVehicleColor && !Core::g_Config.Player.RainbowCar) return; 
                if (!SDK::Pointers::pLocalPlayer || !SDK::Pointers::pLocalPlayer->IsInVehicle()) return; 

                CVehicle* vehicle = SDK::Pointers::pLocalPlayer->GetLastVehicle(); 

                if (vehicle) { 
                    if (MyVehicle && MyVehicle != vehicle) { 
                        MyVehicle->ResetVehicleColors(); 
                    } 
                    MyVehicle = vehicle; 
                    
                    if (Core::g_Config.Player.RainbowCar) {
                        ImColor rainbowColor = HSVtoRGB(currentHue, 1.0f, 1.0f);
                        vehicle->SetVehicleColors(rainbowColor, rainbowColor);
                    } else {
                        vehicle->SetVehicleColors( 
                            Core::g_Config.Player.VehicleColor, 
                            Core::g_Config.Player.VehicleColor 
                        ); 
                    }
                } 
            } 
        }; 
 
         inline cVehicleColor g_VehicleColor; 
     } 
 }