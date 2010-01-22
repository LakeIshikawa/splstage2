#include ".\jiki.h"
#include "..\\Management\\GameControl.h"
#include "..\\Light\\Light.h"
#include "..\\Event\\GameOverEvt.h"
#include "..\\Stage\\Checkpoint\\CheckpointController.h"
#include "..\\Collision\\Rect.h"
#include "..\\Object\\Ashiba.h"
#include "..\\Object\\AshibaTenbin.h"
#include "..\\Event\\ResetMobEvt.h"
#include "..\\Event\\RestoreTekiAfterCheckpoint.h"
#include "..\\Effect\\HitEffect.h"

//?�??��ｰ?�?�?��?��ｰ??
int Jiki::sAniData[][ANIFR] = { 
	{ 0, 1, 2, 3, 4, 5, 6, 7,99},	//	WALK
	{ 0, 1, 2, 1, 3, 4, 5, 4,99},	//	TEISHI
	{ 0, 1, 2, 3, 4,99},			//	HANTEN
	{ 0, 1, 2,99},					//	KOGEKI_START
	{ 3, 4, 5, 6,99},				//	KOGEKI
	{ 3, 4, 5, 6, 7, 8, 9,99},		//	KOGEKI_END
	{ 0, 1, 2, 3, 4,99},			//	KOGEKI_STAN
	{ 0, 1,99},						//	JUMP_START
	{ 2, 3, 4,99},					//	JUMP_UP
	{ 5, 6, 7,99},					//	JUMP_DOWN
	{ 8, 0,99},						//	JUMP_END
	{ 0, 1,99},						//	DRILL_START
	{ 2, 3,99},						//	DRILL
	{ 4, 5, 6, 7, 8,99},			//	DRILL_END
	{ 0, 1, 2, 1,99},				//	FUYU
	{ 0, 1,99},						//	DAMAGE
	{ 2, 3,99},						//	DAMAGE_END
	{ 0, 1, 2, 3,99},				//	HISATU
	{ 3, 99 },						//	DEAD
	{ 3, 99 },						//	MAKUDOWN
	{ 3, 99 },						//	FADEOUT
	{ 0, 1, 2, 1, 3, 4, 5, 4,99},	//	FADEIN

};

//?�ﾚｰ?�ごとの?�??��ｰ?�?�?�補間時間
double Jiki::sAniTime[][ANIFR] = { 
	{ 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2},	//	WALK
	{ 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2},	//	TEISHI
	{ 0.12, 0.12, 0.12, 0.12, 0.12},			//	HANTEN
	{ 0.06, 0.06, 0.08},						//	KOGEKI_START
	{ 0.08, 0.08, 0.08, 0.08},					//	KOGEKI
	{ 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13},//	KOGEKI_END
	{ 0.2, 0.2, 0.2, 0.2, 0.2},					//	KOGEKI_STAN
	{ 0.2, 0.2},								//	JUMP_START
	{ 0.2, 0.2, 0.2},							//	JUMP_UP
	{ 0.2, 0.2, 0.2},							//	JUMP_DOWN
	{ 0.2, 0.2},								//	JUMP_END
	{ 0.2, 0.2},								//	DRILL_START
	{ 0.2, 0.2},								//	DRILL
	{ 0.2, 0.2, 0.2, 0.2, 0.2},					//	DRILL_END
	{ 0.2, 0.2, 0.2, 0.2},						//	FUYU
	{ 0.2, 0.2},								//	DAMAGE
	{ 0.2, 0.2},								//	DAMAGE_END
	{ 0.2, 0.2, 0.2, 0.2},						//	HISATU
	{ 0.2 },									//	DEAD
	{ 0.2 },									//	MAKUDOWN
	{ 0.2 },									//	FADEOUT
	{ 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2},	//	FADEIN

};

//?�?�ﾗﾌｨ?�?�
char Jiki::sGraphic[][GRAME] = { 
	"graphics\\heroine\\heroine_work.png",		//	WALK
	"graphics\\heroine\\heroine_stend.png",		//	TEISHI
	"graphics\\heroine\\heroine_turn.png",		//	HANTEN
	"graphics\\heroine\\heroine_attack.png",	//	KOGEKI_START
	"graphics\\heroine\\heroine_attack.png",	//	KOGEKI
	"graphics\\heroine\\heroine_attack.png",	//	KOGEKI_END
	"graphics\\heroine\\heroin_stan.png",		//	KOGEKI_STAN
	"graphics\\heroine\\heroine_jump.png",		//	JUMP_START
	"graphics\\heroine\\heroine_jump.png",		//	JUMP_UP
	"graphics\\heroine\\heroine_jump.png",		//	JUMP_DOWN
	"graphics\\heroine\\heroine_jump.png",		//	JUMP_END
	"graphics\\heroine\\heroine_drillkick.png",	//	DRILL_START
	"graphics\\heroine\\heroine_drillkick.png",	//	DRILL
	"graphics\\heroine\\heroine_drillkick.png",	//	DRILL_END
	"graphics\\heroine\\heroine_fall.png",		//	FUYU
	"graphics\\heroine\\heroin_damage.png",		//	DAMAGE
	"graphics\\heroine\\heroin_damage.png",		//	DAMAGE_END
	"graphics\\heroine\\heroin_ special.png",	//	HISATU
	"graphics\\heroine\\heroin_damage.png",		//	DEAD
	"graphics\\heroine\\heroin_damage.png",		//	MAKUDOWN
	"graphics\\heroine\\heroin_damage.png",		//	FADEOUT
	"graphics\\heroine\\heroine_stend.png",		//	FADEIN

};

//当たり判定�?��ｰ??
int	Jiki::sHitX[][4][TENSU] = {
	{
		{ 40, 57, 89,-1}, 		//�?
		{ 62, -1},				//�?
		{ 90, 90, 90, 90, 90,-1}, 		//�?
		{ 31, 19, -1}, 			//�?
	}


};
int	Jiki::sHitY[][4][TENSU] = {
	{
		{118,118,118,-1 }, 		//�?
		{ 0, -1},				//�?
		{117, 95, 65, 40, 25, -1}, 		//�?
		{115, 11, -1}, 			//�?
	}

};

// チェイン
float Jiki::sChainMultSp[] = {
	1.2f, 1.3f, 1.6f, 1.9f, 2.2f, 2.4f
};
// チェイン
float Jiki::sChainMultShoSp[] = {
	1.0f, 1.03f, 1.06f, 1.09f, 1.12f, 1.15f
};

