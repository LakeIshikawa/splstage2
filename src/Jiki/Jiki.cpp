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

//?±??¾’ï½°?¼?®?ï¾?¾ï½°??
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

//?Œï¾šï½°?‘ã”ã¨ã®?±??¾’ï½°?¼?®?è£œé–“æ™‚é–“
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

//?¸?ï¾—ï¾Œï½¨?¯?¸
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

//å½“ãŸã‚Šåˆ¤å®šï¾?¾ï½°??
int	Jiki::sHitX[][4][TENSU] = {
	{
		{ 40, 57, 89,-1}, 		//ä¸?
		{ 62, -1},				//ä¸?
		{ 90, 90, 90, 90, 90,-1}, 		//å‰?
		{ 31, 19, -1}, 			//å¾?
	}


};
int	Jiki::sHitY[][4][TENSU] = {
	{
		{118,118,118,-1 }, 		//ä¸?
		{ 0, -1},				//ä¸?
		{117, 95, 65, 40, 25, -1}, 		//å‰?
		{115, 11, -1}, 			//å¾?
	}

};

// ãƒã‚§ã‚¤ãƒ³
float Jiki::sChainMultSp[] = {
	1.2f, 1.3f, 1.6f, 1.9f, 2.2f, 2.4f
};
// ãƒã‚§ã‚¤ãƒ³
float Jiki::sChainMultShoSp[] = {
	1.0f, 1.03f, 1.06f, 1.09f, 1.12f, 1.15f
};

Jiki::Jiki(int rXPx, int rYPy)
{

	// è¨­å®šå®šæ•°
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

	//??¾ï¾’ï½°?¼??
	ResetTempParams();

	//?¹?ï½°?¼?é¡?
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

	// å½“ãŸã‚Šåˆ¤å®?
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
	//?±??¾’ï½°?¼?®??
	mAniTimer	= 0;
	mAniNoX		= 0;
	mAniNoY		= 0;

	//?½??½°??½½
	//SetSuperWait(3.0f);
	mStatus		= WALK;
	mMuki		= 1;	

	//?¹?ï½°?‘ï½µ?°?Šï¾ï½°
	mGmOvFl	 = 0;

	// ãƒ?ƒ¡ãƒ¼ã‚¸
	mDgMutekiFl	 = 0;
	mDgMapFl	 = false;
	mDamageTimer = 0;
	//mTenmetuTimer = 0;
	mAlphaVal = 1.0f;
	mAlphaTimer = 0.0f;

	//?—ï½²??
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

	//?Œï½ª?°??¾?
	mFadeFl = 0;
	mFadeFl2 = false;

	//è¶³å ´
	mAshibaFl = false;
	mCurAshiba = NULL;
	mAshiSpX = 0;

	//å¼·é¢¨
	mKazeAccX = 0;

	// ??½¬?°?¼?ï½´?Œï½ª?¸??
	mChargeFx = NULL;
}

Jiki::~Jiki(void) 
{
	delete mInterface;
}

// ?º?˜ï½¼?ï½®?ç”¨ã€è?æ©Ÿã??»?²?½?ã‚’è¿”ã™
int Jiki::GetSizeX()
{
	return HERSIZE;
}

/*
	åŸºæœ¬?¸?—ï½½ã®??½½?¸ã‚’ã?ã£ãã‚Šè¡Œã„ã¾ã?
*/
void Jiki::RunTask()
{
	Collidable::RunTask();
	LightResponseAble::RunTask();
}

/*
	?‹ï¾›ï½²?ã«??¾ï¾’ï½°?¼?ã‚’ä¸ãˆã‚?
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
			// è¶³å ´ã‹ã‚‰é™ã‚Šã‚?
			if( mCurAshiba ) {
				mCurAshiba->GetOff(this);
				mCurAshiba = NULL;
			}
			mDmSETimer = 0;
			SetTransparent(true);

			//?´?ï¾Šï¾Ÿï½¼?°
			mEmp -= EMP_DOWN;
			if( mEmp <= 0 ){
				Die();
			}
			if( mEmp > EMP_MAX ) mEmp = EMP_MAX;

			//??¾ï½¼?®??
			mTen -= TEN_DOWN2;
			if( mTen < 0 ) mTen = 0;
			if( mTen > TEN_MAX ) mTen = TEN_MAX;

			ResetChain();
		}
	}
}
/*
	?‹ï¾›ï½²?ã???¾ï½¼?®?or??¾ï¾Šï¾Ÿï½¼?°ã‚’ä¸Šã’ã‚?
*/
void Jiki::IncreaseTensEmpa()
{	

		//??¾ï½¼?®??
		if( mStatus == KOGEKI || mStatus == KOGEKI_START || mStatus == KOGEKI_END
			|| mStatus == DRILL || mStatus == DRILL_START ){
			RestoreTension(TEN_UP2, false);
		}
		//?´?ï¾Šï¾Ÿï½¼?°
		if( mStatus == HISATU ){
			mEmpTeki++;
			if( mEmpTeki == EMP_UP ){
				mEmpTeki = 0;
				RestoreEmpacy(1, false);
			}
		}

}
/*
	ã™ã¹ã¦ã®å½“ãŸã‚Šåˆ¤å®šã‚’ã‚ªãƒ•ã«ã™ã‚‹
*/
void Jiki::DisableCollision()
{
	collisionEnabled = false;
	SetCurFrame( FR_DISABLE );
}

