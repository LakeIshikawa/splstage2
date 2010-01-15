#pragma once

#include <list>
#include <vector>

#include "Map.h"
#include "HaichiObj.h"
#include "..\\Object\\AshibaMovable.h"
#include "..\\Object\\Tenbin.h"

using namespace std;

class CheckpointController;

/*
	敵の配置ﾃﾞｰﾀ
*/
class Haichi : public Map
{
public:
	Haichi(void);
	~Haichi(void);

	int	Load(string rFname, CheckpointController* checkpointController);
	void UnLoad();
	void Process();

	//! 敵を復活させる
	void RestoreTekiAfter( int rPos );

	//! 動く足場をゲット
	AshibaMovable* GetAshibaMov(int idx);

	//! 動く足場の数
	int GetAshibaMovNum();

	//! 足場をあたりターゲットとして設定する
	void SetAshibaTargets( Collidable* rToThisObj );
	//! 足場に設定されているﾀｰｹﾞｯﾄを未設定する
	void RemoveAshibaTargets( ICollidable* rRemoveMe );

	//! 天秤の数
	int GetTenbinNum();

	//! 天秤をゲット
	Tenbin* GetTenbin(int idx);

	//! 生データを参照
	int GetData(int rX, int rY);

private:

	// 足場用の特別な処理
	bool IsAshiba(int data);
	void ProcessAshiba(int data, int x, int y);

	list< HaichiObj* > mHaichiListOrig; // mXPx順で並び替えてあるが想定
	list< HaichiObj* > mHaichiListTemp; // mXPx順で並び替えてあるが想定

	vector< AshibaMovable* > mAshibaMovList; // 動く足場
	vector< Ashiba* > mAshibaList; // 動く足場以外の足場
	vector< Tenbin* > mTenbinList; // 天秤

	int mShutugenStartPoint;

	// 設定定数
	int SHUTSUGEN_POINTX;

	// 後の処理を軽くする
	int CHECKPOINT_NO;
	int MOVASHIBA_NO;
	int MOVASHIBA2_NO;
	int MOVASHIBA3_NO;
	int ASHIBA_NO;
	int ASHIBA2_NO;
	int ASHIBA3_NO;
	int INVASHIBA3_NO;
	int TENBIN_NO;

};
