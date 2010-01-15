#include "ChargeEffect.h"
#include "..\\Management\\GameControl.h"

/**
	標準コンストラクタ
*/
ChargeEffect::ChargeEffect(int rXPx, int rYPx)
{
	mSizeX = GI("CHARGEFX_SX");
	mSizeY = GI("CHARGEFX_SY");
	mX = rXPx;
	mY = rYPx;
	mZ = -1.0f;

	mAlpha = 0.0f;
	mStatus = CHARGE;
	mTimer = 0.0f;
}

/**
	標準デストラクタ
*/
ChargeEffect::~ChargeEffect()
{}

/************************************************************//**
*	1ﾌﾚｰﾑ処理
****************************************************************/
void ChargeEffect::Move()
{
	switch( mStatus ){
	case CHARGE:
		// 真ん中が濃くなる
		mAlpha += GF("CHARGEFX_SP");
		if( mAlpha > 1.0f ) {
			mAlpha = 1.0f;
			mStatus = FADING;
			GAMECONTROL->GetFader()->SetSpeed(GF("HISATU_FADE"));
			mAlphaSp = -GF("CHARGEFX_TMSP");
		}

		// 粒の作成
		CreateLightPartsCharge();

		break;

	case FADING:
		if( GAMECONTROL->GetFader()->FadeOut() )
			mStatus = FADINGIN;
		break;

	case FADINGIN:
		if( GAMECONTROL->GetFader()->FadeIn() )
			mStatus = USE;

	case USE:
		mAlpha += mAlphaSp;
		if( mAlpha > 1.0f || mAlpha < 0.5f ) mAlphaSp*=-1;
		// 粒の作成
		CreateLightPartsStill();
		break;
	}

	// 描画
	Draw();
}

/************************************************************//**
*	描画
****************************************************************/
void ChargeEffect::Draw()
{
	// 真ん中
	DX_SCROLL_SCREEN_DRAW("graphics\\effect\\skill_effect3.png", mX-mSizeX/2,
		mY-mSizeY/2, 0, 0, mSizeX, mSizeY, mAlpha);
}

/************************************************************//**
*	ﾁｬｰｼﾞが終了したか
****************************************************************/
bool ChargeEffect::IsChargeCompleted()
{
	return ( mStatus == USE );
}

/************************************************************//**
*	粒を作成する(中心に向けて集まる)
****************************************************************/
void ChargeEffect::CreateLightPartsCharge()
{
	WAIT_TIMER(mTimer, GF("CHARGEFX_PTTIME"))
		float angle = ((float)rand()/RAND_MAX)*D3DX_PI*2;
		float x = cos(angle);
		float y = sin(angle);

		LightPart* p;
		if( rand()%2 ) {
			p = new LightPartSmall(mX + x*GI("CHARGEFX_PTRAD"), 
				mY + y*GI("CHARGEFX_PTRAD"), -x*GF("CHARGEFX_PTSP"), 
				-y*GF("CHARGEFX_PTSP"), GF("CHARGEFX_PTALSP"), 1.0f);
		}
		else {
			p = new LightPartBig(mX + x*GI("CHARGEFX_PTRAD"), 
				mY + y*GI("CHARGEFX_PTRAD"), -x*GF("CHARGEFX_PTSP"), 
				-y*GF("CHARGEFX_PTSP"), GF("CHARGEFX_PTALSP"), 1.0f);
		}

		p->Build();
		GAMECONTROL->GetMobManager()->Request(p, true);
	WAIT_END
}


/************************************************************//**
*	粒を作成する(その場で一回煌く)
****************************************************************/
void ChargeEffect::CreateLightPartsStill()
{
	WAIT_TIMER(mTimer, GF("CHARGEFX_PTTIME"))
		float x = ((float)rand()/RAND_MAX)*2 -1;
		float y = ((float)rand()/RAND_MAX)*2 -1;

		LightPart* p;
		if( rand()%2 ){
			p = new LightPartSmall(mX + x*GI("CHARGEFX_PTRAD"), 
				mY + y*GI("CHARGEFX_PTRAD"), 0, 0, GF("CHARGEFX_PTALSP"), 0.0f);
		}
		else{
			p = new LightPartBig(mX + x*GI("CHARGEFX_PTRAD"), 
				mY + y*GI("CHARGEFX_PTRAD"), 0, 0, GF("CHARGEFX_PTALSP"), 0.0f);
		}
		p->Build();
		GAMECONTROL->GetMobManager()->Request(p, true);
	WAIT_END
}

/************************************************************//**
*	LightPart - ｺﾝｽﾄﾗｸﾀ
****************************************************************/
LightPart::LightPart(int rXPx, int rYPx, float rSpX, float rSpY, float rSpAlpha, float rAlpha)
{
	mX = rXPx;
	mY = rYPx;
	mZ = -1.0f;

	mSpX = rSpX;
	mSpY = rSpY;
	mSpAlpha = rSpAlpha;

	mAlpha = rAlpha;
}

/************************************************************//**
*	LightPart - ﾃﾞｽﾄﾗｸﾀ
****************************************************************/
LightPart::~LightPart()
{}

/************************************************************//**
*	LightPart - 1ﾌﾚｰﾑ処理
****************************************************************/
void LightPart::Move()
{
	mX += mSpX;
	mY += mSpY;
	mAlpha += mSpAlpha;

	if( mAlpha >= 1.0f ) {
		mAlpha = 1.0f;
		mSpAlpha *= -1;
	}
	// ｱﾙﾌｧが0になったら消える
	if( mAlpha < 0 )
		GAMECONTROL->GetMobManager()->Remove(this);

	// 描画
	Draw();
}

/************************************************************//**
*	描画
****************************************************************/
void LightPart::Draw()
{
	// 一粒
	DX_SCROLL_SCREEN_DRAW(mGraphic, mX-mSizeX/2,
		mY-mSizeY/2, 0, 0, mSizeX, mSizeY, mAlpha);
}
