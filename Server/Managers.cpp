#include "pch.h"
#include "Managers.h"

int64 Managers::GenerateID(const wstring& name)
{
	uint64 hash = 0;

	for (const auto& c : name)
	{
		hash = (hash * 31) + static_cast<uint32>(c);
	}

	return static_cast<int64>(hash & 0x7FFFFFFFFFFFFFFF);
}
