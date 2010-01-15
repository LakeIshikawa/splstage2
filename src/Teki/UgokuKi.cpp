#include ".\UgokuKi.h"
#include "..\\Management\\GameControl.h"

/* ｱﾆﾒｰｼｮﾝﾃﾞｰﾀ */
int UgokuKi::sAniData[][MAX_DATA] =
{
	{ 0, 99 },				// KAKUSHI
	{ 1, 2, 99 },			// ACTION
	{ 2, 3, 4, 3, 99 },		// ARUKI

};

float UgokuKi::sAniTimeData[][MAX_DATA] =
{
	{ 0.2f },					// KAKUSHI
	{ 0.2f, 0.2f },				// ACTION
	{ 0.2f, 0.2f, 0.2f, 0.2f, }	// ARUKI
};

/* ｸﾞﾗﾌｨｯｸﾃﾞｰﾀ */
char UgokuKi::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\ene_runner.png",	// KAKUSHI
	"graphics\\teki\\ene_runner.png",	// ACTION
	"graphics\\teki\\ene_runner.png",	// ARUKI
};

// ﾏｯﾌﾟ当たり判定ﾃﾞｰﾀ
int UgokuKi::sMapAtHanteiX[4][MAX_TEN] = 
{
	{ 39, 77, -1 },	//下
	{ -1 },		//上
	{ 147, -1 },	//前
	{ -1 }		//後
};

int UgokuKi::sMapAtHanteiY[4][MAX_TEN] = 
{ 
	{ 181, 181, -1 },	//下
	{ -1 },		//上
	{ 116, -1 },	//前
	{ -1 }		//後
};

UgokuKi::UgokuKi(int rXPx, int rYPx)
{
	// 設定定数
	UGOKUKISX = GI("UGOKUKISX");
	UGOKUKISY = GI("UGOKUKISY");

	UGOKUKIHANI = GF("UGOKUKIHANI");
	UGOKUKISPX = GF("UGOKUKISPX");

	mX = rXPx;
	mY = rYPx - sMapAtHanteiY[0][0] + SP->CHSZY;

	mSizeX = UGOKUKISX;
	mSizeY = UGOKUKISY;

	mStatus = KAKUSHI;


	// 当たり判定	
	AddFrame(0);

	AddRect(0, SP->GRID_HANTEN, 0, 0, 10, mSizeY);
	AddCircle(0, SP->GRID_BOGYO, 60, 60, 49);
	AddCircle(0, SP->GRID_BOGYO, 60, 121, 49);

	
	SetAnim(0);
}

UgokuKi::~UgokuKi(void)
{
}

void UgokuKi::_Move()
{
	SetAnim( mStatus );

	switch( mStatus ){
		case KAKUSHI: {

			// 自機の位置を取得
			int jx = GAMECONTROL->GetJiki()->GetAtHtPointX();

			// ----自機の位置を確認
			float sax = jx - CenterX();

			if( fabs( sax ) < UGOKUKIHANI){
				mStatus = ARUKI;
				mMuki = sax > 0;
			}
		} break;

		case ACTION: {
			if( mDousaEnd )
				mStatus = ARUKI;
		} break;

		case ARUKI: {
				// ----当たりの処理
				MapAtHt();

				// 下
				if(mAtari[0] == SP->CHIP_HIT || mAtari[0] == SP->CHIP_AMHIT || mAtari[0] == SP->CHIP_KGHIT || ISGAMENGAI(mAtari[0])){ 
					mSpY = 0;
					mSpX = (mMuki?1:-1)*UGOKUKISPX;
					mAccX = 0;
					mAccY = 0;
					if( mAtari[0] != SP->CHIP_KGHIT ) mY = mShirabe[0] - sMapAtHanteiY[0][0];
				}
				else{
					mAccY = SP->GRAVITY;
				}
				
				// 前
				if(mAtari[2] == SP->CHIP_HIT || mAtari[2] == SP->CHIP_GMNGAILT || mAtari[2] == SP->CHIP_GMNGAIRT || mAtari[2] == SP->CHIP_KGHIT ){ // 前当たってる
					mMuki = !mMuki;
				}
		} break;


	}

	Teki::Draw();

	mSpX += mAccX;
	mSpY += mAccY;
	mX	 += mSpX;
	mY	 += mSpY;


}

/*
	ﾏｯﾌﾟとの当たり判定を行います。
	この関数の実行ご、次の変数の中身が変わります：
	mShirabe[]
	mAtari[]
*/
void UgokuKi::MapAtHt()
{
	MAP_SUPERATHT(mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, 
		sMapAtHanteiX, sMapAtHanteiY, mSizeX, mSizeY, mAtari, mShirabe);
}


void UgokuKi::CollisionResponse(Collidable* rCollObject, int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	if(jiki){ //当たり！
		if(rThisGroupId == SP->GRID_HANTEN && rOpGroupId == SP->GRID_HANTEN){

			// 自機と同じ方向に歩いている場合は例外
			if( mMuki != GAMECONTROL->GetJiki()->GetMuki() )
				GAMECONTROL->GetJiki()->HantenOrRebound();
			}

		else if( rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_BOGYO ){
			Die();
		}
	}
}