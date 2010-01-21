#include ".\teki.h"
#include "..\\management\\GameControl.h"

class AshibaInvisible;
class AshibaMovable;
class AshibaTenbin;

/**
	標準コンストラクタ
	自動的に呼ばれます
*/
Teki::Teki(void)
{

	// 設定定数
	SHINIPATT_SPX = GF("SHINIPATT_SPX");
	SHINIPATT_SHOSP = GF("SHINIPATT_SHOSP");
	SPANI = GF("SPANI");

	mBasStatus = NORMAL;

	mAnimSet = 0;
	mAniNoX = 0;
	mAniTimer = 0.0f;
	mDousaEnd = false;

	mAshibaSpX = 0.0f;
	mCurAshiba = NULL;
}

/**
	標準デストラクタ
	派生ｸﾗｽがｵｰﾊﾞｰﾗｲﾄﾞするべき
*/
Teki::~Teki(void)
{
}

/*
	CollidableとLightResponsableのﾀｽｸを実行する
*/
void Teki::RunTask()
{
	Collidable::RunTask();
}

void Teki::Move()
{
	switch (mBasStatus){

	case NORMAL : 
		Animate();
		_Move();
		break;

	case SHINI:
		ShiniPattern();
		break;

	}

	mAshibaSpX = 0;
}

/************************************************************//**
*	一発ｺｰﾙﾒｿｯﾄﾞ。基本動作では、敵が逆さまになり、\n
*	その後放物線を描いて画面のしてに抜けていきます
****************************************************************/
void Teki::Die()
{
	if( mBasStatus != SHINI){

		// ﾋﾛｲﾝの位置によってx軸の速度を決める
		mSpX = -SHINIPATT_SPX;
		Jiki* jiki = GAMECONTROL->GetJiki();
		if( jiki->GetAtHtPointX() < CenterX() )
			mSpX *= -1;
	
		mBasStatus = SHINI;
		mSpY = -SHINIPATT_SHOSP;
		mAccY = SP->GRAVITY;	

		DisableAshibaCollision();
	}
}

/************************************************************//**
*	すべての足場のﾀｰｹﾞｯﾄからはずれ、現在乗っている足場から降りる
****************************************************************/
void Teki::DisableAshibaCollision()
{
	// 足場のターゲットから外れる
	GAMECONTROL->GetStageManager()->GetCurrentStage()->GetHaichi()->RemoveAshibaTargets(this);

	Finalize();
}

/************************************************************//**
*	死ぬ前にﾀｰｹﾞｯﾄをはずして足場から降りる
*	\see _Move
****************************************************************/
void Teki::Finalize()
{
	if( mCurAshiba ) mCurAshiba->GetOff(this);
	mCurAshiba = NULL;
}

/************************************************************//**
*	持続呼びﾒｿｯﾄﾞ。このﾒｿｯﾄﾞを_Moveﾒｿｯﾄﾞで必ず一回呼ぶ必要があります
*	\see _Move
****************************************************************/
void Teki::Draw()
{
	switch( mBasStatus ){

		case NORMAL:
			DX_SCROLL_DRAW(GraphicData()+mAnimSet*MAX_NLEN, mX, mY, 
			mNo_x*mSizeX, mMuki*mSizeY, (mNo_x+1)*mSizeX, (mMuki+1)*mSizeY);
			break;

		case SHINI:
			DX_SCROLL_ROT_DRAW(GraphicData()+mAnimSet*MAX_NLEN, mX, mY, 
				mNo_x*mSizeX, mMuki*mSizeY, (mNo_x+1)*mSizeX, (mMuki+1)*mSizeY, D3DX_PI);

	}

	DieIfGamenGai();

	////ﾃﾞﾊﾞｯｸﾞ - 当たり判定の表示
	//if(mDrawer){
	//	mDrawer->SetCollision(pCollision->GetCurFrame());
	//	mDrawer->Draw();
	//}

}

/************************************************************//**
*	一発呼びﾒｿｯﾄﾞ
*	\param rBango ｱﾆﾒｰｼｮﾝﾊﾟﾀｰﾝ番号（ｱﾆﾒｰｼｮﾝﾃﾞｰﾀのY)
****************************************************************/
void Teki::SetAnim(int rBango)
{
	if( rBango != mAnimSet ) mAniNoX = 0;
	mAnimSet = rBango;

	mNo_x = AnimData()[mAnimSet*MAX_DATA + mAniNoX];
}

/************************************************************//**
*	持続呼びﾒｿｯﾄﾞ
*	敵が死んだときから消えるときまで呼ばれるﾒｿｯﾄﾞ\n
*	これをｵｰﾊﾞｰﾗｲﾄﾞﾒｿｯﾄﾞで呼んだ場合、必ずDie()が呼ばれたこと\n
*	を確認しなければならない
****************************************************************/
void Teki::ShiniPattern()
{
	Draw();
	
	mSpX += mAccX + mAshibaSpX;
	mSpY += mAccY;
	mX	 += mSpX;
	mY	 += mSpY;

}

/************************************************************//**
*	持続呼びﾒｿｯﾄﾞ
*	ｱﾆﾒｰｼｮﾝﾃﾞｰﾀに従い、ｱﾆﾒｰｼｮﾝﾌﾚｰﾑを計算します。\n
*	このﾒｿｯﾄﾞが呼ばれた後、描画よ行うと、ｱﾆﾒｰｼｮﾝが実現します
****************************************************************/
void Teki::Animate()
{
	mDousaEnd = false;

	// ｱﾆﾒｰｼｮﾝ
	WAIT_TIMER(mAniTimer, AniTimeData()[mAnimSet*MAX_DATA + mAniNoX])
		mAniNoX++;
		mNo_x = AnimData()[mAnimSet*MAX_DATA + mAniNoX];
		if( mNo_x == 99 ){
			mAniNoX = 0;
			mDousaEnd = true;
			DousaEnd();
		}
	WAIT_END

	mNo_x = AnimData()[mAnimSet*MAX_DATA + mAniNoX];
}

/************************************************************//**
*	標準の当たり判定\n
*	特別な判定の応答を行う場合はこのﾒｿｯﾄﾞをｵｰﾊﾞｰﾗｲﾄﾞします\n
*
*	標準の処理では次のﾊﾟﾀｰﾝが確認されます:
*	- ﾋﾛｲﾝの攻撃に当たると死ぬ
*	- ﾋﾛｲﾝの防御に当たるとﾋﾛｲﾝにﾀﾞﾒｰｼﾞを当たる
*
*	\param rCollObject	当たった先のｵﾌﾞｼﾞｪｸﾄ(例：ﾋﾛｲﾝ)
*	\param rThisGroupId	この敵のGROUPID(所々によって違う)
*	\param rOpGroupId	当たった先のｵﾌﾞｼﾞｪｸﾄのGROUPID(所々によって違う)
*
****************************************************************/
void Teki::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{

	// ヒロイン
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	if(jiki){ //当たり！
		if( rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_BOGYO ){
			if( mBasStatus != SHINI ){
				Die();
				jiki->IncrementChain();
				jiki->IncreaseTensEmpa();
				//SE
				GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kougekimeityuu.wav");
				GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_teki_down.wav");
			}
		}
		else if( rOpGroupId == SP->GRID_BOGYO && (rThisGroupId == SP->GRID_BOGYO || rThisGroupId == SP->GRID_KOUGEKI) ||
			(rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_KOUGEKI )){
			//ﾋﾛｲﾝにﾀﾞﾒｰｼﾞ
			if( mBasStatus == NORMAL )
				GAMECONTROL->GetJiki()->InflictDamage();
		}
	}
}

