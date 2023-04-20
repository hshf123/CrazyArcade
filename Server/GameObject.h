#pragma once

using PositionInfo = Protocol::PPositionInfo;

class GameObject : public enable_shared_from_this<GameObject>
{
public:
	void CopyPositionInfoProtocol(Protocol::PPositionInfo* pkt);
	Protocol::PPositionInfo* GetPositionInfoProtocol();

	PositionInfo PosInfo;
};
