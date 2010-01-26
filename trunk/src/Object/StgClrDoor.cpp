#include "StgClrDoor.h"
#include "..\\Management\\GameControl.h"
#include "..\\Light\\Light.h"
#include "..\\Event\\StageClearEvt.h"

/*
	コンストラクタ
*/
StgClrDoor::StgClrDoor(int rXPx, int rYPx, float rZ)
{
	mSizeX = GI("GOALSX");
	mSizeY = GI("GOALSY");

	mX = rXPx;
	mY = rYPx - mSizeY + SP->CHSZY;
	mZ = rZ;

	stageclear = false;

	// 当たり判定
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, mSizeX/2, mSizeY/2, 1);

	// ｱﾆﾒｰｼｮﾝ (間隔0.1f)
	mAnimation = new Animation();
	mAnimation->SetGraphicSource("graphics\\object\\goal.png");
	mAnimation->SetAnimData(0, 1, 2, -1);
	mAnimation->SetAnimIntervals(0.1f, 0.2f, 0.3f, -1.0f);
	mAnimation->SetAnimMode(Animation::ANMD_LOOP);

	AddTarget( GAMECONTROL->GetJiki() );
}

StgClrDoor::~StgClrDoor()
{
	delete mAnimation;
}

int StgClrDoor::GetSizeX()
{
	return mSizeX;
}

/*
	プロセス
*/
void StgClrDoor::Move()
{
	if( stageclear ){
		if( GAMECONTROL->GetMaku()->IsClosed() && GAMECONTROL->GetTxtGraphicController()->IsFinished()){
			if (GAMECONTROL->GetFader()->FadeOut()  ){
				GAMECONTROL->GetEventManager()->Request(new StageClearEvt());
			}
		}

		// ﾏｳｽｸﾘｯｸでｽｷｯﾌﾟ
		if( GAMECONTROL->GetDXController()->IsMouseClicked() ){
			GAMECONTROL->GetMaku()->SetClosed();
			GAMECONTROL->GetTxtGraphicController()->Reset();
		}
	}

	// アニメーション
	mAnimation->ElapseTime(SP->FrameTime);
	
	// 描画
	DX_SCROLL_SCREEN_DRAW(mAnimation->GetGraphicSource(), mX, mY, mSizeX*mAnimation->GetCurFrameIdx(), 0, 
		mSizeX*(mAnimation->GetCurFrameIdx()+1), mSizeY, 0.5f);
}

/*
	当たり判定
*/
void StgClrDoor::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);
	if( jiki != NULL && rOpGroupId == SP->GRID_BOGYO && !stageclear && jiki->IsStageclearable() ){
		stageclear = true;
		GAMECONTROL->GetJiki()->DisableCollision();
		GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();
		GAMECONTROL->GetJiki()->SetSuperPause();
		GAMECONTROL->GetMaku()->Close();
		GAMECONTROL->GetJiki()->HrWalk();

		GAMECONTROL->GetTxtGraphicController()->ShowWithAlphaFade(
					TxtGraphicController::CENTER, 
					GI("STGCLRMOJI_SX"),GI("STGCLRMOJI_SY"), 
					"graphics\\txtgraphic\\stage_clear_01.png",
					GF("STGCLMOJI_DTIME"), GF("STGCLMOJI_FSP"));
	}
}