#pragma once
#include "Configuration.hpp"
#include "dropboxes.h"
#include "Variables.h"
#include "Themes.h"
#include <cctype>
#include "Logging.h"
#include "Listener.h"


#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#define BUILDSTAMP ( __DATE__ )
typedef void(*CL_FullUpdate_t) (void);
CL_FullUpdate_t CL_FullUpdate = nullptr;

void FullUpdate()
{
	static auto CL_FullUpdate = reinterpret_cast<CL_FullUpdate_t>(U::FindPattern("engine.dll", reinterpret_cast<PBYTE>("\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x56\xFF\x50\x14\x8B\x34\x85"), "x????x????xxxxxxx"));
	CL_FullUpdate();

}

void  setName(const char* name)
{
	static ConVar* namevar = g_CVar->FindVar("name");
	*reinterpret_cast< int* >(reinterpret_cast< DWORD >(&namevar->fnChangeCallback) + 0xC) = NULL;
	namevar->SetValue(name);
}



const char* weaponnames(int id)
{
	switch (id)
	{
	case 1:
		return "deagle";
	case 2:
		return "elite";
	case 3:
		return "fiveseven";
	case 4:
		return "glock";
	case 7:
		return "ak47";
	case 8:
		return "aug";
	case 9:
		return "awp";
	case 10:
		return "famas";
	case 11:
		return "g3sg1";
	case 13:
		return "galilar";
	case 14:
		return "m249";
	case 60:
		return "m4a1_silencer";
	case 16:
		return "m4a1";
	case 17:
		return "mac10";
	case 19:
		return "p90";
	case 24:
		return "ump45";
	case 25:
		return "xm1014";
	case 26:
		return "bizon";
	case 27:
		return "mag7";
	case 28:
		return "negev";
	case 29:
		return "sawedoff";
	case 30:
		return "tec9";
	case 32:
		return "hkp2000";
	case 33:
		return "mp7";
	case 34:
		return "mp9";
	case 35:
		return "nova";
	case 36:
		return "p250";
	case 38:
		return "scar20";
	case 39:
		return "sg556";
	case 40:
		return "ssg08";
	case 61:
		return "usp_silencer";
	case 63:
		return "cz75a";
	case 64:
		return "revolver";
	case 508:
		return "knife_m9_bayonet";
	case 500:
		return "bayonet";
	case 505:
		return "knife_flip";
	case 506:
		return "knife_gut";
	case 507:
		return "knife_karambit";
	case 509:
		return "knife_tactical";
	case 512:
		return "knife_falchion";
	case 514:
		return "knife_survival_bowie";
	case 515:
		return "knife_butterfly";
	case 516:
		return "knife_push";

	default:
		return "";
	}
}

bool IsUtility(ItemDefinitionIndexx index)
{
	switch (index)
	{
	case ItemDefinitionIndexx::ITEM_NONE:
	case ItemDefinitionIndexx::WEAPON_C4:
	case ItemDefinitionIndexx::WEAPON_FLASH:
	case ItemDefinitionIndexx::WEAPON_HE:
	case ItemDefinitionIndexx::WEAPON_INC:
	case ItemDefinitionIndexx::WEAPON_MOLOTOV:
	case ItemDefinitionIndexx::WEAPON_SMOKE:
	case ItemDefinitionIndexx::WEAPON_DECOY:
	case ItemDefinitionIndexx::WEAPON_KNIFE_T:
	case ItemDefinitionIndexx::WEAPON_KNIFE_CT:
	case ItemDefinitionIndexx::GLOVE_T_SIDE:
	case ItemDefinitionIndexx::GLOVE_CT_SIDE:
	case ItemDefinitionIndexx::GLOVE_SPORTY:
	case ItemDefinitionIndexx::GLOVE_SLICK:
	case ItemDefinitionIndexx::GLOVE_LEATHER_WRAP:
	case ItemDefinitionIndexx::GLOVE_STUDDED_BLOODHOUND:
	case ItemDefinitionIndexx::GLOVE_MOTORCYCLE:
	case ItemDefinitionIndexx::GLOVE_SPECIALIST:
	case ItemDefinitionIndexx::GLOVE_HYDRA:
		return true;
	default:
		return false;
	}
}

bool Contains(const std::string &word, const std::string &sentence) {
	if (word == "" || sentence == "")
		return true;

	return sentence.find(word) != std::string::npos;
}

