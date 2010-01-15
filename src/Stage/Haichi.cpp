#include ".\haichi.h"
#include "..\\Management\\GameControl.h"
#include "Checkpoint\\CheckpointController.h"
#include "Checkpoint\\Checkpoint.h"
#include "HaichiObjStatic.h"
#include "..\\Object\\AshibaMovable.h"
#include "..\\Object\\AshibaInvisible.h"

Haichi::Haichi(void)
{
	// 後の処理を軽くする
	CHECKPOINT_NO = GI("CHECKPOINT_NO");
	MOVASHIBA_NO = GI("MOVASHIBA_NO");
	MOVASHIBA2_NO = GI("MOVASHIBA2_NO");
	MOVASHIBA3_NO = GI("MOVASHIBA3_NO");
	ASHIBA_NO = GI("ASHIBA_NO");
	ASHIBA2_NO = GI("ASHIBA2_NO");
	ASHIBA3_NO = GI("ASHIBA3_NO");
	INVASHIBA3_NO = GI("INVASHIBA3_NO");
	TENBIN_NO = GI("TENBIN_NO");

	mShutugenStartPoint = 0;
	SHUTSUGEN_POINTX = GI("SHUTSUGEN_POINTX");
}

Haichi::~Haichi(void)
{
}

/*
	指定されたﾌｧｲﾙから配置ﾃﾞｰﾀを読み込みます。
	この場で配置のﾃﾞｰﾀﾌｫｰﾏｯﾄを変換して、配置
	ｵﾌﾞｼﾞｪｸﾄを作ります。

	配置ﾘｽﾄの項目がXPxが低い順になるはず。

	ｴﾗｰの場合、1を返します。
*/
int Haichi::Load(string rFname, CheckpointController* checkpointController)
{
	// ﾃﾞｰﾀを読み込む
	if(Map::LoadFromFile(rFname)) return 1;

	
	// ﾘｽﾄを作成
	for(int x=0; x<SP->CHIPNX*mNGamen; x++)
		for(int y=0; y<SP->CHIPNY; y++)
		{
			int data = (*(mData[y]))[x];

			// チェックポイント
			if( data == CHECKPOINT_NO && checkpointController ){
				checkpointController->Add(new Checkpoint(x*SP->CHSZX, y*SP->CHSZY));
			}

			else if( IsAshiba(data ) ){
				ProcessAshiba(data, x, y);
			}
					
			// 天秤
			else if( data == TENBIN_NO ){
				Tenbin* newTenbin = new Tenbin(x*SP->CHSZX, y*SP->CHSZY, -1.0f);
				HaichiObjStatic* newObj = new HaichiObjStatic(x*SP->CHSZX, y*SP->CHSZY);
				newObj->SetObject(newTenbin);
				mTenbinList.push_back( newTenbin );

				mHaichiListOrig.push_back( newObj );
				mHaichiListTemp.push_back( newObj );
			}

			// 普通の敵やｽﾀﾃｨｯｸでないｵﾌﾞｼﾞｪｸﾄ
			else if( data!=0 ){ // 0以外
				HaichiObj* newObj = new HaichiObj(x*SP->CHSZX, y*SP->CHSZY, data);
				mHaichiListOrig.push_back( newObj );
				mHaichiListTemp.push_back( newObj );
			}
		}

	// チェックポイントを覆す
	if( checkpointController)
		checkpointController->ReverseList();

	return 0; //OK
}

/*
	リソースを解放する
*/
void Haichi::UnLoad()
{
	// データ解放
	vector<vector<int>*>::iterator it;
	for(it = mData.begin(); it != mData.end(); it++){
		vector<int>* sublist = *it;
		//delete sublist;
	}
	mData.clear();

	// リストを解放
	mHaichiListOrig.clear();
	mHaichiListTemp.clear();

	// 足場をアンロード
	for(int i=0; i<mAshibaList.size();i++) 
	{ 
		delete mAshibaList[i];
		mAshibaList[i] = NULL;
	}
	mAshibaMovList.clear();
	mAshibaList.clear();

	// 天秤をアンロード
	mTenbinList.clear();
}

/*
	現在の配置ﾘｽﾄの一番目のMOB出現するべきかどうかをﾁｪｯｸする。
	出現の場合、ﾘｸｴｽﾄして、ﾘｽﾄから外してしまいます。

	MOBが出現するのは一回のみとなります。
*/
void Haichi::Process()
{
	// ｽｸﾛｰﾙﾎﾟｲﾝﾀｰを取得
	int scpx = (int)GAMECONTROL->GetStageManager()->GetCurScrollPointer();

	// ﾁｪｯｸ
	while( !mHaichiListTemp.empty() && (mHaichiListTemp.front()->GetXPx() <  SHUTSUGEN_POINTX + scpx ) ){

		HaichiObj* obj = mHaichiListTemp.front();
		
		// 静的オブジェクト
		if( obj->GetNo()==-1 ){
			Movable* reqobj = ((HaichiObjStatic*)obj)->GetObject();
			GAMECONTROL->GetMobManager()->Request( reqobj, false );
			mHaichiListTemp.pop_front();
		}

		// 動的オブジェクト
		else{ 
			GAMECONTROL->GetMobManager()->Request( obj->GetNo(), obj->GetXPx(), obj->GetYPx(), true );
			mHaichiListTemp.pop_front();
		}
	}
}

