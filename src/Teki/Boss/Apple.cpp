#include "Apple.h"
#include "..\\..\\Management\\GameControl.h"

Map::HITPOINT Apple::sMapPointX =
{
	{ 20, -1 },	//下
	{ -1 },		//上
	{ -1 },		//前
	{ -1 }		//後
};

Map::HITPOINT Apple::sMapPointY =
{ 
	{ 36, -1 },	//下
	{ -1 },		//上
	{ -1 },		//前
	{ -1 }		//後
};


Apple::Apple(int rXPx, int rYPx)
{

	APPLESZX = GI("APPLESZX");
	APPLESZY = GI("APPLESZY");

	APPLE_BRTM = GF("APPLE_BRTM");

	mSizeX = APPLESZX;
	mSizeY = APPLESZY;

	mX = rXPx;
	mY = rYPx;
	mZ = 1.0f;

	mNo = 0;
	mTimer = 0.0f;
	mBaseStatus = NORMAL;

	// あたり判定
	AddFrame(FR_NORMAL);
	AddCircle(FR_NORMAL, SP->GRID_BOGYO, 20, 20, 15);

	AddFrame(FR_DISABLE);

	SetCurFrame(FR_DISABLE);

}

Apple::~Apple()
{}

/*
	メイン処理
*/
void Apple::Move()
{
	switch( mBaseStatus ) {
		case NORMAL:

		// 床との当たり判定
		DetSpAccPos();
		MapAtHt();
		Draw();
		DieIfGamenGai();
		break;

		case BROKE:
			mTimer += SP->FrameTime;
			if( mTimer >= APPLE_BRTM && mAtari[0] == SP->CHIP_AMHIT){
				GAMECONTROL->GetMobManager()->Remove(this);
			}
			DetSpAccPos();
			MapAtHt();
			Draw();
			break;
	}
}

int Apple::GetSizeX()
{
	return APPLESZX;
}

/*
	重力をつけて落とす
*/
void Apple::Fall()
{
	mAccY = SP->GRAVITY;
}

/*
	りんごが地面に落ちてるかどうかを取得
*/
bool Apple::IsHittingGround()
{
	return ( mAtari[0] == SP->CHIP_HIT || mAtari[0] == SP->CHIP_AMHIT );
}

/*
	マップとの当たり判定
*/
void Apple::MapAtHt()
{
	MAP_SUPERATHT(mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, 
		sMapPointX, sMapPointY, APPLESZX, APPLESZY, mAtari, mMapKabe);

	if( IsHittingGround() )
	{
		mAccY = 0;
		mSpY = 0;
		mY = mMapKabe[0] - sMapPointY[0][0];
	}

}

/*
	位置、速度と加速を再計算する
*/
void Apple::DetSpAccPos()
{
	mSpX += mAccX;
	mSpY += mAccY;
	mX += mSpX;
	mY += mSpY;
}

/*
	描画
*/
void Apple::Draw()
{
	DX_DRAW("graphics\\teki\\apple.png", mX, mY, mNo*APPLESZX, 0, (APPLESZX)*(mNo+1), APPLESZY);
}

/*
	自機との当たり判定
*/
void Apple::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	if( mBaseStatus == BROKE ) return;

	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	if( jiki && rOpGroupId == SP->GRID_BOGYO ){
		jiki->InflictDamage();
		mNo = 1;
		mBaseStatus = BROKE;
	}
	else if ( jiki && rOpGroupId == SP->GRID_KOUGEKI ){
		mNo = 1;
		mBaseStatus = BROKE;
		// SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kougekimeityuu.wav");
	}
}

/*
	当たり判定を無効に
*/
void Apple::DisableCollision()
{
	SetCurFrame(FR_DISABLE);
}

/*
	当たり判定を有効に
*/
void Apple::EnableCollision()
{
	SetCurFrame(FR_NORMAL);
}