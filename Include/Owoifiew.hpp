#ifndef _OWOIFIEW_HPP
#define _OWOIFIEW_HPP

#include <random>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

namespace owoifiew
{
	using List = std::unordered_map<std::string, std::string>;

	static std::vector<std::string> const PREFIXES =
	{
		"<3 ",
		"0w0 ",
		"H-hewwo?? ",
		"HIIII! ",
		"Haiiii! ",
		"Huohhhh. ",
		"OWO ",
		"OwO ",
		"UwU "
	};

	static std::vector<std::string> const SUFFIXES =
	{
		" ._.",
		" :3",
		" :D",
		" :P",
		" ;-;",
		" ;3",
		" ;_;",
		" <{^v^}>",
		" >_<",
		" >_>",
		" UwU",
		" XDDD",
		" ^-^",
		" ^_^",
		" x3",
		" x3",
		" xD",
		", fwendo",
	};

	static std::unordered_map<std::string, std::string> const REPLACE =
	{
		{ "ow", "OWO" },
		{ "r", "w" },
		{ "l", "w" },
		{ "R", "W" },
		{ "L", "W" },
		{ "no", "nu" },
		{ "has", "haz" },
		{ "have", "haz" },
		{ " says", " sez" },
		{ "you", "uu" },
		{ "the", "ze" },
		{ "The", "Ze" },
		{ "THE", "ZE" },
	};

	inline void init()
	{
		std::random_device r;
		std::srand(r());
	}

	inline bool hasPreSufFix()
	{
		return std::rand() & 1;
	}

	inline void replaceInstance(
		std::string& s,
		std::string const& from,
		std::string const& to)
	{
		auto pos = s.find(from);

		while (pos != std::string::npos)
		{
			s.replace(pos, from.size(), to);
			pos = s.find(from);
		}
	}

	inline bool isNumber(std::string const& s)
	{
		try
		{
			std::stoi(s, nullptr, 0);
			return true;
		}
		catch (std::invalid_argument const&)
		{
			return false;
		}
	}

	inline std::string owoify(std::string const& s)
	{
		std::string prefix;
		std::string suffix;
		std::string ret = s;

		//Not owo material ;3;
		if (s.empty() || s == " " || isNumber(s))
			return s;

		if (hasPreSufFix())
			prefix = PREFIXES[std::rand() % PREFIXES.size()];

		if (hasPreSufFix())
			suffix = SUFFIXES[std::rand() % SUFFIXES.size()];

		for (auto const& [key, value] : REPLACE)
			replaceInstance(ret, key, value);

		return prefix + ret + suffix;
	}
}

#endif /* _OWOIFIEW_HPP */