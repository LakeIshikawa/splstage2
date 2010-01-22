#include ".\KumoPink.h"
#include "..\\Management\\GameControl.h"


/* ｱﾆﾒｰｼｮﾝﾃﾞｰﾀ */
int KumoPink::sAniData[][MAX_DATA] =
{
	{ 0, 1, 99 },		// ITO
	{ 0, 99 },			// OCHI
	{ 0, 1, 99 }		// ARUKI
};

float KumoPink::sAniTimeData[][MAX_DATA] =
{
	{ 0.2f, 0.2f },		// ITO
	{ 0.2f },			// OCHI
	{ 0.2f, 0.2f }		// ARUKI
};

/* ｸﾞﾗﾌｨｯｸﾃﾞｰﾀ */
char KumoPink::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\ene_spider3.png",
	"graphics\\teki\\ene_spider4.png",
	"graphics\\teki\\ene_spider4.png"
};

int KumoPink::sMapAtHanteiX[4][MAX_TEN] = 
{
	{ 23, 69, -1 },	//下
	{ -1 },		//上
	{ 89, -1 },	//前
	{ -1 }		//後
};

int KumoPink::sMapAtHanteiY[4][MAX_TEN] = 
{ 
	{ 96, 96, -1 },	//下
	{ -1 },		//上
	{ 81, -1 },	//前
	{ -1 }		//後
};


KumoPink::KumoPink(int rXPx, int rYPx)
{

	KPITO_SP = GF("KPITO_SP");
	KPITO_LEN = GI("KPITO_LEN");
	KPTEISHI_TIME = GF("KPTEISHI_TIME");
	KPARUKI_SP = GF("KPARUKI_SP");

	mX = rXPx;
	mY = rYPx - sMapAtHanteiY[0][0] + SP->CHSZY;

	mSizeX = GI("KUMOPINKSX");
	mSizeY = GI("KUMOPINKSY");

	mStatus		= ITO;

	mMuki = 0;

	mItoNobi		= 10;
	mMoveStatus		= 0;
	mTeishiTimer	= 0.0f;

	mItoX = mX + 47;
	mItoY = mY;

	// 当たり判定
	AddFrame(FR_ITO);
	AddFrame(FR_JIYUU);

	AddCircle(FR_ITO, SP->GRID_BOGYO, 47, 40, 40);
	AddIndexedRect(FR_ITO, SP->GRID_ITO, 0, 47, -200, 49, 0);

	AddRect(FR_JIYUU, SP->GRID_BOGYO, 31, 69, 92, 95);
	AddIndexedRect( FR_JIYUU, SP->GRID_BOUND, TBOUND_IDX, 31, 69, 92, 95);

	SetCurFrame(FR_ITO);

}

//// ｺﾘｼﾞｮﾝ用、ｻｲｽﾞを返す
//int Kumo::GetSizeX()
//{
//	return KUMOSX;
//}

KumoPink::~KumoPink(void)
{
}

void KumoPink::_Move()
{

	SetAnim(mStatus);

	switch( mStatus ){
		case ITO:{

			switch( mMoveStatus ){
				case 0: //上で停止
					mTeishiTimer += SP->FrameTime;
					if(mTeishiTimer > KPTEISHI_TIME){
						mTeishiTimer = 0.0f;
						mMoveStatus++;
					}
					break;

				case 1: //下がり
					mItoNobi += KPITO_SP;
					if( mItoNobi >= KPITO_LEN )
						mMoveStatus++;
					break;

				case 2: //下で停止
					mTeishiTimer += SP->FrameTime;
					if(mTeishiTimer > KPTEISHI_TIME){
						mTeishiTimer = 0.0f;
						mMoveStatus++;
					}
					break;

				case 3: //上り
					mItoNobi -= KPITO_SP;
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
				if( mAtari[0] == SP->CHIP_AMHIT || mAtari[0] == SP->CHIP_KGHIT || mCurAshiba ){

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

			mSpX = KPARUKI_SP * mMuki?1:-1;

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
void KumoPink::CollisionResponse(ICollidable* rCollObject, int rThisGroupId, int rOpGroupId)
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
void KumoPink::MapAtHt()
{
	MAP_SUPERATHT(mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, 
		sMapAtHanteiX, sMapAtHanteiY, mSizeX, mSizeY, mAtari, mShirabe);
}