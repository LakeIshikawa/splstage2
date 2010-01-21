#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Thorn.h"
#include "..\\..\\..\\TrumpSoldier.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Jiki\\Jiki.h"

/************************************************************//**
*�@�ݒ�萔��ǂݍ���
****************************************************************/
Thorn::Thorn(int rX, int rY, float rSp)
{
	// �ʒu
	mSizeX = GI("THORNSX");
	mSizeY = GI("THORNSY");

	mX = rX;
	mY = rY;

	mSpeed = rSp;

	// �����蔻��
	AddFrame(0);
	AddIndexedRect(0, SP->GRID_KOUGEKI, 0, 0, 0, mSizeX, mSizeY);
	AddTarget(GAMECONTROL->GetJiki());

	// �������g�����v�������ޯĂɓo�^
	GAMECONTROL->GetMobManager()->AddAsTargetToAllOf<TrumpSoldier>(this);

	// ������
	mHeight = 0;
	
	// SE
	GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_boss3_toge.wav");


}

/************************************************************//**
*	1�ڰя���
****************************************************************/
void Thorn::Move()
{
	mHeight += mSpeed;
	
	// ���_
	if( mHeight >= mSizeY ){
		mHeight = mSizeY;
		mSpeed *= -1;
	}
	if( mHeight <=0 && mSpeed <0 ){
		GAMECONTROL->GetMobManager()->Remove(this);
	}

	// �����蔻��𒼂�
	((Rect*)(pCollision->GetCurFrame()->GetIndexedShape(0)))->SetTop(-mHeight);
	((Rect*)(pCollision->GetCurFrame()->GetIndexedShape(0)))->SetBottom(0);

	Draw();
}

/************************************************************//**
*	�`��
****************************************************************/
void Thorn::Draw()
{
	DX_DRAW("graphics\\teki\\queen\\boss4_thorn.png", 
		mX, mY-mHeight, 0, 0, mSizeX, mHeight);
}

/************************************************************//**
*	�����蔻��̉���
****************************************************************/
void Thorn::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// �۲�
	if( jiki && rOpGroupId == SP->GRID_BOGYO  || rOpGroupId == SP->GRID_KOUGEKI ){
		jiki->InflictDamage();
	}
}

