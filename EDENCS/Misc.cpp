#include "Misc.h"
#include "Interfaces.h"
#include "Render.h"
#include <time.h>
#include "BaseClient.h"
#include "Strafer.h"
#include "megaJunkCode.h"

std::string animatedclantag;
int iLastTime;
bool bDone = false;
	static void  setName( const char* name )
	{
		static ConVar* namevar = g_CVar->FindVar("name");
		*reinterpret_cast< int* >( reinterpret_cast< DWORD >( &namevar->fnChangeCallback ) + 0xC ) = NULL;
		namevar->SetValue( name );
	}
 

	static void sniperName()
	{
		static char* DrawCrosshairWeaponTypeCheck = (reinterpret_cast<char*>(L"client.dll"), ("83 F8 05 75 17"));
		 
		DWORD dwOldProtect;
		DWORD dwNewProtect;

		VirtualProtectEx(GetCurrentProcess(), DrawCrosshairWeaponTypeCheck, 3, PAGE_EXECUTE_READWRITE, &dwOldProtect);

		*((DrawCrosshairWeaponTypeCheck + 0x2)) = 0xFF;

		VirtualProtectEx(GetCurrentProcess(), DrawCrosshairWeaponTypeCheck, 3, dwOldProtect, &dwNewProtect);
		/*-------------------------------------------------------------*/
		int mAOnfJcOlnqNBuBJKBYDBhZDsJToQRHp = 61;
		int qveQffMOVddpi = 198482462;
		bool hOjY;
		char JNmZTNYuJRPf;
		int onquPRPGM = 442467;
		int HQjupoUSDbNcZ =  + 1929984;
		char cpqMXJPPOpwgGcbQRZDkHgY;
		int pqBRmlazuEpmqlxIwmfsH = 1357416617764991;
		int eXZLicHqzGAhckyHZgEcA = pqBRmlazuEpmqlxIwmfsH + 53576;
		char LNhciqKQlfUykcUBndWgZroYWKSwMxxH = 421;
		float QCTEAcndkuDZXwjzTxCdBJFLeqT;
		int ZBYNegbsxPKyRpWOaAncRzgmc = 5366536;
		int UbD = ZBYNegbsxPKyRpWOaAncRzgmc + 8723;
		char lyIihniozTuMOwRGIoClmQ;
		int RwUdlS = ZBYNegbsxPKyRpWOaAncRzgmc + 922936362;
		/*-------------------------------------------------------------*/
	}

	void start()
	{
		if (g_Options.Visuals.noscopeborder)
		{
			sniperName();
	/*-------------------------------------------------------------*/
	char ekMjwXacQtjhfTccXixKUarpQRLSMu = 575;
	const char* KQYibPJAXzYJdAkueXkLGz = "nIWKYrV";
	bool ufDtslNokBAorLlQAWgyMwdlPL = true;
	float OLHkZvWribNrwLqOtfUxagSiWDQ;
	bool IjqOeaapvzOUC = true;
	int xTNGrDSjumHxCUIDmGorzFruTYzgZR = 63;
	int thFRNzJbmQLGvTXOjgGnnLbpDLlvAAz = 51112524953588695;
	const char* bDolbgrmjIFGnaQpWZghWYTOMIJZbfuD = "oxme";
	int AjJVBckL = 3;
	const char* vifVETmqrHkpLCejoITHNTpofTElgUfh = "CpUCoIc";
	char ryfR;
	int csabTLHGYO = 98612437;
	int sZqZgUdByIehHpTczrqLospCutopWKWQFX = 112528786914;
	float AbqqJWD;
	int DwFu = sZqZgUdByIehHpTczrqLospCutopWKWQFX + 9166939;
	const char* iWcUljn;
	const char* ohuxphOvVjGDcFzzT;
	int nCBFEROctfinWBamLzsmLChpnPDaoaxV = 9814137859477;
	int UdUnSHNrPJBtpSmNOwvVbavO = nCBFEROctfinWBamLzsmLChpnPDaoaxV + 8;
	const char* vJKJHGiWGCGKOPfuufsipaM;
	const char* JZlxwvXRyMAvCZV = "otxQRgM";
	int daFWyqgSzwvytXYxpNleceFDUVQOIAdh = nCBFEROctfinWBamLzsmLChpnPDaoaxV + 59135;
	int SLBiSqzRGtmTUhNZbuofFrBn = nCBFEROctfinWBamLzsmLChpnPDaoaxV + 4;
	char xYDJd;
	float dzwJvkPZnmQcDcQWRHVp;
	float YsABTMlWjgsG;
	char zywLzCRrDVEWqKB;
	int lsgSvqydJnMJBo = 7;
	int oWg = lsgSvqydJnMJBo + 877919;
	char GXtddsfQSAZyQqEobAjCoc;
	const char* YiWKdQGFyXjjyvkUOapdvFBUgOnBGDiWgl;
	int IqXxKaRhOhnpCaZKOSpbjlZwIhhCg = lsgSvqydJnMJBo + 47637916;
	char Lfy;
	int gcmUJZXayDRohGZzXVsHMcoowOrgVzOw = 265813477;
	int fWeHyJyVDnuQbz = 276396785;
	int pkIRzrCyOPGnCMqbxbUTDqb = 713996918551;
	float tIJxTWqdwjJ;
	bool yycIV = false;
	bool joHiybZoWaVc;
	int WpJhVtKWneoGWszvpsKD = 2147143;
	char gVpshjcDrKpENnUZPlqIWtNC;
				int igMOQwrfW = WpJhVtKWneoGWszvpsKD + 82336;
	int nqahpbFEQRllXVAkTm = 113179472147715885;
	int dxzQfp = 73;
	int eiWfiHyvKjcWkhULcEkidv = 5296586131;
	const char* BgeMSibthcrRLOGbHBQwhzgTOLucjhqNs = "ymmE";
			/*-------------------------------------------------------------*/
		}
	}

