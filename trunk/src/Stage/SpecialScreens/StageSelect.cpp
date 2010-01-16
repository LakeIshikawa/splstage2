#include "StageSelect.h"
#include "..\\..\\Management\\GameControl.h"
#include "..\\..\\Light\\Light.h"
#include "..\\..\\Event\\StageClearEvt.h"
#include "..\\..\\Stage\\FixScrollMap.h"

#define LIGHT_AT 30

StageSelect::StageSelect(string rDataFname, string rScrollBckgImg, string rMapChipGr, SoundController::BGMS rBgm)
{
	mDataFname = rDataFname;
	mMapChipGr = rMapChipGr;
	mBgm = rBgm;
	
	mpScrollBackground = new ScrollBackground(rScrollBckgImg);
	mpMap = new FixScrollMap();
}

void StageSelect::Init()
{
	stage = 0;
	scroll = 0;
	scrollNLRdir = 0;
	alpha = 1.0f;
	curScroll = 0;
	LoadSaveData();
	selectedIdx = saveStageTdx;
}

StageSelect::~StageSelect(void)
{
}

void StageSelect::Process()
{
	switch( stage ){

	// �t�F�[�h�C��
	case 0:
		if( GAMECONTROL->GetFader()->FadeIn() ){
			//����������
			GAMECONTROL->GetMaku()->Open();
			GAMECONTROL->GetSoundController()->SetBGM(mBgm);
			stage = 1;
		}
		break;

	// ����������
	case 1:
		if( GAMECONTROL->GetMaku()->IsOpen() ) stage = 2;
		break;

	// �����L���ɂ���
	case 2:
		GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOn();
		stage = 3;
		break;

	// հ�ް�̑�����󂯕t���ĉ�������
	case 3:
		ProcessUserControl();
		break;

	// ���_�E���A̪��ރA�E�g
	case 4:
		if( GAMECONTROL->GetMaku()->IsClosed() ){
			if( GAMECONTROL->GetFader()->FadeOut() ){
				StageManager* sm = GAMECONTROL->GetStageManager();
				sm->GoToStage( selectedIdx + sm->GetFirstStageIdx() );
			}
		}
	}	


	//�`��
	mpScrollBackground->Draw();

	GetMap()->Process();

	DrawInterface();
	
	GAMECONTROL->GetLightManager()->Draw();

	GAMECONTROL->GetMaku()->Draw();

}

void StageSelect::Load()
{
	// ����́E�E�E���܂Ȃ��E�E�E�@���́E�E�@�����E�E�E�@�b�O�I�I�I�I
	GAMECONTROL->GetFader()->Draw();
	GAMECONTROL->GetDXController()->PrintDebugSting(650, 570, "now loading...");
	GAMECONTROL->GetDXController()->mpDevice->EndScene();
	GAMECONTROL->GetDXController()->mpDevice->Present(NULL, NULL, NULL, NULL);
	GAMECONTROL->GetDXController()->mpDevice->BeginScene();

	mpMap->Load( mDataFname, mMapChipGr );
	mpHaichi->Load( mTekiFname, mpCheckpointController );
	GAMECONTROL->GetJiki()->SetPos(-500, 0);
	GAMECONTROL->GetJiki()->ResetLife();
	GAMECONTROL->GetJiki()->ResetTension();
	GAMECONTROL->GetJiki()->ResetEmpacy();
	GAMECONTROL->GetJiki()->ResetChain();
	GAMECONTROL->GetJiki()->ResetTempParams();
	GAMECONTROL->GetJiki()->SetSuperPause();
	GAMECONTROL->GetJiki()->SetMuki(1);

	GAMECONTROL->GetUserLightControl()->GetControlLight()->SetPos( SP->SCRSZX/2, SP->SCRSZY/2 );
	GAMECONTROL->GetSoundController()->PauseBGM();

	mpScrollBackground->SetScrollP(mpMap->GetScrollP());

	Init();
}

void StageSelect::UnLoad()
{
	mpMap->UnLoad();
}

void StageSelect::SetSelectedIdx(int rIdx)
{
	selectedIdx = rIdx;
}

