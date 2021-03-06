#pragma once
#include "HookIncludes.h"
#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);
std::unordered_map<char*, char*> killIcons = {};
#define INVALID_EHANDLE_INDEX 0xFFFFFFFF
HANDLE worldmodel_handle;
CBaseCombatWeapon* worldmodel;

int GetKnifeDefinitionIndex(int si)
{
	// 0 - Bayonet, 1 - Flip, 2 - Gut, 3 - Karambit, 4 - M9Bayonet, 5 - Huntsman, 6 - Falchion, 7 - Bowie, 8 - Butterfly, 9 - Daggers, 10 - Golden
	switch (si)
	{
	case 0:
		return 500;
	case 1:
		return 505;
	case 2:
		return 506;
	case 3:
		return 507;
	case 4:
		return 508;
	case 5:
		return 509;
	case 6:
		return 512;
	case 7:
		return 514;
	case 8:
		return 515;
	case 9:
		return 516;
	default:
		return -1;
	}
}

int GetCurrentKnifeModel(int currentKnife)
{
	// 0 - Bayonet, 1 - Flip, 2 - Gut, 3 - Karambit, 4 - M9Bayonet, 5 - Huntsman, 6 - Falchion, 7 - Bowie, 8 - Butterfly, 9 - Daggers, 10 - Golden
	switch (currentKnife)
	{
	case 0:
		return g_ModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl"); //Bayo
	case 1:
		return g_ModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl"); //Flip
	case 2:
		return g_ModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl"); //Gut
	case 3:
		return g_ModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl"); //Karambit
	case 4:
		return g_ModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl"); //M9 Bayo
	case 5:
		return g_ModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl"); //Huntsman
	case 6:
		return g_ModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl"); //Falchion
	case 7:
		return g_ModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl"); //Bowie
	case 8:
		return g_ModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl"); //Butterfly
	case 9:
		return g_ModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl"); //Daggers
	case 10:
		return g_ModelInfo->GetModelIndex("models/weapons/v_knife_gg.mdl"); //GunGame
	default:
		return 0;
	}
}

void SkinChanger() {
	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	auto weapons = pLocal->m_hMyWeapons();
	for (size_t i = 0; weapons[i] != INVALID_EHANDLE_INDEX; i++)
	{
		C_BaseEntity *pEntity = g_EntityList->GetClientEntityFromHandle(weapons[i]);
		if (pEntity)
		{
			CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)pEntity;
			if (g_Options.Skinchanger.Enabled)
			{

				int weapon = *pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex();
				if (weapon)
				{
					if (g_Options.Skinchanger.W[weapon].ChangerSkin != 0)
						*pWeapon->FallbackPaintKit() = g_Options.Skinchanger.W[weapon].ChangerSkin;
				}
				if (g_Options.Skinchanger.knifemodel > 0)
				{
					if (pEntity->GetClientClass()->m_ClassID)
					{
						if (pEntity->GetClientClass()->m_ClassID == (int)ClassID::CKnife)
						{
							worldmodel_handle = pWeapon->m_hWeaponWorldModel();
							if (worldmodel_handle) worldmodel = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(worldmodel_handle);


							*pWeapon->GetEntityQuality() = 3;

							*pWeapon->ModelIndex() = GetCurrentKnifeModel(g_Options.Skinchanger.knifemodel - 1); // m_nModelIndex
							*pWeapon->ViewModelIndex() = GetCurrentKnifeModel(g_Options.Skinchanger.knifemodel - 1);
							if (worldmodel) *worldmodel->ModelIndex() = GetCurrentKnifeModel(g_Options.Skinchanger.knifemodel - 1) + 1;
							*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = GetKnifeDefinitionIndex(g_Options.Skinchanger.knifemodel - 1);
							*pWeapon->FallbackPaintKit() = g_Options.Skinchanger.W[GetKnifeDefinitionIndex(g_Options.Skinchanger.knifemodel - 1)].ChangerSkin; // Lore 
						}
					}
				}

				/*		OTHER	(to be added)
				*pWeapon->FallbackStatTrak() = amount;
				snprintf(pWeapon->GetCustomName(), 32, "get text from imgui string box");
				*/
				// Junk
				char HIavqbQDFQwePn = 647165184;
int LrpsOmaFCJykBkpwuxrPrAIO = 6866518;
bool GrKhrpFdHUQggFLOnbTGOkdmhp = true;
bool nVCikdVvuOTxJ = false;
char jYJVrMZoOqdaGJcs = 819;
const char* VfMuXJjXCknIXfeIpBnySedYhHhRyCqxey;
int yxagwNiLYgIYJhISEDol = 18225;
float ScUikTGvyzhMBphPcolPKKuc;
const char* JLgembMIAqEItGdHQyWYJ = "Nfhs";
int NvtfZbVcAlbcVa = 49542;
float cIwpVfph;
int gIjFXDOAtZyjZjeyFOYeudxZdPMTfHKK = 98815748;
int sKWifWpwAafXm = 37574821863;
const char* nDSaDN = "tnDF";
char WDFwTBbauLfFDBnCUmAjcvPXvpocB;
float yEgomj;
				// JUnk
				*pWeapon->OwnerXuidLow() = 0;
				*pWeapon->OwnerXuidHigh() = 0;
				*pWeapon->FallbackWear() = g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerWear;
				*pWeapon->FallbackStatTrak() = g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerStatTrak;
				*pWeapon->m_AttributeManager()->m_Item()->ItemIDHigh() = 1;
				snprintf(pWeapon->GetCustomName(), 32, &g_Options.Skinchanger.W->ChangerName[32]);
			}
		}

	}
}