/*
	ã™ã¹ã¦ã®å½“ãŸã‚Šåˆ¤å®šã‚’ã‚ªãƒ³ã«ã™ã‚‹
*/
void Jiki::EnableCollision()
{
	collisionEnabled = true;
}

/*
	ãƒ’ãƒ­ã‚¤ãƒ³ã‚’æ¼”å?ãƒ¢ãƒ¼ãƒ‰ã«ã™ã‚‹ (åœæ­¢)
*/
void Jiki::SetSuperWait(float rTime)
{
	SetLightResponse(false);
	DisableCollision();
	mSuperStatus = WAIT;

	mSuperWaitTimer = rTime;
}

/*
	ãƒ’ãƒ­ã‚¤ãƒ³ã‚’æ“ä½œãƒ¢ãƒ¼ãƒ‰ã«ã™ã‚‹ (æ™®é€?
*/
void Jiki::SetSuperControl()
{
	SetLightResponse(true);
	EnableCollision();
	mSuperStatus = CONTROL;
}

/*
	ãƒ’ãƒ­ã‚¤ãƒ³ã‚’ã„ã£ãŸã‚“æ­¢ã‚ã‚‹
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

	//?ï½¯?Œï¾Ÿã¨ã®å½“ãŸã‚Šåˆ¤å®?
	MapAtHt();
	
	//?±??¾’ï½°?¼?®??
	int	no;
	bool dosa_end = false;

	mAniNoY = mStatus;

	// ãƒã‚§ã‚¤ãƒ³ã«åæ˜ ã•ã›ã‚?æ­©ãã¨æ”»æ’??ã¿)
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

	//?´?Œï½ª?¸????±??¾’ï½°?¼?®??
	if( mStatus == KOGEKI_STAN && mAniNoX > 2 ){
		WAIT_TIMER(mStanTimer, STAN_ANI)
			mStanTimer = 0;
			mStanAni++;
			if( mStanAni > 4 )	mStanAni = 0;
		WAIT_END
	}

	// ã‚¹ãƒ¼ãƒ‘ã?ã‚¹ãƒ??ã‚¿ã‚¹
	switch( mSuperStatus ){
		case WAIT:
			{
				mStatus = TEISHI;
				mSpX = 0;
				mAccX = 0;

				// ã‚¿ã‚¤ãƒã?
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
				//?½??½°??½½
				switch( mStatus ){

					//æ­©ã?
					case WALK :
						mSpX = SPWALK*sChainMultSp[mChainIdx] * GetMukiMult();
						break;


						//æ”»æ’??—ï½²??µ¤)
					case KOGEKI_START :
						mSpX = SPWALK*sChainMultSp[mChainIdx] * GetMukiMult();
						mAccX = 0;
						//é–‹å§‹ï½±??¾’ï½°?¼?®?ãŒçµ‚ã‚ã£ãŸã‚‰æ”»æ’?¸
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
						//?±??¾’ï½°?¼?®??+ã‚’åœæ­¢
						if( mAniNoX == 4 ) mAniTeishi = true;
						//æ­©ãã«æˆ»ã?
						if( mAkaTimer2 >= STAN_TIME ){
							mStatus = WALK;
						}
						break;


						//åœæ­¢ãƒ»åè»¢(?—ï½²??’)
					case TEISHI :
						mSpX = 0;
						mAccX = 0;
						break;

					case HANTEN :
						mSpX = 0;
						mAccX = 0;
						//åè»¢?±??¾’ï½°?¼?®?ãŒçµ‚ã‚ã£ãŸã‚‰å‘ãã‚’å¤‰ãˆã¦æ­©ãã¸
						if( dosa_end ){
							mMuki = !mMuki;
							mStatus = WALK;
						}
						break;


						//?¼?ï½¬?ï¾Œï¾??—ï½²??·?
					case JUMP_START :
						// è¶³å ´ã«ä¹—ã£ã¦ã?‚‹å ´åˆã?ã€ã¾ãšé™ã‚Šã‚‹
						if(mCurAshiba) mCurAshiba->GetOff(this);
						mCurAshiba = NULL;

						mSpX = 0;
						mAccX = 0;
						//é–‹å§‹ï½±??¾’ï½°?¼?®?ãŒçµ‚ã‚ã£ãŸã‚‰?¼?ï½¬?ï¾Œï¾Ÿã¸
						if( dosa_end ){
							mSpY = JUMP_SHOSP*sChainMultShoSp[mChainIdx];
							mStatus = JUMP_UP;
						}
						break;

					case JUMP_UP :
						//å‰ãŒå½“ãŸã£ã¦ãªã?™‚ã®X
						if( mHitFl[2] == SP->CHIP_NOHIT )
							mSpX = SPWALK * sChainMultSp[mChainIdx] * GetMukiMult();
						//?±??¾’ï½°?¼?®??+ã‚’åœæ­¢
						if( mAniNoX == 2 ) mAniTeishi = true;
						//é ‚ç‚¹ã«é”ã—ãŸã‚‰è½ä¸‹ã¸
						if( mSpY >= 0 ){
							mStatus = JUMP_DOWN;
							mAniNoX = 0;
						}
						break;

					case JUMP_DOWN :
						//å‰ãŒå½“ãŸã£ã¦ãªã?™‚ã®X
						if( mHitFl[2] == SP->CHIP_NOHIT ){
							mSpX = SPWALK * GetMukiMult();
						}
						//?±??¾’ï½°?¼?®??+ã‚’åœæ­¢
						if( mAniNoX == 2 ) mAniTeishi = true;
						break;


						//??¾ï¾˜ï¾™ï½·?¯?¸
					case DRILL_START :
						if( mDrillFl == 2 ){
							mSpX = DRILL_SP * GetMukiMult();
							mSpY = DRILL_SP;
						}
						//é–‹å§‹ï½±??¾’ï½°?¼?®?ãŒçµ‚ã‚ã£ãŸã‚‰??¾ï¾˜ï¾™ï½·?¯?¸ã¸
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


						//æµ®é?
					case FUYU :
						mSpX = 0;
						mAccX = 0;
						mAccY = 0;
						mSpY = FUYU_SP;
						break;


						//??¾ï¾’ï½°?¼??
					case DAMAGE :
						mDgMapFl = true;
						//å¾ŒãŒå½“ãŸã£ã¦ãªã?™‚ã®X
						if( mHitFl[3] != SP->CHIP_HIT && mHitFl[3] != SP->CHIP_GMNGAIRT && 
							mHitFl[3] != SP->CHIP_GMNGAILT && mHitFl[3] != SP->CHIP_KGHIT )
							mSpX = SPWALK * -GetMukiMult();
						if( mAniNoX == 1 ){
							mAniTeishi = true;
							// SE
							if( !mDmSE ){//?´?ï¾Šï¾Ÿï½¼?°ãŒæ¸›ã‚‹
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
						//çµ‚äº?½±??¾’ï½°?¼?®?ãŒçµ‚ã‚ã£ãŸã‚‰æ­©ãã¸
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


						//çµ‚äº?‹•ä½?
					case KOGEKI_END :
					/*	mSpX = SPWALK*sChainMultSp[mChainIdx] * GetMukiMult();
						mAccX = 0;
						if( dosa_end ){
							mStatus = WALK;
						}
						break;*/

					case JUMP_END :
					case DRILL_END :
						//æ­©ãã«æˆ»ã?
						mSpX = 0;
						mAccX = 0;
						if( dosa_end ){
							mStatus = WALK;
						}
						break;


						//å¿?®ºæŠ?
					case HISATU :
						{
						mHisatuTime += SP->FrameTime;

						//?—ï½²???é€Ÿåº¦æ¸›å°?
						CONTROLLIGHT->SetSpX( GAMECONTROL->GetDXController()->GetMouseState().lX / HISATU_LTSP );
						CONTROLLIGHT->SetSpY( GAMECONTROL->GetDXController()->GetMouseState().lY / HISATU_LTSP );

						//?½?¸?›ï½°?™ã‚’?—ï½²??¨çµ±ä¸?
						int scpx = GAMECONTROL->GetStageManager()->GetCurScrollPointer();

						mHsX = CONTROLLIGHT->GetX() - HERSIZE/2;
						mHsY = CONTROLLIGHT->GetY() - HERSIZE/2;

						//?‹ï¾›ï½²?ã?ç§»å‹?
						float sax = mHsX - (mX- scpx);
						float say = mHsY - mY;

						if( mHsX > mX - scpx && sax > HISATU_HRSP ) mSpX = sax/HISATU_HRSP;
						if( mHsX < mX - scpx && sax < HISATU_HRSP ) mSpX = sax/HISATU_HRSP;
						if( mHsX == mX - scpx ) { mSpX = 0; mAccX = 0; }

						if( mHsY > mY && say > HISATU_HRSP ) mSpY = say/HISATU_HRSP;
						if( mHsY < mY && say < HISATU_HRSP ) mSpY = say/HISATU_HRSP;
						if( mHsY == mY ) mSpY = 0;

						// é€Ÿåº¦é™ç•Œ
						if( mSpX > GF("HISATSU_MAXSP") ) mSpX = GF("HISATSU_MAXSP");
						if( mSpX < -GF("HISATSU_MAXSP") ) mSpX = -GF("HISATSU_MAXSP");
						if( mSpY > GF("HISATSU_MAXSP") ) mSpY = GF("HISATSU_MAXSP");
						if( mSpY < -GF("HISATSU_MAXSP") ) mSpY = -GF("HISATSU_MAXSP");

						//?‹ï¾›ï½²?ã?å‘ã
						if( mSpX < 0 ){
							mMuki = 0;//â†?
						}
						if( mSpX >= 0 ){
							mMuki = 1;//â†?
						}

						//å½“ãŸã‚Šåˆ¤å®šâ?
						GAMECONTROL->GetStageManager()->GetCurMap()->SuperAtariHantei(
						mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, sHitX[0], sHitY[0], HERSIZE, HERSIZE, mHitFl, mKabeIchi);
						if( mHitFl[2] == SP->CHIP_HIT || mHitFl[2] == SP->CHIP_GMNGAIRT || 
							mHitFl[2] == SP->CHIP_GMNGAILT || mHitFl[2] == SP->CHIP_KGHIT){
								if( mSpX * -GetMukiMult() < 0 ) {
									mSpX = 0;//å‰?
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
							if( mSpY > 0 ) mSpY = 0;//ä¸?
						}
						if( mHitFl[1] == SP->CHIP_HIT || mHitFl[1] == SP->CHIP_KGHIT ){
							if( mSpY < 0 ) {
								mSpY = 0;//ä¸?
								mAccY = 0;
								mY = mKabeIchi[1] - sHitY[0][1][0];
							}
						}


						//æ™‚é–“ãŒããŸã‚‰çµ‚äº?
						if( mHisatuTime > HISATU_TIME ){
							GAMECONTROL->GetFader()->SetSpeed( 0.03 );
							GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();
							if( !mHisatuSE ){//SE
								GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_hiroin_hissatu_end.wav");
								GAMECONTROL->GetSoundController()->SetBGM(GAMECONTROL->GetStageManager()->GetCurrentStage()->GetBGM());
								mHisatuSE = true;
							}
							//å¿?®ºæŠ?µ‚äº?¾Œï½ª?°??¾?
							if( !mFadeFl2  && GAMECONTROL->GetFader()->FadeOut() ){
								mHisatuTime = 0;
								mStatus = JUMP_DOWN;
								mAniNoX = 0;
								mX += mSpX;
								mSpX = SPWALK * -GetMukiMult();
								mTen	 =	0;
								mEmpTeki = 0;
								//?—ï½²???é€Ÿåº¦æˆ»ã?
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

							// ?‹ï¾›ï½²?ã?ä½ç½®ã‚’ãƒã‚§ãƒ?‚¯ãƒã‚¤ãƒ³ãƒˆã«èª¿æ•´
							int restorePointX = curStage->GetCheckpointController()->GetStartPointX(mX + HERSIZE/2);
							int restorePointY = curStage->GetCheckpointController()->GetStartPointY(mX + HERSIZE/2);
							GAMECONTROL->GetStageManager()->GetCurMap()->SetScrollP( restorePointX - GI("SCRSZX")/2);
							mY = restorePointY - HERSIZE;
							mX = restorePointX - HERSIZE/2;

							// é€æ?ã«ã™ã‚‹
							SetTransparent(true);

							// å½“ãŸã‚Šåˆ¤å®šã‚’æœ‰åŠ¹ã«æˆ»ã?
							EnableCollision();

							// ?—ï½²??“ä½œã‚’æˆ»ã?
							SetLightResponse(true);

							// ãƒ?ƒ³ã‚·ãƒ§ãƒ³ã¨ã‚¨ãƒ³ãƒ‘ã‚·ãƒ¼ã‚’ãƒªã‚»ãƒ?ƒˆ
							ResetEmpacy();
							ResetTension();

							// ç¾åœ¨å‡ºã¦ã‚‹ã‚‚ã®ã‚’å?éƒ¨æ¶ˆã™
							GAMECONTROL->GetEventManager()->Request(new ResetMobEvt());

							// æ•µã‚’å¾©æ´»åœ°ã«å¾“ã£ã¦å¾©æ´»ã•ã›ã‚?
							GAMECONTROL->GetEventManager()->Request(new RestoreTekiAfterCheckpoint( mX + HERSIZE/2 ));

							//åˆ¶é™æ™‚é–“ï¾˜ï½¾?¯??
							GAMECONTROL->GetStageManager()->GetCurrentStage()->GetSeigenJikan()->SeigenJikanReset();
						}
						break;

					case FADEIN:
						if( GAMECONTROL->GetFader()->FadeIn() ){
							mStatus = WALK;

							// ç„¡æ•µã«ã™ã‚‹
							mDgMutekiFl = 2;
							mDgMapFl   = false;

							GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOn();
							GAMECONTROL->GetSoundController()->SetBGM(GAMECONTROL->GetStageManager()->GetCurrentStage()->GetBGM());
						}
				}
		break;
		}
	}

	//?Œï½ª?°??¾?
	Fade();

	//SE?™ï½°?Œï¾Ÿçµ‚äº?
	if( mStatus != KOGEKI )
		GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_hiroin_tijoukougeki.wav");
	if( mStatus != DRILL && mStatus != DRILL_START )
		GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_hiroin_kuutyuukougeki.wav");

	//??¾ï¾’ï½°?¼??
	if( mDgMutekiFl == 2 ){
		mDamageTimer += SP->FrameTime;
		//mTenmetuTimer += SP->FrameTime;
		//ç„¡æ•µæ™‚é–“
		if( mDamageTimer > MUTEKI_TIME ){
			mDamageTimer = 0;
			//mTenmetuTimer =0;
			mDgMutekiFl = 0;
			SetTransparent(false);
		}
	}


	//ç§»å‹?
	if( (mStatus != HISATU && mStatus != TEISHI) || mSuperStatus != CONTROL)
		mSpY += mAccY;//å¸¸ã«é‡åŠ›ãŒä»£å…¥ã•ã‚Œã¦ã?‚‹
	
	if( !(mHitFl[2]==SP->CHIP_GMNGAILT || mHitFl[2]==SP->CHIP_GMNGAIRT|| mHitFl[2]==SP->CHIP_HIT ||
		mHitFl[3]==SP->CHIP_GMNGAILT || mHitFl[3]==SP->CHIP_GMNGAIRT || mHitFl[3]==SP->CHIP_HIT )) 
		mSpX += mAccX+mKazeAccX;

		mX += mSpX + mAshiSpX;
		mY += mSpY;

		//// è¶³å ´
		mAshiSpX = 0;
		if( mStatus == HISATU && mCurAshiba ){
			mCurAshiba->GetOff(this);
			mCurAshiba = NULL;
		}
		//if( mCurAshiba && !(mHitFl[2]==SP->CHIP_GMNGAILT || mHitFl[2]==SP->CHIP_GMNGAIRT|| mHitFl[2]==SP->CHIP_HIT ||
		//mHitFl[3]==SP->CHIP_GMNGAILT || mHitFl[3]==SP->CHIP_GMNGAIRT || mHitFl[3]==SP->CHIP_HIT )){
		//	mX += mCurAshiba->GetSpX();
		//}

	//?±??¾’ï½°?¼?®?noæ›´æ–°
	mAniNoY = mStatus;
	no = sAniData[mAniNoY][mAniNoX];


	//æç”»(ç‚¹æ»?
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

	//SE(??¾ï½¼?®??
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
	?—ï½²??¨ã®å½“ãŸã‚Šåˆ¤å®?
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
	?—ï½²???å‡¦ç?
