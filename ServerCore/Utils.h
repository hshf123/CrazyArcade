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
};