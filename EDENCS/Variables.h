#pragma once
#include <set>
#include <map>
#include <unordered_map>

extern void RenderInterface();

struct skinInfo
{
	int seed = -1;
	int paintkit;
	std::string tagName;
};


struct Variables
{
	Variables()
	{

	}

	struct Ragebot_s
	{
		bool	MainSwitch;
		bool 	Enabled;
		bool 	AutoFire;
		float 	FOV;
		bool 	Silent;
		bool	AutoPistol;
		int		KeyPress;
		bool	AimStep;

		//AA Builder
		bool	BuilderAAs;
		bool	Jitter;
		bool	FJitter;
		bool	LBYBreaker;
		float	BuilderReal;
		float	BuilderFake;
		float	BuilderPitch;
		float	JitterRange;
		float	FJitterRange;


		bool	EnabledAntiAim;
		int		SubAATabs;
		bool	PreAAs;
		int		Pitch;
		int		YawTrue;
		int		YawFake;
		int		YawTrueMove;
		int		LBYDeltaReal;
		int		LBYDeltaFake;
		float	PitchAdder;
		float	YawTrueAdder;
		float	YawFakeAdder;
		float	YawFakeMove;
		bool	AtTarget;
		bool	Edge;
		bool	Rotate;
		bool	KnifeAA;
		bool	FakeLag;
		bool	flog;
		int		FakeLagAmt;
		


		bool	FriendlyFire;
		int		Hitbox;
		int		Hitscan;
		float	Pointscale;
		bool	Multipoint;
		float	Multipoints;

		bool	AntiRecoil;
		bool	AutoWall;
		bool	AutoStop;
		bool	AutoCrouch;
		bool	AutoScope;
		float	MinimumDamageSniper;
		float	MinimumDamageRifle;
		float	MinimumDamagePistol;
		float	MinimumDamageHeavy;
		float	MinimumDamageSmg;
		float	MinimumDamageRevolver;
		bool	Hitchance;
		float	HitchanceVal;
		float	MinimumDamageVal;
		bool	mindmg;
		float	HitchanceSniper;
		float	HitchancePistol;
		float	HitchanceRifle;
		float	HitchanceHeavy;
		float	HitchanceSmgs;
		float	HitchanceRevolver;
		bool	Resolver;
		bool	ExperimentalResolver;
		bool	FakeLagFix;
		bool	PosAdjust;
		bool	playerlist;
		int    FakeLagMode;
		int		BAIMkey;

		float	bruteAfterX;
		bool	MovingAA;
	} Ragebot;

	struct
	{
		bool	MainSwitch;
		bool	backtrack;
		float	backtrackTicks;
		struct
		{
			bool 	Enabled;
			bool	AutoPistol;
			bool	Resolver;

		} Aimbot;


	 

		int		hitboxrifle;
		int		MainKey = 1;
		float	MainSmooth;
		float	Mainfov;
		float	main_random_smooth;
		float	main_recoil_min;
		float	main_recoil_max;
		float	main_randomized_angle;
	
		int		hitboxpistol;
		int		PistolKey = 6;
		float	Pistolfov;
		float	PistolSmooth;
		float	pistol_random_smooth;
		float	pistol_recoil_min;
		float	pistol_recoil_max;
		float	pistol_randomized_angle;


		int		hitboxsniper;
		int		SniperKey = 6;
		float	Sniperfov;
		float	SniperSmooth;
		float	sniper_random_smooth;
		float	sniper_recoil_min;
		float	sniper_recoil_max;
		float	sniper_randomized_angle;


		struct
		{
			bool	Enabled;
			float Delay;
			int Key = 6;
			float hitchance;
			struct
			{
				bool Head;
				bool Arms;
				bool Chest;
				bool Stomach;
				bool Legs;
			} Filter;

		} Triggerbot;

	} Legitbot;

	struct
	{
		bool	TeamESP;
		bool	DroppedWeapons;
		bool	NadeLine;
		bool	NadeEnd;
		bool	backtrackcllr;
		bool	CrosshairColor;
		bool	Box;
	 
		bool	HPText;
		bool	minecraft;
		bool	grey;
		int		BoxType;
		bool	health;
		bool	Armor;
		bool	ammo;
		bool	ArmorBar;
		bool	Money;
		bool	VisCheck;
		bool	Name;
		bool	Distance;
		bool	Spec;
		bool	Skeleton;
		bool	Callout;
		bool	Weapon;
		bool	Flashed;
		bool	AimLine;
		bool	angleLines;
		bool	barrel;
		bool	DrawAwall;
		bool	DrawHealthText;
		bool	LBYIndicator;

		bool	Bomb;
		bool	resolveMode;

		bool	Droppedguns;
		bool	Grenades;
		int		GreandeI;

		int		infotab = 0;
		int		wpnmode;
		int		barrelL;
		int		chamsubtab = 0;

		bool	Chams;
		int		matierial;
		bool	outline;
		bool	Teamchams;
		int		champlayeralpha;

