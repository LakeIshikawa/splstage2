#include "CurtainRollScr.h"
#include "..\\..\\Management\\GameControl.h"
#include "..\\..\\Light\\Light.h"
#include "..\\..\\Event\\StageClearEvt.h"
#include "..\\..\\Stage\\FixScrollMap.h"

CurtainRollScr::CurtainRollScr(string rDataFname, string rScrollBckgImg, string rMapChipGr, SoundController::BGMS rBgm)
{
	mDataFname = rDataFname;
	mMapChipGr = rMapChipGr;
	mBgm = rBgm;

	
	mpScrollBackground = new ScrollBackground(rScrollBckgImg);
	mpMap = new FixScrollMap();
	mpHaichi = new Haichi();

}

void CurtainRollScr::Init()
{
	mStage = FADING;
	mTimer = 0.0f;

	GAMECONTROL->GetTxtGraphicController()->Reset();
}

CurtainRollScr::~CurtainRollScr(void)
{
}

void CurtainRollScr::Process()
{
	//描画
	mpScrollBackground->SetScrollP(mpMap->GetScrollP());
	mpScrollBackground->Draw();

	GetMap()->Process();

	GAMECONTROL->GetMobManager()->Process();

	GAMECONTROL->GetMaku()->Draw();

	UpdateStage();

}

void CurtainRollScr::Load()
{
	// これは・・・すまない・・・　俺は・・　もう・・・　ッグ！！！！
	GAMECONTROL->GetFader()->Draw();
	GAMECONTROL->GetDXController()->PrintDebugSting(650, 570, "now loading...");
	GAMECONTROL->GetDXController()->mpDevice->EndScene();
	GAMECONTROL->GetDXController()->mpDevice->Present(NULL, NULL, NULL, NULL);
	GAMECONTROL->GetDXController()->mpDevice->BeginScene();

	mpMap->Load( mDataFname, mMapChipGr );
	mpMap->SetScrollP(0);
	mpHaichi->Load( mTekiFname, mpCheckpointController );
	GAMECONTROL->GetJiki()->SetPos(-1200, -1200);
	GAMECONTROL->GetJiki()->ResetTempParams();
	GAMECONTROL->GetJiki()->SetSuperPause();
	GAMECONTROL->GetJiki()->SetMuki(1);
	GAMECONTROL->GetUserLightControl()->GetControlLight()->SetPos(-1200, -1200);

	GAMECONTROL->GetSoundController()->PauseBGM();
	GAMECONTROL->GetSoundController()->ResetBGMs();				

	GAMECONTROL->GetMobManager()->Remove( GAMECONTROL->GetJiki() );

	GAMECONTROL->GetMaku()->SetClosed();

	DisposeMovieActors();
	Init();

}

void CurtainRollScr::UnLoad()
{
	mpMap->UnLoad();
	mpHaichi->UnLoad();
}