*/
void Jiki::ResponseAka()//---------------------?—ï½²??µ¤
{

	UnTeishi();//æ­©ãå?é–?
	AoCheck();//åè»¢

	Hisatu();//å¿?®ºæŠ?

	//æ”»æ’?
	if( mStatus == WALK ){
		mStatus = KOGEKI_START;
		mSpX	= 0;
		mAniNoX = 0;
		mAkaTimer = 0;
	}

	mAkaTimer += SP->FrameTime;

	//å¼·åˆ¶çµ‚äº?
	if( mAkaTimer > END_TIME && mStatus == KOGEKI ){
		mAkaTimer = 0;
		mAkaTimer2 = 0;
		mStanTimer = 0;
		mStatus	  = KOGEKI_STAN;
		mAniNoX = 0;
	}


	//??¾ï¾˜ï¾™ï½·?¯?¸
	if( mDrillFl == 1 ){//?‘å›ã®?¼?ï½¬?ï¾Œï¾Ÿã«ä¸?º¦ã—ã‹ä½¿ãˆã¾ã›ã‚“
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
	MidCheck();//?¼?ï½¬?ï¾Œï¾?

	//??¾ï½¼?®??
	if( !mTenFl ){
		mTenFl = !mTenFl;
		mTenTime = 0;
	}
	Tension();

}

void Jiki::ResponseAo()//----------------------?—ï½²??’
{

	AkaCheck();//æ”»æ’?
	MidCheck();//?¼?ï½¬?ï¾Œï¾?

	Hisatu();//å¿?®ºæŠ?

	//åœæ­¢
	if( mStatus == WALK ){
		mStatus = TEISHI;
		mAniNoX = 0;
		mAoTimer = 0;
	}

	mAoTimer += SP->FrameTime;

	//æµ®é?
	if( mStatus == JUMP_DOWN ){
		mStatus = FUYU;
		mAniNoX = 0;
		mMidFl	= false;
	}

	//??¾ï¾˜ï¾™ï½·?¯?¸ã¯?‘å›ã®?¼?ï½¬?ï¾Œï¾Ÿã«ä¸?º¦ã—ã‹ä½¿ãˆã¾ã›ã‚“
	if( mDrillFl == 1 )
		mDrillFl  = 0;

	//??¾ï½¼?®??
	if( !mTenFl ){
		mTenFl = !mTenFl;
		mTenTime = 0;
	}
	Tension();

}

void Jiki::ResponseMidori()//------------------?—ï½²??·?
{

	UnTeishi();//æ­©ãå?é–?
	AkaCheck();//æ”»æ’?
	AoCheck();//åè»¢

	Hisatu();//å¿?®ºæŠ?

	//?¼?ï½¬?ï¾Œï¾?
	if( mStatus == WALK ){
		mStatus = JUMP_START;
		mAniNoX = 0;
		mMidTimer = 0;
		//SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_hiroin_junp.wav");
		//?‘å›ã®?¼?ï½¬?ï¾Œï¾Ÿã«ä¸?º¦ã—ã‹ä½¿ãˆã¾ã›ã‚“
		if( mDrillFl == 0 )
			mDrillFl  = 1;
	}

	mMidTimer += SP->FrameTime;
	mMidFl	= true;

	
	//??¾ï½¼?®??
	if( !mTenFl ){
		mTenFl = !mTenFl;
		mTenTime = 0;
	}
	Tension();

}

void Jiki::ResponseMushoku()//-----------------?—ï½²??„¡è‰²
{

	UnTeishi();//æ­©ãå?é–?
	AkaCheck();//æ”»æ’?
	AoCheck();//åè»¢
	MidCheck();//?¼?ï½¬?ï¾Œï¾?

	Hisatu();//å¿?®ºæŠ?

	//??¾ï½¼?®??
	if( !mTenFl ){
		mTenFl = !mTenFl;
		mTenTime = 0;
	}
	Tension();

}

void Jiki::NoLight()//-------------------------?—ï½²??ªã?
{

	UnTeishi();//æ­©ãå?é–?
	AkaCheck();//æ”»æ’?
	AoCheck();//åè»¢
	MidCheck();//?¼?ï½¬?ï¾Œï¾?

	//??¾ï½¼?®??
	if( mTenFl ){
		mTenFl = !mTenFl;
		mTenTime = 0;
	}
	Tension();
}


/*
	?—ï½²???å‡¦ç?ãã?ä»?
*/

//å¿?®ºæŠ?
void	Jiki::Hisatu()
{

	//??¾ï½¼?®?MAX??½½?ï¾Ÿï½°?½æŠ¼ã—ã§å¿?®ºæŠ?
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

//æ”»æ’?Š¶æ…‹ã‹ã‚‰çµ‚äº?‹•ä½œã¸(?—ï½²??µ¤)
void Jiki::AkaCheck(){
	
	//æ”»æ’?
	if( mStatus == KOGEKI ){
		mAkaTimer = 0;
		mAniNoX   = 0;
		mStatus   = KOGEKI_END;
	}

	//??¾ï¾˜ï¾™ï½·?¯?¸
	if( mStatus == DRILL ){
		mAniNoX   = 0;
		mStatus   = JUMP_DOWN;
	}
}

//åè»¢??½ª?¯?¸(?—ï½²??’)
void Jiki::AoCheck()
{
	//HANTEN_TIMEä»¥å†?§åè»¢
	if( mAoTimer <= HANTEN_TIME && mAoTimer > 0.0f && mStatus == WALK ){
		Hanten();
	}
	else{
		mAoTimer = 0;
	}

	//æµ®é?
	if( mStatus == FUYU ){
		mAniNoX   = 0;
		mStatus   = JUMP_DOWN;
	}

}

//åœæ­¢çŠ¶æ…‹ã‹ã‚‰æ­©ãçŠ¶æ…‹ã«æˆ»ã??—ï½²??’)
void	Jiki::UnTeishi()
{
	if( mStatus == TEISHI && mFadeFl != 1 ){
		mStatus = WALK;
	}


}

//?¼?ï½¬?ï¾Œï¾Ÿã‹ã‚‰ç€åœ°å‹•ä½œã¸(?—ï½²??·?
void	Jiki::MidCheck()
{
	if( mStatus == JUMP_UP ){
		mMidTimer = 0;
		mSpY	  = 0;
	}
}


/*
	?‹ï¾›ï½²?ã?å‘ã( + or - )
*/
int		Jiki::GetMukiMult()
{
	if( mMuki == 0 )	return	-1;

	else
		return	1;
}

/*
	?ï½¯?Œï¾Ÿã¨ã®å½“ãŸã‚Šåˆ¤å®?
*/
void	Jiki::MapAtHt()
{
	GAMECONTROL->GetStageManager()->GetCurMap()->SuperAtariHantei(
		mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, sHitX[0], sHitY[0], HERSIZE, HERSIZE, mHitFl, mKabeIchi);

	//å½“ãŸã‚Šåˆ¤å®šã?å¯¾å¿?-------------------------------
	if( (mHitFl[0] == SP->CHIP_AMHIT && mSpY >= 0) || mHitFl[0] == SP->CHIP_KGHIT || mCurAshiba ){//ä¸?
		if(!mCurAshiba && mHitFl[0] != SP->CHIP_KGHIT) mY = (float)mKabeIchi[0] - sHitY[0][0][0];
		mSpY = 0;
		mAccY = 0;
		if( mStatus != JUMP_START ) mDrillFl = 0;
		mMidFl	= false;
		mHozonY = mY+HERSIZE;
		switch( mStatus ){
			case JUMP_DOWN ://?¼?ï½¬?ï¾Œï¾?
				mStatus = JUMP_END;
				mAniNoX = 0;
				break;

			case DRILL ://??¾ï¾˜ï¾?
			case DRILL_START:
				mStatus = DRILL_END;
				mAniNoX = 0;
				break;

			case FUYU://æµ®é?
				mStatus = TEISHI;
				mAniNoX = 0;
				mAoTimer = 0;
				break;

			case DAMAGE://??¾ï¾’ï½°?¼??
				if( mDgMapFl ){
					mStatus = DAMAGE_END;
					mAniNoX = 0;
				}
				break;

		}

	} else {
		//å¿?®ºæŠ?¸­ä»¥å¤–ã?å¸¸ã«é‡åŠ›
		if( mStatus != HISATU )	mAccY = SP->GRAVITY;
		//ä¸‹ã?å½“ãŸã‚Šåˆ¤å®šãªã—â?è½ä¸?
		if( mStatus == WALK ){
			mStatus = JUMP_DOWN;
			mAniNoX = 0;
		}
	}	

	if( mHitFl[1] == SP->CHIP_HIT || mHitFl[1] == SP->CHIP_KGHIT ){  //ä¸?
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
		|| mHitFl[2] == SP->CHIP_GMNGAILT || mHitFl[2] == SP->CHIP_KGHIT){//å‰?
		switch( mStatus ){
			case JUMP_UP :
			case JUMP_DOWN ://?¼?ï½¬?ï¾Œï¾Ÿä¸­
			case FUYU :
					mSpX = 0;
					mAccX = 0;
				break;

			case DRILL_START :
			case DRILL ://??¾ï¾˜ï¾™ä¸­
				mDrillFl = 0;
				mSpX = 0;
				mAccX = 0;
				if( mHitFl[2] == SP->CHIP_GMNGAIRT )
					mX = mKabeIchi[2] - sHitX[0][2][0];
				if( mHitFl[2] == SP->CHIP_GMNGAILT )
					mX = mKabeIchi[2] - (HERSIZE - sHitX[0][2][0]);
				break;


			//case DAMAGE ://??¾ï¾’ï½°?¼??
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
		mHitFl[3] == SP->CHIP_GMNGAILT|| mHitFl[3] == SP->CHIP_KGHIT) {//å¾?
		switch( mStatus ){
			case DAMAGE://??¾ï¾’ï½°?¼??
			if( mDgMapFl ){
				mSpX = 0;
				mAccX = 0;
				mAniTimer = 0;
			}
			break;
		}
	}


	//æ”»æ’?ˆ¤å®šã??ï½¯?Œï¾???¾ï¾’ï½°?¼??
	for( int i=0; i < 4; i++ ){
		if( mHitFl[i] == SP->CHIP_KGHIT && mStatus != HISATU ){
			InflictDamage();
		}
	}


}

//åè»¢å‹•ä½œã«å…¥ã‚?
void	Jiki::Hanten()
{
	if( mStatus != HANTEN && mStatus != HISATU && mStatus != DAMAGE && mStatus != DAMAGE_END && 
		mStatus != FADEOUT && mStatus != FADEIN && mStatus != DEAD && mSuperStatus == CONTROL ){
		mAoTimer = 0;
		mAniNoX  = 0;
		mStatus  = HANTEN;
	}
}

// æ­©ãä¸­ã®å ´åˆåè»¢ã—ã¾ã™ã?ã€?©ºä¸­ã®å ´åˆã?Xã‚’è»¸ã«ã—ã¦è·³ã­è¿”ã‚Šã¾ã™ã?
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
	æ•µã¨ã®å½“ãŸã‚Šåˆ¤å®šç”¨?Œï¾šï½°??
*/
void	Jiki::collisionFrames(){

	if( !collisionEnabled ) return;

	//å½“ãŸã‚Šåˆ¤å®šã??Œï¾šï½°??
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
	?—ï½²??§ã®??¾ï½¼?®?å¢—æ¸?
*/
void	Jiki::Tension()
{

	mTenTime += SP->FrameTime;

	//å¿?®ºæŠ?¸­?¼?ï½®?¼?ï½®ã«??¾ï½¼?®?ãŒä¸‹ãŒã£ã¦ã?
	if( mStatus == HISATU ){
		mTenTime = 0;
		mTen -= ( TEN_MAX/HISATU_TIME ) *SP->FrameTime/2;
	}else{
	//??¾ï½¼?®?å¢?
		if(	mTenFl ) {
			if( mTenTime > TEN_UTIME ){
				mTenTime = 0;
				RestoreTension(TEN_UP1, false);
			}
		}else{
		//??¾ï½¼?®?æ¸?
			if( mTenTime > TEN_DTIME ){
				mTenTime = 0;
				mTen -= TEN_DOWN1;
			}
		}
	}
}

/*
	?Œï½ª?°??¾å?ç?
*/
void	Jiki::Fade()
{

	//å¿?®ºæŠ?–‹å§‹ï¾Œï½ª?°??¾?
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

	//å¿?®ºæŠ?µ‚äº?¾Œï½ª?°??¾?
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
	?¹?ï½°?‘ï½µ?°?Šï¾ï½°
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
	?‹ï¾›ï½²?ã‚’æ­©ãçŠ¶æ…‹ã«æˆ»ã?
*/
void	Jiki::HrWalk()
{
	if( mStatus == HISATU ){
		mHisatuTime = HISATU_TIME + 10;
	}


}

/*
	æ®‹æ©Ÿä¸??æ¸›ã‚‹ã€?ã®å ´åˆã?ã‚²ãƒ¼ãƒ?‚ªãƒ¼ãƒã?
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
	åŠé?æ˜ã«ã—ã¾ã?
*/
void Jiki::SetTransparent(bool mOnOff)
{
	mAlphaVal = mOnOff ? GF("HER_TRSP_A") : 1.0f;
}

/**
	\return æ­»ã¬ã¨ã“ã‚ã?
*/
bool Jiki::IsDying()
{
	return (mStatus==DEAD || mStatus==MAKUDOWN || mStatus==FADEOUT || mStatus==FADEIN || (mStatus == DAMAGE_END && mGmOvFl));
}
/*
	\return æ“ä½œãƒ¢ãƒ¼ãƒ‰ã‹
*/
bool Jiki::IsControl()
{
	return (mSuperStatus == CONTROL);
}

/*
	ãƒã‚§ã‚¤ãƒ³ã‚?å€‹å¢—ã‚„ã?
*/
void Jiki::IncrementChain()
{
	if( mChainIdx < MAX_CHAIN )
		mChainIdx++;

	// æ‰“æ’ƒ?´?Œï½ª?¸??‚‚å‡ºã—ã¾ã?
	MakeHitEffect();
}

/*
	ãƒã‚§ã‚¤ãƒ³ã‚?ã«æˆ»ã?
*/
void Jiki::ResetChain()
{
	mChainIdx=0;
}

/*
	ãƒã‚§ã‚¤ãƒ³ãƒ¬ãƒ™ãƒ«ã‚’è¿”ã™
*/
int Jiki::GetChainLv()
{
	return mChainIdx;
}

/*
	æ™‚æœŸã®è¶³å…?«æ‰“æ’ƒ?´?Œï½ª?¸??‚’å‡ºã?
*/
void Jiki::MakeHitEffect(){
	
	// å‡ºç¾åº§æ¨™ã?è¨ˆç®?
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

	// ?˜ï½¸?´?½??
	GAMECONTROL->GetMobManager()->Request( new HitEffect( efx, efy ), true );

}

/*
* \return ?‹ï¾›ï½²?ãŒä½•ã‹ç‰¹åˆ¥ãªã“ã¨ã‚’ã‚„ã£ã¦ã?‚‹çŠ¶æ…‹ã§ã‚ã‚Šã€æ™®æ®µã®å‡¦ç?«ä¾‹å¤–ã—ã¦ã?‚‹ã?
*/
bool Jiki::IsBusy()
{
	return mHisatuTime > HISATU_TIME;
}

/*
	?—ï½²?ŒUP
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
	??¾ï½¼?®?UP
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
	æ®‹æ©ŸUP
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
