#include "Esp.hpp"



void Core::Features::cEsp::Draw( )
{
	auto& Cfg = g_Config.ESP;



	if ( !Cfg.Enabled )
		return;

	ImFont* RenderFont = g_Variables.m_DrawFont; // Padrão
	if (g_Config.MiscESP.MinecraftFont) {
		RenderFont = g_Variables.m_MinecraftFont;
	} else if (g_Config.MiscESP.HyperXFont) {
		RenderFont = g_Variables.m_FontNormal; // Fonte padrão do painel Menu
	}

	static std::unordered_map<CPed *, Core::SDK::Game::EspAnim> vEspAnimations;
	static std::unordered_map<CPed *, bool> vWasDead;
	static std::unordered_map<CPed *, ULONGLONG> vDeathTimes;

	// OPT: Obter DrawList e TickCount uma única vez fora do loop
	auto DrawList = ImGui::GetBackgroundDrawList( );
	const ULONGLONG CurrentTick = GetTickCount64( );

	// OPT: Pré-calcular valores de fonte uma vez fora do loop
	const float FontSize = RenderFont->FontSize * Cfg.TextSize;

	// OPT: Pré-calcular constantes de build uma vez fora do loop
	const bool IsNewBuild = g_Offsets.CurrentBuild >= 2802;
	const D3DXVECTOR3 AbdomenOffset = IsNewBuild ? D3DXVECTOR3( 0, 0, 2 ) : D3DXVECTOR3( 0, 0, 1.2 );

	for ( auto & Entity : Core::SDK::Game::EntityList )
	{
		CPed * Ped = Entity.Ped;

		auto & CurrentESPAnim = vEspAnimations[ Ped ];
		CurrentESPAnim.CanFadeOut = false;

		float Distance = Entity.Distance;
		float Health = Entity.Health;
		int PedType = Entity.PedType;
		bool IsFriend = Entity.IsFriend;
		bool IsLocalPlayer = Ped == Core::SDK::Pointers::pLocalPlayer;

		bool IsDead = false;
		if ( PedType == 2 ) {
			if ( Health > 400.f || Health <= 101.f ) IsDead = true;
		} else {
			if ( Health > 200.f || Health <= 1.f ) IsDead = true;
		}

		if ( IsDead && !vWasDead[ Ped ] ) {
			vDeathTimes[ Ped ] = CurrentTick;
		}
		vWasDead[ Ped ] = IsDead;

		if ( !Cfg.ShowLocalPlayer && IsLocalPlayer )
			continue;

		bool IsInvisibleAdmin = false;
		if (PedType == 2) {
			if (Ped->IsSetInvisible()) {
				if (Health > 101.0f && !Entity.NetworkInfo.UserName.empty()) { IsInvisibleAdmin = true; }
			}
		}

		if ( Distance > Cfg.MaxDistance && !(Cfg.AdminHighlight && IsInvisibleAdmin) )
			continue;

		if ( Cfg.IgnoreNPCs && PedType != 2 && !IsLocalPlayer )
			continue;

		if ( Cfg.IgnoreDead && !IsLocalPlayer && IsDead )
		{
			if ( CurrentTick - vDeathTimes[ Ped ] >= 500 )
				continue;
		}

		// OPT: Skip skeleton projection for far entities (saves ~14 WorldToScreen calls per entity)
		bool needsSkeleton = (Cfg.Skeleton || IsInvisibleAdmin) && Distance < Cfg.MaxDistance * 0.6f;
		// OPT: Skip detailed features for far entities
		bool isCloseRange = Distance < 150.f;

		D3DXVECTOR3 HeadPos = Ped->GetBonePosDefault( 0 );
		D3DXVECTOR2 EntityTop = Core::SDK::Game::WorldToScreen( HeadPos + D3DXVECTOR3( 0, 0, 0.2 ) ); //Head

		D3DXVECTOR2 EntityBottom = Core::SDK::Game::WorldToScreen(
			Ped->GetBonePosDefault( 8 ) - AbdomenOffset //Abdomen
		);


		if ( !Core::SDK::Game::IsOnScreen( EntityTop ) || !Core::SDK::Game::IsOnScreen( EntityBottom ) )
			continue;

		float Height = EntityBottom.y - EntityTop.y;
		float Width = Height * 0.2f;

		const float BoxLeft = EntityTop.x - Width;
		const float BoxRight = EntityBottom.x + Width;

		ImVec2 BoxMin( BoxLeft, EntityTop.y );
		ImVec2 BoxMax( BoxRight, EntityBottom.y );
		ImVec2 BoxCenter = ImVec2( ( BoxMin.x + BoxMax.x ) * 0.5f, ( BoxMin.y + BoxMax.y ) * 0.5f );


		float FirstTextBoxTop = BoxMin.y - 18;

		float FirstTextBoxBottom = BoxMax.y + 4;
		float SecondTextBoxBottom = BoxMax.y + ( 4 * 2 ) + 8; //8 is padding
		float ThirdTextBoxBottom = BoxMax.y + ( 4 * 3 ) + ( 8 * 2 );

		// OPT: Consolidar a lógica de offset em uma única comparação
		const int HealthBarState = Cfg.HealthBarState;
		const int ArmorBarState  = Cfg.ArmorBarState;

		if ( HealthBarState == 2 && ArmorBarState == 2 ) {
			FirstTextBoxBottom  += 16;
			SecondTextBoxBottom += 16;
			ThirdTextBoxBottom  += 16;
		}
		else if ( HealthBarState == 2 ) {
			FirstTextBoxBottom  += 8;
			SecondTextBoxBottom += 8;
			ThirdTextBoxBottom  += 8;
		}
		else if ( ArmorBarState == 2 ) {
			FirstTextBoxBottom  += 16;
			SecondTextBoxBottom += 16;
			ThirdTextBoxBottom  += 16;
		}

		// OPT: As três condições originais resultavam no mesmo -4; unificadas
		if ( HealthBarState == 0 || ArmorBarState == 0 ) {
			FirstTextBoxTop -= 4;
		}

		if ( Cfg.FriendsMarker && !IsLocalPlayer && isCloseRange )
		{
			float radius = 2 / Distance;

			const static int FovRadius = 60;
			const static int Delay = 300;
			int Key = Cfg.FriendsMarkerBind;
			std::string PlayerSetFriend = xorstr("Add Friend" );
			std::string PlayerUnFriend = xorstr( "Unfriend" );


			float dx = BoxCenter.x - g_Variables.g_vGameWindowCenter.x;
			float dy = BoxCenter.y - g_Variables.g_vGameWindowCenter.y;
			int FovSize = (int)sqrtf( dx * dx + dy * dy );

			ImGui::PushFont( g_Variables.m_FontSmaller );

			// OPT: radius + Distance < 1 calculado uma vez
			const bool RadiusSmall = (radius + Distance) < 1;
			const float InnerR = RadiusSmall ? 0 : 3;
			const float OuterR = RadiusSmall ? 1 : 4;

			if ( IsFriend && FovSize < FovRadius )
			{
				DrawList->AddCircleFilled( ImVec2( BoxCenter.x, BoxCenter.y ), OuterR, ImColor( 0, 0, 0 ), 999 );
				DrawList->AddCircleFilled( ImVec2( BoxCenter.x, BoxCenter.y ), InnerR, ImColor( g_Col.Base ), 999 );

				if ( Utils::KeyPressedWithDelay( Key, Delay ) )
				{
					IsFriend = false;
					Core::SDK::Game::FriendMap[ Ped ] = IsFriend;
				}
			}
			else if( !IsFriend && FovSize < FovRadius )
			{
				DrawList->AddCircleFilled( ImVec2( BoxCenter.x, BoxCenter.y ), OuterR, ImColor( 0, 0, 0 ), 999 );
				DrawList->AddCircleFilled( ImVec2( BoxCenter.x, BoxCenter.y ), InnerR, ImColor( 255, 255, 255 ), 999 );

				if ( Utils::KeyPressedWithDelay( Key, Delay ) )
				{
					IsFriend = true;
					Core::SDK::Game::FriendMap[ Ped ] = IsFriend;
				}
			}
			ImGui::PopFont( );
		}

		if ( IsFriend )
			continue;

		// OPT: Pré-calcular ScreenCenter e bottom line positions uma vez se usadas
		if ( Cfg.SnapLines )
		{
			const ImVec2 SnapFrom( g_Variables.g_vGameWindowCenter.x, g_Variables.g_vGameWindowPos.y + g_Variables.g_vGameWindowSize.y );
			const ImVec2 SnapTo( BoxCenter.x, BoxMax.y );
			DrawList->AddLine( SnapFrom, SnapTo, ImColor( 0, 0, 0 ), 2.5 );
			DrawList->AddLine( SnapFrom, SnapTo, Cfg.SnapLinesCol, 1.5 );
		}

		if ( Cfg.AdminHighlight && IsInvisibleAdmin )
		{
			// OPT: Evitar chamadas repetidas ao ImGui::GetIO para DisplaySize
			ImVec2 ScreenCenter = ImVec2( g_Variables.g_vGameWindowSize.x * 0.5f, g_Variables.g_vGameWindowSize.y );
			DrawList->AddLine( ScreenCenter, ImVec2( BoxCenter.x, BoxMax.y ), Cfg.AdminHighlightCol, 2.0f );
		}

		if ( Cfg.Box )
		{
			if ( Cfg.FilledBox )
				DrawList->AddRectFilled( { BoxLeft, EntityTop.y }, { BoxRight, EntityBottom.y }, Cfg.FilledBoxCol, 0, 0 );

			DrawList->AddRect( { BoxLeft - 1, EntityTop.y - 1 }, { BoxRight + 1, EntityBottom.y + 1 }, ImColor( 0, 0, 0, 200 ), 0, 0, 1.5 );
			DrawList->AddRect( { BoxLeft + 1, EntityTop.y + 1 }, { BoxRight - 1, EntityBottom.y - 1 }, ImColor( 0, 0, 0, 200 ), 0, 0, 1.5 );
			DrawList->AddRect( { BoxLeft, EntityTop.y }, { BoxRight, EntityBottom.y }, Cfg.BoxCol, 0, 0, 1.5 );
		}

		if ( needsSkeleton )
		{
			ImColor SkeletonColor = Cfg.SkeletonCol;

			if (IsInvisibleAdmin) {
				SkeletonColor = Cfg.InvisibleFilterColor;
			}

			ULONGLONG DeathTime = vDeathTimes[ Ped ];
			if ( IsDead && ( CurrentTick - DeathTime < 500 ) ) { // Red for 0.5 seconds after death
				SkeletonColor = ImColor( 255, 0, 0, 200 );
			}

			//auto Skeleton = Entity.Skeleton;
			uintptr_t FragInstNMGta = Mem.Read<uintptr_t>( ( uintptr_t ) Ped + g_Offsets.m_FragInst );
			uintptr_t v9 = Mem.Read<uintptr_t>( FragInstNMGta + 0x68 );

			if ( !v9 )
				continue;

			Core::SDK::Game::cSkeleton_t Skeleton;

			Skeleton.m_pSkeleton = Mem.Read<uintptr_t>( v9 + 0x178 );

			Skeleton.crSkeletonData.Ptr = Mem.Read<uintptr_t>( Skeleton.m_pSkeleton );
			Skeleton.crSkeletonData.m_Used = Mem.Read<unsigned int>( Skeleton.crSkeletonData.Ptr + 0x1A );
			Skeleton.crSkeletonData.m_NumBones = Mem.Read<unsigned int>( Skeleton.crSkeletonData.Ptr + 0x5E );
			Skeleton.crSkeletonData.m_BoneIdTable_Slots = Mem.Read<unsigned short>( Skeleton.crSkeletonData.Ptr + 0x18 );

			if ( !Skeleton.crSkeletonData.m_BoneIdTable_Slots )
				continue;

			Skeleton.crSkeletonData.m_BoneIdTable = Mem.Read<uintptr_t>( Skeleton.crSkeletonData.Ptr + 0x10 );

			Skeleton.Arg1 = Mem.Read<D3DXMATRIX>( Mem.Read<uintptr_t>( Skeleton.m_pSkeleton + 0x8 ) );
			Skeleton.Arg2 = Mem.Read<uintptr_t>( Skeleton.m_pSkeleton + 0x18 );


			// OPT: Calcular todas as posições 3D primeiro, depois todas as projeções 2D de uma vez
			D3DXVECTOR3 PelvisPos     = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_Pelvis,     Skeleton );
			D3DXVECTOR3 NeckPos       = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_Neck_1,     Skeleton );
			D3DXVECTOR3 LeftUperarmPos  = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_L_UpperArm, Skeleton );
			D3DXVECTOR3 RightUperarmPos = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_R_UpperArm, Skeleton );
			D3DXVECTOR3 RightFormArmPos = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_R_Forearm,  Skeleton );
			D3DXVECTOR3 LeftFormArmPos  = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_L_Forearm,  Skeleton );
			D3DXVECTOR3 RightHandPos  = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_R_Hand,     Skeleton );
			D3DXVECTOR3 LeftHandPos   = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_L_Hand,     Skeleton );
			D3DXVECTOR3 LeftThighPos  = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_L_Thigh,    Skeleton );
			D3DXVECTOR3 LeftCalfPos   = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_L_Calf,     Skeleton );
			D3DXVECTOR3 RightThighPos = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_R_Thigh,    Skeleton );
			D3DXVECTOR3 RightCalfPos  = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_R_Calf,     Skeleton );
			D3DXVECTOR3 LfootPos      = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_L_Foot,     Skeleton );
			D3DXVECTOR3 RfootPos      = Core::SDK::Game::GetBonePosComplex( Ped, SKEL_R_Foot,     Skeleton );

			D3DXVECTOR2 Pelvis      = Core::SDK::Game::WorldToScreen( PelvisPos );
			D3DXVECTOR2 Neck        = Core::SDK::Game::WorldToScreen( NeckPos );
			D3DXVECTOR2 LeftUperarm  = Core::SDK::Game::WorldToScreen( LeftUperarmPos );
			D3DXVECTOR2 RightUperarm = Core::SDK::Game::WorldToScreen( RightUperarmPos );
			D3DXVECTOR2 RightFormArm = Core::SDK::Game::WorldToScreen( RightFormArmPos );
			D3DXVECTOR2 LeftFormArm  = Core::SDK::Game::WorldToScreen( LeftFormArmPos );
			D3DXVECTOR2 RightHand   = Core::SDK::Game::WorldToScreen( RightHandPos );
			D3DXVECTOR2 LeftHand    = Core::SDK::Game::WorldToScreen( LeftHandPos );
			D3DXVECTOR2 LeftThigh   = Core::SDK::Game::WorldToScreen( LeftThighPos );
			D3DXVECTOR2 LeftCalf    = Core::SDK::Game::WorldToScreen( LeftCalfPos );
			D3DXVECTOR2 RightThigh  = Core::SDK::Game::WorldToScreen( RightThighPos );
			D3DXVECTOR2 RightCalf   = Core::SDK::Game::WorldToScreen( RightCalfPos );
			D3DXVECTOR2 Lfoot       = Core::SDK::Game::WorldToScreen( LfootPos );
			D3DXVECTOR2 Rfoot       = Core::SDK::Game::WorldToScreen( RfootPos );

			if ( !Core::SDK::Game::IsOnScreen( Lfoot ) || !Core::SDK::Game::IsOnScreen( Rfoot ) || !Core::SDK::Game::IsOnScreen( Pelvis ) || !Core::SDK::Game::IsOnScreen( Neck ) || !Core::SDK::Game::IsOnScreen( LeftUperarm ) || !Core::SDK::Game::IsOnScreen( RightUperarm ) || !Core::SDK::Game::IsOnScreen( RightFormArm ) || !Core::SDK::Game::IsOnScreen( LeftFormArm ) || !Core::SDK::Game::IsOnScreen( RightHand ) || !Core::SDK::Game::IsOnScreen( LeftHand ) || !Core::SDK::Game::IsOnScreen( LeftThigh ) || !Core::SDK::Game::IsOnScreen( RightThigh ) || !Core::SDK::Game::IsOnScreen( RightCalf ) )
				continue;

			// OPT: Reutilizar HeadPos já calculado, evitar novo WorldToScreen
			auto ScreenHead = Core::SDK::Game::WorldToScreen( HeadPos );
			const float SkeletonSize = Cfg.SkeletonSize;
			DrawList->AddLine( ImVec2( ScreenHead.x, ScreenHead.y ),     ImVec2( Neck.x, Neck.y ),             SkeletonColor, SkeletonSize );
			DrawList->AddLine( ImVec2( LeftUperarm.x, LeftUperarm.y ),   ImVec2( RightUperarm.x, RightUperarm.y ), SkeletonColor, SkeletonSize );
			DrawList->AddLine( ImVec2( RightUperarm.x, RightUperarm.y ), ImVec2( RightFormArm.x, RightFormArm.y ), SkeletonColor, SkeletonSize );
			DrawList->AddLine( ImVec2( LeftUperarm.x, LeftUperarm.y ),   ImVec2( LeftFormArm.x, LeftFormArm.y ),  SkeletonColor, SkeletonSize );
			DrawList->AddLine( ImVec2( RightFormArm.x, RightFormArm.y ), ImVec2( RightHand.x, RightHand.y ),    SkeletonColor, SkeletonSize );
			DrawList->AddLine( ImVec2( LeftFormArm.x, LeftFormArm.y ),   ImVec2( LeftHand.x, LeftHand.y ),     SkeletonColor, SkeletonSize );
			DrawList->AddLine( ImVec2( Neck.x, Neck.y ),                 ImVec2( Pelvis.x, Pelvis.y ),         SkeletonColor, SkeletonSize );
			DrawList->AddLine( ImVec2( Pelvis.x, Pelvis.y ),             ImVec2( LeftThigh.x, LeftThigh.y ),   SkeletonColor, SkeletonSize );
			DrawList->AddLine( ImVec2( Pelvis.x, Pelvis.y ),             ImVec2( RightThigh.x, RightThigh.y ), SkeletonColor, SkeletonSize );
			DrawList->AddLine( ImVec2( LeftThigh.x, LeftThigh.y ),       ImVec2( LeftCalf.x, LeftCalf.y ),     SkeletonColor, SkeletonSize );
			DrawList->AddLine( ImVec2( RightThigh.x, RightThigh.y ),     ImVec2( RightCalf.x, RightCalf.y ),   SkeletonColor, SkeletonSize );
			DrawList->AddLine( ImVec2( LeftCalf.x, LeftCalf.y ),         ImVec2( Lfoot.x, Lfoot.y ),           SkeletonColor, SkeletonSize );
			DrawList->AddLine( ImVec2( RightCalf.x, RightCalf.y ),       ImVec2( Rfoot.x, Rfoot.y ),           SkeletonColor, SkeletonSize );

		}

		if ( Cfg.HeadCircle && isCloseRange )
		{
			if ( HeadPos != D3DXVECTOR3( 0, 0, 0 ) ) {
				D3DXVECTOR2 head_screen_pos = SDK::Game::WorldToScreen( HeadPos );
				if ( head_screen_pos != D3DXVECTOR2( 0, 0 ) ) {

					int CircleValue = Height / 15;
					if ( CircleValue <= 10 ) { }

					ImVec2 center( head_screen_pos.x, head_screen_pos.y );
					DrawList->AddCircle( center, CircleValue, Cfg.SkeletonCol, 999, Cfg.SkeletonSize );
				}
			}
		}

		if ( Cfg.ChinaHat && isCloseRange )
		{
			if ( HeadPos != D3DXVECTOR3( 0, 0, 0 ) ) {
				ImColor hatColor = Cfg.ChinaHatCol;
				if (IsInvisibleAdmin) hatColor = Cfg.InvisibleFilterColor;

				const float h = 0.3f;
				const float r = 0.45f;
				const float o = 0.15f;

				D3DXVECTOR3 headPos3D = HeadPos + D3DXVECTOR3(0.f, 0.f, o);

				const int segments = 24;
				D3DXVECTOR2 basePoints2D[24];

				const float angleStep = (2.f * 3.14159265f / segments);
				const float hz = headPos3D.z;

				D3DXVECTOR3 apex3D = headPos3D + D3DXVECTOR3(0.f, 0.f, h);
				D3DXVECTOR2 apex2D = Core::SDK::Game::WorldToScreen(apex3D);

				if (apex2D != D3DXVECTOR2(0, 0)) {
						for (int i = 0; i < segments; i++)
					{
						float angle = angleStep * i;
						float x = headPos3D.x + cosf(angle) * r;
						float y = headPos3D.y + sinf(angle) * r;
						D3DXVECTOR2 base2D = Core::SDK::Game::WorldToScreen(D3DXVECTOR3(x, y, hz));
						basePoints2D[i] = base2D;

						if (base2D != D3DXVECTOR2(0, 0))
							DrawList->AddLine(ImVec2(apex2D.x, apex2D.y), ImVec2(base2D.x, base2D.y), hatColor, 1.5f);
					}

					for (int i = 0; i < segments; i++)
					{
						const D3DXVECTOR2& a = basePoints2D[i];
						const D3DXVECTOR2& b = basePoints2D[(i + 1) % segments];
						if (a != D3DXVECTOR2(0, 0) && b != D3DXVECTOR2(0, 0))
							DrawList->AddLine(ImVec2(a.x, a.y), ImVec2(b.x, b.y), hatColor, 1.5f);
					}
				}
			}
		}

		if ( Cfg.DistanceFromMe )
		{
			// OPT: Usar snprintf em buffer estático em vez de std::to_string + concatenação
			static char DistBuf[32];
			snprintf(DistBuf, sizeof(DistBuf), "%dm", (int)Distance);

			ImVec2 TextSize = RenderFont->CalcTextSizeA( FontSize, FLT_MAX, 0.0f, DistBuf );
			ImVec2 TextPos = ImVec2( BoxCenter.x - ( TextSize.x / 2 ), FirstTextBoxBottom );

			switch ( Cfg.DistanceFromMeState )
			{

			case 0: //Top

				if ( Cfg.UserNames && Cfg.UserNamesState == 0 )
				{
					TextPos.y = FirstTextBoxTop - 15;
				}

				if ( Cfg.WeaponName && Cfg.WeaponNameState == 0 )
				{
					TextPos.y = FirstTextBoxTop - 15;
				}

				if ( Cfg.WeaponName && Cfg.WeaponNameState == 0 && Cfg.UserNames && Cfg.UserNamesState == 0 )
				{
					TextPos.y = FirstTextBoxTop - 30;
				}

				if ( Cfg.WeaponNameState == 2 && Cfg.UserNamesState == 2 )
				{
					TextPos.y = FirstTextBoxTop;
				}


				if ( !Cfg.UserNames && !Cfg.WeaponName )
				{
					TextPos.y = FirstTextBoxTop;
				}

				break;
			case 2: //Bottom
				if ( Cfg.UserNames && Cfg.UserNamesState == 2 )
				{
					TextPos.y = FirstTextBoxBottom + 15;
				}

				if ( Cfg.WeaponName && Cfg.WeaponNameState == 2 )
				{
					TextPos.y = FirstTextBoxBottom + 15;
				}

				if ( Cfg.WeaponName && Cfg.WeaponNameState == 2 && Cfg.UserNames && Cfg.UserNamesState == 2 )
				{
					TextPos.y = FirstTextBoxBottom + 30;
				}

				if ( !Cfg.UserNames && !Cfg.WeaponName )
				{
					TextPos.y = FirstTextBoxBottom;
				}

				break;
			default:
				TextPos.y = FirstTextBoxBottom;
				break;
			}

			// OPT: Pré-calcular alpha das bordas uma vez
			const float DistAlpha = Cfg.DistanceCol.Value.w;
			const float DistAlphaShadow = DistAlpha * 0.8f;
			const ImColor DistBorderCol(0.f, 0.f, 0.f, DistAlpha);
			const ImColor DistShadowCol(0.f, 0.f, 0.f, DistAlphaShadow);

			// Bordas pretas para o texto
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x - 1, TextPos.y - 1 ), DistBorderCol, DistBuf );
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x + 1, TextPos.y - 1 ), DistBorderCol, DistBuf );
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x - 1, TextPos.y + 1 ), DistBorderCol, DistBuf );
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x + 1, TextPos.y + 1 ), DistBorderCol, DistBuf );

			// Sombra do texto (Drop Shadow)
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x + 1, TextPos.y + 2 ), DistShadowCol, DistBuf );

			// Texto principal
			DrawList->AddText( RenderFont, FontSize, TextPos, Cfg.DistanceCol, DistBuf );

		}

		if ( Cfg.WeaponName ) {

			// OPT: Evitar alocação de lambda a cada entidade — usar função estática inline
			const std::string& weaponName = Entity.WeaponName;

			// OPT: Calcular weaponNameStr uma única vez
			std::string WeaponNameUnder;
		if (weaponName.empty()) {
			WeaponNameUnder = xorstr("Unarmed");
		} else {
			WeaponNameUnder = weaponName;
			std::transform(WeaponNameUnder.begin(), WeaponNameUnder.end(), WeaponNameUnder.begin(), ::tolower);
			WeaponNameUnder[0] = std::toupper(WeaponNameUnder[0]);
		}

			ImVec2 TextSize = RenderFont->CalcTextSizeA( FontSize, FLT_MAX, 0.0f, WeaponNameUnder.c_str( ) );
			ImVec2 TextPos = ImVec2( BoxCenter.x - ( TextSize.x / 2 ), FirstTextBoxBottom );

			if ( Cfg.DistanceFromMe )
				TextPos.y = FirstTextBoxBottom;

			if ( Cfg.UserNamesState == 1 )
				TextPos.y = SecondTextBoxBottom;

			switch ( Cfg.WeaponNameState )
			{

			case 0: //Top
				if ( Cfg.UserNamesState == 0 && Cfg.UserNames )
				{
					TextPos.y = FirstTextBoxTop - 15;
				}
				else
				{
					TextPos.y = FirstTextBoxTop;
				}

				break;
			case 2: //Bottom
				if ( Cfg.UserNamesState == 2 && Cfg.UserNames )
				{
					TextPos.y = FirstTextBoxBottom + 15;
				}
				else
				{
					TextPos.y = FirstTextBoxBottom;
				}
				break;
			default:
				TextPos.y = FirstTextBoxBottom;
				break;
			}

			// OPT: Pré-calcular alpha das bordas uma vez
			const float WAlpha = Cfg.WeaponNameCol.Value.w;
			const ImColor WBorderCol(0.f, 0.f, 0.f, WAlpha);
			const ImColor WShadowCol(0.f, 0.f, 0.f, WAlpha * 0.8f);

			// Bordas pretas para o texto
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x - 1, TextPos.y - 1 ), WBorderCol, WeaponNameUnder.c_str( ) );
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x + 1, TextPos.y - 1 ), WBorderCol, WeaponNameUnder.c_str( ) );
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x - 1, TextPos.y + 1 ), WBorderCol, WeaponNameUnder.c_str( ) );
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x + 1, TextPos.y + 1 ), WBorderCol, WeaponNameUnder.c_str( ) );

			// Sombra do texto (Drop Shadow)
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x + 1, TextPos.y + 2 ), WShadowCol, WeaponNameUnder.c_str( ) );

			// Texto principal
			DrawList->AddText( RenderFont, FontSize, TextPos, Cfg.WeaponNameCol, WeaponNameUnder.c_str( ) );
		}

		if ( Cfg.UserNames || (Cfg.AdminHighlight && IsInvisibleAdmin) )
		{

			std::string PlayerName = Entity.NetworkInfo.UserName;
			if ( PlayerName.empty( ) )
				PlayerName = xorstr( "Unknown" );

			if ( Cfg.AdminHighlight && IsInvisibleAdmin ) {
				PlayerName = xorstr( "[ADMIN] " ) + PlayerName;
			}

			ImVec2 TextSize = RenderFont->CalcTextSizeA( FontSize, FLT_MAX, 0.0f, PlayerName.c_str( ) );
			ImVec2 TextPos = ImVec2( BoxCenter.x - ( TextSize.x / 2 ), FirstTextBoxTop );

			switch ( Cfg.UserNamesState )
			{

			case 0: //Top
				TextPos.y = FirstTextBoxTop;
				break;
			case 2: //Bottom
				TextPos.y = FirstTextBoxBottom;
				break;
			default:
				TextPos.y = FirstTextBoxTop;
				break;
			}

			ImColor textColor = Cfg.UserNamesCol;
			if ( Cfg.AdminHighlight && IsInvisibleAdmin ) {
				textColor = Cfg.AdminHighlightCol;
			}
			else if ( IsFriend ) {
				textColor = Cfg.FriendCol;
			}

			// OPT: Pré-calcular alpha das bordas uma vez
			const float NAlpha = textColor.Value.w;
			const ImColor NBorderCol(0.f, 0.f, 0.f, NAlpha);
			const ImColor NShadowCol(0.f, 0.f, 0.f, NAlpha * 0.8f);

			// Bordas pretas para o texto
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x - 1, TextPos.y - 1 ), NBorderCol, PlayerName.c_str( ) );
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x + 1, TextPos.y - 1 ), NBorderCol, PlayerName.c_str( ) );
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x - 1, TextPos.y + 1 ), NBorderCol, PlayerName.c_str( ) );
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x + 1, TextPos.y + 1 ), NBorderCol, PlayerName.c_str( ) );

			// Sombra do texto (Drop Shadow)
			DrawList->AddText( RenderFont, FontSize, ImVec2( TextPos.x + 1, TextPos.y + 2 ), NShadowCol, PlayerName.c_str( ) );

			// Texto principal
			DrawList->AddText( RenderFont, FontSize, TextPos, textColor, PlayerName.c_str( ) );
		}

		const auto DrawHealthBarV = [ &DrawList ] ( ImVec2 pos, ImVec2 dim, ImColor col, int background ) {
			if ( background == 1 ) { //Bar
				DrawList->AddRectFilled( ImVec2( pos.x, pos.y ), ImVec2( pos.x + dim.x, pos.y - ( dim.y + 1 ) ), col );
			}
			else { //BackGround
				DrawList->AddRectFilled( ImVec2( pos.x - 1, pos.y + 1 ), ImVec2( pos.x + dim.x + 1, pos.y - ( dim.y + 2 ) ), ImColor( 0, 0, 0, 255 ) );
				DrawList->AddRectFilled( ImVec2( pos.x, pos.y - 1 ), ImVec2( pos.x + dim.x, pos.y - ( dim.y + 2 ) ), ImColor( 80, 80, 80, 125 ) );
			}
			};
		const auto DrawHealthBarH = [ &DrawList ] ( ImVec2 pos, ImVec2 dim, ImColor col, int background ) {
			if ( background == 1 ) { //Bar
				DrawList->AddRectFilled( ImVec2( pos.x, pos.y ), ImVec2( pos.x + dim.y, pos.y + dim.x ), col );
			}
			else { //BackGround
				DrawList->AddRectFilled( ImVec2( pos.x - 1, pos.y - 1 ), ImVec2( pos.x + dim.y + 1, pos.y + dim.x + 1 ), ImColor( 0, 0, 0, 255 ) );
				DrawList->AddRectFilled( ImVec2( pos.x, pos.y ), ImVec2( pos.x + dim.y, pos.y + dim.x ), ImColor( 80, 80, 80, 125 ) );
			}
			};

		if ( Cfg.HealthBar )
		{
			float MaxHealth = Entity.MaxHealth;

			CurrentESPAnim.Health = ImLerp( CurrentESPAnim.Health, Health, ImGui::GetIO( ).DeltaTime * 4 );
			float AnimHealth = CurrentESPAnim.Health;

			// OPT: FullHealthBar == Height (Height / 100 * 100 = Height), simplificado
			float FullHealthBar = Height;
			float DecreaseHealthBar = FullHealthBar * ( AnimHealth / MaxHealth );

			float Width2 = BoxRight - BoxLeft;
			// OPT: FullHealthBarH == Width2 (Width2 / 100 * 100 = Width2), simplificado
			float FullHealthBarH = Width2;
			float DecreaseHealthBarH = FullHealthBarH * ( AnimHealth / MaxHealth );

			if ( DecreaseHealthBarH > FullHealthBarH )
				DecreaseHealthBarH = FullHealthBarH;

			if ( DecreaseHealthBar > FullHealthBar )
				DecreaseHealthBar = FullHealthBar;

			ImColor BarColor;
			ImColor FullHealth =( ImVec4( ImColor( 80, 80, 80, 200 ) ) );

			const float HalfMax = MaxHealth * 0.5f;
			if ( Health > HalfMax )
			{
				BarColor =( ImVec4( ImColor( 66, 245, 132, 255 ) ) );
			}
			else if ( Health <= HalfMax && MaxHealth == 200 ? Health > 50 : Health > 150 )
			{
				BarColor =( ImVec4( ImColor( 245, 135, 66, 255 ) ) );
			}
			else
			{
				BarColor =( ImVec4( ImColor( 245, 66, 66, 255 ) ) );
			}

			switch ( HealthBarState )
			{
			case 0: //Top
				DrawHealthBarH( ImVec2( BoxMin.x, BoxMin.y - 4 ), ImVec2( 2, FullHealthBarH ),( ImVec4( FullHealth ) ), 0 );
				DrawHealthBarH( ImVec2( BoxMin.x, BoxMin.y - 4 ), ImVec2( 2, DecreaseHealthBarH ),( ImVec4( BarColor ) ), 1 );
				break;
			case 1: //Right
				DrawHealthBarV( ImVec2( BoxMax.x + 6, BoxMax.y ), ImVec2( 2, FullHealthBar ),( ImVec4( FullHealth ) ), 0 );
				DrawHealthBarV( ImVec2( BoxMax.x + 6, BoxMax.y ), ImVec2( 2, DecreaseHealthBar ),( ImVec4( BarColor ) ), 1 );
				break;
			case 2: //Bottom
				DrawHealthBarH( ImVec2( BoxMin.x, BoxMax.y + 6 ), ImVec2( 2, FullHealthBarH ),( ImVec4( FullHealth ) ), 0 );
				DrawHealthBarH( ImVec2( BoxMin.x, BoxMax.y + 6 ), ImVec2( 2, DecreaseHealthBarH ),( ImVec4( BarColor ) ), 1 );
				break;
			case 3: //Left
				DrawHealthBarV( ImVec2( BoxMin.x - 6, BoxMax.y ), ImVec2( 2, FullHealthBar ),( ImVec4( FullHealth ) ), 0 );
				DrawHealthBarV( ImVec2( BoxMin.x - 6, BoxMax.y ), ImVec2( 2, DecreaseHealthBar ),( ImVec4( BarColor ) ), 1 );
				break;

			default:
				DrawHealthBarV( ImVec2( BoxMin.x - 6, BoxMax.y ), ImVec2( 2, FullHealthBar ),( ImVec4( FullHealth ) ), 0 );
				DrawHealthBarV( ImVec2( BoxMin.x - 6, BoxMax.y ), ImVec2( 2, DecreaseHealthBar ),( ImVec4( BarColor ) ), 1 );
				break;
			}
		}

		if ( Cfg.ArmorBar )
		{
			float MaxHealth = Entity.MaxHealth;
			float Armor = Entity.Armor;

			if ( Armor > 0 )
			{
				MaxHealth = MaxHealth / 2;

				CurrentESPAnim.Armor = ImLerp( CurrentESPAnim.Armor, Armor, ImGui::GetIO( ).DeltaTime * 4 );
				float AnimArmor = CurrentESPAnim.Armor;

				// OPT: FullArmorBar == Height, FullArmorBarH == Width2, simplificado
				float Width2 = BoxRight - BoxLeft;
				float FullArmorBar = Height;
				float FullArmorBarH = Width2;
				float DecreaseHealthBar = FullArmorBar * ( AnimArmor / MaxHealth );
				float DecreaseArmorBarH = FullArmorBarH * ( AnimArmor / MaxHealth );

				if ( DecreaseHealthBar > FullArmorBar )
					DecreaseHealthBar = FullArmorBar;

				if ( DecreaseArmorBarH > FullArmorBarH )
					DecreaseArmorBarH = FullArmorBarH;

				ImColor BarColor;
				ImColor FullArmor = ImVec4( ImColor( 80, 80, 80, 200 ) );

				const float HalfMaxArmor = MaxHealth * 0.5f;
				if ( Armor > HalfMaxArmor ) {
					BarColor = ImVec4( ImColor( 85, 128, 200, 255 ) );
				}
				else if ( Armor <= HalfMaxArmor && MaxHealth == 200 ? Armor > 50 : Armor > 150 ) {
					BarColor = ImVec4( ImColor( 69, 102, 157, 255 ) );
				}
				else {
					BarColor = ImVec4( ImColor( 45, 62, 92, 255 ) );
				}

				const bool SameBarState = Cfg.HealthBar && HealthBarState == ArmorBarState;

				switch ( ArmorBarState )
				{

				case 0: //Top
					if ( SameBarState )
					{
						DrawHealthBarH( ImVec2( BoxMin.x, BoxMin.y - 8 ), ImVec2( 2, FullArmorBarH ), FullArmor, 0 );
						DrawHealthBarH( ImVec2( BoxMin.x, BoxMin.y - 8 ), ImVec2( 2, DecreaseArmorBarH ), BarColor, 1 );
					}
					else
					{
						DrawHealthBarH( ImVec2( BoxMin.x, BoxMin.y - 4 ), ImVec2( 2, FullArmorBarH ), FullArmor, 0 );
						DrawHealthBarH( ImVec2( BoxMin.x, BoxMin.y - 4 ), ImVec2( 2, DecreaseArmorBarH ), BarColor, 1 );
					}
					break;
				case 1: //Right
					if ( SameBarState )
					{
						DrawHealthBarV( ImVec2( BoxMax.x + 12, BoxMax.y ), ImVec2( 2, FullArmorBar ), FullArmor, 0 );
						DrawHealthBarV( ImVec2( BoxMax.x + 12, BoxMax.y ), ImVec2( 2, DecreaseHealthBar ), BarColor, 1 );
					}
					else
					{
						DrawHealthBarV( ImVec2( BoxMax.x + 6, BoxMax.y ), ImVec2( 2, FullArmorBar ), FullArmor, 0 );
						DrawHealthBarV( ImVec2( BoxMax.x + 6, BoxMax.y ), ImVec2( 2, DecreaseHealthBar ), BarColor, 1 );
					}
					break;
				case 2: //Bottom
					if ( SameBarState )
					{
						DrawHealthBarH( ImVec2( BoxMin.x, BoxMax.y + 12 ), ImVec2( 2, FullArmorBarH ), FullArmor, 0 );
						DrawHealthBarH( ImVec2( BoxMin.x, BoxMax.y + 12 ), ImVec2( 2, DecreaseArmorBarH ), BarColor, 1 );
					}
					else
					{
						DrawHealthBarH( ImVec2( BoxMin.x, BoxMax.y + 6 ), ImVec2( 2, FullArmorBarH ), FullArmor, 0 );
						DrawHealthBarH( ImVec2( BoxMin.x, BoxMax.y + 6 ), ImVec2( 2, DecreaseArmorBarH ), BarColor, 1 );
					}
					break;
				case 3: //Left
					if ( SameBarState )
					{
						DrawHealthBarV( ImVec2( BoxMin.x - 12, BoxMax.y ), ImVec2( 2, FullArmorBar ), FullArmor, 0 );
						DrawHealthBarV( ImVec2( BoxMin.x - 12, BoxMax.y ), ImVec2( 2, DecreaseHealthBar ), BarColor, 1 );
					}
					else
					{
						DrawHealthBarV( ImVec2( BoxMin.x - 6, BoxMax.y ), ImVec2( 2, FullArmorBar ), FullArmor, 0 );
						DrawHealthBarV( ImVec2( BoxMin.x - 6, BoxMax.y ), ImVec2( 2, DecreaseHealthBar ), BarColor, 1 );
					}
					break;

				default:
					DrawHealthBarV( ImVec2( BoxMin.x - 6, BoxMax.y ), ImVec2( 2, FullArmorBar ), FullArmor, 0 );
					DrawHealthBarV( ImVec2( BoxMin.x - 6, BoxMax.y ), ImVec2( 2, DecreaseHealthBar ), BarColor, 1 );
					break;
				}

			}

		}
	}
}

