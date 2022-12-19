#pragma once

class ShortAlgorightm
{
public:
	static string convURLtoShort(const char* str, int len);

private:
	static string convIDtoURL(int str[]);
	static int convURLtoID(string shortURL);
	static char alphaMap[65];
};

