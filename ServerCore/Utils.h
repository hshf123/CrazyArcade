#pragma once
#include "pch.h"

class Utils
{
public:
	static wstring ConvertStringToWString(string str)
	{
		wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
		wstring wstr = converter.from_bytes(str);
		if(wstr[wstr.size() - 1] == 8203)
			return wstring(wstr.begin(), wstr.end() - 1);
		return wstr;
	}

	static string ConvertWStringToString(wstring wstr)
	{
		wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
		string str = converter.to_bytes(wstr);
		return str;
	}

	static void Log(const wstring& log)
	{
		wcout.imbue(locale("kor"));
		wcout << L"[ LOG ]";
		wcout << log << endl;
	}

	static void Log(const wstringstream& log)
	{
		wcout.imbue(locale("kor"));
		wstringstream ws;
		ws << L"[ LOG ]" << log.str();
		wcout << ws.str() << endl;
	}
};