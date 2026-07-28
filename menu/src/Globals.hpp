#pragma once
#include <Includes/ImGui/Files/imgui.h>
#include <Windows.h>

#ifndef WDA_NONE
#define WDA_NONE 0x00000000
#endif

#ifndef WDA_EXCLUDEFROMCAPTURE
#define WDA_EXCLUDEFROMCAPTURE 0x00000011
#endif

#include <string>
#include <vector>

#include <d3dx11.h>
#include <d3d11.h>
#include <D3DX11tex.h>
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "D3DX11.lib" )

class cColors;
extern cColors g_Col;
class c_globals;
extern c_globals g_Variables;
class c_menu;
extern c_menu g_MenuInfo;

class cColors {
public:
	ImVec4 Base = ImVec4( 255.f/255.f, 255.f/255.f, 255.f/255.f, 1.f ); // White
	ImVec4 BaseEnd = ImVec4( 200.f/255.f, 200.f/255.f, 200.f/255.f, 1.f ); // Darker White for Gradient
	ImVec4 PrimaryText = ImVec4( 200.f/255.f, 200.f/255.f, 200.f/255.f, 1.f );
	ImVec4 SecundaryText = ImVec4( 80.f/255.f, 80.f/255.f, 80.f/255.f, 1.f );

	ImVec4 FeaturesText = ImVec4( 140.f/255.f, 140.f/255.f, 140.f/255.f, 1.f );
	ImVec4 SecundaryFeaturesText = ImVec4( 100.f/255.f, 100.f/255.f, 100.f/255.f, 1.f );

	ImVec4 BorderCol = ImVec4( 32.f/255.f, 32.f/255.f, 34.f/255.f, 1.f );
	ImVec4 LinesCol = ImVec4( 30.f/255.f, 30.f/255.f, 33.f/255.f, 1.f );
	ImVec4 BackgroundCol = ImVec4( 0.f/255.f, 0.f/255.f, 0.f/255.f, 1.f );

	ImVec4 ChildCol = ImVec4( 16.f/255.f, 16.f/255.f, 18.f/255.f, 1.f );
	ImVec4 ChildBorderCol = ImVec4( 18.f/255.f, 18.f/255.f, 20.f/255.f, 1.f );

	ImVec4 TitleBar = ImVec4( 15.f/255.f, 15.f/255.f, 18.f/255.f, 1.f );
	ImVec4 TitleBarBorder = ImVec4( 21.f/255.f, 21.f/255.f, 24.f/255.f, 1.f );

	ImVec4 SideBar = ImVec4( 14.f/255.f, 14.f/255.f, 16.f/255.f, 1.f );
	ImVec4 SideBarBorder = ImVec4( 21.f/255.f, 21.f/255.f, 23.f/255.f, 1.f );

	ImVec4 ButtonHovered = ImVec4( 180.f/255.f, 180.f/255.f, 180.f/255.f, 100.f/255.f );
	ImVec4 TestingTest = ImVec4( 180.f/255.f, 180.f/255.f, 180.f/255.f, 1.f );

	ImVec4 InputBackground = ImVec4( 16.f/255.f, 16.f/255.f, 16.f/255.f, 1.f );
	ImVec4 InputBorder = ImVec4( 22.f/255.f, 22.f/255.f, 22.f/255.f, 1.f );
};

inline cColors g_Col;

class c_globals {
public:
	std::string id;
	std::string version;
	DWORD ProcIdFiveM = 0;
	int Pid;

	bool g_bPassedByThisVerify;
	uintptr_t g_VerifyLogin;
	bool done;
	bool IsOpen;

	std::string ServerIp;
	std::string UserName = "User";
	std::string Role = "Developer";

	ImVec2 TestePos;

	char m_Config[ 6000 ];
	HWND g_hCheatWindow;
	HWND g_hGameWindow;
	ImVec2 g_vGameWindowSize;
	ImVec2 g_vGameWindowPos;
	ImVec2 g_vGameWindowCenter;

	ImFont * m_FontGiant;
	ImFont * m_FontBig;
	ImFont * m_FontBigSmall;
	ImFont * m_FontNormal;
	ImFont * m_FontSecundary;
	ImFont * m_FontSmaller;
	ImFont * m_DrawFont;
	ImFont * m_Expand;
	ImFont * m_MinecraftFont;

	ImFont * FontAwesomeSolid;
	ImFont * FontAwesomeSolidSmall;
	ImFont * FontAwesomeRegular;
	ImFont * FontAwesomeBrands;


	ID3D11ShaderResourceView * Logo = nullptr;
	ID3D11ShaderResourceView * kid_image = nullptr;