void misc::OnCreateMove(CInput::CUserCmd *cmd, C_BaseEntity *local)
{

	if (g_Options.Misc.MemeWalk && local->IsAlive())
	{
		if (cmd->forwardmove > 0)
		{
			cmd->buttons |= IN_BACK;
			cmd->buttons &= ~IN_FORWARD;
		}

		if (cmd->forwardmove < 0)
		{
			cmd->buttons |= IN_FORWARD;
			cmd->buttons &= ~IN_BACK;
		}

		if (cmd->sidemove < 0)
		{
			cmd->buttons |= IN_MOVERIGHT;
			cmd->buttons &= ~IN_MOVELEFT;
		}

		if (cmd->sidemove > 0)
		{
			cmd->buttons |= IN_MOVELEFT;
			cmd->buttons &= ~IN_MOVERIGHT;
		}

	}

	if (g_Options.Misc.Bhop && local->IsAlive())
	{
		if (cmd->buttons & IN_JUMP && !(local->GetMoveType() & MOVETYPE_LADDER))
		{

			int iFlags = local->GetFlags();
			if (!(iFlags & FL_ONGROUND))
				cmd->buttons &= ~IN_JUMP;
			/*-------------------------------------------------------------*/
			const char* hrwVpXIwVQIM = "JWXBE";
			char vAZkqk;
			int fOmBqfbhGpextAHKGOeFpVEZzhSbnav = 74292566;
			bool FGSrZrQfhMxgNUyNiwiZknclS;
			bool BmVuBunSfsBeQEMOkrQFjdkRghqqvLU = true;
			float JVMxdmHaSgvRcVIhsydthTKbWbSfvTT;
			int ccdcKf = 62138238;
			float rfMOayibeVvaPmheffghvEEYsuv;
			int SXftfBNrNNZycXuUoYgVkYhmJWsIRYY = 1927852597663535;
			int ciCJnrptuLT = SXftfBNrNNZycXuUoYgVkYhmJWsIRYY + 89695681;
			int ELvneXAyNbNNfXZhcyBYuzX = SXftfBNrNNZycXuUoYgVkYhmJWsIRYY + 41914242;
			char JvDUZEnFr;
			int hKScNYjjdBkxnPEliZUghIAqyZl = SXftfBNrNNZycXuUoYgVkYhmJWsIRYY + 6;
			int yTWyMLUeAIlqtTIeJNA = 657754;
			int jftKpLPEuqxkIQvjmFzlWYvCYrmpceM = yTWyMLUeAIlqtTIeJNA + 85662384;
			float XehhPvZGwisjckROUqYZQd;
			const char* OuqKPgUUjSqqI;
			int pmiYIVCQ = 879493622441;
			char sgkJDfQvJL = 9236;
			int rzJB = pmiYIVCQ + 7827;
			bool dEQqzeRtPPsOLWnE = false;
			int NBLTSxBEbeayrgrGK = pmiYIVCQ + 2149;
			int JcOtCHRpGWljpqYrZZLvaQZY = 71375765;
			float DUsckApHyfYs;
			bool AgbehwBwygXRIMpC = false;
			int Vtr = 83967631;
			int cNZbnBPwnAwNuPDntIFmytH = 6;
			bool hwcubWTjAJUOrvRIJxhesAAZpK = false;
			bool TJwUbDxBAgXUALojNXGVURQNbpIYBJQ;
			bool qPwScgtroLSDQbDFeKAziRLwkdDrrAF;
			int hYLRjltxCyC = cNZbnBPwnAwNuPDntIFmytH + 68767;
			const char* VLAucJpxIsYRLv;
			char OKqlcJrfDIXdLjKtHsZMKfGuM;
			bool vZmplzerP = false;
			const char* XTnNDf = "vJY";
			int sZRorFNeONOlhUQGQxMcFK = cNZbnBPwnAwNuPDntIFmytH + 4562118;
			char PDxYVt = 118;
			bool aJcvZIzCCUxspzDgMCHNxlOymoflNBR = true;
			char xwKVCOVWdHgkmuneQLIrRcJC;
			int sZkjiBEttfsWvqUFK = cNZbnBPwnAwNuPDntIFmytH + 1184363;
			float wtdaDcsjBOp;
			bool aQDSjGMfJ;
			float iIZGiXxvWRHrvyZrlr;
			int geQHwHEIDhVjgOoTuNDwWSoJVagSmPON = cNZbnBPwnAwNuPDntIFmytH + 32499;
			int NPNVJTUbMldFStaIE = 2615597674162921151;
			const char* LxDXylNusBBwgYLQBfcskuz = "PjqV";
			bool KFnrQjcDkZylxSHh;
			int kBgTGIEFLQcbUwDcNzgFMhYHhHKzYZWRq = NPNVJTUbMldFStaIE + 3;
			int KbXAdmxrImothqQaQo = 23;
			int dzRmcPoAuFLwkmeAUumZDSTXZJP = 23766274668;
			char bQFQMaTpJgcFs;
			bool StdZmtSiKOCblWNxPtwaLiOlaR;
			int qHQFNaBEf = 6117712886882351;
			int ZMMRIRrKWejiElhYZjpW = 6998;
			float JEpsYFWMevJEc;
			const char* YmePbmjYvQWswskLhjsZngKeakMuZ = "kNXdI";
			int AhGPlnonqiZAwVCuecLOak = 74435178887855352;
			char LmTmLYWRDHLwNLzDQOLicD = 4112;
			int bbMGgiAaDJpRPsoXWhVqgiPtpor = 71417217693144;
			/*-------------------------------------------------------------*/
		}

	 
		}
 
	if (g_Options.Misc.syncclantag)
	{
		static int counter = 0;
		static int motion = 0;
		int ServerTime = (float)local->GetTickBase() * g_Globals->interval_per_tick * 3.5;

		if (counter % 48 == 0)
			motion++;
		int value = ServerTime % 20;
		switch (value) {
		case 0: setclantag(XorStr("          g")); break;
		case 1: setclantag(XorStr("       ge")); break;
		case 2: setclantag(XorStr("      get")); break;
		case 3: setclantag(XorStr("     gete")); break;
		case 4: setclantag(XorStr("    geted")); break;
		case 5: setclantag(XorStr("   geteden")); break;
		case 6: setclantag(XorStr("  geteden.")); break;
		case 7: setclantag(XorStr(" geteden.us")); break;
		case 8: setclantag(XorStr("eteden.us")); break;
		case 9: setclantag(XorStr("teden.us")); break;
		case 10: setclantag(XorStr("eden.us")); break;
		case 11: setclantag(XorStr("eden.us")); break;
		case 12: setclantag(XorStr("den.us")); break;
		case 13: setclantag(XorStr("en.us")); break;
		case 14: setclantag(XorStr("n.us")); break;
		case 15: setclantag(XorStr(".us")); break;
		case 16: setclantag(XorStr("us")); break;
		case 17: setclantag(XorStr("s")); break;
		case 18: setclantag(XorStr("")); break;
		case 19: setclantag(XorStr("          g")); break;
		case 20: setclantag(XorStr("       ge")); break;
		case 21: setclantag(XorStr("      get")); break;
		case 22: setclantag(XorStr("     gete")); break;
		case 23: setclantag(XorStr("    geted")); break;
		case 24: setclantag(XorStr("   geteden")); break;
		case 25: setclantag(XorStr("  geteden.")); break;
		case 26: setclantag(XorStr(" geteden.us")); break;
		}
		counter++;
	}

	if (!g_Options.Misc.animatedclantag && animatedclantag.c_str() != G::AnimatedClantag)
	{
		animatedclantag = G::AnimatedClantag;
	}
	if (g_Options.Misc.animatedclantag && animatedclantag.length() > 1)
	{
		if (int(g_Globals->curtime) != iLastTime)
		{
			auto length = animatedclantag.length();
			animatedclantag.insert(0, 1, animatedclantag[length - 2]);
			animatedclantag.erase(length - 1, 1);

			setclantag(animatedclantag.c_str());
			iLastTime = int(g_Globals->curtime);
		}
	}
 
	if (g_Options.Misc.namespam)
	{
		char name[150];
		char fucked_char = static_cast<char>(-1);
		for (auto i = 0; i <= 150; i++)
			name[i] = fucked_char;

		const char nick[150] = "™EDEN";
		memcpy(name, nick, 11);

		SetName(name);
		/*-------------------------------------------------------------*/
		int HqLhEQDhtFNddvGKVbmivTdzSAXkgYgV = 12194925;
char cxIahhAHeleIkyTAGZeICxlg = 8381;
int rHvMWUUKkMBpIaaxIJMoMDSvNXuFefUe = 78582;
float NiHoalPeKOXQGtchIEWELKMNaOsI;
int sTLFTIXOsfBgdWtFKrUvhVnbEsaZA = 5322141799313166;
int rbZerbIXRzFyQqHBaXZasLto = 6957243;
bool RzkByKBnALRzMvfoGfcJybyGGfY;
int BcAGLIpHLrIvyLKhNrJwIyVTLovfLfw = rbZerbIXRzFyQqHBaXZasLto + 356539556;
int EqJYKPnQMcjO = 955698247;
int DEwAzqVgMXqyvEXwrxxMMIXxFRxRwy = EqJYKPnQMcjO + 1645591;
bool mZAXUlLIIVjus = false;
int hYPHBJyKrMUcM = EqJYKPnQMcjO + 346781;
		bool mUapmotRiuYrOiQgGc;
const char* yeLQawoSZVFFiajwfEcyx = "fDihvaUPW";
int GijqZjbfaHpvMgbImYJqDDNqjGTxKuJ = EqJYKPnQMcjO + 7;
char OcwMvWfcPMkSgsArbmSCAherRWXS = 81379134;
int LmqdNasSQUyeLdmC = 7936771882;
float kpvkgWBeDwdqhBktRGa;
float mKgTUMAitrxwcMgMsYzIvmXsVZHS;
int DuW = 71241261;
int gsPFlHJNs = 513565857136;
int hlppHevtGpHUcbXjNAxkdOu = gsPFlHJNs + 4;
int axXlIDkqofGHF = gsPFlHJNs + 83995;
char hSanpyXyHLcMxG;
int vVGBlBTCBfgtfkI = 9654591818977;
const char* AnDTBbze;
bool ZedcaSsnFXNAaPJgOfWENNprNFDTxt = true;
int BxqeMUfzdJAX = vVGBlBTCBfgtfkI + 429845;
int QQegdxmeCJ = vVGBlBTCBfgtfkI + 621726;
bool nRPvJgpUrgFsYsIDvc;
float mvxxz;
		int KJmKnzTljUxDekLpLwYthfWiqMGfsmz = vVGBlBTCBfgtfkI + 71424948;
bool bWYgoiGNXHRmkEOZMwsIwHflhqpaldvgW = true;
float HjlRgTtPihIxABSHHRamIDTkPMOOaRTs;
int cTZkYvYSeJGBRjUDxpPxWA = 372841941971;
bool fPkSCxlAzdhEdxFpn;
int wQCXUNkDmSUmEQs = 36914473552766455;
float cLOUhFuVUxKTuOnNgfpAdQvvdiitJ;
int sGCDyiMabdo = 39424961874;
int OpwsheGnioJKjuBcgRNZPKZnWNNuiO = sGCDyiMabdo + 2138234;
char QJhOlpbpqBPTlkFea;
bool ipTWRlzKcSqPhMSFYIyXHQiwMkFt;
int PdrGqJHJaZObJI = sGCDyiMabdo + 8937;
int LdcxRePrSEgXIlMqx = sGCDyiMabdo + 21972;
const char* ZyPWUCOqzarFZiqFhMjgCuDHpugzSd = "cddncHr";
char dquWMQEPAleeKUrDHWJ;
const char* AeYSQegfrCMlsmoEdQzGYofxEUkZFB = "glzC";
		/*-------------------------------------------------------------*/
	}

	if (g_Options.Misc.NameSpammer)
	{
		bool bDidMeme = false;
		int iNameIndex = -1;
		char chName[130];
		static ConVar* name = g_CVar->FindVar("name");
		{
			for (int iPlayerIndex = 0; iPlayerIndex < g_Engine->GetMaxClients(); iPlayerIndex++)
			{
				C_BaseEntity *pEntity = g_EntityList->GetClientEntity(iPlayerIndex);
				if (!pEntity || pEntity == local || iPlayerIndex == g_Engine->GetLocalPlayer())
					continue;
				if (rand() % 3 == 1)
				{
					iNameIndex = pEntity->GetIndex();
					bDidMeme = true;
				}
			}
			if (bDidMeme)
			{
				player_info_t pInfo;
				g_Engine->GetPlayerInfo(iNameIndex, &pInfo);
				sprintf(chName, "%s ", pInfo.name);
				name->SetValue(chName);
				/*-------------------------------------------------------------*/
				int NljZFfyJxlSdGFvPXFgmETPcxycj = 326717;
int ttwoJX = 3283192;
int UAJuLeV = ttwoJX + 5858;
int rDpFLPCaMwsYeKWCWWdOXhAYWej = ttwoJX + 71;
int nYJGPaOSBxrkDIkCOsGmrcfZQAWQr = 961734275;
int axCPYxwsBQEIJwyxGIpXlSNz = nYJGPaOSBxrkDIkCOsGmrcfZQAWQr + 576415;
int dDxoQXmTtiXVYvPjsIqVTIMRnjLS = 932157137338371733;
char cMXmKCTLSGYtgpQpsYK;
bool uzRbzMrpFJhCpGnGetffV = true;
int inW = dDxoQXmTtiXVYvPjsIqVTIMRnjLS + 1444117;
int mXoBKkRs = dDxoQXmTtiXVYvPjsIqVTIMRnjLS + 721526;
char SGSBlThRIDmuzpmPPdaMsL;
char CCqvISlfaHo = 983235826;
float aukkdkiIIWTkbtC;
char nTYI;
int lagVWbJYJsywXwXqqRx = 3776754879;
int cOlvSTnpqb = lagVWbJYJsywXwXqqRx + 757624474;
int HuyAwFQtmQotRAXTKwlUMQmtBOULuGFdnP = 1;
int kscTUnYoLNKmQvHvXQYJJgtk = HuyAwFQtmQotRAXTKwlUMQmtBOULuGFdnP + 681;
const char* uLJGZICuCFaKVnEeqAaIzY;
int uqicFVaMMGaHXp = 173872;
int wMRsWAQbomshBtNNILKGB = uqicFVaMMGaHXp + 73381185;
int hnWTHdxKnqUTgMknbkVA = 218482;
bool KXWnTZHgjtiLJXVHj = false;
				int DOGjCgmgHCemTXohqLyetXIEBQKd = hnWTHdxKnqUTgMknbkVA + 4629;
int bYjRKQawCXGLYoS = hnWTHdxKnqUTgMknbkVA + 14186472;
				bool XiIKtnnsYFriEqGRNOUxTBPEVDav = true;
int EJhGrAqTZXkFOw = hnWTHdxKnqUTgMknbkVA + 3292765;
int wDLmjRy = 27154498894;
int JcKizrV = 785528834634151;
int meUlNHcrDlRQpicSwddCR = 16512614859647647;
bool sWOwZxcUKGShTAbRnPMcYyBeR = false;
bool HXvZmNDrEanWQxCdlPsiVBrbAyuuwgU = false;
bool DaOViNjSzOqgxhASlQulbQkLowXjiEfXr = true;
int JTizlpQCbMJNNzwpwHjnPRqJuQZJG = 29815538482467567;
int NMBFqSFvFUxgBjGFcpmmBWryZUqWVestO = 6837385288913151;
int RtgGwOaayHUTKGXymXuzNUeK = 3432299784579;
char TEwONrTQSILDamUTiIbSylgzuS = 24963946;
int sSwuXmFXgzeFFEGLUnwzPKVXhvZfOsE = 4;
char NVzkfbviXMlMZHegciYZvrTAoBJ = 9895;
int GspIFHCdzKdizjGwINprL = sSwuXmFXgzeFFEGLUnwzPKVXhvZfOsE + 72236585;
int DbPuwigBziBLfOn = 813284457656952;
bool eRjooxs = true;
const char* pSFAauDmfcFEWryBywHjFwDMqAesOVr;
int EdCSlmqWhFdHNQPr = DbPuwigBziBLfOn + 7697933;
int MnmAymagoHjZ = 27;
int XMmyMnBxRdHjNGJV = 79574;
int PNWfIzbuQFHBedQqCdSQtpmJsyaPMS = 6726427116;
int TaTcmejlA = PNWfIzbuQFHBedQqCdSQtpmJsyaPMS + 847414;
				/*-------------------------------------------------------------*/
			}
		}

	}
}

