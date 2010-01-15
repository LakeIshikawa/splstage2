#include ".\KariudoKen2.h"
#include "..\\Management\\GameControl.h"

class AshibaInvisible;
class AshibaMovable;
class AshibaTenbin;


/* ｱﾆﾒｰｼｮﾝﾃﾞｰﾀ */
int KariudoKen2::sAniData[][MAX_DATA] =
{
	{ 3, 4, 5, 6, 7, 8, 99 },	// ARUKI
	{ 0, 1, 2, 99 },			// WAIT1
	{ 0, 1, 2, 3, 4, 5, 99 },	// KOGEKI
	{ 0, 1, 2, 99 },			// WAIT2
	{ 0, 99 }					// SHINDA

};

float KariudoKen2::sAniTimeData[][MAX_DATA] =
{
	{ 0.05f, 0.05f, 0.05f, 0.1f, 0.1f, 0.1f },	// ARUKI
	{ 0.2f, 0.2f, 0.2f },					// WAIT1
	{ 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f },	// KOGEKI
	{ 0.2f, 0.2f, 0.2f },					// WAIT2
	{ 0.2f, }								// SHINDA
};

/* ｸﾞﾗﾌｨｯｸﾃﾞｰﾀ */
char KariudoKen2::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\ene_hunter12.png",			// ARUKI
	"graphics\\teki\\ene_hunter12.png",			// WAIT1
	"graphics\\teki\\ene_hunter1_attack2.png",	// KOGEKI
	"graphics\\teki\\ene_hunter12.png",			// WAIT2
	"graphics\\teki\\ene_hunter1_damage2.png",	// SHINDA
};

// ﾏｯﾌﾟ当たり判定ﾃﾞｰﾀ
int KariudoKen2::sMapAtHanteiX[4][MAX_TEN] = 
{
	{ 68, 90, -1 },	//下
	{ -1 },		//上
	{ 90, -1 },	//前
	{ -1 }		//後
};

int KariudoKen2::sMapAtHanteiY[4][MAX_TEN] = 
{ 
	{ 117, 117, -1 },	//下
	{ -1 },		//上
	{ 100, -1 },	//前
	{ -1 }		//後
};

KariudoKen2::KariudoKen2(int rXPx, int rYPx)
{

	KARIKEN2SX = GI("KARIKEN2SX");
	KARIKEN2SY = GI("KARIKEN2SY");

	KARIKEN2SPX = GF("KARIKEN2SPX");
	KARIKEN2KGHANI = GF("KARIKEN2KGHANI");
	KARIKEN2WTM1 = GF("KARIKEN2WTM1");
	KARIKEN2WTM2 = GF("KARIKEN2WTM2");

	mX = rXPx;
	mY = rYPx - sMapAtHanteiY[0][0] + SP->CHSZY;

	mSizeX = KARIKEN2SX;
	mSizeY = KARIKEN2SY;

	mStatus = ARUKI;

	mKgTimer = 0.0f;

	// 当たり判定	
	AddFrame(FR_KAMAE);
	AddFrame(FR_ZANZOU);
	AddFrame(FR_DOWN);

	AddRect(FR_KAMAE, SP->GRID_BOGYO, 43, 33, 81, 119);
	AddIndexedRect( FR_KAMAE, SP->GRID_BOUND, TBOUND_IDX, 38, 22, 83, 120);
	
	AddRect(FR_ZANZOU, SP->GRID_BOGYO, 43, 33, 81, 119);
	AddCircle(FR_ZANZOU, SP->GRID_KOUGEKI, 38, 43, 35);
	AddCircle(FR_ZANZOU, SP->GRID_KOUGEKI, 33, 69, 35);
	AddIndexedRect( FR_ZANZOU, SP->GRID_BOUND, TBOUND_IDX, 38, 22, 83, 120);

	AddRect(FR_DOWN, SP->GRID_BOGYO, 43, 33, 81, 119);
	AddCircle(FR_DOWN, SP->GRID_BOGYO, 20, 62, 11);
	AddIndexedRect( FR_DOWN, SP->GRID_BOUND, TBOUND_IDX, 38, 22, 83, 120);

	//AddCircle(0, GRID_BOGYO, 60, 60, 30);

	SetAnim(0);
}

