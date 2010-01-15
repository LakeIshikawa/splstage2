#include "PeHibashira.h"
#include "..\\Management\\GameControl.h"
#include <d3dx9.h>

/**
	�W���R���X�g���N�^
*/
PeHibashira::PeHibashira(int rX, int rY, int rNumParticles, string rTexture, int rWidth, int rHeight, bool rUpDown) 
: ParticleEmitter( rX, rY, rNumParticles, rTexture ), mWidth(rWidth), mHeight( rHeight ), mUpDown( rUpDown )
{
	HIBASHIRA_LNPART = GI("HIBASHIRA_LNPART");
	HIBASHIRA_BASESPX = GF("HIBASHIRA_BASESPX");
	HIBASHIRA_FIREINT = GF("HIBASHIRA_FIREINT");
	HIBASHIRA_PTLFTIME = GF("HIBASHIRA_PTLFTIME");

	// ������
	mFireTimer = 0.0f;

	// �޸޻޸��߰è��
	mParticles = new PtZigZagVertWave[mNumParticles];
}

/**
	�W���f�X�g���N�^
*/
PeHibashira::~PeHibashira(){}

/************************************************************//**
*	������
****************************************************************/
void PeHibashira::InitParticles(D3DCOLOR rColor)
{
	for (int i=0; i<mNumParticles; i++){
		mParticles[i].SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

/************************************************************//**
*	�X�V
****************************************************************/
void PeHibashira::Update()
{

	// �ʒu�̍X�V
	for (int i=0; i<mNumParticles; i++){
		if( mParticles[i].IsAlive() ) {

			// �ړ�
			mParticles[i].UpdatePos();

			// ײ����
			if( fabs(mParticles[i].GetPos()->y-mY) > 
				mHeight + mParticles[i].GetLifeTimePlus() )
			{
				mParticles[i].SetAlive(false);
			}

		}
	}

	// ����
	WAIT_TIMER(mFireTimer, HIBASHIRA_FIREINT)
		FireLine();		
	WAIT_END
}


/************************************************************//**
*	����
****************************************************************/
void PeHibashira::FireLine()
{
	// ��~��ԂŐV�����߰è�ق͍��Ȃ�
	if( mStatus == STOP ) return;

	// �ʒu�̍X�V
	int partNum = 0;
	for (int i=0; i<mNumParticles && partNum<HIBASHIRA_LNPART; i++){
		if( !mParticles[i].IsAlive() ) {
			mParticles[i].Reset();
			mParticles[i].SetAlive(true);
			mParticles[i].SetPos( mX + (mWidth/HIBASHIRA_LNPART)*partNum, mY );
			mParticles[i].SetSpd( 0.0f, ((float)rand()/RAND_MAX+HIBASHIRA_BASESPX) * (mUpDown?1:-1));
			mParticles[i].SetLifeTimePlus( ((float)rand()/RAND_MAX)*HIBASHIRA_PTLFTIME );
			partNum++;
		}
	}
}
