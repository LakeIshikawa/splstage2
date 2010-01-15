#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\ActionControllable\\ActionState.h"

//! �����オ�肫��̂�҂�
/****************************************************************//**
*	�����オ�肫��܂őҋ@����
*	\nosubgrouping
********************************************************************/
class ASWaitForMaku : virtual public ActionState
{

public:

	//! \param rOpenClose 0-�����J���̂�҂� 1-��������̂�҂�
	ASWaitForMaku(bool rOpenClose) : mOpenClose(rOpenClose){}

	//! �����蔻���޼ު�Ă̍����@
	void BuildCollision(ActionState* rPrevState);
	//! ϯ�ߓ����蔻���޼ު�Ă̍����@
	void BuildMapCollider(ActionState* rPrevState);
	//! ��Ұ��ݵ�޼ު�Ă̍����@
	void BuildAnimation(ActionState* rPrevState);
	//! �`����@��������޼ު�Ă̍����@
	void BuildMobDrawer(ActionState* rPrevState);
	//! �h���׽�̎����Ă�����ʏ����߰������@
	void BuildOtherInfo(ActionState* rPrevState);
	
	
	//! �����蔻��̉������@
	virtual void CollisionResponse(ICollidable* rCollObject, 
				int rThisGroupId, int rOpGroupId);

	//! @see ActionState
	void OnEnter();
	//! @see ActionState
	bool Update();
	//! @see ActionState
	void OnExit();

private:
	bool mOpenClose;

};