KariudoKen2::~KariudoKen2(void)
{
}

void KariudoKen2::_Move()
{
	SetAnim( mStatus );

	// 自機の位置を取得
	int jx = GAMECONTROL->GetJiki()->GetAtHtPointX();
	int jy = GAMECONTROL->GetJiki()->GetAtHtPointY();

	// ----当たりの処理
	MapAtHt();

	if( mStatus != SHINDA )
		Ataridp();


	switch( mStatus ){
		case ARUKI: {
			// ----自機の位置を確認
			float sax = jx - CenterX();
			float say = jy - CenterY();
			float sa = sqrt(sax*sax + say*say);

			if( sa < KARIKEN2KGHANI ){
				mStatus = WAIT1;
			}

			break;
		}
		
		case WAIT1:
			mSpX = 0;
			WAIT_TIMER(mKgTimer, KARIKEN2WTM1);
			mStatus = KOGEKI;
			WAIT_END
			break;

		case KOGEKI:
			mSpX = 0;
			mMuki = CenterX() < jx;
			if( mDousaEnd ){
				mStatus = WAIT2;
			}
			break;
	
		case WAIT2:
			mSpX = 0;
			WAIT_TIMER(mKgTimer, KARIKEN2WTM2);
			mStatus = ARUKI;
			WAIT_END
			break;
	}
	
	Draw();

	mSpX += mAccX;
	mSpY += mAccY;
	mX	 += mSpX + mAshibaSpX;
	mY	 += mSpY;

	// 当たり判定のﾌﾚｰﾑ
	if( mStatus != SHINDA )
		HtFrame();
}

/*
	ﾏｯﾌﾟとの当たり判定を行います。
	この関数の実行ご、次の変数の中身が変わります：
	mShirabe[]
	mAtari[]
*/
void KariudoKen2::MapAtHt()
{
	MAP_SUPERATHT(mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, 
		sMapAtHanteiX, sMapAtHanteiY, mSizeX, mSizeY, mAtari, mShirabe);
}
/*
	当たり判定応答
*/
void KariudoKen2::Ataridp()
{
	// 下
	if( mAtari[0] == SP->CHIP_AMHIT || mAtari[0] == SP->CHIP_KGHIT || mCurAshiba){ 
		mSpY = 0;
		mSpX = (mMuki?1:-1)*KARIKEN2SPX;
		mAccX = 0;
		mAccY = 0;
		if( !mCurAshiba )
			mY = mShirabe[0] - sMapAtHanteiY[0][0];
	}
	else{
		mMuki = !mMuki;
		mX -= mSpX;
		mSpX = 0;
	}
	
	// 前
	if(mAtari[2] == SP->CHIP_HIT || mAtari[2] == SP->CHIP_GMNGAILT 
		|| mAtari[2] == SP->CHIP_GMNGAIRT || mAtari[2] == SP->CHIP_KGHIT){ // 前当たってる
		mMuki = !mMuki;
	}
}
/*
	当たり判定のﾌﾚｰﾑ
*/
void KariudoKen2::HtFrame()
{
	switch( mStatus ){
		case ARUKI:
			SetCurFrame( FR_KNDOWN );
			break;

		case KOGEKI:
			if( mAniNoX >= 2 && mAniNoX!=5  ) {
				SetCurFrame( FR_ZANZOU );
			}
			else if( mAniNoX!=5 ) {
				SetCurFrame( FR_KAMAE );
			}
			else {
				SetCurFrame( FR_KNDOWN );
			}

			break;
	}
}

/*
	死んだときの処理(人型)
*/
void KariudoKen2::Die()
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

void KariudoKen2::Move()
{
	Animate();
	_Move();

}
/*
	敵の描画
*/
void KariudoKen2::Draw()
{

	DX_SCROLL_DRAW(GraphicData()+mAnimSet*MAX_NLEN, mX, mY, 
	mNo_x*mSizeX, mMuki*mSizeY, (mNo_x+1)*mSizeX, (mMuki+1)*mSizeY);

	DieIfGamenGai();

	/*//ﾃﾞﾊﾞｯｸﾞ - 当たり判定の表示
	if(mDrawer){
		mDrawer->SetCollision(pCollision->GetCurFrame());
		mDrawer->Draw();
	}*/

}