#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Trump.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Jiki\\Jiki.h"
#include "..\\..\\..\\TrumpSoldier.h"
#include "Chandelier.h"
#include "..\\Actions\\ASQueenTrumpsAttack.h"

/************************************************************//**
*�@�ݒ�萔��ǂݍ���
****************************************************************/
Trump::Trump(int rX, int rY, string rGraphic, int rZ, int rRow, ASQueenTrumpsAttack* rParent) 
	: mGraphic( rGraphic ), mRow(rRow), mParent(rParent)
{
	FLOORY = GI("FLOORY");
	TRUMPTOPY = GI("TRUMPTOPY");
	STD_FADEIN_SP = GF("STD_FADEIN_SP");

	// �ʒu
	mSizeX = GI("TRUMPSX");
	mSizeY = GI("TRUMPSY");

	mX = rX;
	mY = rY;
	mZ = 1.0 + rZ;

	// �����蔻��
	AddFrame(0);
	AddIndexedRect(0, SP->GRID_KOUGEKI, 0, 0, 0, mSizeX, mSizeY);
	AddTarget(GAMECONTROL->GetJiki());

	// ������
	mStatus = WAIT;
	mSpX = 0;
	mSpY = 0;
	mAlpha = 0.0f;
	mTimer = 0.0f;
}

/************************************************************//**
*	1�ڰя���
****************************************************************/
void Trump::Move()
{
	
	switch( mStatus ){
	
	case WAIT:
		WAIT_TIMER(mTimer, mZ/2.0f)
			mStatus = APPEAR;
		WAIT_END
		break;

	case APPEAR:
		// ̪��޲�
		if( mAlpha < 1.0f ){
			mAlpha += STD_FADEIN_SP;
		}
		else{
			//����
			mStatus = THROW;
			mSpY = GF("TRUMPSHOSP");
		}
		break;

	case THROW:
		{
			int rowX[] = { GI("TRUMPROW1"), GI("TRUMPROW2"), GI("TRUMPROW3"), GI("TRUMPROW4") };
			if( mY <= TRUMPTOPY ){
				// ����
				mX = rowX[mRow];
				mSpY = GF("TRUMPFALLSP");
				mStatus = FALL;
			}
			break;
		}

	case FALL:
		if( HasFallen() ) {
			TransformToSoldier(mParent->GetChandelier());
			mParent->TrumpHasFallen(this);
		}
		break;
	}

	// �ʒu�֌W
	mX += mSpX;
	mY += mSpY;

	// �`��
	Draw();
}

/************************************************************//**
*	�`��
****************************************************************/
void Trump::Draw()
{
	DX_DRAWALPHA(mGraphic, mX, mY, 0, 0, mSizeX, mSizeY, mAlpha);
}

/************************************************************//**
*	�����蔻��̉���
****************************************************************/
void Trump::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// �۲�
	if( jiki && rOpGroupId == SP->GRID_BOGYO  || rOpGroupId == SP->GRID_KOUGEKI ){
		jiki->InflictDamage();
	}
}


/************************************************************//**
*	�g�����v���ɕϐg����
****************************************************************/
void Trump::TransformToSoldier(Chandelier* rChandelier)
{
	// SE
	GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_boss3_hart.wav");

	// ����
	GAMECONTROL->GetMobManager()->Remove(this);

	// ����ߕ��ɂȂ�
	TrumpSoldier* ts;
	if( mGraphic.compare("graphics\\teki\\queen\\boss4_card0.png") == 0 ) ts = new TrumpSoldierHearts( mX, FLOORY );
	else if( mGraphic.compare("graphics\\teki\\queen\\boss4_card1.png") == 0 ) ts = new TrumpSoldierDiamonds( mX, FLOORY );
	else if( mGraphic.compare("graphics\\teki\\queen\\boss4_card2.png") == 0 ) ts = new TrumpSoldierClovers( mX, FLOORY );
	else if( mGraphic.compare("graphics\\teki\\queen\\boss4_card3.png") == 0 ) ts = new TrumpSoldierSpades( mX, FLOORY );
	

	ts->AddTarget( rChandelier );
	ts->Build();
	GAMECONTROL->GetMobManager()->Request( ts, true );

}

/************************************************************//**
*	\return �����Ă��邩
****************************************************************/
bool Trump::HasFallen()
{
	return mY+mSizeY >= FLOORY;
}