Jiki::Jiki(int rXPx, int rYPy)
{

	// 設定定数
	LIFE_MAX = GI("LIFE_MAX");
	LIFE_SHOKI = GI("LIFE_SHOKI");
	EMP_SHOKI = GF("EMP_SHOKI");
	HERSIZE = GI("HERSIZE");
	DAMAGE_SP = GF("DAMAGE_SP");
	EMP_DOWN = GF("EMP_DOWN");
	EMP_MAX = GF("EMP_MAX");
	TEN_DOWN2 = GF("TEN_DOWN2");
	TEN_UP2 = GF("TEN_UP2");
	TEN_MAX = GF("TEN_MAX");
	EMP_UP = GF("EMP_UP");
	SPANI = GF("SPANI");
	SPWALK = GF("SPWALK");
	ACCKOGEKI = GF("ACCKOGEKI");
	STAN_TIME = GF("STAN_TIME");
	STAN_ANI = GF("STAN_ANI");
	JUMP_SHOSP = GF("JUMP_SHOSP");
	DRILL_SP = GF("DRILL_SP");
	FUYU_SP = GF("FUYU_SP");
	HISATU_TIME = GF("HISATU_TIME");
	MUTEKI_TIME = GF("MUTEKI_TIME");
	TENMETU_TIME = GF("TENMETU_TIME");
	END_TIME = GF("END_TIME");
	DRILL_HEIGTH = GF("DRILL_HEIGTH");
	HANTEN_TIME = GF("HANTEN_TIME");
	HISATU_LTSP = GF("HISATU_LTSP");
	HISATU_HRSP = GF("HISATU_HRSP");
	HISATU_FADE = GF("HISATU_FADE");
	TEN_UTIME = GF("TEN_UTIME");
	TEN_UP1 = GF("TEN_UP1");
	TEN_DTIME = GF("TEN_DTIME");
	TEN_DOWN1 = GF("TEN_DOWN1");
	HER_DIE_TIME = GF("HER_DIE_TIME");

	mInterface = new InterfaceView(this, GAMECONTROL->GetMaku());

	mX		= rXPx;
	mY		= rYPy;
	mZ 		= 100.0f;
	mSpX	= 0;
	mSpY	= 0;
	mAccX	= 0;
	mAccY	= 0;

	mSizeX = HERSIZE;
	mSizeY = HERSIZE;

	//??��ﾒｰ?�??
	ResetTempParams();

	//?�?�ｰ?�?��?
	ResetLife();
	ResetTension();
	ResetEmpacy();

	//SE
	mDmSE	 = false;
	mDmSETimer = 0;
	mTenSE	 = false;
	mHisatuSE = false;


	collisionEnabled = true;

	mChainIdx = 0;

	// 当たり判�?
	AddFrame(FR_ARUKI);
	AddFrame(FR_TACHI);
	AddFrame(FR_JUMP);
	AddFrame(FR_DRILL);
	AddFrame(FR_KOGEKI);
	AddFrame(FR_HISATU);
	AddFrame(FR_DISABLE);

	AddCircle(FR_ARUKI, SP->GRID_BOGYO, 64, 37, 16);
	AddCircle(FR_ARUKI, SP->GRID_BOGYO, 67, 65, 12);
	AddCircle(FR_ARUKI, SP->GRID_BOGYO, 69, 99, 20);
	AddCircle(FR_ARUKI, SP->GRID_HOUSE, mSizeX/2, mSizeY/2, 2);
	AddIndexedRect(FR_ARUKI, SP->GRID_BOUND, 0, 35, 80, 85, 118);

	AddCircle(FR_TACHI, SP->GRID_BOGYO, 63, 37, 16);
	AddCircle(FR_TACHI, SP->GRID_BOGYO, 63, 67, 16);
	AddCircle(FR_TACHI, SP->GRID_BOGYO, 63, 98, 20);
	AddCircle(FR_TACHI, SP->GRID_HOUSE, mSizeX/2, mSizeY/2, 2);
	AddIndexedRect(FR_TACHI, SP->GRID_BOUND, 0, 35, 80, 85, 118);

	AddCircle(FR_JUMP, SP->GRID_BOGYO, 53, 34, 16);
	AddCircle(FR_JUMP, SP->GRID_BOGYO, 59, 62, 12);
	AddCircle(FR_JUMP, SP->GRID_BOGYO, 57, 95, 20);
	AddCircle(FR_JUMP, SP->GRID_HOUSE, mSizeX/2, mSizeY/2, 2);
	AddIndexedRect(FR_JUMP, SP->GRID_BOUND, 0, 35, 80, 85, 118);

	AddCircle(FR_DRILL, SP->GRID_BOGYO, 76, 44, 16);
	AddCircle(FR_DRILL, SP->GRID_BOGYO, 53, 67, 16);
	AddCircle(FR_DRILL, SP->GRID_KOUGEKI, 25, 95, 24);
	AddCircle(FR_DRILL, SP->GRID_HOUSE, mSizeX/2, mSizeY/2, 2);
	AddIndexedRect(FR_DRILL, SP->GRID_BOUND, 0, 10, 80, 85, 118);

	AddCircle(FR_KOGEKI, SP->GRID_BOGYO, 55, 38, 16);
	AddCircle(FR_KOGEKI, SP->GRID_BOGYO, 55, 69, 16);
	AddCircle(FR_KOGEKI, SP->GRID_BOGYO, 55, 101, 16);
	AddCircle(FR_KOGEKI, SP->GRID_KOUGEKI, 24, 92, 24);
	AddCircle(FR_KOGEKI, SP->GRID_HOUSE, mSizeX/2, mSizeY/2, 2);
	AddIndexedRect(FR_KOGEKI, SP->GRID_BOUND, 0, 35, 80, 85, 118);

	AddCircle(FR_HISATU, SP->GRID_KOUGEKI, 58, 68, 48);
	AddCircle(FR_HISATU, SP->GRID_HOUSE, mSizeX/2, mSizeY/2, 2);
	AddIndexedRect(FR_HISATU, SP->GRID_BOUND, 0, 35, 80, 85, 118);
	
	SetCurFrame(FR_ARUKI);
}

void Jiki::ResetEmpacy(){
	mEmp	 =	EMP_SHOKI; 
	mEmpTeki =	0;
}

void Jiki::ResetLife(){
	mLife	 =	LIFE_SHOKI;
}

void Jiki::ResetTension(){
	 mTen	 =	0; 
	 mTenTime = 0; 
	 mTenFl	 =	false;
}

void Jiki::ResetTempParams()
{
	//?�??��ｰ?�?�??
	mAniTimer	= 0;
	mAniNoX		= 0;
	mAniNoY		= 0;

	//?�??��??��
	//SetSuperWait(3.0f);
	mStatus		= WALK;
	mMuki		= 1;	

	//?�?�ｰ?�ｵ?�?�ﾞｰ
	mGmOvFl	 = 0;

	// �?��ージ
	mDgMutekiFl	 = 0;
	mDgMapFl	 = false;
	mDamageTimer = 0;
	//mTenmetuTimer = 0;
	mAlphaVal = 1.0f;
	mAlphaTimer = 0.0f;

	//?�ｲ??
	mAkaTimer	= 0;
	mAkaTimer2	= 0;
	mStanTimer	= 0;
	mStanAni	= 0;
	mAoTimer	= 0;
	mMidTimer	= 0;
	mAniTeishi	= false;
	mMidFl		= false;

	mHozonY		= mY;
	mDrillFl	= 0;
	mHisatuTime = 0;
	mHsX	= 0;
	mHsY	= 0;

	//?�ｪ?�??�?
	mFadeFl = 0;
	mFadeFl2 = false;

	//足場
	mAshibaFl = false;
	mCurAshiba = NULL;
	mAshiSpX = 0;

	//強風
	mKazeAccX = 0;

	// ??��?�?�?�ｴ?�ｪ?�??
	mChargeFx = NULL;
}

