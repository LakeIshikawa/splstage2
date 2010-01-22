#include "Arrow.h"

Arrow::Arrow(int rX, int rY, int rMtX, int rMtY)
{

	ARROWSX = GI("ARROWSX");
	ARROWSY = GI("ARROWSY");

	ARROWSPXDIV = GF("ARROWSPXDIV");
	ARROWMAXSPY = GF("ARROWMAXSPY");

	ARROWSHMTTIME = GF("ARROWSHMTTIME");

	mX = rX;
	mY = rY;

	mSizeX = ARROWSX;
	mSizeY = ARROWSY;

	mMtX = rMtX;
	mMtY = rMtY;

	mAccY = SP->GRAVITY;

	mStatus = NORMAL;

	mAngle = 0.0f;

	mShoumetsuTimer = 0.0f;

	// ‰‘¬‚ðŒvŽZ‚·‚é
	float sax = mMtX - mX;
	float say = mMtY - mY;

	mSpX = sax/ARROWSPXDIV;
	mSpY = ((float)say * fabs(mSpX) / fabs((float)sax)) - fabs((float)sax)*SP->GRAVITY/(2.0*fabs(mSpX));

	if(mSpY>ARROWMAXSPY) mSpY = ARROWMAXSPY;

	// “–‚½‚è”»’è
	AddFrame(0);
	AddMovableCircle(0, SP->GRID_BOGYO, 0, 6, 6, 6);

	AddTarget( GAMECONTROL->GetJiki() );
	
}

Arrow::~Arrow(void)
{
}
 
void Arrow::Move()
{
	switch( mStatus ){

		case NORMAL: {
			// ‰ñ“]Šp“x‚ðŒvŽZ‚·‚é
			if(mSpX!=0){
				mAngle = atan(mSpY/mSpX);
				if(mSpX<0) mAngle += D3DX_PI;
			}
			else mAngle = mSpY>0?D3DX_PI/2:3*D3DX_PI/2;


			// “–‚½‚è”»’è‰~‚ÌˆÊ’u‚ð’²®
			float sakippox = ARROWSX/2 + cos(mAngle)*(ARROWSX/2 - 6);
			float sakippoy = ARROWSY/2 + sin(mAngle)*(ARROWSX/2 - 6);
			SetCircle(0, 0, sakippox, sakippoy, 6);

			int sakippo_sasare_x = ARROWSX/2 + cos(mAngle)*(ARROWSX/2 - 8);
			float sakippo_sasare_y = ARROWSY/2 + sin(mAngle)*(ARROWSX/2 - 8);

			//Žh‚³‚é”»’è
			int chip = MAP_ATHT( mX + sakippo_sasare_x, mY + sakippo_sasare_y );
			if( chip == SP->CHIP_HIT || chip == SP->CHIP_AMHIT ) {
				mStatus = SASARE;
				mSpX = 0;
				mSpY = 0;
				mAccY = 0;
			}

			DX_SCROLL_ROT_DRAW("graphics\\teki\\arrow.png", mX, mY, 0, 0, ARROWSX, ARROWSY, mAngle);

			break;
		}

		case SASARE:
			DX_SCROLL_ROT_DRAW("graphics\\teki\\arrow.png", mX, mY, 0, 0, ARROWSX - 8, ARROWSY, mAngle);
			WAIT_TIMER( mShoumetsuTimer, ARROWSHMTTIME )
				GAMECONTROL->GetMobManager()->Remove(this);
			WAIT_END
			break;
	}

	DieIfGamenGai();

	mSpX += mAccX;
	mSpY += mAccY;
	mX += mSpX;
	mY += mSpY;

}

void Arrow::CollisionResponse(ICollidable* rCollObject, int rThisGroupId, int rOpGroupId)
{
	if( mStatus == NORMAL ){
		Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

		if(jiki){ //“–‚½‚èI
			if( rOpGroupId == SP->GRID_BOGYO && rThisGroupId == SP->GRID_BOGYO ){
				GAMECONTROL->GetJiki()->InflictDamage();
			}
		}
	}
}