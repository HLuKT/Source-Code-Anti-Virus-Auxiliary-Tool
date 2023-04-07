#pragma once
#include <atlstr.h>
#include <random>
CString GenerateString(const unsigned int len);
void HexToAscii(unsigned char* cHex, CString& csAscii, int nHexLength);
long long  HexToHash(char* cHex);
CString GetMoudleNameByFunctionName(LPCSTR csFunctionName);