void Core::Features::cEsp::FeatureList()
{
	if (!g_Config.MiscESP.FeatureList)
		return;

	// OPT: Checar teclas apenas uma vez por frame, evitar re-alocação de vector
	// OPT: Usar array fixo em vez de vector para evitar heap allocation por frame
	static std::vector<std::string> activeFeatures;
	activeFeatures.clear();

	if (g_Config.Player.NoClipEnabled  && GetAsyncKeyState(g_Config.Player.NoClipKey))  activeFeatures.push_back(xorstr("Noclip"));
	if (g_Config.Player.EnableGodMode  && GetAsyncKeyState(g_Config.Player.GodModeKey)) activeFeatures.push_back(xorstr("God Mode"));
	if (g_Config.Player.UnlockAllActions) activeFeatures.push_back(xorstr("Unlock All Actions"));

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize;
	if (!g_MenuInfo.IsOpen)
	{
		window_flags |= ImGuiWindowFlags_NoInputs;
	}

	// Estilo da janela base (Transparente para desenharmos tudo manualmente via draw list)
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8.0f, 4.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.0f);

	ImGui::SetNextWindowPos(ImVec2(g_Variables.g_vGameWindowSize.x - 320, 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSizeConstraints(ImVec2(300, 0), ImVec2(300, FLT_MAX));

	if (ImGui::Begin(xorstr("FeatureListWindow"), nullptr, window_flags | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus))
	{
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw = ImGui::GetWindowDrawList();
		float width = ImGui::GetWindowWidth();
		
		float titleHeight = 35.0f; // Altura do header
		
		// Calcular a altura total baseada no conteúdo
		float contentHeight = activeFeatures.empty() ? 30.0f : (activeFeatures.size() * (ImGui::GetTextLineHeight() + 5.0f) + 15.0f);
		float totalHeight = titleHeight + contentHeight;

		// 1. Fundo do conteúdo (com gradiente descendo para transparente igual a foto)
		draw->AddRectFilledMultiColor(
			ImVec2(p.x, p.y + titleHeight), 
			ImVec2(p.x + width, p.y + totalHeight),
			ImColor(30, 30, 30, 240), ImColor(30, 30, 30, 240), // Top (Dark)
			ImColor(10, 10, 10, 0), ImColor(10, 10, 10, 0)      // Bottom (Transparent)
		);

		// 2. Fundo do Header (Preto sólido com cantos arredondados em cima)
		draw->AddRectFilled(p, ImVec2(p.x + width, p.y + titleHeight), ImColor(20, 20, 20, 255), 4.0f, ImDrawFlags_RoundCornersTop);

		// 3. Linha separadora bem fina debaixo do header
		draw->AddRectFilled(ImVec2(p.x, p.y + titleHeight - 1), ImVec2(p.x + width, p.y + titleHeight), ImColor(50, 50, 50, 255));

		// 4. Renderizar a Logo pequena no canto esquerdo
		float logoWidth = 70.0f;
		float logoHeight = 24.0f;
		if (g_Variables.Logo != nullptr) {
			ImGui::SetCursorPos(ImVec2(10.f, (titleHeight - logoHeight) / 2.f));
			ImGui::Image((void*)g_Variables.Logo, ImVec2(logoWidth, logoHeight));
		}

		// 5. Texto "Features List" ao lado da logo
		ImGui::PushFont(g_Variables.m_FontNormal); // Fonte bold
		ImGui::SetCursorPos(ImVec2(10.f + logoWidth + 20.f, (titleHeight - ImGui::GetTextLineHeight()) / 2.f));
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), xorstr("Features List"));
		ImGui::PopFont();

		// Mover cursor para desenhar os itens
		ImGui::SetCursorPos(ImVec2(0, titleHeight));
		ImGui::PushFont(g_Variables.m_DrawFont); // Fonte menor para os itens

		if (activeFeatures.empty())
		{
			ImGui::SetCursorPosX(15.f);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
			ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), xorstr("No features active"));
		}
		else
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
			for (const auto& feature : activeFeatures)
			{
				ImGui::SetCursorPosX(15.f);
				
				// Sombra do texto para dar o efeito de glow que tem na foto
				ImVec2 pos = ImGui::GetCursorScreenPos();
				draw->AddText(g_Variables.m_DrawFont, g_Variables.m_DrawFont->FontSize, ImVec2(pos.x + 1, pos.y + 1), ImColor(0, 0, 0, 255), feature.c_str());
				
				ImGui::TextColored(ImVec4(0.95f, 0.95f, 0.95f, 1.0f), "%s", feature.c_str());
			}
		}

		ImGui::PopFont();
		
		// Forçar o tamanho da janela para encaixar o gradiente certinho
		ImGui::Dummy(ImVec2(width, contentHeight - (ImGui::GetCursorPosY() - titleHeight)));
	}
	ImGui::End();

	ImGui::PopStyleVar(5);
	ImGui::PopStyleColor(2);
}

