#include "LightKobito.h"
#include "..\\..\\Management\\GameControl.h"
#include "Majo.h"

LightKobito::LightKobito()
{
	Init();
}

LightKobito::LightKobito(Majo* rParent)
{
	Init();
	mParent = rParent;
}

void LightKobito::Init()
{
	mStatus = WALK;
	mParent = NULL;
	LKOBITO_JTK = GF("LKOBITO_JTK");
	LKOBITO_BOUNDTK1 = GF("LKOBITO_BOUNDTK1");
	LKOBITO_BOUNDTK2 = GF("LKOBITO_BOUNDTK2");

	mSizeX = GI("LKOBITO_SX");
	mSizeY = GI("LKOBITO_SY");

	mX = GI("LKOBITO_ENTX");
	mY = GI("LKOBITO_ENTY");

	// ìñÇΩÇËîªíËóp
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, 44, 10, 22);
	AddCircle(0, SP->GRID_BOGYO, 44, 54, 22);

}

LightKobito::~LightKobito()
{}

void LightKobito::RunTask()
{
	LightResponseAble::RunTask();
	Collidable::RunTask();
}

/*
	óéâ∫
*/
void LightKobito::Fall()
{
	if( mStatus == WALK ){
		mStatus = FALL;
		mAccY = SP->GRAVITY;
		mSpY = -sqrt( LKOBITO_JTK * 2.0 * SP->GRAVITY );
	}
}

/*
	ñÇèóÇ™éÄÇÒÇæÇÁÅAëñÇÈ
*/
void LightKobito::_Move()
{
	if( mParent && mParent->GetStatus() == Majo::DIYING ){
		mSpX = -GF("LKOBITO_FSPX");
	}
}

/*
	éÄñS
*/
void LightKobito::DieIfGamenGai()
{
	if( mX + mSizeX <= 0 || mY > SP->SCRSZY ){
		mParent->KobitoDied();
		GAMECONTROL->GetMobManager()->Remove(this);
	}
}

/*
	ñÇèóÇ∆ÇÃÇ†ÇΩÇËîªíË
*/
void LightKobito::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	Majo* majo = dynamic_cast<Majo*>(rCollObject);

	if( majo && majo->GetStatus() != Majo::DIYING ){
		majo->InflictDamage();

		// íµÇÀï‘ÇÈ
		mSpY = majo->GetEntPt() >=3 ? 
			-sqrt( LKOBITO_BOUNDTK1 * 2.0f * SP->GRAVITY ): 
			-sqrt( LKOBITO_BOUNDTK2 * 2.0f * SP->GRAVITY );
	}
}