Jiki::~Jiki(void) 
{
	delete mInterface;
}

// ?�?�ｼ?�ｮ?�用、�?機�??�?�?�?�を返す
int Jiki::GetSizeX()
{
	return HERSIZE;
}

/*
	基本?�?�ｽの??��?�を�?っきり行いま�?
*/
void Jiki::RunTask()
{
	Collidable::RunTask();
	LightResponseAble::RunTask();
}

/*
	?�ﾛｲ?�に??��ﾒｰ?�?�を与え�?
*/
void Jiki::InflictDamage()
{	

	if( mDgMutekiFl == 0 && !mHouseProtected){
		if( mStatus != DAMAGE && mStatus != DAMAGE_END && 
			mStatus != DEAD && mStatus != FADEIN && mStatus != FADEOUT 
			&& mSuperStatus == CONTROL ){
			// SE
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kougekimeityuu.wav");
			mStatus = DAMAGE;
			mDgMutekiFl = 1;
			mDgMapFl= true;
			mAniNoX = 0;
			mSpY	= DAMAGE_SP;
			// 足場から降り�?
			if( mCurAshiba ) {
				mCurAshiba->GetOff(this);
				mCurAshiba = NULL;
			}
			mDmSETimer = 0;
			SetTransparent(true);

			//?�?�ﾊﾟｼ?�
			mEmp -= EMP_DOWN;
			if( mEmp <= 0 ){
				Die();
			}
			if( mEmp > EMP_MAX ) mEmp = EMP_MAX;

			//??��ｼ?�??
			mTen -= TEN_DOWN2;
			if( mTen < 0 ) mTen = 0;
			if( mTen > TEN_MAX ) mTen = TEN_MAX;

			ResetChain();
		}
	}
}
/*
	?�ﾛｲ?��???��ｼ?�?�or??��ﾊﾟｼ?�を上げ�?
*/
void Jiki::IncreaseTensEmpa()
{	

		//??��ｼ?�??
		if( mStatus == KOGEKI || mStatus == KOGEKI_START || mStatus == KOGEKI_END
			|| mStatus == DRILL || mStatus == DRILL_START ){
			RestoreTension(TEN_UP2, false);
		}
		//?�?�ﾊﾟｼ?�
		if( mStatus == HISATU ){
			mEmpTeki++;
			if( mEmpTeki == EMP_UP ){
				mEmpTeki = 0;
				RestoreEmpacy(1, false);
			}
		}

}
/*
	すべての当たり判定をオフにする
*/
void Jiki::DisableCollision()
{
	collisionEnabled = false;
	SetCurFrame( FR_DISABLE );
}

/*
	すべての当たり判定をオンにする
*/
void Jiki::EnableCollision()
{
	collisionEnabled = true;
}

/*
	ヒロインを演�?モードにする (停止)
*/
void Jiki::SetSuperWait(float rTime)
{
	SetLightResponse(false);
	DisableCollision();
	mSuperStatus = WAIT;

	mSuperWaitTimer = rTime;
}

/*
	ヒロインを操作モードにする (普�?
*/
void Jiki::SetSuperControl()
{
	SetLightResponse(true);
	EnableCollision();
	mSuperStatus = CONTROL;
}

/*
	ヒロインをいったん止める
*/
void Jiki::SetSuperPause()
{
	SetLightResponse(false);
	DisableCollision();
	mSuperStatus = PAUSE;
	mSpX = 0;
	mSpY = 0;
	mAccX = 0;
	mAccY = SP->GRAVITY;

}

