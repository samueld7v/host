#pragma once

#pragma region Enums
#pragma region Enums
enum BoneMasks : int { SKEL_ROOT = 0x0, SKEL_Pelvis = 0x2e28, SKEL_L_Thigh = 0xe39f, SKEL_L_Calf = 0xf9bb, SKEL_L_Foot = 0x3779, SKEL_L_Toe0 = 0x83c, IK_L_Foot = 0xfedd, PH_L_Foot = 0xe175, MH_L_Knee = 0xb3fe, SKEL_R_Thigh = 0xca72, SKEL_R_Calf = 0x9000, SKEL_R_Foot = 0xcc4d, SKEL_R_Toe0 = 0x512d, IK_R_Foot = 0x8aae, PH_R_Foot = 0x60e6, MH_R_Knee = 0x3fcf, RB_L_ThighRoll = 0x5c57, RB_R_ThighRoll = 0x192a, SKEL_Spine_Root = 0xe0fd, SKEL_Spine0 = 0x5c01, SKEL_Spine1 = 0x60f0, SKEL_Spine2 = 0x60f1, SKEL_Spine3 = 0x60f2, SKEL_L_Clavicle = 0xfcd9, SKEL_L_UpperArm = 0xb1c5, SKEL_L_Forearm = 0xeeeb, SKEL_L_Hand = 0x49d9, SKEL_L_Finger00 = 0x67f2, SKEL_L_Finger01 = 0xff9, SKEL_L_Finger02 = 0xffa, SKEL_L_Finger10 = 0x67f3, SKEL_L_Finger11 = 0x1049, SKEL_L_Finger12 = 0x104a, SKEL_L_Finger20 = 0x67f4, SKEL_L_Finger21 = 0x1059, SKEL_L_Finger22 = 0x105a, SKEL_L_Finger30 = 0x67f5, SKEL_L_Finger31 = 0x1029, SKEL_L_Finger32 = 0x102a, SKEL_L_Finger40 = 0x67f6, SKEL_L_Finger41 = 0x1039, SKEL_L_Finger42 = 0x103a, PH_L_Hand = 0xeb95, IK_L_Hand = 0x8cbd, RB_L_ForeArmRoll = 0xee4f, RB_L_ArmRoll = 0x1470, MH_L_Elbow = 0x58b7, SKEL_R_Clavicle = 0x29d2, SKEL_R_UpperArm = 0x9d4d, SKEL_R_Forearm = 0x6e5c, SKEL_R_Hand = 0xdead, SKEL_R_Finger00 = 0xe5f2, SKEL_R_Finger01 = 0xfa10, SKEL_R_Finger02 = 0xfa11, SKEL_R_Finger10 = 0xe5f3, SKEL_R_Finger11 = 0xfa60, SKEL_R_Finger12 = 0xfa61, SKEL_R_Finger20 = 0xe5f4, SKEL_R_Finger21 = 0xfa70, SKEL_R_Finger22 = 0xfa71, SKEL_R_Finger30 = 0xe5f5, SKEL_R_Finger31 = 0xfa40, SKEL_R_Finger32 = 0xfa41, SKEL_R_Finger40 = 0xe5f6, SKEL_R_Finger41 = 0xfa50, SKEL_R_Finger42 = 0xfa51, PH_R_Hand = 0x6f06, IK_R_Hand = 0x188e, RB_R_ForeArmRoll = 0xab22, RB_R_ArmRoll = 0x90ff, MH_R_Elbow = 0xbb0, SKEL_Neck_1 = 0x9995, SKEL_Head = 0x796e, IK_Head = 0x322c, FACIAL_facialRoot = 0xfe2c, FB_L_Brow_Out_000 = 0xe3db, FB_L_Lid_Upper_000 = 0xb2b6, FB_L_Eye_000 = 0x62ac, FB_L_CheekBone_000 = 0x542e, FB_L_Lip_Corner_000 = 0x74ac, FB_R_Lid_Upper_000 = 0xaa10, FB_R_Eye_000 = 0x6b52, FB_R_CheekBone_000 = 0x4b88, FB_R_Brow_Out_000 = 0x54c, FB_R_Lip_Corner_000 = 0x2ba6, FB_Brow_Centre_000 = 0x9149, FB_UpperLipRoot_000 = 0x4ed2, FB_UpperLip_000 = 0xf18f, FB_L_Lip_Top_000 = 0x4f37, FB_R_Lip_Top_000 = 0x4537, FB_Jaw_000 = 0xb4a0, FB_LowerLipRoot_000 = 0x4324, FB_LowerLip_000 = 0x508f, FB_L_Lip_Bot_000 = 0xb93b, FB_R_Lip_Bot_000 = 0xc33b, FB_Tongue_000 = 0xb987, RB_Neck_1 = 0x8b93, IK_Root = 0xdd1c };
//enum ePedConfigFlag { NoCriticalHits = 2, DrownsInWater = 3, DisableReticuleFixedLockon = 4, UpperBodyDamageAnimsOnly = 7, NeverLeavesGroup = 13, BlockNonTemporaryEvents = 17, CanPunch = 18, IgnoreSeenMelee = 24, GetOutUndriveableVehicle = 29, CanFlyThruWindscreen = 32, DiesWhenRagdoll = 33, HasHelmet = 34, PutOnMotorcycleHelmet = 35, DontTakeOffHelmet = 36, DisableEvasiveDives = 39, DontInfluenceWantedLevel = 42, DisablePlayerLockon = 43, DisableLockonToRandomPeds = 44, AllowLockonToFriendlyPlayers = 45, BeingDeleted = 47, BlockWeaponSwitching = 48, NoCollision = 52, IsShooting = 58, WasShooting = 59, IsOnGround = 60, WasOnGround = 61, InVehicle = 62, OnMount = 63, AttachedToVehicle = 64, IsSwimming = 65, WasSwimming = 66, IsSkiing = 67, IsSitting = 68, KilledByStealth = 69, KilledByTakedown = 70, Knockedout = 71, IsSniperScopeActive = 72, SuperDead = 73, UsingCoverPoint = 75, IsInTheAir = 76, IsAimingGun = 78, ForcePedLoadCover = 93, VaultFromCover = 97, IsDrunk = 100, ForcedAim = 101, IsNotRagdollAndNotPlayingAnim = 104, ForceReload = 105, DontActivateRagdollFromVehicleImpact = 106, DontActivateRagdollFromBulletImpact = 107, DontActivateRagdollFromExplosions = 108, DontActivateRagdollFromFire = 109, DontActivateRagdollFromElectrocution = 110, KeepWeaponHolsteredUnlessFired = 113, GetOutBurningVehicle = 116, BumpedByPlayer = 117, RunFromFiresAndExplosions = 118, TreatAsPlayerDuringTargeting = 119, IsHandCuffed = 120, IsAnkleCuffed = 121, DisableMelee = 122, DisableUnarmedDrivebys = 123, JustGetsPulledOutWhenElectrocuted = 124, NmMessage466 = 125, WillNotHotwireLawEnforcementVehicle = 126, WillCommandeerRatherThanJack = 127, CanBeAgitated = 128, ForcePedToFaceLeftInCover = 129, ForcePedToFaceRightInCover = 130, BlockPedFromTurningInCover = 131, KeepRelationshipGroupAfterCleanUp = 132, ForcePedToBeDragged = 133, PreventPedFromReactingToBeingJacked = 134, IsScuba = 135, WillArrestRatherThanJack = 136, RemoveDeadExtraFarAway = 137, RidingTrain = 138, ArrestResult = 139, CanAttackFriendly = 140, WillJackAnyPlayer = 141, WillJackWantedPlayersRatherThanStealCar = 144, ShootingAnimFlag = 145, DisableLadderClimbing = 146, StairsDetected = 147, SlopeDetected = 148, CowerInsteadOfFlee = 150, CanActivateRagdollWhenVehicleUpsideDown = 151, AlwaysRespondToCriesForHelp = 152, DisableBloodPoolCreation = 153, ShouldFixIfNoCollision = 154, CanPerformArrest = 155, CanPerformUncuff = 156, CanBeArrested = 157, PlayerPreferFrontSeatMP = 159, IsInjured = 166, DontEnterVehiclesInPlayersGroup = 167, PreventAllMeleeTaunts = 169, IsInjured2 = 170, AlwaysSeeApproachingVehicles = 171, CanDiveAwayFromApproachingVehicles = 172, AllowPlayerToInterruptVehicleEntryExit = 173, OnlyAttackLawIfPlayerIsWanted = 174, PedsJackingMeDontGetIn = 177, PedIgnoresAnimInterruptEvents = 179, IsInCustody = 180, ForceStandardBumpReactionThresholds = 181, LawWillOnlyAttackIfPlayerIsWanted = 182, IsAgitated = 183, PreventAutoShuffleToDriversSeat = 184, UseKinematicModeWhenStationary = 185, EnableWeaponBlocking = 186, HasHurtStarted = 187, DisableHurt = 188, PlayerIsWeird = 189, DoNothingWhenOnFootByDefault = 193, UsingScenario = 194, VisibleOnScreen = 195, DontActivateRagdollOnVehicleCollisionWhenDead = 199, HasBeenInArmedCombat = 200, AvoidanceIgnoreAll = 202, AvoidanceIgnoredByAll = 203, AvoidanceIgnoreGroup1 = 204, AvoidanceMemberOfGroup1 = 205, ForcedToUseSpecificGroupSeatIndex = 206, DisableExplosionReactions = 208, DodgedPlayer = 209, WaitingForPlayerControlInterrupt = 210, ForcedToStayInCover = 211, GeneratesSoundEvents = 212, ListensToSoundEvents = 213, AllowToBeTargetedInAVehicle = 214, WaitForDirectEntryPointToBeFreeWhenExiting = 215, OnlyRequireOnePressToExitVehicle = 216, ForceExitToSkyDive = 217, DontEnterLeadersVehicle = 220, DisableExitToSkyDive = 221, Shrink = 223, MeleeCombat = 224, DisablePotentialToBeWalkedIntoResponse = 225, DisablePedAvoidance = 226, ForceRagdollUponDeath = 227, DisablePanicInVehicle = 229, AllowedToDetachTrailer = 230, IsHoldingProp = 236, BlocksPathingWhenDead = 237, ForceSkinCharacterCloth = 240, DisableStoppingVehicleEngine = 241, PhoneDisableTextingAnimations = 242, PhoneDisableTalkingAnimations = 243, PhoneDisableCameraAnimations = 244, DisableBlindFiringInShotReactions = 245, AllowNearbyCoverUsage = 246, CanPlayInCarIdles = 248, CanAttackNonWantedPlayerAsLaw = 249, WillTakeDamageWhenVehicleCrashes = 250, AICanDrivePlayerAsRearPassenger = 251, PlayerCanJackFriendlyPlayers = 252, IsOnStairs = 253, AIDriverAllowFriendlyPassengerSeatEntry = 255, AllowMissionPedToUseInjuredMovement = 257, PreventUsingLowerPrioritySeats = 261, DisableClosingVehicleDoor = 264, TeleportToLeaderVehicle = 268, AvoidanceIgnoreWeirdPedBuffer = 269, OnStairSlope = 270, DontBlipCop = 272, ClimbedShiftedFence = 273, KillWhenTrapped = 275, EdgeDetected = 276, AvoidTearGas = 279, NoWrithe = 281, OnlyUseForcedSeatWhenEnteringHeliInGroup = 282, DisableWeirdPedEvents = 285, ShouldChargeNow = 286, RagdollingOnBoat = 287, HasBrandishedWeapon = 288, FreezePosition = 292, DisableShockingEvents = 294, NeverReactToPedOnRoof = 296, DisableShockingDrivingOnPavementEvents = 299, DisablePedConstraints = 301, ForceInitialPeekInCover = 302, DisableJumpingFromVehiclesAfterLeader = 305, IsInCluster = 310, ShoutToGroupOnPlayerMelee = 311, IgnoredByAutoOpenDoors = 312, NoPedMelee = 314, CheckLoSForSoundEvents = 315, CanSayFollowedByPlayerAudio = 317, ActivateRagdollFromMinorPlayerContact = 318, ForcePoseCharacterCloth = 320, HasClothCollisionBounds = 321, HasHighHeels = 322, DontBehaveLikeLaw = 324, DisablePoliceInvestigatingBody = 326, DisableWritheShootFromGround = 327, LowerPriorityOfWarpSeats = 328, DisableTalkTo = 329, DontBlip = 330, IsSwitchingWeapon = 331, IgnoreLegIkRestrictions = 332, AllowTaskDoNothingTimeslicing = 339, NotAllowedToJackAnyPlayers = 342, AlwaysLeaveTrainUponArrival = 345, OnlyWritheFromWeaponDamage = 347, UseSloMoBloodVfx = 348, EquipJetpack = 349, PreventDraggedOutOfCarThreatResponse = 350, ForceDeepSurfaceCheck = 356, DisableDeepSurfaceAnims = 357, DontBlipNotSynced = 358, IsDuckingInVehicle = 359, PreventAutoShuffleToTurretSeat = 360, DisableEventInteriorStatusCheck = 361, HasReserveParachute = 362, UseReserveParachute = 363, TreatDislikeAsHateWhenInCombat = 364, OnlyUpdateTargetWantedIfSeen = 365, AllowAutoShuffleToDriversSeat = 366, PreventReactingToSilencedCloneBullets = 372, DisableInjuredCryForHelpEvents = 373, NeverLeaveTrain = 374, DontDropJetpackOnDeath = 375, DisableAutoEquipHelmetsInBikes = 380, IsClimbingLadder = 388, HasBareFeet = 389, GoOnWithoutVehicleIfItIsUnableToGetBackToRoad = 391, BlockDroppingHealthSnacksOnDeath = 392, ForceThreatResponseToNonFriendToFriendMeleeActions = 394, DontRespondToRandomPedsDamage = 395, AllowContinuousThreatResponseWantedLevelUpdates = 396, KeepTargetLossResponseOnCleanup = 397, PlayersDontDragMeOutOfCar = 398, BroadcastRepondedToThreatWhenGoingToPointShooting = 399, IgnorePedTypeForIsFriendlyWith = 400, TreatNonFriendlyAsHateWhenInCombat = 401, DontLeaveVehicleIfLeaderNotInVehicle = 402, AllowMeleeReactionIfMeleeProofIsOn = 404, UseNormalExplosionDamageWhenBlownUpInVehicle = 407, DisableHomingMissileLockForVehiclePedInside = 408, DisableTakeOffScubaGear = 409, Alpha = 410, LawPedsCanFleeFromNonWantedPlayer = 411, ForceBlipSecurityPedsIfPlayerIsWanted = 412, IsHolsteringWeapon = 413, UseGoToPointForScenarioNavigation = 414, DontClearLocalPassengersWantedLevel = 415, BlockAutoSwapOnWeaponPickups = 416, ThisPedIsATargetPriorityForAI = 417, IsSwitchingHelmetVisor = 418, ForceHelmetVisorSwitch = 419, FlamingFootprints = 421, DisableVehicleCombat = 422, DisablePropKnockOff = 423, FallsLikeAircraft = 424, UseLockpickVehicleEntryAnimations = 426, IgnoreInteriorCheckForSprinting = 427, SwatHeliSpawnWithinLastSpottedLocation = 428, DisableStartingVehicleEngine = 429, IgnoreBeingOnFire = 430, DisableTurretOrRearSeatPreference = 431, DisableWantedHelicopterSpawning = 432, UseTargetPerceptionForCreatingAimedAtEvents = 433, DisableHomingMissileLockon = 434, ForceIgnoreMaxMeleeActiveSupportCombatants = 435, StayInDefensiveAreaWhenInVehicle = 436, DontShoutTargetPosition = 437, DisableHelmetArmor = 438, PreventVehExitDueToInvalidWeapon = 441, IgnoreNetSessionFriendlyFireCheckForAllowDamage = 442, DontLeaveCombatIfTargetPlayerIsAttackedByPolice = 443, CheckLockedBeforeWarp = 444, DontShuffleInVehicleToMakeRoom = 445, GiveWeaponOnGetup = 446, DontHitVehicleWithProjectiles = 447, DisableForcedEntryForOpenVehiclesFromTryLockedDoor = 448, FiresDummyRockets = 449, IsArresting = 450, IsDecoyPed = 451, HasEstablishedDecoy = 452, BlockDispatchedHelicoptersFromLanding = 453, DontCryForHelpOnStun = 454, CanBeIncapacitated = 456, MutableForcedAim = 457, DontChangeTargetFromMelee = 458 };
enum ePedConfigFlags
{
	CPED_CONFIG_FLAG_CreatedByFactory = 0,
	CPED_CONFIG_FLAG_CanBeShotInVehicle = 1,
	CPED_CONFIG_FLAG_NoCriticalHits, // Detected by AC
	CPED_CONFIG_FLAG_DrownsInWater,
	CPED_CONFIG_FLAG_DrownsInSinkingVehicle,
	CPED_CONFIG_FLAG_DiesInstantlyWhenSwimming,
	CPED_CONFIG_FLAG_HasBulletProofVest,
	CPED_CONFIG_FLAG_UpperBodyDamageAnimsOnly,
	CPED_CONFIG_FLAG_NeverFallOffSkis,
	CPED_CONFIG_FLAG_NeverEverTargetThisPed,
	CPED_CONFIG_FLAG_ThisPedIsATargetPriority,
	CPED_CONFIG_FLAG_TargettableWithNoLos,
	CPED_CONFIG_FLAG_DoesntListenToPlayerGroupCommands,
	CPED_CONFIG_FLAG_NeverLeavesGroup,
	CPED_CONFIG_FLAG_DoesntDropWeaponsWhenDead,
	CPED_CONFIG_FLAG_SetDelayedWeaponAsCurrent,
	CPED_CONFIG_FLAG_KeepTasksAfterCleanUp,
	CPED_CONFIG_FLAG_BlockNonTemporaryEvents,
	CPED_CONFIG_FLAG_HasAScriptBrain,
	CPED_CONFIG_FLAG_WaitingForScriptBrainToLoad,
	CPED_CONFIG_FLAG_AllowMedicsToReviveMe,
	CPED_CONFIG_FLAG_MoneyHasBeenGivenByScript,
	CPED_CONFIG_FLAG_NotAllowedToCrouch,
	CPED_CONFIG_FLAG_DeathPickupsPersist,
	CPED_CONFIG_FLAG_IgnoreSeenMelee,
	CPED_CONFIG_FLAG_ForceDieIfInjured,
	CPED_CONFIG_FLAG_DontDragMeOutCar,
	CPED_CONFIG_FLAG_StayInCarOnJack,
	CPED_CONFIG_FLAG_ForceDieInCar, // prae
	CPED_CONFIG_FLAG_GetOutUndriveableVehicle,
	CPED_CONFIG_FLAG_WillRemainOnBoatAfterMissionEnds,
	CPED_CONFIG_FLAG_DontStoreAsPersistent,
	CPED_CONFIG_FLAG_WillFlyThroughWindscreen,
	CPED_CONFIG_FLAG_DieWhenRagdoll,
	CPED_CONFIG_FLAG_HasHelmet,
	CPED_CONFIG_FLAG_UseHelmet,
	CPED_CONFIG_FLAG_DontTakeOffHelmet,
	CPED_CONFIG_FLAG_HideInCutscene,
	CPED_CONFIG_FLAG_PedIsEnemyToPlayer,
	CPED_CONFIG_FLAG_DisableEvasiveDives,
	CPED_CONFIG_FLAG_PedGeneratesDeadBodyEvents,
	CPED_CONFIG_FLAG_DontAttackPlayerWithoutWantedLevel,
	CPED_CONFIG_FLAG_DontInfluenceWantedLevel,
	CPED_CONFIG_FLAG_DisablePlayerLockon,
	CPED_CONFIG_FLAG_DisableLockonToRandomPeds,
	CPED_CONFIG_FLAG_AllowLockonToFriendlyPlayers,
	CPED_CONFIG_FLAG_DisableHornAudioWhenDead,
	CPED_CONFIG_FLAG_PedBeingDeleted,
	CPED_CONFIG_FLAG_BlockWeaponSwitching,
	CPED_CONFIG_FLAG_BlockGroupPedAimedAtResponse,
	CPED_CONFIG_FLAG_WillFollowLeaderAnyMeans,
	CPED_CONFIG_FLAG_BlippedByScript,
	CPED_CONFIG_FLAG_DrawRadarVisualField,
	CPED_CONFIG_FLAG_StopWeaponFiringOnImpact,
	CPED_CONFIG_FLAG_DissableAutoFallOffTests,
	CPED_CONFIG_FLAG_SteerAroundDeadBodies,
	CPED_CONFIG_FLAG_ConstrainToNavMesh,
	CPED_CONFIG_FLAG_SyncingAnimatedProps,
	CPED_CONFIG_FLAG_IsFiring,
	CPED_CONFIG_FLAG_WasFiring,
	CPED_CONFIG_FLAG_IsStanding,
	CPED_CONFIG_FLAG_WasStanding,
	CPED_CONFIG_FLAG_IsInVehicleValue,
	CPED_CONFIG_FLAG_OnMount,
	CPED_CONFIG_FLAG_AttachedToVehicle,
	CPED_CONFIG_FLAG_IsSwimming,
	CPED_CONFIG_FLAG_WasSwimming,
	CPED_CONFIG_FLAG_IsSkiing,
	CPED_CONFIG_FLAG_IsSitting,
	CPED_CONFIG_FLAG_KilledByStealth,
	CPED_CONFIG_FLAG_KilledByTakedown,
	CPED_CONFIG_FLAG_Knockedout,
	CPED_CONFIG_FLAG_ClearRadarBlipOnDeath,
	CPED_CONFIG_FLAG_JustGotOffTrain,
	CPED_CONFIG_FLAG_JustGotOnTrain,
	CPED_CONFIG_FLAG_UsingCoverPoint,
	CPED_CONFIG_FLAG_IsInTheAir,
	CPED_CONFIG_FLAG_KnockedUpIntoAir,
	CPED_CONFIG_FLAG_IsAimingGun,
	CPED_CONFIG_FLAG_HasJustLeftCar,
	CPED_CONFIG_FLAG_TargetWhenInjuredAllowed,
	CPED_CONFIG_FLAG_CurrLeftFootCollNM,
	CPED_CONFIG_FLAG_PrevLeftFootCollNM,
	CPED_CONFIG_FLAG_CurrRightFootCollNM,
	CPED_CONFIG_FLAG_PrevRightFootCollNM,
	CPED_CONFIG_FLAG_HasBeenBumpedInCar,
	CPED_CONFIG_FLAG_InWaterTaskQuitToClimbLadder,
	CPED_CONFIG_FLAG_NMTwoHandedWeaponBothHandsConstrained,
	CPED_CONFIG_FLAG_CreatedBloodPoolTimer,
	CPED_CONFIG_FLAG_DontActivateRagdollFromAnyPedImpact,
	CPED_CONFIG_FLAG_GroupPedFailedToEnterCover,
	CPED_CONFIG_FLAG_AlreadyChattedOnPhone,
	CPED_CONFIG_FLAG_AlreadyReactedToPedOnRoof,
	CPED_CONFIG_FLAG_ForcePedLoadCover,
	CPED_CONFIG_FLAG_BlockCoweringInCover,
	CPED_CONFIG_FLAG_BlockPeekingInCover,
	CPED_CONFIG_FLAG_JustLeftCarNotCheckedForDoors,
	CPED_CONFIG_FLAG_VaultFromCover,
	CPED_CONFIG_FLAG_AutoConversationLookAts,
	CPED_CONFIG_FLAG_UsingCrouchedPedCapsule,
	CPED_CONFIG_FLAG_HasDeadPedBeenReported,
	CPED_CONFIG_FLAG_ForcedAim,
	CPED_CONFIG_FLAG_SteersAroundPeds,
	CPED_CONFIG_FLAG_SteersAroundObjects,
	CPED_CONFIG_FLAG_OpenDoorArmIK,
	CPED_CONFIG_FLAG_ForceReload,
	CPED_CONFIG_FLAG_DontActivateRagdollFromVehicleImpact,
	CPED_CONFIG_FLAG_DontActivateRagdollFromBulletImpact,
	CPED_CONFIG_FLAG_DontActivateRagdollFromExplosions,
	CPED_CONFIG_FLAG_DontActivateRagdollFromFire,
	CPED_CONFIG_FLAG_DontActivateRagdollFromElectrocution,
	CPED_CONFIG_FLAG_IsBeingDraggedToSafety,
	CPED_CONFIG_FLAG_HasBeenDraggedToSafety,
	CPED_CONFIG_FLAG_KeepWeaponHolsteredUnlessFired,
	CPED_CONFIG_FLAG_ForceScriptControlledKnockout,
	CPED_CONFIG_FLAG_FallOutOfVehicleWhenKilled,
	CPED_CONFIG_FLAG_GetOutBurningVehicle,
	CPED_CONFIG_FLAG_BumpedByPlayer,
	CPED_CONFIG_FLAG_RunFromFiresAndExplosions,
	CPED_CONFIG_FLAG_TreatAsPlayerDuringTargeting,
	CPED_CONFIG_FLAG_IsHandCuffed,
	CPED_CONFIG_FLAG_IsAnkleCuffed,
	CPED_CONFIG_FLAG_DisableMelee,
	CPED_CONFIG_FLAG_DisableUnarmedDrivebys,
	CPED_CONFIG_FLAG_JustGetsPulledOutWhenElectrocuted,
	CPED_CONFIG_FLAG_UNUSED_REPLACE_ME,
	CPED_CONFIG_FLAG_WillNotHotwireLawEnforcementVehicle,
	CPED_CONFIG_FLAG_WillCommandeerRatherThanJack,
	CPED_CONFIG_FLAG_CanBeAgitated,
	CPED_CONFIG_FLAG_ForcePedToFaceLeftInCover,
	CPED_CONFIG_FLAG_ForcePedToFaceRightInCover,
	CPED_CONFIG_FLAG_BlockPedFromTurningInCover,
	CPED_CONFIG_FLAG_KeepRelationshipGroupAfterCleanUp,
	CPED_CONFIG_FLAG_ForcePedToBeDragged,
	CPED_CONFIG_FLAG_PreventPedFromReactingToBeingJacked,
	CPED_CONFIG_FLAG_IsScuba,
	CPED_CONFIG_FLAG_WillArrestRatherThanJack,
	CPED_CONFIG_FLAG_RemoveDeadExtraFarAway,
	CPED_CONFIG_FLAG_RidingTrain,
	CPED_CONFIG_FLAG_ArrestResult,
	CPED_CONFIG_FLAG_CanAttackFriendly,
	CPED_CONFIG_FLAG_WillJackAnyPlayer,
	CPED_CONFIG_FLAG_BumpedByPlayerVehicle,
	CPED_CONFIG_FLAG_DodgedPlayerVehicle,
	CPED_CONFIG_FLAG_WillJackWantedPlayersRatherThanStealCar,
	CPED_CONFIG_FLAG_NoCopWantedAggro,
	CPED_CONFIG_FLAG_DisableLadderClimbing,
	CPED_CONFIG_FLAG_StairsDetected,
	CPED_CONFIG_FLAG_SlopeDetected,
	CPED_CONFIG_FLAG_HelmetHasBeenShot,
	CPED_CONFIG_FLAG_CowerInsteadOfFlee,
	CPED_CONFIG_FLAG_CanActivateRagdollWhenVehicleUpsideDown,
	CPED_CONFIG_FLAG_AlwaysRespondToCriesForHelp,
	CPED_CONFIG_FLAG_DisableBloodPoolCreation,
	CPED_CONFIG_FLAG_ShouldFixIfNoCollision,
	CPED_CONFIG_FLAG_CanPerformArrest,
	CPED_CONFIG_FLAG_CanPerformUncuff,
	CPED_CONFIG_FLAG_CanBeArrested,
	CPED_CONFIG_FLAG_MoverConstrictedByOpposingCollisions,
	CPED_CONFIG_FLAG_PlayerPreferFrontSeatMP,
	CPED_CONFIG_FLAG_DontActivateRagdollFromImpactObject,
	CPED_CONFIG_FLAG_DontActivateRagdollFromMelee,
	CPED_CONFIG_FLAG_DontActivateRagdollFromWaterJet,
	CPED_CONFIG_FLAG_DontActivateRagdollFromDrowning,
	CPED_CONFIG_FLAG_DontActivateRagdollFromFalling,
	CPED_CONFIG_FLAG_DontActivateRagdollFromRubberBullet,
	CPED_CONFIG_FLAG_IsInjured,
	CPED_CONFIG_FLAG_DontEnterVehiclesInPlayersGroup,
	CPED_CONFIG_FLAG_SwimmingTasksRunning,
	CPED_CONFIG_FLAG_PreventAllMeleeTaunts,
	CPED_CONFIG_FLAG_ForceDirectEntry,
	CPED_CONFIG_FLAG_AlwaysSeeApproachingVehicles,
	CPED_CONFIG_FLAG_CanDiveAwayFromApproachingVehicles,
	CPED_CONFIG_FLAG_AllowPlayerToInterruptVehicleEntryExit,
	CPED_CONFIG_FLAG_OnlyAttackLawIfPlayerIsWanted,
	CPED_CONFIG_FLAG_PlayerInContactWithKinematicPed,
	CPED_CONFIG_FLAG_PlayerInContactWithSomethingOtherThanKinematicPed,
	CPED_CONFIG_FLAG_PedsJackingMeDontGetIn,
	CPED_CONFIG_FLAG_AdditionalRappellingPed,
	CPED_CONFIG_FLAG_PedIgnoresAnimInterruptEvents,
	CPED_CONFIG_FLAG_IsInCustody,
	CPED_CONFIG_FLAG_ForceStandardBumpReactionThresholds,
	CPED_CONFIG_FLAG_LawWillOnlyAttackIfPlayerIsWanted,
	CPED_CONFIG_FLAG_IsAgitated,
	CPED_CONFIG_FLAG_PreventAutoShuffleToDriversSeat,
	CPED_CONFIG_FLAG_UseKinematicModeWhenStationary,
	CPED_CONFIG_FLAG_EnableWeaponBlocking,
	CPED_CONFIG_FLAG_HasHurtStarted,
	CPED_CONFIG_FLAG_DisableHurt,
	CPED_CONFIG_FLAG_PlayerIsWeird,
	CPED_CONFIG_FLAG_PedHadPhoneConversation,
	CPED_CONFIG_FLAG_BeganCrossingRoad,
	CPED_CONFIG_FLAG_WarpIntoLeadersVehicle,
	CPED_CONFIG_FLAG_DoNothingWhenOnFootByDefault,
	CPED_CONFIG_FLAG_UsingScenario,
	CPED_CONFIG_FLAG_VisibleOnScreen,
	CPED_CONFIG_FLAG_DontCollideWithKinematic,
	CPED_CONFIG_FLAG_ActivateOnSwitchFromLowPhysicsLod,
	CPED_CONFIG_FLAG_DontActivateRagdollOnPedCollisionWhenDead,
	CPED_CONFIG_FLAG_DontActivateRagdollOnVehicleCollisionWhenDead,
	CPED_CONFIG_FLAG_HasBeenInArmedCombat,
	CPED_CONFIG_FLAG_UseDiminishingAmmoRate,
	CPED_CONFIG_FLAG_Avoidance_Ignore_All,
	CPED_CONFIG_FLAG_Avoidance_Ignored_by_All,
	CPED_CONFIG_FLAG_Avoidance_Ignore_Group1,
	CPED_CONFIG_FLAG_Avoidance_Member_of_Group1,
	CPED_CONFIG_FLAG_ForcedToUseSpecificGroupSeatIndex,
	CPED_CONFIG_FLAG_LowPhysicsLodMayPlaceOnNavMesh,
	CPED_CONFIG_FLAG_DisableExplosionReactions,
	CPED_CONFIG_FLAG_DodgedPlayer,
	CPED_CONFIG_FLAG_WaitingForPlayerControlInterrupt,
	CPED_CONFIG_FLAG_ForcedToStayInCover,
	CPED_CONFIG_FLAG_GeneratesSoundEvents,
	CPED_CONFIG_FLAG_ListensToSoundEvents,
	CPED_CONFIG_FLAG_AllowToBeTargetedInAVehicle,
	CPED_CONFIG_FLAG_WaitForDirectEntryPointToBeFreeWhenExiting,
	CPED_CONFIG_FLAG_OnlyRequireOnePressToExitVehicle,
	CPED_CONFIG_FLAG_ForceExitToSkyDive,
	CPED_CONFIG_FLAG_SteersAroundVehicles,
	CPED_CONFIG_FLAG_AllowPedInVehiclesOverrideTaskFlags,
	CPED_CONFIG_FLAG_DontEnterLeadersVehicle,
	CPED_CONFIG_FLAG_DisableExitToSkyDive,
	CPED_CONFIG_FLAG_ScriptHasDisabledCollision,
	CPED_CONFIG_FLAG_UseAmbientModelScaling,
	CPED_CONFIG_FLAG_DontWatchFirstOnNextHurryAway,
	CPED_CONFIG_FLAG_DisablePotentialToBeWalkedIntoResponse,
	CPED_CONFIG_FLAG_DisablePedAvoidance,
	CPED_CONFIG_FLAG_ForceRagdollUponDeath,
	CPED_CONFIG_FLAG_CanLosePropsOnDamage,
	CPED_CONFIG_FLAG_DisablePanicInVehicle,
	CPED_CONFIG_FLAG_AllowedToDetachTrailer,
	CPED_CONFIG_FLAG_HasShotBeenReactedToFromFront,
	CPED_CONFIG_FLAG_HasShotBeenReactedToFromBack,
	CPED_CONFIG_FLAG_HasShotBeenReactedToFromLeft,
	CPED_CONFIG_FLAG_HasShotBeenReactedToFromRight,
	CPED_CONFIG_FLAG_AllowBlockDeadPedRagdollActivation,
	CPED_CONFIG_FLAG_IsHoldingProp,
	CPED_CONFIG_FLAG_BlocksPathingWhenDead,
	CPED_CONFIG_FLAG_ForcePlayNormalScenarioExitOnNextScriptCommand,
	CPED_CONFIG_FLAG_ForcePlayImmediateScenarioExitOnNextScriptCommand,
	CPED_CONFIG_FLAG_ForceSkinCharacterCloth,
	CPED_CONFIG_FLAG_LeaveEngineOnWhenExitingVehicles,
	CPED_CONFIG_FLAG_PhoneDisableTextingAnimations,
	CPED_CONFIG_FLAG_PhoneDisableTalkingAnimations,
	CPED_CONFIG_FLAG_PhoneDisableCameraAnimations,
	CPED_CONFIG_FLAG_DisableBlindFiringInShotReactions,
	CPED_CONFIG_FLAG_AllowNearbyCoverUsage,
	CPED_CONFIG_FLAG_InStrafeTransition,
	CPED_CONFIG_FLAG_CanPlayInCarIdles,
	CPED_CONFIG_FLAG_CanAttackNonWantedPlayerAsLaw,
	CPED_CONFIG_FLAG_WillTakeDamageWhenVehicleCrashes,
	CPED_CONFIG_FLAG_AICanDrivePlayerAsRearPassenger,
	CPED_CONFIG_FLAG_PlayerCanJackFriendlyPlayers,
	CPED_CONFIG_FLAG_OnStairs,
	CPED_CONFIG_FLAG_SimulatingAiming,
	CPED_CONFIG_FLAG_AIDriverAllowFriendlyPassengerSeatEntry,
	CPED_CONFIG_FLAG_ParentCarIsBeingRemoved,
	CPED_CONFIG_FLAG_AllowMissionPedToUseInjuredMovement,
	CPED_CONFIG_FLAG_CanLoseHelmetOnDamage,
	CPED_CONFIG_FLAG_NeverDoScenarioExitProbeChecks,
	CPED_CONFIG_FLAG_SuppressLowLODRagdollSwitchWhenCorpseSettles,
	CPED_CONFIG_FLAG_PreventUsingLowerPrioritySeats,
	CPED_CONFIG_FLAG_JustLeftVehicleNeedsReset,
	CPED_CONFIG_FLAG_TeleportIfCantReachPlayer,
	CPED_CONFIG_FLAG_PedsInVehiclePositionNeedsReset,
	CPED_CONFIG_FLAG_PedsFullyInSeat,
	CPED_CONFIG_FLAG_AllowPlayerLockOnIfFriendly,
	CPED_CONFIG_FLAG_UseCameraHeadingForDesiredDirectionLockOnTest,
	CPED_CONFIG_FLAG_TeleportToLeaderVehicle,
	CPED_CONFIG_FLAG_Avoidance_Ignore_WeirdPedBuffer,
	CPED_CONFIG_FLAG_OnStairSlope,
	CPED_CONFIG_FLAG_HasPlayedNMGetup,
	CPED_CONFIG_FLAG_DontBlipCop,
	CPED_CONFIG_FLAG_SpawnedAtExtendedRangeScenario,
	CPED_CONFIG_FLAG_WalkAlongsideLeaderWhenClose,
	CPED_CONFIG_FLAG_KillWhenTrapped,
	CPED_CONFIG_FLAG_EdgeDetected,
	CPED_CONFIG_FLAG_AlwaysWakeUpPhysicsOfIntersectedPeds,
	CPED_CONFIG_FLAG_EquippedAmbientLoadOutWeapon,
	CPED_CONFIG_FLAG_AvoidTearGas,
	CPED_CONFIG_FLAG_StoppedSpeechUponFreezing,
	CPED_CONFIG_FLAG_DisableGoToWritheWhenInjured,
	CPED_CONFIG_FLAG_OnlyUseForcedSeatWhenEnteringHeliInGroup,
	CPED_CONFIG_FLAG_ThrownFromVehicleDueToExhaustion,
	CPED_CONFIG_FLAG_UpdateEnclosedSearchRegion,
	CPED_CONFIG_FLAG_DisableWeirdPedEvents,
	CPED_CONFIG_FLAG_ShouldChargeNow,
	CPED_CONFIG_FLAG_RagdollingOnBoat,
	CPED_CONFIG_FLAG_HasBrandishedWeapon,
	CPED_CONFIG_FLAG_AllowMinorReactionsAsMissionPed,
	CPED_CONFIG_FLAG_BlockDeadBodyShockingEventsWhenDead,
	CPED_CONFIG_FLAG_PedHasBeenSeen,
	CPED_CONFIG_FLAG_PedIsInReusePool,
	CPED_CONFIG_FLAG_PedWasReused,
	CPED_CONFIG_FLAG_DisableShockingEvents,
	CPED_CONFIG_FLAG_MovedUsingLowLodPhysicsSinceLastActive,
	CPED_CONFIG_FLAG_NeverReactToPedOnRoof,
	CPED_CONFIG_FLAG_ForcePlayFleeScenarioExitOnNextScriptCommand,
	CPED_CONFIG_FLAG_JustBumpedIntoVehicle,
	CPED_CONFIG_FLAG_DisableShockingDrivingOnPavementEvents,
	CPED_CONFIG_FLAG_ShouldThrowSmokeNow,
	CPED_CONFIG_FLAG_DisablePedConstraints,
	CPED_CONFIG_FLAG_ForceInitialPeekInCover,
	CPED_CONFIG_FLAG_CreatedByDispatch,
	CPED_CONFIG_FLAG_PointGunLeftHandSupporting,
	CPED_CONFIG_FLAG_DisableJumpingFromVehiclesAfterLeader,
	CPED_CONFIG_FLAG_DontActivateRagdollFromPlayerPedImpact,
	CPED_CONFIG_FLAG_DontActivateRagdollFromAiRagdollImpact,
	CPED_CONFIG_FLAG_DontActivateRagdollFromPlayerRagdollImpact,
	CPED_CONFIG_FLAG_DisableQuadrupedSpring,
	CPED_CONFIG_FLAG_IsInCluster,
	CPED_CONFIG_FLAG_ShoutToGroupOnPlayerMelee,
	CPED_CONFIG_FLAG_IgnoredByAutoOpenDoors,
	CPED_CONFIG_FLAG_PreferInjuredGetup,
	CPED_CONFIG_FLAG_ForceIgnoreMeleeActiveCombatant,
	CPED_CONFIG_FLAG_CheckLoSForSoundEvents,
	CPED_CONFIG_FLAG_JackedAbandonedCar,
	CPED_CONFIG_FLAG_CanSayFollowedByPlayerAudio,
	CPED_CONFIG_FLAG_ActivateRagdollFromMinorPlayerContact,
	CPED_CONFIG_FLAG_HasPortablePickupAttached,
	CPED_CONFIG_FLAG_ForcePoseCharacterCloth,
	CPED_CONFIG_FLAG_HasClothCollisionBounds,
	CPED_CONFIG_FLAG_HasHighHeels,
	CPED_CONFIG_FLAG_TreatAsAmbientPedForDriverLockOn,
	CPED_CONFIG_FLAG_DontBehaveLikeLaw,
	CPED_CONFIG_FLAG_SpawnedAtScenario,
	CPED_CONFIG_FLAG_DisablePoliceInvestigatingBody,
	CPED_CONFIG_FLAG_DisableWritheShootFromGround,
	CPED_CONFIG_FLAG_LowerPriorityOfWarpSeats,
	CPED_CONFIG_FLAG_DisableTalkTo,
	CPED_CONFIG_FLAG_DontBlip,
	CPED_CONFIG_FLAG_IsSwitchingWeapon,
	CPED_CONFIG_FLAG_IgnoreLegIkRestrictions,
	CPED_CONFIG_FLAG_ScriptForceNoTimesliceIntelligenceUpdate,
	CPED_CONFIG_FLAG_JackedOutOfMyVehicle,
	CPED_CONFIG_FLAG_WentIntoCombatAfterBeingJacked,
	CPED_CONFIG_FLAG_DontActivateRagdollForVehicleGrab,
	CPED_CONFIG_FLAG_ForcePackageCharacterCloth,
	CPED_CONFIG_FLAG_DontRemoveWithValidOrder,
	CPED_CONFIG_FLAG_AllowTaskDoNothingTimeslicing,
	CPED_CONFIG_FLAG_ForcedToStayInCoverDueToPlayerSwitch,
	CPED_CONFIG_FLAG_ForceProneCharacterCloth,
	CPED_CONFIG_FLAG_NotAllowedToJackAnyPlayers,
	CPED_CONFIG_FLAG_InToStrafeTransition,
	CPED_CONFIG_FLAG_KilledByStandardMelee,
	CPED_CONFIG_FLAG_AlwaysLeaveTrainUponArrival,
	CPED_CONFIG_FLAG_ForcePlayDirectedNormalScenarioExitOnNextScriptCommand,
	CPED_CONFIG_FLAG_OnlyWritheFromWeaponDamage,
	CPED_CONFIG_FLAG_UseSloMoBloodVfx,
	CPED_CONFIG_FLAG_EquipJetpack,
	CPED_CONFIG_FLAG_PreventDraggedOutOfCarThreatResponse,
	CPED_CONFIG_FLAG_ScriptHasCompletelyDisabledCollision,
	CPED_CONFIG_FLAG_NeverDoScenarioNavChecks,
	CPED_CONFIG_FLAG_ForceSynchronousScenarioExitChecking,
	CPED_CONFIG_FLAG_ThrowingGrenadeWhileAiming,
	CPED_CONFIG_FLAG_HeadbobToRadioEnabled,
	CPED_CONFIG_FLAG_ForceDeepSurfaceCheck,
	CPED_CONFIG_FLAG_DisableDeepSurfaceAnims,
	CPED_CONFIG_FLAG_DontBlipNotSynced,
	CPED_CONFIG_FLAG_IsDuckingInVehicle,
	CPED_CONFIG_FLAG_PreventAutoShuffleToTurretSeat,
	CPED_CONFIG_FLAG_DisableEventInteriorStatusCheck,
	CPED_CONFIG_FLAG_HasReserveParachute,
	CPED_CONFIG_FLAG_UseReserveParachute,
	CPED_CONFIG_FLAG_TreatDislikeAsHateWhenInCombat,
	CPED_CONFIG_FLAG_OnlyUpdateTargetWantedIfSeen,
	CPED_CONFIG_FLAG_AllowAutoShuffleToDriversSeat,
	CPED_CONFIG_FLAG_DontActivateRagdollFromSmokeGrenade,
	CPED_CONFIG_FLAG_LinkMBRToOwnerOnChain,
	CPED_CONFIG_FLAG_AmbientFriendBumpedByPlayer,
	CPED_CONFIG_FLAG_AmbientFriendBumpedByPlayerVehicle,
	CPED_CONFIG_FLAG_InFPSUnholsterTransition,
	CPED_CONFIG_FLAG_PreventReactingToSilencedCloneBullets,
	CPED_CONFIG_FLAG_DisableInjuredCryForHelpEvents,
	CPED_CONFIG_FLAG_NeverLeaveTrain,
	CPED_CONFIG_FLAG_DontDropJetpackOnDeath,
	CPED_CONFIG_FLAG_UseFPSUnholsterTransitionDuringCombatRoll,
	CPED_CONFIG_FLAG_ExitingFPSCombatRoll,
	CPED_CONFIG_FLAG_ScriptHasControlOfPlayer,
	CPED_CONFIG_FLAG_PlayFPSIdleFidgetsForProjectile,
	CPED_CONFIG_FLAG_DisableAutoEquipHelmetsInBikes,
	CPED_CONFIG_FLAG_DisableAutoEquipHelmetsInAircraft,
	CPED_CONFIG_FLAG_WasPlayingFPSGetup,
	CPED_CONFIG_FLAG_WasPlayingFPSMeleeActionResult,
	CPED_CONFIG_FLAG_PreferNoPriorityRemoval,
	CPED_CONFIG_FLAG_FPSFidgetsAbortedOnFire,
	CPED_CONFIG_FLAG_ForceFPSIKWithUpperBodyAnim,
	CPED_CONFIG_FLAG_SwitchingCharactersInFirstPerson,
	CPED_CONFIG_FLAG_IsClimbingLadder,
	CPED_CONFIG_FLAG_HasBareFeet,
	CPED_CONFIG_FLAG_UNUSED_REPLACE_ME_2,
	CPED_CONFIG_FLAG_GoOnWithoutVehicleIfItIsUnableToGetBackToRoad,
	CPED_CONFIG_FLAG_BlockDroppingHealthSnacksOnDeath,
	CPED_CONFIG_FLAG_ResetLastVehicleOnVehicleExit,
	CPED_CONFIG_FLAG_ForceThreatResponseToNonFriendToFriendMeleeActions,
	CPED_CONFIG_FLAG_DontRespondToRandomPedsDamage,
	CPED_CONFIG_FLAG_AllowContinuousThreatResponseWantedLevelUpdates,
	CPED_CONFIG_FLAG_KeepTargetLossResponseOnCleanup,
	CPED_CONFIG_FLAG_PlayersDontDragMeOutOfCar,
	CPED_CONFIG_FLAG_BroadcastRepondedToThreatWhenGoingToPointShooting,
	CPED_CONFIG_FLAG_IgnorePedTypeForIsFriendlyWith,
	CPED_CONFIG_FLAG_TreatNonFriendlyAsHateWhenInCombat,
	CPED_CONFIG_FLAG_DontLeaveVehicleIfLeaderNotInVehicle,
	CPED_CONFIG_FLAG_ChangeFromPermanentToAmbientPopTypeOnMigration,
	CPED_CONFIG_FLAG_AllowMeleeReactionIfMeleeProofIsOn,
	CPED_CONFIG_FLAG_UsingLowriderLeans,
	CPED_CONFIG_FLAG_UsingAlternateLowriderLeans,
	CPED_CONFIG_FLAG_UseNormalExplosionDamageWhenBlownUpInVehicle,
	CPED_CONFIG_FLAG_DisableHomingMissileLockForVehiclePedInside,
	CPED_CONFIG_FLAG_DisableTakeOffScubaGear,
	CPED_CONFIG_FLAG_IgnoreMeleeFistWeaponDamageMult,
	CPED_CONFIG_FLAG_LawPedsCanFleeFromNonWantedPlayer,
	CPED_CONFIG_FLAG_ForceBlipSecurityPedsIfPlayerIsWanted,
	CPED_CONFIG_FLAG_IsHolsteringWeapon,
	CPED_CONFIG_FLAG_UseGoToPointForScenarioNavigation,
	CPED_CONFIG_FLAG_DontClearLocalPassengersWantedLevel,
	CPED_CONFIG_FLAG_BlockAutoSwapOnWeaponPickups,
	CPED_CONFIG_FLAG_ThisPedIsATargetPriorityForAI,
	CPED_CONFIG_FLAG_IsSwitchingHelmetVisor,
	CPED_CONFIG_FLAG_ForceHelmetVisorSwitch,
	CPED_CONFIG_FLAG_IsPerformingVehicleMelee,
	CPED_CONFIG_FLAG_UseOverrideFootstepPtFx,
	CPED_CONFIG_FLAG_DisableVehicleCombat,
	CPED_CONFIG_FLAG_TreatAsFriendlyForTargetingAndDamage,
	CPED_CONFIG_FLAG_AllowBikeAlternateAnimations,
	CPED_CONFIG_FLAG_TreatAsFriendlyForTargetingAndDamageNonSynced,
	CPED_CONFIG_FLAG_UseLockpickVehicleEntryAnimations,
	CPED_CONFIG_FLAG_IgnoreInteriorCheckForSprinting,
	CPED_CONFIG_FLAG_SwatHeliSpawnWithinLastSpottedLocation,
	CPED_CONFIG_FLAG_DisableStartEngine,
	CPED_CONFIG_FLAG_IgnoreBeingOnFire,
	CPED_CONFIG_FLAG_DisableTurretOrRearSeatPreference,
	CPED_CONFIG_FLAG_DisableWantedHelicopterSpawning,
	CPED_CONFIG_FLAG_UseTargetPerceptionForCreatingAimedAtEvents,
	CPED_CONFIG_FLAG_DisableHomingMissileLockon,
	CPED_CONFIG_FLAG_ForceIgnoreMaxMeleeActiveSupportCombatants,
	CPED_CONFIG_FLAG_StayInDefensiveAreaWhenInVehicle,
	CPED_CONFIG_FLAG_DontShoutTargetPosition,
	CPED_CONFIG_FLAG_DisableHelmetArmor,
	CPED_CONFIG_FLAG_CreatedByConcealedPlayer,
	CPED_CONFIG_FLAG_PermanentlyDisablePotentialToBeWalkedIntoResponse,
	CPED_CONFIG_FLAG_PreventVehExitDueToInvalidWeapon,
	CPED_CONFIG_FLAG_IgnoreNetSessionFriendlyFireCheckForAllowDamage,
	CPED_CONFIG_FLAG_DontLeaveCombatIfTargetPlayerIsAttackedByPolice,
	CPED_CONFIG_FLAG_CheckLockedBeforeWarp,
	CPED_CONFIG_FLAG_DontShuffleInVehicleToMakeRoom,
	CPED_CONFIG_FLAG_GiveWeaponOnGetup,
	CPED_CONFIG_FLAG_DontHitVehicleWithProjectiles,
	CPED_CONFIG_FLAG_DisableForcedEntryForOpenVehiclesFromTryLockedDoor,
	CPED_CONFIG_FLAG_FiresDummyRockets,
	CPED_CONFIG_FLAG_PedIsArresting,
	CPED_CONFIG_FLAG_IsDecoyPed,
	CPED_CONFIG_FLAG_HasEstablishedDecoy,
	CPED_CONFIG_FLAG_BlockDispatchedHelicoptersFromLanding,
	CPED_CONFIG_FLAG_DontCryForHelpOnStun,
	CPED_CONFIG_FLAG_HitByTranqWeapon,
	CPED_CONFIG_FLAG_CanBeIncapacitated,
	CPED_CONFIG_FLAG_ForcedAimFromArrest,
	CPED_CONFIG_FLAG_CanFlyThruWindscreen = 32,
	CPED_CONFIG_FLAG_SuperDead = 73,
	CPED_CONFIG_FLAG_IsOnGround = 60,
	CPED_CONFIG_FLAG_NoCollision = 52,
	CPED_CONFIG_FLAG_Shrink = 223,

