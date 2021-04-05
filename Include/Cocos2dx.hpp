#ifndef _COCOS2DX_HPP
#define _COCOS2DX_HPP

#include <cstdint>

namespace cocos2dx
{
	using CCTextAlignment = std::uint32_t;

	struct CCPoint
	{
		float x, y;
	};

	typedef bool(__thiscall* BMFont_initWithString_T)(
		void* pthis,
		char const* str,
		char const* fontFile,
		float x,
		CCTextAlignment const alignment,
		CCPoint const point);

	static char constexpr BMFONT_INITWITHSTRING_SYM[] =
		"?initWithString@CCLabelBMFont@cocos2d@@QAE_NPBD0MW4CCTextAlignment@2@VCCPoint@2@@Z";
}

#endif /* _COCOS2DX_HPP */