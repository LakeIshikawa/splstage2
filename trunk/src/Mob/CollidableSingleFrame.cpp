#include <exception>
using namespace std;

#include "CollidableSingleFrame.h"
#include "Movable.h"
#include "ICollidable.h"

/************************************************************//**
*	�����ǉ�����
****************************************************************/
CollidableSingleFrame::CollidableSingleFrame() {
	AddTask(this);
}

/************************************************************//**
*	�^�[�Q�b�g�̃��X�g���񂵁A�����蔻����s���܂��B
****************************************************************/
void CollidableSingleFrame::RunTask() {
	
	//�����蔻������
	Collision* cur_frame = GetCurFrame();
	if(cur_frame){
		list<ICollidable*>::iterator it = mlTargets.begin(), en = mlTargets.end();
		for( ; it!=en; it++ ){
			Collision* coll_frame = (*it)->GetCurFrame();
			cur_frame->Hantei(coll_frame, this, *it);
		}
	}
}

/************************************************************//**
*	\param rTarget �����蔻��̃^�[�Q�b�g�Ƃ��Ēǉ�����
****************************************************************/
void CollidableSingleFrame::AddTarget(ICollidable* rTarget) {
	mlTargets.push_back(rTarget);
}


/************************************************************//**
*	\param rTarget �����蔻��̃^�[�Q�b�g�Ƃ��ĉ�������
****************************************************************/
void CollidableSingleFrame::RemoveTarget(ICollidable* rTarget) {
	mlTargets.remove(rTarget);
}

