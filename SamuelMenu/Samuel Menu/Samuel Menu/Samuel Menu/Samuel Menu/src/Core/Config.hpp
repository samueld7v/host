#pragma once
#include <Includes/Includes.hpp>
#include <Includes/Utils.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace Core {

	class Config {
	public:
		struct General {
			bool StreamProof = false;
			bool WaterMark = false;
			bool WaterMarkCol = false;
			bool ArrayList = false;
			bool ArrayListCol = false;
			bool VSync = false;
			bool SecondMonitor = false;
			int ProcessPriority = 0;
			int MenuKey = VK_INSERT;
		} General;

		struct Aimbot {
			bool Enabled = false;
			bool ShowFov = false;
			bool OnlyVisible = false;
			bool IgnoreNPCs = false;
			bool Prediction = false;
			int FOV = 180;
			int MaxDistance = 240;
			int AimbotSpeed = 12;
			int SmoothVertical = 12;
			int KeyBind = 0;
			ImColor FovColor{ 255, 255, 255 };
		} Aimbot;

		struct TriggerBot {
			bool Enabled = false;
			bool ShowFov = false;
			bool OnlyVisible = false;
			bool IgnoreNPCs = false;
			bool SmartTrigger = false;
			int FOV = 20;
			int MaxDistance = 200;
			int Delay = 0;
			int KeyBind = 0;
			ImColor FovColor{ 255, 255, 255 };
		} TriggerBot;

		struct SilentAim {
			bool Enabled = false;
			bool ShowFov = false;
			bool OnlyVisible = false;
			bool MagicBullets = false;
			bool IgnoreNPCs = false;
			int FOV = 40;
			int MissChance = 0;
			int MaxDistance = 200;
			int KeyBind = 0;
			ImColor FovColor{ 224, 94, 103, 200 };
		} SilentAim;

		struct ESP {
			bool UpdateCfgESP = false;
			bool Enabled = false;
			bool Box = false;
			bool FilledBox = false;
			int BoxState = 0;
			bool Skeleton = false;
			float SkeletonSize = 1.5f;
			bool HealthBar = false;
			ImVec2 HealthBarPos{};
			int HealthBarState = 0;
			bool ArmorBar = false;
			ImVec2 ArmorBarPos{};
			int ArmorBarState = 0;
			bool WeaponName = false;
			ImVec2 WeaponNamePos{};
			int WeaponNameState = 0;
			bool SnapLines = false;
			bool UserNames = false;
			ImVec2 UserNamesPos{};
			int UserNamesState = 0;
			bool HeadCircle = false;
			bool ChinaHat = false;
			bool IgnoreNPCs = false;
			bool ShowLocalPlayer = false;
			bool HighlightVisible = false;
			bool IgnoreDead = false;
			bool DistanceFromMe = false;
			bool FriendsMarker = false;
			bool AdminList = false;
			bool AdminHighlight = false;
			bool InvisiblePlayerWarning = false;
			int FriendsMarkerBind = 0;
			ImVec2 DistanceFromMePos{};
			int DistanceFromMeState = 0;
			int MaxDistance = 200;
			float TextSize = 1.0f;
			int KeyBind = 0;
			ImColor DistanceCol{ 230, 230, 230, 255 };
			ImColor ChinaHatCol{ 230, 230, 230, 255 };
			ImColor UserNamesCol{ 230, 230, 230, 255 };
			ImColor WeaponNameCol{ 230, 230, 230, 255 };
			ImColor SkeletonCol{ 255, 255, 255, 200 };
			ImColor InvisibleFilterColor{ 255, 0, 0, 255 };
			ImColor BoxCol{ 255, 255, 255, 200 };
			ImColor FilledBoxCol{ 0, 0, 0, 40 };
			ImColor SnapLinesCol{ 255, 255, 255, 200 };
			ImColor FriendCol{ 255, 204, 0, 255 };
			ImColor AdminHighlightCol{ 255, 0, 0, 255 };
			bool Crosshair = false;
			int CrosshairType = 0;
			float CrosshairSize = 10.0f;
			float CrosshairThickness = 1.0f;
			ImColor CrosshairColor{ 255, 255, 255, 255 };
		} ESP;

		struct VehicleESP {
			bool Enabled = false;
			bool SnapLines = false;
			bool ShowLockUnlock = false;
			bool VehName = false;
			bool DistanceFromMe = false;
			int MaxDistance = 200;
			ImColor SnapLinesCol{ 255, 255, 255, 200 };
		} VehicleESP;

		struct Player {
			float CurrentHealthValue = 0.f;
			float CurrentArmorValue = 0.f;
			bool SuperJump = false;
			bool BeastJump = false;
			bool FastRun = false;
			float RunSpeed = 1.f;
			bool InfiniteStamina = false;
			bool WeaponOptions = false;
			bool NoRecoilEnabled = false;
			float RecoilValue = 0.f;
			bool NoSpreadEnabled = false;
			float SpreadValue = 0.f;
			bool InfiniteAmmoEnabled = false;
			bool NoReloadEnabled = false;
			bool NoClipEnabled = false;
			int NoClipMode = 0;
			bool NoClipHoldMode = false;
			bool HandlingEditor = false;
			int NoClipKey = 0;
			float NoClipSpeed = 1.0f;
			bool InfiniteCombatRoll = false;
			bool EnableGodMode = false;
			bool SpectateEnabled = false;
			bool VehicleGodMode = false;
			bool SeatBelt = false;
			bool JumpingCar = false;
			bool CarPlaning = false;
			bool ChangeVehicleColor = false;
			bool RainbowCar = false;
			float RainbowCarSpeed = 1.0f;
			ImColor VehicleColor{ 255, 0, 0, 255 };
			bool CamFov = false;
			float CamFovAmount = 0.f;
			uint64_t currentModelInfo = 0;
			float originalCamDistance = 0.f;
			bool RocketBoost = false;
			bool BuzinaBoost = false;
			int BuzinaBoostKey = 0x45;
			float BuzinaBoostSpeed = 30.0f;
			bool PsychicGun = false;
			float HornBoostPower = 30.0f;
			int RocketBoostBind = 0;
			bool SpeedHack = false;
			int SpeedHackBind = 0;
			float SpeedHackSpeed = 0.f;
			bool FixVehicle = false;
			int FixVehicleBind = 0;
			int RainVehiclesBind = 0;
			bool ModifyHandling = false;
			float Acceleration = 0.f;
			float BreakForce = 0.f;
			float TractionCurveMin = 0.f;
			float CollisionDamage = 0.f;
			bool TpToWayPoint = false;
			int TpToWayPointBind = 0;
			bool ForceWeaponWheel = false;
			bool SuperFist = false;
			bool ExplosiveFist = false;
			bool DoubleShot = false;
			bool FireAmmo = false;
			bool ShrinkEnabled = false;
			bool NoRagDollEnabled = false;
			bool AntiHSEnabled = false;
			bool StealCarEnabled = false;
			bool UnlockAllActions = false;
			int GodModeKey = 0;
			bool InvisibleLocal = false;
			bool WeaponSizeEnabled = false;
			float WeaponSize = 1.0f;
			bool AntiEntityAttach = false;
			bool ParaDeVenderEssaMerda = false;
			int ParaDeVenderEssaMerdaKey = 0;
			float SavedPeekX = 0.0f;
			float SavedPeekY = 0.0f;
			float SavedPeekZ = 0.0f;
			bool PeekPositionSaved = false;
			int SavePeekKey = 0;
			int TeleportPeekKey = 0;
			bool SpinbotEnabled = false;
			float SpinbotSpeed = 100.0f;
			bool CombatGlitch = false;
			bool FakeLagEnabled = false;
			int FakeLagDelay = 200;
			bool WeatherControlEnabled = false;
			int SelectedWeather = 0;
			bool SoloSessionEnabled = false;
			bool FreecamEnabled = false;
			int FreecamKey = 0;
			float FreecamSpeed = 1.0f;
			bool FreeCamActivate = false;
			int current_mode = 0;
			int iMaxModes = 6;
		} Player;

		struct MiscESP {
			bool MinecraftFont = false;
			bool HyperXFont = false;
			bool VegasFont = false;
			bool FeatureList = false;
		} MiscESP;

	private:
		static nlohmann::json ImColToJson(const ImColor& Col) {
			return nlohmann::json::array({ Col.Value.x, Col.Value.y, Col.Value.z, Col.Value.w });
		}

		static ImColor JsonToImCol(const nlohmann::json& JsonCol) {
			if (JsonCol.is_array() && JsonCol.size() == 4)
				return ImColor(static_cast<float>(JsonCol[0]), static_cast<float>(JsonCol[1]), static_cast<float>(JsonCol[2]), static_cast<float>(JsonCol[3]));
			return ImColor(0.0f, 0.0f, 0.0f, 1.0f);
		}

		template<typename T>
		static void WriteOpt(nlohmann::json& j, const char* key, const T& val) {
			j[key] = val;
		}

		static void WriteCol(nlohmann::json& j, const char* key, const ImColor& col) {
			j[key] = ImColToJson(col);
		}

		template<typename T>
		static T ReadOpt(const nlohmann::json& j, const char* key, const T& fallback) {
			if (j.contains(key)) return j[key];
			return fallback;
		}

		static ImColor ReadCol(const nlohmann::json& j, const char* key, const ImColor& fallback) {
			if (j.contains(key)) return JsonToImCol(j[key]);
			return fallback;
		}

		template<typename S>
		static void SerializeStruct(nlohmann::json& j, S& s) {
			(void)j; (void)s;
		}

		template<typename S, typename T, typename... Rest>
		static void SerializeStruct(nlohmann::json& j, S& s, const char* key, T S::* member, Rest... rest) {
			WriteOpt(j, key, s.*member);
			SerializeStruct(j, s, rest...);
		}

		template<typename S>
		static void DeserializeStruct(const nlohmann::json& j, S& s) {
			(void)j; (void)s;
		}

		template<typename S, typename T, typename... Rest>
		static void DeserializeStruct(const nlohmann::json& j, S& s, const char* key, T S::* member, Rest... rest) {
			if constexpr (std::is_same_v<T, ImColor>) {
				s.*member = ReadCol(j, key, s.*member);
			}
			else {
				s.*member = ReadOpt(j, key, s.*member);
			}
			DeserializeStruct(j, s, rest...);
		}

		void SerializeAimbot(nlohmann::json& j) {
			auto& a = j[xorstr("Aimbot")];
			WriteOpt(a, xorstr("Enabled"), Aimbot.Enabled);
			WriteOpt(a, xorstr("ShowFov"), Aimbot.ShowFov);
			WriteOpt(a, xorstr("OnlyVisible"), Aimbot.OnlyVisible);
			WriteOpt(a, xorstr("IgnoreNPCs"), Aimbot.IgnoreNPCs);
			WriteOpt(a, xorstr("Prediction"), Aimbot.Prediction);
			WriteOpt(a, xorstr("FOV"), Aimbot.FOV);
			WriteOpt(a, xorstr("MaxDistance"), Aimbot.MaxDistance);
			WriteOpt(a, xorstr("AimSpeed"), Aimbot.AimbotSpeed);
			WriteOpt(a, xorstr("SmoothVertical"), Aimbot.SmoothVertical);
			WriteOpt(a, xorstr("KeyBind"), Aimbot.KeyBind);
			WriteCol(a, xorstr("FovColor"), Aimbot.FovColor);
		}

		void DeserializeAimbot(const nlohmann::json& j) {
			auto& a = j[xorstr("Aimbot")];
			Aimbot.Enabled = a[xorstr("Enabled")];
			Aimbot.ShowFov = a[xorstr("ShowFov")];
			Aimbot.OnlyVisible = a[xorstr("OnlyVisible")];
			Aimbot.IgnoreNPCs = a[xorstr("IgnoreNPCs")];
			Aimbot.Prediction = ReadOpt(a, xorstr("Prediction"), false);
			Aimbot.FOV = a[xorstr("FOV")];
			Aimbot.MaxDistance = a[xorstr("MaxDistance")];
			Aimbot.AimbotSpeed = a[xorstr("AimSpeed")];
			Aimbot.SmoothVertical = ReadOpt(a, xorstr("SmoothVertical"), 12);
			Aimbot.KeyBind = a[xorstr("KeyBind")];
			Aimbot.FovColor = ReadCol(a, xorstr("FovColor"), ImColor(255, 255, 255));
		}

		void SerializeTriggerBot(nlohmann::json& j) {
			auto& t = j[xorstr("TriggerBot")];
			WriteOpt(t, xorstr("Enabled"), TriggerBot.Enabled);
			WriteOpt(t, xorstr("ShowFov"), TriggerBot.ShowFov);
			WriteOpt(t, xorstr("OnlyVisible"), TriggerBot.OnlyVisible);
			WriteOpt(t, xorstr("IgnoreNPCs"), TriggerBot.IgnoreNPCs);
			WriteOpt(t, xorstr("SmartTrigger"), TriggerBot.SmartTrigger);
			WriteOpt(t, xorstr("FOV"), TriggerBot.FOV);
			WriteOpt(t, xorstr("MaxDistance"), TriggerBot.MaxDistance);
			WriteOpt(t, xorstr("Delay"), TriggerBot.Delay);
			WriteOpt(t, xorstr("KeyBind"), TriggerBot.KeyBind);
			WriteCol(t, xorstr("FovColor"), TriggerBot.FovColor);
		}

		void DeserializeTriggerBot(const nlohmann::json& j) {
			auto& t = j[xorstr("TriggerBot")];
			TriggerBot.Enabled = t[xorstr("Enabled")];
			TriggerBot.ShowFov = t[xorstr("ShowFov")];
			TriggerBot.OnlyVisible = t[xorstr("OnlyVisible")];
			TriggerBot.IgnoreNPCs = t[xorstr("IgnoreNPCs")];
			TriggerBot.SmartTrigger = ReadOpt(t, xorstr("SmartTrigger"), false);
			TriggerBot.FOV = t[xorstr("FOV")];
			TriggerBot.MaxDistance = t[xorstr("MaxDistance")];
			TriggerBot.Delay = t[xorstr("Delay")];
			TriggerBot.KeyBind = t[xorstr("KeyBind")];
			TriggerBot.FovColor = ReadCol(t, xorstr("FovColor"), ImColor(255, 255, 255));
		}

		void SerializeSilentAim(nlohmann::json& j) {
			auto& s = j[xorstr("SilentAim")];
			WriteOpt(s, xorstr("Enabled"), SilentAim.Enabled);
			WriteOpt(s, xorstr("ShowFov"), SilentAim.ShowFov);
			WriteOpt(s, xorstr("OnlyVisible"), SilentAim.OnlyVisible);
			WriteOpt(s, xorstr("IgnoreNPCs"), SilentAim.IgnoreNPCs);
			WriteOpt(s, xorstr("FOV"), SilentAim.FOV);
			WriteOpt(s, xorstr("MaxDistance"), SilentAim.MaxDistance);
			WriteOpt(s, xorstr("KeyBind"), SilentAim.KeyBind);
			WriteOpt(s, xorstr("MissChance"), SilentAim.MissChance);
			WriteOpt(s, xorstr("MagicBullets"), SilentAim.MagicBullets);
			WriteCol(s, xorstr("FovColor"), SilentAim.FovColor);
		}

		void DeserializeSilentAim(const nlohmann::json& j) {
			auto& s = j[xorstr("SilentAim")];
			SilentAim.Enabled = s[xorstr("Enabled")];
			SilentAim.ShowFov = s[xorstr("ShowFov")];
			SilentAim.OnlyVisible = s[xorstr("OnlyVisible")];
			SilentAim.IgnoreNPCs = s[xorstr("IgnoreNPCs")];
			SilentAim.FOV = s[xorstr("FOV")];
			SilentAim.MaxDistance = s[xorstr("MaxDistance")];
			SilentAim.KeyBind = s[xorstr("KeyBind")];
			SilentAim.MagicBullets = s[xorstr("MagicBullets")];
			SilentAim.FovColor = ReadCol(s, xorstr("FovColor"), ImColor(224, 94, 103, 200));
		}

		void SerializeESP(nlohmann::json& j) {
			auto& e = j[xorstr("ESP")];
			WriteOpt(e, xorstr("Enabled"), ESP.Enabled);
			WriteOpt(e, xorstr("Box"), ESP.Box);
			WriteOpt(e, xorstr("FilledBox"), ESP.FilledBox);
			WriteOpt(e, xorstr("BoxState"), ESP.BoxState);
			WriteOpt(e, xorstr("Skeleton"), ESP.Skeleton);
			WriteOpt(e, xorstr("SkeletonSize"), ESP.SkeletonSize);
			WriteOpt(e, xorstr("HealthBar"), ESP.HealthBar);
			WriteOpt(e, xorstr("HealthBarState"), ESP.HealthBarState);
			WriteOpt(e, xorstr("ArmorBar"), ESP.ArmorBar);
			WriteOpt(e, xorstr("ArmorBarState"), ESP.ArmorBarState);
			WriteOpt(e, xorstr("WeaponName"), ESP.WeaponName);
			WriteOpt(e, xorstr("WeaponNameState"), ESP.WeaponNameState);
			WriteOpt(e, xorstr("SnapLines"), ESP.SnapLines);
			WriteOpt(e, xorstr("UserNames"), ESP.UserNames);
			WriteOpt(e, xorstr("UserNamesState"), ESP.UserNamesState);
			WriteOpt(e, xorstr("HeadCircle"), ESP.HeadCircle);
			WriteOpt(e, xorstr("ChinaHat"), ESP.ChinaHat);
			WriteOpt(e, xorstr("IgnoreNPCs"), ESP.IgnoreNPCs);
			WriteOpt(e, xorstr("HighlightVisible"), ESP.HighlightVisible);
			WriteOpt(e, xorstr("IgnoreDead"), ESP.IgnoreDead);
			WriteOpt(e, xorstr("DistanceFromMe"), ESP.DistanceFromMe);
			WriteOpt(e, xorstr("AdminList"), ESP.AdminList);
			WriteOpt(e, xorstr("AdminHighlight"), ESP.AdminHighlight);
			WriteOpt(e, xorstr("InvisiblePlayerWarning"), ESP.InvisiblePlayerWarning);
			WriteOpt(e, xorstr("DistanceFromMeState"), ESP.DistanceFromMeState);
			WriteOpt(e, xorstr("MaxDistance"), ESP.MaxDistance);
			WriteOpt(e, xorstr("TextSize"), ESP.TextSize);
			WriteOpt(e, xorstr("ShowLocalPlayer"), ESP.ShowLocalPlayer);
			WriteOpt(e, xorstr("FriendsMarker"), ESP.FriendsMarker);
			WriteOpt(e, xorstr("FriendsMarkerBind"), ESP.FriendsMarkerBind);
			WriteCol(e, xorstr("DistanceCol"), ESP.DistanceCol);
			WriteCol(e, xorstr("ChinaHatCol"), ESP.ChinaHatCol);
			WriteCol(e, xorstr("UserNamesCol"), ESP.UserNamesCol);
			WriteCol(e, xorstr("WeaponNameCol"), ESP.WeaponNameCol);
			WriteCol(e, xorstr("SkeletonCol"), ESP.SkeletonCol);
			WriteCol(e, xorstr("InvisibleFilterColor"), ESP.InvisibleFilterColor);
			WriteCol(e, xorstr("AdminHighlightCol"), ESP.AdminHighlightCol);
			WriteCol(e, xorstr("BoxCol"), ESP.BoxCol);
			WriteCol(e, xorstr("FilledBoxCol"), ESP.FilledBoxCol);
			WriteCol(e, xorstr("SnapLinesCol"), ESP.SnapLinesCol);
			WriteCol(e, xorstr("FriendCol"), ESP.FriendCol);
		}

		void DeserializeESP(const nlohmann::json& j) {
			auto& e = j[xorstr("ESP")];
			ESP.Enabled = e[xorstr("Enabled")];
			ESP.Box = e[xorstr("Box")];
			ESP.FilledBox = ReadOpt(e, xorstr("FilledBox"), false);
			ESP.BoxState = e[xorstr("BoxState")];
			ESP.Skeleton = e[xorstr("Skeleton")];
			ESP.SkeletonSize = ReadOpt(e, xorstr("SkeletonSize"), 1.5f);
			ESP.HealthBar = e[xorstr("HealthBar")];
			ESP.HealthBarState = e[xorstr("HealthBarState")];
			ESP.ArmorBar = e[xorstr("ArmorBar")];
			ESP.ArmorBarState = e[xorstr("ArmorBarState")];
			ESP.WeaponName = e[xorstr("WeaponName")];
			ESP.WeaponNameState = e[xorstr("WeaponNameState")];
			ESP.SnapLines = e[xorstr("SnapLines")];
			ESP.UserNames = e[xorstr("UserNames")];
			ESP.UserNamesState = e[xorstr("UserNamesState")];
			ESP.HeadCircle = e[xorstr("HeadCircle")];
			ESP.ChinaHat = ReadOpt(e, xorstr("ChinaHat"), false);
			ESP.IgnoreNPCs = e[xorstr("IgnoreNPCs")];
			ESP.HighlightVisible = e[xorstr("HighlightVisible")];
			ESP.IgnoreDead = e[xorstr("IgnoreDead")];
			ESP.DistanceFromMe = e[xorstr("DistanceFromMe")];
			ESP.AdminList = ReadOpt(e, xorstr("AdminList"), false);
			ESP.AdminHighlight = ReadOpt(e, xorstr("AdminHighlight"), false);
			ESP.InvisiblePlayerWarning = ReadOpt(e, xorstr("InvisiblePlayerWarning"), false);
			ESP.DistanceFromMeState = e[xorstr("DistanceFromMeState")];
			ESP.MaxDistance = e[xorstr("MaxDistance")];
			ESP.TextSize = ReadOpt(e, xorstr("TextSize"), 1.0f);
			ESP.ShowLocalPlayer = e[xorstr("ShowLocalPlayer")];
			ESP.DistanceCol = ReadCol(e, xorstr("DistanceCol"), ImColor(230, 230, 230, 255));
			ESP.ChinaHatCol = ReadCol(e, xorstr("ChinaHatCol"), ImColor(230, 230, 230, 255));
			ESP.UserNamesCol = ReadCol(e, xorstr("UserNamesCol"), ImColor(230, 230, 230, 255));
			ESP.WeaponNameCol = ReadCol(e, xorstr("WeaponNameCol"), ImColor(230, 230, 230, 255));
			ESP.SkeletonCol = ReadCol(e, xorstr("SkeletonCol"), ImColor(255, 255, 255, 200));
			ESP.InvisibleFilterColor = ReadCol(e, xorstr("InvisibleFilterColor"), ImColor(255, 0, 0, 255));
			ESP.AdminHighlightCol = ReadCol(e, xorstr("AdminHighlightCol"), ImColor(255, 0, 0, 255));
			ESP.BoxCol = ReadCol(e, xorstr("BoxCol"), ImColor(255, 255, 255, 200));
			ESP.FilledBoxCol = ReadCol(e, xorstr("FilledBoxCol"), ImColor(0, 0, 0, 40));
			ESP.SnapLinesCol = ReadCol(e, xorstr("SnapLinesCol"), ImColor(255, 255, 255, 200));
			ESP.FriendCol = ReadCol(e, xorstr("FriendCol"), ImColor(255, 204, 0, 255));
		}

		void SerializeVehicleESP(nlohmann::json& j) {
			auto& v = j[xorstr("VehicleESP")];
			WriteOpt(v, xorstr("Enabled"), VehicleESP.Enabled);
			WriteOpt(v, xorstr("SnapLines"), VehicleESP.SnapLines);
			WriteOpt(v, xorstr("ShowLockUnlock"), VehicleESP.ShowLockUnlock);
			WriteOpt(v, xorstr("VehName"), VehicleESP.VehName);
			WriteOpt(v, xorstr("DistanceFromMe"), VehicleESP.DistanceFromMe);
			WriteOpt(v, xorstr("MaxDistance"), VehicleESP.MaxDistance);
			WriteCol(v, xorstr("SnapLinesCol"), VehicleESP.SnapLinesCol);
		}

		void DeserializeVehicleESP(const nlohmann::json& j) {
			auto& v = j[xorstr("VehicleESP")];
			VehicleESP.Enabled = v[xorstr("Enabled")];
			VehicleESP.SnapLines = v[xorstr("SnapLines")];
			VehicleESP.ShowLockUnlock = v[xorstr("ShowLockUnlock")];
			VehicleESP.VehName = v[xorstr("VehName")];
			VehicleESP.DistanceFromMe = v[xorstr("DistanceFromMe")];
			VehicleESP.MaxDistance = v[xorstr("MaxDistance")];
			VehicleESP.SnapLinesCol = ReadCol(v, xorstr("SnapLinesCol"), ImColor(255, 255, 255, 200));
		}

		void SerializePlayer(nlohmann::json& j) {
			auto& p = j[xorstr("Player")];
			WriteOpt(p, xorstr("NoClipKey"), Player.NoClipKey);
			WriteOpt(p, xorstr("NoClipSpeed"), Player.NoClipSpeed);
			WriteOpt(p, xorstr("GodModeKey"), Player.GodModeKey);
			WriteOpt(p, xorstr("SuperJump"), Player.SuperJump);
			WriteOpt(p, xorstr("BeastJump"), Player.BeastJump);
			WriteOpt(p, xorstr("WeaponSizeEnabled"), Player.WeaponSizeEnabled);
			WriteOpt(p, xorstr("WeaponSize"), Player.WeaponSize);
			WriteOpt(p, xorstr("ParaDeVenderEssaMerda"), Player.ParaDeVenderEssaMerda);
			WriteOpt(p, xorstr("ParaDeVenderEssaMerdaKey"), Player.ParaDeVenderEssaMerdaKey);
			WriteOpt(p, xorstr("FastRun"), Player.FastRun);
			WriteOpt(p, xorstr("RunSpeed"), Player.RunSpeed);
			WriteOpt(p, xorstr("InfiniteStamina"), Player.InfiniteStamina);
			WriteOpt(p, xorstr("WeaponOptions"), Player.WeaponOptions);
			WriteOpt(p, xorstr("NoRecoilEnabled"), Player.NoRecoilEnabled);
			WriteOpt(p, xorstr("RecoilValue"), Player.RecoilValue);
			WriteOpt(p, xorstr("NoSpreadEnabled"), Player.NoSpreadEnabled);
			WriteOpt(p, xorstr("SpreadValue"), Player.SpreadValue);
			WriteOpt(p, xorstr("InfiniteAmmoEnabled"), Player.InfiniteAmmoEnabled);
			WriteOpt(p, xorstr("NoReloadEnabled"), Player.NoReloadEnabled);
			WriteOpt(p, xorstr("NoClipEnabled"), Player.NoClipEnabled);
			WriteOpt(p, xorstr("NoClipMode"), Player.NoClipMode);
			WriteOpt(p, xorstr("NoClipHoldMode"), Player.NoClipHoldMode);
			WriteOpt(p, xorstr("HandlingEditor"), Player.HandlingEditor);
			WriteOpt(p, xorstr("InfiniteCombatRoll"), Player.InfiniteCombatRoll);
			WriteOpt(p, xorstr("EnableGodMode"), Player.EnableGodMode);
			WriteOpt(p, xorstr("VehicleGodMode"), Player.VehicleGodMode);
			WriteOpt(p, xorstr("SeatBelt"), Player.SeatBelt);
			WriteOpt(p, xorstr("JumpingCar"), Player.JumpingCar);
			WriteOpt(p, xorstr("CarPlaning"), Player.CarPlaning);
			WriteOpt(p, xorstr("RocketBoost"), Player.RocketBoost);
			WriteOpt(p, xorstr("BuzinaBoost"), Player.BuzinaBoost);
			WriteOpt(p, xorstr("BuzinaBoostKey"), Player.BuzinaBoostKey);
			WriteOpt(p, xorstr("BuzinaBoostSpeed"), Player.BuzinaBoostSpeed);
			WriteOpt(p, xorstr("PsychicGun"), Player.PsychicGun);
			WriteOpt(p, xorstr("HornBoostPower"), Player.HornBoostPower);
			WriteOpt(p, xorstr("FreecamEnabled"), Player.FreecamEnabled);
			WriteOpt(p, xorstr("FreecamKey"), Player.FreecamKey);
			WriteOpt(p, xorstr("FreecamSpeed"), Player.FreecamSpeed);
			WriteOpt(p, xorstr("RocketBoostBind"), Player.RocketBoostBind);
			WriteOpt(p, xorstr("SpeedHack"), Player.SpeedHack);
			WriteOpt(p, xorstr("SpeedHackBind"), Player.SpeedHackBind);
			WriteOpt(p, xorstr("SpeedHackSpeed"), Player.SpeedHackSpeed);
			WriteOpt(p, xorstr("FixVehicle"), Player.FixVehicle);
			WriteOpt(p, xorstr("FixVehicleBind"), Player.FixVehicleBind);
			WriteOpt(p, xorstr("RainVehiclesBind"), Player.RainVehiclesBind);
			WriteOpt(p, xorstr("ModifyHandling"), Player.ModifyHandling);
			WriteOpt(p, xorstr("Acceleration"), Player.Acceleration);
			WriteOpt(p, xorstr("BreakForce"), Player.BreakForce);
			WriteOpt(p, xorstr("TractionCurveMin"), Player.TractionCurveMin);
			WriteOpt(p, xorstr("CollisionDamage"), Player.CollisionDamage);
			WriteOpt(p, xorstr("TpToWayPoint"), Player.TpToWayPoint);
			WriteOpt(p, xorstr("TpToWayPointBind"), Player.TpToWayPointBind);
			WriteOpt(p, xorstr("ForceWeaponWheel"), Player.ForceWeaponWheel);
			WriteOpt(p, xorstr("SuperFist"), Player.SuperFist);
			WriteOpt(p, xorstr("ExplosiveFist"), Player.ExplosiveFist);
			WriteOpt(p, xorstr("DoubleShot"), Player.DoubleShot);
			WriteOpt(p, xorstr("FireAmmo"), Player.FireAmmo);
			WriteOpt(p, xorstr("ShrinkEnabled"), Player.ShrinkEnabled);
			WriteOpt(p, xorstr("NoRagDollEnabled"), Player.NoRagDollEnabled);
			WriteOpt(p, xorstr("AntiHSEnabled"), Player.AntiHSEnabled);
			WriteOpt(p, xorstr("StealCarEnabled"), Player.StealCarEnabled);
			WriteOpt(p, xorstr("UnlockAllActions"), Player.UnlockAllActions);
			WriteOpt(p, xorstr("WeatherControlEnabled"), Player.WeatherControlEnabled);
			WriteOpt(p, xorstr("SelectedWeather"), Player.SelectedWeather);
			WriteOpt(p, xorstr("SoloSessionEnabled"), Player.SoloSessionEnabled);
			WriteOpt(p, xorstr("InvisibleLocal"), Player.InvisibleLocal);
			WriteOpt(p, xorstr("SpinbotEnabled"), Player.SpinbotEnabled);
			WriteOpt(p, xorstr("SpinbotSpeed"), Player.SpinbotSpeed);
			WriteOpt(p, xorstr("CombatGlitch"), Player.CombatGlitch);
		}

		void DeserializePlayer(const nlohmann::json& j) {
			auto& p = j[xorstr("Player")];
			Player.NoClipKey = ReadOpt(p, xorstr("NoClipKey"), 0);
			Player.NoClipSpeed = ReadOpt(p, xorstr("NoClipSpeed"), 1.0f);
			Player.GodModeKey = ReadOpt(p, xorstr("GodModeKey"), 0);
			Player.SuperJump = ReadOpt(p, xorstr("SuperJump"), false);
			Player.BeastJump = ReadOpt(p, xorstr("BeastJump"), false);
			Player.WeaponSizeEnabled = ReadOpt(p, xorstr("WeaponSizeEnabled"), false);
			Player.WeaponSize = ReadOpt(p, xorstr("WeaponSize"), 1.0f);
			Player.ParaDeVenderEssaMerda = ReadOpt(p, xorstr("ParaDeVenderEssaMerda"), false);
			Player.ParaDeVenderEssaMerdaKey = ReadOpt(p, xorstr("ParaDeVenderEssaMerdaKey"), 0);
			Player.FastRun = ReadOpt(p, xorstr("FastRun"), false);
			Player.RunSpeed = ReadOpt(p, xorstr("RunSpeed"), 1.f);
			Player.InfiniteStamina = ReadOpt(p, xorstr("InfiniteStamina"), false);
			Player.WeaponOptions = ReadOpt(p, xorstr("WeaponOptions"), false);
			Player.NoRecoilEnabled = ReadOpt(p, xorstr("NoRecoilEnabled"), false);
			Player.RecoilValue = ReadOpt(p, xorstr("RecoilValue"), 0.f);
			Player.NoSpreadEnabled = ReadOpt(p, xorstr("NoSpreadEnabled"), false);
			Player.SpreadValue = ReadOpt(p, xorstr("SpreadValue"), 0.f);
			Player.InfiniteAmmoEnabled = ReadOpt(p, xorstr("InfiniteAmmoEnabled"), false);
			Player.NoReloadEnabled = ReadOpt(p, xorstr("NoReloadEnabled"), false);
			Player.NoClipEnabled = ReadOpt(p, xorstr("NoClipEnabled"), false);
			Player.NoClipMode = ReadOpt(p, xorstr("NoClipMode"), 0);
			Player.NoClipHoldMode = ReadOpt(p, xorstr("NoClipHoldMode"), false);
			Player.HandlingEditor = ReadOpt(p, xorstr("HandlingEditor"), false);
			Player.InfiniteCombatRoll = ReadOpt(p, xorstr("InfiniteCombatRoll"), false);
			Player.EnableGodMode = ReadOpt(p, xorstr("EnableGodMode"), false);
			Player.VehicleGodMode = ReadOpt(p, xorstr("VehicleGodMode"), false);
			Player.SeatBelt = ReadOpt(p, xorstr("SeatBelt"), false);
			Player.JumpingCar = ReadOpt(p, xorstr("JumpingCar"), false);
			Player.CarPlaning = ReadOpt(p, xorstr("CarPlaning"), false);
			Player.RocketBoost = ReadOpt(p, xorstr("RocketBoost"), false);
			Player.BuzinaBoost = ReadOpt(p, xorstr("BuzinaBoost"), false);
			Player.BuzinaBoostKey = ReadOpt(p, xorstr("BuzinaBoostKey"), 0x45);
			Player.BuzinaBoostSpeed = ReadOpt(p, xorstr("BuzinaBoostSpeed"), 30.0f);
			Player.PsychicGun = ReadOpt(p, xorstr("PsychicGun"), false);
			Player.HornBoostPower = ReadOpt(p, xorstr("HornBoostPower"), 30.0f);
			Player.FreecamEnabled = ReadOpt(p, xorstr("FreecamEnabled"), false);
			Player.FreecamKey = ReadOpt(p, xorstr("FreecamKey"), 0);
			Player.FreecamSpeed = ReadOpt(p, xorstr("FreecamSpeed"), 1.0f);
			Player.RocketBoostBind = ReadOpt(p, xorstr("RocketBoostBind"), 0);
			Player.SpeedHack = ReadOpt(p, xorstr("SpeedHack"), false);
			Player.SpeedHackBind = ReadOpt(p, xorstr("SpeedHackBind"), 0);
			Player.SpeedHackSpeed = ReadOpt(p, xorstr("SpeedHackSpeed"), 0.f);
			Player.FixVehicle = ReadOpt(p, xorstr("FixVehicle"), false);
			Player.FixVehicleBind = ReadOpt(p, xorstr("FixVehicleBind"), 0);
			Player.RainVehiclesBind = ReadOpt(p, xorstr("RainVehiclesBind"), 0);
			Player.ModifyHandling = ReadOpt(p, xorstr("ModifyHandling"), false);
			Player.Acceleration = ReadOpt(p, xorstr("Acceleration"), 0.f);
			Player.BreakForce = ReadOpt(p, xorstr("BreakForce"), 0.f);
			Player.TractionCurveMin = ReadOpt(p, xorstr("TractionCurveMin"), 0.f);
			Player.CollisionDamage = ReadOpt(p, xorstr("CollisionDamage"), 0.f);
			Player.TpToWayPoint = ReadOpt(p, xorstr("TpToWayPoint"), false);
			Player.TpToWayPointBind = ReadOpt(p, xorstr("TpToWayPointBind"), 0);
			Player.ForceWeaponWheel = ReadOpt(p, xorstr("ForceWeaponWheel"), false);
			Player.SuperFist = ReadOpt(p, xorstr("SuperFist"), false);
			Player.ExplosiveFist = ReadOpt(p, xorstr("ExplosiveFist"), false);
			Player.DoubleShot = ReadOpt(p, xorstr("DoubleShot"), false);
			Player.FireAmmo = ReadOpt(p, xorstr("FireAmmo"), false);
			Player.ShrinkEnabled = ReadOpt(p, xorstr("ShrinkEnabled"), false);
			Player.NoRagDollEnabled = ReadOpt(p, xorstr("NoRagDollEnabled"), false);
			Player.AntiHSEnabled = ReadOpt(p, xorstr("AntiHSEnabled"), false);
			Player.StealCarEnabled = ReadOpt(p, xorstr("StealCarEnabled"), false);
			Player.UnlockAllActions = ReadOpt(p, xorstr("UnlockAllActions"), false);
			Player.WeatherControlEnabled = ReadOpt(p, xorstr("WeatherControlEnabled"), false);
			Player.SelectedWeather = ReadOpt(p, xorstr("SelectedWeather"), 0);
			Player.SoloSessionEnabled = ReadOpt(p, xorstr("SoloSessionEnabled"), false);
			Player.InvisibleLocal = ReadOpt(p, xorstr("InvisibleLocal"), false);
			Player.SpinbotEnabled = ReadOpt(p, xorstr("SpinbotEnabled"), false);
			Player.SpinbotSpeed = ReadOpt(p, xorstr("SpinbotSpeed"), 100.0f);
			Player.CombatGlitch = ReadOpt(p, xorstr("CombatGlitch"), false);
		}

		void SerializeMiscESP(nlohmann::json& j) {
			auto& m = j[xorstr("MiscESP")];
			WriteOpt(m, xorstr("MinecraftFont"), MiscESP.MinecraftFont);
			WriteOpt(m, xorstr("HyperXFont"), MiscESP.HyperXFont);
			WriteOpt(m, xorstr("VegasFont"), MiscESP.VegasFont);
			WriteOpt(m, xorstr("FeatureList"), MiscESP.FeatureList);
		}

		void DeserializeMiscESP(const nlohmann::json& j) {
			auto& m = j[xorstr("MiscESP")];
			MiscESP.MinecraftFont = ReadOpt(m, xorstr("MinecraftFont"), false);
			MiscESP.HyperXFont = ReadOpt(m, xorstr("HyperXFont"), false);
			MiscESP.VegasFont = ReadOpt(m, xorstr("VegasFont"), false);
			MiscESP.FeatureList = ReadOpt(m, xorstr("FeatureList"), false);
		}

	public:
		static nlohmann::json ImColToJsonPublic(const ImColor& Col) {
			return nlohmann::json::array({ Col.Value.x, Col.Value.y, Col.Value.z, Col.Value.w });
		}

		static ImColor JsonToImColPublic(const nlohmann::json& JsonCol) {
			if (JsonCol.is_array() && JsonCol.size() == 4)
				return ImColor(static_cast<float>(JsonCol[0]), static_cast<float>(JsonCol[1]), static_cast<float>(JsonCol[2]), static_cast<float>(JsonCol[3]));
			return ImColor(0.0f, 0.0f, 0.0f, 1.0f);
		}

		std::string GetConfigDirectory() {
			std::string path = "C:\\HyperX\\Configs\\";
			std::error_code ec;
			if (!std::filesystem::exists(path, ec))
				std::filesystem::create_directories(path, ec);
			return path;
		}

		std::vector<std::string> GetConfigs() {
			std::vector<std::string> configs;
			try {
				std::string path = GetConfigDirectory();
				for (const auto& entry : std::filesystem::directory_iterator(path)) {
					if (entry.path().extension() == ".json")
						configs.push_back(entry.path().stem().string());
				}
			}
			catch (const std::exception&) {}
			return configs;
		}

		std::string DeleteConfig(std::string CfgName) {
			try {
				std::string path = GetConfigDirectory() + CfgName + ".json";
				std::error_code ec;
				if (std::filesystem::exists(path, ec)) {
					std::filesystem::remove(path, ec);
					return xorstr("Config Deleted.");
				}
				return xorstr("Config not found.");
			}
			catch (const std::exception&) {
				return xorstr("Error deleting config.");
			}
		}

		std::string SaveCurrentConfig(std::string CfgName) {
			try {
				nlohmann::json CfgJson;
				SerializeGeneral(CfgJson);
				SerializeAimbot(CfgJson);
				SerializeTriggerBot(CfgJson);
				SerializeSilentAim(CfgJson);
				SerializeESP(CfgJson);
				SerializeVehicleESP(CfgJson);
				SerializePlayer(CfgJson);
				SerializeMiscESP(CfgJson);

				std::ofstream file(GetConfigDirectory() + CfgName + ".json");
				if (file.is_open()) {
					file << CfgJson.dump(4);
					file.close();
					return xorstr("Config Saved to Disk.");
				}
				return xorstr("Failed to save config.");
			}
			catch (const std::exception&) {
				return xorstr("Failed to save config.");
			}
		}

		std::string LoadCurrentConfig(std::string CfgName) {
			try {
				std::ifstream file(GetConfigDirectory() + CfgName + ".json");
				if (!file.is_open())
					return xorstr("Config not found.");
				std::stringstream buffer;
				buffer << file.rdbuf();
				file.close();
				return LoadCfg(CfgName, buffer.str());
			}
			catch (const std::exception&) {
				return xorstr("Error reading config file.");
			}
		}

		void SerializeGeneral(nlohmann::json& j) {
			auto& g = j[xorstr("General")];
			WriteOpt(g, xorstr("StreamProof"), General.StreamProof);
			WriteOpt(g, xorstr("WaterMark"), General.WaterMark);
			WriteOpt(g, xorstr("ArrayList"), General.ArrayList);
			WriteOpt(g, xorstr("VSync"), General.VSync);
			WriteOpt(g, xorstr("SecondMonitor"), General.SecondMonitor);
			WriteOpt(g, xorstr("ProcessPriority"), General.ProcessPriority);
			WriteOpt(g, xorstr("MenuKey"), General.MenuKey);
		}

		void DeserializeGeneral(const nlohmann::json& j) {
			auto& g = j[xorstr("General")];
			if (!g.is_null()) {
				General.StreamProof = g[xorstr("StreamProof")];
				General.WaterMark = g[xorstr("WaterMark")];
				General.ArrayList = g[xorstr("ArrayList")];
				General.VSync = g[xorstr("VSync")];
				General.SecondMonitor = g[xorstr("SecondMonitor")];
				General.ProcessPriority = g[xorstr("ProcessPriority")];
				General.MenuKey = g[xorstr("MenuKey")];
			}
		}

		std::string LoadCfg(std::string CfgName, std::string CfgCode) {
			try {
				nlohmann::json CfgJson = nlohmann::json::parse(CfgCode);
				DeserializeGeneral(CfgJson);
				DeserializeAimbot(CfgJson);
				DeserializeTriggerBot(CfgJson);
				DeserializeSilentAim(CfgJson);
				DeserializeESP(CfgJson);
				DeserializeVehicleESP(CfgJson);
				DeserializePlayer(CfgJson);
				DeserializeMiscESP(CfgJson);
				ESP.UpdateCfgESP = true;
				return xorstr("Config loaded with success.");
			}
			catch (const std::exception&) {
				return xorstr("Error Loading Config!");
			}
		}
	};

	inline Config g_Config;

}