void Jiki::Move()
{

	//?�ｯ?�ﾟとの当たり判�?
	MapAtHt();
	
	//?�??��ｰ?�?�??
	int	no;
	bool dosa_end = false;

	mAniNoY = mStatus;

	// チェインに反映させ�?歩きと攻�??み)
	float mfactor = 1.0f;
	if( mStatus == KOGEKI || mStatus == KOGEKI_END || mStatus == KOGEKI_START ||
		mStatus == WALK || mStatus == HANTEN )
	{
		mfactor = sChainMultSp[mChainIdx];
	}


	mAniTimer += SP->FrameTime;
	if( mAniTimer >= sAniTime[mAniNoY][mAniNoX]/mfactor ){
		mAniTimer = 0;
		if( !mAniTeishi ) mAniNoX++;
		no = sAniData[mAniNoY][mAniNoX];
		if( no == 99 ){
			mAniNoX = 0;
			dosa_end = true;
		}
	}
	no = sAniData[mAniNoY][mAniNoX];
	mAniTeishi	= false;

	//?�?�ｪ?�????�??��ｰ?�?�??
	if( mStatus == KOGEKI_STAN && mAniNoX > 2 ){
		WAIT_TIMER(mStanTimer, STAN_ANI)
			mStanTimer = 0;
			mStanAni++;
			if( mStanAni > 4 )	mStanAni = 0;
		WAIT_END
	}

	// スーパ�?ス�??タス
	switch( mSuperStatus ){
		case WAIT:
			{
				mStatus = TEISHI;
				mSpX = 0;
				mAccX = 0;

				// タイマ�?
				mSuperWaitTimer -= SP->FrameTime;
				if( mSuperWaitTimer < 0 ){
					mSuperWaitTimer = 0;
					SetSuperControl();
				}
				break;
			}
		case PAUSE:
			{
				mStatus = TEISHI;
				mSpX = 0;
				mAccX = 0;
				break;
			}
		case CONTROL:
			{
				//?�??��??��
				switch( mStatus ){

					//歩�?
					case WALK :
						mSpX = SPWALK*sChainMultSp[mChainIdx] * GetMukiMult();
						break;


						//攻�??�ｲ??��)
					case KOGEKI_START :
						mSpX = SPWALK*sChainMultSp[mChainIdx] * GetMukiMult();
						mAccX = 0;
						//開始ｱ??��ｰ?�?�?�が終わったら攻�?��
						if( dosa_end ){
							mStatus = KOGEKI;
							//SE
							GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_hiroin_tijoukougeki.wav");
						}
						break;

					case KOGEKI :
						mAccX = (float)( ACCKOGEKI / SP->FRAMERATE ) * GetMukiMult();
						//mSpX += mAccX * GetMukiMult();
						break;

					case KOGEKI_STAN :
						mAkaTimer2 += SP->FrameTime;
						mSpX = 0;
						mAccX = 0;
						//?�??��ｰ?�?�??+を停止
						if( mAniNoX == 4 ) mAniTeishi = true;
						//歩きに戻�?
						if( mAkaTimer2 >= STAN_TIME ){
							mStatus = WALK;
						}
						break;


						//停止・反転(?�ｲ??��)
					case TEISHI :
						mSpX = 0;
						mAccX = 0;
						break;

					case HANTEN :
						mSpX = 0;
						mAccX = 0;
						//反転?�??��ｰ?�?�?�が終わったら向きを変えて歩きへ
						if( dosa_end ){
							mMuki = !mMuki;
							mStatus = WALK;
						}
						break;


						//?�?�ｬ?�ﾌ�??�ｲ??�?
					case JUMP_START :
						// 足場に乗って�?��場合�?、まず降りる
						if(mCurAshiba) mCurAshiba->GetOff(this);
						mCurAshiba = NULL;

						mSpX = 0;
						mAccX = 0;
						//開始ｱ??��ｰ?�?�?�が終わったら?�?�ｬ?�ﾌﾟへ
						if( dosa_end ){
							mSpY = JUMP_SHOSP*sChainMultShoSp[mChainIdx];
							mStatus = JUMP_UP;
						}
						break;

					case JUMP_UP :
						//前が当たってな�?��のX
						if( mHitFl[2] == SP->CHIP_NOHIT )
							mSpX = SPWALK * sChainMultSp[mChainIdx] * GetMukiMult();
						//?�??��ｰ?�?�??+を停止
						if( mAniNoX == 2 ) mAniTeishi = true;
						//頂点に達したら落下へ
						if( mSpY >= 0 ){
							mStatus = JUMP_DOWN;
							mAniNoX = 0;
						}
						break;

					case JUMP_DOWN :
						//前が当たってな�?��のX
						if( mHitFl[2] == SP->CHIP_NOHIT ){
							mSpX = SPWALK * GetMukiMult();
						}
						//?�??��ｰ?�?�??+を停止
						if( mAniNoX == 2 ) mAniTeishi = true;
						break;


						//??��ﾘﾙｷ?�?�
					case DRILL_START :
						if( mDrillFl == 2 ){
							mSpX = DRILL_SP * GetMukiMult();
							mSpY = DRILL_SP;
						}
						//開始ｱ??��ｰ?�?�?�が終わったら??��ﾘﾙｷ?�?�へ
						if( dosa_end ){
							mStatus = DRILL;
						}
						break;

					case DRILL :
						if( mDrillFl == 2 ){
							mSpX = DRILL_SP * GetMukiMult();
							mSpY = DRILL_SP;
						}
						break;


						//浮�?
					case FUYU :
						mSpX = 0;
						mAccX = 0;
						mAccY = 0;
						mSpY = FUYU_SP;
						break;


						//??��ﾒｰ?�??
					case DAMAGE :
						mDgMapFl = true;
						//後が当たってな�?��のX
						if( mHitFl[3] != SP->CHIP_HIT && mHitFl[3] != SP->CHIP_GMNGAIRT && 
							mHitFl[3] != SP->CHIP_GMNGAILT && mHitFl[3] != SP->CHIP_KGHIT )
							mSpX = SPWALK * -GetMukiMult();
						if( mAniNoX == 1 ){
							mAniTeishi = true;
							// SE
							if( !mDmSE ){//?�?�ﾊﾟｼ?�が減る
								WAIT_TIMER( mDmSETimer, 0.2 )
								GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_hiroin_damage.wav");
								mDmSE = true;
								WAIT_END
							}

						}
						break;

					case DAMAGE_END :
						mSpX = 0;
						mAccX = 0;
						mDmSE = false;
						mDmSETimer = 0;
						//終�?��??��ｰ?�?�?�が終わったら歩きへ
						if( mGmOvFl == 0 ){
							if( dosa_end ){
								mStatus = WALK;
								mDgMutekiFl = 2;
								mDgMapFl   = false;
							}
						}else{
							if( dosa_end ) {
								mAniNoX = 1;
								if( mGmOvFl == 1 ) mGmOvFl = 2;
							}
						}
						break;


						//終�?���?
					case KOGEKI_END :
					/*	mSpX = SPWALK*sChainMultSp[mChainIdx] * GetMukiMult();
						mAccX = 0;
						if( dosa_end ){
							mStatus = WALK;
						}
						break;*/

					case JUMP_END :
					case DRILL_END :
						//歩きに戻�?
						mSpX = 0;
						mAccX = 0;
						if( dosa_end ){
							mStatus = WALK;
						}
						break;


						//�?���?
					case HISATU :
						{
						mHisatuTime += SP->FrameTime;

						//?�ｲ???速度減�?
						CONTROLLIGHT->SetSpX( GAMECONTROL->GetDXController()->GetMouseState().lX / HISATU_LTSP );
						CONTROLLIGHT->SetSpY( GAMECONTROL->GetDXController()->GetMouseState().lY / HISATU_LTSP );

						//?�?�?�ｰ?�を?�ｲ??��統�?
						int scpx = GAMECONTROL->GetStageManager()->GetCurScrollPointer();

						mHsX = CONTROLLIGHT->GetX() - HERSIZE/2;
						mHsY = CONTROLLIGHT->GetY() - HERSIZE/2;

						//?�ﾛｲ?��?移�?
						float sax = mHsX - (mX- scpx);
						float say = mHsY - mY;

						if( mHsX > mX - scpx && sax > HISATU_HRSP ) mSpX = sax/HISATU_HRSP;
						if( mHsX < mX - scpx && sax < HISATU_HRSP ) mSpX = sax/HISATU_HRSP;
						if( mHsX == mX - scpx ) { mSpX = 0; mAccX = 0; }

						if( mHsY > mY && say > HISATU_HRSP ) mSpY = say/HISATU_HRSP;
						if( mHsY < mY && say < HISATU_HRSP ) mSpY = say/HISATU_HRSP;
						if( mHsY == mY ) mSpY = 0;

						// 速度限界
						if( mSpX > GF("HISATSU_MAXSP") ) mSpX = GF("HISATSU_MAXSP");
						if( mSpX < -GF("HISATSU_MAXSP") ) mSpX = -GF("HISATSU_MAXSP");
						if( mSpY > GF("HISATSU_MAXSP") ) mSpY = GF("HISATSU_MAXSP");
						if( mSpY < -GF("HISATSU_MAXSP") ) mSpY = -GF("HISATSU_MAXSP");

						//?�ﾛｲ?��?向き
						if( mSpX < 0 ){
							mMuki = 0;//�?
						}
						if( mSpX >= 0 ){
							mMuki = 1;//�?
						}

						//当たり判定�?
						GAMECONTROL->GetStageManager()->GetCurMap()->SuperAtariHantei(
						mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, sHitX[0], sHitY[0], HERSIZE, HERSIZE, mHitFl, mKabeIchi);
						if( mHitFl[2] == SP->CHIP_HIT || mHitFl[2] == SP->CHIP_GMNGAIRT || 
							mHitFl[2] == SP->CHIP_GMNGAILT || mHitFl[2] == SP->CHIP_KGHIT){
								if( mSpX * -GetMukiMult() < 0 ) {
									mSpX = 0;//�?
									mAccX = 0;
									if( mMuki ){
										mX = mKabeIchi[2] - sHitX[0][2][0];
									}
									else{
										mX = mKabeIchi[2] - ( HERSIZE - sHitX[0][2][0]);
									}
								}
						}
						if( mHitFl[0] == SP->CHIP_AMHIT || mHitFl[0] == SP->CHIP_KGHIT ){
							if( mSpY > 0 ) mSpY = 0;//�?
						}
						if( mHitFl[1] == SP->CHIP_HIT || mHitFl[1] == SP->CHIP_KGHIT ){
							if( mSpY < 0 ) {
								mSpY = 0;//�?
								mAccY = 0;
								mY = mKabeIchi[1] - sHitY[0][1][0];
							}
						}


						//時間がきたら終�?
						if( mHisatuTime > HISATU_TIME ){
							GAMECONTROL->GetFader()->SetSpeed( 0.03 );
							GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();
							if( !mHisatuSE ){//SE
								GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_hiroin_hissatu_end.wav");
								GAMECONTROL->GetSoundController()->SetBGM(GAMECONTROL->GetStageManager()->GetCurrentStage()->GetBGM());
								mHisatuSE = true;
							}
							//�?���?���?��ｪ?�??�?
							if( !mFadeFl2  && GAMECONTROL->GetFader()->FadeOut() ){
								mHisatuTime = 0;
								mStatus = JUMP_DOWN;
								mAniNoX = 0;
								mX += mSpX;
								mSpX = SPWALK * -GetMukiMult();
								mTen	 =	0;
								mEmpTeki = 0;
								//?�ｲ???速度戻�?
								CONTROLLIGHT->SetSpX( GAMECONTROL->GetDXController()->GetMouseState().lX );
								CONTROLLIGHT->SetSpY( GAMECONTROL->GetDXController()->GetMouseState().lY );
								//l->TurnOff();
								mDgMapFl   = false;
								mDgMutekiFl = 0;
								mFadeFl2 = true;
								mHisatuSE = false;
							}
						}

						mChargeFx->SetPos(mX + HERSIZE/2, mY + HERSIZE/2);

						break;
						}

					case DEAD:
						WAIT_TIMER(mAlphaTimer, HER_DIE_TIME)
							mLife--;
							if( mLife == 0){
								mGmOvFl = 1;
								mStatus = DAMAGE_END;
							}
							else{
									mStatus = FADEOUT;
							}
						WAIT_END
						break;

					case FADEOUT:
						if( GAMECONTROL->GetFader()->FadeOut()){
							mStatus = FADEIN;

							Stage* curStage = GAMECONTROL->GetStageManager()->GetCurrentStage();

							// ?�ﾛｲ?��?位置をチェ�?��ポイントに調整
							int restorePointX = curStage->GetCheckpointController()->GetStartPointX(mX + HERSIZE/2);
							int restorePointY = curStage->GetCheckpointController()->GetStartPointY(mX + HERSIZE/2);
							GAMECONTROL->GetStageManager()->GetCurMap()->SetScrollP( restorePointX - GI("SCRSZX")/2);
							mY = restorePointY - HERSIZE;
							mX = restorePointX - HERSIZE/2;

							// 透�?にする
							SetTransparent(true);

							// 当たり判定を有効に戻�?
							EnableCollision();

							// ?�ｲ??��作を戻�?
							SetLightResponse(true);

							// �?��ションとエンパシーをリセ�?��
							ResetEmpacy();
							ResetTension();

							// 現在出てるものを�?部消す
							GAMECONTROL->GetEventManager()->Request(new ResetMobEvt());

							// 敵を復活地に従って復活させ�?
							GAMECONTROL->GetEventManager()->Request(new RestoreTekiAfterCheckpoint( mX + HERSIZE/2 ));

							//制限時間ﾘｾ?�??
							GAMECONTROL->GetStageManager()->GetCurrentStage()->GetSeigenJikan()->SeigenJikanReset();
						}
						break;

					case FADEIN:
						if( GAMECONTROL->GetFader()->FadeIn() ){
							mStatus = WALK;

							// 無敵にする
							mDgMutekiFl = 2;
							mDgMapFl   = false;

							GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOn();
							GAMECONTROL->GetSoundController()->SetBGM(GAMECONTROL->GetStageManager()->GetCurrentStage()->GetBGM());
						}
				}
		break;
		}
	}

	//?�ｪ?�??�?
	Fade();

	//SE?�ｰ?�ﾟ終�?
	if( mStatus != KOGEKI )
		GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_hiroin_tijoukougeki.wav");
	if( mStatus != DRILL && mStatus != DRILL_START )
		GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_hiroin_kuutyuukougeki.wav");

	//??��ﾒｰ?�??
	if( mDgMutekiFl == 2 ){
		mDamageTimer += SP->FrameTime;
		//mTenmetuTimer += SP->FrameTime;
		//無敵時間
		if( mDamageTimer > MUTEKI_TIME ){
			mDamageTimer = 0;
			//mTenmetuTimer =0;
			mDgMutekiFl = 0;
			SetTransparent(false);
		}
	}


	//移�?
	if( (mStatus != HISATU && mStatus != TEISHI) || mSuperStatus != CONTROL)
		mSpY += mAccY;//常に重力が代入されて�?��
	
	if( !(mHitFl[2]==SP->CHIP_GMNGAILT || mHitFl[2]==SP->CHIP_GMNGAIRT|| mHitFl[2]==SP->CHIP_HIT ||
		mHitFl[3]==SP->CHIP_GMNGAILT || mHitFl[3]==SP->CHIP_GMNGAIRT || mHitFl[3]==SP->CHIP_HIT )) 
		mSpX += mAccX+mKazeAccX;

		mX += mSpX + mAshiSpX;
		mY += mSpY;

		//// 足場
		mAshiSpX = 0;
		if( mStatus == HISATU && mCurAshiba ){
			mCurAshiba->GetOff(this);
			mCurAshiba = NULL;
		}
		//if( mCurAshiba && !(mHitFl[2]==SP->CHIP_GMNGAILT || mHitFl[2]==SP->CHIP_GMNGAIRT|| mHitFl[2]==SP->CHIP_HIT ||
		//mHitFl[3]==SP->CHIP_GMNGAILT || mHitFl[3]==SP->CHIP_GMNGAIRT || mHitFl[3]==SP->CHIP_HIT )){
		//	mX += mCurAshiba->GetSpX();
		//}

	//?�??��ｰ?�?�?�no更新
	mAniNoY = mStatus;
	no = sAniData[mAniNoY][mAniNoX];


	//描画(点�?
	int scr = (int)(GAMECONTROL->GetStageManager()->GetCurScrollPointer());
	/*if( mTenmetuTimer > TENMETU_TIME ){
		if( mTenmetuTimer > TENMETU_TIME*2 ) mTenmetuTimer = 0;
	}else{*/
		DX_DRAWALPHA(sGraphic[mStatus], 
			(int)mX - scr, (int)mY, HERSIZE*no, HERSIZE*mMuki, HERSIZE+HERSIZE*no, HERSIZE+HERSIZE*mMuki, mAlphaVal);
	//}
	if( mStatus == KOGEKI_STAN && mAniNoX > 2 ){
	DX_DRAW("graphics\\effect\\staneffect.png", 
		((int)mX + HERSIZE/2*!mMuki + 25*GetMukiMult()) - scr, (int)mY, 56*mStanAni, 0, 56+56*mStanAni, 56);
	}

	collisionFrames();
	Gameover();

	//SE(??��ｼ?�??
	if( mTen >= TEN_MAX ){
		if( !mTenSE ){
			mTenSE = true;
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_tensyon_maxn.wav");
		}
	}else{
		mTenSE = false;
	}

	mKazeAccX = 0;
	mHouseProtected = false;

}


