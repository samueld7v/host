#pragma once
#include <Includes/Includes.hpp>
#include <Core/Offsets.hpp>
#include <Core/SDK/SDK.hpp>

extern const char * keys[ ];

namespace Core
{
	namespace Features
	{
		class cEsp
		{
		public:
			void Draw( );
			void DrawVehicle();
			void AdminList( );
			void InvisibleWarning();
			void FeatureList();
			void WeatherPersist();
		};

		inline cEsp g_Esp;

	}
}