/* 役者の配置 */
void CurtainRollScr::DisposeMovieActors()
{
	// ﾋﾛｲﾝ
	heroine = new MovieActor(GI("HERSIZE"), GI("HERSIZE"));
	
	Animation* walk = new Animation();
	walk->SetGraphicSource("graphics\\heroine\\heroine_work.png");
	walk->SetAnimData(0, 1, 2, 3, 4, 5, 6, 7, -1);
	walk->SetAnimIntervals(0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, -1.0f);
	walk->SetAnimMode(Animation::ANMD_LOOP);
	
	Animation* stop = new Animation();
	stop->SetGraphicSource("graphics\\heroine\\heroine_stend.png");
	stop->SetAnimData(0, 1, 2, 1, 3, 4, 5, 4, -1);
	stop->SetAnimIntervals(0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, -1.0f);
	stop->SetAnimMode(Animation::ANMD_LOOP);

	Animation* attack = new Animation();
	attack->SetGraphicSource("graphics\\heroine\\heroine_attack.png");
	attack->SetAnimData(0, 1, 2, 3, 4, 5, 6, -1);
	attack->SetAnimIntervals(0.06, 0.12, 0.20, 0.28, 0.36, 0.44, 0.52, -1.0f);
	attack->SetLoopStartIdx(3);
	attack->SetAnimMode(Animation::ANMD_LOOP);
	
	Animation* attackEnd = new Animation();
	attackEnd->SetGraphicSource("graphics\\heroine\\heroine_attack.png");
	attackEnd->SetAnimData(3, 4, 5, 6, 7, 8, 9, -1);
	attackEnd->SetAnimIntervals(0.07, 0.15, 0.24, 0.34, 0.45, 0.57, 0.70, -1.0f);
	attackEnd->SetAnimMode(Animation::ANMD_STOPATEND);
	
	heroine->GetAnimationSet()->AddAnimation(HERAN_WALK, walk);
	heroine->GetAnimationSet()->AddAnimation(HERAN_STOP, stop);
	heroine->GetAnimationSet()->AddAnimation(HERAN_ATT, attack);
	heroine->GetAnimationSet()->AddAnimation(HERAN_ATTEND, attackEnd);
	heroine->GetAnimationSet()->SetCurAnimation(HERAN_WALK);
	heroine->SetPos( -120, -120 );
	heroine->SetMuki(1);
	heroine->SetZ(100.0f);
	heroine->AddFrame(0);
	heroine->AddCircle(0, SP->GRID_KOUGEKI, 24, 92, 24);

	// カエルキング
	Animation* frogStand = new Animation();
	frogStand->SetGraphicSource("graphics\\teki\\ene_frogking.png");
	frogStand->SetAnimData(0, -1);
	frogStand->SetAnimIntervals(0.2f, -1.0f);

	Animation* frogDie = frogStand->Clone();
	frogDie->SetRotAngle( D3DX_PI );

	actors[0] = new MovieActor(GI("KAERUKSX"), GI("KAERUKSY"));
	actors[0]->GetAnimationSet()->AddAnimation( TEKI_STAND, frogStand );
	actors[0]->GetAnimationSet()->AddAnimation( TEKI_DIE, frogDie );
	actors[0]->SetPos( 216+500, 464-16 );
	actors[0]->SetMuki(0);
	actors[0]->SetZ(0);
	actors[0]->AddFrame(0);
	actors[0]->AddCircle(0, SP->GRID_BOGYO, 44, 44, 44);
	actors[0]->AddTarget(heroine);

	// ﾄﾗﾝﾌﾟ兵
	Animation* trumpStand = new Animation();
	trumpStand->SetGraphicSource("graphics\\teki\\queen\\ene_tranpma1_walk.png");
	trumpStand->SetAnimData(0, -1);
	trumpStand->SetAnimIntervals(0.2f, -1.0f);

	Animation* trumpDie = new Animation();
	trumpDie->SetGraphicSource( "graphics\\teki\\queen\\ene_tranpman1_down.png" );
	trumpDie->SetAnimData( 0, 1, -1 );
	trumpDie->SetAnimIntervals( 0.2f, 0.4f, -1.0f );
	trumpDie->SetAnimMode(Animation::ANMD_STOPATEND);

	actors[1] = new MovieActor(GI("TRUMPHEISX"), GI("TRUMPHEISY"));
	actors[1]->GetAnimationSet()->AddAnimation( TEKI_STAND, trumpStand );
	actors[1]->GetAnimationSet()->AddAnimation( TEKI_DIE, trumpDie );
	actors[1]->SetPos( 204+500, 344-16 );
	actors[1]->SetMuki(0);
	actors[1]->SetZ(1);
	actors[1]->AddFrame(0);
	actors[1]->AddRect(0, SP->GRID_BOGYO, 77, 98, 109, 207);
	actors[1]->AddTarget(heroine);

	// 魔女
	Animation* majoStand = new Animation();
	majoStand->SetGraphicSource("graphics\\teki\\boss_witch_side.png");
	majoStand->SetAnimData(0, 1, 2, 1, -1);
	majoStand->SetAnimIntervals(0.2f, 0.4f, 0.6f, 0.8f, -1.0f);
	majoStand->SetAnimMode( Animation::ANMD_LOOP );

	Animation* majoDie = new Animation();
	majoDie->SetGraphicSource("graphics\\teki\\boss_witch_side.png");
	majoDie->SetAnimData(11, 12, 13, 14, -1);
	majoDie->SetAnimIntervals(0.2f, 0.4f, 0.6f, 0.8f, -1.0f);
	majoDie->SetAnimMode( Animation::ANMD_STOPATEND );

	actors[2] = new MovieActor(GI("MAJO_DOORSX"), GI("MAJO_DOORSY"));
	actors[2]->GetAnimationSet()->AddAnimation( TEKI_STAND, majoStand );
	actors[2]->GetAnimationSet()->AddAnimation( TEKI_DIE, majoDie );
	actors[2]->SetPos( 280+500, 436-16 );
	actors[2]->SetMuki(0);
	actors[2]->SetZ(2);
	actors[2]->AddFrame(0);
	actors[2]->AddCircle(0, SP->GRID_BOGYO, 60, 50, 18);
	actors[2]->AddCircle(0, SP->GRID_BOGYO, 64, 91, 18);
	actors[2]->AddTarget(heroine);

	// ｸｲｰﾝ
	Animation* queenStand = Animation::ParseFromFile( "data\\animdata\\queen\\Stand.txt" );
	Animation* queenDie = Animation::ParseFromFile( "data\\animdata\\queen\\Damage.txt" );
	actors[3] = new MovieActor(GI("QUEEN_SX"), GI("QUEEN_SY"));
	actors[3]->GetAnimationSet()->AddAnimation( TEKI_STAND, queenStand );
	actors[3]->GetAnimationSet()->AddAnimation( TEKI_DIE, queenDie );
	actors[3]->SetPos( 342+500, 408-16 );
	actors[3]->SetMuki(0);
	actors[3]->SetZ(3);
	actors[3]->AddFrame(0);
	actors[3]->AddTarget(heroine);
	actors[3]->AddRect(0, SP->GRID_BOGYO, 44, 50, 77, 142);

	// 狼
	Animation* wolfStand = Animation::ParseFromFile( "data\\animdata\\ookami\\Stand.txt" );
	Animation* wolfDie = Animation::ParseFromFile( "data\\animdata\\ookami\\Damage.txt" );
	actors[4] = new MovieActor(GI("OOKAMI_SX"), GI("OOKAMI_SY"));
	actors[4]->GetAnimationSet()->AddAnimation( TEKI_STAND, wolfStand);
	actors[4]->GetAnimationSet()->AddAnimation( TEKI_DIE, wolfDie );
	actors[4]->SetPos( 400+500, 418-16 );
	actors[4]->SetMuki(1);
	actors[4]->SetZ(2);
	actors[4]->AddFrame(0);
	actors[4]->AddTarget(heroine);
	actors[4]->AddRect(0, SP->GRID_BOGYO, 38, 32, 75, 131);

	// 狩人剣
	Animation* hunterStand = new Animation();
	hunterStand->SetGraphicSource("graphics\\teki\\ene_hunter1.png");
	hunterStand->SetAnimData(0, 1, 2, -1);
	hunterStand->SetAnimIntervals(0.2f, 0.4f, 0.6f, -1.0f);
	hunterStand->SetAnimMode( Animation::ANMD_LOOP );

	Animation* hunterDie = new Animation();
	hunterDie->SetGraphicSource("graphics\\teki\\ene_hunter1_damage.png");
	hunterDie->SetAnimData(0, -1);
	hunterDie->SetAnimIntervals(0.2f, -1.0f);
	hunterDie->SetAnimMode( Animation::ANMD_STOPATEND );

	actors[5] = new MovieActor(GI("KARIKENSX"), GI("KARIKENSY"));
	actors[5]->GetAnimationSet()->AddAnimation( TEKI_STAND, hunterStand );
	actors[5]->GetAnimationSet()->AddAnimation( TEKI_DIE, hunterDie );
	actors[5]->SetPos( 448+500, 438-16 );
	actors[5]->SetMuki(1);
	actors[5]->SetZ(1);
	actors[5]->AddFrame(0);
	actors[5]->AddTarget(heroine);
	actors[5]->AddRect(0, SP->GRID_BOGYO, 43, 33, 81, 119);

	// 兎
	Animation* rabbitStand = new Animation();
	rabbitStand->SetGraphicSource("graphics\\teki\\ene_rabbit_01.png");
	rabbitStand->SetAnimData(0, -1);
	rabbitStand->SetAnimIntervals(0.2f, -1.0f);
	rabbitStand->SetAnimMode( Animation::ANMD_LOOP );

	Animation* rabbitDie = rabbitStand->Clone();
	rabbitDie->SetRotAngle( D3DX_PI );

	actors[6] = new MovieActor(GI("USAGISX"), GI("USAGISY"));
	actors[6]->GetAnimationSet()->AddAnimation( TEKI_STAND, rabbitStand );
	actors[6]->GetAnimationSet()->AddAnimation( TEKI_DIE, rabbitDie );
	actors[6]->SetPos( 528+500, 482-16 );
	actors[6]->SetMuki(1);
	actors[6]->SetZ(0);
	actors[6]->AddFrame(0);
	actors[6]->AddTarget(heroine);
	actors[6]->AddCircle(0, SP->GRID_BOGYO, 36, 36, 28);


	// 停止状態にしてリクエストする
	for( int i=0; i<7; i++ ){
		actors[i]->GetAnimationSet()->SetCurAnimation( TEKI_STAND );
		GAMECONTROL->GetMobManager()->Request(actors[i], true);
	}
}