/*
	?�ｲ??��の当たり判�?
*/
int Jiki::GetAtHtPointX()
{
	return (int)mX + HERSIZE/2;	
}

int Jiki::GetAtHtPointY()
{
	return (int)mY + HERSIZE/2;
}

bool Jiki::GetMuki()
{
	return mMuki;
}

/*
	?�ｲ???処�?
*/
void Jiki::ResponseAka()//---------------------?�ｲ??��
{

	UnTeishi();//歩き�?�?
	AoCheck();//反転

	Hisatu();//�?���?

	//攻�?
	if( mStatus == WALK ){
		mStatus = KOGEKI_START;
		mSpX	= 0;
		mAniNoX = 0;
		mAkaTimer = 0;
	}

	mAkaTimer += SP->FrameTime;

	//強制終�?
	if( mAkaTimer > END_TIME && mStatus == KOGEKI ){
		mAkaTimer = 0;
		mAkaTimer2 = 0;
		mStanTimer = 0;
		mStatus	  = KOGEKI_STAN;
		mAniNoX = 0;
	}


	//??��ﾘﾙｷ?�?�
	if( mDrillFl == 1 ){//?�回の?�?�ｬ?�ﾌﾟに�?��しか使えません
		if( mY+HERSIZE <= mHozonY-DRILL_HEIGTH && mMidFl ){
			if( mStatus == JUMP_UP || mStatus == JUMP_DOWN ){
				mDrillFl = 2;
				mMidTimer = 0;
				mStatus = DRILL_START;
				mAniNoX = 0;
				mMidFl	= false;
				//SE
				GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_hiroin_kuutyuukougeki.wav");

			}
		}
	}
	MidCheck();//?�?�ｬ?�ﾌ�?

	//??��ｼ?�??
	if( !mTenFl ){
		mTenFl = !mTenFl;
		mTenTime = 0;
	}
	Tension();

}