/************************************************************//**
* rPosより先(右)に配置された敵が復活します。
*	\param rPos この位置(X)以降は全ての敵が復活する
*	\note ｽｸﾛｰﾙでﾘｸｴｽﾄさせるまで、敵が現れません。\n
*	このﾒｿｯﾄﾞで「再配置」されるだけです
****************************************************************/
void Haichi::RestoreTekiAfter(int rPos)
{
	mHaichiListTemp.clear();

	for each ( HaichiObj* obj in mHaichiListOrig ){
		if( !ISTEKI(obj->GetNo()) || obj->GetXPx() >= rPos ){
			mHaichiListTemp.push_back( obj );
		}
	}

	// 動く足場の位置をリセット
	for each ( AshibaMovable* am in mAshibaMovList ){
		am->Reset();
	}

	// 天秤のリセット
	for each ( Tenbin* tb in mTenbinList ){
		tb->Reset();
	}
}

/************************************************************//**
* 動く足場を取得
*	\param idx 足場番号(0～9)
****************************************************************/
AshibaMovable* Haichi::GetAshibaMov(int idx)
{
	return mAshibaMovList[idx];
}

/************************************************************//**
* \return 動く足場の数
****************************************************************/
int Haichi::GetAshibaMovNum()
{
	return mAshibaMovList.size();
}

/************************************************************//**
* 指定されたCollidableに全部の足場を当たりﾀｰｹﾞｯﾄとして登録する。
* \param rToThisObj このオブジェクトに登録する
****************************************************************/
void Haichi::SetAshibaTargets(Collidable* rToThisObj)
{
	for each(Ashiba* a in mAshibaList){
		a->AddTarget(rToThisObj);
	}
}

/************************************************************//**
* 足場に設定されている指定のﾀｰｹﾞｯﾄを削除する
* \param rRemoveMe リストから外す項目
****************************************************************/
void Haichi::RemoveAshibaTargets(ICollidable* rRemoveMe)
{
	for each(Ashiba* a in mAshibaList){
		if(a) a->RemoveTarget(rRemoveMe);
	}
}

/************************************************************//**
* 天秤を取得
*	\param idx 天秤番号(配置された順番)
****************************************************************/
Tenbin* Haichi::GetTenbin(int idx)
{
	return mTenbinList[idx];
}

/************************************************************//**
* \return 天秤の数
****************************************************************/
int Haichi::GetTenbinNum()
{
	return mTenbinList.size();
}


/************************************************************//**
* 配列のデータを取得する。
* データが配置データどおりになっています。
****************************************************************/
int Haichi::GetData(int rX, int rY)
{
	return (*(mData[rY]))[rX];
}

/************************************************************//**
* @param data 配置番号
* @ return 足場だかどうだか
****************************************************************/
bool Haichi::IsAshiba(int data)
{
	return (data==ASHIBA_NO || data==ASHIBA2_NO || data == ASHIBA3_NO ||
		data==MOVASHIBA_NO || data==MOVASHIBA2_NO || data == MOVASHIBA3_NO ||
		data==INVASHIBA3_NO );
}

/************************************************************//**
* 足場の配置を処理する
****************************************************************/
void Haichi::ProcessAshiba(int data, int x, int y){

	string graphic;
	int sizex, sizey;
	if(data==ASHIBA_NO||data==MOVASHIBA_NO||data==INVASHIBA3_NO){
		graphic = "graphics\\object\\stage_1_asiba.png"; 
		sizex = GI("ASHIBASX");
		sizey = GI("ASHIBASY");
	}
	if(data==ASHIBA2_NO||data==MOVASHIBA2_NO){
		graphic = "graphics\\object\\stage_2_asiba.png"; 
		sizex = GI("ASHIBA2SX");
		sizey = GI("ASHIBA2SY");
	}
	if(data==ASHIBA3_NO||data==MOVASHIBA3_NO){
		graphic = "graphics\\object\\stage_4_asiba.png"; 
		sizex = GI("ASHIBA3SX");
		sizey = GI("ASHIBA3SY");
	}

	// 動く足場
	if( data == MOVASHIBA_NO || data == MOVASHIBA2_NO || data == MOVASHIBA3_NO ){
		AshibaMovable* newAshiba = 
			new AshibaMovable(x*SP->CHSZX, y*SP->CHSZY, 1.0f, graphic, sizex, sizey);
		
		HaichiObjStatic* newObj = new HaichiObjStatic(x*SP->CHSZX, y*SP->CHSZY);
		newObj->SetObject(newAshiba);
		mAshibaList.push_back( newAshiba );
		mAshibaMovList.push_back( newAshiba );
		
		mHaichiListOrig.push_back( newObj );
		mHaichiListTemp.push_back( newObj );
	}

	// 足場
	else if( data == ASHIBA_NO || data == ASHIBA2_NO || data == ASHIBA3_NO ){
	
		Ashiba* newAshiba = 
			new Ashiba(x*SP->CHSZX, y*SP->CHSZY, 1.0f, graphic, sizex, sizey);

		HaichiObjStatic* newObj = new HaichiObjStatic(x*SP->CHSZX, y*SP->CHSZY);
		newObj->SetObject(newAshiba);
		mAshibaList.push_back( newAshiba );

		mHaichiListOrig.push_back( newObj );
		mHaichiListTemp.push_back( newObj );
	}

	// 見えない足場
	else if( data == INVASHIBA3_NO ){
		AshibaInvisible* newAshiba = 
			new AshibaInvisible(x*SP->CHSZX, y*SP->CHSZY, 1.0f, sizex, sizey);
		
		HaichiObjStatic* newObj = new HaichiObjStatic(x*SP->CHSZX, y*SP->CHSZY);
		newObj->SetObject(newAshiba);
		mAshibaList.push_back( newAshiba );

		mHaichiListOrig.push_back( newObj );
		mHaichiListTemp.push_back( newObj );
	}
}