void CurtainRollScr::UpdateStage()
{
	switch( mStage ){

	// ﾌｪｰﾄﾞｲﾝ
	case FADING:	
		if( GAMECONTROL->GetFader()->FadeIn() ){
			//幕をあげる
			GAMECONTROL->GetMaku()->Open();
			mStage = OPENING;
		}
		break;

	// 幕アップ
	case OPENING:
		if( GAMECONTROL->GetMaku()->IsOpen() ){
			mStage = WAIT1SEC;
		}
		break;

	// 1秒待機
	case WAIT1SEC:
		WAIT_TIMER(mTimer, 1.0f)
			GAMECONTROL->GetTxtGraphicController()->ShowWithAlphaFade( TxtGraphicController::CENTER, 
				GI("THANKSSX"), GI("THANKSSY"), "graphics\\screen\\thank_you.png", 3.0f, 0.05f );
			mStage = THANKSPLAYING;
		WAIT_END
		break;

	// サンキュー
	case THANKSPLAYING:
		if( GAMECONTROL->GetTxtGraphicController()->IsFinished() )
			mStage = WAIT1SECMORE;
		break;

	// さらに1秒待機
	case WAIT1SECMORE:
		WAIT_TIMER(mTimer, 1.0f)
			mStage = HEROINE_ENTERING;
			heroine->SetPos(500-GI("HERSIZE"), GI("FLOORY") - GI("HERSIZE"));
			heroine->GetAnimationSet()->SetCurAnimation(HERAN_WALK);
			heroine->SetSp( GF("SPWALK"), 0 );
			GAMECONTROL->GetMobManager()->Request( heroine, true );
		WAIT_END
		break;

	// ﾋﾛｲﾝ登場
	case HEROINE_ENTERING:
		if( heroine->GetX() >= 500+170-GI("HERSIZE") ){
			heroine->SetSp(0,0);
			heroine->GetAnimationSet()->SetCurAnimation(HERAN_STOP);
			mStage = HEROINE_STOP1SEC;
		}
		break;

	// ﾋﾛｲﾝ停止
	case HEROINE_STOP1SEC:
		WAIT_TIMER(mTimer, 1.0f)
			mStage = HEROINE_ATTACK;
			heroine->GetAnimationSet()->SetCurAnimation(HERAN_ATT);
			heroine->SetSp( GF("SPWALK"), 0 ) ;
			heroine->SetAcc( GF("ACCKOGEKI") / SP->FRAMERATE, 0 );
			GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_hiroin_tijoukougeki.wav");
		WAIT_END
		break;

	// ﾋﾛｲﾝ攻撃
	case HEROINE_ATTACK:
		// 敵に当たったら敵が死ぬ
		for(int i=0; i<7; i++){
			if( actors[i]->IsJikiColliding() && actors[i]->GetAnimationSet()->GetCurAnimationIdx() == TEKI_STAND ){
				actors[i]->GetAnimationSet()->SetCurAnimation( TEKI_DIE );
				actors[i]->SetSp( GF("SHINIPATT_SPX"), -GF("SHINIPATT_SHOSP") );
				actors[i]->SetAcc( 0, SP->GRAVITY );
				GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kougekimeityuu.wav");
			}
		}

		// 到着
		if( heroine->GetX() >= 500+740-GI("HERSIZE") && 
			heroine->GetAnimationSet()->GetCurAnimation()->GetCurFrameIdx() == 3)
		{
			heroine->SetSp(0,0);
			heroine->SetAcc(0,0);
			heroine->GetAnimationSet()->SetCurAnimation(HERAN_ATTEND);
			mStage = HEROINE_ATTACKEND;
			GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_hiroin_tijoukougeki.wav");
		}
		break;

	// 攻撃終了動作
	case HEROINE_ATTACKEND:
		if( heroine->GetAnimationSet()->GetCurAnimation()->GetLoopCount() == 1 ){
			heroine->GetAnimationSet()->SetCurAnimation(HERAN_STOP);
			mStage = HEROINE_STOP1SECMORE;
		}
		break;

	// さらに1秒停止
	case HEROINE_STOP1SECMORE:
		WAIT_TIMER(mTimer, 1.0f)
			mStage = SEEYOUAGAIN;
			GAMECONTROL->GetTxtGraphicController()->ShowWithAlphaFade( TxtGraphicController::CENTER, 
				GI("SEEYOUSX"), GI("SEEYOUSY"), "graphics\\screen\\see_you_again.png", 3.0f, 0.05f );
		WAIT_END
		break;

	// また遊んでね
	case SEEYOUAGAIN:
		if( GAMECONTROL->GetTxtGraphicController()->IsFinished() ){
			mStage = CLOSINGANDFADINGOUT;
			GAMECONTROL->GetMaku()->Close();
		}
		break;

	// ﾊﾞｲﾊﾞｲ
	case CLOSINGANDFADINGOUT:
		if( GAMECONTROL->GetMaku()->IsClosed() ){
			if( GAMECONTROL->GetFader()->FadeOut() ){
				STAGE_CLEAR;
			}
		}
		break;
	}
}