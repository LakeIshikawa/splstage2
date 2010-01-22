#include ".\kumo.h"
#include "..\\Management\\GameControl.h"


/* ｱﾆﾒｰｼｮﾝﾃﾞｰﾀ */
int Kumo::sAniData[][MAX_DATA] =
{
	{ 0, 1, 99 },		// ITO
	{ 0, 99 },			// OCHI
	{ 0, 1, 99 }		// ARUKI
};

float Kumo::sAniTimeData[][MAX_DATA] =
{
	{ 0.2f, 0.2f },		// ITO
	{ 0.2f },			// OCHI
	{ 0.2f, 0.2f }		// ARUKI
};

/* ｸﾞﾗﾌｨｯｸﾃﾞｰﾀ */
char Kumo::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\ene_spider.png",
	"graphics\\teki\\ene_spider_walk.png",
	"graphics\\teki\\ene_spider_walk.png"
};

int Kumo::sMapAtHanteiX[4][MAX_TEN] = 
{
	{ 40, 16, -1 },	//下
	{ -1 },		//上
	{ 51, -1 },	//前
	{ -1 }		//後
};

int Kumo::sMapAtHanteiY[4][MAX_TEN] = 
{ 
	{ 54, 54, -1 },	//下
	{ -1 },		//上
	{ 35, -1 },	//前
	{ -1 }		//後
};


Kumo::Kumo(int rXPx, int rYPx)
{

	KUMOSX = GI("KUMOSX");
	KUMOSY = GI("KUMOSY");

	ITO_SP = GF("ITO_SP");
	ITO_LEN = GI("ITO_LEN");
	TEISHI_TIME = GF("TEISHI_TIME");
	ARUKI_SP = GF("ARUKI_SP");

	mX = rXPx;
	mY = rYPx - sMapAtHanteiY[0][0] + SP->CHSZY;

	mSizeX = KUMOSX;
	mSizeY = KUMOSY;

	mStatus		= ITO;

	mMuki = 0;

	mItoNobi		= 10;
	mMoveStatus		= 0;
	mTeishiTimer	= 0.0f;

	mItoX = mX + mSizeX/2;
	mItoY = mY - 10;

	// 当たり判定
	AddFrame(FR_ITO);
	AddFrame(FR_JIYUU);

	AddCircle(FR_ITO, SP->GRID_BOGYO, 26, 26, 16);
	AddIndexedRect(FR_ITO, SP->GRID_ITO, 0, 26, -200, 30, 0);

	AddRect(FR_JIYUU, SP->GRID_BOGYO, 8, 32, 56, 56);
	AddIndexedRect( FR_JIYUU, SP->GRID_BOUND, TBOUND_IDX, 8, 32, 56, 56);

	SetCurFrame(FR_ITO);

}

//// ｺﾘｼﾞｮﾝ用、ｻｲｽﾞを返す
//int Kumo::GetSizeX()
//{
//	return KUMOSX;
//}

Kumo::~Kumo(void)
{
}

void Kumo::_Move()
{

	SetAnim(mStatus);

	switch( mStatus ){
		case ITO:{

			switch( mMoveStatus ){
				case 0: //上で停止
					mTeishiTimer += SP->FrameTime;
					if(mTeishiTimer > GF("TEISHI_TIME")){
						mTeishiTimer = 0.0f;
						mMoveStatus++;
					}
					break;

				case 1: //下がり
					mItoNobi += ITO_SP;
					if( mItoNobi >= ITO_LEN )
						mMoveStatus++;
					break;

				case 2: //下で停止
					mTeishiTimer += SP->FrameTime;
					if(mTeishiTimer > TEISHI_TIME){
						mTeishiTimer = 0.0f;
						mMoveStatus++;
					}
					break;

				case 3: //上り
					mItoNobi -= ITO_SP;
					if( mItoNobi <= 10 ){
						mItoNobi = 10;
						mMoveStatus = 0;
					}
					break;

			}

			mY = mItoY + mItoNobi; // 蜘蛛が糸の頭についている
			Rect* r = (Rect*)pCollision->GetCurFrame()->GetIndexedShape(0);
			r->SetTop(-mItoNobi);

			// 糸の描画
			DX_SCROLL_DRAW("graphics\\teki\\ito.png", mItoX, mItoY, 0, 0, 1, mItoNobi);
		}
		break;

		case OCHI:
			{
				MapAtHt();

				// 下が当たっている
				if(	mAtari[0] == SP->CHIP_AMHIT || mAtari[0] == SP->CHIP_KGHIT || mCurAshiba ){

					// 速度と加速度をゼロにして、座標を地面に設定
					mSpY = 0;
					mAccY = 0;
					if( !mCurAshiba )
						mY = mShirabe[0] - sMapAtHanteiY[0][0];

					// 歩きまわす
					mStatus = ARUKI;
				}
				else { 
					// 重力を設定
					mAccY = SP->GRAVITY;
				}

				break;
			}

		case ARUKI:

			mSpX = ARUKI_SP * mMuki?1:-1;

			MapAtHt();

			// 前に壁がある
			if( mAtari[2] == SP->CHIP_HIT || mAtari[2] == SP->CHIP_GMNGAILT || mAtari[2] == SP->CHIP_GMNGAIRT || mAtari[2] == SP->CHIP_KGHIT ){
				mMuki = !mMuki;
			}

			// 下に床がある
			if( mAtari[0] == SP->CHIP_AMHIT || mAtari[0] == SP->CHIP_KGHIT || mCurAshiba){
				mSpY = 0;
				mAccY = 0;
				if( mAtari[0] != SP->CHIP_KGHIT && !mCurAshiba) mY = mShirabe[0] - sMapAtHanteiY[0][0];
			}
			else {
				mAccY = SP->GRAVITY;
			}

			break;
	}

	Teki::Draw();

	mSpX += mAccX;
	mSpY += mAccY;
	mX	 += mSpX + mAshibaSpX;
	mY	 += mSpY;
}

/*
	1- 自機に当たる
*/
void Kumo::CollisionResponse(ICollidable* rCollObject, int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	if(jiki){ //当たり！
		if(rThisGroupId == SP->GRID_ITO && mBasStatus == NORMAL && 
			(rOpGroupId == SP->GRID_BOGYO || rOpGroupId == SP->GRID_KOUGEKI)){
				mAniNoX = 0;
				mStatus = OCHI;
				SetCurFrame(FR_JIYUU);
				mMuki = 1;
				//SE
				if( !IsGamenGai() )
					GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kumo_ito.wav");
			}
		else Teki::CollisionResponse(rCollObject, rThisGroupId, rOpGroupId);
	}

}

//////////////////////////protected//////////////////////////////
/*
	ﾏｯﾌﾟとの当たり判定を行います。
	この関数の実行ご、次の変数の中身が変わります：
	mShirabe[]
	mAtari[]
*/
void Kumo::MapAtHt()
{
	MAP_SUPERATHT(mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, 
		sMapAtHanteiX, sMapAtHanteiY, mSizeX, mSizeY, mAtari, mShirabe);
}