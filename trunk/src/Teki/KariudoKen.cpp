#include ".\KariudoKen.h"
#include "..\\Management\\GameControl.h"

class AshibaInvisible;
class AshibaMovable;
class AshibaTenbin;


/* ��Ұ����ް� */
int KariudoKen::sAniData[][MAX_DATA] =
{
	{ 3, 4, 5, 6, 7, 8, 99 },	// ARUKI
	{ 0, 1, 2, 99 },			// WAIT1
	{ 0, 1, 2, 3, 4, 5, 99 },	// KOGEKI
	{ 0, 1, 2, 99 },			// WAIT2
	{ 0, 99 }					// SHINDA

};

float KariudoKen::sAniTimeData[][MAX_DATA] =
{
	{ 0.05f, 0.05f, 0.05f, 0.1f, 0.1f, 0.1f },	// ARUKI
	{ 0.2f, 0.2f, 0.2f },					// WAIT1
	{ 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f },	// KOGEKI
	{ 0.2f, 0.2f, 0.2f },					// WAIT2
	{ 0.2f, }								// SHINDA
};

/* ���̨���ް� */
char KariudoKen::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\ene_hunter1.png",			// ARUKI
	"graphics\\teki\\ene_hunter1.png",			// WAIT1
	"graphics\\teki\\ene_hunter1_attack.png",	// KOGEKI
	"graphics\\teki\\ene_hunter1.png",			// WAIT2
	"graphics\\teki\\ene_hunter1_damage.png",	// SHINDA
};

// ϯ�ߓ����蔻���ް�
int KariudoKen::sMapAtHanteiX[4][MAX_TEN] = 
{
	{ 48, 90, -1 },	//��
	{ -1 },		//��
	{ 90, -1 },	//�O
	{ -1 }		//��
};

int KariudoKen::sMapAtHanteiY[4][MAX_TEN] = 
{ 
	{ 117, 117, -1 },	//��
	{ -1 },		//��
	{ 100, -1 },	//�O
	{ -1 }		//��
};

KariudoKen::KariudoKen(int rXPx, int rYPx)
{

	KARIKENSX = GI("KARIKENSX");
	KARIKENSY = GI("KARIKENSY");

	KARIKENSPX = GF("KARIKENSPX");
	KARIKENKGHANI = GF("KARIKENKGHANI");
	KARIKENWTM1 = GF("KARIKENWTM1");
	KARIKENWTM2 = GF("KARIKENWTM2");

	mX = rXPx;
	mY = rYPx - sMapAtHanteiY[0][0] + SP->CHSZY;

	mSizeX = KARIKENSX;
	mSizeY = KARIKENSY;

	mStatus = ARUKI;

	mKgTimer = 0.0f;

	mSeFl = false;

	// �����蔻��	
	AddFrame(FR_KAMAE);
	AddFrame(FR_ZANZOU);
	AddFrame(FR_DOWN);

	AddRect(FR_KAMAE, SP->GRID_BOGYO, 43, 33, 81, 119);
	AddIndexedRect( FR_KAMAE, SP->GRID_BOUND, TBOUND_IDX, 38, 22, 83, 120);
	
	AddRect(FR_ZANZOU, SP->GRID_BOGYO, 43, 33, 81, 119);
	AddCircle(FR_ZANZOU, SP->GRID_KOUGEKI, 38, 43, 35);
	AddCircle(FR_ZANZOU, SP->GRID_KOUGEKI, 33, 69, 35);
	AddIndexedRect( FR_ZANZOU, SP->GRID_BOUND, TBOUND_IDX, 38, 22, 83, 120);

	AddRect(FR_DOWN, SP->GRID_BOGYO, 43, 33, 81, 119);
	AddCircle(FR_DOWN, SP->GRID_BOGYO, 20, 62, 11);
	AddIndexedRect( FR_DOWN, SP->GRID_BOUND, TBOUND_IDX, 38, 22, 83, 120);

	//AddCircle(0, GRID_BOGYO, 60, 60, 30);

	SetAnim(0);
}

KariudoKen::~KariudoKen(void)
{
}

