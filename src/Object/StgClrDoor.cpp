#include "StgClrDoor.h"
#include "..\\Management\\GameControl.h"
#include "..\\Light\\Light.h"
#include "..\\Event\\StageClearEvt.h"

/*
	コンストラクタ
*/
StgClrDoor::StgClrDoor(int rXPx, int rYPx, float rZ)
{
	STGCLRDOORSX = GI("STGCLRDOORSX");
	STGCLRDOORSY = GI("STGCLRDOORSY");

	mX = rXPx;
	mY = rYPx - STGCLRDOORSY + SP->CHSZY;
	mZ = rZ;

	stageclear = false;

	AddFrame(0);
	AddRect(0, SP->GRID_BOGYO, 60, 0, 110, 50);

	AddTarget( GAMECONTROL->GetJiki() );
}

StgClrDoor::~StgClrDoor()
{}

int StgClrDoor::GetSizeX()
{
	return STGCLRDOORSX;
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

	DX_SCROLL_DRAW("graphics\\object\\doorgai.png", mX, mY, 0, 0, STGCLRDOORSX, STGCLRDOORSY);
}

/*
	当たり判定
*/
void StgClrDoor::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);
	if( jiki != NULL && rOpGroupId == SP->GRID_BOGYO && !stageclear ){
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