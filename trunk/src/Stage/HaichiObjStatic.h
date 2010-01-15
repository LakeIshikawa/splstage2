#pragma once
#include "HaichiObj.h"
#include "..\\Mob\\Movable.h"

/*
	メモリーを最初から確保する種類の配置オブジェクト
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
