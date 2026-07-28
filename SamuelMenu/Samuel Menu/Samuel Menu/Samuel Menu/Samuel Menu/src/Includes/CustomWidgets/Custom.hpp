#pragma once
#include <Globals.hpp>
#include <Includes/Utils.hpp>
#include <Includes/Includes.hpp>
#include <map>
#include <functional>


namespace Custom {

	using namespace ImGui;

	inline double EaseInOutCirc( double t ) 
	{
		if ( t < 0.5 )
			return ( 1 - std::sqrt( 1 - 2 * t ) ) * 0.5;
		else
			return ( 1 + std::sqrt( 2 * t - 1 ) ) * 0.5;
	}

	inline int rotation_start_index;
	inline void ImRotateStart( )
	{
		rotation_start_index = ImGui::GetWindowDrawList( )->VtxBuffer.Size;
	}

	inline ImVec2 ImRotationCenter( )
	{
		ImVec2 l( FLT_MAX, FLT_MAX ), u( -FLT_MAX, -FLT_MAX ); // bounds

		const auto & buf = ImGui::GetWindowDrawList( )->VtxBuffer;
		for ( int i = rotation_start_index; i < buf.Size; i++ )
			l = ImMin( l, buf[ i ].pos ), u = ImMax( u, buf[ i ].pos );

		return ImVec2( ( l.x + u.x ) / 2, ( l.y + u.y ) / 2 ); // or use _ClipRectStack?
	}

	inline void ImRotateEnd( float rad, ImVec2 center = ImRotationCenter( ) )
	{
		float s = sin( rad ), c = cos( rad );
		center = ImRotate( center, s, c ) - center;

		auto & buf = ImGui::GetWindowDrawList( )->VtxBuffer;
		for ( int i = rotation_start_index; i < buf.Size; i++ )
			buf[ i ].pos = ImRotate( buf[ i ].pos, s, c ) - center;
	}

	inline void ProfileBar( ) {
		ImVec2 WindowPos = ImGui::GetWindowPos( );
		ImDrawList * DrawList = ImGui::GetWindowDrawList( );

		std::string Username = g_Variables.UserName;
		std::string Role = g_Variables.Role;
		std::string PrimeiraLetra = Username.substr( 0, 1 );
		std::transform( PrimeiraLetra.begin( ), PrimeiraLetra.end( ), PrimeiraLetra.begin( ), [ ] ( unsigned char c ) { return std::toupper( c ); } );

		if ( Username.length( ) > 10 ) {
			Username = Username.substr( 0, 7 ) + xorstr( "..." );
		}

		ImVec2 PrimeiraLetraNameTextSize = ::Utils::CalcTextSize( g_Variables.m_FontNormal, (int)g_Variables.m_FontNormal->FontSize, PrimeiraLetra.c_str( ) );
		ImVec2 NameTextSize = ::Utils::CalcTextSize( g_Variables.m_FontSecundary, (int)g_Variables.m_FontSecundary->FontSize, Username.c_str( ) );
		ImVec2 RoleTextSize = ::Utils::CalcTextSize( g_Variables.m_FontSmaller, (int)g_Variables.m_FontSmaller->FontSize, Role.c_str( ) );

		ImVec2 ProfilePos = { WindowPos.x + g_MenuInfo.MenuSize.x - 30, WindowPos.y + 30 };
		DrawList->AddCircleFilled( ProfilePos, 20, ImGui::GetColorU32( ( ImVec4 ) ImColor( 17, 17, 20 ) ), 100 );
		DrawList->AddCircle( ProfilePos, 20, ImGui::GetColorU32( ( ImVec4 ) ( g_Col.BorderCol ) ), 100 );


		ImVec2 ProfileLetra = { ProfilePos.x - PrimeiraLetraNameTextSize.x / 2, ProfilePos.y - PrimeiraLetraNameTextSize.y / 2 - 1 };
		DrawList->AddText( g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, ProfileLetra, ImGui::GetColorU32( ( ImVec4 ) ImColor( 163, 163, 163 ) ), PrimeiraLetra.c_str( ) );

		ImVec2 UsernamePos = { ProfilePos.x - 32 - NameTextSize.x, ProfileLetra.y - 6 };
		DrawList->AddText( g_Variables.m_FontSecundary, g_Variables.m_FontSecundary->FontSize, UsernamePos, ImGui::GetColorU32( ( ImVec4 ) ImColor( 163, 163, 163 ) ), Username.c_str( ) );

		ImVec2 RolePos = { ProfilePos.x - 32 - RoleTextSize.x, ProfileLetra.y + 8 };
		DrawList->AddText( g_Variables.m_FontSmaller, g_Variables.m_FontSmaller->FontSize, RolePos, ImGui::GetColorU32( ( ImVec4 ) ImColor( 80, 80, 80 ) ), Role.c_str( ) );
	}

	inline void DrawBackground( bool Logged ) {
		const ImVec2 pos = ImGui::GetWindowPos( );
		ImDrawList * draw = ImGui::GetWindowDrawList( );
		ImVec2 size = Logged ? g_MenuInfo.MenuSize : g_MenuInfo.LoginSize;

		//Brackground
		if (g_MenuInfo.Glassmorphism) {
			// Semi-transparent glass background
			draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x, pos.y + size.y),
				ImGui::GetColorU32(ImVec4(10.f/255.f, 10.f/255.f, 15.f/255.f, 0.80f)), 12.f);

