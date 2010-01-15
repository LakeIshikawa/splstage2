#pragma once
#include "HaichiObj.h"
#include "..\\Mob\\Movable.h"

/*
	�������[���ŏ�����m�ۂ����ނ̔z�u�I�u�W�F�N�g
*/
class HaichiObjStatic : public HaichiObj
{
public:
	HaichiObjStatic(int rXPx, int rYPx) : HaichiObj(rXPx, rYPx, -1){mObject=NULL;}
	~HaichiObjStatic(void) {if(mObject) delete mObject;}

	Movable* GetObject() {return mObject;}
	void	 SetObject(Movable* rObject) {mObject = rObject;}

private:
	Movable* mObject;

};