	// Short name aliases to fix compilation errors
	VisibleOnScreen = CPED_CONFIG_FLAG_VisibleOnScreen,
	BlockWeaponSwitching = CPED_CONFIG_FLAG_BlockWeaponSwitching,
	NoCriticalHits = CPED_CONFIG_FLAG_NoCriticalHits,
	Shrink = CPED_CONFIG_FLAG_Shrink,
};
using ePedConfigFlag = ePedConfigFlags;
#pragma endregion

class CPed;
class CVehicle;
class CPlayerInfo;
class CWeaponManager;

#pragma region Infos
class CPlayerInfo {
public:
	int PlayerID( ) {
		if ( !this ) { return 0; }
		return Mem.Read<int>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_PlayerId );
	}

	std::string GetName( ) {
		if ( !this ) { return ""; }
		uintptr_t addr = reinterpret_cast<uintptr_t>(this);
		auto isValidName = [](const std::string& n) {
			if (n.empty() || n.length() < 2 || n.length() > 32) return false;
			if (n.find("Invalid") != std::string::npos) return false;
			for (unsigned char c : n) {
				if (c < 32 || c > 126) return false;
			}
			return true;
		};
		uintptr_t offsets[] = { 0x7C, 0x88, 0x8C, 0x90, 0x94, 0x9C, 0xA0 };
		for (auto off : offsets) {
			std::string n = Mem.ReadString(addr + off);
			if (isValidName(n))
				return n;
		}
		return "";
	}

	void SetInfStamina( bool Toggle ) {
		if ( !this ) { return; }
		Mem.Write<float>( reinterpret_cast< uintptr_t >( this ) + 0xCF4, Toggle ? FLT_MAX : 100 );
	}
};

