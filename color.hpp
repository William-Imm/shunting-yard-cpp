// Description for Color struct and example colors
// William Immendorf - 2016

#include <string>

#pragma once

namespace EquParser
{
	struct Color
	{
		std::string name = "";
		float red = 0.0f;
		float green = 0.0f;
		float blue = 0.0f;

		Color(std::string name, float red, float green, float blue) : name(name), red(red), green(green), blue(blue) { }
	};

	const Color Colors[3] =
	{
		{ "Black", 0.0f, 0.0f, 0.0f },
		{ "Red", 1.0f, 0.0f, 0.0f },
		{ "Green", 0.0f, 1.0f, 0.0f }
	};
}
