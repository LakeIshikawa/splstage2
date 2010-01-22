#include ".\movable.h"
#include "..\\Management\\GameControl.h"

Movable::Movable(void)
{
	mMuki = 0;

	mX = 0;
	mY = 0;

	mSpX = 0;
	mSpY = 0;

	mAccX = 0;
	mAccY = 0;

	mZ = 0;
}

/*
	MOBの基本的な処理
*/
void Movable::Process()
{
	// ﾀｽｸﾘｽﾄに入っているﾀｽｸを行う
	list<Movable*>::iterator it = mlTaskLst.begin(), en = mlTaskLst.end();
	for( ; it!=en; it++ ){
		(*it)->RunTask();
	}

	// 波形ｸﾗｽのﾑｰﾌﾞを呼ぶ
	Move();
}

/*
	ﾀｽｸｵﾌﾞｼﾞｪｸﾄを追加
*/
void Movable::AddTask(Movable* rTask)
{
	mlTaskLst.push_back(rTask);
}

/*
	所属者をセット
*/
void Movable::SetOwnershipTransfered(bool rTrueFalse)
{
	mOwnershipTransfered = rTrueFalse;
}

/*
	所属者参照
*/
bool Movable::IsOwnershipTransfered()
{
	return mOwnershipTransfered;
}


/*
	画面外になったときに消滅される
*/
void Movable::DieIfGamenGai()
{
	// ﾏｯﾌﾟ外に抜けたら消す
	if( mX < -mSizeX || mY < -mSizeY || mX > GAMECONTROL->GetStageManager()->GetCurMap()->GetNGamen() * SP->SCRSZX ||
		mY > SP->SCRSZY){
			Finalize();
			GAMECONTROL->GetMobManager()->Remove(this);
	}
}

float Movable::Z()
{
	return mZ;
}


/************************************************************//**
*	\return 画面外に出ているか
****************************************************************/
bool Movable::IsGamenGai()
{
	return ISGAMENGAI(mX, mY, mSizeX, mSizeY);
}
