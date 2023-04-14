#pragma once

class Managers
{
private:
	Managers() { }
	~Managers() { }

public:
	static Managers* GetInstance()
	{
		static Managers instance;
		return &instance;
	}

public:
    int64 GenerateID(const wstring& name);
};
