
#include "ESP.h"
#include "Interfaces.h"
#include "Render.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include "GrenadePrediction.h"
#include "LagComp.h"
#include "Autowall.h"
#include "JunkCode13.h"

visuals::visuals()
{
	BombCarrier = nullptr;
}

int width = 0;
int height = 0;
bool done = false;

float damage;
char bombdamagestringdead[24];
char bombdamagestringalive[24];

void visuals::OnPaintTraverse(C_BaseEntity* local)
{


	NightMode();
	if (g_Options.Misc.SpecList) SpecList(local);
	grenade_prediction::instance().Paint();
	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());


	if (g_Options.Visuals.Crosshair)
		Crosshair(local);

	if (g_Options.Visuals.Hitmarker)
		Hitmarker();

	if (g_Options.Visuals.angleLines && pLocal->IsAlive())
		DrawAngles();

	if (g_Options.Visuals.DrawAwall && pLocal->IsAlive())
		DrawAwall();

	 

	for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
	{

		C_BaseEntity *entity = g_EntityList->GetClientEntity(i);
		if (entity == nullptr)
			continue;
		if (entity == local && !g_Input->m_fCameraInThirdPerson == true)
			continue;

		if (entity == local)
			continue;
		if (entity->IsDormant())
			continue;
	 

		player_info_t pinfo;
		Vector pos, pos3D;
		pos3D = entity->GetOrigin();
		CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)(entity);


		 auto owner = entity->GetOwnerHandle();
		 ClientClass* cClass = (ClientClass*)entity->GetClientClass();

	
		if (!g_Render->WorldToScreen(pos3D, pos))
			continue;

		if (g_Options.Visuals.Droppedguns)
		{
			if (strstr(entity->GetClientClass()->m_pNetworkName, XorStr("CWeapon")))
			{
				int ClassID = cClass->m_ClassID;
				int owner = entity->GetOwnerHandle();

				
				if (owner = -1)
				{
				
					//backtrackcllr
					auto meme = Color(g_Options.Colors.DroppedWeapons[0] * 255, g_Options.Colors.DroppedWeapons[1] * 255, g_Options.Colors.DroppedWeapons[2] * 255, 255);
					CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)(entity);
					Vector vOrig; Vector vScreen;
					vOrig = entity->GetOrigin();
					g_Render->DrawString2(g_Render->font.ESPMini, (int)pos.x, (int)pos.y - 10, meme, FONT_CENTER, "%i FT", flGetDistance(local->GetOrigin(), vOrig));
					g_Render->DrawString2(g_Render->font.ESPMini, (int)pos.x, (int)pos.y, meme, FONT_CENTER, "%s" " " "(" "%i" "/" "%i" ")", std::string(entity->GetClientClass()->m_pNetworkName).substr(7).c_str(), weapon->ammo(), weapon->ammo2());

					if (ClassID == 1)
					{
						g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y, Color(255, 255, 255, 255), FONT_RIGHT, "%s", XorStr("Desert Eagle"));
					}
					if (ClassID == 39)
					{
						g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y, Color(255, 255, 255, 255), FONT_RIGHT, "%s", XorStr("AK-47"));
					}

					if (ClassID == 29)
					{
						g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y, Color(255, 255, 255, 255), FONT_RIGHT, "%s", XorStr("Dropped C4"));
					}
					if (ClassID == 2)
					{
						g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y, Color(255, 255, 255, 255), FONT_RIGHT, "%s", XorStr("Defuse Kit"));
					}
				}
			}
		}

		

		if (g_Options.Visuals.Bomb && cClass->m_ClassID == (int)ClassID::CPlantedC4)
		{
			BombCarrier = nullptr;

			Vector vOrig; Vector vScreen;
			vOrig = entity->GetOrigin();
			CCSBomb* Bomb = (CCSBomb*)entity;
			float flBlow = Bomb->GetC4BlowTime();
			float lifetime = flBlow - (g_Globals->interval_per_tick * local->GetTickBase());
			if (g_Render->WorldToScreen(vOrig, vScreen))
			{
				if (local->IsAlive() && !Bomb->IsBombDefused())
				{
					float flDistance = local->GetEyePosition().DistTo(entity->GetEyePosition());
					float a = 450.7f;
					float b = 75.68f;
					float c = 789.2f;
					float d = ((flDistance - b) / c);
					float flDamage = a*exp(-d * d);

					g_Render->DrawString2(g_Render->font.ESPMini, (int)vScreen.x, int(vScreen.y - 7), Color(250, 255, 255, 255), FONT_LEFT, "%i FT", flGetDistance(local->GetOrigin(), vOrig));
					damage = float((std::max)((int)ceilf(CSGO_Armor(flDamage, local->ArmorValue())), 0));

					sprintf_s(bombdamagestringdead, sizeof(bombdamagestringdead) - 1, "fatal");
					sprintf_s(bombdamagestringalive, sizeof(bombdamagestringalive) - 1, "health left: %.0f", local->GetHealth() - damage);
					if (lifetime > -2.f)
					{
						if (damage >= local->GetHealth())
						{
							g_Render->Text((int)vScreen.x, int(vScreen.y + 10), Color(250, 42, 42, 255), g_Render->font.ESPMini, bombdamagestringdead);
						}
						else if (local->GetHealth() > damage)
						{
							g_Render->Text((int)vScreen.x, int(vScreen.y + 10), Color(0, 255, 0, 255), g_Render->font.ESPMini, bombdamagestringalive);
						}
					}
				}
				char buffer[64];
				if (lifetime > 0.01f && !Bomb->IsBombDefused())
				{
					sprintf_s(buffer, "bomb: %.1f", lifetime);
					g_Render->Text((int)vScreen.x, (int)vScreen.y, Color(250, 42, 42, 255), g_Render->font.ESPMini, buffer);
				}

			}

			g_Engine->GetScreenSize(width, height);
			int halfX = width / 2;
			int halfY = height / 2;


			if (Bomb->GetBombDefuser() > 0)
			{
				float countdown = Bomb->GetC4DefuseCountDown() - (local->GetTickBase() * g_Globals->interval_per_tick);
				if (countdown > 0.01f)
				{
					if (lifetime > countdown)
					{
						char defuseTimeString[24];
						sprintf_s(defuseTimeString, sizeof(defuseTimeString) - 1, "defusing: %.1f", countdown);
						g_Render->Text(halfX - 50, halfY + 200, Color(0, 255, 0, 255), g_Render->font.ESPMini, defuseTimeString);
					}
					else
					{
						g_Render->Text(halfX - 50, halfY + 200, Color(255, 0, 0, 255), g_Render->font.ESPMini, "no time left");
					}
				}
			}
		}



		if (g_Options.Visuals.Grenades)
		{

			if (!g_Render->WorldToScreen(pos3D, pos))
				continue;

			Color GrenadeColor	= Color(0, 0, 0, 0);
			char* szModelName	= "";
			char* szIconName	= "";
			if (strstr(cClass->m_pNetworkName, XorStr("Projectile")))
			{
				const model_t* pModel	= entity->GetModel();
				if (!pModel)
					return;


				const studiohdr_t* pHdr = g_ModelInfo->GetStudiomodel(pModel);
				if (!pHdr)
					return;

				if (!strstr(pHdr->name, XorStr("thrown")) && !strstr(pHdr->name, XorStr("dropped")))
					return;



				IMaterial* mats[32];
				g_ModelInfo->GetModelMaterials(pModel, pHdr->numtextures, mats);

				for (int i = 0; i < pHdr->numtextures; i++)
				{
					IMaterial* mat = mats[i];
					if (!mat)
						continue;

					if (strstr(mat->GetName(), "flashbang"))
					{
						szModelName		= "flashbang";
						szIconName		= "G";
						GrenadeColor	= Color(255, 255, 0, 255);
					}
					else if (strstr(mat->GetName(), "m67_grenade") || strstr(mat->GetName(), "hegrenade"))
					{
						szModelName		= "Frag";
						szIconName		= "H";
						GrenadeColor	= Color(255, 0, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "smoke"))
					{
						szModelName		= "Smoke";
						szIconName		= "P";
						GrenadeColor	= Color(0, 255, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "decoy"))
					{
						szModelName		= "Decoy";
						szIconName		= "G";
						GrenadeColor	= Color(0, 255, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "incendiary"))
					{
						szModelName		= "Incendiary";
						szIconName		= "P";
						GrenadeColor	= Color(255, 0, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "molotov"))
					{
						szModelName		= "Molotov";
						szIconName		= "P";
						GrenadeColor	= Color(255, 0, 0, 255);
						break;
					}
				}
				int r, g, b, a;
				GrenadeColor.GetColor(r, g, b, a);
				/* would be better to do a switch but who cares br0tha*/
				if (g_Options.Visuals.GreandeI == 0) 
				{
					// wont return cuz i still wana be p100
				}
				if (g_Options.Visuals.GreandeI == 1)
				{
					g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y + 15, GrenadeColor, FONT_CENTER, "%s", szModelName);
				}
				else if (g_Options.Visuals.GreandeI == 2)
				{
					g_Render->DrawString2(g_Render->font.CounterStrike, (int)pos.x, (int)pos.y + 15, GrenadeColor, FONT_CENTER, "%s", szIconName);
				}
				 
				g_Render->OutlineCircle(pos.x, pos.y, 10.f, 10.f, Color(r, g, b, a));

			}
		}


 

		if (g_Engine->GetPlayerInfo(i, &pinfo) && entity->IsAlive())
		{
			if (g_Options.Legitbot.backtrack)
			{
				if (local->IsAlive())
				{
					for (int t = 0; t < g_Options.Legitbot.backtrackTicks; ++t)
					{
						Vector screenbacktrack[64][12];

						if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimulationTime())
						{
							if (g_Render->WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
							{
								//backtrackcllr
								auto backtrackclr = Color(g_Options.Colors.backtrackcllr[0] * 255, g_Options.Colors.backtrackcllr[1] * 255, g_Options.Colors.backtrackcllr[2] * 255, 255);
								g_Surface->DrawSetColor(backtrackclr);
								g_Render->DrawString2(g_Render->font.ESPClear, screenbacktrack[i][t].x, screenbacktrack[i][t].y, backtrackclr, FONT_CENTER, "+");

							}
						}
					}
				}
				else
				{
					memset(&headPositions[0][0], 0, sizeof(headPositions));
				}
			}
			if (g_Options.Ragebot.PosAdjust)
			{
				if (local->IsAlive())
				{
					for (int t = 0; t < 12; ++t)
					{
						Vector screenbacktrack[64][12];

						if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimulationTime())
						{
							if (g_Render->WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
							{

								auto backtrackclr = Color(255, 0, 0, 255);
								g_Surface->DrawSetColor(backtrackclr);
								g_Render->DrawString2(g_Render->font.ESPClear, screenbacktrack[i][t].x, screenbacktrack[i][t].y, backtrackclr, FONT_CENTER, "+");

							}
						}
					}
				}
				else
				{
					memset(&headPositions[0][0], 0, sizeof(headPositions));
				}
			}
			if (g_Options.Ragebot.FakeLagFix)
			{
				if (local->IsAlive())
				{
					Vector screenbacktrack[64];

					if (backtracking->records[i].tick_count + 12 > g_Globals->tickcount)
					{
						if (g_Render->WorldToScreen(backtracking->records[i].headPosition, screenbacktrack[i]))
						{

							g_Surface->DrawSetColor(Color::Black());
							g_Surface->DrawLine(screenbacktrack[i].x, screenbacktrack[i].y, screenbacktrack[i].x + 2, screenbacktrack[i].y + 2);

						}
					}
				}
				else
				{
					memset(&backtracking->records[0], 0, sizeof(backtracking->records));
				}
			}
		 

			if (!g_Render->WorldToScreen(pos3D, pos))
				continue;

			Color clr = entity->GetTeamNum() == local->GetTeamNum() ?
				Color(g_Options.Colors.TeamESP[0] * 255, g_Options.Colors.TeamESP[1] * 255, g_Options.Colors.TeamESP[2] * 255, 255) :
				Color(g_Options.Colors.EnemyESP[0] * 255, g_Options.Colors.EnemyESP[1] * 255, g_Options.Colors.EnemyESP[2] * 255, 255);
			if (entity->GetTeamNum() == local->GetTeamNum() && !g_Options.Visuals.TeamESP)
				continue;
			if (!entity->IsAlive())
				continue;

			bool PVS = true;
			RECT rect = DynamicBox(entity, PVS, local);

			DrawInfo(rect, entity, local);

			if (g_Options.Visuals.Box)
			{
				switch (g_Options.Visuals.BoxType)
				{
				case 0:
					DrawBox(rect, clr);

					break;
				case 1:
					DrawCorners(rect, clr);
					break;
				case 2:
					ThreeDBox(entity->GetCollideable()->OBBMins(), entity->GetCollideable()->OBBMaxs(), entity->GetOrigin(), clr);
					break;
				}
			}
			if (g_Options.Visuals.AimLine)
				 DrawSnapLine(rect);
			if (g_Options.Visuals.Skeleton)
				Skeleton(entity, Color(255, 255, 255, 255));
			if (g_Options.Visuals.health)
				DrawHealth(rect, entity);
			if (g_Options.Visuals.armor) 
				armorbar(rect, entity);
			if (g_Options.Visuals.barrel)
				BulletTrace(entity, clr);

		}


	}
}

