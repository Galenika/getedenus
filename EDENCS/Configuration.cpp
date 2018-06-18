#include "Configuration.hpp"
#include "Variables.h"
#include <winerror.h>
#pragma warning( disable : 4091)
#include <ShlObj.h>
#include <string>
#include <sstream>
#include "XorStr.hpp"
char* colornames(int col)
{
	switch (col)
	{
	case 0:
		return "R";
		break;
	case 1:
		return "G";
		break;
	case 2:
		return "B";
		break;
	}
}

void CConfig::Setup()
{
	/*---------------------------------------------------------------------------
										Ragebot
	---------------------------------------------------------------------------*/
	SetupValue(g_Options.Ragebot.Enabled, false, ("Ragebot"), ("rbot_enabled"));
	SetupValue(g_Options.Ragebot.AutoFire, false, ("Ragebot"), ("rbot_autofire"));
	SetupValue(g_Options.Ragebot.FOV, 0.f, ("Ragebot"), ("rbot_fov"));
	SetupValue(g_Options.Ragebot.Silent, false, ("Ragebot"), ("rbot_silentaim"));
	SetupValue(g_Options.Ragebot.AutoPistol, false, ("Ragebot"), ("rbot_autopistol"));
	SetupValue(g_Options.Ragebot.KeyPress, 0, ("Ragebot"), ("rbot_key"));
	SetupValue(g_Options.Ragebot.MinimumDamageSniper, 0.f, ("Ragebot"), ("rbot_mindamage_sniper"));
	SetupValue(g_Options.Ragebot.MinimumDamagePistol, 0.f, ("Ragebot"), ("rbot_mindamage_pistol"));
	SetupValue(g_Options.Ragebot.MinimumDamageRifle, 0.f, ("Ragebot"), ("rbot_mindamage_rifle"));
	SetupValue(g_Options.Ragebot.MinimumDamageHeavy, 0.f, ("Ragebot"), ("rbot_mindamage_heavy"));
	SetupValue(g_Options.Ragebot.MinimumDamageSmg, 0.f, ("Ragebot"), ("rbot_mindamage_smg"));
	SetupValue(g_Options.Ragebot.MinimumDamageRevolver, 0.f, ("Ragebot"), ("rbot_mindamage_revolver_deag"));
	SetupValue(g_Options.Ragebot.Hitchance, false, ("Ragebot"), ("rbot_hitchance_enabled"));
	SetupValue(g_Options.Ragebot.HitchanceSniper, 0.f, ("Ragebot"), ("rbot_hitchance_sniper"));
	SetupValue(g_Options.Ragebot.HitchancePistol, 0.f, ("Ragebot"), ("rbot_hitchance_pistol"));
	SetupValue(g_Options.Ragebot.HitchanceHeavy, 0.f, ("Ragebot"), ("rbot_hitchance_heavy"));
	SetupValue(g_Options.Ragebot.HitchanceSmgs, 0.f, ("Ragebot"), ("rbot_hitchance_smg"));
	SetupValue(g_Options.Ragebot.HitchanceRifle, 0.f, ("Ragebot"), ("rbot_hitchance_rifle"));
	SetupValue(g_Options.Ragebot.HitchanceRevolver, 0.f, ("Ragebot"), ("rbot_hitchance_revolver_deag"));

	SetupValue(g_Options.Ragebot.EnabledAntiAim, false, ("Ragebot"), ("rbot_antiaim_enabled"));
	SetupValue(g_Options.Ragebot.PreAAs, false, ("Ragebot"), ("Pre-set-AAs"));
	SetupValue(g_Options.Ragebot.Pitch, 0, ("Ragebot"), ("rbot_antiaim_pitch"));
	SetupValue(g_Options.Ragebot.YawTrue, 0, ("Ragebot"), ("rbot_antiaim_yaw_real"));
	SetupValue(g_Options.Ragebot.LBYDeltaReal, 0, ("Ragebot"), ("rbot_antiaim_delta"));
	SetupValue(g_Options.Ragebot.YawFake, 0, ("Ragebot"), ("rbot_antiaim_fake"));
	SetupValue(g_Options.Ragebot.AtTarget, false, ("Ragebot"), ("rbot_antiaim_attargets"));
	SetupValue(g_Options.Ragebot.Edge, false, ("Ragebot"), ("rbot_antiaim_edge"));
	SetupValue(g_Options.Ragebot.BuilderAAs, false, ("Ragebot"), ("rbot_builder_enabled"));
	SetupValue(g_Options.Ragebot.FakeLag, false, ("Ragebot"), ("rbot_fakelag_enabled"));
	SetupValue(g_Options.Ragebot.FakeLagAmt, 0, ("Ragebot"), ("rbot_fakelag_amt"));


	SetupValue(g_Options.Ragebot.FriendlyFire, false, ("Ragebot"), ("rbot_friendlyfire"));
	SetupValue(g_Options.Ragebot.Hitbox, 0, ("Ragebot"), ("rbot_hitbox"));
	SetupValue(g_Options.Ragebot.Hitscan, 0, ("Ragebot"), ("rbot_hitscan"));

	SetupValue(g_Options.Ragebot.AntiRecoil, false, ("Ragebot"), ("rbot_antirecoil"));
	SetupValue(g_Options.Ragebot.AutoStop, false, ("Ragebot"), ("rbot_autostop"));
	SetupValue(g_Options.Ragebot.AutoCrouch, false, ("Ragebot"), ("rbot_autocrouch"));
	SetupValue(g_Options.Ragebot.AutoScope, false, ("Ragebot"), ("rbot_autoscope"));
	SetupValue(g_Options.Ragebot.MinimumDamageVal, 0.f, ("Ragebot"), ("rbot_mindmg_sniper"));
	SetupValue(g_Options.Ragebot.HitchanceVal, 0.f, ("Ragebot"), ("rbot_hitchance_value"));
	SetupValue(g_Options.Ragebot.Hitchance, false, ("Ragebot"), ("rbot_hitchance"));
	SetupValue(g_Options.Ragebot.mindmg, false, ("Ragebot"), ("rbot_mindmg_enabled"));
	SetupValue(g_Options.Ragebot.Resolver, false, ("Ragebot"), ("rbot_resolver"));
	SetupValue(g_Options.Ragebot.PosAdjust, false, ("Ragebot"), ("rbot_position_adjustment"));
	SetupValue(g_Options.Ragebot.BAIMkey, 0, ("Ragebot"), ("BAIMKey"));

	/*---------------------------------------------------------------------------
										Legitbot
	---------------------------------------------------------------------------*/
	SetupValue(g_Options.Legitbot.MainSwitch, false, ("Legitbot"), ("lbot_enabled"));
	SetupValue(g_Options.Legitbot.Aimbot.Enabled, false, ("Legitbot"), ("lbot_enabled"));
	SetupValue(g_Options.Legitbot.backtrack, false, ("Legitbot"), ("lbot_backtrack"));
	SetupValue(g_Options.Legitbot.backtrackTicks, 0, ("Legitbot"), ("lbot_ticks"));


	SetupValue(g_Options.Legitbot.MainKey, 1, ("Legitbot"), ("lbot_key"));
	SetupValue(g_Options.Legitbot.Mainfov, 0.f, ("Legitbot"), ("lbot_fov"));
	SetupValue(g_Options.Legitbot.MainSmooth, 1.f, ("Legitbot"), ("lbot_speed"));
	SetupValue(g_Options.Legitbot.main_recoil_min, 0, ("Legitbot"), ("lbot_rcsmin"));
	SetupValue(g_Options.Legitbot.main_recoil_max, 0, ("Legitbot"), ("lbot_rcsmax"));

	SetupValue(g_Options.Legitbot.PistolKey, 6, ("Legitbot"), ("lbot_pistol_key"));
	SetupValue(g_Options.Legitbot.Pistolfov, 0.f, ("Legitbot"), ("lbot_pistol_fov"));
	SetupValue(g_Options.Legitbot.PistolSmooth, 1.f, ("Legitbot"), ("lbot_pistol_speed"));
	SetupValue(g_Options.Legitbot.pistol_recoil_min, 0, ("Legitbot"), ("lbot_pistol_rcsmin"));
	SetupValue(g_Options.Legitbot.pistol_recoil_max, 0, ("Legitbot"), ("lbot_pistol_rcsmax"));

	SetupValue(g_Options.Legitbot.SniperKey, 6, ("Legitbot"), ("lbot_sniper_key"));
	SetupValue(g_Options.Legitbot.Sniperfov, 0.f, ("Legitbot"), ("lbot_sniper_fov"));
	SetupValue(g_Options.Legitbot.SniperSmooth, 0.f, ("Legitbot"), ("lbot_sniper_speed"));
	SetupValue(g_Options.Legitbot.sniper_recoil_min, 0, ("Legitbot"), ("lbot_sniper_rcsmin"));
	SetupValue(g_Options.Legitbot.sniper_recoil_max, 0, ("Legitbot"), ("lbot_sniper_rcsmax"));

	SetupValue(g_Options.Legitbot.Triggerbot.Enabled, false, ("Triggerbot"), ("lbot_trigger_enabled"));
	SetupValue(g_Options.Legitbot.Triggerbot.Key, 6, ("Triggerbot"), ("lbot_trigger_key"));
	SetupValue(g_Options.Legitbot.Triggerbot.Delay, 0.f, ("Triggerbot"), ("lbot_trigger_delay"));
	SetupValue(g_Options.Legitbot.Triggerbot.hitchance, 0.f, ("Triggerbot"), ("lbot_trigger_hitchance"));

	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Head, false, ("Triggerbot"), ("lbot_trigger_filter_head"));
	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Chest, false, ("Triggerbot"), ("lbot_trigger_filter_chest"));
	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Stomach, false, ("Triggerbot"), ("lbot_trigger_filter_stomach"));
	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Arms, false, ("Triggerbot"), ("lbot_trigger_filter_arms"));
	SetupValue(g_Options.Legitbot.Triggerbot.Filter.Legs, false, ("Triggerbot"), ("lbot_trigger_filter_legs"));
	/*---------------------------------------------------------------------------
									Visuals
	---------------------------------------------------------------------------*/
	SetupValue(g_Options.Visuals.Box, false, ("Visuals"), ("vis_box"));
	SetupValue(g_Options.Visuals.BoxType, 0, ("Visuals"), ("vis_box_type"));
	SetupValue(g_Options.Visuals.Name, false, ("Visuals"), ("vis_name"));
	SetupValue(g_Options.Visuals.health, false, ("Visuals"), ("vis_health"));
	SetupValue(g_Options.Visuals.Weapon, false, ("Visuals"), ("vis_weapon"));
	SetupValue(g_Options.Visuals.wpnmode, 0, ("Visuals"), ("vis_weapontype"));
	SetupValue(g_Options.Visuals.Chams, false, ("Visuals"), ("vis_chams"));
	SetupValue(g_Options.Visuals.Skeleton, false, ("Visuals"), ("vis_skeleton"));
	SetupValue(g_Options.Visuals.TeamESP, false, ("Visuals"), ("vis_team"));
	SetupValue(g_Options.Visuals.Grenades, false, ("Visuals"), ("vis_grenade"));
	SetupValue(g_Options.Visuals.Grenades, 0, ("Visuals"), ("vis_grenade_string"));
	SetupValue(g_Options.Visuals.AimLine, false, ("Visuals"), ("vis_aimlines"));
	SetupValue(g_Options.Visuals.ammo, false, ("Visuals"), "vis_ammo");
	SetupValue(g_Options.Visuals.NoVisualRecoil, false, ("Visuals"), ("vis_novisualrecoil"));
	SetupValue(g_Options.Visuals.Hitmarker, false, ("Visuals"), ("vis_hitmarker"));
	SetupValue(g_Options.Visuals.Hitsound, 0, ("Visuals"), ("vis_hitsound"));
	SetupValue(g_Options.Visuals.tpopacity, 0, ("Visuals"), ("vis_scope_opacity"));
	SetupValue(g_Options.Visuals.FOVChanger, 0.f, ("Visuals"), ("vis_fovchanger"));
	SetupValue(g_Options.Visuals.viewmodelChanger, 68.f, ("Visuals"), ("vis_viewmodel_fov"));
	SetupValue(g_Options.Visuals.NoFlash, false, ("Visuals"), ("vis_noflash"));
	SetupValue(g_Options.Visuals.NoSmoke, false, ("Visuals"), ("vis_nosmoke")); 
	SetupValue(g_Options.Visuals.NoPP, false, ("Visuals"), ("vis_nopostprocess"));
	SetupValue(g_Options.Visuals.Time, false, ("Visuals"), ("vis_lbytimer"));
	SetupValue(g_Options.Visuals.noscopeborder, false, ("Visuals"), ("vis_noscope"));
	SetupValue(g_Options.Visuals.Droppedguns, false, ("Visuals"), ("vis_dropped_weapons"));
	SetupValue(g_Options.Visuals.GrenadePrediction, false, ("Visuals"), ("vis_grenade_prediction"));
	SetupValue(g_Options.Visuals.TPKey, false, ("Visuals"), ("vis_thirdperson_key"));
	SetupValue(g_Options.Visuals.ThirdPerson, false, ("Visuals"), ("vis_thirdperson"));
	SetupValue(g_Options.Visuals.Callout, false, ("Visuals"), ("vis_callout"));
	SetupValue(g_Options.Visuals.armor, false, ("Visuals"), ("vis_armor"));
	SetupValue(g_Options.Visuals.Flashed, false, ("Visuals"), ("vis_flags"));
	SetupValue(g_Options.Visuals.Distance, false, ("Visuals"), ("vis_distance"));
	SetupValue(g_Options.Visuals.Money, false, ("Visuals"), ("vis_money"));
	SetupValue(g_Options.Visuals.resolveMode, false, ("Visuals"), ("vis_resolve_mode"));
	SetupValue(g_Options.Visuals.Chams, false, ("Visuals"), ("vis_playerchams"));
	SetupValue(g_Options.Visuals.Teamchams, false, ("Visuals"), ("vis_teamchams"));
	SetupValue(g_Options.Visuals.Chamweapon, false, ("Visuals"), ("vis_weaponchams"));
	SetupValue(g_Options.Visuals.XQZ, false, ("Visuals"), ("vis_xqzchams"));
	SetupValue(g_Options.Visuals.champlayeralpha, 0, ("Visuals"), ("vis_cham_alpha"));
	SetupValue(g_Options.Visuals.matierial, 0, ("Visuals"), ("vis_cham_material"));
	/*
	SetupValue(g_Options.Visuals.glowplayer, false, ("Visuals"), ("vis_glow"));
	SetupValue(g_Options.Visuals.teamglow, false, ("Visuals"), ("vis_glowteam"));
	SetupValue(g_Options.Visuals.playerglowalpha, 0, ("Visuals"), ("vis_glowalpha"));
	SetupValue(g_Options.Visuals.weaponglow, false, ("Visuals"), ("vis_weaponglow"));
	SetupValue(g_Options.Visuals.weaponglowalpha, 0, ("Visuals"), ("vis_weaponglowalpha"));
	SetupValue(g_Options.Visuals.bombglow, false, ("Visuals"), ("vis_bombglow"));
	SetupValue(g_Options.Visuals.bombglowalpha, 0, ("Visuals"), ("vis_bombglowalpha"));
	*/
	SetupValue(g_Options.Visuals.angleLines, false, ("Visuals"), ("vis_anglelines"));
	SetupValue(g_Options.Visuals.LBYIndicator, false, ("Visuals"), ("vis_lbyindicator"));
	SetupValue(g_Options.Visuals.DrawAwall, false, ("Visuals"), ("vis_autowallindicator"));
	SetupValue(g_Options.Visuals.HPText, false, ("Visuals"), ("vis_healthtext"));
	SetupValue(g_Options.Visuals.grey, false, ("Visuals"), ("vis_graymode"));
	SetupValue(g_Options.Visuals.minecraft, false, ("Visuals"), ("vis_minecraftmode"));
	SetupValue(g_Options.Misc.nightMode, false, ("Visuals"), ("vis_nightmode"));
	SetupValue(g_Options.Visuals.Bomb, false, ("Visuals"), ("vis_bombesp"));
	SetupValue(g_Options.Visuals.Crosshair, false, ("Visuals"), ("vis_spreadcrosshair"));
	SetupValue(g_Options.Visuals.floatingRagdolls, false, ("Visuals"), ("vis_floatingragdolls"));

	/*---------------------------------------------------------------------------
										Misc
	---------------------------------------------------------------------------*/
	SetupValue(g_Options.Misc.Bhop, false, ("Misc"), ("misc_bhop"));
	SetupValue(g_Options.Misc.SpecList, false, ("Misc"), ("misc_spectatorlist"));
	SetupValue(g_Options.Misc.AutoStrafe, false, ("Misc"), ("misc_autostrafe"));
	SetupValue(g_Options.Misc.syncclantag, false, ("Misc"), ("misc_clangtag"));
	SetupValue(g_Options.Misc.fakewalk, false, ("Misc"), ("misc_fakewalk"));
	SetupValue(g_Options.Misc.fakewalkkey, false, ("Misc"), ("misc_fakewalk_key"));
	SetupValue(g_Options.Misc.purchase_bot_nades, false, ("Misc"), ("misc_purchase_bot_extras"));
	SetupValue(g_Options.Misc.purchase_bot, 0, ("Misc"), ("misc_purchase_bot"));
 
}