	struct FiveM_Weapons_t {
		ID3D11ShaderResourceView * gadget_parachute = nullptr;
		ID3D11ShaderResourceView * weapon_advancedrifle = nullptr;
		ID3D11ShaderResourceView * weapon_appistol = nullptr;
		ID3D11ShaderResourceView * weapon_assaultrifle = nullptr;
		ID3D11ShaderResourceView * weapon_assaultrifle_mk2 = nullptr;
		ID3D11ShaderResourceView * weapon_assaultshotgun = nullptr;
		ID3D11ShaderResourceView * weapon_assaultsmg = nullptr;
		ID3D11ShaderResourceView * weapon_autoshotgun = nullptr;
		ID3D11ShaderResourceView * weapon_ball = nullptr;
		ID3D11ShaderResourceView * weapon_bat = nullptr;
		ID3D11ShaderResourceView * weapon_battleaxe = nullptr;
		ID3D11ShaderResourceView * weapon_bottle = nullptr;
		ID3D11ShaderResourceView * weapon_bullpuprifle = nullptr;
		ID3D11ShaderResourceView * weapon_bullpuprifle_mk2 = nullptr;
		ID3D11ShaderResourceView * weapon_bullpupshotgun = nullptr;
		ID3D11ShaderResourceView * weapon_bzgas = nullptr;
		ID3D11ShaderResourceView * weapon_carbinerifle = nullptr;
		ID3D11ShaderResourceView * weapon_carbinerifle_mk2 = nullptr;
		ID3D11ShaderResourceView * weapon_ceramicpistol = nullptr;
		ID3D11ShaderResourceView * weapon_combatmg = nullptr;
		ID3D11ShaderResourceView * weapon_combatmg_mk2 = nullptr;
		ID3D11ShaderResourceView * weapon_combatpdw = nullptr;
		ID3D11ShaderResourceView * weapon_combatpistol = nullptr;
		ID3D11ShaderResourceView * weapon_combatshotgun = nullptr;
		ID3D11ShaderResourceView * weapon_compactlauncher = nullptr;
		ID3D11ShaderResourceView * weapon_compactrifle = nullptr;
		ID3D11ShaderResourceView * weapon_crowbar = nullptr;
		ID3D11ShaderResourceView * weapon_dagger = nullptr;
		ID3D11ShaderResourceView * weapon_dbshotgun = nullptr;
		ID3D11ShaderResourceView * weapon_doubleaction = nullptr;
		ID3D11ShaderResourceView * weapon_fireextinguisher = nullptr;
		ID3D11ShaderResourceView * weapon_firework = nullptr;
		ID3D11ShaderResourceView * weapon_flare = nullptr;
		ID3D11ShaderResourceView * weapon_flaregun = nullptr;
		ID3D11ShaderResourceView * weapon_flashlight = nullptr;
		ID3D11ShaderResourceView * weapon_gadgetpistol = nullptr;
		ID3D11ShaderResourceView * weapon_golfclub = nullptr;
		ID3D11ShaderResourceView * weapon_grenade = nullptr;
		ID3D11ShaderResourceView * weapon_grenadelauncher = nullptr;
		ID3D11ShaderResourceView * weapon_grenadelauncher_smoke = nullptr;
		ID3D11ShaderResourceView * weapon_gusenberg = nullptr;
		ID3D11ShaderResourceView * weapon_hammer = nullptr;
		ID3D11ShaderResourceView * weapon_hatchet = nullptr;
		ID3D11ShaderResourceView * weapon_hazardcan = nullptr;
		ID3D11ShaderResourceView * weapon_heavypistol = nullptr;
		ID3D11ShaderResourceView * weapon_heavyshotgun = nullptr;
		ID3D11ShaderResourceView * weapon_heavysniper = nullptr;
		ID3D11ShaderResourceView * weapon_heavysniper_mk2 = nullptr;
		ID3D11ShaderResourceView * weapon_hominglauncher = nullptr;
		ID3D11ShaderResourceView * weapon_knife = nullptr;
		ID3D11ShaderResourceView * weapon_knuckle = nullptr;
		ID3D11ShaderResourceView * weapon_machete = nullptr;
		ID3D11ShaderResourceView * weapon_machinepistol = nullptr;
		ID3D11ShaderResourceView * weapon_marksmanpistol = nullptr;
		ID3D11ShaderResourceView * weapon_marksmanrifle = nullptr;
		ID3D11ShaderResourceView * weapon_marksmanrifle_mk2 = nullptr;
		ID3D11ShaderResourceView * weapon_mg = nullptr;
		ID3D11ShaderResourceView * weapon_microsmg = nullptr;
		ID3D11ShaderResourceView * weapon_militaryrifle = nullptr;
		ID3D11ShaderResourceView * weapon_minigun = nullptr;
		ID3D11ShaderResourceView * weapon_minismg = nullptr;
		ID3D11ShaderResourceView * weapon_molotov = nullptr;
		ID3D11ShaderResourceView * weapon_musket = nullptr;
		ID3D11ShaderResourceView * weapon_navyrevolver = nullptr;
		ID3D11ShaderResourceView * weapon_nightstick = nullptr;
		ID3D11ShaderResourceView * weapon_petrolcan = nullptr;
		ID3D11ShaderResourceView * weapon_pipebomb = nullptr;
		ID3D11ShaderResourceView * weapon_pistol = nullptr;
		ID3D11ShaderResourceView * weapon_pistol50 = nullptr;
		ID3D11ShaderResourceView * weapon_pistol_mk2 = nullptr;
		ID3D11ShaderResourceView * weapon_poolcue = nullptr;
		ID3D11ShaderResourceView * weapon_proxmine = nullptr;
		ID3D11ShaderResourceView * weapon_pumpshotgun = nullptr;
		ID3D11ShaderResourceView * weapon_pumpshotgun_mk2 = nullptr;
		ID3D11ShaderResourceView * weapon_railgun = nullptr;
		ID3D11ShaderResourceView * weapon_raycarbine = nullptr;
		ID3D11ShaderResourceView * weapon_rayminigun = nullptr;
		ID3D11ShaderResourceView * weapon_raypistol = nullptr;
		ID3D11ShaderResourceView * weapon_revolver = nullptr;
		ID3D11ShaderResourceView * weapon_revolver_mk2 = nullptr;
		ID3D11ShaderResourceView * weapon_rpg = nullptr;
		ID3D11ShaderResourceView * weapon_sawnoffshotgun = nullptr;
		ID3D11ShaderResourceView * weapon_smg = nullptr;
		ID3D11ShaderResourceView * weapon_smg_mk2 = nullptr;
		ID3D11ShaderResourceView * weapon_smokegrenade = nullptr;
		ID3D11ShaderResourceView * weapon_sniperrifle = nullptr;
		ID3D11ShaderResourceView * weapon_snowball = nullptr;
		ID3D11ShaderResourceView * weapon_snspistol = nullptr;
		ID3D11ShaderResourceView * weapon_snspistol_mk2 = nullptr;
		ID3D11ShaderResourceView * weapon_specialcarbine = nullptr;
		ID3D11ShaderResourceView * weapon_specialcarbine_mk2 = nullptr;
		ID3D11ShaderResourceView * weapon_stickybomb = nullptr;
		ID3D11ShaderResourceView * weapon_stone_hatchet = nullptr;
		ID3D11ShaderResourceView * weapon_stungun = nullptr;
		ID3D11ShaderResourceView * weapon_switchblade = nullptr;
		ID3D11ShaderResourceView * weapon_unarmed = nullptr;
		ID3D11ShaderResourceView * weapon_vintagepistol = nullptr;
		ID3D11ShaderResourceView * weapon_wrench = nullptr;

	}FiveM_WeaponsPic;
	
};