class CWeaponInfo {
public:
	std::string GetName( ) {
		if ( !this ) { return xorstr( "" ); }
		return Mem.ReadString( Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x5F0 ) );
	}
};
#pragma endregion

#pragma region List
class CVehicleList {
public:
	CVehicle * Vehicle( int Idx )
	{
		if ( !this ) { return 0; }
		return ( CVehicle * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + ( Idx * 0x10U ) );
	}

};

class CPedList {
public:
	CPed * Ped( int Idx ) {
		if ( !this ) { return 0; }
		return ( CPed * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + ( Idx * 0x10U ) );
	}
};
#pragma endregion

#pragma region InterFaces
class CPedInterFace {
public:
	int MaxPed( ) { return Mem.Read<int>( reinterpret_cast< uintptr_t >( this ) + 0x108 ); }
	int PedCount( ) { return Mem.Read<int>( reinterpret_cast< uintptr_t >( this ) + 0x110 ); }
	CPedList * PedList( ) { return ( CPedList * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x100 ); }
};

class CVehInterFace {
public:
	int MaxVehicles( ) { return Mem.Read<int>( reinterpret_cast< uintptr_t >( this ) + 0x188 ); }
	int VehicleCount( ) { return Mem.Read<int>( reinterpret_cast< uintptr_t >( this ) + 0x190 ); }
	CVehicleList * VehicleList( ) { return ( CVehicleList * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x180 ); }
};