		bool	Chamweapon;
		bool	XQZ;

		bool	handcham;
		bool	weaponviewcham;
		int		chamhandalpha;

		int		weaponmat;
		int		handmat;
		int		weaponhandalpha;

		bool	Crosshair;
		bool	xSpread;
		bool	xRecoil;

		bool	Hitmarker = true;
		int		Hitsound = 4;

		bool	EventLog;

		bool	NoVisualRecoil;
		float	FOVChanger;
		float	viewmodelChanger = 68;
		bool	NoFlash;
		bool	NoSmoke;
		bool	NoPP;
		bool	Ccheck;
		int		TPKey;
		float	tpdist = 200;
		bool	ThirdPerson;
		bool	Time = true;

		bool	noscopeborder;
		bool	tpopacity;
		bool	GrenadePrediction;
		bool	bChamsFakeAA;

		int		glowsubtab = 0;
		bool	glowplayer;
		int		playerglowalpha;
		bool	teamglow;

		bool	weaponglow;
		int		weaponglowalpha;

		bool	bombglow;
		bool	armor;
		bool	floatingRagdolls;
		bool	FakeAngleChams;
		int		bombglowalpha;
		bool Hitbox;
		float HitboxDuration;
	} Visuals;

	struct
	{
		bool	antiuntrusted = true;
		bool	silentstealer;
		int		ragequit;
		bool 	Bhop;
		bool	MemeWalk;
		bool    ayyware;
		bool 	AutoStrafe;
		bool	Speclist;
		bool	armor;
		float	MinVel;
		int		AirStuckKey;
		float	FakeLag;
		bool	AdaptiveFakeLag;
		bool	nightMode;
		int		NameSpammer;
		bool	NameChangerFix;
		bool	NoName;
		int		ChatSpamMode;
		bool	ClantagChanger;
		int		ClanTagSpeed;
		bool	syncclantag;
		bool	SpecList;
		bool	FPSBooster;
		int		SkyBoxChanger;
		bool	namespam;
		int		spammer;
		int		AutoDefuse;
		bool	Spam;
		bool	AutoAccept;
		bool	SpoofConfirmation = false;
		bool	animatedclantag = false;
		int		fakewalkkey;
		bool	fakewalk;
		int		purchase_bot;
		bool	purchase_bot_nades; 
	} Misc;
	struct
	{
		bool Enabled;

		int knifemodel;

		int glove;
		int gloeskin;


		class WeaponCFG
		{
		public:
			bool ChangerEnabled = true;
			int ChangerSkin = 0;
			char ChangerName[32] = "geteden.us";
			int ChangerStatTrak = 1;
			int ChangerSeed = 0.0001f;
			float ChangerWear = 0.0001f;
		};
		WeaponCFG* W = new WeaponCFG[520];

		std::unordered_map<std::string, std::set<std::string>> weaponSkins;
		std::unordered_map<std::string, skinInfo> skinMap;
		std::unordered_map<std::string, std::string> skinNames;
		std::vector<std::string> weaponNames;
	} Skinchanger;

	struct
	{
		bool	Opened = false;
		bool	skinmenu;
		int 	Key;
		int		rageSubtab;
		int		legitSubtab;
		int		ConfigFile = 0;
		int		Theme = 0;
		int		iTab;
		bool	bShowTabs;
		float   flMainAlpha;
		float   flTabsAlpha;
		int currentWeapon;
	} Menu;

	struct
	{
		// 60, 120, 180
		 
		float TeamESP[3] = { 0.6f, 0.28f, 1.0f };
		float EnemyESP[3] = { 1.f, 1.f, 1.f };
		float TeamDLights[3] = { 0, 1.f, 0 };
		float EnemyDLights[3] = { 1.f, 0, 0 };
		float EnemyGlow[3] = { 1.f, 0, 0 };
		float TeamGlow[3] = { 0, 1.f, 0 };
		float WeaponGlow[3] = { 1.f, 0, 0 };
		float C4glow[3] = { 1.f, 0, 0 };
		float EnemyChamsVis[3] = { 1.f, 0, 0 };
		float EnemyChamsNVis[3] = { 1.f, 1.f, 0 };
		float TeamChamsVis[3] = { 0, 1.f, 0 };
		float TeamChamsNVis[3] = { 0, 1.f, 0 };
		float WeaponCham[3] = { 1.f, 0, 0 };
		float HandCham[3] = { 1.f, 0, 0 };
		float WeaponViewCham[3] = { 1.f, 0, 0 };
		float DroppedWeapons[3] = { 1.f, 1.f, 1.f };
		float backtrackcllr[3] = { 1.f, 1.f, 1.f };//nameclr
		float nameclr[3] = { 1.f, 1.f, 1.f };//nameclr
		float CrosshairColor[3] = { 0, 0, 0 };
		float NadeLine[3] = {0, 0.63f, 1.f};
		float NadeEnd[3] = { 1.f, 1.f, 1.f };
	}Colors;
};

extern Variables g_Options;