void visuals::DrawBox(RECT rect,  Color Col)
{
	g_Render->DrawOutlinedRect(rect.left - 1, rect.top - 1, rect.right - rect.left + 2, rect.bottom - rect.top + 2, Color(0, 0, 0, 255));
	g_Render->DrawOutlinedRect(rect.left + 1, rect.top + 1, rect.right - rect.left - 2, rect.bottom - rect.top - 2, Color(0, 0, 0, 255));
	g_Render->DrawOutlinedRect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, Col);
}

void visuals::DrawCorners(RECT rect, Color Col)
{
	int x1, y1, x2, y2, w, h;
	x1 = rect.left;
	y1 = rect.top;
	x2 = rect.right;
	y2 = rect.bottom;

	w = x2;
	h = y2;

	int Line_Size	= (y1 - h) / 6;
	int Line_Size2	= (y1 - h) / 6;

	int red		= 0;
	int green	= 0;
	int blue	= 0;
	int alpha	= 0;
	Col.GetColor(red, green, blue, alpha);
	g_Surface->DrawSetColor(red, green, blue, alpha);

	//top inwards
	g_Surface->DrawLine(w, y1, w + Line_Size, y1);
	g_Surface->DrawLine(x1, y1, x1 - Line_Size, y1);

	//top downwards
	g_Surface->DrawLine(x1, y1, x1, y1 - Line_Size);
	g_Surface->DrawLine(w, y1, w, y1 - Line_Size);

	//bottom inwards
	g_Surface->DrawLine(x1, h, x1 - Line_Size, h);
	g_Surface->DrawLine(w, h, w + Line_Size, h);

	//bottom upwards
	g_Surface->DrawLine(x1, h, x1, h + Line_Size);
	g_Surface->DrawLine(w, h, w, h + Line_Size);

	//outlines

	g_Surface->DrawSetColor(0, 0, 0, 200);

	//top inwards
	g_Surface->DrawLine(w, y1 - 1, w + Line_Size, y1 - 1);
	g_Surface->DrawLine(x1, y1 - 1, x1 - Line_Size, y1 - 1);
	//inlines
	g_Surface->DrawLine(w - 1, y1 + 1, w + Line_Size, y1 + 1);
	g_Surface->DrawLine(x1 + 1, y1 + 1, x1 - Line_Size, y1 + 1);

	// top downwards
	g_Surface->DrawLine(x1 - 1, y1 - 1, x1 - 1, y1 - Line_Size);
	g_Surface->DrawLine(w + 1, y1 - 1, w + 1, y1 - Line_Size);
	//inlines
	g_Surface->DrawLine(x1 + 1, y1, x1 + 1, y1 - Line_Size);
	g_Surface->DrawLine(w - 1, y1, w - 1, y1 - Line_Size);

	//bottom inwards
	g_Surface->DrawLine(x1, h + 1, x1 - Line_Size, h + 1);
	g_Surface->DrawLine(w, h + 1, w + Line_Size, h + 1);
	//inlines
	g_Surface->DrawLine(x1 + 1, h - 1, x1 - Line_Size, h - 1);
	g_Surface->DrawLine(w - 1, h - 1, w + Line_Size, h - 1);

	//bottom upwards
	g_Surface->DrawLine(x1 - 1, h + 1, x1 - 1, h + Line_Size);
	g_Surface->DrawLine(w + 1, h + 1, w + 1, h + Line_Size);
	//inlines
	g_Surface->DrawLine(x1 + 1, h, x1 + 1, h + Line_Size);
	g_Surface->DrawLine(w - 1, h, w - 1, h + Line_Size);
}