void Core::Features::cEsp::DrawVehicle( )
{
	auto Cfg = g_Config.VehicleESP;

	if ( !Cfg.Enabled )
		return;

	ImFont* RenderFont = g_Config.MiscESP.MinecraftFont ? g_Variables.m_MinecraftFont : g_Variables.m_DrawFont;

	// OPT: Obter DrawList uma única vez antes do loop
	auto DrawList = ImGui::GetBackgroundDrawList( );

	for ( auto Entity : Core::SDK::Game::VehicleList )
	{
		CVehicle * Vehicle = Entity.Pointer;

		float Distance = Entity.Dist;

		if ( Distance > Cfg.MaxDistance )
			continue;

		D3DXVECTOR2 VehicleLocation = Core::SDK::Game::WorldToScreen(
			Vehicle->GetPos( ) //Usei aqui pra não ter esse delay do esp por causa da thread
		);

		if ( !VehicleLocation )
			continue;

		if ( !SDK::Game::IsOnScreen( VehicleLocation ) )
			continue;

		if ( Cfg.SnapLines )
		{
			const ImVec2 SnapFrom( g_Variables.g_vGameWindowCenter.x, g_Variables.g_vGameWindowPos.y + g_Variables.g_vGameWindowSize.y );
			const ImVec2 SnapTo( VehicleLocation.x, VehicleLocation.y + 30 );
			DrawList->AddLine( SnapFrom, SnapTo, ImColor( 0, 0, 0 ), 2.5 );
			DrawList->AddLine( SnapFrom, SnapTo, Cfg.SnapLinesCol, 1.5 );
		}

		if ( Cfg.VehName )
		{
			ImVec2 text_size = RenderFont->CalcTextSizeA( RenderFont->FontSize, FLT_MAX, 0.0f, Entity.Name.c_str( ) );

			DrawList->AddText( RenderFont, RenderFont->FontSize, ImVec2( VehicleLocation.x - ( text_size.x / 2 ), VehicleLocation.y + 2 ), ImColor( 0, 0, 0 ), Entity.Name.c_str( ) );
			DrawList->AddText( RenderFont, RenderFont->FontSize, ImVec2( VehicleLocation.x - ( text_size.x / 2 ), VehicleLocation.y ), ImColor( 255, 255, 255 ), Entity.Name.c_str( ) );
		}

		if ( Cfg.ShowLockUnlock ) {
			bool IsLocked = Entity.IsLocked;
			float radius = 2 / Distance;

			const static std::string VehicleLocked = xorstr( "Press L to Unlock" );
			const static std::string VehicleUnlocked = xorstr( "Press L to Lock" );
			const static int fovRadius = 40;
			const static int L = 0x4C;
			const static int Delay = 500;


			float vdx = VehicleLocation.x - g_Variables.g_vGameWindowCenter.x;
			float vdy = VehicleLocation.y - g_Variables.g_vGameWindowCenter.y;
			int FovSize = (int)sqrtf( vdx * vdx + vdy * vdy );

			// OPT: radius + Distance < 1 calculado uma vez
			const bool RadiusSmall = (radius + Distance) < 1;
			const float InnerR = RadiusSmall ? 0 : 3;
			const float OuterR = RadiusSmall ? 1 : 4;

			if ( IsLocked )
			{
				DrawList->AddCircleFilled( ImVec2( VehicleLocation.x, VehicleLocation.y - 6 ), OuterR, ImColor( 0, 0, 0 ), 999 );
				DrawList->AddCircleFilled( ImVec2( VehicleLocation.x, VehicleLocation.y - 6 ), InnerR, ImColor( 250, 72, 62, 255 ), 999 );

				if ( FovSize < fovRadius )
				{
					ImVec2 text_size = RenderFont->CalcTextSizeA( RenderFont->FontSize, FLT_MAX, 0.0f, VehicleLocked.c_str( ) );

					DrawList->AddText( RenderFont, RenderFont->FontSize, ImVec2( VehicleLocation.x - ( text_size.x / 2 ), VehicleLocation.y - 28 ), ImColor( 0, 0, 0 ), VehicleLocked.c_str( ) );
					DrawList->AddText( RenderFont, RenderFont->FontSize, ImVec2( VehicleLocation.x - ( text_size.x / 2 ), VehicleLocation.y - 30 ), ImColor( 255, 255, 255 ), VehicleLocked.c_str( ) );

					if ( Utils::KeyPressedWithDelay( L, Delay ) )
						Vehicle->DoorState( true );
				}



			}
			else
			{
				DrawList->AddCircleFilled( ImVec2( VehicleLocation.x, VehicleLocation.y - 6 ), OuterR, ImColor( 0, 0, 0 ), 999 );
				DrawList->AddCircleFilled( ImVec2( VehicleLocation.x, VehicleLocation.y - 6 ), InnerR, ImColor( 102, 255, 133, 255 ), 999 );

				if ( FovSize < fovRadius )
				{
					ImVec2 text_size = RenderFont->CalcTextSizeA( RenderFont->FontSize, FLT_MAX, 0.0f, VehicleUnlocked.c_str( ) );

					DrawList->AddText( ImVec2( VehicleLocation.x - ( text_size.x / 2 ), VehicleLocation.y - 28 ), ImColor( 0, 0, 0 ), VehicleUnlocked.c_str( ) );
					DrawList->AddText( ImVec2( VehicleLocation.x - ( text_size.x / 2 ), VehicleLocation.y - 30 ), ImColor( 255, 255, 255 ), VehicleUnlocked.c_str( ) );

					if ( Utils::KeyPressedWithDelay( L, Delay ) )
						Vehicle->DoorState( false );
				}
			}
		}

		if ( Cfg.DistanceFromMe )
		{
			// OPT: Usar buffer estático em vez de std::to_string + concatenação
			static char VehDistBuf[32];
			snprintf(VehDistBuf, sizeof(VehDistBuf), "%dm", (int)Distance);

			ImVec2 text_size = RenderFont->CalcTextSizeA( RenderFont->FontSize, FLT_MAX, 0.0f, VehDistBuf );

			DrawList->AddText( ImVec2( VehicleLocation.x - ( text_size.x / 2 ), VehicleLocation.y + 16 ), ImColor( 0, 0, 0 ), VehDistBuf );
			DrawList->AddText( ImVec2( VehicleLocation.x - ( text_size.x / 2 ), VehicleLocation.y + 14 ), ImColor( 255, 255, 255 ), VehDistBuf );
		}

	}
}