void CConfig::SetupValue(int &value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValue<int>(category, name, &value));
}

void CConfig::SetupValue(float &value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue<float>(category, name, &value));
}

void CConfig::SetupValue(bool &value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValue<bool>(category, name, &value));
}

void CConfig::Save()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
	{


		folder = std::string(path) + ("\\eden\\");
		switch (g_Options.Menu.ConfigFile)
		{
		case 0:
			file = std::string(path) + ("\\eden\\") + std::string("Legit") + XorStr(".cfg");
			break;
		case 1:
			file = std::string(path) + ("\\eden\\") + std::string("Rage") + XorStr(".cfg");
			break;
		case 2:
			file = std::string(path) + ("\\eden\\") + std::string("HvH") + XorStr(".cfg");
			break;
		case 3:
			file = std::string(path) + ("\\eden\\") + std::string("Other") + XorStr(".cfg");
			break;
		}

	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::Load()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
	{
		folder = std::string(path) + ("\\eden\\");
		switch (g_Options.Menu.ConfigFile)
		{
		case 0:
			file = std::string(path) + ("\\eden\\") + std::string("Legit") + XorStr(".cfg");;
			break;
		case 1:
			file = std::string(path) + ("\\eden\\") + std::string("Rage") + XorStr(".cfg");;
			break;
		case 2:
			file = std::string(path) + ("\\eden\\") + std::string("HvH") + XorStr(".cfg");;
			break;
		case 3:
			file = std::string(path) + ("\\eden") + std::string("Other") + XorStr(".cfg");;
			break;
		}
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = (float)atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

CConfig* Config = new CConfig();
Variables g_Options;