void KariudoKen::_Move()
{
	SetAnim( mStatus );

	// ���@�̈ʒu���擾
	int jx = GAMECONTROL->GetJiki()->GetAtHtPointX();
	int jy = GAMECONTROL->GetJiki()->GetAtHtPointY();

	// ----������̏���
	MapAtHt();

	if( mStatus != SHINDA )
		Ataridp();


	switch( mStatus ){
		case ARUKI: {
			// ----���@�̈ʒu���m�F
			float sax = jx - CenterX();
			float say = jy - CenterY();
			float sa = sqrt(sax*sax + say*say);

			if( sa < KARIKENKGHANI ){
				mStatus = WAIT1;
			}

			break;
		}
		
		case WAIT1:
			mSpX = 0;
			WAIT_TIMER(mKgTimer, KARIKENWTM1);
			mStatus = KOGEKI;
			WAIT_END
			break;

		case KOGEKI:
			if( mAniNoX == 2 &&  !mSeFl ){//SE
				GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_ken_atack.wav");
				mSeFl = true;
			}
			mSpX = 0;
			mMuki = CenterX() < jx;
			if( mDousaEnd ){
				mStatus = WAIT2;
				mSeFl = false;
			}
			break;
	
		case WAIT2:
			mSpX = 0;
			WAIT_TIMER(mKgTimer, KARIKENWTM2);
			mStatus = ARUKI;
			WAIT_END
			break;
	}
	
	Draw();

	mSpX += mAccX;
	mSpY += mAccY;
	mX	 += mSpX + mAshibaSpX;
	mY	 += mSpY;

	// �����蔻����ڰ�
	if( mStatus != SHINDA )
		HtFrame();
}

/*
	ϯ�߂Ƃ̓����蔻����s���܂��B
	���̊֐��̎��s���A���̕ϐ��̒��g���ς��܂��F
	mShirabe[]
	mAtari[]
*/
void KariudoKen::MapAtHt()
{
	MAP_SUPERATHT(mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, 
		sMapAtHanteiX, sMapAtHanteiY, mSizeX, mSizeY, mAtari, mShirabe);
}
/*
	�����蔻�艞��
*/
void KariudoKen::Ataridp()
{
	// ��
	if( mAtari[0] == SP->CHIP_AMHIT || mAtari[0] == SP->CHIP_KGHIT || mCurAshiba){ 
		mSpY = 0;
		mSpX = (mMuki?1:-1)*KARIKENSPX;
		mAccX = 0;
		mAccY = 0;
		if( !mCurAshiba )
			mY = mShirabe[0] - sMapAtHanteiY[0][0];
	}
	else{
		mAccY = SP->GRAVITY;
	}
	
	// �O
	if(mAtari[2] == SP->CHIP_HIT || mAtari[2] == SP->CHIP_GMNGAILT 
		|| mAtari[2] == SP->CHIP_GMNGAIRT || mAtari[2] == SP->CHIP_KGHIT){ // �O�������Ă�
		mMuki = !mMuki;
	}
}
/*
	�����蔻����ڰ�
*/
void KariudoKen::HtFrame()
{
	switch( mStatus ){
		case ARUKI:
			SetCurFrame( FR_KNDOWN );
			break;

		case KOGEKI:
			if( mAniNoX >= 2 && mAniNoX!=5  ) {
				SetCurFrame( FR_ZANZOU );
			}
			else if( mAniNoX!=5 ) {
				SetCurFrame( FR_KAMAE );
			}
			else {
				SetCurFrame( FR_KNDOWN );
			}

			break;
	}
}

/*
	���񂾂Ƃ��̏���(�l�^)
*/
void KariudoKen::Die()
{
		// �۲݂̈ʒu�ɂ����x���̑��x�����߂�
		mSpX = -SHINIPATT_SPX;
		Jiki* jiki = GAMECONTROL->GetJiki();
		if( jiki->GetAtHtPointX() < CenterX() )
			mSpX *= -1;

		mStatus = SHINDA;
	
		mBasStatus = SHINI;
		mSpY = -SHINIPATT_SHOSP;
		mAccY = SP->GRAVITY;

		//Finalize();
		DisableAshibaCollision();
}

void KariudoKen::Move()
{
	Animate();
	_Move();

}
/*
	�G�̕`��
*/
void KariudoKen::Draw()
{

	DX_SCROLL_DRAW(GraphicData()+mAnimSet*MAX_NLEN, mX, mY, 
	mNo_x*mSizeX, mMuki*mSizeY, (mNo_x+1)*mSizeX, (mMuki+1)*mSizeY);

	DieIfGamenGai();
}