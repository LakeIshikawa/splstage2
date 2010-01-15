#include "ChargeEffect.h"
#include "..\\Management\\GameControl.h"

/**
	�W���R���X�g���N�^
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
	�W���f�X�g���N�^
*/
ChargeEffect::~ChargeEffect()
{}

/************************************************************//**
*	1�ڰя���
****************************************************************/
void ChargeEffect::Move()
{
	switch( mStatus ){
	case CHARGE:
		// �^�񒆂��Z���Ȃ�
		mAlpha += GF("CHARGEFX_SP");
		if( mAlpha > 1.0f ) {
			mAlpha = 1.0f;
			mStatus = FADING;
			GAMECONTROL->GetFader()->SetSpeed(GF("HISATU_FADE"));
			mAlphaSp = -GF("CHARGEFX_TMSP");
		}

		// ���̍쐬
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
		// ���̍쐬
		CreateLightPartsStill();
		break;
	}

	// �`��
	Draw();
}

/************************************************************//**
*	�`��
****************************************************************/
void ChargeEffect::Draw()
{
	// �^��
	DX_SCROLL_SCREEN_DRAW("graphics\\effect\\skill_effect3.png", mX-mSizeX/2,
		mY-mSizeY/2, 0, 0, mSizeX, mSizeY, mAlpha);
}

/************************************************************//**
*	����ނ��I��������
****************************************************************/
bool ChargeEffect::IsChargeCompleted()
{
	return ( mStatus == USE );
}

/************************************************************//**
*	�����쐬����(���S�Ɍ����ďW�܂�)
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
*	�����쐬����(���̏�ň������)
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
*	LightPart - �ݽ�׸�
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
*	LightPart - �޽�׸�
****************************************************************/
LightPart::~LightPart()
{}

/************************************************************//**
*	LightPart - 1�ڰя���
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
	// ��̧��0�ɂȂ����������
	if( mAlpha < 0 )
		GAMECONTROL->GetMobManager()->Remove(this);

	// �`��
	Draw();
}

/************************************************************//**
*	�`��
****************************************************************/
void LightPart::Draw()
{
	// �ꗱ
	DX_SCROLL_SCREEN_DRAW(mGraphic, mX-mSizeX/2,
		mY-mSizeY/2, 0, 0, mSizeX, mSizeY, mAlpha);
}
