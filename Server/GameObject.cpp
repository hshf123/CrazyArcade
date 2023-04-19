#include "pch.h"
#include "GameObject.h"

void GameObject::CopyPositionInfoProtocol(Protocol::PPositionInfo* pkt)
{
	pkt->CopyFrom(PosInfo);
}

Protocol::PPositionInfo* GameObject::GetPositionInfoProtocol()
{
	Protocol::PPositionInfo* pkt = new Protocol::PPositionInfo();
	pkt->CopyFrom(PosInfo);
	return pkt;
}