#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Heart.h"
#include "..\\..\\..\\TrumpSoldier.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Jiki\\Jiki.h"

/************************************************************//**
*�@�ݒ�萔��ǂݍ���
****************************************************************/
Heart::Heart(int rX, int rY, float rAngle) : mAngle( rAngle )
{
	HEARTSP = GF("HEARTSP");

	// �ʒu
	mSizeX = GI("HEARTSX");
	mSizeY = GI("HEARTSY");

	mX = rX - mSizeX/2;
	mY = rY - mSizeY/2;
	mSpX = cos( rAngle - D3DX_PI/2 ) * HEARTSP;
	mSpY = sin( rAngle - D3DX_PI/2 ) * HEARTSP;
	
	// �����蔻��
	AddFrame(0);
	AddIndexedRect(0, SP->GRID_KOUGEKI, 0, 0, 0, mSizeX, mSizeY);
	AddTarget(GAMECONTROL->GetJiki());

	// �g�����v��
	GAMECONTROL->GetMobManager()->AddAsTargetToAllOf<TrumpSoldier>(this);

	// ������
	
}

/************************************************************//**
*	1�ڰя���
****************************************************************/
void Heart::Move()
{
	DieIfGamenGai();
	Kaiten();

	// �ړ�
	mX += mSpX;
	mY += mSpY;

	// �`��
	Draw();
}
/************************************************************//**
*	��]����
****************************************************************/
void Heart::Kaiten()
{
	mAngle += GF("HEART_KAITENSP");
	if( mAngle >= D3DX_PI*2 ){
		mAngle = 0;
	}
}

/************************************************************//**
*	�`��
****************************************************************/
void Heart::Draw()
{
	DX_SCROLL_ROT_DRAW("graphics\\teki\\queen\\boss4_heart.png", 
		mX, mY, 0, 0, mSizeX, mSizeY, mAngle);
}

/************************************************************//**
*	�����蔻��̉���
****************************************************************/
void Heart::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// �۲�
	if( jiki && rOpGroupId == SP->GRID_BOGYO  || rOpGroupId == SP->GRID_KOUGEKI ){
		jiki->InflictDamage();
	}
}
