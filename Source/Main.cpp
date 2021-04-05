#include "MinHook.h"
#include "HackPro.h"
#include "Cocos2dx.hpp"
#include "Owoifiew.hpp"

using namespace cocos2dx;
using namespace owoifiew;

//Globals

static BMFont_initWithString_T BMFont_initWithString = nullptr;

//Callbacks

static bool __fastcall BMFont_initWithString_Cb(
	void* pthis,
	std::uintptr_t,
	char const* str,
	char const* fontFile,
	float x,
	CCTextAlignment const alignment,
	CCPoint const point)
{
	auto newStr = owoify(str);

	return ::BMFont_initWithString(
		pthis,
		newStr.c_str(),
		fontFile,
		-1.0f,
		alignment,
		point);
}

//Main

static DWORD errorBreak(DWORD const x)
{
#if defined(_DEBUG)
	DebugBreak();
#endif
	return x;
}

static void debugString(std::string const& s) {}

static void HPAPI hackproEnable(void*)
{
	MH_EnableHook(MH_ALL_HOOKS);
}

static void HPAPI hackproDisable(void*)
{
	MH_DisableHook(MH_ALL_HOOKS);
}

static bool initHackPro()
{
	if (InitialiseHackpro())
	{
		if (HackproIsReady())
		{
			void* ext = HackproInitialiseExt("Owoifier");
			HackproAddCheckbox(
				ext,
				"Owoify!",
				&hackproEnable,
				&hackproDisable);
			HackproCommitExt(ext);
			return true;
		}
	}

	return false;
}

static bool initHooks()
{
	auto cocos = ::GetModuleHandleA("libcocos2d.dll");

	if (cocos == NULL)
	{
		debugString("ERROR: cocos was null.");
		return false;
	}

	auto bmfont_initWithString_p = ::GetProcAddress(
		cocos,
		BMFONT_INITWITHSTRING_SYM);

	if (!bmfont_initWithString_p)
	{
		debugString("ERROR: bmfont_initWithString_p was null.");
		return false;
	}

	auto status = ::MH_CreateHook(
		reinterpret_cast<LPVOID>(bmfont_initWithString_p),
		reinterpret_cast<LPVOID>(&BMFont_initWithString_Cb),
		reinterpret_cast<LPVOID*>(&BMFont_initWithString));

	if (status != MH_OK)
	{
		debugString("ERROR: MH_CreateHook() failed: " + std::to_string(static_cast<int>(status)));
		return false;
	}
}

static DWORD WINAPI MainThread(LPVOID)
{
	//Init MinHook
	if (::MH_Initialize() != MH_OK)
	{
		debugString("ERROR: MH_Initialize() failed.");
		return ::errorBreak(0);
	}

	//Init hooks
	if (!::initHooks())
	{
		debugString("ERROR: could not load hooks.");
		return ::errorBreak(0);
	}

	owoifiew::init();

	if (!initHackPro())
		hackproEnable(nullptr);

	debugString("Hack loaded OWO");
	return 0;
}

BOOL WINAPI DllMain(
	HINSTANCE const dll,
	DWORD const reason,
	LPCVOID)
{
	DisableThreadLibraryCalls(dll);

	if (reason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, &MainThread, 0, 0, 0);

	return TRUE;
}