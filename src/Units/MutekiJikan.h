#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\Mob\\ActionControllable\\IActionThread.h"

//! 無敵時間
/****************************************************************//**
*	無敵時間の並行処理を担当するｽﾚｯﾄﾞ
*	\nosubgrouping
********************************************************************/
class MutekiJikan : public IActionThread
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	MutekiJikan();

	//! @see ActionThread
	void Run();


	//! 無敵時間を設定する
	void SetMutekiTime(float rTime);

	//! 操作・無敵にする
	void Start();
	//! ｱｸｾｽ
	bool IsMuteki();

	//! ｸﾛｰﾝ
	MutekiJikan* Clone();

private:
	float mTimer;
	float mMutekiTime;
	bool  mMutekiFl;
};