void visuals::ThreeDBox(Vector minin, Vector maxin, Vector pos, Color Col)
{
	Vector min = minin + pos;
	Vector max = maxin + pos;

	Vector corners[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(min.x, min.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(max.x, max.y, max.z),
		Vector(max.x, min.y, max.z) };


	int edges[12][2] = { { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 },{ 0, 4 },{ 1, 5 },{ 2, 6 },{ 3, 7 }, };

	for (const auto edge : edges)
	{
		Vector p1, p2;
		if (!g_Render->WorldToScreen(corners[edge[0]], p1) || !g_Render->WorldToScreen(corners[edge[1]], p2))
			return;
		int red		= 0;
		int green	= 0;
		int blue	= 0;
		int alpha	= 0;
		Col.GetColor(red, green, blue, alpha);
		g_Surface->DrawSetColor(red, green, blue, alpha);
		g_Surface->DrawLine(p1.x, p1.y, p2.x, p2.y);
		g_Surface->DrawSetColor(0, 0, 0, 255);
 
	}
}




void visuals::DrawInfo(RECT rect, C_BaseEntity* pPlayer, C_BaseEntity* local)
{
	player_info_t info;
	static class Text
	{
	public:
		std::string text;
		int side;
		int Font;
		Color color;

		Text(std::string text, int side, int Font, Color color) : text(text), side(side), Font(Font), color(color)
		{
		}
	};
	std::vector< Text > texts;
	if (pPlayer->GetClientClass()->m_ClassID == 83 || pPlayer->GetClientClass()->m_ClassID == 84)
	{
		if (g_Options.Visuals.Name)
			texts.push_back(Text("Hostage", 0, g_Render->font.ESP, Color(255, 255, 255, 255)));
	}
	else if (g_Engine->GetPlayerInfo(pPlayer->GetIndex(), &info))
	{
		if (g_Options.Visuals.Armor && pPlayer == BombCarrier)
			texts.push_back(Text("Bomb Carrier", 0, g_Render->font.ESP, Color(255, 220, 220, 255)));
		if (g_Options.Visuals.Armor && pPlayer->IsFlashed())
			texts.push_back(Text("Flashed", 0, g_Render->font.ESP, Color(255, 255, 183, 255)));
		if (g_Options.Visuals.Name)
		{
			auto nameclr = Color(g_Options.Colors.nameclr[0] * 255, g_Options.Colors.nameclr[1] * 255, g_Options.Colors.nameclr[2] * 255, 255);
			texts.push_back(Text(info.name, 0, g_Render->font.ESP, Color(nameclr)));
		}
		if (g_Options.Visuals.Distance)
			texts.push_back(Text(std::to_string(flGetDistance(local->GetOrigin(), pPlayer->GetOrigin())) + std::string("FT"), 2, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
		if (g_Options.Visuals.Callout)
			texts.push_back(Text(pPlayer->GetCallout(), 1, g_Render->font.ESPMini, Color(255, 220, 220, 255)));

		CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(pPlayer->GetActiveWeaponHandle());
		if (weapon)
		{
			if (g_Options.Visuals.Weapon && weapon)
				switch (g_Options.Visuals.wpnmode)
				{
				case 0:
					texts.push_back(Text(weapon->GetGunName(), 2, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
					break;
				case 1:
					texts.push_back(Text(weapon->GetGunIcon(), 2, g_Render->font.ESPWEP, Color(255, 255, 255, 255)));
					break;
				}

			if (g_Options.Visuals.Armor && weapon->IsInReload())
				texts.push_back(Text("Reloading", 2, g_Render->font.ESP, Color(121, 252, 250, 255)));
			if (g_Options.Visuals.Armor)
				texts.push_back(Text(pPlayer->GetArmorName(), 1, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
			if (g_Options.Visuals.Armor && pPlayer->hasDefuser())
				texts.push_back(Text("defuser", 1, g_Render->font.ESPMini, Color(49, 106, 198, 255)));
			if (g_Options.Visuals.Armor && pPlayer->m_bHasHeavyArmor())
				texts.push_back(Text("heavy armor", 1, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
			if (g_Options.Visuals.ammo)
			{
				C_BaseEntity* pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
				CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(pPlayer->GetActiveWeaponHandle());

				if (MiscFunctions::IsKnife(pWeapon) || MiscFunctions::IsGrenade(pWeapon))
				{

					texts.push_back(Text(std::string("ammo: 0"), 1, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
				}
				else
				{
					texts.push_back(Text(std::string("ammo: ") + std::to_string(weapon->ammo()), 1, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
				}
			}
			if (g_Options.Visuals.Armor && pPlayer->IsScoped())
				texts.push_back(Text("zoom", 1, g_Render->font.ESPMini, Color(16, 171, 232, 255)));
			if (g_Options.Visuals.Money)
				texts.push_back(Text(std::string("$") + std::to_string(pPlayer->iAccount()), 1, g_Render->font.ESPMini, Color(25, 224, 55, 255)));
			if (g_Options.Visuals.ArmorBar)
				texts.push_back(Text(std::string("a: ") + std::to_string(pPlayer->ArmorValue()), 2, g_Render->font.ESPMini, Color(0, 163, 255, 255)));
		}
	}


	if (g_Options.Visuals.resolveMode)
	{
		if (Globals::resolvemode == 1)
		{
			texts.push_back(Text(std::string("R: Prediction"), 0, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
		}

		else if (Globals::resolvemode == 2)
		{
			texts.push_back(Text(std::string("R: Bruteforce"), 0, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
		}
		else if (Globals::resolvemode == 3)
		{
			texts.push_back(Text(std::string("R: LBY Update"), 0, g_Render->font.ESPMini, Color(255, 255, 255, 255)));
		}
		else if (Globals::resolvemode == 4)
		{
			texts.push_back(Text(std::string("Resolver: Legit Player"), 0, g_Render->font.ESP, Color(255, 255, 255, 255)));
		}
		else if (Globals::resolvemode == 5)
		{
			texts.push_back(Text(std::string("R: Stationery"), 0, g_Render->font.ESP, Color(255, 255, 255, 255)));
		}
	}

	int middle = ((rect.right - rect.left) / 2) + rect.left;
	int Top[3] = { rect.top,rect.top, rect.bottom };
	for (auto text : texts)
	{
		RECT nameSize = g_Render->GetTextSize(text.Font, (char*)text.text.c_str());
		switch (text.side)
		{
		case 0:
			Top[0] -= nameSize.bottom + 1;
			g_Render->DrawString2(text.Font, middle, Top[0] + 8, text.color, FONT_CENTER, (char*)text.text.c_str());
			break;
		case 1:
			g_Render->DrawString2(text.Font, rect.right + 2, Top[1] + 8, text.color, FONT_LEFT, (char*)text.text.c_str());
			Top[1] += nameSize.bottom - 4;
			break;
		case 2:
			g_Render->DrawString2(text.Font, middle, Top[2] + 8, text.color, FONT_CENTER, (char*)text.text.c_str());
			Top[2] += nameSize.bottom - 4;
			break;
		}
	}
}


void visuals::DrawAwall()
{
	int MidX;
	int MidY;
	g_Engine->GetScreenSize(MidX, MidY);

	int damage;
	C_BaseEntity* pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());

	if (MiscFunctions::IsKnife(pWeapon))
		return;
	if (MiscFunctions::IsGrenade(pWeapon))
		return;
	if (CanWallbang(damage))
	{
 		g_Render->GradientH(MidX / 2 - 3, MidY / 2 - 3, 7, 7, Color(0, 255, 0, 255), Color(0, 255, 0, 255));

		g_Render->DrawOutlinedRect(MidX / 2 - 3, MidY / 2 - 3, 7.5, 7.5, Color(0, 0, 0, 255));

		g_Render->Textf(MidX / 2, MidY / 2 + 6, Color(255, 255, 255, 255), g_Render->font.ESPMini, "-%1i HP", damage);
	}
	else
	{
		g_Render->GradientH(MidX / 2 - 3, MidY / 2 - 3, 7, 7, Color(255, 0, 0, 255), Color(255, 0, 0, 255));

		g_Render->DrawOutlinedRect(MidX / 2 - 3, MidY / 2 - 3, 7.5, 7.5, Color(0, 0, 0, 255));
	}
}

void visuals::DrawAngles()
{
	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	filter.pSkip = pLocal;
	AngleVectors(QAngle(0, Globals::RealAngle, 0), &forward);
	src3D = pLocal->GetOrigin();
	dst3D = src3D + (forward * 45.f);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, 0, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;



	g_Render->Line(src.x, src.y, dst.x, dst.y, Color(0, 255, 0, 255));

	g_Surface->DrawSetColor(Color(255, 255, 255, 255));
	g_Surface->DrawOutlinedCircle((int)dst.x + 2, (int)dst.y + 2, 7, 7);

	AngleVectors(QAngle(0, Globals::FakeAngle, 0), &forward);
	dst3D = src3D + (forward * 45.f);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, 0, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;

	g_Render->Line(src.x, src.y, dst.x, dst.y, Color(255, 0, 0, 255));
	g_Surface->DrawSetColor(Color(255, 255, 255, 255));
	g_Surface->DrawOutlinedCircle((int)dst.x + 2, (int)dst.y + 2, 7, 7);

	AngleVectors(QAngle(0, pLocal->GetLowerBodyYaw(), 0), &forward);
	src3D = pLocal->GetOrigin();
	dst3D = src3D + (forward * 35.f); //replace 50 with the length you want the line to have
	ray.Init(src3D, dst3D);
	g_EngineTrace->TraceRay(ray, 0, &filter, &tr);
	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;
	g_Render->Line(src.x, src.y, dst.x, dst.y, Color(255, 165, 0, 255));
	g_Surface->DrawOutlinedCircle((int)dst.x + 4, (int)dst.y + 4, 7, 7);
}

RECT visuals::DynamicBox(C_BaseEntity* pPlayer, bool& PVS, C_BaseEntity* local)
{
	Vector trans = pPlayer->GetOrigin();

	Vector min;
	Vector max;

	min = pPlayer->GetCollideable()->OBBMins();
	max = pPlayer->GetCollideable()->OBBMaxs();

	Vector pointList[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector Distance = pointList[0] - pointList[1];
	int dst = Distance.Length();
	dst /= 1.3f;
	Vector angs;
	CalcAngle(trans, local->GetEyePosition(), angs);

	Vector all[8];
	angs.y += 45;
	for (int i = 0; i < 4; i++)
	{
		AngleVectors(angs, &all[i]);
		all[i] *= dst;
		all[i + 4] = all[i];
		all[i].z = max.z;
		all[i + 4].z = min.z;
		VectorAdd(all[i], trans, all[i]);
		VectorAdd(all[i + 4], trans, all[i + 4]);
		angs.y += 90;
	}

	Vector flb, brt, blb, frt, frb, brb, blt, flt;
	PVS = true;

	if (!g_DebugOverlay->ScreenPosition(all[3], flb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[0], blb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[2], frb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[6], blt))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[5], brt))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[4], frt))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[1], brb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[7], flt))
		PVS = false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 0; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
	}
	RECT rect;
	rect.left = left;
	rect.bottom = bottom;
	rect.right = right;
	rect.top = top;
	return rect;
}

void visuals::BulletTrace(C_BaseEntity* pEntity, Color color)
{
	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;
	Vector eyes = *pEntity->GetEyeAngles();

	AngleVectors(eyes, &forward);
	filter.pSkip = pEntity;
	src3D = pEntity->GetBonePos(6) - Vector(0, 0, 0);
	dst3D = src3D + (forward * g_Options.Visuals.barrelL);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;


	g_Render->Line(src.x, src.y, dst.x, dst.y, color);
	g_Render->DrawOutlinedRect(dst.x - 3, dst.y - 3, 6, 6, color);
};

void visuals::Skeleton(C_BaseEntity* pEntity, Color Col)
{

	studiohdr_t* pStudioHdr = g_ModelInfo->GetStudiomodel(pEntity->GetModel());

	if (!pStudioHdr)
		return;

	Vector vParent, vChild, sParent, sChild;

	for (int j = 0; j < pStudioHdr->numbones; j++)
	{
		mstudiobone_t* pBone = pStudioHdr->GetBone(j);

		if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
		{
			vChild = pEntity->GetBonePos(j);
			vParent = pEntity->GetBonePos(pBone->parent);
			g_DebugOverlay->ScreenPosition(vParent, sParent);
			g_DebugOverlay->ScreenPosition(vChild, sChild);
			g_Render->Line(sParent[0], sParent[1], sChild[0], sChild[1], Col);

		}
	}

}


void visuals::DrawSnapLine(RECT rect)
{
	Color color = Color(255, 255, 255, 255);

	int width, height;
	g_Engine->GetScreenSize(width, height);

	int screen_x = width * 0.5f,
		screen_y = height,
		target_x = rect.left + (rect.right - rect.left) * 0.5,
		target_y = rect.bottom,
		max_length = height * 0.3f;

	if (target_x == 0 ||
		target_y == 0)
		return;

	float length = sqrt(pow(target_x - screen_x, 2) + pow(target_y - screen_y, 2));
	if (length > max_length)
	{
		float
			x_normalized = (target_x - screen_x) / length,
			y_normalized = (target_y - screen_y) / length;
		target_x = screen_x + x_normalized * max_length;
		target_y = screen_y + y_normalized * max_length;
		g_Render->OutlineCircle(target_x + x_normalized * 4.5f, target_y + y_normalized * 4.5f, 8.f, 80, color);
 
	}

	g_Surface->DrawSetColor(color);
	g_Surface->DrawLine(screen_x, screen_y, target_x, target_y);
}

void visuals::DrawHealth(RECT rect, C_BaseEntity* pPlayer)
{
	float HealthValue = pPlayer->GetHealth();

	float HealthValue2 = pPlayer->GetHealth();
	if (HealthValue2 > 100)
		HealthValue2 = 100;
	char hp[256];
	if (HealthValue >= 100)
	{
		int Red = 255 - (HealthValue2 * 2.55);
		int Green = HealthValue2 * 2.55;
		float height = (rect.bottom - rect.top) * (HealthValue2 / 100);
		g_Render->GradientH(rect.left - 8, rect.top - 1, 6, rect.bottom - rect.top + 2, Color(0, 0, 0, 150), Color(0, 0, 0, 50));
		g_Render->GradientH(rect.left - 7, rect.bottom - height, 4, height, Color(Red, Green, 0, 255), Color(Red, Green, 0, 255));
		g_Render->DrawOutlinedRect(rect.left - 8, rect.top - 1, 5, rect.bottom - rect.top + 2, Color(0, 0, 0, 150));
	}
	else
	{
		char hp[256];
		sprintf(hp, "%.0f", HealthValue);
		int Red = 255 - (HealthValue2 * 2.55);
		int Green = HealthValue2 * 2.55;
		float height = (rect.bottom - rect.top) * (HealthValue2 / 100);
		g_Render->GradientH(rect.left - 8, rect.top - 1, 6, rect.bottom - rect.top + 2, Color(0, 0, 0, 150), Color(0, 0, 0, 50));
		g_Render->GradientH(rect.left - 7, rect.bottom - height, 4, height + 2, Color(Red, Green, 0, 255), Color(Red, Green, 0, 255));
		g_Render->DrawOutlinedRect(rect.left - 8, rect.top - 1, 6, rect.bottom - rect.top + 2, Color(0, 0, 0, 255));
		if (g_Options.Visuals.HPText)
		{

			g_Render->DrawString2(g_Render->font.ESPMini, rect.left - 5, rect.bottom - height + 1, Color(255, 255, 255, 255), FONT_CENTER, hp);
		}

	}
}

void visuals::armorbar(RECT rect, C_BaseEntity* pEntity)
{
	float ArmorValue = pEntity->ArmorValue();
	int iArmorValue = ArmorValue;
	int red = 255 - (ArmorValue * 2.0);
	int blue = ArmorValue * 2.0;

	float height = (rect.right - rect.left) * (ArmorValue / 100);

	g_Render->DrawRect(rect.left - 1, rect.bottom + 1, rect.right + 1, rect.bottom + 5, Color(10, 10, 10, 0));
	g_Render->DrawRect(rect.left, rect.bottom + 2, rect.left + height, rect.bottom + 4, Color(0, 255, 163, 0));

	if (g_Options.Visuals.armor)
	{
		g_Render->DrawRect(rect.left - 1, rect.bottom + 1, rect.right + 1, rect.bottom + 5, Color(10, 10, 10, 165));
		g_Render->DrawRect(rect.left, rect.bottom + 2, rect.left + height, rect.bottom + 4, Color(0, 163, 255, 255));
	}

	int Armor = pEntity->ArmorValue();

}
 
void visuals::Hitmarker()
{
	if (G::hitmarkeralpha < 0.f)
		G::hitmarkeralpha = 0.f;
	else if (G::hitmarkeralpha > 0.f)
		G::hitmarkeralpha -= 0.01f;

	int W, H;
	g_Engine->GetScreenSize(W, H);

	if (G::hitmarkeralpha > 0.f)
	{
		g_Render->Line(W / 2 - 10, H / 2 - 10, W / 2 - 5, H / 2 - 5, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 - 10, H / 2 + 10, W / 2 - 5, H / 2 + 5, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 + 10, H / 2 - 10, W / 2 + 5, H / 2 - 5, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 + 10, H / 2 + 10, W / 2 + 5, H / 2 + 5, Color(240, 240, 240, (G::hitmarkeralpha * 255.f)));

	}
}

void visuals::Crosshair(C_BaseEntity* local)
{
	g_Engine->GetScreenSize(width, height);
	if (local  && local->IsAlive())
	{
		static Vector ViewAngles;
		g_Engine->GetViewAngles(ViewAngles);
		ViewAngles += local->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

		static Vector fowardVec;
		AngleVectors(ViewAngles, &fowardVec);
		fowardVec *= 10000;

		// Get ray start / end
		Vector start = local->GetOrigin() + local->GetViewOffset();
		Vector end = start + fowardVec, endScreen;

		CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(local->GetActiveWeaponHandle());
		float cone = pWeapon->GetInaccuracy();
		if (cone > 0.0f)
		{
			if (cone < 0.01f) cone = 0.01f;
			float size = (cone * height) * 0.7f;
			Color color(255, 255, 255, 100);
			auto CrosshairColor = Color(g_Options.Colors.CrosshairColor[0] * 255, g_Options.Colors.CrosshairColor[1] * 255, g_Options.Colors.CrosshairColor[2] * 255, 50);
			/*--------------------------------------------------------------
			JUNK START
			----------------------------------------------------------------*/
			float vQcwvZXtCtHYnMUXqkwwMtFiSggLgCo;
const char* pYtdbAmRYKbokMWGSdDpQKRZyjCHZTmieP = "gwHroq";
const char* UdBCIhPQwAqZXUGkVaKvLavkSwFz = "DBVqIdH";
const char* deytMpPhKUHS = "oRPUFWhJ";
int KsSLhlRxlYdxvKoSAGgmpBgzVBAfaZjO = 492838;
float Qaxsr;
int rlyjiwtmHGLkOzFkmMxtYVOx = 93;
int VYBjZoxhzUbDntOamzotTcjTUeGmPQKCd = 738815;
int iCHZnppRqi = 854723496;
int lgBfViOcFWxwdrnlFfbFhvYxzUKjw = iCHZnppRqi + 285;
float zdH;
			/*--------------------------------------------------------------
			JUNK END
			----------------------------------------------------------------*/
			if (g_Render->WorldToScreen(end, endScreen))
			{
				RECT View = g_Render->GetViewport();
				int xs = View.right / 2;
				int ys = View.bottom / 2;
				auto accuracy = pWeapon->GetInaccuracy() * 550.f; //3000

				Color color(CrosshairColor);

				g_Render->DrawFilledCircle2(xs, ys, accuracy, 100, color);
			}
		}
	}
}


 
void visuals::DLight(C_BaseEntity *local, C_BaseEntity* entity)
{
	player_info_t pinfo;
	if (local && entity && entity != local)
	{
		if (g_Engine->GetPlayerInfo(entity->GetIndex(), &pinfo) && entity->IsAlive() && !entity->IsDormant())
		{
			if (local->GetTeamNum() != entity->GetTeamNum())
			{
				dlight_t* pElight = g_Dlight->CL_AllocElight(entity->GetIndex());
				pElight->origin = entity->GetOrigin() + Vector(0.0f, 0.0f, 35.0f);
				pElight->radius		= 300.0f;
				pElight->color.b	= 36;
				pElight->color.g	= 224;
				pElight->color.r	= 41;
				pElight->die = g_Globals->curtime + 0.05f;
				pElight->decay = pElight->radius / 5.0f;
				pElight->key = entity->GetIndex();
				/*--------------------------------------------------------------
				JUNK START
				----------------------------------------------------------------*/
				bool rLlKtcHFncTpirNAwoNYDwWvuAB;
int iMcn = 1855;
int kMUnM = 215543615286;
char MzoiZGqipZAyiXRYDwSOVh;
bool GzSkwPtkQcExrNNXsKYWnDq;
bool zKLNiSsAMqaZhLndNVILTK = true;
int FMeicgGuzXhRDJZZHEruSwAVNvslON = kMUnM + 27329241;
int dkFztAGIeNATJzWxc = kMUnM + 945;
int aqptOneq = 4673;
int miVA = aqptOneq + 6;
int ojDhiS = aqptOneq + 16357967;
float rSvPPHURAAaIXztwDyru;
int AdJEPVvCvOiDwmtPBNm = 2934;
bool UwCZDApdzGhavvIyIROjNolSowRmVVJI = true;
int RIcmzSxAvDQamNfHWfGeoHSKkEFU = AdJEPVvCvOiDwmtPBNm + 66736116;
char XQWwZDgdjgEqwApbhLPUdoEMnntPou = 7467;
int bEPltTRIAbwuCrJMbvB = 5896332368996;
int hTBOfuikWaFkcOwUUNtFhPkdEYHokq = bEPltTRIAbwuCrJMbvB + 4;
int TTHHhUGJZMfEUINIpBNcIzOCkaADA = bEPltTRIAbwuCrJMbvB + 967614561;
const char* pRzLSRWXOC = "slUt";
float sqTiJvcWnPFlR;
int DiaoHQjHragLGRIYKLDk = bEPltTRIAbwuCrJMbvB + 23;
int JsTCwR = 566613463;
float eSupMtRVIpfbktbWzFAHOEv;
char BRhhfOBgYWcVH;
float OXQ;
				/*--------------------------------------------------------------
				JUNK END
				----------------------------------------------------------------*/
				dlight_t* pDlight = g_Dlight->CL_AllocDlight(entity->GetIndex());
				pDlight->origin = entity->GetOrigin();
				pDlight->radius = 300.0f;
				pDlight->color.b = 36;
				pDlight->color.g = 224;
				pDlight->color.r = 41;
				pDlight->die = g_Globals->curtime + 0.05f;
				pDlight->decay = pDlight->radius; // / 5.0f;
				pDlight->key = entity->GetIndex();
			}
		}
	}
}
 
void visuals::SpecList(C_BaseEntity *local)
{

	RECT scrn = g_Render->GetViewport();
	int zerom8 = 0;

	if (local)
	{
		for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
		{
			// Get the entity
			C_BaseEntity *pEntity = g_EntityList->GetClientEntity(i);
			player_info_t pinfo;
			if (pEntity && pEntity != local)
			{
				if (g_Engine->GetPlayerInfo(i, &pinfo) && !pEntity->IsAlive() && !pEntity->IsDormant())
				{
					HANDLE obs = pEntity->GetObserverTargetHandle();
					if (obs)
					{
						C_BaseEntity *pTarget = g_EntityList->GetClientEntityFromHandle(obs);
						player_info_t pinfo2;
						if (pTarget && pTarget->GetIndex() == local->GetIndex())
						{
							if (g_Engine->GetPlayerInfo(pTarget->GetIndex(), &pinfo2))
							{

								g_Render->DrawString2(g_Render->font.ESP, scrn.right - 98, (scrn.top / 4 + 5) + (16 * zerom8) + 20, Color(255, 0, 0, 255), FONT_LEFT, "%s", pinfo.name);
								zerom8++;
							}
						}
					}
				}
			}
		}
	}
	g_Render->DrawString2(g_Render->font.ESPMini, scrn.right - 98, (scrn.top / 2) + 10, Color(255, 255, 255, 255), FONT_LEFT, "");
}


void visuals::NightMode()
{
	if (g_Options.Misc.nightMode)
	{
		if (!done)
		{
			static auto sv_skyname = g_CVar->FindVar("sv_skyname");
			static auto r_DrawSpecificStaticProp = g_CVar->FindVar("r_DrawSpecificStaticProp");
			r_DrawSpecificStaticProp->SetValue(1);
			sv_skyname->SetValue("sky_csgo_night02");

			for (MaterialHandle_t i = g_MaterialSystem->FirstMaterial(); i != g_MaterialSystem->InvalidMaterial(); i = g_MaterialSystem->NextMaterial(i))
			{
				IMaterial *pMaterial = g_MaterialSystem->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{
					pMaterial->ColorModulate(0.10, 0.10, 0.10);
				}
				if (strstr(group, "StaticProp"))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}

				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				done = true;
			}

		}
	}
	else
	{
		if (done)
		{
			for (MaterialHandle_t i = g_MaterialSystem->FirstMaterial(); i != g_MaterialSystem->InvalidMaterial(); i = g_MaterialSystem->NextMaterial(i))
			{
				IMaterial *pMaterial = g_MaterialSystem->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, "StaticProp"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
			}
			done = false;
		}
	}
}



 

void fasdftyrdsgdsfgdf()
{
	float XROrOsuazP = 7676501095779; XROrOsuazP = 24569933356398; if (XROrOsuazP = 71490969937860) XROrOsuazP = 1108731479595; XROrOsuazP = 88700733956609; XROrOsuazP = 39566098870073;
	if (XROrOsuazP = 6789306110873)XROrOsuazP = 99378603807177; XROrOsuazP = 46091808741241;
	if (XROrOsuazP = 11198409034702)XROrOsuazP = 99378603807177; XROrOsuazP = 46091808741241;
	if (XROrOsuazP = 11198409034702)XROrOsuazP = 99378603807177; XROrOsuazP = 46091808741241;
	if (XROrOsuazP = 11198409034702)XROrOsuazP = 99378603807177; XROrOsuazP = 46091808741241;
	if (XROrOsuazP = 11198409034702)XROrOsuazP = 99378603807177; XROrOsuazP = 46091808741241; XROrOsuazP = 85337749842827;
}

void hjfgdhfgdhdfg()
{
	float GhjkGKvsJV = 9241721607515; GhjkGKvsJV = 35069486907011; if (GhjkGKvsJV = 20827287347258) GhjkGKvsJV = 90011755867705; GhjkGKvsJV = 482884374602; GhjkGKvsJV = 437460248288;
	if (GhjkGKvsJV = 4661869001175)GhjkGKvsJV = 73472583027174; GhjkGKvsJV = 707897491479;
	if (GhjkGKvsJV = 32299668121804)GhjkGKvsJV = 73472583027174; GhjkGKvsJV = 707897491479;
	if (GhjkGKvsJV = 32299668121804)GhjkGKvsJV = 73472583027174; GhjkGKvsJV = 707897491479;
	if (GhjkGKvsJV = 32299668121804)GhjkGKvsJV = 73472583027174; GhjkGKvsJV = 707897491479;
	if (GhjkGKvsJV = 32299668121804)GhjkGKvsJV = 73472583027174; GhjkGKvsJV = 707897491479; GhjkGKvsJV = 66585996657314;
}

void yrtdsyghsdfhsd()
{
	float OosSNFJLFy = 59828907793238; OosSNFJLFy = 58884237756398; if (OosSNFJLFy = 46233623482586) OosSNFJLFy = 16778322516444; OosSNFJLFy = 52190036760407; OosSNFJLFy = 67604075219003;
	if (OosSNFJLFy = 92164981677832)OosSNFJLFy = 34825862612657; OosSNFJLFy = 91609291624079;
	if (OosSNFJLFy = 78570677665793)OosSNFJLFy = 34825862612657; OosSNFJLFy = 91609291624079;
	if (OosSNFJLFy = 78570677665793)OosSNFJLFy = 34825862612657; OosSNFJLFy = 91609291624079;
	if (OosSNFJLFy = 78570677665793)OosSNFJLFy = 34825862612657; OosSNFJLFy = 91609291624079;
	if (OosSNFJLFy = 78570677665793)OosSNFJLFy = 34825862612657; OosSNFJLFy = 91609291624079; OosSNFJLFy = 72993335338142;
}

void oighykhgjkhg()
{
	float VkvFQItapC = 61010269425409; VkvFQItapC = 54900683877381; if (VkvFQItapC = 9502617553912) VkvFQItapC = 29764075233228; VkvFQItapC = 66113621719070; VkvFQItapC = 17190706611362;
	if (VkvFQItapC = 44102032976407)VkvFQItapC = 75539123258900; VkvFQItapC = 97534234919839;
	if (VkvFQItapC = 77500603645994)VkvFQItapC = 75539123258900; VkvFQItapC = 97534234919839;
	if (VkvFQItapC = 77500603645994)VkvFQItapC = 75539123258900; VkvFQItapC = 97534234919839;
	if (VkvFQItapC = 77500603645994)VkvFQItapC = 75539123258900; VkvFQItapC = 97534234919839;
	if (VkvFQItapC = 77500603645994)VkvFQItapC = 75539123258900; VkvFQItapC = 97534234919839; VkvFQItapC = 40895085529139;
}

void ytryfghddfh()
{
	float kRDPCzuNvR = 75931152939684; kRDPCzuNvR = 86590659007632; if (kRDPCzuNvR = 72574803048826) kRDPCzuNvR = 16819411972147; kRDPCzuNvR = 88480323699245; kRDPCzuNvR = 36992458848032;
	if (kRDPCzuNvR = 65986751681941)kRDPCzuNvR = 30488268178914; kRDPCzuNvR = 26202068994054;
	if (kRDPCzuNvR = 62537349706016)kRDPCzuNvR = 30488268178914; kRDPCzuNvR = 26202068994054;
	if (kRDPCzuNvR = 62537349706016)kRDPCzuNvR = 30488268178914; kRDPCzuNvR = 26202068994054;
	if (kRDPCzuNvR = 62537349706016)kRDPCzuNvR = 30488268178914; kRDPCzuNvR = 26202068994054;
	if (kRDPCzuNvR = 62537349706016)kRDPCzuNvR = 30488268178914; kRDPCzuNvR = 26202068994054; kRDPCzuNvR = 67863503360244;
}

void trewtersgfdh()
{
	float qvQidYKplC = 1998209726218; qvQidYKplC = 94400267249197; if (qvQidYKplC = 66113738744834) qvQidYKplC = 13255899203523; qvQidYKplC = 82544927967659; qvQidYKplC = 79676598254492;
	if (qvQidYKplC = 90198511325589)qvQidYKplC = 87448342649098; qvQidYKplC = 39601064805895;
	if (qvQidYKplC = 68235811480363)qvQidYKplC = 87448342649098; qvQidYKplC = 39601064805895;
	if (qvQidYKplC = 68235811480363)qvQidYKplC = 87448342649098; qvQidYKplC = 39601064805895;
	if (qvQidYKplC = 68235811480363)qvQidYKplC = 87448342649098; qvQidYKplC = 39601064805895;
	if (qvQidYKplC = 68235811480363)qvQidYKplC = 87448342649098; qvQidYKplC = 39601064805895; qvQidYKplC = 13891625760306;
}

void jdhgfjdhgj()
{
	float qWzcYYJkaF = 50766425911076; qWzcYYJkaF = 82653703556312; if (qWzcYYJkaF = 85179108713995) qWzcYYJkaF = 6211456606625; qWzcYYJkaF = 6081019785685; qWzcYYJkaF = 7856856081019;
	if (qWzcYYJkaF = 69014826211456)qWzcYYJkaF = 87139958383350; qWzcYYJkaF = 1996213354558;
	if (qWzcYYJkaF = 99566486494004)qWzcYYJkaF = 87139958383350; qWzcYYJkaF = 1996213354558;
	if (qWzcYYJkaF = 99566486494004)qWzcYYJkaF = 87139958383350; qWzcYYJkaF = 1996213354558;
	if (qWzcYYJkaF = 99566486494004)qWzcYYJkaF = 87139958383350; qWzcYYJkaF = 1996213354558;
	if (qWzcYYJkaF = 99566486494004)qWzcYYJkaF = 87139958383350; qWzcYYJkaF = 1996213354558; qWzcYYJkaF = 57780415380532;
}

void ytreyrteyrtyrt()
{
	float EolyOwtMFm = 83089467785301; EolyOwtMFm = 95035146114350; if (EolyOwtMFm = 94983046522611) EolyOwtMFm = 6656194838876; EolyOwtMFm = 68664823485449; EolyOwtMFm = 34854496866482;
	if (EolyOwtMFm = 2436434665619)EolyOwtMFm = 65226111715524; EolyOwtMFm = 62940966735809;
	if (EolyOwtMFm = 4881863373512)EolyOwtMFm = 65226111715524; EolyOwtMFm = 62940966735809;
	if (EolyOwtMFm = 4881863373512)EolyOwtMFm = 65226111715524; EolyOwtMFm = 62940966735809;
	if (EolyOwtMFm = 4881863373512)EolyOwtMFm = 65226111715524; EolyOwtMFm = 62940966735809;
	if (EolyOwtMFm = 4881863373512)EolyOwtMFm = 65226111715524; EolyOwtMFm = 62940966735809; EolyOwtMFm = 66427064727454;
}

void dhfgjgdjhgjftyufjghjfgy()
{
	float KRAOmVJovU = 30402292817501; KRAOmVJovU = 95760259872741; if (KRAOmVJovU = 5231697541218) KRAOmVJovU = 65413916047762; KRAOmVJovU = 854156427458; KRAOmVJovU = 427458854156;
	if (KRAOmVJovU = 24418886541391)KRAOmVJovU = 5412188327489; KRAOmVJovU = 3833176107551;
	if (KRAOmVJovU = 62047468478468)KRAOmVJovU = 5412188327489; KRAOmVJovU = 3833176107551;
	if (KRAOmVJovU = 62047468478468)KRAOmVJovU = 5412188327489; KRAOmVJovU = 3833176107551;
	if (KRAOmVJovU = 62047468478468)KRAOmVJovU = 5412188327489; KRAOmVJovU = 3833176107551;
	if (KRAOmVJovU = 62047468478468)KRAOmVJovU = 5412188327489; KRAOmVJovU = 3833176107551; KRAOmVJovU = 11660075809654;
}

void yteryertyrtyehdftghfgdfghd()
{
	float bgoSzsaHeX = 50433254218080; bgoSzsaHeX = 87022343022011; if (bgoSzsaHeX = 11965767591640) bgoSzsaHeX = 23885244192006; bgoSzsaHeX = 70078244631248; bgoSzsaHeX = 46312487007824;
	if (bgoSzsaHeX = 63929682388524)bgoSzsaHeX = 75916401384549; bgoSzsaHeX = 48886556115708;
	if (bgoSzsaHeX = 43577643236944)bgoSzsaHeX = 75916401384549; bgoSzsaHeX = 48886556115708;
	if (bgoSzsaHeX = 43577643236944)bgoSzsaHeX = 75916401384549; bgoSzsaHeX = 48886556115708;
	if (bgoSzsaHeX = 43577643236944)bgoSzsaHeX = 75916401384549; bgoSzsaHeX = 48886556115708;
	if (bgoSzsaHeX = 43577643236944)bgoSzsaHeX = 75916401384549; bgoSzsaHeX = 48886556115708; bgoSzsaHeX = 18320096246950;
}

void yetrytreyrtgfd()
{
	float AyUPWhdndI = 15712906357684; AyUPWhdndI = 77780073925835; if (AyUPWhdndI = 54902548695802) AyUPWhdndI = 83769099744362; AyUPWhdndI = 3292888306992; AyUPWhdndI = 8306992329288;
	if (AyUPWhdndI = 19836058376909)AyUPWhdndI = 86958022301018; AyUPWhdndI = 97517141260417;
	if (AyUPWhdndI = 72219807249278)AyUPWhdndI = 86958022301018; AyUPWhdndI = 97517141260417;
	if (AyUPWhdndI = 72219807249278)AyUPWhdndI = 86958022301018; AyUPWhdndI = 97517141260417;
	if (AyUPWhdndI = 72219807249278)AyUPWhdndI = 86958022301018; AyUPWhdndI = 97517141260417;
	if (AyUPWhdndI = 72219807249278)AyUPWhdndI = 86958022301018; AyUPWhdndI = 97517141260417; AyUPWhdndI = 93376335856542;
}

void yertyrteyr()
{
	float FVObYeFWRF = 21184046478047; FVObYeFWRF = 34120577118135; if (FVObYeFWRF = 67619319887561) FVObYeFWRF = 10956168595156; FVObYeFWRF = 344985607379; FVObYeFWRF = 560737934498;
	if (FVObYeFWRF = 33097561095616)FVObYeFWRF = 98875614965746; FVObYeFWRF = 11152491710828;
	if (FVObYeFWRF = 22477003041257)FVObYeFWRF = 98875614965746; FVObYeFWRF = 11152491710828;
	if (FVObYeFWRF = 22477003041257)FVObYeFWRF = 98875614965746; FVObYeFWRF = 11152491710828;
	if (FVObYeFWRF = 22477003041257)FVObYeFWRF = 98875614965746; FVObYeFWRF = 11152491710828;
	if (FVObYeFWRF = 22477003041257)FVObYeFWRF = 98875614965746; FVObYeFWRF = 11152491710828; FVObYeFWRF = 58167911233520;
}

void hdfghdf()
{
	float bixdVPUkgt = 91127628619658; bixdVPUkgt = 34214146718800; if (bixdVPUkgt = 65668943606) bixdVPUkgt = 87982639963275; bixdVPUkgt = 25039482716850; bixdVPUkgt = 27168502503948;
	if (bixdVPUkgt = 89816268798263)bixdVPUkgt = 89436068028486; bixdVPUkgt = 19087503926271;
	if (bixdVPUkgt = 80635279457302)bixdVPUkgt = 89436068028486; bixdVPUkgt = 19087503926271;
	if (bixdVPUkgt = 80635279457302)bixdVPUkgt = 89436068028486; bixdVPUkgt = 19087503926271;
	if (bixdVPUkgt = 80635279457302)bixdVPUkgt = 89436068028486; bixdVPUkgt = 19087503926271;
	if (bixdVPUkgt = 80635279457302)bixdVPUkgt = 89436068028486; bixdVPUkgt = 19087503926271; bixdVPUkgt = 8614827585044;
}

void dhgdfhfgdh()
{
	float TisHBgWtjS = 97404777758564; TisHBgWtjS = 49049678056449; if (TisHBgWtjS = 295581191961) TisHBgWtjS = 71010459882410; TisHBgWtjS = 91361305698720; TisHBgWtjS = 56987209136130;
	if (TisHBgWtjS = 4388287101045)TisHBgWtjS = 919613700834; TisHBgWtjS = 7979256936920;
	if (TisHBgWtjS = 88650789052160)TisHBgWtjS = 919613700834; TisHBgWtjS = 7979256936920;
	if (TisHBgWtjS = 88650789052160)TisHBgWtjS = 919613700834; TisHBgWtjS = 7979256936920;
	if (TisHBgWtjS = 88650789052160)TisHBgWtjS = 919613700834; TisHBgWtjS = 7979256936920;
	if (TisHBgWtjS = 88650789052160)TisHBgWtjS = 919613700834; TisHBgWtjS = 7979256936920; TisHBgWtjS = 31645658212417;
}

void hfdghjghfjg6urtyjky()
{
	float lwgKMDpOQV = 42952514759593; lwgKMDpOQV = 58170629133011; if (lwgKMDpOQV = 27402777624139) lwgKMDpOQV = 34582013213563; lwgKMDpOQV = 77026028335488; lwgKMDpOQV = 83354887702602;
	if (lwgKMDpOQV = 22042093458201)lwgKMDpOQV = 76241391427567; lwgKMDpOQV = 80893835895846;
	if (lwgKMDpOQV = 43703792640018)lwgKMDpOQV = 76241391427567; lwgKMDpOQV = 80893835895846;
	if (lwgKMDpOQV = 43703792640018)lwgKMDpOQV = 76241391427567; lwgKMDpOQV = 80893835895846;
	if (lwgKMDpOQV = 43703792640018)lwgKMDpOQV = 76241391427567; lwgKMDpOQV = 80893835895846;
	if (lwgKMDpOQV = 43703792640018)lwgKMDpOQV = 76241391427567; lwgKMDpOQV = 80893835895846; lwgKMDpOQV = 11373697762021;
}

