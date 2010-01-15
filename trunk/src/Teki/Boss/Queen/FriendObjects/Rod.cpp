#include <string>
#include <vector>
#include <exception>
#include <d3dx9.h>
using namespace std;

#include "Rod.h"
#include "Heart.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Jiki\\Jiki.h"
#include "..\\..\\..\\..\\Collision\\Circle.h"

/************************************************************//**
*　設定定数を読み込む
****************************************************************/
Rod::Rod(float rAngle, bool rDir) : mAngle( rAngle ), mStartAngle( rAngle ), mDir( rDir )
{
	RODSPANG = GF("RODSPANG");
	STD_FADEIN_SP = GF("STD_FADEIN_SP");

	// 位置
	mSizeX = GI("RODSX");
	mSizeY = GI("RODSY");

	mX = GI("RODX");
	mY = GI("RODY");

	// 初期化
	mStatus = APPEAR;
	mAlpha = 0.0f;
	mHeartShot = 0;

	AddFrame(0);
}

/************************************************************//**
*	1ﾌﾚｰﾑ処理
****************************************************************/
void Rod::Move()
{
	// ﾋﾛｲﾝとのあたり判定(:UGLY:)
	if( CollidesWithHeroine() ){
		CollisionResponse( GAMECONTROL->GetJiki(), 0, 0 );
	}
	
	// 挙動
	switch( mStatus ){
	
	case APPEAR:

		// ﾌｪｰﾄﾞｲﾝ
		if( mAlpha < 1.0f ){
			mAlpha += STD_FADEIN_SP;
		}
		else{
			//発射
			mStatus = ROTATE;
		}
		break;

	case ROTATE:
		{
			// 回転
			mAngle += (mDir?1.0:-1.0) * (RODSPANG*(D3DX_PI/180)) * SP->FrameTime;
			
			// ﾊｰﾄの発射
			if( fabs( mAngle - mStartAngle ) >= (RODSPANG*(D3DX_PI/180))*mHeartShot){
				mHeartShot++;
				GAMECONTROL->GetMobManager()->Request( 
					new Heart( mX+mSizeX/2 + (mSizeY-10)*cos( mAngle-D3DX_PI/2 ), 
						mY+(mSizeY-10) + (mSizeY-10)*sin( mAngle-D3DX_PI/2 ), 
						mAngle),
					true );
				// SE
				GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_boss1_atack.wav");
			}

			// 終了
			if( fabs(mAngle - mStartAngle) >= D3DX_PI*2 ){
				mStatus = DISAPPEAR;
			}
			break;
		}

	case DISAPPEAR:
		{
			mAlpha -= 0.1f;
			if( mAlpha <= 0.0f ){
				mAlpha = 0.0f;
				mStatus = INACTIVE;
			}
			break;
		}
	}

	// 描画
	Draw();
}

/************************************************************//**
*	ﾋﾛｲﾝとの当たり判定
*
*	:UGLY:
*	抽象性ない、使いまわしもない。　四角い判定で回転するものは
*	このゲームの中で、このロッドしかない。したがって、ロッド事態
*	のレベルでやっちゃいます。ﾋﾛｲﾝのあたり判定も重複さます。
*	
*	このメソッドだけ、いい子は絶対に真似しないで下さい。
****************************************************************/
bool Rod::CollidesWithHeroine()
{
	// ﾋﾛｲﾝの丸い判定
	Jiki* jiki = GAMECONTROL->GetJiki();
	int jx = jiki->GetX();
	int jy = jiki->GetY();
	
	Circle* cl[3];

	cl[0] = new Circle(jiki->GetCurFrame(), 0, 64, 37, 16);
	cl[1] = new Circle(jiki->GetCurFrame(), 0, 67, 65, 12);
	cl[2] = new Circle(jiki->GetCurFrame(), 0, 69, 99, 20);
	
	// ロッドの四角
	Rect* thisRect;
	thisRect = new Rect(pCollision->GetCurFrame(), 0, 0, 0, mSizeX, mSizeY);

	// 回転行列
	D3DXMATRIX rot;
	D3DXVECTOR2 center(mX+mSizeX/2, mY+(mSizeY-10));
	D3DXMatrixTransformation2D(&rot, NULL, 0.0f, NULL, &center, -mAngle, NULL);

	for( int i=0; i<3; i++ ){
		// 座標変換
		D3DXVECTOR3 res;
		D3DXVECTOR3 src(cl[i]->X() + jx, cl[i]->Y() + jy, 0.0f);
		D3DXVec3TransformCoord( &res, &src, &rot );
		cl[i]->Set(res.x, res.y, cl[i]->Hankei());
		
		// 判定
		if ( Rect::RectCircle(thisRect, cl[i], mX, mY, 0, mSizeX, 0, 0, 0, 0 ) ) return true;
	}

	return false;
}

/************************************************************//**
*	描画
****************************************************************/
void Rod::Draw()
{
	DX_CENTERROT_DRAWALPHA("graphics\\teki\\queen\\boss4_stick.png", 
		mX, mY, 0, 0, mSizeX, mSizeY, mAngle, mSizeX/2, mSizeY-10, mAlpha);
}

/************************************************************//**
*	当たり判定の応答
****************************************************************/
void Rod::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// ﾋﾛｲﾝ
	if( jiki && rOpGroupId == SP->GRID_BOGYO  || rOpGroupId == SP->GRID_KOUGEKI ){
		jiki->InflictDamage();
	}
}

/************************************************************//**
*	\return 挙動終わっているか
****************************************************************/
bool Rod::HasFinished()
{
	return mStatus == INACTIVE;
}