inline c_globals g_Variables;

class c_menu {
public:

	enum PAGES {
		Combat,
		Visuals,
		Local,
		World,
		Resoucer,
		Exploits,
		Teste,
		Settings,
		Login
	};

	bool IsOpen = true;

	int iTabCount = 0;
	float TabAlpha = 0.f;
	int iCurrentPage = 0;
	float TabAdd = 0.f;
	bool IsLogged = false;
	bool IsSplashFinished = false;
	DWORD SplashStartTime = 0;
	bool IsSuccessSplashFinished = false;
	DWORD SuccessSplashStartTime = 0;
	float MenuAlpha = 0.f;

	char cDiscordId[ 200 ] ;
	char user[30] = ""; // Variable para almacenar la clave ingresada
	char pass[30] = ""; // Variable para almacenar la clave ingresada
	char key[100] = ""; // Key for auth
	bool remember_key = false;
	bool login_success = false;
	bool show_product_selection = false;
	bool is_injecting = false;
	std::string server_response;

	ImVec2 MenuSize = ImVec2(1120, 480);
	ImVec2 LoginSize = ImVec2(900, 440);

	// Menu Particles
	bool EnableParticles = true;

	// Glassmorphism effect
	bool Glassmorphism = false;

	// Resolution scaling
	float ResolutionScale = 1.0f;

};

inline c_menu g_MenuInfo;