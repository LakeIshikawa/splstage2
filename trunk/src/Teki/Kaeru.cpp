#include ".\kaeru.h"
#include "..\\Management\\GameControl.h"

/* ｱﾆﾒｰｼｮﾝﾃﾞｰﾀ */
int Kaeru::sAniData[][MAX_DATA] =
{
	{ 0, 99 },	// TAIKI
	{ 1, 99 },	// JUMP_START
	{ 2, 99 },	// JUMP

};

float Kaeru::sAniTimeData[][MAX_DATA] =
{
	{ 0.2f },	// TAIKI
	{ 0.2f },	// JUMP_START
	{ 0.2f }	// JUMP
};

/* ｸﾞﾗﾌｨｯｸﾃﾞｰﾀ */
char Kaeru::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\ene_frog.png",
	"graphics\\teki\\ene_frog.png",
	"graphics\\teki\\ene_frog.png"
};

int Kaeru::sMapAtHanteiX[4][MAX_TEN] = 
{
	{ 40, 16, -1 },	//下
	{ -1 },		//上
	{ 51, -1 },	//前
	{ -1 }		//後
};

int Kaeru::sMapAtHanteiY[4][MAX_TEN] = 
{ 
	{ 54, 54, -1 },	//下
	{ -1 },		//上
	{ 35, -1 },	//前
	{ -1 }		//後
};


Kaeru::Kaeru(int rXPx, int rYPx)
{

	KAERUSX = GI("KAERUSX");
	KAERUSY = GI("KAERUSY");

	TAIKI_TIME = GF("TAIKI_TIME");
	JUMPSTART_TIME = GF("JUMPSTART_TIME");
	JMPSPX = GF("JMPSPX");
	JMPTAKASA = GF("JMPTAKASA");

	mX = rXPx;
	mY = rYPx - sMapAtHanteiY[0][0] + SP->CHSZY;

	mSizeX = KAERUSX;
	mSizeY = KAERUSY;

	mStatus		= JUMP;

	mTaikiTimer = 0.0f;

	mCurAshiba = NULL;

	// 当たり判定
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, 26, 26, 26);
	AddIndexedRect(0, SP->GRID_BOUND, TBOUND_IDX, 10, 12, 48, 56);
	SetCurFrame(0);
}

Kaeru::~Kaeru(void)
{
}

void Kaeru::_Move()
{

	SetAnim(mStatus);

	// 行動
	switch( mStatus ){
		
		case JUMP:
			MapAtHt();

			if( mAtari[0] == SP->CHIP_AMHIT || mAtari[0] == SP->CHIP_KGHIT || mCurAshiba ){ //下当たってる
				mSpY = 0;
				mSpX = 0;
				mAccX = 0;
				mAccY = 0;
				if( !mCurAshiba )
					mY = mShirabe[0] - sMapAtHanteiY[0][0];
				mStatus = TAIKI;
			}
			else{
				mAccY = SP->GRAVITY;
			}

			if(mAtari[2] == SP->CHIP_HIT || mAtari[2] == SP->CHIP_KGHIT || 
				mAtari[2] == SP->CHIP_GMNGAIRT || mAtari[2] == SP->CHIP_GMNGAILT ){ // 前当たってる
				mMuki = !mMuki;
				mSpX *= -1;
			}
			break;

		case TAIKI:
			WAIT_TIMER(mTaikiTimer, TAIKI_TIME)
			{
				mStatus = JUMP_START;
				if( mCurAshiba ) {
					mCurAshiba->GetOff(this);
					mCurAshiba = NULL;
				}
			}	
			WAIT_END
			break;


		case JUMP_START:
			WAIT_TIMER(mTaikiTimer, JUMPSTART_TIME)
			{
				mStatus = JUMP;
				mSpX = (mMuki?1:-1)*JMPSPX;
				mSpY = -sqrt(2 * SP->GRAVITY * JMPTAKASA);
				//SE
				GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kaeru_junp.wav");
			}	
			WAIT_END
			break;
	
	}// switch

	Teki::Draw();

	mSpX += mAccX;
	mSpY += mAccY;
	mX	 += mSpX + mAshibaSpX;
	mY	 += mSpY;
}


//////////////////////////protected//////////////////////////////
/*
	ﾏｯﾌﾟとの当たり判定を行います。
	この関数の実行ご、次の変数の中身が変わります：
	mShirabe[]
	mAtari[]
*/
void Kaeru::MapAtHt()
{
	MAP_SUPERATHT(mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, 
		sMapAtHanteiX, sMapAtHanteiY, mSizeX, mSizeY, mAtari, mShirabe);
}

/*
	画面の下に落ちたら消える
*/
void Kaeru::DieIfGamenGai()
{
	if(mY > SP->SCRSZY)
		GAMECONTROL->GetMobManager()->Remove(this);
}