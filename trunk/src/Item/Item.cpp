#include <string>
#include <vector>
#include <exception>
#include <stdarg.h>
using namespace std;

#include "PickUpEffect.h"
#include "Item.h"
#include "..\\Management\\GameControl.h"

/************************************************************//**
*	�W���R���X�g���N�^
****************************************************************/
Item::Item( int rX, int rY )
{
	mSizeX = GI("ITEMSX");
	mSizeY = GI("ITEMSY");
	mX = rX;
	mY = rY - mSizeY + SP->CHSZY;
	
	mMuki = false;

	// �����蔻��
	AddFrame(0);
	AddCircle( 0, SP->GRID_BOGYO, mSizeX/2, mSizeY/2, mSizeX/2 );
	AddTarget( GAMECONTROL->GetJiki() );

	// ϯ�߂����蔻��
	mMapCollider = new PointMapCollider( this );
	mMapCollider->AddCollisionPoint( MapCollider::MCSD_DOWN, mSizeX/2, mSizeY );
	mMapCollider->AddCollisionPoint( MapCollider::MCSD_FRONT, mSizeX, 0 );
}

/************************************************************//**
*	�W���f�X�g���N�^
****************************************************************/
Item::~Item()
{}

/************************************************************//**
*	�X�V�ƕ`��
****************************************************************/
void Item::Move()
{
	mMapCollider->CollisionRecognition();

	// ������
	if( mMapCollider->GetCollision(MapCollider::MCSD_DOWN) == SP->CHIP_AMHIT ){
		mY = mMapCollider->GetAdjustedPosition(MapCollider::MCSD_DOWN);
		mSpY = 0;
		mAccY = 0;
		mSpX = 0;
	}
	else mAccY = SP->GRAVITY;

	// �ǂɓ�����
	if( mMapCollider->GetCollision(MapCollider::MCSD_FRONT) == SP->CHIP_HIT ){
		mSpX = 0;
	}

	mSpY += mAccY;
	mSpX += mAccX;
	mX += mSpX;
	mY += mSpY;

	// �`��
	DX_SCROLL_DRAW( GetGraphic(), mX, mY, 0, 0, mSizeX, mSizeY );
	CustomEffect();
}

/************************************************************//**
*	������
****************************************************************/
void Item::Launch(float rSpX, float rSpY, bool rMuki)
{
	mMuki = rMuki;
	mSpY = rSpX;
	mSpX = rSpY*(rMuki?1:-1);
}


/************************************************************//**
*	�W���̓����蔻��\n
*
*	�q���C��������Ώۂ���B
*	
*	\param rCollObject	����������̵�޼ު��(��F�۲�)
*	\param rThisGroupId	��������GROUPID(���X�ɂ���ĈႤ)
*	\param rOpGroupId	����������̵�޼ު�Ă�GROUPID(���X�ɂ���ĈႤ)
*
****************************************************************/
void Item::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	if(jiki && rOpGroupId == SP->GRID_BOGYO ){

		//SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_item_get.wav");
		// ����
		DoEffect();
		// ����
		GAMECONTROL->GetMobManager()->Remove(this);
		// ���o
		GAMECONTROL->GetMobManager()->Request( new PickUpEffect( GetEffectGraphic() ), true );
		
	}
}