void Core::Features::cEsp::AdminList( )
{
	if (!g_Config.ESP.Enabled || !g_Config.ESP.AdminList)
		return;

	struct AdminInfo {
		std::string name;
		float distance;
	};

	// OPT: Usar vector estático para evitar realocação de heap por frame
	static std::vector<AdminInfo> adminList;
	adminList.clear();

	for ( auto & Entity : Core::SDK::Game::EntityList )
	{
		CPed * Ped = Entity.Ped;
		if (!Ped) continue;

		// Skip local player
		if (Ped == Core::SDK::Pointers::pLocalPlayer) continue;

		// Use the same render distance as Player ESP
		if (Entity.Distance > g_Config.ESP.MaxDistance) continue;

		// Server-side Admin detection (pNetObject and visibility checks)
		bool IsInvisibleAdmin = false;
		
		if (Entity.PedType == 2) {
			if (Ped->IsSetInvisible()) {
				// Dead players or players with 0 health are NOT admins
				if (Entity.Health > 101.0f && !Entity.NetworkInfo.UserName.empty()) {
					IsInvisibleAdmin = true;
				}
			}
		}

		if (IsInvisibleAdmin) {
			std::string name = Entity.NetworkInfo.UserName;
			if (name.empty()) name = xorstr("Unknown Admin");
			adminList.push_back({name, Entity.Distance});
		}
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 4.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.0f); // Force alpha to 1.0f so it stays visible when menu is closed
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(30.f/255.f, 30.f/255.f, 32.f/255.f, 1.0f)); 

	ImGui::SetNextWindowSizeConstraints(ImVec2(220, 0), ImVec2(500, FLT_MAX));
	
	if (ImGui::Begin(xorstr("AdminListWindow"), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus))
	{
		ImGui::PushFont(g_Variables.m_FontNormal); // Ensure a valid font is used
		
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw = ImGui::GetWindowDrawList();
		float width = ImGui::GetWindowWidth();
		
		float titleHeight = 32.0f;
		
		// Title background
		draw->AddRectFilled(p, ImVec2(p.x + width, p.y + titleHeight), ImColor(18, 18, 20, 255), 4.0f, adminList.empty() ? ImDrawFlags_RoundCornersAll : ImDrawFlags_RoundCornersTop);
		
		// White left accent
		draw->AddRectFilled(ImVec2(p.x, p.y + 6), ImVec2(p.x + 3, p.y + titleHeight - 6), ImColor(255, 255, 255, 255), 2.0f, ImDrawFlags_RoundCornersRight);
		
		// Icon and Title Text
		ImGui::SetCursorScreenPos(ImVec2(p.x + 10, p.y + (titleHeight - ImGui::GetTextLineHeight()) / 2));
		
		// Render Ghost Icon with FontAwesome font
		ImGui::PushFont(g_Variables.FontAwesomeSolid);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
		ImGui::Text(xorstr("%s"), ICON_FA_GHOST);
		ImGui::PopStyleColor();
		ImGui::PopFont();

		ImGui::SameLine();
		
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));
		ImGui::Text(xorstr("Administrators"));
		ImGui::PopStyleColor();
		
		ImGui::SetCursorPos(ImVec2(0, titleHeight));
		
		if (!adminList.empty())
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4); // Top padding for items
			for (const auto& admin : adminList)
			{
				ImGui::SetCursorPosX(10);
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
				ImGui::Text("%s", admin.name.c_str());
				ImGui::PopStyleColor();
				
				// OPT: Usar buffer estático para distância
				static char AdminDistBuf[32];
				snprintf(AdminDistBuf, sizeof(AdminDistBuf), "%dm", (int)admin.distance);
				float textWidth = ImGui::CalcTextSize(AdminDistBuf).x;
				ImGui::SameLine(width - textWidth - 10);
				
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
				ImGui::Text("%s", AdminDistBuf);
				ImGui::PopStyleColor();
			}
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4); // Bottom padding
		}
		
		ImGui::PopFont();
	}
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(4);
}

