#include ".\UgokuKi.h"
#include "..\\Management\\GameControl.h"

/* ��Ұ����ް� */
int UgokuKi::sAniData[][MAX_DATA] =
{
	{ 0, 99 },				// KAKUSHI
	{ 1, 2, 99 },			// ACTION
	{ 2, 3, 4, 3, 99 },		// ARUKI

};

float UgokuKi::sAniTimeData[][MAX_DATA] =
{
	{ 0.2f },					// KAKUSHI
	{ 0.2f, 0.2f },				// ACTION
	{ 0.2f, 0.2f, 0.2f, 0.2f, }	// ARUKI
};

/* ���̨���ް� */
char UgokuKi::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\ene_runner.png",	// KAKUSHI
	"graphics\\teki\\ene_runner.png",	// ACTION
	"graphics\\teki\\ene_runner.png",	// ARUKI
};

// ϯ�ߓ����蔻���ް�
int UgokuKi::sMapAtHanteiX[4][MAX_TEN] = 
{
	{ 39, 77, -1 },	//��
	{ -1 },		//��
	{ 147, -1 },	//�O
	{ -1 }		//��
};

int UgokuKi::sMapAtHanteiY[4][MAX_TEN] = 
{ 
	{ 181, 181, -1 },	//��
	{ -1 },		//��
	{ 116, -1 },	//�O
	{ -1 }		//��
};

UgokuKi::UgokuKi(int rXPx, int rYPx)
{
	// �ݒ�萔
	UGOKUKISX = GI("UGOKUKISX");
	UGOKUKISY = GI("UGOKUKISY");

	UGOKUKIHANI = GF("UGOKUKIHANI");
	UGOKUKISPX = GF("UGOKUKISPX");

	mX = rXPx;
	mY = rYPx - sMapAtHanteiY[0][0] + SP->CHSZY;

	mSizeX = UGOKUKISX;
	mSizeY = UGOKUKISY;

	mStatus = KAKUSHI;


	// �����蔻��	
	AddFrame(0);

	AddRect(0, SP->GRID_HANTEN, 0, 0, 10, mSizeY);
	AddCircle(0, SP->GRID_BOGYO, 60, 60, 49);
	AddCircle(0, SP->GRID_BOGYO, 60, 121, 49);

	
	SetAnim(0);
}

UgokuKi::~UgokuKi(void)
{
}

void UgokuKi::_Move()
{
	SetAnim( mStatus );

	switch( mStatus ){
		case KAKUSHI: {

			// ���@�̈ʒu���擾
			int jx = GAMECONTROL->GetJiki()->GetAtHtPointX();

			// ----���@�̈ʒu���m�F
			float sax = jx - CenterX();

			if( fabs( sax ) < UGOKUKIHANI){
				mStatus = ARUKI;
				mMuki = sax > 0;
			}
		} break;

		case ACTION: {
			if( mDousaEnd )
				mStatus = ARUKI;
		} break;

		case ARUKI: {
				// ----������̏���
				MapAtHt();

				// ��
				if(mAtari[0] == SP->CHIP_HIT || mAtari[0] == SP->CHIP_AMHIT || mAtari[0] == SP->CHIP_KGHIT || ISGAMENGAI(mAtari[0])){ 
					mSpY = 0;
					mSpX = (mMuki?1:-1)*UGOKUKISPX;
					mAccX = 0;
					mAccY = 0;
					if( mAtari[0] != SP->CHIP_KGHIT ) mY = mShirabe[0] - sMapAtHanteiY[0][0];
				}
				else{
					mAccY = SP->GRAVITY;
				}
				
				// �O
				if(mAtari[2] == SP->CHIP_HIT || mAtari[2] == SP->CHIP_GMNGAILT || mAtari[2] == SP->CHIP_GMNGAIRT || mAtari[2] == SP->CHIP_KGHIT ){ // �O�������Ă�
					mMuki = !mMuki;
				}
		} break;


	}

	Teki::Draw();

	mSpX += mAccX;
	mSpY += mAccY;
	mX	 += mSpX;
	mY	 += mSpY;


}

/*
	ϯ�߂Ƃ̓����蔻����s���܂��B
	���̊֐��̎��s���A���̕ϐ��̒��g���ς��܂��F
	mShirabe[]
	mAtari[]
*/
void UgokuKi::MapAtHt()
{
	MAP_SUPERATHT(mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, 
		sMapAtHanteiX, sMapAtHanteiY, mSizeX, mSizeY, mAtari, mShirabe);
}


void UgokuKi::CollisionResponse(Collidable* rCollObject, int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	if(jiki){ //������I
		if(rThisGroupId == SP->GRID_HANTEN && rOpGroupId == SP->GRID_HANTEN){

			// ���@�Ɠ��������ɕ����Ă���ꍇ�͗�O
			if( mMuki != GAMECONTROL->GetJiki()->GetMuki() )
				GAMECONTROL->GetJiki()->HantenOrRebound();
			}

		else if( rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_BOGYO ){
			Die();
		}
	}
}