std::string ToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), (int(*)(int))std::tolower);

	return str;
}
/*----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
bool defaultk;
bool bayonet;
bool flip;
bool gut;
bool karambit;
bool m9bayonet;
bool huntsman;
bool falchion;
bool bowie;
bool butterfly;
bool daggers;

void doknives(bool* disknife)
{
	defaultk = false;
	bayonet = false;
	flip = false;
	gut = false;
	karambit = false;
	m9bayonet = false;
	huntsman = false;
	falchion = false;
	bowie = false;
	butterfly = false;
	daggers = false;

	*disknife = true;
}

const char* HitmarkSound[] =
{
	"disabled",
	"default",
	"metallic"
};

void uninject()
{


	if (VK_DELETE) // dont forget to remove this (used for when the menu fucks up)
	{
		g_Engine->ClientCmd_Unrestricted("cl_mouseenable 1");
		unload = true;
		Sleep(1000);
		FullUpdate();
	}
}

int tab = 1;





void RenderInterface() {


	auto& style = ImGui::GetStyle();
	bool is_renderer_active = renderer->IsActive();
	if (&g_Options.Menu.Opened && style.Alpha < 1.f)
	{
		g_Options.Menu.Opened = true;
		if (style.Alpha > 1.f)
			style.Alpha = 1.f;
		else if (style.Alpha != 1.f)
			style.Alpha += 0.03f;
	}
	else if (style.Alpha > 0.f)
	{
		if (style.Alpha < 0.f)
			style.Alpha = 0.f;
		else if (style.Alpha != 0.f)
			style.Alpha -= 0.03f;
		if (style.Alpha == 0.f)
			g_Options.Menu.Opened = false;
	}


	ImGui::Begin("dork.cc", &g_Options.Menu.Opened, ImVec2(890, 600), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::BeginChild("first child", ImVec2(150, 505), true);
	{
		style.Colors[ImGuiCol_Button] = ImVec4(0, 0, 0, 0);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0, 0, 0, 0);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0, 0, 0, 0);

		ImGui::PushFont(fTabs);
		if (ImGui::Button("ragebot", ImVec2(130, 45)))
		{
			tab = 1;
		}
		if (ImGui::Button("legitbot", ImVec2(130, 45)))
		{
			tab = 6;
		}
		if (ImGui::Button("visual", ImVec2(130, 45)))
		{
			tab = 2;
		}

		if (ImGui::Button("miscellaneous", ImVec2(130, 45)))
		{
			tab = 3;
		}
		if (ImGui::Button("configuration", ImVec2(130, 45)))
		{
			tab = 4;
		}
		if (ImGui::Button("skins", ImVec2(130, 45)))
		{
			tab = 5;
		}
		ImGui::PopFont();

	}ImGui::EndChild();
	ImGui::SameLine();
	ImGui::PushItemWidth(-1);
	ImGui::PushFont(fDefault);
	/* Tab Contents -
	*****************
	|	1 - Rage	|
	|	2 - Visual	|
	|	3 - Misc	|
	|	4 - Config	|
	|	5 - Skins	|
	|	6 - Legit	|
	***************** */
	/*----------------------------------------------------------------------------------*/
	/*——	  While changing the tabs i messed up, so its out of order but /shrug	  ——*/
	/*----------------------------------------------------------------------------------*/
	/*									      TABS									    */
	/*----------------------------------------------------------------------------------*/

	if (tab == 1) // aimbot
	{
		ImGui::BeginChild("mega child", ImVec2(620, 505), true);
		{
			ImGui::Columns(2, "yes", false);
			ImGui::Text("aimbot");
			ImGui::BeginChild("Aimbot", ImVec2(246, 294), true);
			{
				ImGui::PushItemWidth(200);
				ImGui::Checkbox(XorStr("enabled"), &g_Options.Ragebot.Enabled);
				ImGui::Checkbox(XorStr("automatic fire"), &g_Options.Ragebot.AutoFire);
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("field of view"), &g_Options.Ragebot.FOV, 1.f, 180.f, "%.0f");
				ImGui::Checkbox(XorStr("silent aim"), &g_Options.Ragebot.Silent);
				ImGui::Checkbox(XorStr("automatic pistol"), &g_Options.Ragebot.AutoPistol);
				ImGui::Text("target hitbox");
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::Combo(XorStr("##hitbox"), &g_Options.Ragebot.Hitbox, aimBones, ARRAYSIZE(aimBones));
				ImGui::Text("target hitscan");
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::Combo(XorStr("##hitscan"), &g_Options.Ragebot.Hitscan, hitscan, ARRAYSIZE(hitscan));
				ImGui::Checkbox(XorStr("minimum damage"), &g_Options.Ragebot.mindmg);
				if (g_Options.Ragebot.mindmg)
				{
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::SliderFloat(("snipers##sniper"), &g_Options.Ragebot.MinimumDamageSniper, 1.f, 100.f, "%.2f");
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::SliderFloat(("rifles##rifle"), &g_Options.Ragebot.MinimumDamageRifle, 1.f, 100.f, "%.2f");
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::SliderFloat(("pistols##pistol"), &g_Options.Ragebot.MinimumDamagePistol, 1.f, 100.f, "%.2f");
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::SliderFloat(("heavies##heavy"), &g_Options.Ragebot.MinimumDamageHeavy, 1.f, 100.f, "%.2f");
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::SliderFloat(("smgs##smg"), &g_Options.Ragebot.MinimumDamageSmg, 1.f, 100.f, "%.2f");
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::SliderFloat(("deagle##deagandrevol"), &g_Options.Ragebot.MinimumDamageRevolver, 1.f, 100.f, "%.2f");
				}
				ImGui::Checkbox(XorStr("hitchance"), &g_Options.Ragebot.Hitchance);
				if (g_Options.Ragebot.Hitchance)
				{
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::SliderFloat(XorStr("snipers"), &g_Options.Ragebot.HitchanceSniper, 0.f, 100.f, "%.1f");
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::SliderFloat(XorStr("rifles"), &g_Options.Ragebot.HitchanceRifle, 0.f, 100.f, "%.1f");
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::SliderFloat(XorStr("pistols"), &g_Options.Ragebot.HitchancePistol, 0.f, 100.f, "%.1f");
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::SliderFloat(XorStr("smgs"), &g_Options.Ragebot.HitchanceSmgs, 0.f, 100.f, "%.1f");
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::SliderFloat(XorStr("heavies"), &g_Options.Ragebot.HitchanceHeavy, 0.f, 100.f, "%.1f");
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::SliderFloat(XorStr("deagle"), &g_Options.Ragebot.HitchanceRevolver, 0.f, 100.f, "%.1f");
				}
			}ImGui::EndChild();
			ImGui::Text("fake-lag");
			ImGui::BeginChild("##fakelag", ImVec2(246, 150), true);
			{
				ImGui::PushItemWidth(200);
				ImGui::Checkbox(("enable fake-lag"), &g_Options.Ragebot.FakeLag);
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::SliderInt(("##Fakelag"), &g_Options.Ragebot.FakeLagAmt, 1.f, 15.f);
			}ImGui::EndChild();
			ImGui::NextColumn();
			ImGui::Text("other");
			ImGui::BeginChild("other", ImVec2(246, 199), true);
			{
				ImGui::Checkbox(XorStr("anti-aim resolver"), &g_Options.Ragebot.Resolver);
				ImGui::Checkbox(XorStr("position adjustment"), &g_Options.Ragebot.PosAdjust);
				ImGui::Checkbox(XorStr("fake-lag correction"), &g_Options.Ragebot.FakeLagFix);
				ImGui::Checkbox(XorStr("compensate recoil"), &g_Options.Ragebot.AntiRecoil);
				ImGui::Checkbox(XorStr("automatic stop"), &g_Options.Ragebot.AutoStop);
				ImGui::Checkbox(XorStr("automatic crouch"), &g_Options.Ragebot.AutoCrouch);
				ImGui::Checkbox(XorStr("automatic scope"), &g_Options.Ragebot.AutoScope);
			}ImGui::EndChild();

			ImGui::Text("anti-aimbot");
			ImGui::BeginChild("antiaim", ImVec2(246, 245), true);
			{
				ImGui::PushItemWidth(200);
				ImGui::Checkbox(XorStr("anti-aim enabled"), &g_Options.Ragebot.EnabledAntiAim);
				ImGui::Text("pitch");
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::Combo(XorStr("##pitch"), &g_Options.Ragebot.Pitch, antiaimpitch, ARRAYSIZE(antiaimpitch));
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("pitch add: "), &g_Options.Ragebot.PitchAdder, -180, 180, "%1.f");
				ImGui::Text("yaw");
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::Combo(XorStr("##yaw"), &g_Options.Ragebot.YawTrue, antiaimyawtrue, ARRAYSIZE(antiaimyawtrue));
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("real add: "), &g_Options.Ragebot.YawTrueAdder, -180, 180, "%1.f");
				ImGui::Text("fake");
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::Combo(XorStr("##fake"), &g_Options.Ragebot.YawFake, antiaimyawfake, ARRAYSIZE(antiaimyawfake));
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("fake add: "), &g_Options.Ragebot.YawFakeAdder, -180, 180, "%1.f");
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::SliderInt(XorStr("lby delta: "), &g_Options.Ragebot.LBYDeltaReal, -180, 180, "%1.f");
				ImGui::Checkbox(XorStr("edge"), &g_Options.Ragebot.Edge);
