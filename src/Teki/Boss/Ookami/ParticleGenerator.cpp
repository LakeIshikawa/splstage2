#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ParticleGenerator.h"
#include "..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*	”j•Ð‚Ì”­ŽË‚ð“o˜^‚µ‚Ü‚·
*	\param rAngle ”­ŽË‚Ì‰Šp“x
*	\param rSpeed ‘¬“x
*	\param rInterval ŽŸ‚Ì”­ŽË‚Ü‚Å‚ÌŽžŠÔ
*	\param rGraphicScr Žg—p‚·‚é¸Þ×Ì¨¯¸‚ÌÌ§²Ù–¼
****************************************************************/
void ParticleGenerator::BookPartThrow(float rAngle, float rSpeed, 
			float rInterval, string rGraphicSrc)
{
	mData.push_back(PartThrow(rAngle, rSpeed, rInterval, rGraphicSrc));
}

/************************************************************//**
*	”­ŽËÓ°ÄÞ‚ðÝ’è‚µ‚Ü‚·
****************************************************************/
void ParticleGenerator::SetMode(PG_MODE rMode)
{
	mMode = rMode;
}

/************************************************************//**
*	1ÌÚ°Ñˆ—
*	”j•Ð‚ð‘±X‚Æì¬‚µ‚Ä”ò‚Î‚·B”j•Ð‚ÌŠ‘®‚ÍMobController‚Æ‚È‚é
****************************************************************/
void ParticleGenerator::Generate()
{
	// ‚Ü‚¾”­ŽË‚µ‚Ä‚¢‚È‚¯‚ê‚Î”­ŽË‚·‚é
	if( !mData[mCurPartIdx].thrown ){
		mData[mCurPartIdx].thrown = true;
		Particle* newpart = 
			new Particle(mData[mCurPartIdx].angle, mData[mCurPartIdx].speed, 
			mData[mCurPartIdx].graphic, mX, mY);

		GAMECONTROL->GetMobManager()->Request(newpart, true);
	}

	// ŽŸ‚Ì”j•Ð‚Ü‚Å‘Ò‚Â
	WAIT_TIMER(mTimer, mData[mCurPartIdx].interval)
		switch( mMode ){
			case PG_LINEAR:
				{
					mCurPartIdx++;
					if( mCurPartIdx >= mData.size() ) {

						//‘S”j•ÐƒŠƒZƒbƒg
						for (int i=0; i<mData.size(); i++) mData[i].thrown = false;
						mCurPartIdx = 0;
					}
					break;
				}

			case PG_RANDOM:
				{
					mData[mCurPartIdx].thrown = false;
					mCurPartIdx = rand()%(mData.size());
					break;
				}
	}
	WAIT_END
}



/************************************************************//**
*	‰Šú‰»
****************************************************************/
Particle::Particle(float rAngle, float rSpeed, string rGraphic, 
		int rStartX, int rStartY)
{
	mX = rStartX;
	mY = rStartY;
	mSpX = cos(rAngle) * rSpeed;
	mSpY = sin(rAngle) * rSpeed;
	mGraphic = rGraphic;
	mSizeX = GI("OOKAMI_HSPTSX");
	mSizeY = GI("OOKAMI_HSPTSY");
	OOKAMI_HSPTROTSP = GF("OOKAMI_HSPTROTSP")*((rand()%2)==0?1:-1);

	mRotAngle = 0.0f;

	// “–‚½‚è”»’è
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, 24, 24, 24);
	AddTarget(GAMECONTROL->GetJiki());

}

/************************************************************//**
*	1ÌÚ°Ñˆ—
****************************************************************/
void Particle::Move()
{
	// ‰æ–ÊŠO‚ÍÁ–Å‚·‚é
	DieIfGamenGai();

	// “®‚«
	mSpY += SP->GRAVITY;
	mX += mSpX;
	mY += mSpY;

	// ‰ñ“]
	mRotAngle += OOKAMI_HSPTROTSP;
	if( mRotAngle >= D3DX_PI*2 ) mRotAngle = 0.0f;

	//•`‰æ
	DX_SCROLL_ROT_DRAW(mGraphic, mX, mY, 0, 0, mSizeX, mSizeY, mRotAngle);
}


/************************************************************//**
*	“–‚½‚è”»’è‰ž“š
****************************************************************/
void Particle::CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);
	jiki->InflictDamage();
}