void Jiki::ResponseAo()//----------------------?�ｲ??��
{

	AkaCheck();//攻�?
	MidCheck();//?�?�ｬ?�ﾌ�?

	Hisatu();//�?���?

	//停止
	if( mStatus == WALK ){
		mStatus = TEISHI;
		mAniNoX = 0;
		mAoTimer = 0;
	}

	mAoTimer += SP->FrameTime;

	//浮�?
	if( mStatus == JUMP_DOWN ){
		mStatus = FUYU;
		mAniNoX = 0;
		mMidFl	= false;
	}

	//??��ﾘﾙｷ?�?�は?�回の?�?�ｬ?�ﾌﾟに�?��しか使えません
	if( mDrillFl == 1 )
		mDrillFl  = 0;

	//??��ｼ?�??
	if( !mTenFl ){
		mTenFl = !mTenFl;
		mTenTime = 0;
	}
	Tension();

}

void Jiki::ResponseMidori()//------------------?�ｲ??�?
{

	UnTeishi();//歩き�?�?
	AkaCheck();//攻�?
	AoCheck();//反転

	Hisatu();//�?���?

	//?�?�ｬ?�ﾌ�?
	if( mStatus == WALK ){
		mStatus = JUMP_START;
		mAniNoX = 0;
		mMidTimer = 0;
		//SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_hiroin_junp.wav");
		//?�回の?�?�ｬ?�ﾌﾟに�?��しか使えません
		if( mDrillFl == 0 )
			mDrillFl  = 1;
	}

	mMidTimer += SP->FrameTime;
	mMidFl	= true;

	
	//??��ｼ?�??
	if( !mTenFl ){
		mTenFl = !mTenFl;
		mTenTime = 0;
	}
	Tension();

}

void Jiki::ResponseMushoku()//-----------------?�ｲ??��色
{

	UnTeishi();//歩き�?�?
	AkaCheck();//攻�?
	AoCheck();//反転
	MidCheck();//?�?�ｬ?�ﾌ�?

	Hisatu();//�?���?

	//??��ｼ?�??
	if( !mTenFl ){
		mTenFl = !mTenFl;
		mTenTime = 0;
	}
	Tension();

}

void Jiki::NoLight()//-------------------------?�ｲ??���?
{

	UnTeishi();//歩き�?�?
	AkaCheck();//攻�?
	AoCheck();//反転
	MidCheck();//?�?�ｬ?�ﾌ�?

	//??��ｼ?�??
	if( mTenFl ){
		mTenFl = !mTenFl;
		mTenTime = 0;
	}
	Tension();
}


/*
	?�ｲ???処�?そ�?�?
*/

//�?���?
void	Jiki::Hisatu()
{

	//??��ｼ?�?�MAX??��?�ﾟｰ?�押しで�?���?
	if( mStatus == WALK ){
		if( GAMECONTROL->GetDXController()->KeyPush( DIK_SPACE ) &&
				mTen >= TEN_MAX ){
		mStatus = TEISHI;
		//mTenmetuTimer = 0;
		mFadeFl = 1;
		//GAMECONTROL->GetFader()->SetSpeed( HISATU_FADE );
		GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();
		mDgMutekiFl = 1;
		SetTransparent(false);
		//SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_hiroin_hissatu.wav");
		}
	}

}

//攻�?��態から終�?��作へ(?�ｲ??��)
void Jiki::AkaCheck(){
	
	//攻�?
	if( mStatus == KOGEKI ){
		mAkaTimer = 0;
		mAniNoX   = 0;
		mStatus   = KOGEKI_END;
	}

	//??��ﾘﾙｷ?�?�
	if( mStatus == DRILL ){
		mAniNoX   = 0;
		mStatus   = JUMP_DOWN;
	}
}

//反転??��?�?�(?�ｲ??��)
void Jiki::AoCheck()
{
	//HANTEN_TIME以�?��反転
	if( mAoTimer <= HANTEN_TIME && mAoTimer > 0.0f && mStatus == WALK ){
		Hanten();
	}
	else{
		mAoTimer = 0;
	}

	//浮�?
	if( mStatus == FUYU ){
		mAniNoX   = 0;
		mStatus   = JUMP_DOWN;
	}

}

//停止状態から歩き状態に戻�??�ｲ??��)
void	Jiki::UnTeishi()
{
	if( mStatus == TEISHI && mFadeFl != 1 ){
		mStatus = WALK;
	}


}

