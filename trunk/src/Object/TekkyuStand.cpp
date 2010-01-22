#include "TekkyuStand.h"
#include "Tekkyu.h"
#include "..\\Management\\GameControl.h"

/**
	�W���R���X�g���N�^
*/
TekkyuStand::TekkyuStand(int rXPx, int rYPx, float rZ)
{
	mSizeX = GI("TEKKYUSTDSX");
	mSizeY = GI("TEKKYUSTDSY");

	mX = rXPx;
	mY = rYPx - mSizeY + SP->CHSZY;
	mZ = rZ;

	TEKKYUSTD_PRODTIME1 = GF("TEKKYUSTD_PRODTIME1");
	TEKKYUSTD_PRODTIME2 = GF("TEKKYUSTD_PRODTIME2");
	TEKKYUSTD_MAXTEKKYU = GI("TEKKYUSTD_MAXTEKKYU");
	mProdTimer = TEKKYUSTD_PRODTIME1;
}

/**
	�W���f�X�g���N�^
*/
TekkyuStand::~TekkyuStand()
{}

/************************************************************//**
*	1�ڰя���
****************************************************************/
void TekkyuStand::Move()
{
	// ��ʊO�̏ꍇ�A��ϰ��ؾ��
	if( GAMECONTROL->GetStageManager()->GetCurrentStage()->GetMap()->IsGamenGai( mX, mY, mSizeX, mSizeY ) )
		mProdTimer = TEKKYUSTD_PRODTIME1;

	// ��ϰ��ҋ@
	mProdTimer -= SP->FrameTime;
	if( mProdTimer <= 0.0f && !TekkyuMaxReached() ){
		mProdTimer = TEKKYUSTD_PRODTIME2;
		ProduceTekkyu();
	}

	// ���u�̕`��
	Draw();
}

/************************************************************//**
*	�`��
****************************************************************/
void TekkyuStand::Draw()
{
	DX_SCROLL_DRAW("graphics\\object\\obj_ag_stand.png", 
		mX, mY, 0, 0, mSizeX, mSizeY);
}

/************************************************************//**
*	�S�����Y��
****************************************************************/
void TekkyuStand::ProduceTekkyu()
{
	Tekkyu* newTekkyu = new Tekkyu( mX, mY+GI("TEKKYU_STARTY"), mZ-0.5f, this );
	GAMECONTROL->GetMobManager()->Request( newTekkyu, true );
}

/************************************************************//**
*	\return true-����ȏ�͍�点�Ȃ���  false-����Ăč\��Ȃ���
****************************************************************/
bool TekkyuStand::TekkyuMaxReached()
{
	return 
		GAMECONTROL->GetMobManager()->GetInScreenNumOf<Tekkyu>()==
		TEKKYUSTD_MAXTEKKYU;
}