#ifdef Bread
				ImGui::Checkbox(XorStr("rotate in air"), &g_Options.Ragebot.Rotate);
#endif // Bread


			}ImGui::EndChild();
		}ImGui::EndChild();
	}
	if (tab == 2)
	{
		ImGui::BeginChild("fourth child", ImVec2(620, 505), true);
		{
			ImGui::Columns(2, "gangster", false);
			ImGui::Text("esp main");
			ImGui::BeginChild("esp-main", ImVec2(246, 294), true);
			{
				ImGui::PushItemWidth(200);
				ImGui::Checkbox(XorStr("team esp"), &g_Options.Visuals.TeamESP);
				ImGui::SameLine();
				ImGui::MyColorEdit3("##ESP", g_Options.Colors.TeamESP, 1 << 7);
				ImGui::Checkbox(XorStr("box"), &g_Options.Visuals.Box);
				ImGui::SameLine();
				ImGui::MyColorEdit3("##EdddSP", g_Options.Colors.EnemyESP, 1 << 7);
				if (g_Options.Visuals.Box)
				{
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::Combo("##boxkek", &g_Options.Visuals.BoxType, "rectangle\0\redges\0\r3d\0\0", -1);
				}
				ImGui::Checkbox(XorStr("skeleton"), &g_Options.Visuals.Skeleton);
				ImGui::Checkbox(XorStr("name"), &g_Options.Visuals.Name);
				ImGui::SameLine();
				ImGui::MyColorEdit3("##NAMECLR", g_Options.Colors.nameclr, 1 << 7);
				ImGui::Checkbox(XorStr("weapon"), &g_Options.Visuals.Weapon);
				if (g_Options.Visuals.Weapon)
				{
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::Combo("##wpnkek", &g_Options.Visuals.wpnmode, "name\0\ricon\0\0", -1);
				}
				ImGui::Checkbox(XorStr("health"), &g_Options.Visuals.health);
				ImGui::NewLine();
				ImGui::SameLine(28);
				ImGui::Checkbox(XorStr("hp text"), &g_Options.Visuals.HPText);
				ImGui::Checkbox(XorStr("flags"), &g_Options.Visuals.Armor);
				ImGui::Checkbox(XorStr("armor"), &g_Options.Visuals.armor);
				ImGui::Checkbox(XorStr("ammo"), &g_Options.Visuals.ammo);
				ImGui::Checkbox(XorStr("money"), &g_Options.Visuals.Money);
				ImGui::Checkbox(XorStr("callout"), &g_Options.Visuals.Callout);
				ImGui::Checkbox(XorStr("distance"), &g_Options.Visuals.Distance);
				ImGui::Checkbox(XorStr("snap lines"), &g_Options.Visuals.AimLine);
			}ImGui::EndChild();

			ImGui::Text("chams");
			ImGui::BeginChild("esp-chams", ImVec2(246, 150), true);
			{
				ImGui::PushItemWidth(200);
				ImGui::Checkbox(XorStr("cham players"), &g_Options.Visuals.Chams);
				ImGui::SameLine();

				ImGui::MyColorEdit3("##45ESP", g_Options.Colors.EnemyChamsVis, 1 << 7);
				ImGui::Checkbox(XorStr("cham team"), &g_Options.Visuals.Teamchams);
				ImGui::SameLine();
				ImGui::MyColorEdit3("##E772SP", g_Options.Colors.TeamChamsVis, 1 << 7);
				ImGui::Checkbox(XorStr("through walls"), &g_Options.Visuals.XQZ);
				ImGui::SameLine();
				ImGui::MyColorEdit3("##43ESP", g_Options.Colors.EnemyChamsNVis, 1 << 7);
				ImGui::PushItemWidth(200);
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::SliderInt(XorStr(" ##pca"), &g_Options.Visuals.champlayeralpha, 0, 100);
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::Combo("##sdgl", &g_Options.Visuals.matierial, "normal\0\rflat\0\rwireframe\0\rglass\0\rgold\0\rplatinum\0\rplastic\0\rcrystal\0\0", -1);
			}ImGui::EndChild();
			ImGui::NextColumn();
			ImGui::Text("other");
			ImGui::BeginChild("esp-other", ImVec2(246, 199), true);
			{
				ImGui::PushItemWidth(200);
				ImGui::Checkbox(XorStr("bomb esp"), &g_Options.Visuals.Bomb);
				ImGui::Checkbox(XorStr("grenades"), &g_Options.Visuals.Grenades);
				ImGui::Combo("##grenade", &g_Options.Visuals.GreandeI, "off\0\rtext\0\ricon\0\0", -1);
				ImGui::Checkbox(XorStr("resolve mode"), &g_Options.Visuals.resolveMode);
				ImGui::Checkbox(XorStr("dropped weapons"), &g_Options.Visuals.Droppedguns);
				ImGui::SameLine();
				ImGui::MyColorEdit3("##DROPFGTS", g_Options.Colors.DroppedWeapons, 1 << 7);
				ImGui::Checkbox(XorStr("anti-aim lines"), &g_Options.Visuals.angleLines);
				ImGui::Checkbox(XorStr("wallbang damage"), &g_Options.Visuals.DrawAwall);
				ImGui::Checkbox(XorStr("lby indicator"), &g_Options.Visuals.Time);
				ImGui::Checkbox(XorStr("grenade line"), &g_Options.Visuals.GrenadePrediction);
				ImGui::SameLine();
				ImGui::MyColorEdit3("##NADELN", g_Options.Colors.NadeLine, 1 << 7);
				ImGui::SameLine();
				ImGui::MyColorEdit3("##NADEEND", g_Options.Colors.NadeEnd, 1 << 7);
				ImGui::Checkbox(XorStr("spread crosshair"), &g_Options.Visuals.Crosshair);
				ImGui::SameLine();
				ImGui::MyColorEdit3("##CHCOLOR", g_Options.Colors.CrosshairColor, 1 << 7);
				ImGui::Checkbox(XorStr("spectator list"), &g_Options.Misc.SpecList);
			}ImGui::EndChild();
			ImGui::Text("effects");
			ImGui::BeginChild("esp-effects", ImVec2(246, 245), true);
			{
				ImGui::PushItemWidth(200);
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("fov"), &g_Options.Visuals.FOVChanger, 0, 60, "%.0f");
				ImGui::NewLine();
				ImGui::SameLine();
				ImGui::SliderFloat(XorStr("viewmodel fov"), &g_Options.Visuals.viewmodelChanger, 68, 140, "%.0f");
				ImGui::Checkbox(XorStr("force thirdperson"), &g_Options.Visuals.ThirdPerson);
				if (g_Options.Visuals.ThirdPerson)
				{
					ImGui::NewLine();
					ImGui::SameLine();
					ImGui::Hotkey(XorStr("##key"), &g_Options.Visuals.TPKey);
				}
				ImGui::Checkbox(XorStr("night mode"), &g_Options.Misc.nightMode);
				ImGui::Checkbox(XorStr("gray mode"), &g_Options.Visuals.grey);
				ImGui::Checkbox(XorStr("minecraft mode"), &g_Options.Visuals.minecraft);
				ImGui::Checkbox(XorStr("floating ragdolls"), &g_Options.Visuals.floatingRagdolls);
				ImGui::Checkbox(XorStr("scope opacity"), &g_Options.Visuals.tpopacity);
				ImGui::Checkbox(XorStr("remove smokes"), &g_Options.Visuals.NoSmoke);
				ImGui::Checkbox(XorStr("remove flashes"), &g_Options.Visuals.NoFlash);
				ImGui::Checkbox(XorStr("remove scope"), &g_Options.Visuals.noscopeborder);
				ImGui::Checkbox(XorStr("remove post processing"), &g_Options.Visuals.NoPP);
			}ImGui::EndChild();
		}ImGui::EndChild();
	}
	if (tab == 3)
	{
		ImGui::BeginChild("fith child", ImVec2(620, 505), true);
		{
			ImGui::BeginChild("sub 1", ImVec2(195, 200), true);
			{
				ImGui::PushItemWidth(-1);
				ImGui::Checkbox("anti-untrusted", &g_Options.Misc.antiuntrusted);
				ImGui::Checkbox(XorStr("automatic hop"), &g_Options.Misc.Bhop);
				ImGui::Checkbox(XorStr("automatic strafe"), &g_Options.Misc.AutoStrafe);

				ImGui::Checkbox(XorStr("slide walk"), &g_Options.Misc.MemeWalk);
				ImGui::Combo(XorStr("##purchase_bot"), &g_Options.Misc.purchase_bot, purchaseBot, ARRAYSIZE(purchaseBot));
				ImGui::Checkbox(XorStr("kevlar + nades"), &g_Options.Misc.purchase_bot_nades);
				ImGui::Checkbox(XorStr("fakewalk"), &g_Options.Misc.fakewalk);
				ImGui::Hotkey(XorStr("##fakewalk key"), &g_Options.Misc.fakewalkkey);
				if (ImGui::Button(XorStr("uninject")))
				{
					g_Engine->ClientCmd_Unrestricted("cl_mouseenable 1");
					unload = true;
					Sleep(1000);
					FullUpdate();
				}
			}ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild("sub 2", ImVec2(195, 200), true);
			{
				ImGui::PushItemWidth(-1);
				ImGui::Checkbox("eden clantag", &g_Options.Misc.syncclantag);
				if (ImGui::Button("eden name changer"))
					setName(u8"-EDEN-");
				if (ImGui::Button("ayyware crasher"))
					setName(u8"------------------------------------------------------------CYA AYYWARE------------------------------------------------------------");
			}ImGui::EndChild();

		}ImGui::EndChild();
	}
	if (tab == 4)
	{
		ImGui::BeginChild("sixth child", ImVec2(620, 505), true);
		{
			ImGui::PushItemWidth(200);
			ImGui::Combo(("File"), &g_Options.Menu.ConfigFile, configFiles, ARRAYSIZE(configFiles));
			if (ImGui::Button("save config")) Config->Save();

			if (ImGui::Button("load config")) Config->Load();
		}ImGui::EndChild();
	}
	if (tab == 5)
	{
		ImGui::BeginChild("sixth child", ImVec2(620, 505), true);
		{
			ImGui::Checkbox(XorStr("enabled"), &g_Options.Skinchanger.Enabled);
			if (ImGui::Button(XorStr("force update"), ImVec2(-1, 20))) FullUpdate();
			ImGui::BeginChild("first child", ImVec2(190, 200), true);
			{
				static char filterWeapons[32];
				static char filterSkins[32];
				ImGui::PushItemWidth(-1);
				ImGui::InputText(XorStr("##FILTERWEAPONS"), filterWeapons, IM_ARRAYSIZE(filterWeapons));
				ImGui::PopItemWidth();
				ImGui::ListBoxHeader(XorStr("##GUNS"), ImVec2(-1, -1));
				for (auto it : ItemDefinitionIndexMap)
				{
					bool isDefault = (int)it.first < 0;
					if (!isDefault && !Contains(ToLower(std::string(filterWeapons)), ToLower(ItemDefinitionIndexMap.at(it.first).entityName)))
						continue;

					if (IsUtility(it.first))
						continue;

					const bool item_selected = ((int)it.first == (int)g_Options.Menu.currentWeapon);
					//ImGui::PushID((int)it.first);
					std::string formattedName;

					formattedName = ItemDefinitionIndexMap.at(it.first).killIcon;
					if (ImGui::Selectable(formattedName.c_str(), item_selected))
					{
						g_Options.Menu.currentWeapon = (int)it.first;
					}
					//ImGui::PopID();
				}
				ImGui::ListBoxFooter();
			}ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild("second child", ImVec2(190, 200), true);
			{
				static char filterWeapons[32];
				static char filterSkins[32];
				std::string skinName = weaponnames(g_Options.Menu.currentWeapon);
				{
					static char filterWeapons[32];
					static char filterSkins[32];
					ImGui::PushItemWidth(-1);
					ImGui::InputText(XorStr("##FILTERSKINS"), filterSkins, IM_ARRAYSIZE(filterSkins));
					ImGui::InputInt(XorStr("##custom ID"), &g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin);
					ImGui::PopItemWidth();
					ImGui::ListBoxHeader(XorStr("##SKINS"), ImVec2(-1, -1));
					std::string skinStr = "";
					int curItem = -1;
					int s = 0;
					for (auto skin : g_Options.Skinchanger.weaponSkins[skinName])
					{
						int pk = g_Options.Skinchanger.skinMap[skin].paintkit;
						if (pk == g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin)
							curItem = s;
						bool selected = g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin == pk;

						skinStr = g_Options.Skinchanger.skinNames[g_Options.Skinchanger.skinMap[skin].tagName].c_str();
						skinStr += " | ";
						skinStr += std::to_string(g_Options.Skinchanger.skinMap[skin].paintkit);


						if (!Contains(ToLower(std::string(filterSkins)), ToLower(skinStr)))
							continue;
						if (ImGui::Selectable(skinStr.c_str(), selected))
						{
							pk = g_Options.Skinchanger.skinMap[skin].paintkit;
							g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin = pk;
							//      FullUpdate();
							break;
						}
						s++;
					}

					ImGui::ListBoxFooter();
				}
			}ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild("third child", ImVec2(-1, 200), true);
			{
				ImGui::ListBoxHeader("##KNIVES", ImVec2(-1, -1));
				{
					if (ImGui::RadioButton(XorStr("Default"), &g_Options.Skinchanger.knifemodel, 0))
					{
					}
					if (ImGui::RadioButton(XorStr("Bayonet"), &g_Options.Skinchanger.knifemodel, 1))
					{
					}
					if (ImGui::RadioButton(XorStr("Flip Knife"), &g_Options.Skinchanger.knifemodel, 2))
					{
					}
					if (ImGui::RadioButton(XorStr("Gut Knife"), &g_Options.Skinchanger.knifemodel, 3))
					{
					}
					if (ImGui::RadioButton(XorStr("Karambit"), &g_Options.Skinchanger.knifemodel, 4))
					{
					}
					if (ImGui::RadioButton(XorStr("M9 Bayonet"), &g_Options.Skinchanger.knifemodel, 5))
					{
					}
					if (ImGui::RadioButton(XorStr("Huntsman"), &g_Options.Skinchanger.knifemodel, 6))
					{
					}
					if (ImGui::RadioButton(XorStr("Falchion"), &g_Options.Skinchanger.knifemodel, 7))
					{
					}
					if (ImGui::RadioButton(XorStr("Bowie"), &g_Options.Skinchanger.knifemodel, 8))
					{
					}
					if (ImGui::RadioButton(XorStr("Butterfly Knife"), &g_Options.Skinchanger.knifemodel, 9))
					{
					}
					if (ImGui::RadioButton(XorStr("Shadow Daggers"), &g_Options.Skinchanger.knifemodel, 10))
					{
					}
					/*------------------------------------------------------------------------------------*/
					ImGui::Separator();
					/*------------------------------------------------------------------------------------*/
					if (ImGui::RadioButton(XorStr("Bloodhound"), &g_Options.Skinchanger.glove, 1))
					{
						FullUpdate();
					}
					if (ImGui::RadioButton(XorStr("Sport"), &g_Options.Skinchanger.glove, 2))
					{
						FullUpdate();
					}
					if (ImGui::RadioButton(XorStr("Driver"), &g_Options.Skinchanger.glove, 3))
					{
						FullUpdate();
					}
					if (ImGui::RadioButton(XorStr("Hand Wraps"), &g_Options.Skinchanger.glove, 4))
					{
						FullUpdate();
					}
					if (ImGui::RadioButton(XorStr("Motorcycle"), &g_Options.Skinchanger.glove, 5))
					{
						FullUpdate();
					}
					if (ImGui::RadioButton(XorStr("Specialst"), &g_Options.Skinchanger.glove, 6))
					{
						FullUpdate();
					}
					if (ImGui::RadioButton(XorStr("Hydra"), &g_Options.Skinchanger.glove, 7))
					{
						FullUpdate();
					}

					const char* gstr;
					if (g_Options.Skinchanger.glove == 1)
					{
						gstr = "Charred\0\rSnakebite\0\rBronzed\0\rGuerilla\0\rCustom\0\0";
					}
					else if (g_Options.Skinchanger.glove == 2)
					{
						gstr = "Hedge Maze\0\rPandoras Box\0\rSuperconductor\0\rArid\0\rVice\0\rOmega\0\rBronze Morph\0\rAmphibious\0\0";
					}
					else if (g_Options.Skinchanger.glove == 3)
					{

						gstr = "Lunar Weave\0\rConvoy\0\rCrimson Weave\0\rDiamondback\0\rRacing Green\0\rOvertake\0\rImperial Plaid\0\rKing Snake\0\0";
					}
					else if (g_Options.Skinchanger.glove == 4)
					{
						gstr = "Leather\0\rSpruce DDPAT\0\rSlaughter\0\rBadlands\0\rArboreal\0\rDuct Tape\0\rOverprint\0\rCobalt Skulls\0\0";
					}
					else if (g_Options.Skinchanger.glove == 5)
					{
						gstr = "Eclipse\0\rSpearmint\0\rBoom!\0\rCool Mint\0\rPolygon\0\rTransport\0\rTurtle\0\rPOW!\0\0";
					}
					else if (g_Options.Skinchanger.glove == 6)
					{
						gstr = "Forest DDPAT\0\rCrimson Kimono\0\rEmerald Web\0\rFoundation\0\rMogul\0\rFade\0\rBuckshot\0\rCrimson Web\0\0";
					}
					else if (g_Options.Skinchanger.glove == 7)
					{
						gstr = "Case Hardened\0\rRattler\0\rMangrove\0\rEmerald\0\0";
					}
					else
					{
						gstr = "";
					}
					ImGui::PushItemWidth(-1);
					if (ImGui::Combo(XorStr("##2"), &g_Options.Skinchanger.gloeskin, gstr, -1))
						FullUpdate();
				}
				ImGui::ListBoxFooter();
			}ImGui::EndChild();

			ImGui::BeginGroupBox("final child");
			{
				ImGui::PushItemWidth(200);

				ImGui::Text("name:");
				ImGui::InputText(XorStr("##name"), &g_Options.Skinchanger.W->ChangerName[32], 32); //
				ImGui::Text("stattrack:");
				ImGui::InputInt("##stat", &g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerStatTrak);
				ImGui::Text("wear:");
				ImGui::SliderFloat("##skinwear", &g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerWear, 0.f, 1.f, "%.3f");
			}ImGui::EndGroupBox();

		}
		ImGui::EndChild();
	}
	if (tab == 6)
	{
		ImGui::BeginChild("second child", ImVec2(620, 505), true);
		{
			ImGui::Checkbox(XorStr("enabled"), &g_Options.Legitbot.MainSwitch);
			ImGui::BeginChild("first child", ImVec2(195, 200), true);

			{
				ImGui::Text("Rifles");
				ImGui::PushItemWidth(-1);
				ImGui::Hotkey(XorStr("Key##0"), &g_Options.Legitbot.MainKey);
				ImGui::SliderFloat(XorStr("smooth##0"), &g_Options.Legitbot.MainSmooth, 1.00f, 100.00f, "%.2f");
				ImGui::SliderFloat(XorStr("field of view##0"), &g_Options.Legitbot.Mainfov, 0.00f, 30.00f, "%.2f");
				ImGui::SliderFloat(XorStr("minimum rcs##0"), &g_Options.Legitbot.main_recoil_min, 1.00f, 100.00f, "%.2f");
				ImGui::SliderFloat(XorStr("maximum rcs##0"), &g_Options.Legitbot.main_recoil_max, 1.00f, 100.00f, "%.2f");
				ImGui::Separator();
				ImGui::PushItemWidth(-1);
				ImGui::Checkbox(XorStr("position adjustment"), &g_Options.Legitbot.backtrack);
				ImGui::SameLine();
				ImGui::MyColorEdit3("##BTCOL", g_Options.Colors.backtrackcllr, 1 << 7);
				ImGui::SliderFloat(XorStr("ticks: "), &g_Options.Legitbot.backtrackTicks, 0, 12, "%1.f");
			}ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild("second child", ImVec2(195, 200), true);
			{
				ImGui::Text("Pistols");
				ImGui::PushItemWidth(-1);
				ImGui::Hotkey(XorStr("Key##1"), &g_Options.Legitbot.PistolKey);
				ImGui::SliderFloat(XorStr("smooth##1"), &g_Options.Legitbot.PistolSmooth, 1.00f, 100.00f, "%.2f");
				ImGui::SliderFloat(XorStr("field of view##1"), &g_Options.Legitbot.Pistolfov, 0.00f, 30.00f, "%.2f");
				ImGui::SliderFloat(XorStr("minimum rcs##1"), &g_Options.Legitbot.pistol_recoil_min, 1.00f, 100.00f, "%.2f");
				ImGui::SliderFloat(XorStr("maximum rcs##1"), &g_Options.Legitbot.pistol_recoil_max, 1.00f, 100.00f, "%.2f");
			}ImGui::EndChild();
			ImGui::SameLine();

			ImGui::BeginChild("third child", ImVec2(195, 200), true);
			{
				ImGui::Text("Snipers");
				ImGui::PushItemWidth(-1);
				ImGui::Hotkey(XorStr("Key##2"), &g_Options.Legitbot.SniperKey);
				ImGui::SliderFloat(XorStr("smooth##2"), &g_Options.Legitbot.SniperSmooth, 1.00f, 100.00f, "%.2f");
				ImGui::SliderFloat(XorStr("field of view##2"), &g_Options.Legitbot.Sniperfov, 0.00f, 30.00f, "%.2f");
				ImGui::SliderFloat(XorStr("minimum rcs##2"), &g_Options.Legitbot.sniper_recoil_min, 1.00f, 100.00f, "%.2f");
				ImGui::SliderFloat(XorStr("maximum rcs##2"), &g_Options.Legitbot.sniper_recoil_max, 1.00f, 100.00f, "%.2f");
			}ImGui::EndChild();

			ImGui::BeginChild("fourth child", ImVec2(195, 200), true);
			{
				ImGui::PushItemWidth(-1);
				ImGui::Hotkey("Key##3", &g_Options.Legitbot.Triggerbot.Key);
				ImGui::SliderFloat(("delay"), &g_Options.Legitbot.Triggerbot.Delay, 1.f, 150.f, "%.0f");
				ImGui::SliderFloat(("hitchance"), &g_Options.Legitbot.Triggerbot.hitchance, 1.f, 100.f, "%.0f");
				ImGui::Text(("filter"));
				ImGui::Separator();
				ImGui::Selectable((" head"), &g_Options.Legitbot.Triggerbot.Filter.Head);
				ImGui::Selectable((" arms"), &g_Options.Legitbot.Triggerbot.Filter.Arms);
				ImGui::Selectable((" chest"), &g_Options.Legitbot.Triggerbot.Filter.Chest);
				ImGui::Selectable((" stomach"), &g_Options.Legitbot.Triggerbot.Filter.Stomach);
				ImGui::Selectable((" legs"), &g_Options.Legitbot.Triggerbot.Filter.Legs);


			}ImGui::EndChild();

		}ImGui::EndChild();
	}

	/*----------------------------------------------------------------------------------*/
	/*									      TABS									    */
	/*----------------------------------------------------------------------------------*/
	ImGui::PopFont();
	ImGui::End();
}