			// Glass reflection highlight (subtle white gradient from top-left corner)
			draw->AddRectFilledMultiColor(
				ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x * 0.5f, pos.y + size.y * 0.35f),
				ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 0.04f)),
				ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 0.015f)),
				ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 0.f)),
				ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 0.f)));

			// Inner shadow at top edge for depth
			draw->AddRectFilledMultiColor(
				ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x, pos.y + 3.f),
				ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, 0.25f)),
				ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, 0.25f)),
				ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, 0.f)),
				ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, 0.f)));

			// Inner shadow at bottom edge
			draw->AddRectFilledMultiColor(
				ImVec2(pos.x, pos.y + size.y - 3.f), ImVec2(pos.x + size.x, pos.y + size.y),
				ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, 0.f)),
				ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, 0.f)),
				ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, 0.25f)),
				ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, 0.25f)));
		}
		else {
			draw->AddRectFilled(ImVec2(pos.x + 0, pos.y + 0), ImVec2(pos.x + size.x, pos.y + size.y), ImGui::GetColorU32(g_Col.BackgroundCol), 12.f);
		}

		if (g_MenuInfo.EnableParticles) {
			ImGui::PushClipRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), true);

			static float cachedTime = 0.f;
			static float time = 0.f;
			static int frameCounter = 0;
			const int updateInterval = 3;
			bool needsUpdate = (++frameCounter % updateInterval) == 0;
			if (needsUpdate) {
				time = ImGui::GetTime() * 0.4f;
				cachedTime = time;
			} else {
				time = cachedTime;
			}

			int num_lines = 5;
			int points_count = 50;
			float step_x = size.x / (points_count - 1);

			for (int line_idx = 0; line_idx < num_lines; line_idx++) {
				float speed_offset = line_idx * 0.1f;
				float amplitude = 30.f + (line_idx * 15.f);

				for (int i = 0; i < points_count - 1; i++) {
					float x1 = i * step_x;
					float x2 = (i + 1) * step_x;

					float wave_y1 = sinf(x1 * 0.003f + time * (0.5f + speed_offset)) * amplitude + sinf(x1 * 0.001f - time * 0.3f) * 20.f;
					float wave_y2 = sinf(x2 * 0.003f + time * (0.5f + speed_offset)) * amplitude + sinf(x2 * 0.001f - time * 0.3f) * 20.f;

					float base_y = (size.y / (num_lines + 1)) * (line_idx + 1) + sinf(time * 0.4f + line_idx) * 30.f;

					float y1 = base_y + wave_y1;
					float y2 = base_y + wave_y2;

					ImVec2 p1 = ImVec2(pos.x + x1, pos.y + y1);
					ImVec2 p2 = ImVec2(pos.x + x2, pos.y + y2);

				ImU32 line_color = ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 0.25f - (line_idx * 0.03f))); 
				ImU32 glow_color = ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 0.08f)); 

					draw->AddLine(p1, p2, glow_color, 6.0f); 
					draw->AddLine(p1, p2, line_color, 1.5f); 
				}
			}

			if (Logged) {
				int num_particles = 20;
				for (int i = 0; i < num_particles; i++) {
					float x = pos.x + fmodf(size.x * 0.13f * i + time * 6.f * (i % 3 + 1), size.x);
					float y_anim = fmodf(size.y * 0.3f * i + time * 12.5f * (i % 4 + 1), size.y + 50.f);
					float y = pos.y + size.y + 20.f - y_anim;

					float radius = 1.5f + (i % 3);

					float alpha = 0.1f + 0.6f * sinf(time * 1.5f + i);
					if (alpha < 0.0f) alpha = 0.0f;

					ImVec4 color_vec = (i % 2 == 0) ? ImVec4(1.0f, 1.0f, 1.0f, alpha) : ImVec4(0.8f, 0.8f, 0.8f, alpha * 0.6f);
					ImU32 particle_color = ImGui::GetColorU32(color_vec);

					draw->AddCircleFilled(ImVec2(x, y), radius, particle_color);
				}
			}

			ImGui::PopClipRect();
		}

		//Window Border
		if (g_MenuInfo.Glassmorphism) {
			// Brighter glass border
			draw->AddRect(ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x, pos.y + size.y),
				ImGui::GetColorU32(ImVec4(55.f/255.f, 55.f/255.f, 62.f/255.f, 0.85f)), 12.f);
			// Outer glow border
			draw->AddRect(ImVec2(pos.x - 1.f, pos.y - 1.f), ImVec2(pos.x + size.x + 1.f, pos.y + size.y + 1.f),
				ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 0.035f)), 12.f);
			// Inner subtle border highlight
			draw->AddRect(ImVec2(pos.x + 1.f, pos.y + 1.f), ImVec2(pos.x + size.x - 1.f, pos.y + size.y - 1.f),
				ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 0.04f)), 12.f);
		}
		else {
			draw->AddRect(ImVec2(pos.x + 0, pos.y + 0), ImVec2(pos.x + size.x, pos.y + size.y), ImGui::GetColorU32(g_Col.BorderCol), 12.f);
		}

		if ( Logged )
		{
			float headerHeight = 45.f; // Reduced header height
			
			// Header background
			if (g_MenuInfo.Glassmorphism) {
				draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x, pos.y + headerHeight),
					ImGui::GetColorU32(ImVec4(20.f/255.f, 20.f/255.f, 24.f/255.f, 0.80f)), 12.f, ImDrawFlags_RoundCornersTop);
			}
			else {
				draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x, pos.y + headerHeight), ImGui::GetColorU32(ImVec4(20/255.f, 20/255.f, 22/255.f, 1.f)), 12.f, ImDrawFlags_RoundCornersTop);
			}
			
			// Subtle shadow below header for visual depth
			draw->AddRectFilledMultiColor( ImVec2( pos.x, pos.y + headerHeight ), ImVec2( pos.x + size.x, pos.y + headerHeight + 8.f ), 
				ImGui::GetColorU32( ImVec4(0, 0, 0, 100/255.f) ), ImGui::GetColorU32( ImVec4(0, 0, 0, 100/255.f) ), 
				ImGui::GetColorU32( ImVec4(0, 0, 0, 0) ), ImGui::GetColorU32( ImVec4(0, 0, 0, 0) ) );

			static float LogoHeight = 60.f; // Reduced logo height to fit new menu
			static float LogoWidth = 140.f;  // Reduced logo width to fit new menu
			
			// Logo positioned on the LEFT, moved down a bit
			float logo_margin_left = 20.f;
			float padY = (headerHeight - LogoHeight) / 2.f + 4.f; // Added offset to move logo down
			ImGui::SetCursorPos( ImVec2( logo_margin_left, padY ) );
			ImGui::Image( g_Variables.Logo, ImVec2( LogoWidth, LogoHeight ) );
			
			// Espaço vazio no lugar da barra de pesquisa (removida)
			// Logo permanece no canto esquerdo
		}
	}

	inline bool Tab( const char * label, bool active, const char * icon = nullptr )
	{
		struct Tab_t {
			float UnderlineAnim;
			ImVec4 TextColor;
			float UnSelectedAnim;
			ImVec4 IconColor;
		};

		ImGuiWindow * window = ImGui::GetCurrentWindow( );
		ImDrawList * DrawList = window->DrawList;

		if ( window->SkipItems ) {
			return false;
		}

		ImGuiContext & g = *GImGui;
		const ImGuiStyle & style = g.Style;
		std::string IdStr = std::string( label );
		const ImGuiID id = window->GetID( IdStr.c_str( ) );
		const ImGuiIO IO = g.IO;

		const ImVec2 pos = window->DC.CursorPos;
		ImFont* font = g_Variables.m_FontNormal;
		float font_size = font->FontSize + 2.f;

		float icon_extra = 0.f;
		ImVec2 icon_size(0, 0);
		if (icon) {
			icon_size = g_Variables.FontAwesomeSolid->CalcTextSizeA(16.f, FLT_MAX, 0.0f, icon);
			icon_extra = icon_size.x + 6.f;
		}

		ImGui::PushFont(font);
		ImVec2 text_size = font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, label);
		ImGui::PopFont();

		const ImRect rect( pos, pos + ImVec2( text_size.x + 16.f + icon_extra, 36.f ) );
		ImGui::ItemSize( rect, style.FramePadding.y );
		if ( !ImGui::ItemAdd( rect, id ) ) {
			return false;
		}

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior( rect, id, &hovered, &held );
		if ( pressed ) { ImGui::MarkItemEdited( id ); }

		static std::map<ImGuiID, Tab_t> anim;
		if (anim.size() > 500) anim.clear();
		auto TabAnim = anim.find( id );

		if ( TabAnim == anim.end( ) ) {
			anim.insert( { id, Tab_t( ) } );
			TabAnim = anim.find( id );
		}

		float NormalizedTime = ImClamp( IO.DeltaTime * 12.f, 0.0f, 1.0f );
		TabAnim->second.UnderlineAnim = ImLerp( TabAnim->second.UnderlineAnim, active ? 1.f : 0.f, NormalizedTime );
		TabAnim->second.TextColor = ImLerp( TabAnim->second.TextColor, active ? ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 1.f ) : ( hovered ? ImVec4( 0.9f, 0.9f, 0.9f, 1.f ) : ImVec4( 0.4f, 0.4f, 0.4f, 1.f ) ), NormalizedTime );
		TabAnim->second.IconColor = ImLerp( TabAnim->second.IconColor, active ? ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 1.f ) : ( hovered ? ImVec4( 0.9f, 0.9f, 0.9f, 1.f ) : ImVec4( 0.4f, 0.4f, 0.4f, 1.f ) ), NormalizedTime );

		if ( TabAnim->second.UnderlineAnim > 0.001f ) {
			float line_width = (text_size.x + 8.f + icon_extra) * TabAnim->second.UnderlineAnim;
			float center_x = rect.Min.x + rect.GetWidth() / 2.0f;
			ImVec2 line_start = ImVec2(center_x - line_width / 2.0f, rect.Max.y - 2.f);
			ImVec2 line_end = ImVec2(center_x + line_width / 2.0f, rect.Max.y - 2.f);
			DrawList->AddLine(line_start, line_end, ImGui::GetColorU32(ImVec4(g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, TabAnim->second.UnderlineAnim)), 2.0f);
		}

		float total_w = text_size.x + icon_extra;
		float start_x = rect.Min.x + (rect.GetWidth() - total_w) / 2.0f;

		if (icon) {
			DrawList->AddText( g_Variables.FontAwesomeSolid, 16.f, ImVec2(start_x, rect.Min.y + (rect.GetHeight() - icon_size.y) / 2.0f), ImGui::GetColorU32( TabAnim->second.IconColor ), icon );
			start_x += icon_size.x + 6.f;
		}

		ImVec2 text_pos = ImVec2( start_x, rect.Min.y + ( rect.GetHeight( ) - text_size.y ) / 2.0f );
		DrawList->AddText( font, font_size, text_pos, ImGui::GetColorU32( TabAnim->second.TextColor ), label );

		IMGUI_TEST_ENGINE_ITEM_INFO( id, label, g.LastItemData.StatusFlags );
		return pressed;
	}

	inline bool SubTab( const char * label, bool active )
	{
		struct SubTab_t {
			float HoverAnim;
			ImVec4 TextColor;
		};

		ImGuiWindow * window = ImGui::GetCurrentWindow( );
		ImDrawList * DrawList = window->DrawList;

		if ( window->SkipItems ) {
			return false;
		}

		ImGuiContext & g = *GImGui;
		const ImGuiStyle & style = g.Style;
		std::string IdStr = std::string( label );
		const ImGuiID id = window->GetID( IdStr.c_str( ) );
		const ImGuiIO IO = g.IO;

		const ImVec2 pos = window->DC.CursorPos;

		ImGui::PushFont(g_Variables.m_FontSecundary);
		ImVec2 TextSize = ImGui::CalcTextSize(label);
		ImGui::PopFont();

		// Create a button-like rect padding
		const ImVec2 padding(14.f, 6.f);
		const ImRect rect( pos, pos + ImVec2( TextSize.x + padding.x * 2.f, TextSize.y + padding.y * 2.f ) ); 
		
		ImGui::ItemSize( rect, style.FramePadding.y );
		if ( !ImGui::ItemAdd( rect, id ) ) {
			return false;
		}

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior( rect, id, &hovered, &held );
		if ( pressed ) { ImGui::MarkItemEdited( id ); }

		static std::map<ImGuiID, SubTab_t> anim;
		if (anim.size() > 500) anim.clear();
		auto SubTabAnim = anim.find( id );

		if ( SubTabAnim == anim.end( ) ) {
			anim.insert( { id, SubTab_t( ) } );
			SubTabAnim = anim.find( id );
		}

		float NormalizedTime = ImClamp( IO.DeltaTime * 12.f, 0.0f, 1.0f );
		
		// Animate background on hover and active state
		SubTabAnim->second.HoverAnim = ImLerp( SubTabAnim->second.HoverAnim, active || hovered ? 1.f : 0.f, NormalizedTime );
		
		// Text color white when active, gray when inactive
		SubTabAnim->second.TextColor = ImLerp( SubTabAnim->second.TextColor, active ? ImVec4(1.f, 1.f, 1.f, 1.f) : ImVec4(0.6f, 0.6f, 0.6f, 1.f), NormalizedTime );

		// Draw background exactly like the image
		if (SubTabAnim->second.HoverAnim > 0.01f) {
			// Background box slightly visible
			// DrawList->AddRectFilled( rect.Min, rect.Max, ImGui::GetColorU32( ImVec4(1.f, 1.f, 1.f, 0.08f * SubTabAnim->second.HoverAnim) ), 6.f );
			
			// Border removed as requested
			// DrawList->AddRect( rect.Min, rect.Max, ImGui::GetColorU32( ImVec4(1.f, 1.f, 1.f, 0.1f * SubTabAnim->second.HoverAnim) ), 6.f, 0, 1.0f );
		}
		
		// Underline removed as requested
		/*
		if (active) {
			float line_width = rect.GetWidth() * 0.5f; // Line is 50% of the button width
			float center_x = rect.Min.x + rect.GetWidth() / 2.0f;
			ImVec2 line_start = ImVec2(center_x - line_width / 2.0f, rect.Max.y - 1.f);
			ImVec2 line_end = ImVec2(center_x + line_width / 2.0f, rect.Max.y - 1.f);
			
			DrawList->AddLine(line_start, line_end, ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 0.8f)), 2.0f);
		}
		*/

		// Centered Text
		ImVec2 text_pos = ImVec2(
			rect.Min.x + (rect.GetWidth() - TextSize.x) * 0.5f,
			rect.Min.y + (rect.GetHeight() - TextSize.y) * 0.5f - 1.f
		);

		DrawList->AddText( g_Variables.m_FontSecundary, g_Variables.m_FontSecundary->FontSize, text_pos, ImGui::GetColorU32( SubTabAnim->second.TextColor ), label );

		IMGUI_TEST_ENGINE_ITEM_INFO( id, label, g.LastItemData.StatusFlags );
		return pressed;
	}

	inline void InvisibleShadow( const float alpha, const ImVec2 pos_min, const ImVec2 pos_max, ImU32 color, float shadow_tickness )
	{
		ImGui::PushStyleVar( ImGuiStyleVar_Alpha, alpha );
		ImGui::PushClipRect( pos_min, pos_max, true );
		ImGui::GetWindowDrawList( )->AddShadowCircle( ImVec2( ImGui::GetMousePos( ) ), 1.f, ImGui::GetColorU32( color ), shadow_tickness, ImVec2( 0, 0 ), 1000.f );
		ImGui::PopClipRect( );
		ImGui::PopStyleVar( );
	}

	inline void ToolTip( const char * Label, const char * Desc, const char * Icon, bool State ) {
		//bool Check = CheckBox( Label, Checked );
		bool Hovered = State;

		ImVec2 Pos = ImGui::GetMousePos( ) + ImVec2( 20, 0 );
		auto DrawList = ImGui::GetForegroundDrawList( );
		float Padding = 12;
		float Rounding = 4;
		float Spacing = 6;

		struct ToolTip_t {
			ImVec4 BackGroundColor = ImColor( 20, 20, 22 );
			ImVec4 TextColor = ImColor( 200, 200, 200, 0 );
			ImVec4 IconColor = ImColor( 245, 158, 66, 0 );

			float GlobalAlpha = 0.f;
			float SlideX = 0.f;
		};

		static std::map<std::string, ToolTip_t> anim;
		std::string a1 = std::string( Label ) + std::string( Desc );
		auto ToolTipAnim = anim.find( a1 );

		if ( ToolTipAnim == anim.end( ) ) {
			anim.insert( { a1, ToolTip_t( ) } );
			ToolTipAnim = anim.find( a1 );
		}

		ImVec2 TextSize = ::Utils::CalcTextSize( g_Variables.m_FontNormal, (int)g_Variables.m_FontNormal->FontSize, Desc );
		ImVec2 IconTextSize = ::Utils::CalcTextSize( g_Variables.FontAwesomeSolid, (int)g_Variables.FontAwesomeSolid->FontSize, Icon );

		ToolTipAnim->second.GlobalAlpha = ImLerp( ToolTipAnim->second.GlobalAlpha, Hovered ? 1.f : 0.f, ImGui::GetIO( ).DeltaTime * 8 );
		ToolTipAnim->second.SlideX = ImLerp( ToolTipAnim->second.SlideX, Hovered ? ( IconTextSize.x + TextSize.x + Padding + Spacing ) : 0.f, ImGui::GetIO( ).DeltaTime * 8 );
		ToolTipAnim->second.TextColor = ImLerp( ToolTipAnim->second.TextColor, Hovered ? ImVec4( ImColor( 180, 180, 180 ) ) : ImVec4( ImColor( 180, 180, 180, 0 ) ), ImGui::GetIO( ).DeltaTime * 12 );
		ToolTipAnim->second.IconColor = ImLerp( ToolTipAnim->second.IconColor, Hovered ? ImVec4( g_Col.Base ) : ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 0.f ), ImGui::GetIO( ).DeltaTime * 8 );

		ImGui::PushStyleVar( ImGuiStyleVar_Alpha, ToolTipAnim->second.GlobalAlpha );


		ImVec2 RectEndPos = ImVec2( Pos.x + ToolTipAnim->second.SlideX, Pos.y + TextSize.y + Padding );
		DrawList->AddRectFilled( Pos, RectEndPos, ImGui::GetColorU32( ImVec4( ImColor( 16, 16, 18 ) ) ), Rounding );
		DrawList->AddRect( Pos, RectEndPos, ImGui::GetColorU32( ImVec4( ImColor( 22, 22, 24 ) ) ), Rounding );


		DrawList->AddText( g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize, ImVec2( Pos.x + Padding / 2, Pos.y + ( ( TextSize.y + Padding ) / 2 - IconTextSize.y / 2 ) ), ImGui::GetColorU32( ToolTipAnim->second.IconColor ), Icon );

		if ( ToolTipAnim->second.SlideX < TextSize.x + Padding ) {

			//ChatGPT patrocina
			std::string ClippedDesc = Desc;
			while ( ImGui::CalcTextSize( ClippedDesc.c_str( ) ).x > ToolTipAnim->second.SlideX - Padding && !ClippedDesc.empty( ) ) {
				ClippedDesc.pop_back( );
			}

			DrawList->AddText( g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, ImVec2( Pos.x + Padding / 2 + ( IconTextSize.x + Spacing ), Pos.y + Padding / 2 ), ImGui::GetColorU32( ToolTipAnim->second.TextColor ), ClippedDesc.c_str( ) );
		}
		else {
			DrawList->AddText( g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, ImVec2( Pos.x + Padding / 2 + ( IconTextSize.x + Spacing ), Pos.y + Padding / 2 ), ImGui::GetColorU32( ToolTipAnim->second.TextColor ), Desc );
		}

		ImGui::PopStyleVar( );

		//return Check;
	}

	inline bool CheckBox( const char * Label, bool * Checked, bool bToolTip = false, const char * ToolTipMsg = "", const char * ToolTipIcon = "" ) {
		ImGuiWindow * Window = ImGui::GetCurrentWindow( );
		if ( Window->SkipItems )
			return false;

		ImGuiContext & g = *GImGui;
		const ImGuiStyle & style = g.Style;

		std::string UniqueID = ( std::string ) Label + std::to_string( ( int ) Checked );
		const ImGuiID id = Window->GetID( UniqueID.c_str( ) );

		float Width = ImGui::GetWindowContentRegionMax( ).x - ImGui::GetWindowContentRegionMin( ).x - ( Window->ScrollbarY ? 5.f : 0.f );
		//if ( CustomWidth != 0.f ) {
		//	Width = CustomWidth - ImGui::GetWindowContentRegionMin( ).x - ( Window->ScrollbarY ? 5.f : 0.f );
		//}

		ImVec2 TextSize = ImGui::CalcTextSize( Label );
		const ImVec2 CheckBoxSize( 36, 18 );

		const ImVec2 Pos = Window->DC.CursorPos;
		const ImRect Rect( Pos, Pos + ImVec2( Width, CheckBoxSize.y - 4 ) );
		const ImRect Clickable( Pos, Pos + ImVec2( Width, CheckBoxSize.y ) );

		ImGui::ItemSize( Rect, style.FramePadding.y );

		if ( !ImGui::ItemAdd( Rect, id, &Clickable ) ) {
			return false;
		}

		bool Hovered, Held;
		bool Pressed = ImGui::ButtonBehavior( Clickable, id, &Hovered, &Held );
		if ( Pressed ) {
			*Checked = !( *Checked );
			ImGui::MarkItemEdited( id );
		}

		struct WidCheckBox_t {
			ImVec4 BackGroundColor = ImColor( 18, 18, 20 );
			ImVec4 BackGroundColorEnd = ImColor( 18, 18, 20 );
			ImVec4 LabelColor = g_Col.SecundaryText;

			float SlideX = 9.f;
			ImVec4 CircleColor = ImColor( 40, 40, 45, 255 );
			ImVec4 IconColor = ImColor( 245, 158, 66, 0 );
		};

		static std::map<ImGuiID, WidCheckBox_t> anim;
		if (anim.size() > 500) anim.clear();
		auto CheckBoxAnim = anim.find( id );

		if ( CheckBoxAnim == anim.end( ) )
		{
			anim.insert( { id, WidCheckBox_t( ) } );
			CheckBoxAnim = anim.find( id );
		}

		ImVec2 IconTextSize = ::Utils::CalcTextSize( g_Variables.FontAwesomeSolid, (int)g_Variables.FontAwesomeSolid->FontSize, ICON_FA_TRIANGLE_EXCLAMATION );

		float circle_radius = (CheckBoxSize.y / 2.f) - 2.f;
		float target_circle_pos = *Checked ? (CheckBoxSize.x - circle_radius - 2.f) : (circle_radius + 2.f);

		CheckBoxAnim->second.SlideX = ImLerp( CheckBoxAnim->second.SlideX, target_circle_pos, g.IO.DeltaTime * 12.f );
		
		ImVec4 target_circle_color = *Checked ? ImVec4(ImColor(20, 20, 20, 255)) : ImVec4(ImColor(60, 60, 65, 255));
		CheckBoxAnim->second.CircleColor = ImLerp( CheckBoxAnim->second.CircleColor, target_circle_color, g.IO.DeltaTime * 12.f );

		CheckBoxAnim->second.IconColor = ImLerp( CheckBoxAnim->second.IconColor, Hovered || *Checked ? ImVec4( g_Col.Base ) : ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 0.f ), ImGui::GetIO( ).DeltaTime * 12 );
		CheckBoxAnim->second.LabelColor = ImLerp( CheckBoxAnim->second.LabelColor, *Checked ? g_Col.FeaturesText : g_Col.SecundaryFeaturesText, g.IO.DeltaTime * 8.f );
		CheckBoxAnim->second.BackGroundColor = ImLerp( CheckBoxAnim->second.BackGroundColor, *Checked ? ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 1.f ) : Hovered ? ImVec4( ImColor( 40, 40, 45 ) ) : ImVec4( ImColor( 30, 30, 35 ) ), g.IO.DeltaTime * 10.f );
		CheckBoxAnim->second.BackGroundColorEnd = ImLerp( CheckBoxAnim->second.BackGroundColorEnd, *Checked ? ImVec4( g_Col.BaseEnd.x, g_Col.BaseEnd.y, g_Col.BaseEnd.z, 1.f ) : Hovered ? ImVec4( ImColor( 40, 40, 45 ) ) : ImVec4( ImColor( 30, 30, 35 ) ), g.IO.DeltaTime * 10.f );

		Window->DrawList->AddRectFilledMultiColor( ImVec2( Rect.Max.x - CheckBoxSize.x, Rect.Min.y ), ImVec2( Rect.Max.x, Rect.Min.y + CheckBoxSize.y ), ImGui::GetColorU32( CheckBoxAnim->second.BackGroundColor ), ImGui::GetColorU32( CheckBoxAnim->second.BackGroundColorEnd ), ImGui::GetColorU32( CheckBoxAnim->second.BackGroundColorEnd ), ImGui::GetColorU32( CheckBoxAnim->second.BackGroundColor ), CheckBoxSize.y / 2.f );
		//Window->DrawList->AddRect( Rect.Min, Rect.Min + CheckBoxSize, ImGui::GetColorU32( ImVec4( ImColor( 30, 30, 32 ) ) ), CheckBoxSize.y / 2.f );

		ImVec2 CircleCenter( Rect.Max.x - CheckBoxSize.x + CheckBoxAnim->second.SlideX, Rect.Min.y + CheckBoxSize.y / 2.f );
		Window->DrawList->AddCircleFilled( CircleCenter, circle_radius, ImGui::GetColorU32( CheckBoxAnim->second.CircleColor ), 32 );

		if ( bToolTip )
		{
			ToolTip( Label, ToolTipMsg, ToolTipIcon, Hovered && g_MenuInfo.IsOpen );
			//Window->DrawList->AddText( g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize, ImVec2( Rect.Min.x + CheckBoxSize.x + 8.f + ( TextSize.x + 8 ), Pos.y + Rect.Max.y / 2 - ( Pos.y + IconTextSize.y ) / 2 ), ImGui::GetColorU32( CheckBoxAnim->second.IconColor ), ICON_FA_TRIANGLE_EXCLAMATION );
		}

		Window->DrawList->AddText( ImVec2( Rect.Min.x, Pos.y + Rect.Max.y / 2 - ( Pos.y + TextSize.y ) / 2 ), ImGui::GetColorU32( CheckBoxAnim->second.LabelColor ), Label );

		//Window->DrawList->AddText( g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize, ImVec2( Rect.Min.x + CheckBoxSize.x + 8.f, Pos.y + Rect.Max.y / 2 - ( Pos.y + TextSize.y ) / 2 ) + ImVec2( TextSize.x + 8, 0 ), ImGui::GetColorU32( ImVec4( ImColor( 204, 76, 67 ) ) ), ICON_FA_CIRCLE_EXCLAMATION );
		IMGUI_TEST_ENGINE_ITEM_INFO( id, Label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | ( *Checked ? ImGuiItemStatusFlags_Checked : 0 ) );
		return Pressed;
	}

	inline void ColorPicker( const char * label, float * col )
	{
		ImGuiContext& g = *GImGui;
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImGui::PushStyleVar( ImGuiStyleVar_FrameRounding, 4.f );
		ImGui::PushStyleVar( ImGuiStyleVar_PopupRounding, 6.f );
		ImGui::PushStyleColor( ImGuiCol_PopupBg, ImVec4( 0.07f, 0.07f, 0.08f, 1.0f ) );
		ImGui::PushStyleColor( ImGuiCol_Border, ImVec4( 1.0f, 1.0f, 1.0f, 0.05f ) );

		if ( ImGui::ColorButton( label, *( ImVec4 * ) col, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_AlphaPreview, ImVec2( 22, 22 ) ) )
			ImGui::OpenPopup( label );

		if ( ImGui::BeginPopup( label ) ) {
			ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 8, 8 ) );
			
			// Custom modern color picker style
			ImGui::ColorPicker4( label, col, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHex );
			
			ImGui::PopStyleVar( );
			ImGui::EndPopup( );
		}
		ImGui::PopStyleColor( 2 );
		ImGui::PopStyleVar( 2 );
	}

	inline bool CheckBoxCfg( const char * Label, bool * Checked, std::function<void( )> Components, bool bToolTip = false, const char * ToolTipMsg = "", const char * ToolTipIcon = "" ) {
		ImGuiWindow * Window = ImGui::GetCurrentWindow( );
		if ( Window->SkipItems )
			return false;

		ImGuiContext & g = *GImGui;
		const ImGuiStyle & style = g.Style;

		std::string UniqueID = ( std::string ) Label + std::to_string( ( int ) Checked );
		const ImGuiID id = Window->GetID( UniqueID.c_str( ) );

		float Width = ImGui::GetWindowContentRegionMax( ).x - ImGui::GetWindowContentRegionMin( ).x - ( Window->ScrollbarY ? 5.f : 0.f );

		ImVec2 TextSize = ImGui::CalcTextSize( Label );
		const ImVec2 CheckBoxSize( 36, 18 );

		const ImVec2 Pos = Window->DC.CursorPos;
		const ImRect Rect( Pos, Pos + ImVec2( Width, CheckBoxSize.y - 4 ) );
		const ImRect Clickable( Pos, Pos + ImVec2( Width, CheckBoxSize.y ) );

		ImGui::ItemSize( Rect, style.FramePadding.y );

		if ( !ImGui::ItemAdd( Rect, id, &Clickable ) ) {
			return false;
		}

		bool Hovered, Held;
		bool Pressed = ImGui::ButtonBehavior( Clickable, id, &Hovered, &Held );
		if ( Pressed ) {
			*Checked = !( *Checked );
			ImGui::MarkItemEdited( id );
		}

		struct WidCheckBox_t {
			ImVec4 BackGroundColor = ImColor( 18, 18, 20 );
			ImVec4 BackGroundColorEnd = ImColor( 18, 18, 20 );
			ImVec4 LabelColor = g_Col.SecundaryText;

			float SlideX = 9.f;
			ImVec4 CircleColor = ImColor( 40, 40, 45, 255 );

			float PopupAlpha = 0.f;

			ImVec4 IconColor = ImColor( 245, 158, 66, 0 );
			float GearRotation = 0.f;
			bool PopupActive = false;
		};

		static std::map<ImGuiID, WidCheckBox_t> anim;
		if (anim.size() > 500) anim.clear();
		auto CheckBoxAnim = anim.find( id );

		if ( CheckBoxAnim == anim.end( ) )
		{
			anim.insert( { id, WidCheckBox_t( ) } );
			CheckBoxAnim = anim.find( id );
		}

		float circle_radius = (CheckBoxSize.y / 2.f) - 2.f;
		float target_circle_pos = *Checked ? (CheckBoxSize.x - circle_radius - 2.f) : (circle_radius + 2.f);

		CheckBoxAnim->second.SlideX = ImLerp( CheckBoxAnim->second.SlideX, target_circle_pos, g.IO.DeltaTime * 12.f );
		
		ImVec4 target_circle_color = *Checked ? ImVec4(ImColor(20, 20, 20, 255)) : ImVec4(ImColor(60, 60, 65, 255));
		CheckBoxAnim->second.CircleColor = ImLerp( CheckBoxAnim->second.CircleColor, target_circle_color, g.IO.DeltaTime * 12.f );

		CheckBoxAnim->second.LabelColor = ImLerp( CheckBoxAnim->second.LabelColor, *Checked ? ImVec4(g_Col.FeaturesText) : ImVec4(g_Col.SecundaryFeaturesText), g.IO.DeltaTime * 8.f );
		CheckBoxAnim->second.BackGroundColor = ImLerp( CheckBoxAnim->second.BackGroundColor, *Checked ? ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 1.f ) : (Hovered ? ImVec4( ImColor( 40, 40, 45 ) ) : ImVec4( ImColor( 30, 30, 35 ) )), g.IO.DeltaTime * 10.f );
		CheckBoxAnim->second.BackGroundColorEnd = ImLerp( CheckBoxAnim->second.BackGroundColorEnd, *Checked ? ImVec4( g_Col.BaseEnd.x, g_Col.BaseEnd.y, g_Col.BaseEnd.z, 1.f ) : (Hovered ? ImVec4( ImColor( 40, 40, 45 ) ) : ImVec4( ImColor( 30, 30, 35 ) )), g.IO.DeltaTime * 10.f );

		Window->DrawList->AddRectFilledMultiColor( ImVec2( Rect.Max.x - CheckBoxSize.x, Rect.Min.y ), ImVec2( Rect.Max.x, Rect.Min.y + CheckBoxSize.y ), ImGui::GetColorU32( CheckBoxAnim->second.BackGroundColor ), ImGui::GetColorU32( CheckBoxAnim->second.BackGroundColorEnd ), ImGui::GetColorU32( CheckBoxAnim->second.BackGroundColorEnd ), ImGui::GetColorU32( CheckBoxAnim->second.BackGroundColor ), CheckBoxSize.y / 2.f );
		//Window->DrawList->AddRect( Rect.Min, Rect.Min + CheckBoxSize, ImGui::GetColorU32( ImVec4( ImColor( 30, 30, 32 ) ) ), CheckBoxSize.y / 2.f );

		ImVec2 CircleCenter( Rect.Max.x - CheckBoxSize.x + CheckBoxAnim->second.SlideX, Rect.Min.y + CheckBoxSize.y / 2.f );
		Window->DrawList->AddCircleFilled( CircleCenter, circle_radius, ImGui::GetColorU32( CheckBoxAnim->second.CircleColor ), 32 );

		if ( bToolTip ) {
			ToolTip( Label, ToolTipMsg, ToolTipIcon, Hovered && g_MenuInfo.IsOpen );
		}

		ImVec2 TextPos = ImVec2( Rect.Min.x, Pos.y + Rect.Max.y / 2 - ( Pos.y + TextSize.y ) / 2 );
		Window->DrawList->AddText( TextPos, ImGui::GetColorU32( CheckBoxAnim->second.LabelColor ), Label );

		////////////////////////////
		// CFG Popup
		////////////////////////////
		static bool IconHovered = false;
		ImVec2 IconTextSize = ::Utils::CalcTextSize( g_Variables.FontAwesomeSolid, (int)g_Variables.FontAwesomeSolid->FontSize - 4, ICON_FA_GEAR ); //ICON_FA_ELLIPSIS
		ImVec2 MousePos = ImGui::GetMousePos( );
		ImVec2 MinPos = TextPos + ImVec2( TextSize.x, ( CheckBoxSize.y / 2 - TextSize.y / 2 ) - 4 );
		ImVec2 MaxPos = TextPos + ImVec2( TextSize.x + ( 10 * 2 ) + IconTextSize.x, ( MinPos.y - TextPos.y ) + IconTextSize.y + 4 );

		if ( MousePos.x > MinPos.x && MousePos.x < MaxPos.x && MousePos.y > MinPos.y && MousePos.y < MaxPos.y ) {
			IconHovered = true;
		}
		else {
			IconHovered = false;
		}

		static ImVec2 PopupSize( 180, 90 );
		ImVec2 PopupMin = ImVec2(Rect.Max.x - CheckBoxSize.x, TextPos.y) + ImVec2( -PopupSize.x, IconTextSize.y + 4 );

		if ( IconHovered && g.IO.MouseClicked[ 0 ] ) {
			CheckBoxAnim->second.PopupActive = !CheckBoxAnim->second.PopupActive;
		}
		else if ( !IconHovered && g.IO.MouseClicked[ 0 ] && CheckBoxAnim->second.PopupActive ) {
			if ( !( MousePos.x > PopupMin.x && MousePos.x < PopupMin.x + PopupSize.x && MousePos.y > PopupMin.y && MousePos.y < PopupMin.y + PopupSize.y ) ) {
				CheckBoxAnim->second.PopupActive = false;
			}
		}

		CheckBoxAnim->second.GearRotation = ImLerp( CheckBoxAnim->second.GearRotation, CheckBoxAnim->second.PopupActive ? 1.f : -1.f, g.IO.DeltaTime * 10.f );
		CheckBoxAnim->second.IconColor = ImLerp( CheckBoxAnim->second.IconColor, CheckBoxAnim->second.PopupActive ? ImVec4(g_Col.Base) : ImVec4(ImColor( 60, 60, 60 )), g.IO.DeltaTime * 10.f );

		ImRotateStart( );
		Window->DrawList->AddText( g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize - 4, TextPos + ImVec2( TextSize.x + 10, CheckBoxSize.y / 2 - TextSize.y / 2 ), ImGui::GetColorU32( CheckBoxAnim->second.IconColor ), ICON_FA_GEAR ); //ICON_FA_ELLIPSIS
		ImRotateEnd( 1.57f * CheckBoxAnim->second.GearRotation );

		CheckBoxAnim->second.PopupAlpha = ImClamp( CheckBoxAnim->second.PopupAlpha + ( 6.f * g.IO.DeltaTime * ( CheckBoxAnim->second.PopupActive && g_MenuInfo.IsOpen ? 1.f : -1.f ) ), 0.f, 1.f );

		if ( CheckBoxAnim->second.PopupAlpha >= 0.001f ) {
			PushStyleVar( ImGuiStyleVar_Alpha, CheckBoxAnim->second.PopupAlpha );
			PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 10, 10 ) );
			PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2( 10, 10 ) );
			PushStyleVar( ImGuiStyleVar_CellPadding, ImVec2( 10, 10 ) );
			PushStyleVar( ImGuiStyleVar_WindowRounding, 4.f );
			PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 15, 15 ) );
			PushStyleVar( ImGuiStyleVar_PopupBorderSize, 1 );
			PushStyleColor( ImGuiCol_Border, GetColorU32( ImVec4( ImColor( 20, 20, 22 ) ) ) );
			PushStyleColor( ImGuiCol_PopupBg, GetColorU32( ImVec4( ImColor( 14, 14, 16 ) ) ) );

			SetNextWindowSize( ImVec2( PopupSize.x, 0 ) );
			SetNextWindowPos( PopupMin );

			Begin( Label, NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_WithoutScrollClamp | ImGuiWindowFlags_Tooltip );
			{
				PopupSize = ImGui::GetWindowSize( );
				Components( );
			}

			PopStyleVar( 7 );
			PopStyleColor( 2 );

			End( );
		}
		/////////////////////


		IMGUI_TEST_ENGINE_ITEM_INFO( id, Label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | ( *Checked ? ImGuiItemStatusFlags_Checked : 0 ) );
		return Pressed;
	}

	inline bool CfgButton( const char * Label, std::function<void( )> Components )
	{
		ImGuiWindow * Window = ImGui::GetCurrentWindow( );
		if ( Window->SkipItems )
			return false;

		ImGuiContext & g = *GImGui;
		const ImGuiStyle & style = g.Style;

		std::string IdStr = ( std::string ) Label;
		const ImGuiID id = Window->GetID( IdStr.c_str( ) );

		ImVec2 IconTextSize = ::Utils::CalcTextSize( g_Variables.FontAwesomeSolid, (int)g_Variables.FontAwesomeSolid->FontSize - 4, ICON_FA_GEAR ); //ICON_FA_ELLIPSIS
		ImVec2 MousePos = ImGui::GetMousePos( );

		const ImVec2 Pos = Window->DC.CursorPos;
		const ImRect Rect( Pos, Pos + ImVec2( IconTextSize.x, IconTextSize.y ) );

		ImGui::ItemSize( Rect, style.FramePadding.y );

		if ( !ImGui::ItemAdd( Rect, id ) ) {
			return false;
		}

		bool Hovered, Held;
		bool Pressed = ImGui::ButtonBehavior( Rect, id, &Hovered, &Held );
		if ( Pressed ) {
			ImGui::MarkItemEdited( id );
		}

		struct CfgBtn_t {
			ImVec4 IconColor = ImColor( 245, 158, 66, 0 );
			float GearRotation = 0.f;
			float PopupAlpha = 0.f;
			bool PopupActive = false;
		};

		static std::map<ImGuiID, CfgBtn_t> anim;
		if (anim.size() > 500) anim.clear();
		auto CfgAnim = anim.find( id );

		if ( CfgAnim == anim.end( ) )
		{
			anim.insert( { id, CfgBtn_t( ) } );
			CfgAnim = anim.find( id );
		}

		static ImVec2 PopupSize( 180, 90 );
		ImVec2 PopupMin = Pos + ImVec2( IconTextSize.x + 4, IconTextSize.y + 4 );

		if ( Hovered && g.IO.MouseClicked[ 0 ] ) {
			CfgAnim->second.PopupActive = !CfgAnim->second.PopupActive;
		}
		else if ( !Hovered && g.IO.MouseClicked[ 0 ] && CfgAnim->second.PopupActive ) {
			if ( !( MousePos.x > PopupMin.x && MousePos.x < PopupMin.x + PopupSize.x && MousePos.y > PopupMin.y && MousePos.y < PopupMin.y + PopupSize.y ) ) {
				CfgAnim->second.PopupActive = false;
			}
		}

		CfgAnim->second.GearRotation = ImLerp( CfgAnim->second.GearRotation, CfgAnim->second.PopupActive ? 1.f : -1.f, g.IO.DeltaTime * 10.f );
		CfgAnim->second.IconColor = ImLerp( CfgAnim->second.IconColor, CfgAnim->second.PopupActive ? ImVec4(g_Col.Base) : ImVec4(ImColor( 60, 60, 60 )), g.IO.DeltaTime * 10.f );

		ImRotateStart( );
		Window->DrawList->AddText( g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize - 4, Pos, ImGui::GetColorU32( CfgAnim->second.IconColor ), ICON_FA_GEAR ); //ICON_FA_ELLIPSIS
		ImRotateEnd( 1.57f * CfgAnim->second.GearRotation );

		CfgAnim->second.PopupAlpha = ImClamp( CfgAnim->second.PopupAlpha + ( 6.f * g.IO.DeltaTime * ( CfgAnim->second.PopupActive && g_MenuInfo.IsOpen ? 1.f : -1.f ) ), 0.f, 1.f );

		if ( CfgAnim->second.PopupAlpha >= 0.001f ) {
			PushStyleVar( ImGuiStyleVar_Alpha, CfgAnim->second.PopupAlpha );
			PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 10, 10 ) );
			PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2( 10, 10 ) );
			PushStyleVar( ImGuiStyleVar_CellPadding, ImVec2( 10, 10 ) );
			PushStyleVar( ImGuiStyleVar_WindowRounding, 4.f );
			PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 15, 15 ) );
			PushStyleVar( ImGuiStyleVar_PopupBorderSize, 1 );
			PushStyleColor( ImGuiCol_Border, GetColorU32( ImVec4( ImColor( 20, 20, 22 ) ) ) );
			PushStyleColor( ImGuiCol_PopupBg, GetColorU32( ImVec4( ImColor( 14, 14, 16 ) ) ) );

			SetNextWindowSize( ImVec2( PopupSize.x, 0 ) );
			SetNextWindowPos( PopupMin );

			Begin( Label, NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_WithoutScrollClamp | ImGuiWindowFlags_Tooltip );
			{
				PopupSize = ImGui::GetWindowSize( );
				Components( );
			}

			PopStyleVar( 7 );
			PopStyleColor( 2 );

			End( );
		}
	}

	inline bool CheckBoxPage( const char * Label, bool * Checked, std::function<void( )> Code, bool bToolTip = false, const char * ToolTipMsg = "" ) {
		ImGuiWindow * Window = ImGui::GetCurrentWindow( );
		if ( Window->SkipItems )
			return false;

		ImGuiContext & g = *GImGui;
		const ImGuiStyle & style = g.Style;

		std::string UniqueID = ( std::string ) Label + std::to_string( ( int ) Checked );
		const ImGuiID id = Window->GetID( UniqueID.c_str( ) );

		float Width = ImGui::GetWindowContentRegionMax( ).x - ImGui::GetWindowContentRegionMin( ).x - ( Window->ScrollbarY ? 5.f : 0.f );

		ImVec2 TextSize = ImGui::CalcTextSize( Label );
		const ImVec2 CheckBoxSize( 36, 18 );

		const ImVec2 Pos = Window->DC.CursorPos;
		const ImRect Rect( Pos, Pos + ImVec2( Width, CheckBoxSize.y - 4 ) );
		const ImRect Clickable( Pos, Pos + ImVec2( Width, CheckBoxSize.y ) );

		ImGui::ItemSize( Rect, style.FramePadding.y );

		if ( !ImGui::ItemAdd( Rect, id, &Clickable ) ) {
			return false;
		}

		bool Hovered, Held;
		bool Pressed = ImGui::ButtonBehavior( Clickable, id, &Hovered, &Held );
		if ( Pressed ) {
			*Checked = !( *Checked );
			ImGui::MarkItemEdited( id );
		}

		struct WidCheckBox_t {
			ImVec4 BackGroundColor = ImColor( 18, 18, 20 );
			ImVec4 BackGroundColorEnd = ImColor( 18, 18, 20 );
			ImVec4 LabelColor = g_Col.SecundaryText;

			float SlideX = 9.f;
			ImVec4 CircleColor = ImColor( 40, 40, 45, 255 );

			float SlideUp = 0.f;
			ImVec4 IconColor = ImColor( 245, 158, 66, 0 );
		};

		static std::map<ImGuiID, WidCheckBox_t> anim;
		if (anim.size() > 500) anim.clear();
		auto CheckBoxAnim = anim.find( id );

		if ( CheckBoxAnim == anim.end( ) )
		{
			anim.insert( { id, WidCheckBox_t( ) } );
			CheckBoxAnim = anim.find( id );
		}

		float circle_radius = (CheckBoxSize.y / 2.f) - 2.f;
		float target_circle_pos = *Checked ? (CheckBoxSize.x - circle_radius - 2.f) : (circle_radius + 2.f);

		CheckBoxAnim->second.SlideX = ImLerp( CheckBoxAnim->second.SlideX, target_circle_pos, g.IO.DeltaTime * 12.f );
		
		ImVec4 target_circle_color = *Checked ? ImVec4(ImColor(20, 20, 20, 255)) : ImVec4(ImColor(60, 60, 65, 255));
		CheckBoxAnim->second.CircleColor = ImLerp( CheckBoxAnim->second.CircleColor, target_circle_color, g.IO.DeltaTime * 12.f );

		CheckBoxAnim->second.LabelColor = ImLerp( CheckBoxAnim->second.LabelColor, *Checked ? ImVec4(g_Col.FeaturesText) : ImVec4(g_Col.SecundaryFeaturesText), g.IO.DeltaTime * 8.f );
		CheckBoxAnim->second.BackGroundColor = ImLerp( CheckBoxAnim->second.BackGroundColor, *Checked ? ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 1.f ) : (Hovered ? ImVec4( ImColor( 40, 40, 45 ) ) : ImVec4( ImColor( 30, 30, 35 ) )), g.IO.DeltaTime * 10.f );
		CheckBoxAnim->second.BackGroundColorEnd = ImLerp( CheckBoxAnim->second.BackGroundColorEnd, *Checked ? ImVec4( g_Col.BaseEnd.x, g_Col.BaseEnd.y, g_Col.BaseEnd.z, 1.f ) : (Hovered ? ImVec4( ImColor( 40, 40, 45 ) ) : ImVec4( ImColor( 30, 30, 35 ) )), g.IO.DeltaTime * 10.f );

		Window->DrawList->AddRectFilledMultiColor( ImVec2( Rect.Max.x - CheckBoxSize.x, Rect.Min.y ), ImVec2( Rect.Max.x, Rect.Min.y + CheckBoxSize.y ), ImGui::GetColorU32( CheckBoxAnim->second.BackGroundColor ), ImGui::GetColorU32( CheckBoxAnim->second.BackGroundColorEnd ), ImGui::GetColorU32( CheckBoxAnim->second.BackGroundColorEnd ), ImGui::GetColorU32( CheckBoxAnim->second.BackGroundColor ), CheckBoxSize.y / 2.f );
		//Window->DrawList->AddRect( Rect.Min, Rect.Min + CheckBoxSize, ImGui::GetColorU32( ImVec4( ImColor( 30, 30, 32 ) ) ), CheckBoxSize.y / 2.f );

		ImVec2 CircleCenter( Rect.Max.x - CheckBoxSize.x + CheckBoxAnim->second.SlideX, Rect.Min.y + CheckBoxSize.y / 2.f );
		Window->DrawList->AddCircleFilled( CircleCenter, circle_radius, ImGui::GetColorU32( CheckBoxAnim->second.CircleColor ), 32 );

		ImVec2 TextPos = ImVec2( Rect.Min.x, Pos.y + Rect.Max.y / 2 - ( Pos.y + TextSize.y ) / 2 );
		Window->DrawList->AddText( TextPos, ImGui::GetColorU32( CheckBoxAnim->second.LabelColor ), Label );

		////////////////////////////
		// Link Obj
		////////////////////////////
		static bool IconHovered = false;
		ImVec2 IconTextSize = ::Utils::CalcTextSize( g_Variables.FontAwesomeSolid, (int)g_Variables.FontAwesomeSolid->FontSize - 4, ICON_FA_SHARE );
		ImVec2 MousePos = ImGui::GetMousePos( );
		ImVec2 MinPos = TextPos + ImVec2( TextSize.x, ( CheckBoxSize.y / 2 - TextSize.y / 2 ) - 4 );
		ImVec2 MaxPos = TextPos + ImVec2( TextSize.x + ( 10 * 2 ) + IconTextSize.x, ( MinPos.y - TextPos.y ) + IconTextSize.y + 4 );

		if ( MousePos.x > MinPos.x && MousePos.x < MaxPos.x && MousePos.y > MinPos.y && MousePos.y < MaxPos.y ) {
			IconHovered = true;
		}
		else {
			IconHovered = false;
		}

		if ( bToolTip ) {
			ToolTip( Label, ToolTipMsg, ICON_FA_SHARE, IconHovered && g_MenuInfo.IsOpen );
		}

		CheckBoxAnim->second.SlideUp = ImLerp( CheckBoxAnim->second.SlideUp, IconHovered ? 2.f : 0.f,
			g.IO.DeltaTime * 10.f );
		CheckBoxAnim->second.IconColor = ImLerp( CheckBoxAnim->second.IconColor, IconHovered
			? ImVec4(g_Col.Base) : ImVec4(ImColor( 60, 60, 60 )), g.IO.DeltaTime * 10.f );

		Window->DrawList->AddText( g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize - 4
			, TextPos + ImVec2( TextSize.x + 10, ( CheckBoxSize.y / 2 - TextSize.y / 2 ) - CheckBoxAnim->second.SlideUp ),
			ImGui::GetColorU32( CheckBoxAnim->second.IconColor ), ICON_FA_SHARE );

		if ( IconHovered && g.IO.MouseClicked[ 0 ] ) {
			Code( );
		}

		IMGUI_TEST_ENGINE_ITEM_INFO( id, Label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | ( *Checked ? ImGuiItemStatusFlags_Checked : 0 ) );
		return Pressed;
	}

	inline void TextCentered( const char * text, int m ) {

		ImVec2 textSize = ImGui::CalcTextSize( text );
		float posX = ( g_MenuInfo.MenuSize.x  -textSize.x ) * 0.5f;
		float posY = ( g_MenuInfo.MenuSize.y - textSize.y ) * 0.5f;

		switch ( m ) {

		case 0:
			ImGui::SetCursorPos( { posX, posY } );
			ImGui::Text( text );
			break;
		case 1:
			ImGui::SetCursorPosX( posX );
			ImGui::Text( text );
			break;
		case 2:
			ImGui::SetCursorPosY( posY );
			ImGui::Text( text );
			break;
		default:
			ImGui::SetCursorPos( { posX, posY } );
			ImGui::Text( text );
			break;

		}
	}


	inline bool ButtonWithIcon( const char * icon, const char * label, const ImVec2 & size_arg, ImGuiButtonFlags flags ) {
		struct button_struct {
			ImVec4 BorderCol;
			ImVec4 background;
			ImVec4 LabelColor;
			float UpBackground;
		};

		ImGuiWindow * window = ImGui::GetCurrentWindow( );
		if ( window->SkipItems )
			return false;

		ImGuiContext & g = *GImGui;
		const ImGuiStyle & style = g.Style;
		const ImGuiID id = window->GetID( label );
		const ImVec2 label_size = g_Variables.m_FontNormal->CalcTextSizeA( g_Variables.m_FontNormal->FontSize, FLT_MAX, 0, label );
		const ImVec2 IconTextSize = g_Variables.FontAwesomeSolid->CalcTextSizeA( g_Variables.FontAwesomeSolid->FontSize - 4, FLT_MAX, 0, icon );
		const ImVec2 pos = window->DC.CursorPos;

		static std::map<ImGuiID, button_struct> anim;
		if (anim.size() > 500) anim.clear();
		auto it_anim = anim.find( id );

		if ( it_anim == anim.end( ) ) {
			anim.insert( { id, button_struct( ) } );
			it_anim = anim.find( id );
		}

		ImVec2 size = ImGui::CalcItemSize( size_arg, label_size.x + IconTextSize.x + style.FramePadding.x * 3.0f, label_size.y + style.FramePadding.y * 2.0f );

		const ImRect bb( pos, ImVec2( pos.x + size.x, pos.y + size.y ) );
		ImGui::ItemSize( size, 0.f );

		if ( !ImGui::ItemAdd( bb, id ) )
			return false;

		bool Hovered, Held, Pressed = ImGui::ButtonBehavior( bb, id, &Hovered, &Held, flags );

		it_anim->second.BorderCol = ImLerp( it_anim->second.BorderCol, Hovered ? ImVec4( g_Col.Base ) : ImVec4( ImColor( 18, 18, 20 ) ), g.IO.DeltaTime * 6.f );
		it_anim->second.background = ImLerp( it_anim->second.background, Hovered ? ImVec4( ImColor( 14, 14, 16 ) ) : ImVec4( ImColor( 14, 14, 16 ) ), g.IO.DeltaTime * 6.f );
		it_anim->second.LabelColor = ImLerp( it_anim->second.LabelColor, Hovered ? ImVec4( ImColor( 225, 225, 225 ) ) : ImVec4( ImColor( 225, 225, 225 ) ), g.IO.DeltaTime * 6.f );
		it_anim->second.UpBackground = ImLerp( it_anim->second.UpBackground, Hovered ? ( bb.Min.y - pos.y ) - ( bb.Max.y - pos.y ) : 0.f, g.IO.DeltaTime * 6.f );

		float totalWidth = label_size.x + IconTextSize.x + style.FramePadding.x;
		ImVec2 TextPos = { pos.x + ( size.x - totalWidth ) * 0.5f + IconTextSize.x + style.FramePadding.x, pos.y + ( size.y - label_size.y ) * 0.5f - 0.5f };
		ImVec2 TextWithoutIconPos = { pos.x + ( size.x - label_size.x ) * 0.5f + style.FramePadding.x, pos.y + ( size.y - label_size.y ) * 0.5f - 0.5f };
		ImVec2 IconPos = { pos.x + ( size.x - totalWidth ) * 0.5f, pos.y + ( size.y - IconTextSize.y ) * 0.5f - 0.5f };

		window->DrawList->AddRectFilled( bb.Min, bb.Max, ImGui::GetColorU32( it_anim->second.background ), 4 );
		window->DrawList->AddRect( bb.Min, bb.Max, ImGui::GetColorU32( it_anim->second.BorderCol ), 4 );

		window->DrawList->AddRectFilledMultiColor( ImVec2( bb.Min.x, bb.Max.y ), ImVec2( bb.Max.x, bb.Max.y + it_anim->second.UpBackground ), ImGui::GetColorU32( g_Col.Base ), ImGui::GetColorU32( g_Col.BaseEnd ), ImGui::GetColorU32( g_Col.BaseEnd ), ImGui::GetColorU32( g_Col.Base ), 4 );

		//window->DrawList->AddText( g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize - 4, IconPos, ImGui::GetColorU32( it_anim->second.LabelColor ), icon );
		window->DrawList->AddText( g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, TextWithoutIconPos, ImGui::GetColorU32( it_anim->second.LabelColor ), label );

		return Pressed;
	}

	inline bool Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		const float arrow_size = 30.f;
		float Width = ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x - (window->ScrollbarY ? 5.f : 0.f);

		ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		float height = 30.f;

		const ImVec2 pos = window->DC.CursorPos;
		const ImRect rect(pos + ImVec2(0, label_size.y + 5.f), pos + ImVec2(Width, label_size.y + 5.f + height));
		const ImRect total_rect(pos, rect.Max);

		ImGui::ItemSize(total_rect, style.FramePadding.y);
		if (!ImGui::ItemAdd(total_rect, id, &rect))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held);
		bool popup_open = ImGui::IsPopupOpen(id, ImGuiPopupFlags_None);

		if (pressed || g.NavActivateId == id)
		{
			if (!popup_open)
			{
				ImGui::OpenPopupEx(id, ImGuiPopupFlags_None);
				popup_open = true;
			}
			else
			{
				ImGui::ClosePopupToLevel(g.BeginPopupStack.Size, true);
				popup_open = false;
			}
		}

		// Render Label
		window->DrawList->AddText(g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, pos, ImGui::GetColorU32(ImVec4(ImColor(180, 180, 180))), label);

		// Render Background
		const ImU32 bg_col = ImGui::GetColorU32(ImVec4(ImColor(35, 35, 35)));
		const ImU32 border_col = ImGui::GetColorU32(ImVec4(ImColor(50, 50, 50)));
		window->DrawList->AddRectFilled(rect.Min, rect.Max, bg_col, 4.f);
		window->DrawList->AddRect(rect.Min, rect.Max, border_col, 4.f);

		// Render Text
		if (*current_item >= 0 && *current_item < items_count)
		{
			window->DrawList->AddText(g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, rect.Min + ImVec2(10.f, height / 2.f - label_size.y / 2.f), ImGui::GetColorU32(ImVec4(ImColor(180, 180, 180))), items[*current_item]);
		}

		// Render Arrow background
		const ImRect arrow_rect(ImVec2(rect.Max.x - arrow_size, rect.Min.y), rect.Max);
		window->DrawList->AddRectFilled(arrow_rect.Min, arrow_rect.Max, ImGui::GetColorU32(ImVec4(ImColor(45, 45, 45))), 4.f, ImDrawFlags_RoundCornersRight);
		window->DrawList->AddRect(arrow_rect.Min, arrow_rect.Max, border_col, 4.f, ImDrawFlags_RoundCornersRight);

		// Render Arrow (triangle)
		float arrow_w = 8.f;
		float arrow_h = 5.f;
		ImVec2 center = ImVec2(arrow_rect.Min.x + arrow_size / 2.f, arrow_rect.Min.y + height / 2.f);
		if (popup_open)
			window->DrawList->AddTriangleFilled(center + ImVec2(-arrow_w/2, arrow_h/2), center + ImVec2(arrow_w/2, arrow_h/2), center + ImVec2(0, -arrow_h/2), ImGui::GetColorU32(ImVec4(ImColor(180, 180, 180))));
		else
			window->DrawList->AddTriangleFilled(center + ImVec2(-arrow_w/2, -arrow_h/2), center + ImVec2(arrow_w/2, -arrow_h/2), center + ImVec2(0, arrow_h/2), ImGui::GetColorU32(ImVec4(ImColor(180, 180, 180))));

		bool value_changed = false;
		if (popup_open)
		{
			ImGui::SetNextWindowPos(rect.Min + ImVec2(0, height + 2.f));
			ImGui::SetNextWindowSize(ImVec2(Width, 0.f));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5, 5));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 4.f);
			ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(ImColor(35, 35, 35)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(50, 50, 50)));
			
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_Popup | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove;
			if (ImGui::BeginPopupEx(id, window_flags))
			{
				for (int i = 0; i < items_count; i++)
				{
					ImGui::PushID(i);
					bool item_selected = (i == *current_item);
					if (ImGui::Selectable(items[i], item_selected))
					{
						*current_item = i;
						value_changed = true;
					}
					if (item_selected)
						ImGui::SetItemDefaultFocus();
					ImGui::PopID();
				}
				ImGui::EndPopup();
			}
			ImGui::PopStyleColor(2);
			ImGui::PopStyleVar(2);
		}

		return value_changed;
	}

	inline bool Button( const char * label, const ImVec2 & size_arg, ImGuiButtonFlags flags, bool bToolTip = false, const char * ToolTipMsg = "", const char * ToolTipIcon = "" )
	{
		struct button13Anims {
			float closing_anim;
			float closing_alpha;
			float label_alpha;
			bool animation_complete;
		};

		ImGuiWindow * window = GetCurrentWindow( );
		if ( window->SkipItems )
			return false;

		ImGuiContext & g = *GImGui;
		const ImGuiStyle & style = g.Style;
		const ImGuiID id = window->GetID( label );
		const ImVec2 label_size = ImGui::CalcTextSize( label, NULL, true );
		ImDrawList * draw = GetWindowDrawList( );

		static std::map<ImGuiID, button13Anims> anim;
		if (anim.size() > 500) anim.clear();
		auto it_anim = anim.find( id );
		if ( it_anim == anim.end( ) )
		{
			anim.insert( { id, button13Anims( ) } );
			it_anim = anim.find( id );
		}

		ImVec2 pos = window->DC.CursorPos;
		if ( ( flags & ImGuiButtonFlags_AlignTextBaseLine ) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset ) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
			pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
		ImVec2 size = CalcItemSize( size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f );

		const ImRect bb( pos, pos + size );
		ItemSize( size, style.FramePadding.y );
		if ( !ItemAdd( bb, id ) )
			return false;

		if ( g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat )
			flags |= ImGuiButtonFlags_Repeat;

		bool hovered, held;
		bool pressed = ButtonBehavior( bb, id, &hovered, &held, flags );

		if ( bToolTip ) {
			ToolTip( label, ToolTipMsg, ToolTipIcon, hovered && g_MenuInfo.IsOpen );
		}

		it_anim->second.closing_anim = ImLerp( it_anim->second.closing_anim, ( hovered ? size.y : 0 ), g.IO.DeltaTime * 8.f );

		if ( hovered || pressed ) {
			if ( it_anim->second.label_alpha < 255.f )
				it_anim->second.label_alpha += 5.f / GetIO( ).Framerate * 160.f;

			if ( it_anim->second.closing_alpha < 255.f )
				it_anim->second.closing_alpha += 15.f / GetIO( ).Framerate * 160.f;
		}
		else {
			if ( it_anim->second.label_alpha > 0.f )
				it_anim->second.label_alpha -= 5.f / GetIO( ).Framerate * 160.f;

			if ( it_anim->second.closing_alpha > 0.f )
				it_anim->second.closing_alpha -= 10.f / GetIO( ).Framerate * 160.f;
		}

		// Render
		const ImU32 inside_solid_col = GetColorU32( ImVec4( ImColor( 35, 35, 35 ) ) );
		const ImU32 outside_solid_col = GetColorU32( ImVec4( ImColor( 50, 50, 50 ) ) );

		draw->AddRectFilled( ImVec2( bb.Min.x, bb.Min.y ), ImVec2( bb.Max.x, bb.Max.y ), inside_solid_col, 4 );
		draw->AddRect( bb.Min, bb.Max, outside_solid_col, 4 );

		PushStyleColor( ImGuiCol_Text, ColorConvertFloat4ToU32( ImColor( 180, 180, 180, 255 - ( int ) it_anim->second.label_alpha ) ) );
		RenderTextClipped( bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, ImVec2(0.5f, 0.5f), &bb );
		PopStyleColor( );

		PushStyleColor( ImGuiCol_Text, ColorConvertFloat4ToU32( ImColor( 255, 255, 255, ( int ) it_anim->second.label_alpha ) ) );
		RenderTextClipped( bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, ImVec2(0.5f, 0.5f), &bb );
		PopStyleColor( );

		IMGUI_TEST_ENGINE_ITEM_INFO( id, label, g.LastItemData.StatusFlags );

		return pressed;
	}

	inline bool ButtonHeld( const char * label, const ImVec2 & size_arg, ImGuiButtonFlags flags )
	{
		struct button13Anims {
			float closing_anim;
			float closing_alpha;
			float label_alpha;
			bool animation_complete;
		};

		ImGuiWindow * window = GetCurrentWindow( );
		if ( window->SkipItems )
			return false;

		ImGuiContext & g = *GImGui;
		const ImGuiStyle & style = g.Style;
		const ImGuiID id = window->GetID( label );
		const ImVec2 label_size = ImGui::CalcTextSize( label, NULL, true );
		ImDrawList * draw = GetWindowDrawList( );

		static std::map<ImGuiID, button13Anims> anim;
		if (anim.size() > 500) anim.clear();
		auto it_anim = anim.find( id );
		if ( it_anim == anim.end( ) )
		{
			anim.insert( { id, button13Anims( ) } );
			it_anim = anim.find( id );
		}

		ImVec2 pos = window->DC.CursorPos;
		if ( ( flags & ImGuiButtonFlags_AlignTextBaseLine ) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset ) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
			pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
		ImVec2 size = CalcItemSize( size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f );

		const ImRect bb( pos, pos + size );
		ItemSize( size, style.FramePadding.y );
		if ( !ItemAdd( bb, id ) )
			return false;

		if ( g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat )
			flags |= ImGuiButtonFlags_Repeat;

		bool hovered, held;
		bool pressed = ButtonBehavior( bb, id, &hovered, &held, flags );

		it_anim->second.closing_anim = ImLerp( it_anim->second.closing_anim, ( held ? size.y : 0 ), g.IO.DeltaTime * 8.f );

		if ( held || pressed ) {
			if ( it_anim->second.label_alpha < 255.f )
				it_anim->second.label_alpha += 5.f / GetIO( ).Framerate * 160.f;

			if ( it_anim->second.closing_alpha < 255.f )
				it_anim->second.closing_alpha += 15.f / GetIO( ).Framerate * 160.f;
		}
		else {
			if ( it_anim->second.label_alpha > 0.f )
				it_anim->second.label_alpha -= 5.f / GetIO( ).Framerate * 160.f;

			if ( it_anim->second.closing_alpha > 0.f )
				it_anim->second.closing_alpha -= 10.f / GetIO( ).Framerate * 160.f;
		}

		// Render
		const ImU32 inside_solid_col = GetColorU32( ImVec4( ImColor( 35, 35, 35 ) ) );
		const ImU32 outside_solid_col = GetColorU32( ImVec4( ImColor( 50, 50, 50 ) ) );
		const ImU32 inside_hover_col = ImColor( 180, 180, 180, ( int ) it_anim->second.closing_alpha );

		draw->AddRectFilled( ImVec2( bb.Min.x, bb.Min.y ), ImVec2( bb.Max.x, bb.Max.y ), inside_solid_col, 4 );
		draw->AddRect( bb.Min, bb.Max, outside_solid_col, 4 );
		draw->AddRectFilled( ImVec2( bb.Min.x, bb.Max.y - it_anim->second.closing_anim ), ImVec2( bb.Max.x, bb.Max.y ), inside_hover_col, 4 );

		PushStyleColor( ImGuiCol_Text, ColorConvertFloat4ToU32( ImColor( 180, 180, 180, 255 - ( int ) it_anim->second.label_alpha ) ) );
		RenderTextClipped( bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, ImVec2(0.5f, 0.5f), &bb );
		PopStyleColor( );

		PushStyleColor( ImGuiCol_Text, ColorConvertFloat4ToU32( ImColor( 255, 255, 255, ( int ) it_anim->second.label_alpha ) ) );
		RenderTextClipped( bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, ImVec2(0.5f, 0.5f), &bb );
		PopStyleColor( );

		IMGUI_TEST_ENGINE_ITEM_INFO( id, label, g.LastItemData.StatusFlags );

		bool completed = it_anim->second.closing_anim >= ( size.y - 1.f );
		if ( completed && !it_anim->second.animation_complete ) {
			it_anim->second.animation_complete = true;
			return true;
		}

		if ( pressed ) {
			it_anim->second.animation_complete = false;
		}

		return false;
	}

	inline bool WeaponButtonHeld( ImTextureID Icon, const char * label, ImGuiButtonFlags flags )
	{
		ImGuiWindow * window = GetCurrentWindow( );
		if ( window->SkipItems )
			return false;

		ImGuiContext & g = *GImGui;
		const ImGuiStyle & style = g.Style;
		const ImVec2 LabelSize = ::Utils::CalcTextSize( g_Variables.m_FontSecundary, (int)g_Variables.m_FontSecundary->FontSize, label );
		const ImGuiID id = window->GetID( label );
		ImDrawList * Draw = window->DrawList;

		struct WeaponButtonHeld_t {
			ImVec4 ProgressCol = ImColor( );
			ImVec4 ShadowProgressCol = ImColor( );
			ImVec4 SlideCol = ImColor( );
			float Alpha = 0.f;
			float SlideX = 0.f;
			float SlideXShadow = 0.f;
			float IconSize = 0.f;
			bool Completed = false;
		};

		static std::map<ImGuiID, WeaponButtonHeld_t> anim;
		if (anim.size() > 500) anim.clear();
		auto WeaponButtonAnim = anim.find( id );
		if ( WeaponButtonAnim == anim.end( ) )
		{
			anim.insert( { id, WeaponButtonHeld_t( ) } );
			WeaponButtonAnim = anim.find( id );
		}

		const float Width = 100;
		const float Height = Width;
		ImVec2 Pos = window->DC.CursorPos;
		const ImRect Rect( Pos, Pos + ImVec2( Width, Height ) );
		ItemSize( ImVec2( Width, Height ), style.FramePadding.y );
		if ( !ItemAdd( Rect, id ) )
			return false;

		if ( g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat )
			flags |= ImGuiButtonFlags_Repeat;

		bool Hovered, Held;
		bool Pressed = ButtonBehavior( Rect, id, &Hovered, &Held, flags );

		bool Condition = WeaponButtonAnim->second.Completed ? false : Held;

		WeaponButtonAnim->second.Alpha = ImLerp( WeaponButtonAnim->second.Alpha, Condition ? 0.8f : Hovered ? 1.f : 0.6f, g.IO.DeltaTime * 8.f );
		WeaponButtonAnim->second.IconSize = ImLerp( WeaponButtonAnim->second.IconSize, Condition ? 4.f : 0.f, g.IO.DeltaTime * 8.f );
		WeaponButtonAnim->second.SlideX = ImLerp( WeaponButtonAnim->second.SlideX, Condition ? Width : 0.f, g.IO.DeltaTime * 2.2f );
		WeaponButtonAnim->second.SlideXShadow = ImLerp( WeaponButtonAnim->second.SlideXShadow, WeaponButtonAnim->second.SlideX >= 1.f ? WeaponButtonAnim->second.SlideX + 1.f : WeaponButtonAnim->second.SlideX, g.IO.DeltaTime * 3.f );
		WeaponButtonAnim->second.ProgressCol = ImLerp( WeaponButtonAnim->second.ProgressCol, WeaponButtonAnim->second.SlideX >= 0.6f ? ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 255.f / 255.f ) : ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 0.f ), g.IO.DeltaTime * 18.f );
		WeaponButtonAnim->second.ShadowProgressCol = ImLerp( WeaponButtonAnim->second.ShadowProgressCol, WeaponButtonAnim->second.SlideXShadow >= 0.6f ? ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 0.4f ) : ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 0.f ), g.IO.DeltaTime * 18.f );

		float Size = ( 10 + WeaponButtonAnim->second.IconSize );
		ImGui::PushStyleVar( ImGuiStyleVar_Alpha, g.Style.Alpha * WeaponButtonAnim->second.Alpha );
		{
			Draw->AddRectFilled( Rect.Min, Rect.Max, GetColorU32( ImVec4( ImColor( 20, 20, 22 ) ) ), 8 );
			//Draw->AddRectFilledMultiColor( Rect.Min, Rect.Max, GetColorU32( ImVec4( ImColor( g_Col.Base ) ), WeaponButtonAnim->second.Alpha ), GetColorU32( ImVec4( ImColor( g_Col.Base ) ), WeaponButtonAnim->second.Alpha ), GetColorU32( ImVec4( ImColor( 20, 20, 22, 0 ) ) ), GetColorU32( ImVec4( ImColor( 20, 20, 22, 0 ) ) ), 8 );
			Draw->AddRectFilled( Pos + ImVec2( 0, Height - 4 ), Pos + ImVec2( WeaponButtonAnim->second.SlideXShadow, Height ), GetColorU32( WeaponButtonAnim->second.ShadowProgressCol ), 8 );
			Draw->AddRectFilled( Pos + ImVec2( 0, Height - 4 ), Pos + ImVec2( WeaponButtonAnim->second.SlideX, Height ), GetColorU32( WeaponButtonAnim->second.ProgressCol ), 8 );
			Draw->AddImage( Icon, ImVec2( Rect.Min.x + Size, Rect.Min.y + Size ), ImVec2( Rect.Max.x - Size, Rect.Max.y - Size ), { 0,0 }, { 1,1 }, GetColorU32( ImVec4( ImColor( 255, 255, 255 ) ) ) );
		}
		ImGui::PopStyleVar( );

		Draw->AddRect( Rect.Min - ImVec2( 4, 4 ), Rect.Max + ImVec2( 4, 4 ), GetColorU32( g_Col.BackgroundCol ), 8, 0, 8.f );

		IMGUI_TEST_ENGINE_ITEM_INFO( id, label, g.LastItemData.StatusFlags );

		bool Completed = WeaponButtonAnim->second.SlideX >= ( Width - 1.f );

		if ( WeaponButtonAnim->second.Completed && Held ) {
			return false;
		}


		if ( Completed ) {
			WeaponButtonAnim->second.Completed = true;
			return true;
		}

		if ( !Held ) {
			WeaponButtonAnim->second.Completed = false;
		}

		return false;
	}

	inline bool ResourceListButton( const char * Label, uint32_t ResourceState, ImVec2 SizeArg, ImGuiButtonFlags flags ) {


		ImGuiWindow * Window = ImGui::GetCurrentWindow( );
		if ( Window->SkipItems )
			return false;

		ImGuiContext & g = *GImGui;
		const ImGuiStyle & style = g.Style;
		const ImGuiID id = Window->GetID( Label );
		const ImVec2 LabelSize = g_Variables.m_FontNormal->CalcTextSizeA( g_Variables.m_FontNormal->FontSize, FLT_MAX, 0, Label );
		const ImVec2 TwoTextSize = g_Variables.m_FontSecundary->CalcTextSizeA( g_Variables.m_FontSecundary->FontSize, FLT_MAX, 0, xorstr( "Stop" ) );
		const ImVec2 IconTextSize = g_Variables.FontAwesomeSolid->CalcTextSizeA( g_Variables.FontAwesomeSolid->FontSize, FLT_MAX, 0, ICON_FA_CIRCLE_STOP );
		const ImVec2 pos = Window->DC.CursorPos;


		float Width = ImGui::GetWindowContentRegionMax( ).x - ImGui::GetWindowContentRegionMin( ).x - ( Window->ScrollbarY ? 12.f : 0.f );
		SizeArg.x = Width;
		ImVec2 size = ImGui::CalcItemSize( SizeArg, LabelSize.x + IconTextSize.x + style.FramePadding.x * 3.0f, LabelSize.y + style.FramePadding.y * 2.0f );

		const ImRect Rect( pos, ImVec2( pos.x + size.x, pos.y + size.y ) );
		ImGui::ItemSize( size, 0.f );

		if ( !ImGui::ItemAdd( Rect, id ) )
			return false;

		bool Hovered, Held, Pressed = ImGui::ButtonBehavior( Rect, id, &Hovered, &Held, flags );

		struct ResourceBtn_t {
			float Alpha = 0.f;
			float SlideHeld = 0.f;
			float Size = 0.f;
			bool Completed = false;
		};

		static std::map<ImGuiID, ResourceBtn_t> anim;
		if (anim.size() > 500) anim.clear();
		auto ResourceBtnAnim = anim.find( id );

		if ( ResourceBtnAnim == anim.end( ) ) {
			anim.insert( { id, ResourceBtn_t( ) } );
			ResourceBtnAnim = anim.find( id );
		}

		auto TextPos = ImVec2( Rect.Min.x + 8, pos.y + ( size.y / 2 - LabelSize.y / 2 ) );

		ResourceBtnAnim->second.Alpha = ImLerp( ResourceBtnAnim->second.Alpha, ResourceState == 3 ? 1.f : 0.4f, g.IO.DeltaTime * 8 );
		ResourceBtnAnim->second.SlideHeld = ImLerp( ResourceBtnAnim->second.SlideHeld, Held && ResourceState == 3 ? Rect.Max.x - pos.x : TextPos.x - pos.x + LabelSize.x + 8, g.IO.DeltaTime * 4 );
		ResourceBtnAnim->second.Size = ImLerp( ResourceBtnAnim->second.Size, ResourceState == 3 && Held ? 4.f : 3.f, g.IO.DeltaTime * 4 );

		ImGui::PushStyleVar( ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * ResourceBtnAnim->second.Alpha );

		Window->DrawList->AddRectFilled( Rect.Min, Rect.Max, GetColorU32( ( ImVec4 ) ImColor( 16, 16, 18 ) ), 6 );
		Window->DrawList->AddRectFilled( Rect.Min, ImVec2( pos.x + ResourceBtnAnim->second.SlideHeld, Rect.Max.y ), GetColorU32( ( ImVec4 ) ImColor( 24, 24, 26 ) ), 6 );
		Window->DrawList->AddText( g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, TextPos, GetColorU32( ImVec4( ImColor( g_Col.FeaturesText ) ) ), Label );

		ImVec2 CirclePos( Rect.Max.x - 16, pos.y + ( size.y ) / 2 );
		
		if ( ResourceState == 3 ) {
			Window->DrawList->AddCircleFilled( CirclePos, ResourceBtnAnim->second.Size, GetColorU32( ImVec4( ImColor( 55, 237, 125, 180 ) ) ), 99 );
		}
		else {
			Window->DrawList->AddCircleFilled( CirclePos, ResourceBtnAnim->second.Size, GetColorU32( ImVec4( ImColor( 237, 55, 55, 180 ) ) ), 99 );
		}

		ImGui::PopStyleVar( );

		if ( ResourceState == 3 ) {
			if( Held && ResourceBtnAnim->second.SlideHeld >= (Rect.Max.x - pos.x) - 1.f )
			{
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	inline bool SliderInt( const char * label, int * v, int v_min, int v_max, const char * format = "%d", ImGuiSliderFlags flags = 0 ) {
		ImGuiWindow * window = GetCurrentWindow( );
		if ( window->SkipItems )
			return false;

		ImGuiContext & g = *GImGui;
		const ImGuiStyle & style = g.Style;
		const ImGuiID id = window->GetID( label );
		const float w = ImGui::GetWindowContentRegionMax( ).x - ImGui::GetWindowContentRegionMin( ).x - ( window->ScrollbarY ? 5.f : 0.f ); // removed -40.f to align with checkboxes

		const ImVec2 label_size = CalcTextSize( label, NULL, true );
		
		char value_buf[64];
		DataTypeFormatString( value_buf, IM_ARRAYSIZE( value_buf ), ImGuiDataType_S32, v, format );
		const ImVec2 value_size = CalcTextSize( value_buf, NULL, true );

		const ImRect frame_bb( window->DC.CursorPos, window->DC.CursorPos + ImVec2( w, label_size.y + 12.0f ) );
		const ImRect total_bb( frame_bb.Min, frame_bb.Max );

		ItemSize( total_bb, style.FramePadding.y );
		if ( !ItemAdd( total_bb, id, &frame_bb ) )
			return false;

		if ( format == NULL )
			format = "%d";

		bool hovered, held;
		bool pressed = ButtonBehavior( frame_bb, id, &hovered, &held );

		const float slider_height = 10.0f;
		const float slider_pos_y = frame_bb.Min.y + label_size.y + 6.0f;

		ImRect slider_bb( ImVec2( frame_bb.Min.x, slider_pos_y ), ImVec2( frame_bb.Max.x, slider_pos_y + slider_height ) );
		ImRect grab_bb;

		bool value_changed = SliderBehavior( frame_bb, id, ImGuiDataType_S32, v, &v_min, &v_max, format, flags, &grab_bb );
		if ( value_changed )
			MarkItemEdited( id );

		// Render track
		window->DrawList->AddRectFilled( slider_bb.Min, slider_bb.Max, GetColorU32( ImVec4( ImColor( 25, 25, 27 ) ) ), slider_height / 2.0f );

		// Render fill
		float fraction = ImSaturate( ( float ) ( *v - v_min ) / ( float ) ( v_max - v_min ) );
		ImVec2 fill_max = ImVec2( slider_bb.Min.x + ( slider_bb.GetWidth( ) * fraction ), slider_bb.Max.y );
		if ( fraction > 0.0f ) {
			window->DrawList->AddRectFilledMultiColor( slider_bb.Min, fill_max, GetColorU32( g_Col.Base ), GetColorU32( g_Col.BaseEnd ), GetColorU32( g_Col.BaseEnd ), GetColorU32( g_Col.Base ), slider_height / 2.0f );
		}

		// Render label (left)
		window->DrawList->AddText( frame_bb.Min, GetColorU32( g_Col.FeaturesText ), label );

		// Render value (right)
		window->DrawList->AddText( ImVec2( frame_bb.Max.x - value_size.x, frame_bb.Min.y ), GetColorU32( g_Col.FeaturesText ), value_buf );

		return value_changed;
	}

	inline bool SliderFloat( const char * label, float * v, float v_min, float v_max, const char * format = "%.3f", ImGuiSliderFlags flags = 0 ) {
		ImGuiWindow * window = GetCurrentWindow( );
		if ( window->SkipItems )
			return false;

		ImGuiContext & g = *GImGui;
		const ImGuiStyle & style = g.Style;
		const ImGuiID id = window->GetID( label );
		const float w = ImGui::GetWindowContentRegionMax( ).x - ImGui::GetWindowContentRegionMin( ).x - ( window->ScrollbarY ? 5.f : 0.f ); // removed -40.f to align with checkboxes

		const ImVec2 label_size = CalcTextSize( label, NULL, true );

		char value_buf[64];
		DataTypeFormatString( value_buf, IM_ARRAYSIZE( value_buf ), ImGuiDataType_Float, v, format );
		const ImVec2 value_size = CalcTextSize( value_buf, NULL, true );

		const ImRect frame_bb( window->DC.CursorPos, window->DC.CursorPos + ImVec2( w, label_size.y + 12.0f ) );
		const ImRect total_bb( frame_bb.Min, frame_bb.Max );

		ItemSize( total_bb, style.FramePadding.y );
		if ( !ItemAdd( total_bb, id, &frame_bb ) )
			return false;

		if ( format == NULL )
			format = "%.3f";

		bool hovered, held;
		bool pressed = ButtonBehavior( frame_bb, id, &hovered, &held );

		const float slider_height = 10.0f;
		const float slider_pos_y = frame_bb.Min.y + label_size.y + 6.0f;

		ImRect slider_bb( ImVec2( frame_bb.Min.x, slider_pos_y ), ImVec2( frame_bb.Max.x, slider_pos_y + slider_height ) );
		ImRect grab_bb;

		bool value_changed = SliderBehavior( frame_bb, id, ImGuiDataType_Float, v, &v_min, &v_max, format, flags, &grab_bb );
		if ( value_changed )
			MarkItemEdited( id );

		// Render track
		window->DrawList->AddRectFilled( slider_bb.Min, slider_bb.Max, GetColorU32( ImVec4( ImColor( 25, 25, 27 ) ) ), slider_height / 2.0f );

		// Render fill
		float fraction = ImSaturate( ( *v - v_min ) / ( v_max - v_min ) );
		ImVec2 fill_max = ImVec2( slider_bb.Min.x + ( slider_bb.GetWidth( ) * fraction ), slider_bb.Max.y );
		if ( fraction > 0.0f ) {
			window->DrawList->AddRectFilledMultiColor( slider_bb.Min, fill_max, GetColorU32( g_Col.Base ), GetColorU32( g_Col.BaseEnd ), GetColorU32( g_Col.BaseEnd ), GetColorU32( g_Col.Base ), slider_height / 2.0f );
		}

		// Render label (left)
		window->DrawList->AddText( frame_bb.Min, GetColorU32( g_Col.FeaturesText ), label );

		// Render value (right)
		window->DrawList->AddText( ImVec2( frame_bb.Max.x - value_size.x, frame_bb.Min.y ), GetColorU32( g_Col.FeaturesText ), value_buf );

		return value_changed;
	}

	inline bool ListSelectableCustom( const char * Label, bool * Selected, int Type )
	{
		if ( Type == 0 ) //Players
		{
			//if ( SelectableCustomResources( Label, *Selected, 3 ) ) {
				//*Selected = !*Selected;
				//return true;
			//}
		} 
		else if ( Type == 1 ) //Vehicles
		{
			//if ( SelectableCustomResources( Label, *Selected, 3 ) ) {
				//*Selected = !*Selected;
				//return true;
			//}
		}

		return false;
	}

}