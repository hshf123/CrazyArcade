#include "pch.h"
#include "Managers.h"

int64 Managers::GenerateID(const wstring& name)
{
	// djb2 algorithm
	int64 hash = 5381;

	for (wchar_t c : name)
	{
		hash = ((hash << 5) + hash) + static_cast<int64>(c);
	}

	return hash;
}
