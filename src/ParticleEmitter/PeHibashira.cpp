#include "PeHibashira.h"
#include "..\\Management\\GameControl.h"
#include <d3dx9.h>

/**
	標準コンストラクタ
*/
PeHibashira::PeHibashira(int rX, int rY, int rNumParticles, string rTexture, int rWidth, int rHeight, bool rUpDown) 
: ParticleEmitter( rX, rY, rNumParticles, rTexture ), mWidth(rWidth), mHeight( rHeight ), mUpDown( rUpDown )
{
	HIBASHIRA_LNPART = GI("HIBASHIRA_LNPART");
	HIBASHIRA_BASESPX = GF("HIBASHIRA_BASESPX");
	HIBASHIRA_FIREINT = GF("HIBASHIRA_FIREINT");
	HIBASHIRA_PTLFTIME = GF("HIBASHIRA_PTLFTIME");

	// 初期化
	mFireTimer = 0.0f;

	// ｼﾞｸﾞｻﾞｸﾞﾊﾟｰﾃｨｸﾙ
	mParticles = new PtZigZagVertWave[mNumParticles];
}

/**
	標準デストラクタ
*/
PeHibashira::~PeHibashira(){}

/************************************************************//**
*	初期化
****************************************************************/
void PeHibashira::InitParticles(D3DCOLOR rColor)
{
	for (int i=0; i<mNumParticles; i++){
		mParticles[i].SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

/************************************************************//**
*	更新
****************************************************************/
void PeHibashira::Update()
{

	// 位置の更新
	for (int i=0; i<mNumParticles; i++){
		if( mParticles[i].IsAlive() ) {

			// 移動
			mParticles[i].UpdatePos();

			// ﾗｲﾌﾀｲﾑ
			if( fabs(mParticles[i].GetPos()->y-mY) > 
				mHeight + mParticles[i].GetLifeTimePlus() )
			{
				mParticles[i].SetAlive(false);
			}

		}
	}

	// 発射
	WAIT_TIMER(mFireTimer, HIBASHIRA_FIREINT)
		FireLine();		
	WAIT_END
}


/************************************************************//**
*	発射
****************************************************************/
void PeHibashira::FireLine()
{
	// 停止状態で新しいﾊﾟｰﾃｨｸﾙは作らない
	if( mStatus == STOP ) return;

	// 位置の更新
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