class CVehicle {
public:

	D3DXVECTOR3 GetPos( ) {
		if ( !this ) { return D3DXVECTOR3( 0, 0, 0 ); }
		return Mem.Read<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x90 );
	}

	void SetPos( D3DXVECTOR3 Pos ) {
		if ( !this ) { return; }

		//suintptr_t Navigation = Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x30 );
		//Mem.Write<D3DXVECTOR3>( Navigation + 0x30, D3DXVECTOR3( 0, 0, 0 ) );
		Mem.Write<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x90, Pos );
	}

	uintptr_t GetNavigation( ) {
		if ( !this ) { return 0; }
		return Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x30 );
	}

	uint64_t GetModelInfo()
	{
		if (!this)
			return 0;

		return Mem.Read<uint64_t>(reinterpret_cast<uintptr_t>(this) + 0x20);
	}

	uintptr_t GetHandling( ) {
		if ( !this ) { return 0; }
		return Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_Handling );
	}

	void FreezeVehicle(bool toggle) {
		if (!this) { return; }
		uintptr_t Navigation = Mem.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x30);
		if (!Navigation) return;
		
		uint8_t flags = Mem.Read<uint8_t>(Navigation + 0x11);
		if (toggle) {
			flags |= 2; // Add freeze flag
		} else {
			flags &= ~2; // Remove freeze flag
		}
		Mem.Write<uint8_t>(Navigation + 0x11, flags);
	}

	bool GetGodMode( ) {
		if ( !this ) { return false; }
		//Atualizar Offsets ??
		return Mem.Read<BYTE>( reinterpret_cast< uintptr_t >( this ) + 0x189 );
	}

	void SetGodMode( bool Toggle ) {
		if ( !this ) { return; }
		//Atualizar Offsets ??
		Mem.Write<BYTE>( reinterpret_cast< uintptr_t >( this ) + 0x189, Toggle );
	}

	float GetGravity( ) {
		if ( !this ) { return 0; }
		return Mem.Read<float>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_VehicleGravity );
	}

	void SetGravity( float Value ) {
		if ( !this ) { return; }
		Mem.Write<float>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_VehicleGravity, Value );
	}

	void Fix() {
		if (!this) { return; }

		float Value = 1000.0f;
		Mem.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x280, Value); // Vehicle Health
		Mem.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x820, Value); // Vehicle Body Health (approx)
		Mem.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x970, Value); // Vehicle Engine Health
	}

	int GetHandleByPointer(uint64_t vehicle) {

		uint64_t result_cave = Mem.CreateCodeCave(8);
		if (!result_cave)
			return 0;

		std::vector<uint8_t> handle_shellcode = {
			0x48, 0x83, 0xEC, 0x28,
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0xFF, 0xD0,
			0x48, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x89, 0x03,
			0x48, 0x83, 0xC4, 0x28,
			0xC3
		};

		memcpy(handle_shellcode.data() + 6, &vehicle, 8);
		memcpy(handle_shellcode.data() + 16, &g_Offsets.m_PointerToHandle, 8);
		memcpy(handle_shellcode.data() + 28, &result_cave, 8);

		auto handle_cave = Mem.CreateCodeCave(handle_shellcode.size());
		if (!handle_cave) {
			Mem.CreateCodeCave(result_cave);
			return 0;
		}

		if (!Mem.WriteBytes(handle_cave, handle_shellcode)) {
			Mem.FreeCave(handle_cave);
			Mem.FreeCave(result_cave);
			return 0;
		}

		auto handle_thread = CreateRemoteThread(Mem.ProcHandle, nullptr, 0,
			(LPTHREAD_START_ROUTINE)handle_cave, nullptr, 0, nullptr);
		if (!handle_thread) {
			Mem.FreeCave(handle_cave);
			Mem.FreeCave(result_cave);
			return 0;
		}

		WaitForSingleObject(handle_thread, 2000);
		CloseHandle(handle_thread);
		Mem.FreeCave(handle_cave);

		int vehicle_handle = 0;
		if (!ReadProcessMemory(Mem.ProcHandle, (LPCVOID)result_cave,
			&vehicle_handle, sizeof(vehicle_handle), nullptr)) {
			Mem.FreeCave(result_cave);
			return 0;
		}
		Mem.FreeCave(result_cave);

		if (vehicle_handle == 0)
			return 0;

		return vehicle_handle;
	}

	void SetVehicleForwardSpeed(float speed)
	{
		int handle = GetHandleByPointer((uint64_t)this);
		if (handle == 0)
			return;

		std::vector<uint8_t> ShellCode = {
			0x48, 0x83, 0xEC, 0x28,                                       // sub rsp, 0x28
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // mov rcx, handle/entity 
			0xF3, 0x0F, 0x10, 0x0D, 0x11, 0x00, 0x00, 0x00,              // movss xmm1, [rip+0x11] 
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // mov rax, func_addr  
			0xFF, 0xD0,                                                    // call rax
			0x48, 0x83, 0xC4, 0x28,                                       // add rsp, 0x28
			0xC3,                                                          // ret
			0x00, 0x00, 0x00, 0x00                                        // speed float
		};

		uintptr_t Cave = Mem.CreateCodeCave(ShellCode.size());
		uintptr_t Func = g_Offsets.m_SetVehicleForwardSpeed;

		int64_t entityHandle = (int64_t)handle;

		memcpy(ShellCode.data() + 6, &entityHandle, 8); 
		memcpy(ShellCode.data() + 24, &Func, 8); 
		memcpy(ShellCode.data() + 39, &speed, 4); 

		Mem.WriteBytes(Cave, ShellCode);

		HANDLE RemoteThread = CreateRemoteThread(Mem.ProcHandle, NULL, 0,
			(LPTHREAD_START_ROUTINE)Cave, NULL, 0, NULL);
		if (RemoteThread) {
			WaitForSingleObject(RemoteThread, 5000);
			CloseHandle(RemoteThread);
		}
		Mem.FreeCave(Cave);
	}

	bool IsLocked( ) {
		if ( !this ) { return false; }
		return Mem.Read<uint32_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_VehicleDoorsLockState ) == 2;
	}

	void DoorState( bool Unlock ) {
		if ( !this ) { return; }

		Mem.Write<uint32_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_VehicleDoorsLockState, Unlock ? 1 : 2 );
	}

	D3DXVECTOR3 GetVelocity( ) {
		if ( !this ) { return D3DXVECTOR3( 0, 0, 0 ); }
		return Mem.Read<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x320 );
	}

	void SetVelocity( D3DXVECTOR3 Velocity ) {
		if ( !this ) { return; }
		Mem.Write<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x320, Velocity );
	}

	CPed * GetDriver( )
	{
		if ( !this ) return 0;
		return ( CPed * )::Core::Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_VehicleDriver );
	}

	uintptr_t GetVehicleDrawHandler() {
		if (!this) return 0;
		return Mem.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x48);
	}

	uintptr_t GetCustomShaderEffectVehicle() {
		uintptr_t drawHandler = GetVehicleDrawHandler();
		if (!drawHandler) return 0;
		return Mem.Read<uintptr_t>(drawHandler + 0x20);
	}

	int ImColorToARGB(const ImColor& color) {
		int a = static_cast<int>(color.Value.w * 255.0f);
		int r = static_cast<int>(color.Value.x * 255.0f);
		int g = static_cast<int>(color.Value.y * 255.0f);
		int b = static_cast<int>(color.Value.z * 255.0f);
		return (a << 24) | (r << 16) | (g << 8) | b;
	}

	void SetPrimaryVehicleColor(const ImColor& color) {
		if (!this) return;

		uintptr_t shaderEffect = GetCustomShaderEffectVehicle();
		if (!shaderEffect) return;

		int argbColor = ImColorToARGB(color);
		Mem.Write<int>(shaderEffect + 0xA4, argbColor);
	}

	void SetSecondaryVehicleColor(const ImColor& color) {
		if (!this) return;

		uintptr_t shaderEffect = GetCustomShaderEffectVehicle();
		if (!shaderEffect) return;

		int argbColor = ImColorToARGB(color);
		Mem.Write<int>(shaderEffect + 0xA8, argbColor);
	}

	void SetVehicleColors(const ImColor& primaryColor, const ImColor& secondaryColor) {
		SetPrimaryVehicleColor(primaryColor);
		SetSecondaryVehicleColor(secondaryColor);
	}

	void ResetVehicleColors() {
		if (!this) return;

		uintptr_t shaderEffect = GetCustomShaderEffectVehicle();
		if (!shaderEffect) return;

		Mem.Write<int>(shaderEffect + 0xA4, 0xFFFFFFFF);
		Mem.Write<int>(shaderEffect + 0xA8, 0xFFFFFFFF);
	}

	bool HasCustomShaderEffect() {
		return GetCustomShaderEffectVehicle() != 0;
	}


};

