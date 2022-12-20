#include "pch.h"
#include "ShortAlgorightm.h"
#include "KISA_SHA256.h"

char ShortAlgorightm::alphaMap[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
string ShortAlgorightm::convIDtoURL(int str[]) {
    string url;
    int n = 0;
    for (int i = 1; i <= 7; i++) {
        n = 0;
        n += str[(i * 6) - 6] * 1;
        n += str[(i * 6) - 5] * 2;
        n += str[(i * 6) - 4] * 4;
        n += str[(i * 6) - 3] * 8;
        n += str[(i * 6) - 2] * 16;
        n += str[(i * 6) - 1] * 32;
        url.push_back(alphaMap[n]);
    }
    return url;
}

string ShortAlgorightm::convURLtoShort(const char* str, int len)
{
    BYTE* dest = new BYTE[32];
    SHA256_Encrpyt((BYTE*)str, len, dest);
    int tmp[42] = { 0, };
    int pos = 0;
    for (int i = 0; i < 5; i++) {
        pos = (i+1) * 8;
        while (dest[i] != 0) {
            tmp[--pos] = (int)dest[i] % 2;
            dest[i] /= 2;
        }
    }
    delete[] dest;
    string a = convIDtoURL(tmp);
    return a;
}
