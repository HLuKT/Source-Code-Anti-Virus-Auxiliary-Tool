#include "pch.h"
#include "Common.h"
#include <sstream>

CString GenerateString(const unsigned int len)
{
	CString dest;
	const CString baseChar = _T("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	const int baseLen = baseChar.GetLength();
	const int expandedLen = max(2 * len, baseLen);
	CString expandedChar(_T(' '), expandedLen);

	// 将可用字符列表进行扩展
	for (int i = 0; i < baseLen; i++) {
		if (2 * i < expandedLen) {
			expandedChar.SetAt(2 * i, baseChar.GetAt(i));
		}
		if (2 * i + 1 < expandedLen) {
			expandedChar.SetAt(2 * i + 1, baseChar.GetAt(i));
		}
	}

	// 对扩展后的字符串进行随机化
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(expandedChar.GetBuffer(), expandedChar.GetBuffer() + expandedLen, gen);
	expandedChar.ReleaseBuffer(expandedLen);

	// 从随机化后的字符串中选择 len 个字符
	std::uniform_int_distribution<> dis(0, expandedLen - 1);
	do
	{
		for (unsigned int i = 0; i < len; i++) {
			dest += expandedChar.GetAt(dis(gen));
		}
		if (*(LPCTSTR)dest.Left(1) < '0' || *(LPCTSTR)dest.Left(1) > '9')
		{
			return dest;
		}
		dest.Empty();
	} while (true);
}


void HexToAscii(unsigned char* cHex, CString& csAscii, int nHexLength)
{
	std::stringstream ss;
	for (int i = 0; i < nHexLength; i++)
	{
		unsigned char c = cHex[i];
		ss << "0x" << std::hex << static_cast<int>(c) << ", ";
	}
	std::string str = ss.str();
	str.pop_back(); // 删除最后一个逗号和空格
	csAscii += str.c_str();
}

LONGLONG HexToHash(char* cHex)
{
	LONGLONG hash = 0x99;
	for (int i = 0; i < strlen(cHex); i++) {
		hash += (LONGLONG)cHex[i] + (hash << 1);
	}
	return hash;
}

//#include <psapi.h>
#include <TlHelp32.h>
CString GetMoudleNameByFunctionName(LPCSTR csFunctionName) 
{
	CString csError = L"";
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		return csError;
	}
	MODULEENTRY32 moduleEntry = { 0 };
	moduleEntry.dwSize = sizeof(MODULEENTRY32);
	if (Module32First(hSnapshot, &moduleEntry)) {
		do {
			FARPROC funcInModule = GetProcAddress(moduleEntry.hModule, csFunctionName);
			if (funcInModule) {
				return moduleEntry.szModule;
			}
		} while (Module32Next(hSnapshot, &moduleEntry));
	}
	else {
		return csError;
	}
	CloseHandle(hSnapshot);
	return csError;


	/*
	HMODULE hMods[1024];
	DWORD cbNeeded;
	if (!EnumProcessModules(GetCurrentProcess(), hMods, sizeof(hMods), &cbNeeded)) {
		//std::cerr << "Error: Failed to enumerate process modules." << std::endl;
		return 0;
	}

	TCHAR szModName[MAX_PATH];
	for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) 
	{
		if (GetModuleFileNameEx(GetCurrentProcess(), hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR))) {
			FARPROC funcInModule = GetProcAddress(hMods[i], csFunctionName);

			if (funcInModule) {
				//std::cout << "The CreateThread function is located in module: " << szModName << std::endl;
				//break;.
				return szModName;
			}
		}
	}
	CString csError = L"";
	return csError;
	*/
}

