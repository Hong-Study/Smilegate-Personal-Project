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

int ShortAlgorightm::convURLtoID(string shortURL) {
    int urlID = 0;
    for (int i = 0; i < shortURL.length(); i++) {
        // if char is in between A and Z
        if ('A' <= shortURL[i] && shortURL[i] <= 'Z')
            urlID = urlID * 62 + shortURL[i] - 'A';
        // if char is in between a and z (till 26 we have A to Z)
        if ('a' <= shortURL[i] && shortURL[i] <= 'z')
            urlID = urlID * 62 + shortURL[i] - 'a' + 26;

        // if char is in between 0 and 9 (till 52 we have a to b)
        if ('0' <= shortURL[i] && shortURL[i] <= '9')
            urlID = urlID * 62 + shortURL[i] - '0' + 52;
    }
    return urlID;
}

string ShortAlgorightm::convTest(const char* str, int len)
{
    BYTE* dest = new BYTE[32];
    SHA256_Encrpyt((BYTE*)str, len, dest);
    int tmp[42] = { 0, };
    int pos = 0;
    for (int i = 0; i < 5; i++) {
        pos = (i+1) * 8;
        cout << (int)dest[i] << " ";
        while (dest[i] != 0) {
            tmp[--pos] = (int)dest[i] % 2;
            dest[i] /= 2;
        }
    }
    cout << endl;
    delete[] dest;
    string a = convIDtoURL(tmp);
    cout << a << endl;
    return a;
}