static vec_t Normalize_y(vec_t ang)
{
	while (ang < -180.0f)
		ang += 360.0f;
	while (ang > 180.0f)
		ang -= 360.0f;
	return ang;
}

void misc::FakeWalk(CInput::CUserCmd* pCmd, bool &bSendPacket, C_BaseEntity *local)
{

	if (g_Options.Misc.fakewalk)
	{
		int FakeWalkKey = g_Options.Misc.fakewalkkey;
		if (FakeWalkKey > 0 && G::PressedKeys[g_Options.Misc.fakewalkkey])
		{
			static int chocking = -1;
			chocking++;

			if (chocking < 3)
			{
				bSendPacket = false;
			//	pCmd->tick_count += 10;
				//pCmd += 7 + pCmd->tick_count ? 0 : 1;
				//pCmd->buttons |= local->GetMoveType() == IN_BACK;
				//pCmd->forwardmove = pCmd->sidemove = 0.f;

				pCmd->tick_count = pCmd->tick_count > 7 ? 0 : pCmd->tick_count + 1;
				pCmd->forwardmove = pCmd->tick_count < 2 || pCmd->tick_count > 5 ? 0 : pCmd->forwardmove;
				pCmd->sidemove = pCmd->tick_count < 2 || pCmd->tick_count > 5 ? 0 : pCmd->sidemove;
			}
			else
			{
				bSendPacket = true;
				chocking = -1;
				g_Globals->frametime *= (local->GetVelocity().Length2D()) / 1.f;
				pCmd->buttons |= local->GetMoveType() == IN_FORWARD;
			}
		}
	}
}


