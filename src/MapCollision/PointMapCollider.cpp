#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "PointMapCollider.h"
#include "..\\Management\\GameControl.h"
#include "..\\Mob\\Movable.h"

/************************************************************//**
*	�W���ݽ�׸�
****************************************************************/
PointMapCollider::PointMapCollider( Movable* rTarget ) : mTarget( rTarget )
{
	// ���ׂĂ̓_��-1�ɏ�����
	for( int i=MCSD_DOWN; i<=MCSD_BACK; i++){
		for( int j=0; j<MAX_TEN; j++){
			mCollisionPointsX[i][j] = -1;
			mCollisionPointsY[i][j] = -1;
		}
	}
}

/************************************************************//**
*	�W���޽�׸�
****************************************************************/
PointMapCollider::~PointMapCollider()
{
}

/************************************************************//**
*	\param rSide ���ׂ����
*	\return ���ׂ������̂����葮��(SP->CHIP_XXX)
****************************************************************/
int PointMapCollider::GetCollision(MapCollider::MC_SIDE rSide) {
	return mAtari[rSide];
}

/************************************************************//**
*	\param rSide ���ׂ����
*	\return �w�肳�ꂽ�����̓����葮����[MCCG_NONE]�ȊO�̏ꍇ,
*			���������Ƃ���̏C�����ꂽ���W��Ԃ��B
*			�w��������u���A��v�̏ꍇ�AY���W���Ԃ���܂��B
*			�w��������u�E�A���v�̏ꍇ�AX��΍��W���Ԃ���܂��B
*
*	�w�肳�ꂽ�������uMCG_NONE�v�̏ꍇ�A�Ԃ����l�����m��ł��B
*
*	\note �C�����ꂽ�ʒu�́A���̨���̍�������ے����Ă��܂��B
*		  ���̂܂܁AmY = [collider]->GetAdjustedPosition( MCSD_DOWN )
*		  �̂悤�Ɏg���Ă��������B
****************************************************************/
int PointMapCollider::GetAdjustedPosition(MapCollider::MC_SIDE rSide) {

	switch( rSide ){

		case MCSD_DOWN: 
		case MCSD_UP:
			return mShirabe[rSide] - mCollisionPointsY[rSide][0];  break;

		case MCSD_FRONT:
		case MCSD_BACK:
			if( mTarget->GetMuki() == 0 ){ //�E����
				return mShirabe[rSide] - mCollisionPointsX[rSide][0]; break;
			}
			else{ // ������
				return mShirabe[rSide] - (mTarget->GetFrameSizeX() - mCollisionPointsX[rSide][0]);
			}

		default:
			GAMECONTROL->ThrowError("GetAdjustedPosition(%d)�͖��Ӗ��ȎQ�Ƃł�", rSide);
			return -1;
	}
}

/************************************************************//**
*	�����蔻����s���܂��B
*	�����̂��߁A1�ڰтɈ�񂱂̃��\�b�h���ĂԂ��Ƃ����z�I����
*`	�v���܂��B
****************************************************************/
void PointMapCollider::CollisionRecognition() {
	MAP_SUPERATHT(mTarget->GetX(), mTarget->GetY(), mTarget->GetMuki(), 
		mTarget->GetSpX(), mTarget->GetSpY(), mTarget->GetAccX(), mTarget->GetAccY(), 
		mCollisionPointsX, mCollisionPointsY, mTarget->GetFrameSizeX(), mTarget->GetFrameSizeY(), 
		mAtari, mShirabe);
}

/************************************************************//**
*	\param side ���̓_�̏���������
*	\param rX �_��X(���̨���̉E��������_)
*	\param rY �_��Y(���̨���̉E��������_)
****************************************************************/
void PointMapCollider::AddCollisionPoint(MapCollider::MC_SIDE rSide, int rX, int rY) {

	// �󂢂Ă�Ƃ���T��
	int curidx = -1;
	while( mCollisionPointsX[rSide][++curidx] != -1 );

	mCollisionPointsX[rSide][curidx] = rX;
	mCollisionPointsY[rSide][curidx] = rY;
}