class CWeaponManager {
public:
	CWeaponInfo * GetWeaponInfo( ) {
		if ( !this ) { return 0; }
		return ( CWeaponInfo * ) ::Core::Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x20 );
	}

	float GetRecoil( ) {
		if ( !this ) { return 0.0f; }
		CWeaponInfo * WeaponInfo = ( CWeaponInfo * ) GetWeaponInfo( );
		return ::Core::Mem.Read<float>( ( uintptr_t ) WeaponInfo + g_Offsets.m_Recoil );
	}

	float SetRecoil( float Recoil ) {
		if ( !this ) { return 0.0f; }
		CWeaponInfo * WeaponInfo = ( CWeaponInfo * ) GetWeaponInfo( );
		return ::Core::Mem.Write<float>( ( uintptr_t ) WeaponInfo + g_Offsets.m_Recoil, Recoil );
	}

	float GetSpread( ) {
		if ( !this ) { return 0.0f; }
		CWeaponInfo * WeaponInfo = ( CWeaponInfo * ) GetWeaponInfo( );
		return ::Core::Mem.Read<float>( ( uintptr_t ) WeaponInfo + g_Offsets.m_Spread );
	}

	float SetSpread( float Spread ) {
		if ( !this ) { return 0.0f; }
		CWeaponInfo * WeaponInfo = ( CWeaponInfo * ) GetWeaponInfo( );
		return ::Core::Mem.Write<float>( ( uintptr_t ) WeaponInfo + g_Offsets.m_Spread, Spread );
	}
};

