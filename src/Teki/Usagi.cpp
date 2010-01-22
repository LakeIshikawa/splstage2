#include ".\Usagi.h"
#include "..\\Management\\GameControl.h"

/* ��Ұ����ް� */
int Usagi::sAniData[][MAX_DATA] =
{
	{ 0, 99 },	// TAIKI
	{ 1, 2, 99 },	// JUMP_START
	{ 3, 99 },	// JUMP
	{ 4, 99 }   // LAND

};

float Usagi::sAniTimeData[][MAX_DATA] =
{
	{ 0.2f, 0.2f },	// TAIKI
	{ 0.2f, 0.2f },	// JUMP_START
	{ 0.2f },	// JUMP
	{ 0.2f }	// LAND
};

/* ���̨���ް� */
char Usagi::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\ene_rabbit_01.png",
	"graphics\\teki\\ene_rabbit_01.png",
	"graphics\\teki\\ene_rabbit_01.png",
	"graphics\\teki\\ene_rabbit_01.png"
};

int Usagi::sMapAtHanteiX[4][MAX_TEN] = 
{
	{ 50, 26, -1 },	//��
	{ -1 },		//��
	{ 60, -1 },	//�O
	{ -1 }		//��
};

int Usagi::sMapAtHanteiY[4][MAX_TEN] = 
{ 
	{ 72, 72, -1 },	//��
	{ -1 },		//��
	{ 35, -1 },	//�O
	{ -1 }		//��
};


Usagi::Usagi(int rXPx, int rYPx)
{

	USAGISX = GI("USAGISX");
	USAGISY = GI("USAGISY");

	UTAIKI_TIME = GF("UTAIKI_TIME");
	UJUMPSTART_TIME = GF("UJUMPSTART_TIME");
	UJMPSPX = GF("UJMPSPX");
	UJMPTAKASA = GF("UJMPTAKASA");

	mX = rXPx;
	mY = rYPx - sMapAtHanteiY[0][0] + SP->CHSZY;

	mSizeX = USAGISX;
	mSizeY = USAGISY;

	mStatus		= JUMP;

	mTaikiTimer = 0.0f;

	mCurAshiba = NULL;

	// �����蔻��
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, 36, 36, 28);
	AddIndexedRect(0, SP->GRID_BOUND, TBOUND_IDX, 10, 12, 48, 72);
	SetCurFrame(0);
}

Usagi::~Usagi(void)
{
}

void Usagi::_Move()
{

	SetAnim(mStatus);

	// �s��
	switch( mStatus ){
		
		case JUMP:
			MapAtHt();

			if(mAtari[0] == SP->CHIP_HIT || mAtari[0] == SP->CHIP_AMHIT || mAtari[0] == SP->CHIP_KGHIT || mCurAshiba ){ //���������Ă�
				mSpY = 0;
				mSpX = 0;
				mAccX = 0;
				mAccY = 0;
				if( !mCurAshiba )
					mY = mShirabe[0] - sMapAtHanteiY[0][0];
				mStatus = LAND;
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
			WAIT_TIMER(mTaikiTimer, UTAIKI_TIME)
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
			WAIT_TIMER(mTaikiTimer, UJUMPSTART_TIME)
			{
				mStatus = JUMP;
				mSpX = (mMuki?1:-1)*UJMPSPX;
				mSpY = -sqrt(2 * SP->GRAVITY * UJMPTAKASA);
				//SE
				if( !IsGamenGai() )
					GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kaeru_junp.wav");
			}	
			WAIT_END
			break;

		case LAND:
			if( mDousaEnd ) mStatus = TAIKI;
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
void Usagi::MapAtHt()
{
	MAP_SUPERATHT(mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, 
		sMapAtHanteiX, sMapAtHanteiY, mSizeX, mSizeY, mAtari, mShirabe);
}

/*
	��ʂ̉��ɗ������������
*/
void Usagi::DieIfGamenGai()
{
	if(mY > SP->SCRSZY)
		GAMECONTROL->GetMobManager()->Remove(this);
}