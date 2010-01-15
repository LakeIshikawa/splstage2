#include "TitleScr.h"
#include "..\\..\\Management\\GameControl.h"
#include "..\\..\\Light\\Light.h"
#include "..\\..\\Event\\StageClearEvt.h"
#include "..\\..\\Stage\\FixScrollMap.h"

TitleScr::TitleScr(string rDataFname, string rTekiFname, string rScrollBckgImg, string rMapChipGr, SoundController::BGMS rBgm)
{
	mDataFname = rDataFname;
	mTekiFname = rTekiFname;
	mMapChipGr = rMapChipGr;
	mBgm = rBgm;
	
	mpScrollBackground = new ScrollBackground(rScrollBckgImg);
	mpMap = new FixScrollMap();
	mpHaichi = new Haichi();

	Init();
}

void TitleScr::Init()
{
	mFading = false;
	AniNo	= 0;
	mGoTugi = false;
	mLightOn = false;
}

TitleScr::~TitleScr(void)
{
}

void TitleScr::Process()
{
	if( !mFading ){
		if( GAMECONTROL->GetFader()->FadeIn() ){
			mFading = true;
			//����������
			GAMECONTROL->GetMaku()->Open();
			GAMECONTROL->GetSoundController()->SetBGM(mBgm);
		}
	}
	// �q���C�����~�߂�
	GAMECONTROL->GetJiki()->SetSuperPause();

	//��������������ײ�on
	if( GAMECONTROL->GetMaku()->IsOpen() && !mLightOn ){
		mLightOn = true;
		GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOn();
	}

	//�������肽��ð�ނ�
	if( GAMECONTROL->GetMaku()->IsClosed() && mFading ) mGoTugi = true;

	if( CONTROLLIGHT->GetX() > 223 && CONTROLLIGHT->GetX() < 223+350 &&
		 CONTROLLIGHT->GetY() > 300 && CONTROLLIGHT->GetY() < 300+100 ){
		if( AniNo != 2 ) AniNo = 1;
		if( GAMECONTROL->GetDXController()->IsMouseClicked() &&
			GAMECONTROL->GetMaku()->IsOpen() ){
			AniNo = 2;
			//����������
			GAMECONTROL->GetMaku()->Close();
			GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();
			//SE
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kettei.wav");
		}
	}else{
		if( AniNo == 1 ) AniNo = 0;
	}

	if( mGoTugi ){
		if( GAMECONTROL->GetFader()->FadeOut() )
			GAMECONTROL->GetEventManager()->Request(new StageClearEvt());
	}


	//�`��
	mpScrollBackground->SetScrollP(mpMap->GetScrollP());
	mpScrollBackground->Draw();

	GetMap()->Process();

	//GAMECONTROL->GetLightManager()->Move();

	GAMECONTROL->GetMobManager()->Process();

	DX_DRAW("graphics\\screen\\game start0.png",//�߯������
		223, 300, 350*AniNo, 0, 350+350*AniNo, 100);

	GAMECONTROL->GetLightManager()->Draw();

	DX_DRAW("graphics\\screen\\game title.png", //���دï�޽ð��
		155, 100, 0, 0, 490, 120);

	GAMECONTROL->GetMaku()->Draw();

}

void TitleScr::Load()
{
	// ����́E�E�E���܂Ȃ��E�E�E�@���́E�E�@�����E�E�E�@�b�O�I�I�I�I
	GAMECONTROL->GetFader()->Draw();
	GAMECONTROL->GetDXController()->PrintDebugSting(650, 570, "now loading...");
	GAMECONTROL->GetDXController()->mpDevice->EndScene();
	GAMECONTROL->GetDXController()->mpDevice->Present(NULL, NULL, NULL, NULL);
	GAMECONTROL->GetDXController()->mpDevice->BeginScene();

	mpMap->Load( mDataFname, mMapChipGr );
	mpHaichi->Load( mTekiFname, mpCheckpointController );
	GAMECONTROL->GetJiki()->SetPos(GF("HERINITX")+500, GF("HERINITY"));
	GAMECONTROL->GetJiki()->ResetLife();
	GAMECONTROL->GetJiki()->ResetTension();
	GAMECONTROL->GetJiki()->ResetEmpacy();
	GAMECONTROL->GetJiki()->ResetTempParams();
	GAMECONTROL->GetJiki()->SetSuperPause();
	GAMECONTROL->GetJiki()->SetMuki(1);

	GAMECONTROL->GetUserLightControl()->GetControlLight()->SetPos( SP->SCRSZX/2, SP->SCRSZY/2 );
	GAMECONTROL->GetSoundController()->PauseBGM();

	Init();

}

void TitleScr::UnLoad()
{
	mpMap->UnLoad();
	mpHaichi->UnLoad();
}
