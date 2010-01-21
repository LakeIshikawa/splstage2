#include ".\KariudoYumi2.h"
#include "Arrow.h"
#include "..\\Management\\GameControl.h"

class AshibaInvisible;
class AshibaMovable;
class AshibaTenbin;

/* ｱﾆﾒｰｼｮﾝﾃﾞｰﾀ */
int KariudoYumi2::sAniData[][MAX_DATA] =
{
	{ 0, 1, 2, 1, 99 },			// WAIT1
	{ 3, 4, 5, 6, 7, 6, 99 },	// SHOOT1
	{ 0, 1, 2, 1, 99 },			// WAIT2
	{ 3, 4, 5, 6, 7, 6, 99 },	// SHOOT2
	{ 0, 1, 2, 1, 99 },			// WAIT3
	{ 3, 4, 5, 6, 7, 6, 99 },	// SHOOT3
	{ 0, 99 },					// IDLE
	{ 0, 99 }					// SHINDA


};

float KariudoYumi2::sAniTimeData[][MAX_DATA] =
{
	{ 0.2f, 0.2f, 0.2f, 0.2f },				// WAIT1
	{ 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f },	// SHOOT1
	{ 0.2f, 0.2f, 0.2f, 0.2f },				// WAIT2
	{ 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f },	// SHOOT2
	{ 0.2f, 0.2f, 0.2f, 0.2f },				// WAIT3
	{ 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f },	// SHOOT3
	{ 0.2f },								// IDLE
	{ 0.2f }								// SHINDA
};

/* ｸﾞﾗﾌｨｯｸﾃﾞｰﾀ */
char KariudoYumi2::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\ene_hunter22.png",
	"graphics\\teki\\ene_hunter22.png",
	"graphics\\teki\\ene_hunter22.png",
	"graphics\\teki\\ene_hunter22.png",
	"graphics\\teki\\ene_hunter22.png",
	"graphics\\teki\\ene_hunter22.png",
	"graphics\\teki\\ene_hunter22.png",
	"graphics\\teki\\ene_hunter2_damage2.png"
};

KariudoYumi2::KariudoYumi2(int rXPx, int rYPx)
{

	// 設定定数
	KARIYUMI2SY = GI("KARIYUMI2SY");
	KARIYUMI2SX = GI("KARIYUMI2SX");

	KARIYUMI2_WTM = GF("KARIYUMI2_WTM");
	KARIYUMI2_WTM2 = GF("KARIYUMI2_WTM2");
	YUMI2TGT1 = GI("YUMI2TGT1");
	YUMI2TGT2 = GI("YUMI2TGT2");
	KARIYUMI2_NKHI = GF("KARIYUMI2_NKHI");

	mX = rXPx;
	mY = rYPx - KARIYUMI2SY + SP->CHSZY;

	mSizeX = KARIYUMI2SX;
	mSizeY = KARIYUMI2SY;

	mShootTimer = 0.0f;
	mStatus = WAIT1;

	// 当たり判定	
	AddFrame(0);
	AddRect(0, SP->GRID_BOGYO, 43, 33, 81, 119);
	AddIndexedRect(0, SP->GRID_BOUND, TBOUND_IDX, 28, 32, 87, 120);

	SetAnim(0);
}

KariudoYumi2::~KariudoYumi2(void)
{
}

void KariudoYumi2::_Move()
{
	SetAnim( mStatus );

	// 自機の位置を取得
	int jx = GAMECONTROL->GetJiki()->GetAtHtPointX();
	int jy = GAMECONTROL->GetJiki()->GetAtHtPointY();

	if( mStatus != SHINDA ){
		mMuki = CenterX()<jx;
	
		// とまって動かない
		mSpX = 0;
		mSpY = 0;
	}

	switch( mStatus ){
		case WAIT1:
			WAIT_TIMER(mShootTimer, KARIYUMI2_WTM);
			mStatus = SHOOT1;
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_yumi_tame.wav");//SE
			WAIT_END
			break;
		
		case SHOOT1:
			if( mDousaEnd ){
				Arrow* shageki = new Arrow(CenterX(), CenterY(), jx+YUMI2TGT1, jy);
				GAMECONTROL->GetMobManager()->Request(shageki, true);
				mStatus = WAIT2;
				GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_yumi_hassya.wav");//SE
			}
			break;
	
		case WAIT2:
			WAIT_TIMER(mShootTimer, KARIYUMI2_WTM2);
			mStatus = SHOOT2;
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_yumi_tame.wav");//SE
			WAIT_END

			break;

		case SHOOT2:
			if( mDousaEnd ){
				Arrow* shageki = new Arrow(CenterX(), CenterY(), jx, jy);
				GAMECONTROL->GetMobManager()->Request(shageki, true);
				mStatus = WAIT3;
				GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_yumi_hassya.wav");//SE
			}
			break;

		case WAIT3:
			WAIT_TIMER(mShootTimer, KARIYUMI2_WTM2);
			mStatus = SHOOT3;
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_yumi_tame.wav");//SE
			WAIT_END
			break;

		case SHOOT3:
			if( mDousaEnd ){
			Arrow* shageki = new Arrow(CenterX(), CenterY(), jx+YUMI2TGT2, jy);
			GAMECONTROL->GetMobManager()->Request(shageki, true);
			mStatus = WAIT1;
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_yumi_hassya.wav");//SE
			}
			break;

		case IDLE:
			int scx = GAMECONTROL->GetStageManager()->GetCurScrollPointer();
			if( mX < scx + SP->SCRSZX && mX + mSizeX > scx )
			mStatus = SHOOT1;
			break;

	}

	// 画面外になったら消えはしないけど、せめて矢を撃つのはやめる。
	int scx = GAMECONTROL->GetStageManager()->GetCurScrollPointer();
	if( mX > scx + SP->SCRSZX || mX + mSizeX < scx )
		mStatus = IDLE;

	if( mStatus != SHINDA ){
		//自機が近づいたら強制的に射撃をやめる
		if( abs( CenterX() - GAMECONTROL->GetJiki()->GetAtHtPointX() ) < KARIYUMI2_NKHI ){
			mStatus = WAIT1;
			mShootTimer = 0.0f;
		}
	}
	
	Draw();

	mSpX += mAccX;
	mSpY += mAccY;
	mX	 += mSpX + mAshibaSpX;
	mY	 += mSpY;
}

/*
	死んだときの処理(人型)
*/
void KariudoYumi2::Die()
{
		// ﾋﾛｲﾝの位置によってx軸の速度を決める
		mSpX = -SHINIPATT_SPX;
		Jiki* jiki = GAMECONTROL->GetJiki();
		if( jiki->GetAtHtPointX() < CenterX() )
			mSpX *= -1;

		mStatus = SHINDA;
	
		mBasStatus = SHINI;
		mSpY = -SHINIPATT_SHOSP;
		mAccY = SP->GRAVITY;

		//Finalize();
		DisableAshibaCollision();
}

void KariudoYumi2::Move()
{
	Animate();
	_Move();

}
/*
	敵の描画
*/
void KariudoYumi2::Draw()
{

	DX_SCROLL_DRAW(GraphicData()+mAnimSet*MAX_NLEN, mX, mY, 
	mNo_x*mSizeX, mMuki*mSizeY, (mNo_x+1)*mSizeX, (mMuki+1)*mSizeY);

	DieIfGamenGai();

}