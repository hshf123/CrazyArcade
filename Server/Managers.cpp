#include "pch.h"
#include "Managers.h"

uint64 Managers::GenerateID(const wstring& name)
{
	// djb2 algorithm
	uint64 hash = 5381;

	for (wchar_t c : name)
	{
		hash = ((hash << 5) + hash) + static_cast<uint64>(c);
	}

	return hash;
}