//?�?�ｬ?�ﾌﾟから着地動作へ(?�ｲ??�?
void	Jiki::MidCheck()
{
	if( mStatus == JUMP_UP ){
		mMidTimer = 0;
		mSpY	  = 0;
	}
}


/*
	?�ﾛｲ?��?向き( + or - )
*/
int		Jiki::GetMukiMult()
{
	if( mMuki == 0 )	return	-1;

	else
		return	1;
}

/*
	?�ｯ?�ﾟとの当たり判�?
*/
void	Jiki::MapAtHt()
{
	GAMECONTROL->GetStageManager()->GetCurMap()->SuperAtariHantei(
		mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, sHitX[0], sHitY[0], HERSIZE, HERSIZE, mHitFl, mKabeIchi);

	//当たり判定�?対�?-------------------------------
	if( (mHitFl[0] == SP->CHIP_AMHIT && mSpY >= 0) || mHitFl[0] == SP->CHIP_KGHIT || mCurAshiba ){//�?
		if(!mCurAshiba && mHitFl[0] != SP->CHIP_KGHIT) mY = (float)mKabeIchi[0] - sHitY[0][0][0];
		mSpY = 0;
		mAccY = 0;
		if( mStatus != JUMP_START ) mDrillFl = 0;
		mMidFl	= false;
		mHozonY = mY+HERSIZE;
		switch( mStatus ){
			case JUMP_DOWN ://?�?�ｬ?�ﾌ�?
				mStatus = JUMP_END;
				mAniNoX = 0;
				break;

			case DRILL ://??��ﾘ�?
			case DRILL_START:
				mStatus = DRILL_END;
				mAniNoX = 0;
				break;

			case FUYU://浮�?
				mStatus = TEISHI;
				mAniNoX = 0;
				mAoTimer = 0;
				break;

			case DAMAGE://??��ﾒｰ?�??
				if( mDgMapFl ){
					mStatus = DAMAGE_END;
					mAniNoX = 0;
				}
				break;

		}

	} else {
		//�?���?��以外�?常に重力
		if( mStatus != HISATU )	mAccY = SP->GRAVITY;
		//下�?当たり判定なし�?落�?
		if( mStatus == WALK ){
			mStatus = JUMP_DOWN;
			mAniNoX = 0;
		}
	}	

	if( mHitFl[1] == SP->CHIP_HIT || mHitFl[1] == SP->CHIP_KGHIT ){  //�?
		switch( mStatus ){
			case JUMP_UP :
			case DRILL:
			case DRILL_END:
			case DRILL_START:
				if( mSpY < 0 ){
					mSpY = 0;
					mY = mKabeIchi[1] - sHitY[0][1][0];
				}
				break;
		}
	}
	else if( mHitFl[1] == SP->CHIP_GMNGAIDN && mStatus!=DEAD && mStatus!=FADEOUT && mStatus!=FADEIN && mStatus!=DAMAGE_END) {
		Die();
	}

	if( mHitFl[2] == SP->CHIP_HIT || mHitFl[2] == SP->CHIP_GMNGAIRT 
		|| mHitFl[2] == SP->CHIP_GMNGAILT || mHitFl[2] == SP->CHIP_KGHIT){//�?
		switch( mStatus ){
			case JUMP_UP :
			case JUMP_DOWN ://?�?�ｬ?�ﾌﾟ中
			case FUYU :
					mSpX = 0;
					mAccX = 0;
				break;

			case DRILL_START :
			case DRILL ://??��ﾘﾙ中
				mDrillFl = 0;
				mSpX = 0;
				mAccX = 0;
				if( mHitFl[2] == SP->CHIP_GMNGAIRT )
					mX = mKabeIchi[2] - sHitX[0][2][0];
				if( mHitFl[2] == SP->CHIP_GMNGAILT )
					mX = mKabeIchi[2] - (HERSIZE - sHitX[0][2][0]);
				break;


			//case DAMAGE ://??��ﾒｰ?�??
			//	if( mDgMapFl ){
			//		Hanten();
			//	}
			//	break;

			case WALK :
			case KOGEKI:
			case KOGEKI_END:
			case KOGEKI_START:
					Hanten();
				break;
		}
	}	

	if( mHitFl[3] == SP->CHIP_HIT || mHitFl[3] == SP->CHIP_GMNGAIRT || 
		mHitFl[3] == SP->CHIP_GMNGAILT|| mHitFl[3] == SP->CHIP_KGHIT) {//�?
		switch( mStatus ){
			case DAMAGE://??��ﾒｰ?�??
			if( mDgMapFl ){
				mSpX = 0;
				mAccX = 0;
				mAniTimer = 0;
			}
			break;
		}
	}


	//攻�?��定�??�ｯ?��???��ﾒｰ?�??
	for( int i=0; i < 4; i++ ){
		if( mHitFl[i] == SP->CHIP_KGHIT && mStatus != HISATU ){
			InflictDamage();
		}
	}


}

//反転動作に入�?
void	Jiki::Hanten()
{
	if( mStatus != HANTEN && mStatus != HISATU && mStatus != DAMAGE && mStatus != DAMAGE_END && 
		mStatus != FADEOUT && mStatus != FADEIN && mStatus != DEAD && mSuperStatus == CONTROL ){
		mAoTimer = 0;
		mAniNoX  = 0;
		mStatus  = HANTEN;
	}
}

// 歩き中の場合反転します�?�?��中の場合�?Xを軸にして跳ね返ります�?
void	Jiki::HantenOrRebound()
{
	switch( mStatus ){
		case WALK:
		case KOGEKI:
		case KOGEKI_END:
		case KOGEKI_START:
			Hanten();
			break;

		case JUMP_DOWN:
		case JUMP_START:
		case JUMP_UP:
		case JUMP_END:
		case DRILL_START:
		case DRILL:
		case DRILL_END:
		case FUYU:
			mMuki *= -1;
			break;
	}
}


/*
	敵との当たり判定用?�ﾚｰ??
*/
void	Jiki::collisionFrames(){

	if( !collisionEnabled ) return;

	//当たり判定�??�ﾚｰ??
	switch(mStatus){

		case WALK:
		case DAMAGE:
		case KOGEKI_END:
		case KOGEKI_STAN:
		case DRILL_END:
			SetCurFrame(FR_ARUKI);
			break;

		case TEISHI:
		case HANTEN:
			SetCurFrame(FR_TACHI);
			break;

		case KOGEKI:
			SetCurFrame(FR_KOGEKI);
			break;

		case JUMP_UP:
		case JUMP_DOWN:
		case JUMP_START:
		case JUMP_END:
		case FUYU:
			SetCurFrame(FR_JUMP);
			break;

		case DRILL:
		case DRILL_START:
			SetCurFrame(FR_DRILL);
			break;

		case HISATU :
			if( mHisatuTime > HISATU_TIME ) SetCurFrame(FR_DISABLE);
			else SetCurFrame(FR_HISATU);
		default:
			break;

	}//switch

	/*char buffer[6];
	sprintf(buffer,"%d",pCollision->GetIndex());
	SHOW(0, 0, buffer);*/
}

