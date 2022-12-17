#pragma once

class ShortAlgorightm
{
public:
	static string convIDtoURL(int str[]);
	static int convURLtoID(string shortURL);
	static string convTest(const char* str, int len);
private:
	static char alphaMap[65];
};

