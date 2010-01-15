#include "InterfaceView.h"
#include "..\\Management\\GameControl.h"
#include "..\\Stage\\SeigenJikan.h"

//�\�����W
int	InterfaceView::sIndData[][INDMAX] = { 
	{ 11, 28, 45, 62, 79, 96, 113, 130, 147, 164 },	//	�ݼ��X
	{ 11, 12, 17, 20, 23, 24,  21,  18,  16,  12 },	//	�ݼ��Y
	{ 11, 28, 45, 62, 79, 96, 113, 130, 147, 164 },	//	���߼�X
	{ 48, 49, 54, 57, 60, 61,  58,  55,  53,  49 },	//	���߼�Y

};

InterfaceView::InterfaceView(Jiki* rJiki, MakuController* rMaku)
{
	EMP_MAX = GF("EMP_MAX");
	TEN_MAX = GF("TEN_MAX");
	DODAI_X = GI("DODAI_X");
	DODAI_Y = GI("DODAI_Y");
	CLOKESIZE = GI("CLOKESIZE");
	PINSIZE = GI("PINSIZE");
	EMPSIZE = GI("EMPSIZE");
	TENSIZE = GI("TENSIZE");
	LIFESIZE = GI("LIFESIZE");
	CHAINX = GI("CHAINX");
	CHAINY = GI("CHAINY");
	CHAINSX = GI("CHAINSX");
	CHAINSY = GI("CHAINSY");

	mJiki = rJiki;
	mMaku = rMaku;

	mSeigenTime = 0.0f;
	mAniTimer = 0.0f;
	mAniNo = 0;
	mPls = 1;

	mHidden = false;
}

InterfaceView::~InterfaceView()
{}

/*
	�`��
*/
void InterfaceView::Draw()
{

	//��-------------------------------------------------------
	mMaku->Draw();

	if( !mHidden ){
		//�y��
		DX_DRAW("graphics\\interface\\inte_dodai.png", DODAI_X, DODAI_Y,  0, 0, GI("DODAI_SX"), GI("DODAI_SY"));

		Jikan();//��������
		Enpashi();//���߼��ް��
		Tenshon();//�ݼ�ݹް��
		Zanki();//�c�@

		// �`�F�C��
		int chain = GAMECONTROL->GetJiki()->GetChainLv();
		DX_DRAW("graphics\\interface\\Chain_actor.png", CHAINX, CHAINY,  chain*CHAINSX, 0, (chain+1)*CHAINSX, CHAINSY);
	}
}
/*
	��������
*/
void InterfaceView::Jikan()
{
	float maxtime = GAMECONTROL->GetStageManager()->GetCurrentStage()->GetSeigenJikan()->GetMaxJikan();
	float gettime = GAMECONTROL->GetStageManager()->GetCurrentStage()->GetSeigenJikan()->GetRemainingTime();
	float time = gettime * ( ( D3DX_PI * 2.0 ) / maxtime );
	
	// ���v(3/4�ɂȂ�����_��)
	mSeigenTime = maxtime * ( 3.0 / 4.0 );
	if( mSeigenTime <= gettime ){
		mAniTimer += SP->FrameTime;
		if( mAniTimer >= GF("CLOKEANITIME") ){
			mAniTimer = 0;
			mAniNo += mPls;
			if( mAniNo > 5 || mAniNo < 1 )
				mPls *= -1;
		}
		DX_DRAW("graphics\\interface\\inte_blink.png", 
			DODAI_X, DODAI_Y, CLOKESIZE * mAniNo, 0, CLOKESIZE * mAniNo + CLOKESIZE, CLOKESIZE);
	}

	//���v�̐j
	int scpx = GAMECONTROL->GetStageManager()->GetCurScrollPointer();
	DX_SCROLL_ROT_DRAW("graphics\\interface\\inte_clock_pin.png",
		(DODAI_X + GI("PIN_X")) + scpx , DODAI_Y + GI("PIN_Y"), 0, 0, PINSIZE, PINSIZE, time );

}

/*
	���߼�(ײ�)
*/
void InterfaceView::Enpashi()
{
	for( int i=0; i < mJiki->GetEmpa(); i++ )
		DX_DRAW("graphics\\interface\\inte_enpasy.png", 
			DODAI_X + CLOKESIZE + sIndData[0][i], DODAI_Y + sIndData[1][i], 0, 0, EMPSIZE, EMPSIZE);

}

/*
	�ݼ��
*/
void InterfaceView::Tenshon()
{
	int ten1 = (int)mJiki->GetTens() / 10;//10�̈�
	int ten2 = (int)mJiki->GetTens() % 10;//1�̈�(5�ȏゾ�����甼�����\��)
	for( int i=0; i < ten1+1; i++ ){
		if( i == ten1 ){
			//1�̈ʂ�5�ȏゾ�����甼�����\��
			if( 5 <= ten2 ){
				DX_DRAWALPHA("graphics\\interface\\inte_tension.png",
					DODAI_X + CLOKESIZE + sIndData[2][i], DODAI_Y + sIndData[3][i],
						0, 0, TENSIZE, TENSIZE, GF("TEN_ALPHA"));
			}
		}else{
			DX_DRAW("graphics\\interface\\inte_tension.png",
				DODAI_X + CLOKESIZE + sIndData[2][i], DODAI_Y + sIndData[3][i], 0, 0, TENSIZE, TENSIZE);
		}
	}
}

/*
	�c�@
*/
void InterfaceView::Zanki()
{
	int life = mJiki->GetLife();
	if( life < 0 ) life = 0;//0�ȉ��ɂȂ����ꍇ�A0��
	DX_DRAW("graphics\\interface\\inte_zannki.png",	
		DODAI_X + CLOKESIZE + GI("LIFE_X"), DODAI_Y,  0+(life*LIFESIZE), 0, LIFESIZE+(life*LIFESIZE), LIFESIZE);

}
