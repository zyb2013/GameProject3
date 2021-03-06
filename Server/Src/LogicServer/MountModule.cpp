﻿#include "stdafx.h"
#include "MountModule.h"
#include "DataPool.h"
#include "GlobalDataMgr.h"
#include "PlayerObject.h"
#include "Log.h"
#include "../Message/Msg_ID.pb.h"

CMountModule::CMountModule(CPlayerObject* pOwner): CModuleBase(pOwner)
{

}

CMountModule::~CMountModule()
{

}

BOOL CMountModule::OnCreate(UINT64 u64RoleID)
{

	return TRUE;
}


BOOL CMountModule::OnDestroy()
{
	for(auto itor = m_mapMountData.begin(); itor != m_mapMountData.end(); itor++)
	{
		itor->second->release();
	}

	m_mapMountData.clear();

	return TRUE;
}

BOOL CMountModule::OnLogin()
{
	return TRUE;
}

BOOL CMountModule::OnLogout()
{
	return TRUE;
}

BOOL CMountModule::OnNewDay()
{
	return TRUE;
}

BOOL CMountModule::ReadFromDBLoginData(DBRoleLoginAck& Ack)
{
	const DBMountData& MountData = Ack.mountdata();
	for(int i = 0; i < MountData.mountlist_size(); i++)
	{
		const DBMountItem& MountItem = MountData.mountlist(i);
		MountDataObject* pObject = g_pMountDataObjectPool->NewObject(FALSE);
		pObject->lock();
		pObject->unlock();
		m_mapMountData.insert(std::make_pair(pObject->m_uGuid, pObject));
	}
	return TRUE;
}

BOOL CMountModule::SaveToClientLoginData(RoleLoginAck& Ack)
{
	return TRUE;
}

BOOL CMountModule::CalcFightValue(INT32 nValue[PROPERTY_NUM], INT32 nPercent[PROPERTY_NUM], INT32& FightValue)
{
	return TRUE;
}

UINT64 CMountModule::AddMount(UINT32 dwMountID)
{
	MountDataObject* pObject = g_pMountDataObjectPool->NewObject(TRUE);
	pObject->lock();
	pObject->m_MountID = dwMountID;
	pObject->m_uGuid   = CGlobalDataManager::GetInstancePtr()->MakeNewGuid();
	pObject->m_StrengthLvl = 0;
	pObject->m_RefineExp = 0;
	pObject->m_StarExp = 0;
	pObject->m_StarLevel = 0;
	pObject->unlock();
	m_mapMountData.insert(std::make_pair(pObject->m_uGuid, pObject));
	return pObject->m_uGuid;
}


BOOL CMountModule::NotifyChange()
{
	MountChangeNty Nty;
	for(auto itor = m_setChange.begin(); itor != m_setChange.end(); itor++)
	{
		MountDataObject* pObject = GetMountByGuid(*itor);
		ERROR_CONTINUE_EX(pObject != NULL);

		MountItem* pItem = Nty.add_changelist();
	}

	for(auto itor = m_setRemove.begin(); itor != m_setRemove.end(); itor++)
	{
		Nty.add_removelist(*itor);
	}

	m_pOwnPlayer->SendMsgProtoBuf(MSG_MOUNT_CHANGE_NTY, Nty);

	m_setChange.clear();
	m_setRemove.clear();

	return TRUE;
}

MountDataObject* CMountModule::GetMountByGuid(UINT64 uGuid)
{
	auto itor = m_mapMountData.find(uGuid);
	if(itor != m_mapMountData.end())
	{
		return itor->second;
	}

	return NULL;
}
