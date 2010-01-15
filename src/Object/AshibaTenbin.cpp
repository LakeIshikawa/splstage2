#include <exception>
using namespace std;

#include "AshibaTenbin.h"
#include "..\\Management\\GameControl.h"

char* AshibaTenbin::mGraphicData[2] = 
{
	"graphics\\object\\ashibatenbinL.png",
	"graphics\\object\\ashibatenbinR.png"
};

/************************************************************//**
*	�W���R���X�g���N�^
****************************************************************/
AshibaTenbin::AshibaTenbin(int rXPx, int rYPx, float rZ)
{
	TENASHIBASX = GI("TENASHIBASX");
	TENASHIBASY = GI("TENASHIBASY");
	TENBIN_DFOR = GF("TENBIN_DFOR");
	TENASHIBA_MAXSP = GF("TENASHIBA_MAXSP");
	TENASHIBA_MAXSA = GI("TENASHIBA_MAXSA");
	TENASHIBA_BACKSP = GI("TENASHIBA_BACKSP");

	mZ = rZ;

	mGrapIdx = 0;

	AddTarget(GAMECONTROL->GetJiki());

	AddFrame(0);
	AddIndexedRect(0, SP->GRID_BOUND, 0, 0, 565, 
		TENASHIBASX, TENASHIBASY);

	mHaichiX = rXPx;
	mHaichiY = rYPx - TENASHIBASY + SP->CHSZY;

	Reset();
}

/************************************************************//**
	�W���f�X�g���N�^
****************************************************************/
AshibaTenbin::~AshibaTenbin()
{}

/************************************************************//**
*	@return ���̑��ꂪ�������Ă�V��
****************************************************************/
Tenbin* AshibaTenbin::GetTenbin() {
	return mParent;
}

/************************************************************//**
*	�����I�ɏ㏸����
****************************************************************/
void AshibaTenbin::BringUp() {
	mStatus = UP;
}

/************************************************************//**
*	�����I�ɗ�������
****************************************************************/
void AshibaTenbin::BringDown() {
	mStatus = DOWN;
}

/************************************************************//**
*	�Î~(�z�u)��Ԃɖ߂�
****************************************************************/
void AshibaTenbin::BringBack() {
	if( mStatus == STOP || mStatus == BACK ) return;

	mStatus = BACK;

	// ���݈ʒu�ƐÎ~��Ԃ̈ʒu���擾����
	float say = mY - mHaichiY;

	if( say > 0 ){
		mBreakFl = -1; // ��������
	}
	else{
		mBreakFl = 1; // ��������
	}
}

/************************************************************//**
*	\return ����Ă�����̂̐�
****************************************************************/
int AshibaTenbin::GetRidersNum() {
	return mRiders.size();
}

/************************************************************//**
*	\param rLeftRight 0-������̸��̨�� 1-�E������̨��
****************************************************************/
void AshibaTenbin::SetGraphic(int rLeftRight) {
	mGrapIdx = rLeftRight;
}

/************************************************************//**
*	�ď�����
*	�z�u�̏�Ԃɖ߂��B
****************************************************************/
void AshibaTenbin::Reset()
{
	mX = mHaichiX;
	mY = mHaichiY;
	mBreakAcc = 0;
	mBreakFl = false;

	mStatus = STOP;
}


/************************************************************//**
*	�����ƕ`��̏���
****************************************************************/
void AshibaTenbin::Move()
{

	// ����
	switch( mStatus ){

		// �Î~
		case STOP:
			mAccY = 0;
			mSpY = 0;
			break;

		// ����
		case DOWN:
			mAccY = TENBIN_DFOR;
			break;

		// �㏸
		case UP:
			mAccY = -TENBIN_DFOR;
			break;
		
		// �߂�
		case BACK:

			// ���݈ʒu�ƐÎ~��Ԃ̈ʒu���擾����
			float say = mY - mHaichiY;

			// ���݈ʒu���u���v�̏ꍇ
			if( say > 0 ){
				// -- ��������Ɍ�������
				if( mBreakFl == 1 ){
					Reset();
				}
			}
			// ���݈ʒu���u��v�̏ꍇ
			else{
				// -- ���������Ɍ�������
				if( mBreakFl == -1 ){
					Reset();
				}
			}

			// �����̍X�V
			mSpY = (TENASHIBA_BACKSP) * mBreakFl;
			mAccY = 0;
			break;
	}

	mSpY += mAccY;

	// ���x���
	if( mSpY > TENASHIBA_MAXSP ){
		mSpY = TENASHIBA_MAXSP;
	}

	mY += mSpY;

	// ����ʒu
	// ���݈ʒu�ƐÎ~��Ԃ̈ʒu���擾����
	float say = mY - mHaichiY;
	if(( fabs(say) ) > TENASHIBA_MAXSA){
		mY = mHaichiY + TENASHIBA_MAXSA*(say>0?1:-1);
	}

	// ��q�̏���
	UpdateRiders();

	// �`��
	DX_SCROLL_DRAW(mGraphicData[mGrapIdx] ,mX, mY, 0, 0, 
		TENASHIBASX, TENASHIBASY);

	// �����蔻��g
	if(mDrawer){
		mDrawer->SetCollision(pCollision->GetCurFrame());
		mDrawer->Draw();
	}
}