struct TeleportTarget
{
	uintptr_t Object;
	uintptr_t Navigation;
	uintptr_t ModelInfo;
};

class CReplayInterFace {
public:

	CPedInterFace * InterfacePed( ) {
		if ( !this ) { return 0; }
		return ( CPedInterFace * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x18 );
	}

	CVehInterFace * InterfaceVeh( ) {
		if ( !this ) { return 0; }
		return ( CVehInterFace * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x10 );
	}
};

#pragma endregion

class CPed {
public:

	CPed* pNetObject() {
		if (!this) return 0;
		return (CPed*)Mem.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0xD0);
	}

	void SetInvisible(bool enable) {
		Mem.Write<uint8_t>((uintptr_t)this + 0xD1, enable ? 1 : 0);
	}

	bool IsInvisible() {
		if (!this) return false;
		CPed* pNet = pNetObject();
		if (!pNet) return false;
		return Mem.Read<uint8_t>((uintptr_t)pNet + 0xD1) == 1;
	}

	bool IsSetInvisible() {
		if (!this) return false;

		// No GTA V / FiveM, o offset 0x2C da CEntity contém as flags de visibilidade principal. 
		// Bit 0 (0x01): 1 = Visível, 0 = Invisível (SetEntityVisible false). 
		uint8_t flag = Mem.Read<uint8_t>((uintptr_t)this + 0x2C);

		// Também verificamos o Alpha no offset 0xAC. Se for 0, a entidade está invisível (SetEntityAlpha 0). 
		int alpha = Mem.Read<int>((uintptr_t)this + 0xAC);

		// Verifica se o player está carregado (distância > 0) para evitar falsos positivos de entidades não sincronizadas
		D3DXVECTOR3 pos = GetPos();
		if (pos.x == 0 && pos.y == 0 && pos.z == 0) return false;

		// Detecta se a entidade está forçadamente invisível por SetEntityVisible(false) ou Alpha 0 
		// A condição (flag & 0x01) == 0 significa que a entidade está marcada como invisível no motor do jogo. 
		return (((flag & 0x01) == 0) || (alpha == 0));
	}
	
	float GetMaxHealth( ) {
		if ( !this ) { return 0; }
		return Mem.Read<float>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_MaxHealth );
	}

	float GetHealth( ) {
		if ( !this ) { return 0; }
		return Mem.Read<float>( reinterpret_cast< uintptr_t >( this ) + 0x280 );
	}

	void SetHealth( float Health ) {
		if ( !this ) { return; }
		Mem.Write<float>( reinterpret_cast< uintptr_t >( this ) + 0x280, Health );
	}

	float GetArmor( ) {
		if ( !this ) { return 0; }
		return Mem.Read<float>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_Armor );
	}

	void SetArmor( float Armor ) {
		if ( !this ) { return; }
		Mem.Write<float>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_Armor, Armor );
	}

	float GetSpeed( ) {
		if ( !this ) { return 0; }
		CPlayerInfo * PlayerInfo = this->GetPlayerInfo( );
		return Mem.Read<float>( reinterpret_cast< uintptr_t >( PlayerInfo ) + g_Offsets.m_Speed );
	}

	void SetSpeed( float Speed ) {
		if ( !this ) { return; }
		CPlayerInfo * PlayerInfo = this->GetPlayerInfo( );
		Mem.Write<float>( reinterpret_cast< uintptr_t >( PlayerInfo ) + g_Offsets.m_Speed, Speed );
	}

	D3DXVECTOR3 GetPos( ) {
		if ( !this ) { return D3DXVECTOR3( 0, 0, 0 ); }
		return Mem.Read<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x90 );
	}

	void SetPos( D3DXVECTOR3 Pos ) {
		if ( !this ) { return; }
		bool InsideVehicle = IsInVehicle( );
		uintptr_t LastVeh = reinterpret_cast< uintptr_t >( GetLastVehicle( ) );

		if ( LastVeh && InsideVehicle ) {
			uintptr_t Navigation = Mem.Read<uintptr_t>( LastVeh + 0x30 );
			Mem.Write<D3DXVECTOR3>( LastVeh + 0x320, D3DXVECTOR3( 0, 0, 0 ) ); // Zero velocity
			Mem.Write<D3DXVECTOR3>( LastVeh + 0x90, Pos );
		}
		else if ( !InsideVehicle ) {
			uintptr_t Navigation = this->GetNavigation( );
			Mem.Write<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x320, D3DXVECTOR3 { 0, 0, 0 } ); // Zero velocity
			Mem.Write<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x90, Pos );
		}
	}

	void SeatBealt(bool toggle) {
		if (!this) { return; }
		bool InsideVehicle = IsInVehicle();

		if (InsideVehicle) {
			if (toggle) {
				uintptr_t Path = Mem.FindSignature({ 0x83, 0xa1, 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x83, 0xe2 });
				Mem.WriteBytes(Path, { 0x90,0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, });
				Mem.Write<BYTE>((uintptr_t)this + g_Offsets.m_SeatBealt, 0xC9);
			}
			else {
				Mem.Write<BYTE>((uintptr_t)this + g_Offsets.m_SeatBealt, 0xC8);
			} 
		}

	}

	CVehicle * GetLastVehicle( ) {
		if ( !this ) return 0;
		return ( CVehicle * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_LastVehicle );
	}

	CPlayerInfo * GetPlayerInfo( ) {
		if ( !this ) return 0;
		return ( CPlayerInfo * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_PlayerInfo );
	}

	CWeaponManager * GetWeaponManager( ) {
		if ( !this ) return 0;
		return ( CWeaponManager * ) Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_WeaponManager );
	}

	uint32_t GetPedType( ) {
		if ( !this ) { return 0; }
		return Mem.Read<uint32_t>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_EntityType ) << 11 >> 25;
	}

	int GetID( ) {
		if ( !this ) { return -1; }
		CPlayerInfo * PlayerInfo = ( CPlayerInfo * ) GetPlayerInfo( );
		if ( !PlayerInfo ) { return -1; }
		int Id = PlayerInfo->PlayerID( );
		return Id;
	}

	bool HasFlag( ePedConfigFlag Flag )
	{
		if ( !this ) { return false; }

		auto v1 = ( int ) Flag;
		if ( !this || v1 > 0x1CA ) return false;

		auto v2 = 1 << ( v1 & 0x1F );
		auto v3 = v1 >> 5;
		auto v4 = reinterpret_cast< uintptr_t >( this ) + 4 * v3 + g_Offsets.m_PedFlag;
		auto v5 = Mem.Read<long>( v4 );

		return ( v2 & v5 ) != 0;
	}

	void SetConfigFlag( ePedConfigFlag Flag, bool Value )
	{
		if ( !this ) { return; }

		auto v1 = ( int ) Flag;
		if ( !this || v1 > 0x1CA ) return;

		auto v2 = 1 << ( v1 & 0x1F );
		auto v3 = v1 >> 5;
		auto v4 = ( uintptr_t ) ( this ) + 4 * v3 + g_Offsets.m_PedFlag;
		auto v5 = Mem.Read<long>( v4 );

		if ( Value != ( ( v2 & v5 ) != 0 ) ) {
			auto v6 = v2 & ( v5 ^ -( uint8_t ) ( Value ? 1 : 0 ) );
			v5 ^= v6;
			Mem.Write( v4, v5 );
		}
	}

	bool IsPedVisible( ) {
		if ( !this ) return false;
		return HasFlag( CPED_CONFIG_FLAG_VisibleOnScreen );
	}

	bool IsEntityAttached() {
		if (!this) return false;
		uintptr_t unk = Mem.Read<uintptr_t>((uintptr_t)this + 0x50);
		if (!unk) return false;
		uintptr_t unk2 = Mem.Read<uintptr_t>(unk + 0x48);
		return (unk2 && !IsInVehicle());
	}

	void DetachEntity(int a1, int a2) {
		if (!this) return;
		if (!g_Offsets.m_DettachEntity) {
			g_Offsets.m_DettachEntity = Mem.FindSignatureStr("48 8b c4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8d a8 ? ? ? ? 48 81 ec ? ? ? ? 80 79");
		}
		if (g_Offsets.m_DettachEntity) {
			// Using the logic provided by the user for the call
			uintptr_t ped = reinterpret_cast<uintptr_t>(this);
			
			struct shell_data {
				uintptr_t self;
				int64_t flags;
				int64_t p3;
				uintptr_t target;
			} data = { ped, (int64_t)a1, (int64_t)a2, g_Offsets.m_DettachEntity };

			std::thread([data]() {
				uint8_t shellcode[] = { 
					0x48, 0x83, 0xEC, 0x28,                                     // sub rsp, 28h 
					0x48, 0xB9, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, // mov rcx, self (Offset 6) 
					0x48, 0xBA, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, // mov rdx, flags (Offset 16) 
					0x49, 0xB8, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, // mov r8, p3 (Offset 26) 
					0x48, 0xB8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, // mov rax, function (Offset 36) 
					0xFF, 0xD0,                                                 // call rax 
					0x48, 0x83, 0xC4, 0x28,                                     // add rsp, 28h 
					0xC3                                                        // ret 
				}; 

				*(uintptr_t*)(shellcode + 6) = data.self; 
				*(int64_t*)(shellcode + 16) = data.flags; 
				*(int64_t*)(shellcode + 26) = data.p3; 
				*(uintptr_t*)(shellcode + 36) = data.target; 

				uintptr_t Cave = ::Core::Mem.CreateCodeCave(sizeof(shellcode));
				if (Cave) {
					::Core::Mem.WriteBytes(Cave, std::vector<uint8_t>(shellcode, shellcode + sizeof(shellcode)));
					HANDLE hThread = CreateRemoteThread(::Core::Mem.ProcHandle, NULL, 0, (LPTHREAD_START_ROUTINE)Cave, NULL, 0, NULL);
					if (hThread) {
						WaitForSingleObject(hThread, 1000);
						CloseHandle(hThread);
					}
					::Core::Mem.FreeCave(Cave);
				}
			}).detach();
		}
	}

	void UnfreezePed() {
		if (!this) return;
		this->FreezePed(false);
	}

	bool IsVisible() {
		if (!this) return false;
		if (g_Offsets.m_VisibleFlag == 0) return true; // Falback for unsupported builds
		
		uint8_t VisibilityFlag = Mem.Read<uint8_t>((uintptr_t)this + g_Offsets.m_VisibleFlag);
		
		if (VisibilityFlag == 36 || VisibilityFlag == 0 || VisibilityFlag == 4 || 
			VisibilityFlag == 12 || VisibilityFlag == 28 || VisibilityFlag == 44) {
			return false;
		}

		if (VisibilityFlag == 2 || VisibilityFlag == 6 || VisibilityFlag == 10 || 
			VisibilityFlag == 14 || VisibilityFlag == 18) {
			return true;
		}

		return true;
	}

	bool IsInVehicle( ) {
		if ( !this ) return false;
		return HasFlag( CPED_CONFIG_FLAG_IsInVehicleValue );
	}

	void NoRagDoll( bool Toggle )
	{
		if ( !this ) return;
		Mem.Write<BYTE>( reinterpret_cast< uintptr_t >( this ) + g_Offsets.m_NoRagDoll, Toggle ? 0x80 : 0x20 );
	}


	D3DXVECTOR3 GetVelocity( ) {
		if ( !this ) { return D3DXVECTOR3( 0, 0, 0 ); }
		return Mem.Read<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x320 );
	}

	void SetVelocity( D3DXVECTOR3 Velocity ) {
		if ( !this ) { return; }
		Mem.Write<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + 0x320, Velocity );
	}

	void FreezePed( bool Toggle ) {
		if ( !this ) { return; }
		if ( !IsInVehicle( ) ) {
			uintptr_t CModelInfo = Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x20 );
			Mem.Write<float>( CModelInfo + 0x2C, Toggle ? 0.f : 1.f );
		}
		else {
			Mem.Write<BYTE>( reinterpret_cast< uintptr_t >( GetLastVehicle( ) ) + 0x2E, Toggle ? 1 : 2 );
		}
	}



	TeleportTarget GetTeleportTarget()
	{
		TeleportTarget out{ 0, 0, 0 };

		if (!this)
			return out;

		CPed* ped = this;
		if (ped->IsInVehicle())
		{
			CVehicle* veh = ped->GetLastVehicle();
			if (!veh)
				return out;

			out.Object = reinterpret_cast<uintptr_t>(veh);
			out.Navigation = veh->GetNavigation();
			out.ModelInfo = veh->GetModelInfo();
		}
		else
		{
			out.Object = reinterpret_cast<uintptr_t>(ped);
			out.Navigation = ped->GetNavigation();
			out.ModelInfo = ped->GetModelInfo();

		}

		return out;
	}

	inline void TeleportFunc(
		uintptr_t Object,
		uintptr_t Navigation,
		uintptr_t ModelInfo,
		const D3DXVECTOR3& Position,
		const D3DXVECTOR3& VisualPosition,
		bool Stop
	)
	{
		if (!Object || !Navigation)
			return;

		float backupMagic = 0.f;

		if (Stop && ModelInfo)
		{
			backupMagic = Mem.Read<float>(ModelInfo + 0x2C);
			Mem.Write<float>(ModelInfo + 0x2C, 0.f);
		}

		Mem.Write<D3DXVECTOR3>(Object + 0x90, VisualPosition);

		Mem.Write<D3DXVECTOR3>(Navigation + 0x50, Position);

		if (Stop && ModelInfo)
		{
			Mem.Write<float>(ModelInfo + 0x2C, backupMagic);
		}
	}

	void TeleportTo(const D3DXVECTOR3& targetPos)
	{
		TeleportTarget tp = GetTeleportTarget();

		if (!tp.Object || !tp.Navigation || !tp.ModelInfo)
			return;

		TeleportFunc(
			tp.Object,
			tp.Navigation,
			tp.ModelInfo,
			targetPos,
			targetPos,
			true
		);
	}

	void SpectatePlayer(bool toggle, uintptr_t entity)
	{
		// Offset que verifica se o jogador já está em modo espectador 
		uintptr_t patch = g_Offsets.m_IsInSpectatorMode;

		// Patch para forçar o retorno como 'false' (evitar verificações de segurança do jogo) 
		std::vector<uint8_t> ret =
		{
			0x30, 0xC0,      // xor al, al (return false) 
			0xC3,            // ret 
			0x90, 0x90, 0x90 // nop (preenchimento) 
		};

		// Aplica o patch na memória 
		Mem.WriteBytes(patch, ret);

		// Endereço da função interna do jogo para definir o modo espectador 
		uintptr_t func = g_Offsets.m_SetInSpectatorMode;

		// Estrutura do ShellCode em Assembly x64 
		std::vector<uint8_t> ShellCode =
		{
			0x51,                                               // push rcx 
			0x52,                                               // push rdx 
			0x48, 0x83, 0xEC, 0x28,                             // sub rsp, 0x28 
			0x48, 0xB9,                                         // mov rcx, ... 
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     // [8] toggle (0 ou 1) 
			0x48, 0xBA,                                         // mov rdx, ... 
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     // [18] handle do player 
			0xFF, 0x15, 0x02, 0x00, 0x00, 0x00,                 // call qword ptr [rip+2] 
			0xEB, 0x08,                                         // jmp +8 
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     // [34] endereço da função 
			0x48, 0x83, 0xC4, 0x28,                             // add rsp, 0x28 
			0x5A,                                               // pop rdx 
			0x59,                                               // pop rcx 
			0xC3                                                // ret 
		};

		uint64_t toggleVal = toggle ? 1ULL : 0ULL;
		// Converte o ponteiro da entidade para um handle interno do GTA 
		int handleVal = GetHandleByPointer((uint64_t)entity);

		// Insere os valores dinâmicos no ShellCode 
		memcpy(ShellCode.data() + 8, &toggleVal, sizeof(uint64_t));
		memcpy(ShellCode.data() + 18, &handleVal, sizeof(int));
		memcpy(ShellCode.data() + 34, &func, sizeof(uint64_t));

		// Cria um CodeCave (espaço de memória) para executar o código 
		uintptr_t Cave = Mem.CreateCodeCave(ShellCode.size());
		Mem.WriteBytes(Cave, ShellCode);

		// Executa o ShellCode em uma nova thread no processo do jogo 
		HANDLE RemoteThread = CreateRemoteThread(Mem.ProcHandle, NULL, 0,
			(LPTHREAD_START_ROUTINE)Cave, NULL, 0, NULL);

		if (RemoteThread) {
			WaitForSingleObject(RemoteThread, INFINITE);
			CloseHandle(RemoteThread);
		}

		// Libera a memória alocada 
		Mem.FreeCave(Cave);
	}

	void SetLocalAlpha(int alpha) { if (!this) return; Mem.Write<uint8_t>(reinterpret_cast<uintptr_t>(this) + 0xAC, (uint8_t)alpha); }

	int GetHandleByPointer(uint64_t vehicle) {

		uint64_t result_cave = Mem.CreateCodeCave(8);
		if (!result_cave)
			return 0;

		std::vector<uint8_t> handle_shellcode = {
			0x48, 0x83, 0xEC, 0x28,
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0xFF, 0xD0,
			0x48, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x89, 0x03,
			0x48, 0x83, 0xC4, 0x28,
			0xC3
		};

		memcpy(handle_shellcode.data() + 6, &vehicle, 8);
		memcpy(handle_shellcode.data() + 16, &g_Offsets.m_PointerToHandle, 8);
		memcpy(handle_shellcode.data() + 28, &result_cave, 8);

		auto handle_cave = Mem.CreateCodeCave(handle_shellcode.size());
		if (!handle_cave) {
			Mem.CreateCodeCave(result_cave);
			return 0;
		}

		if (!Mem.WriteBytes(handle_cave, handle_shellcode)) {
			Mem.FreeCave(handle_cave);
			Mem.FreeCave(result_cave);
			return 0;
		}

		auto handle_thread = CreateRemoteThread(Mem.ProcHandle, nullptr, 0,
			(LPTHREAD_START_ROUTINE)handle_cave, nullptr, 0, nullptr);
		if (!handle_thread) {
			Mem.FreeCave(handle_cave);
			Mem.FreeCave(result_cave);
			return 0;
		}

		WaitForSingleObject(handle_thread, 2000);
		CloseHandle(handle_thread);
		Mem.FreeCave(handle_cave);

		int vehicle_handle = 0;
		if (!ReadProcessMemory(Mem.ProcHandle, (LPCVOID)result_cave,
			&vehicle_handle, sizeof(vehicle_handle), nullptr)) {
			Mem.FreeCave(result_cave);
			return 0;
		}
		Mem.FreeCave(result_cave);

		if (vehicle_handle == 0)
			return 0;

		return vehicle_handle;
	}

	void SetGodMode(bool Toggle) {
		if (!this) { return; }
		if (Toggle) {
			uintptr_t godmodeAddr = reinterpret_cast<uintptr_t>(this) + 0x188;
			Mem.Write<DWORD>(godmodeAddr, 0x1000u);
		}
		else {
			uintptr_t disableAddr = reinterpret_cast<uintptr_t>(this) + 0x189;
			Mem.Write<bool>(disableAddr, 0);
		}
	}

	void SetInfStamina( bool Toggle ) {
		if ( !this ) { return; }
		CPlayerInfo * PlayerInfo = ( CPlayerInfo * ) GetPlayerInfo( );
		Mem.Write<float>( reinterpret_cast< uintptr_t >( PlayerInfo ) + 0xCF4, Toggle ? FLT_MAX : 100 );
	}


	void SetInfCombatRoll( bool enable ) {
		if ( !this ) { return; }

		uintptr_t Address = g_Offsets.m_InfiniteCombatRoll;
		static std::vector<uint8_t> OriginalTable;

		if ( OriginalTable.empty( ) ) {
			OriginalTable = Mem.ReadBytes( Address, 6 );
		}

		std::vector <uint8_t> Patch = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

		Mem.WriteBytes( Address, enable ? Patch : OriginalTable );
	}

	D3DXVECTOR3 GetBonePosDefault( const int Bone )
	{
		if ( !this ) { return D3DXVECTOR3( 0, 0, 0 ); }
		D3DXMATRIX Mtx = Mem.Read<D3DXMATRIX>( reinterpret_cast< uintptr_t >( this ) + 0x60 );
		D3DXVECTOR3 BonePos = Mem.Read<D3DXVECTOR3>( reinterpret_cast< uintptr_t >( this ) + ( g_Offsets.CurrentBuild >= 2802 ? 0x410 : 0x430 + Bone * 0x10 ) );;

		D3DXVECTOR4 Transform;
		D3DXVec3Transform( &Transform, &BonePos, &Mtx );
		return D3DXVECTOR3( Transform.x, Transform.y, Transform.z );
	}

	float GetDistance( D3DXVECTOR3 pos1, D3DXVECTOR3 pos2 ) {
		return std::sqrtf( std::pow( pos2.x - pos1.x, 2.f ) + std::pow( pos2.y - pos1.y, 2.f ) );
	}

	uintptr_t GetCPedInventory( ) {
		if ( !this ) { return 0; }
		return Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + ( g_Offsets.m_WeaponManager - 8 ) );
	}

	uintptr_t GetNavigation( ) {
		if ( !this ) { return 0; }
		return Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x30 );
	}

	uint64_t GetModelInfo()
	{
		if (!this)
			return 0;

		return Mem.Read<uint64_t>(reinterpret_cast<uintptr_t>(this) + 0x20);
	}

	void RemoveKinematics( )
	{
		if ( !g_Offsets.m_ArmsKinematics || !g_Offsets.m_LegsKinematics )
			return;

		Mem.PatchFunc( g_Offsets.m_ArmsKinematics, 5 );
		Mem.PatchFunc( g_Offsets.m_LegsKinematics, 5 );
	}

	void ForceWeaponWheel( bool toggle )
	{
		if ( !this ) return;

		static uintptr_t DisableControlAction = 0;
		static uintptr_t HideHudComponentThisFrame = 0;

		if ( DisableControlAction == 0 ) {
			DisableControlAction = Mem.FindSignature( 
				{ 0x48, 0x8b, 0x41, 0x00 , 0x83, 0x78, 0x00 , 0x00 , 0x8b, 0x50, 0x00 , 0x8b, 0x08, 0xe9, 0x00 , 0x00 , 0x00 , 0x00 , 0x48, 0x89, 0x5c, 0x24 } 
			);
		}

		if ( HideHudComponentThisFrame == 0 ) {
			HideHudComponentThisFrame = Mem.FindSignature(
				{ 0x48, 0x83, 0xec, 0x00 , 0x48, 0x8b, 0x41, 0x00 , 0x83, 0x38, 0x00 , 0x48, 0x89, 0x6c, 0x24 } 
			);
		}

		if ( toggle ) {
			Mem.WriteBytes( DisableControlAction, { 0xC3 } );
			Mem.WriteBytes( HideHudComponentThisFrame, { 0xC3 } );
			SetConfigFlag( CPED_CONFIG_FLAG_BlockWeaponSwitching, false );
		}
		else {
			Mem.WriteBytes( DisableControlAction, { 0x48 } );
			Mem.WriteBytes( HideHudComponentThisFrame, { 0x48 } );
			SetConfigFlag( CPED_CONFIG_FLAG_BlockWeaponSwitching, true ); //Isso pode dar problema pra frente*
		}
	}

};