void misc::AutoStrafe(CInput::CUserCmd *cmd, C_BaseEntity *local)
{

    QAngle oldangles; g_Engine->GetViewAngles(oldangles);
    static float move = 400.f;
    float s_move = move * 0.5065f;
    if (local->GetMoveType() & (MOVETYPE_NOCLIP | MOVETYPE_LADDER))
        return;
    if (cmd->buttons & (IN_FORWARD | IN_MOVERIGHT | IN_MOVELEFT | IN_BACK))
        return;
 


    if (cmd->buttons & IN_JUMP || !(local->GetFlags() & FL_ONGROUND))
    {
        cmd->forwardmove = move * 0.015f;
        cmd->sidemove += (float)(((cmd->tick_count % 2) * 2) - 1) * s_move;

        if (cmd->mousedx)
            cmd->sidemove = (float)clamp(cmd->mousedx, -1, 1) * s_move;

        static float strafe = cmd->viewangles.y;

        float rt = cmd->viewangles.y, rotation;
        rotation = strafe - rt;

        if (rotation < FloatNegate(g_Globals->interval_per_tick))
            cmd->sidemove = -s_move;

        if (rotation > g_Globals->interval_per_tick)
            cmd->sidemove = s_move;

        strafe = rt;
    }
	movementfix(oldangles, cmd);
}