/**
* հ�ް�����ɃN���b�N������A�ð�ނ̉摜���ʂ̉摜�ɽײ�ނ���B
* հ�ް���ð�މ摜���N���b�N������A�ްъJ�n
*/
void StageSelect::ProcessUserControl()
{
	if( GAMECONTROL->GetDXController()->IsMouseClicked() )
	{
		// ײĂ̈ʒu
		int lx = GAMECONTROL->GetUserLightControl()->GetControlLight()->GetX();
		int ly = GAMECONTROL->GetUserLightControl()->GetControlLight()->GetY();
		
		// ���
		// -- ��
		int lyx = GI("STGSELECT_LARX") + GI("STGSELECT_ARSX")/2;
		int lyy = GI("STGSELECT_ARY") + GI("STGSELECT_ARSY")/2;
		if( sqrt( pow((float)(lyx-lx), 2) + pow((float)(lyy-ly), 2)) <= LIGHT_AT ){
			GoToLeft();
			return;
		}

		// -- �E
		int ryx = GI("STGSELECT_RARX") + GI("STGSELECT_ARSX")/2;
		if( sqrt( pow((float)(ryx-lx), 2) + pow((float)(lyy-ly), 2) ) <= LIGHT_AT ){
			GoToRight();
			return;
		}

		// �ð�ފJ�n
		int top = GI("STGSELECT_IMGY");
		int left = SP->SCRSZX/2 - GI("STGSELECT_IMGSX")/2;
		int bottom = top + GI("STGSELECT_IMGSY");
		int right = left + GI("STGSELECT_IMGSX");

		// �ð�ފJ�n���I�����ꂽ��
		if( lx >= left && lx <= right && ly>=top && ly <= bottom && selectedIdx <= saveStageTdx && scroll == 0){
			GAMECONTROL->GetMaku()->Close();
			GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();
			stage = 4;
		}
	}
}