class CHandlingData {
public:

	uint64_t qword0; //0x0000
	uint32_t m_model_hash; //0x0008
	float m_mass; //0x000C
	float m_initial_drag_coeff; //0x0010
	float m_downforce_multiplier; //0x0014
	float m_popup_light_rotation; //0x0018
	char pad_001C[ 4 ]; //0x001C
	D3DXVECTOR3 m_centre_of_mass; //0x0020
	char pad_002C[ 4 ]; //0x002C
	D3DXVECTOR3 m_inertia_mult; //0x0030
	char pad_003C[ 4 ]; //0x003C
	float m_buoyancy; //0x0040
	float m_drive_bias_rear; //0x0044
	float m_drive_bias_front; //0x0048
	float m_acceleration; //0x004C
	uint8_t m_initial_drive_gears; //0x0050
	char pad_0051[ 3 ]; //0x0051
	float m_drive_inertia; //0x0054
	float m_upshift; //0x0058
	float m_downshift; //0x005C
	float m_initial_drive_force; //0x0060
	float m_drive_max_flat_velocity; //0x0064
	float m_initial_drive_max_flat_vel; //0x0068
	float m_brake_force; //0x006C
	char pad_0070[ 4 ]; //0x0070
	float m_brake_bias_front; //0x0074
	float m_brake_bias_rear; //0x0078
	float m_handbrake_force; //0x007C
	float m_steering_lock; //0x0080
	float m_steering_lock_ratio; //0x0084
	float m_traction_curve_max; //0x0088
	float m_traction_curve_lateral; //0x008C
	float m_traction_curve_min; //0x0090
	float m_traction_curve_ratio; //0x0094
	float m_curve_lateral; //0x0098
	float m_curve_lateral_ratio; //0x009C
	float m_traction_spring_delta_max; //0x00A0
	float m_traction_spring_delta_max_ratio; //0x00A4
	float m_low_speed_traction_loss_mult; //0x00A8
	float m_camber_stiffness; //0x00AC
	float m_traction_bias_front; //0x00B0
	float m_traction_bias_rear; //0x00B4
	float m_traction_loss_mult; //0x00B8
	float m_suspension_force; //0x00BC
	float m_suspension_comp_damp; //0x00C0
	float m_suspension_rebound_damp; //0x00C4
	float m_suspension_upper_limit; //0x00C8
	float m_suspension_lower_limit; //0x00CC
	float m_suspension_raise; //0x00D0
	float m_suspension_bias_front; //0x00D4
	float m_suspension_bias_rear; //0x00D8
	float m_anti_rollbar_force; //0x00DC
	float m_anti_rollbar_bias_front; //0x00E0
	float m_anti_rollbar_bias_rear; //0x00E4
	float m_roll_centre_height_front; //0x00E8
	float m_roll_centre_height_rear; //0x00EC
	float m_collision_damage_mult; //0x00F0
	float m_weapon_damamge_mult; //0x00F4
	float m_deformation_mult; //0x00F8
	float m_engine_damage_mult; //0x00FC
	float m_petrol_tank_volume; //0x0100
	float m_oil_volume; //0x0104
	char pad_0108[ 4 ]; //0x0108
	D3DXVECTOR3 m_seat_offset_dist; //0x010C
	uint32_t m_monetary_value; //0x0118
	char pad_011C[ 8 ]; //0x011C
	uint32_t m_model_flags; //0x0124
	uint32_t m_handling_flags; //0x0128
	uint32_t m_damage_flags; //0x012C
	char pad_0130[ 12 ]; //0x0130
	uint32_t m_ai_handling_hash; //0x013C
	char pad_140[ 24 ]; //0x140
};

