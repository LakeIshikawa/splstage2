#pragma once
#include "..\\\Mob\\LightResponseAble.h"
#include "..\\Mob\\Collidable.h"
#include "InterfaceView.h"
#include "..\\Collision\\Rect.h"
#include "..\\Mob\\IRideCapable.h"
#include "..\\Effect\\ChargeEffect.h"

class Ashiba;

////ﾊﾟﾗﾒｰﾀ
#define	ANIFR	100//ｱﾆﾒｰｼｮﾝﾌﾚｰﾑMAX
#define	GRAME	200//ｸﾞﾗﾌｨｯｸ名の文字数MAX
#define TENSU	20 //当たり判定の点の最大個数

#define MAX_CHAIN 5

/*
	自機
*/
class Jiki :
	public virtual LightResponseAble, public virtual Collidable, public IRideCapable
{
public:
	Jiki(int rXPx, int rYPx);
	~Jiki(void);

	void Move();

	void ResponseAka();
	void ResponseAo();
	void ResponseMidori();
	void ResponseMushoku();
	void NoLight();

	int	GetAtHtPointX();
	int GetAtHtPointY();

	bool GetMuki();

	void CollisionResponse(ICollidable* rCollObject, int rThisGroupId, int rOpGroupId);
	int GetSizeX();

	void RunTask();
	void HrWalk();


	// 外部インターフェース
	void InflictDamage();
	void IncreaseTensEmpa();
	void HantenOrRebound();
	void DisableCollision();
	void EnableCollision();

	void RestoreEmpacy(int n) { mEmp += n; if( mEmp > EMP_MAX ) mEmp = EMP_MAX; }
	void RestoreTension(int n) { mTen += n; if( mTen > TEN_MAX ) mTen = TEN_MAX; }
	void RestoreLife(int n) { mLife += n; if( mLife > LIFE_MAX) mLife = LIFE_MAX; }

	int GetLife() { return mLife; }
	float GetEmpa() { return mEmp; }
	float GetTens() { return mTen; }
	
	InterfaceView* GetInterface() { return mInterface; }

	void SetPos(int rX, int rY) { mX = rX; mY = rY; }
	void SetMuki( int rMuki )	{ mMuki = rMuki; }
	void ResetLife();
	void ResetTension();
	void ResetEmpacy();
	void ResetTempParams();

	void Die();
	bool IsDying();
	bool IsControl();

	bool IsBusy();

	// チェイン
	void IncrementChain();
	void ResetChain();
	int GetChainLv();

	// 打撃ｴﾌｪｸﾄ
	void MakeHitEffect();
	
	//強風
	void	SetWindForce(float rAccX) { if( !mHouseProtected) mKazeAccX = rAccX; }
	void	SetHouseProtected() { mHouseProtected = true; }

	void SetSuperWait(float rTime);
	void SetSuperControl();
	void SetSuperPause();

	// IRideCapableの実装
	Rect* GetRideRect() { collisionFrames(); return (Rect*)(pCollision->GetFrame(FR_ARUKI)->GetIndexedShape(0)); }
	float GetSpX() {return mSpX;}
	float GetSpY() {return mSpY;}
	void SetX(int rX) { mX = rX; }
	void SetY(int rY) { mY = rY; }
	void SetSpX(float rNewSpX) { mSpX = rNewSpX; }
	void SetSpY(float rNewSpY) { mSpY = rNewSpY; }
	void AddSpX(float rAddX){ mAshiSpX = rAddX; }
	void RideResponse(Ashiba* rAshiba) { mCurAshiba = rAshiba; }
	void GetOffResponse(Ashiba* rAshiba) { mCurAshiba = NULL; }


	enum SUPER_STATUS{
		WAIT,
		CONTROL,
		PAUSE
	};

	enum STATUS
		{
			WALK = 0,
			TEISHI,
			HANTEN,
			KOGEKI_START,
			KOGEKI,
			KOGEKI_END,
			KOGEKI_STAN,
			JUMP_START,
			JUMP_UP,
			JUMP_DOWN,
			JUMP_END,
			DRILL_START,
			DRILL,
			DRILL_END,
			FUYU,
			DAMAGE,
			DAMAGE_END,
			HISATU,
			DEAD,
			MAKUDOWN,
			FADEOUT,
			FADEIN
		};

	enum FRAMES
	{
		FR_ARUKI,
		FR_TACHI,
		FR_JUMP,
		FR_KOGEKI,
		FR_DRILL,
		FR_HISATU,
		FR_DISABLE
	};

private:
	float mSpX;//ｽﾋﾟｰﾄﾞ
	float mSpY;
	float mAccX;//加速度
	float mAccY;

	float mKazeAccX;
	bool mHouseProtected;

	//当たり判定
	int mHitFl[4];//0:↓　1:↑　2:前　3:後
	int mKabeIchi[4];
	static	int	sAniData[][ANIFR];
	static	double sAniTime[][ANIFR];
	static	char sGraphic[][GRAME];
	static	int	sHitX[][4][TENSU];
	static	int	sHitY[][4][TENSU];

	SUPER_STATUS mSuperStatus;
	STATUS	mStatus;

	//ｱﾆﾒｰｼｮﾝ
	float	mAniTimer;
	int		mAniNoX;
	int		mAniNoY;
	bool	mAniTeishi;

	//ﾀﾞﾒｰｼﾞ用
	int		mDgMutekiFl;
	bool	mDgMapFl;
	float	mDamageTimer;

	//float	mTenmetuTimer;
	float	mAlphaTimer;
	float	mAlphaVal;

	//当たり判定オン・オフ
	bool	collisionEnabled;

	//赤用
	float	mAkaTimer;
	float	mAkaTimer2;
	float	mStanTimer;
	int		mStanAni;
	//青用
	float	mAoTimer;
	//緑用
	float	mMidTimer;
	bool	mMidFl;

	//ﾄﾞﾘﾙｷｯｸ
	float	mHozonY;
	int		mDrillFl;
	//必殺技
	float	mHisatuTime;
	float	mHsX;
	float	mHsY;
	float	mHshozon;
	float	mHisatuMuki;
	//ﾌｪｰﾄﾞ
	int		mFadeFl;
	bool	mFadeFl2;
	//ｹﾞｰﾑｵｰﾊﾞｰ
	int		mGmOvFl;

	//ﾁｬｰｼﾞｴﾌｪｸﾄ
	ChargeEffect* mChargeFx;

	//SE
	bool	mDmSE;
	float	mDmSETimer;
	bool	mTenSE;
	
	//ｹﾞｰｼﾞ類
	int		mLife;
	float	mEmp;
	float	mEmpTeki;
	float	mTen;
	float	mTenTime;
	bool	mTenFl;

	// インターフェースビュー
	InterfaceView *mInterface;

	// スーパーステータス
	float mSuperWaitTimer;

	// 足場よう
	bool	mAshibaFl;
	Ashiba*	mCurAshiba;
	float mAshiSpX;

	// チェイン
	int mChainIdx;
	static float sChainMultSp[MAX_CHAIN+1];
	static float sChainMultShoSp[MAX_CHAIN+1];

	//関数群
	void	UnTeishi();
	void	AkaCheck();
	void	AoCheck();
	void	MidCheck();
	void	Hisatu();

	void	MapAtHt();
	int		GetMukiMult();

	//ｱｸｼｮﾝ
	void	Hanten();

	//当たり判定
	void collisionFrames();

	//ﾃﾝｼｮﾝ
	void	Tension();
	//ﾌｪｰﾄﾞ
	void	Fade();
	//ｹﾞｰﾑｵｰﾊﾞｰ
	void	Gameover();

	//半透明にする
	void	SetTransparent(bool mOnOff);

	//設定定数
	int LIFE_MAX;
	int LIFE_SHOKI;
	float EMP_SHOKI;
	int HERSIZE;
	float DAMAGE_SP;
	float EMP_DOWN;
	float EMP_MAX;
	float TEN_DOWN2;
	float TEN_UP2;
	float TEN_MAX;
	float EMP_UP;
	float SPANI;
	float SPWALK;
	float ACCKOGEKI;
	float STAN_TIME;
	float STAN_ANI;
	float JUMP_SHOSP;
	float DRILL_SP;
	float FUYU_SP;
	float HISATU_TIME;
	float MUTEKI_TIME;
	float TENMETU_TIME;
	float END_TIME;
	float DRILL_HEIGTH;
	float HANTEN_TIME;
	float HISATU_LTSP;
	float HISATU_HRSP;
	float HISATU_FADE;
	float TEN_UTIME;
	float TEN_UP1;
	float TEN_DTIME;
	float TEN_DOWN1;
	float HER_DIE_TIME;


};