/**
* �ð�ޑI�����̪���̕`��
*/
void StageSelect::DrawInterface()
{
	
	// ����
	StageManager* sm = GAMECONTROL->GetStageManager();
	
	// ̪���
	alpha += 0.05f;
	if( alpha > 1.0f ) alpha = 1.0f;
	// ������
	DX_DRAWALPHA(sm->GetStageSelectTitleGraphic(sm->GetFirstStageIdx() + selectedIdx), 
		SP->SCRSZX/2-GI("STGSELECT_TITSX")/2, GI("STGSELECT_TITY"), 0, 0, 
		GI("STGSELECT_TITSX"), GI("STGSELECT_TITSY"), alpha );
	// �O����
	if( scrollNLRdir != 0 ){
		int scridx = selectedIdx + (scrollNLRdir==1?1:-1);	
		string graphic = sm->GetStageSelectTitleGraphic(sm->GetFirstStageIdx() + scridx);
		DX_DRAWALPHA(graphic,SP->SCRSZX/2-GI("STGSELECT_TITSX")/2, GI("STGSELECT_TITY"), 0, 0, 
			GI("STGSELECT_TITSX"), GI("STGSELECT_TITSY"), 1.0f-alpha );
	}

	// ���
	DX_DRAW("graphics\\stageselect\\left.png", GI("STGSELECT_LARX"), GI("STGSELECT_ARY"),
		0, 0, GI("STGSELECT_ARSX"), GI("STGSELECT_ARSY") );
	DX_DRAW("graphics\\stageselect\\right.png", GI("STGSELECT_RARX"), GI("STGSELECT_ARY"),
		0, 0, GI("STGSELECT_ARSX"), GI("STGSELECT_ARSY") );


	// �Ұ�މ摜
	// �ײ�޲�
	if( scrollNLRdir == 2 ) scroll -= GI("STGSELECT_SLDSP");
	else if( scrollNLRdir == 1 ) scroll += GI("STGSELECT_SLDSP");
	// ��~����
	if( scrollNLRdir == 2 && scroll < 0 ) { scroll = 0; scrollNLRdir = 0; }
	if( scrollNLRdir == 1 && scroll > 0 ) { scroll = 0; scrollNLRdir = 0; }

	// ���ݲҰ��
	DX_DRAW(saveStageTdx >= selectedIdx ? sm->GetStageSelectImageGraphic(sm->GetFirstStageIdx() + selectedIdx) : 
		"graphics\\stageselect\\stgNA.png",	SP->SCRSZX/2-GI("STGSELECT_IMGSX")/2 + scroll, GI("STGSELECT_IMGY"), 0, 0, 
		GI("STGSELECT_IMGSX"), GI("STGSELECT_IMGSY") );
	
	// �O��Ұ��(��۰ٗp)
	if( scrollNLRdir != 0 ){
		bool leftright = scrollNLRdir == 1;
		int scridx = selectedIdx + (leftright?1:-1);
		string graphic = saveStageTdx >= scridx? sm->GetStageSelectImageGraphic(sm->GetFirstStageIdx() + scridx) : 
			"graphics\\stageselect\\stgNA.png";
		int scroll2 = leftright ? GI("STGSELECT_SLDDIST") +scroll : scroll - GI("STGSELECT_SLDDIST");

		DX_DRAW(graphic, SP->SCRSZX/2-GI("STGSELECT_IMGSX")/2 + scroll2, GI("STGSELECT_IMGY"), 0, 0, 
			GI("STGSELECT_IMGSX"), GI("STGSELECT_IMGSY") );
	}

	// �S�̐}
	DX_DRAW("graphics\\stageselect\\stageallgray.png", SP->SCRSZX/2-GI("STGSELECT_ALLSX")/2, 
		GI("STGSELECT_ALLY"), 0, 0, GI("STGSELECT_ALLSX"), GI("STGSELECT_ALLSY") );
	DX_DRAW("graphics\\stageselect\\stageall.png", SP->SCRSZX/2-GI("STGSELECT_ALLSX")/2, 
		GI("STGSELECT_ALLY"), 0, 0, GI("STGSELECT_ALL1SX") * (saveStageTdx+1), GI("STGSELECT_ALLSY") );
	DX_DRAW_BLEND("graphics\\stageselect\\stageall.png", SP->SCRSZX/2-GI("STGSELECT_ALLSX")/2 + GI("STGSELECT_ALL1SX") * (saveStageTdx+1), 
		GI("STGSELECT_ALLY"), GI("STGSELECT_ALL1SX") * (saveStageTdx+1), 0, GI("STGSELECT_ALLSX"), GI("STGSELECT_ALLSY"),
		D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

	// ����
	// ��۰�
	float sp = GI("STGSELECT_ALL1SX") / ((float)GI("STGSELECT_SLDDIST")/GI("STGSELECT_SLDSP"));
	curScroll += scrollNLRdir == 1 ? -0.78 : scrollNLRdir == 2 ? 0.78 : 0;
	if( scrollNLRdir == 0 ) curScroll = 0;
	DX_DRAW("graphics\\stageselect\\cursor.png", SP->SCRSZX/2-GI("STGSELECT_ALLSX")/2 + selectedIdx*GI("STGSELECT_ALL1SX") + curScroll,
		GI("STGSELECT_ALLY"), 0, 0, GI("STGSELECT_CURSORSX"), GI("STGSELECT_CURSORSY") );

	// �g
	DX_DRAW("graphics\\stageselect\\Image_frame.png", SP->SCRSZX/2-GI("STGSELECT_FRAMESX")/2,
		GI("STGSELECT_IMGY")-10, 0, 0, GI("STGSELECT_FRAMESX"), GI("STGSELECT_FRAMESY"));

}

/**
* �ۑ��ް���۰�ނ�����@-
*/
void StageSelect::LoadSaveData()
{
	// �����l
	saveStageTdx = 6;

	// ���W�X�g���[����ǂݍ���
	HKEY key;
	DWORD dwDisposition;

	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\GekidanShimi\\SplendidStage"), 0, REG_NONE, REG_OPTION_NON_VOLATILE,
		KEY_WRITE|KEY_READ, NULL, &key, &dwDisposition) == ERROR_SUCCESS)
	{
		DWORD dwType = REG_DWORD;
		DWORD dwSize = sizeof( DWORD );
		BYTE res = 0;
		RegQueryValueEx( key, TEXT("SaveIdx"), NULL, &dwType, &res, &dwSize ); 
		saveStageTdx = (int) res;
	}

	RegCloseKey( key );

	// 6�������l�n�̂��߁A�ޯ��T�|�[�g��o�O��h�����߂ɁA6�ȉ��͒���
	if( saveStageTdx < 6 ) {
		saveStageTdx = 6;
	}
	if( saveStageTdx > GAMECONTROL->GetStageManager()->GetLastStageIdx() - GAMECONTROL->GetStageManager()->GetFirstStageIdx() ){
		saveStageTdx = GAMECONTROL->GetStageManager()->GetLastStageIdx() - GAMECONTROL->GetStageManager()->GetFirstStageIdx();
	}
}

/**
* ���̽ð�ނɑI�����ڂ�
*/
void StageSelect::GoToLeft()
{
	if( selectedIdx > 0 /*&& scrollNLRdir == 0*/){
		selectedIdx--;
		// ��۰�
		scroll = -GI("STGSELECT_SLDDIST");
		scrollNLRdir = 1;
		// �A���t�@̪���
		alpha = 0.0f;
		// ����
		curScroll = GI("STGSELECT_ALL1SX");
	}
}


/**
* �E�̽ð�ނɑI�����ڂ�
*/
void StageSelect::GoToRight()
{
	if( selectedIdx < GAMECONTROL->GetStageManager()->GetLastStageIdx() - 
		GAMECONTROL->GetStageManager()->GetFirstStageIdx() )
	{
		selectedIdx++;
		scroll = GI("STGSELECT_SLDDIST");
		scrollNLRdir = 2;
		// �A���t�@̪���
		alpha = 0.0f;
		// ����
		curScroll = -GI("STGSELECT_ALL1SX");
	}
}