class CPedFactory {
public:
	CPed * GetLocalPlayer( ) {
		if ( !this ) { return 0; }
		return ( CPed * ) ::Core::Mem.Read<uintptr_t>( reinterpret_cast< uintptr_t >( this ) + 0x8 );
	}

	void CopyVariation(CPed* ped, CPed* target, bool use_extra_components)
	{
		if (!this || !ped || !target)
			return;

		std::vector<uint8_t> ShellCode = {
			0x48, 0x83, 0xEC, 0x28,                  
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x48, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x49, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x41, 0xB1, 0x00,                                    
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
			0xFF, 0xD0,                                                   
			0x48, 0x83, 0xC4, 0x28,                                      
			0xC3                                                        
		};

		uintptr_t Cave = Mem.CreateCodeCave(ShellCode.size());
		uintptr_t Func = g_Offsets.m_CopyVariation;

		uint64_t fact = (uint64_t)this;
		uint64_t ped_ptr = (uint64_t)ped;
		uint64_t target_ptr = (uint64_t)target;
		uint8_t  useExtra = (uint8_t)use_extra_components;

		memcpy(ShellCode.data() + 6, &fact, 8);
		memcpy(ShellCode.data() + 16, &ped_ptr, 8);
		memcpy(ShellCode.data() + 26, &target_ptr, 8);
		memcpy(ShellCode.data() + 36, &useExtra, 1);
		memcpy(ShellCode.data() + 39, &Func, 8);

		Mem.WriteBytes(Cave, ShellCode);

		HANDLE RemoteThread = CreateRemoteThread(
			Mem.ProcHandle, NULL, 0,
			(LPTHREAD_START_ROUTINE)Cave, NULL, 0, NULL
		);

		if (RemoteThread) {
			WaitForSingleObject(RemoteThread, 5000);
			CloseHandle(RemoteThread);
		}

		Mem.FreeCave(Cave);
	}
};

