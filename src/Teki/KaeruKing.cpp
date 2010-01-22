#include ".\KaeruKing.h"
#include "..\\Management\\GameControl.h"

/* ��Ұ����ް� */
int KaeruKing::sAniData[][MAX_DATA] =
{
	{ 0, 99 },	// TAIKI
	{ 1, 99 },	// JUMP_START
	{ 2, 99 },	// JUMP

};

float KaeruKing::sAniTimeData[][MAX_DATA] =
{
	{ 0.2f },	// TAIKI
	{ 0.2f },	// JUMP_START
	{ 0.2f }	// JUMP
};

/* ���̨���ް� */
char KaeruKing::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\ene_frogking.png",
	"graphics\\teki\\ene_frogking.png",
	"graphics\\teki\\ene_frogking.png"
};

int KaeruKing::sMapAtHanteiX[4][MAX_TEN] = 
{
	{ 60, 27, -1 },	//��
	{ -1 },		//��
	{ 80, -1 },	//�O
	{ -1 }		//��
};

int KaeruKing::sMapAtHanteiY[4][MAX_TEN] = 
{ 
	{ 85, 85, -1 },	//��
	{ -1 },		//��
	{ 57, -1 },	//�O
	{ -1 }		//��
};


KaeruKing::KaeruKing(int rXPx, int rYPx)
{

	KAERUKSX = GI("KAERUKSX");
	KAERUKSY = GI("KAERUKSY");

	KTAIKI_TIME = GF("KTAIKI_TIME");
	KJUMPSTART_TIME = GF("KJUMPSTART_TIME");
	KJMPSPX = GF("KJMPSPX");
	KJMPTAKASA = GF("KJMPTAKASA");

	mX = rXPx;
	mY = rYPx - sMapAtHanteiY[0][0] + SP->CHSZY;

	mSizeX = KAERUKSX;
	mSizeY = KAERUKSY;

	mStatus		= JUMP;

	mTaikiTimer = 0.0f;

	mCurAshiba = NULL;

	// �����蔻��
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, 44, 44, 44);
	AddIndexedRect(0, SP->GRID_BOUND, TBOUND_IDX, 10, 12, 73, 85);
	SetCurFrame(0);
}

KaeruKing::~KaeruKing(void)
{
}

void KaeruKing::_Move()
{

	SetAnim(mStatus);

	// �s��
	switch( mStatus ){
		
		case JUMP:
			MapAtHt();

			if( mAtari[0] == SP->CHIP_AMHIT || mAtari[0] == SP->CHIP_KGHIT || mCurAshiba ){ //���������Ă�
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
				mAtari[2] == SP->CHIP_GMNGAIRT || mAtari[2] == SP->CHIP_GMNGAILT ){ // �O�������Ă�
				mMuki = !mMuki;
				mSpX *= -1;
			}
			break;

		case TAIKI:
			WAIT_TIMER(mTaikiTimer, KTAIKI_TIME)
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
			WAIT_TIMER(mTaikiTimer, KJUMPSTART_TIME)
			{
				mStatus = JUMP;
				mSpX = (mMuki?1:-1)*KJMPSPX;
				mSpY = -sqrt(2 * SP->GRAVITY * KJMPTAKASA);
				//SE
				if( !IsGamenGai() )
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
	ϯ�߂Ƃ̓����蔻����s���܂��B
	���̊֐��̎��s���A���̕ϐ��̒��g���ς��܂��F
	mShirabe[]
	mAtari[]
*/
void KaeruKing::MapAtHt()
{
	MAP_SUPERATHT(mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, 
		sMapAtHanteiX, sMapAtHanteiY, mSizeX, mSizeY, mAtari, mShirabe);
}

/*
	��ʂ̉��ɗ������������
*/
void KaeruKing::DieIfGamenGai()
{
	if(mY > SP->SCRSZY)
		GAMECONTROL->GetMobManager()->Remove(this);
}