#include "AshibaMovable.h"
#include "..\\Management\\GameControl.h"

/**
	�W���R���X�g���N�^
*/
AshibaMovable::AshibaMovable(int rXPx, int rYPx, float rZ, string graphic, int sizex, int sizey) : 
Ashiba(rXPx, rYPx, rZ, graphic, sizex, sizey)
{
	ZeroMemory(route, sizeof(route));

	mHaichiX = rXPx;
	mHaichiY = rYPx;

	AddRoutePoint(0, rXPx, rYPx);

	ASHIBAMOV_SP = GF("ASHIBAMOV_SP");

	mLooping = false;

	Reset();
}

/**
	�W���f�X�g���N�^
*/
AshibaMovable::~AshibaMovable()
{
	for each (RoutePoint* r in route){
		if( r )	delete r;
	}
}

/************************************************************//**
*	�ړ����s���܂��BmLooping�ɂ��A�Ō�̃m�[�h��ʉ߂���
*	����Ԗڂɖ߂邩�o�b�N�Ŗ߂邩�����܂�܂��B
****************************************************************/
void AshibaMovable::Move()
{
	// �ړ�
	if( HasArrived() ){
		GoToNext();
	}
	_Move();

	Ashiba::Move();
}

/************************************************************//**
*	�m�[�h�̒ǉ�
****************************************************************/
void AshibaMovable::AddRoutePoint(int card, int rX, int rY)
{
	route[card] = new RoutePoint(rX, rY);
}

/************************************************************//**
*	\param rOnOff �I��->���ꂪ���[�v���ď����l�ɖ߂�\n
*				  �I�t->�o�b�N���Ė߂�
****************************************************************/
void AshibaMovable::SetLooping(bool rOnOff)
{
	mLooping = rOnOff;
}

/************************************************************//**
*	\return ٰ�ߗp��ɰ�ޔԍ�
****************************************************************/
int AshibaMovable::GetLoopNodeIdx()
{
	if( this == GAMECONTROL->GetStageManager()->GetCurrentStage()
		->GetHaichi()->GetAshibaMov(0) ){
			return 0xF;
	}
	else return 0x10;
}

/************************************************************//**
*	���̃m�[�h�܂ňړ�����
****************************************************************/
void AshibaMovable::_Move()
{
	// �ړ�
	RoutePoint* curRp = route[mCurRPoint];

	float sax = curRp->X - mX;
	float say = curRp->Y - mY;
	
	// ����
	float length = sqrt(sax*sax + say*say);
	if( length != 0 ){
		// nomalize
		mSpX = (sax / length) * ASHIBAMOV_SP;
		mSpY = (say / length) * ASHIBAMOV_SP;
	}
	
	mX += mSpX;
	mY += mSpY;
}

/************************************************************//**
*	���̃m�[�h�ɐ؂�ւ���
****************************************************************/
void AshibaMovable::GoToNext()
{
	// �o�b�N�̏ꍇ�̓}�C�i�X
	if( mBacking ){
		mCurRPoint--;
	}
	else{
		mCurRPoint++;
	}

	// �Ō�ɓ���

	// �o�b�N�̓���
	if( mBacking && mCurRPoint <= -1 ){
		mBacking = false;
		mCurRPoint = 0;
		return;
	}

	// �O�i�̓���
	// -- ���[�v�̓���

	// --- �p�X�͈̔͂���͂ݏo������
	if( mCurRPoint >= GetLoopNodeIdx()+1 ){
		// --- ���[�v���Ă���킯������A�ŏ��̃m�[�h��
		mCurRPoint = 0;
	}

	// -- ���i�̓���
	// --- ���ꂩ���A�m�[�h���Ȃ�������
	else if( route[mCurRPoint] == NULL ){
		if( mLooping ){
			// --- �Ō�̑���Ɉړ�
			mCurRPoint = GetLoopNodeIdx();
		}
		else{
			// --- ���[�v����Ȃ��A��i����
			mCurRPoint-=2;
			if( mCurRPoint < 0 ) mCurRPoint = 0;
			mBacking = true;
		}
	}
}

/************************************************************//**
*	�����̔���
*	@return ����������
****************************************************************/
bool AshibaMovable::HasArrived()
{
	RoutePoint* curRp = route[mCurRPoint];

	// ���E�ւɍs��������
	if( mSpX > 0 && mX >= curRp->X ) return true;
	if( mSpX < 0 && mX <= curRp->X ) return true;

	// �㉺�ɍs��������
	if( mSpY > 0 && mY >= curRp->Y ) return true;
	if( mSpY < 0 && mY <= curRp->Y ) return true;

	return false;

}

/************************************************************//**
*	�ď�����
*	�z�u�̏�Ԃɖ߂��B
****************************************************************/
void AshibaMovable::Reset()
{
	mX = mHaichiX;
	mY = mHaichiY - ASHIBASY + SP->CHSZY;

	mCurRPoint = 0;
	mBacking = false;
}
