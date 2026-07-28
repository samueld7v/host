#pragma once
#include <Includes/Includes.hpp>
#include <Core/Offsets.hpp>
#include <Core/SDK/SDK.hpp>
#include <Core/Config.hpp>

namespace Core
{
	namespace Features
	{
		namespace Player
		{
			class Spinbot { 
			private: 
				float angle = 0.0f; 
				DWORD lastTime = GetTickCount(); 
			
			public: 
				void Apply(uintptr_t ped) { 
					if (!ped || !g_Config.Player.SpinbotEnabled) return; 

					CPed* pPed = reinterpret_cast<CPed*>(ped);

					if (g_Config.Player.CombatGlitch) {
						bool inAir = pPed->HasFlag(CPED_CONFIG_FLAG_IsInTheAir);
						
						bool isAiming = (GetAsyncKeyState(VK_RBUTTON) & 0x8000);
						bool isPressingSpace = (GetAsyncKeyState(VK_SPACE) & 0x8000);
						
						static DWORD rollEndTime = 0;
						
						// Se o jogador mirar e apertar espaço, ativamos um timer para o rolamento
						if (isAiming && isPressingSpace && !inAir) {
							rollEndTime = GetTickCount() + 800; // O rolamento dura cerca de 800ms
						}

						// Se estiver no ar ou o tempo do rolamento tiver acabado, não gira
						if (inAir || GetTickCount() > rollEndTime) {
							return; 
						}
					}
			
					// Atualiza ângulo com a velocidade ajustável 
					DWORD now = GetTickCount(); 
					angle += (now - lastTime) * (g_Config.Player.SpinbotSpeed / 1000.0f); // Converte para graus por milissegundo 
					lastTime = now; 
					
					if (angle > 360.0f) angle -= 360.0f; 
			
					// Converte para radianos 
					float rad = angle * 0.01745329251f; 
			
					// Vetores de rotação 
					D3DXVECTOR3 forward(sin(rad), cos(rad), 0.0f); 
					D3DXVECTOR3 right(cos(rad), -sin(rad), 0.0f); 
					D3DXVECTOR3 up(0.0f, 0.0f, 1.0f); 
			
					uintptr_t addr = (uintptr_t)ped; 
			
					// Só aplica rotação 
					Core::Mem.Write<D3DXVECTOR3>(addr + 0x60, right); 
					Core::Mem.Write<D3DXVECTOR3>(addr + 0x70, forward); 
					Core::Mem.Write<D3DXVECTOR3>(addr + 0x80, up); 
				} 
			}; 

			inline Spinbot g_Spinbot;

			inline D3DXVECTOR3 savedCamPos = D3DXVECTOR3(0, 0, 0);
			inline D3DXVECTOR3 savedCamAngle = D3DXVECTOR3(0, 0, 0);

			float GetNoClipSpeedValue(float level);

			void NoClip();
			void ResetNoClip();
			void ApplyPlayerFlags();
			void DoubleShot();
			void NoReload();
		}
	}
}
