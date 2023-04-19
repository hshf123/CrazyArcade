#pragma once

using PositionInfo = Protocol::PPositionInfo;

class GameObject
{
public:
	void CopyPositionInfoProtocol(Protocol::PPositionInfo* pkt);
	Protocol::PPositionInfo* GetPositionInfoProtocol();

	PositionInfo PosInfo;
};