void Jiki::CollisionResponse(ICollidable* rCollObject, int rThisGroupId, int rOpGroupId)
{

}
/*
	?�ｲ??��の??��ｼ?�?�増�?
*/
void	Jiki::Tension()
{

	mTenTime += SP->FrameTime;

	//�?���?��?�?�ｮ?�?�ｮに??��ｼ?�?�が下がって�?��
	if( mStatus == HISATU ){
		mTenTime = 0;
		mTen -= ( TEN_MAX/HISATU_TIME ) *SP->FrameTime/2;
	}else{
	//??��ｼ?�?��?
		if(	mTenFl ) {
			if( mTenTime > TEN_UTIME ){
				mTenTime = 0;
				RestoreTension(TEN_UP1, false);
			}
		}else{
		//??��ｼ?�?��?
			if( mTenTime > TEN_DTIME ){
				mTenTime = 0;
				mTen -= TEN_DOWN1;
			}
		}
	}
}

/*
	?�ｪ?�??���?�?
*/
void	Jiki::Fade()
{

	//�?���?��始ﾌｪ?�??�?
	if( mFadeFl == 1 ){
		mChargeFx = new ChargeEffect(mX+HERSIZE/2, mY+HERSIZE/2);
		SetSuperPause();
		GAMECONTROL->GetMobManager()->Request(mChargeFx, false);
		mFadeFl = 2;
	}
	else if( mFadeFl == 2 && mChargeFx->IsChargeCompleted() ){
		mStatus = HISATU;
		SetSuperControl();
		mAniNoX = 0;
		mHisatuTime = 0;
		mHisatuMuki = GAMECONTROL->GetDXController()->GetMouseState().lX;
		GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOn();
		mFadeFl = 0;
		//BGM
		GAMECONTROL->GetSoundController()->SetBGM(SoundController::HISATU);
	}

	//�?���?���?��ｪ?�??�?
	if( mFadeFl2  && GAMECONTROL->GetFader()->FadeIn() ){
		mFadeFl2 = false;
		GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOn();
		GAMECONTROL->GetFader()->SetSpeed( GF("FADE_INCR") );
		//BGM
		GAMECONTROL->GetMobManager()->Remove(mChargeFx);
		mChargeFx = NULL;
	}

	if( mChargeFx ) mChargeFx->SetPos(mX + HERSIZE/2, mY + HERSIZE/2);

}
/*
	?�?�ｰ?�ｵ?�?�ﾞｰ
*/
void	Jiki::Gameover()
{

	if( mGmOvFl == 2 ){
		if( GAMECONTROL->GetMaku()->IsClosed()){
			mGmOvFl = 3;
			GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();
			//BGM
			GAMECONTROL->GetSoundController()->PauseBGM();
		}
		GAMECONTROL->GetMaku()->Close();
	}
	if( mGmOvFl == 3 && GAMECONTROL->GetFader()->FadeOut() ){
		mGmOvFl = 0;
		GAMECONTROL->GetEventManager()->Request(new GameOverEvt());
	}

}
/*
	?�ﾛｲ?�を歩き状態に戻�?
*/
void	Jiki::HrWalk()
{
	if( mStatus == HISATU ){
		mHisatuTime = HISATU_TIME + 10;
	}


}

/*
	残機�??減る�?の場合�?ゲー�?��ーバ�?
*/
void	Jiki::Die()
{
	ResetTempParams();
	mChainIdx = 0;

	mStatus = DEAD;
	mSpX = 0.0f;
	mAccX = 0.0f;

	DisableCollision();
	SetLightResponse(false);
	SetTransparent(true);
	GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();
}

/*
	半�?明にしま�?
*/
void Jiki::SetTransparent(bool mOnOff)
{
	mAlphaVal = mOnOff ? GF("HER_TRSP_A") : 1.0f;
}

/**
	\return 死ぬところ�?
*/
bool Jiki::IsDying()
{
	return (mStatus==DEAD || mStatus==MAKUDOWN || mStatus==FADEOUT || mStatus==FADEIN || (mStatus == DAMAGE_END && mGmOvFl));
}
/*
	\return 操作モードか
*/
bool Jiki::IsControl()
{
	return (mSuperStatus == CONTROL);
}

/*
	チェイン�?個増や�?
*/
void Jiki::IncrementChain()
{
	if( mChainIdx < MAX_CHAIN )
		mChainIdx++;

	// 打撃?�?�ｪ?�??��出しま�?
	MakeHitEffect();
}

/*
	チェイン�?に戻�?
*/
void Jiki::ResetChain()
{
	mChainIdx=0;
}

/*
	チェインレベルを返す
*/
int Jiki::GetChainLv()
{
	return mChainIdx;
}

/*
	時期の足�?��打撃?�?�ｪ?�??��出�?
*/
void Jiki::MakeHitEffect(){
	
	// 出現座標�?計�?
	int efx, efy;

	switch( mStatus ){

	case KOGEKI:
		efx = GetMuki() ? GetX() + 120 : efx = GetX();
		efy = GetY() + 70;
		break;
		
	case DRILL:
	case DRILL_START:
	case DRILL_END:
		efx = GetMuki() ? GetX() + 120 : efx = GetX();
		efy = GetY() + 120;
		break;

	default:
		return;
	}

	// ?�ｸ?�?�??
	GAMECONTROL->GetMobManager()->Request( new HitEffect( efx, efy ), true );

}

/*
* \return ?�ﾛｲ?�が何か特別なことをやって�?��状態であり、普段の処�?��例外して�?���?
*/
bool Jiki::IsBusy()
{
	return mHisatuTime > HISATU_TIME;
}

/*
	?�ｲ?�UP
*/
void Jiki::RestoreEmpacy(int n, bool SEdelayed)
{ 
	if( mEmp < EMP_MAX ) {
		mEmp += n;
		//SE
		if( SEdelayed )
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_enpacy_up_delayed.wav");
		else
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_enpacy_up.wav");
	}

	if( mEmp > EMP_MAX ) mEmp = EMP_MAX; 

}

/*
	??��ｼ?�?�UP
*/
void Jiki::RestoreTension(int n, bool SEdelayed) 
{ 
	bool fl = false;

	if( mTen < TEN_MAX ) {
		mTen += n;
		fl = true;
		//SE
		if( SEdelayed )
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_tensyon_up_delayed.wav");
		else
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_tensyon_up.wav");
	}

	if( mTen >= TEN_MAX && fl )//SE
		if( SEdelayed )
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_tensyon_maxn.wav");
		else
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_tensyon_maxn_delayed.wav");

	if( mTen > TEN_MAX ) mTen = TEN_MAX;
}

/*
	残機UP
*/
void Jiki::RestoreLife(int n, bool SEdelayed) 
{ 
	if( mLife < LIFE_MAX ) {
		mLife += n;
		//SE[
		if( SEdelayed )
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_zanki_up_delayed.wav");
		else
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_zanki_up.wav");
	}
	if( mLife > LIFE_MAX ) mLife = LIFE_MAX; 
}
