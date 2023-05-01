#pragma once
#include "pch.h"

class Utils
{
public:
	static std::wstring ConvertStringToWString(std::string str)
	{
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], static_cast<int>(str.size()), nullptr, 0);
		std::wstring wstr(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], static_cast<int>(str.size()), &wstr[0], size_needed);
		if (wstr.size() > 0 && wstr[wstr.size() - 1] == 8203)
		{
			return std::wstring(wstr.begin(), wstr.end() - 1);
		}
		return wstr;
	}

	static std::string ConvertWStringToString(std::wstring wstr)
	{
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
		std::string str(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], static_cast<int>(wstr.size()), &str[0], size_needed, nullptr, nullptr);
		return str;
	}

	static void Log(const wstring& log)
	{
		wcout.imbue(locale("kor"));
		wcout << L"[ LOG ] [TIME STAMP : " << TimeStamp() << L"s ] ";
		wcout << log << endl;
	}

	static void Log(const wstringstream& log)
	{
		Log(log.str());
	}

	static int32 TimeStamp()
	{
		return ::clock() / 1000;
	}
};