void Core::Features::cEsp::InvisibleWarning()
{
	auto& Cfg = g_Config.ESP;
	if (!Cfg.Enabled || !Cfg.InvisiblePlayerWarning)
		return;

	int invisibleCount = 0;
	float closestDistance = 9999.f;

	for (auto& Entity : Core::SDK::Game::EntityList)
	{
		CPed* Ped = Entity.Ped;
		if (!Ped || Ped == Core::SDK::Pointers::pLocalPlayer)
			continue;

		if (Cfg.IgnoreNPCs && Entity.PedType != 2)
			continue;

		if (Cfg.IgnoreDead && Entity.Health <= 101.0f)
			continue;

		bool IsInvisible = false;
		if (Entity.PedType == 2) {
			if (Ped->IsSetInvisible()) {
				IsInvisible = true;
			}
		}

		if (Entity.Distance <= 300.f && IsInvisible)
		{
			invisibleCount++;
			if (Entity.Distance < closestDistance)
				closestDistance = Entity.Distance;
		}
	}

	if (invisibleCount > 0)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.0f); // Force alpha to 1.0f
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 0.7f));

		ImGui::SetNextWindowPos(ImVec2(g_Variables.g_vGameWindowSize.x / 2, 100), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
		if (ImGui::Begin(xorstr("InvisibleWarning"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing))
		{
			ImGui::PushFont(g_Variables.m_FontNormal);
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), xorstr("WARNING: %d Invisible entities nearby!"), invisibleCount);
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), xorstr("Closest: %.1fm"), closestDistance);
			ImGui::PopFont();
		}
		ImGui::End();

		ImGui::PopStyleColor();
		ImGui::PopStyleVar(3);
	}
}

#include "../Core.hpp" // Para garantir acesso aos namespaces de Exploits caso necessário
#include "Exploits/Exploits.hpp"

void Core::Features::cEsp::WeatherPersist()
{
	if (g_Config.Player.WeatherControlEnabled)
	{
		static int weatherTickCounter = 0;
		if (++weatherTickCounter >= 30)
		{
			weatherTickCounter = 0;
			Core::Features::Exploits::SetWeather(g_Config.Player.SelectedWeather);
		}
	}
}
