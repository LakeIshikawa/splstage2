#include ".\koumori.h"
#include "..\\Management\\GameControl.h"

/* ��Ұ����ް� */
int Koumori::sAniData[][MAX_DATA] =
{
	{ 0, 99 },		// WAIT
	{ 1, 2, 3, 99 },	// MOVE
	{ 1, 2, 3, 99 }	// NIGE
};

float Koumori::sAniTimeData[][MAX_DATA] =
{
	{ 0.2f },		// WAIT
	{ 0.2f, 0.2f },	// MOVE
	{ 0.2f, 0.2f }	// NIGE
};

/* ���̨���ް� */
char Koumori::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\ene_bat.png",
	"graphics\\teki\\ene_bat.png",
	"graphics\\teki\\ene_bat.png",
};

Koumori::Koumori(int rXPx, int rYPy)
{
	MAAI_HABA = GI("MAAI_HABA");
	KOMORAISE = GF("KOMORAISE");
	KOMOSPX = GF("KOMOSPX");
	KOMOCHOTEN = GI("KOMOCHOTEN");

	mSizeX = GI("KOMOSX");;
	mSizeY = GI("KOMOSY");;

	mX = rXPx;
	mY = rYPy - mSizeY + SP->CHSZY;

	mStatus = WAIT;

	// �����蔻��
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, 28, 28, 14);
}

Koumori::~Koumori(void)
{
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_bat_fly.wav");
}

void Koumori::_Move()
{
	SetAnim(mStatus);

	switch( mStatus ){
	
		case WAIT:{
			// ���@�̈ʒu���擾���Ċԍ����Ɣ�r����
			int jiki_x = GAMECONTROL->GetJiki()->GetAtHtPointX();
			int maai_left = GetAtHtPointX() - MAAI_HABA;
			int maai_right = maai_left + MAAI_HABA;

			if( jiki_x > maai_left && jiki_x < maai_right ){
				mStatus = MOVE;
				//SE
				if( !IsGamenGai() )
					GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_bat_fly.wav");
				mSpY = DetermineShosoku( KOMORAISE );
				mSpX = -KOMOSPX;
			}
				  }
			break;

		case MOVE:			
			mAccY = -KOMORAISE;
			break;

		case NIGE:
			break;
	}

	//SE STOP
	if( IsGamenGai() )
		GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_bat_fly.wav");


	Teki::Draw();

	mSpX += mAccX;
	mSpY += mAccY;
	mX	 += mSpX;
	mY	 += mSpY;
}

/*
	�n�ʂ̍����𒲂ׁA�啂����傤�ǂ���KOMOCHOTEN�߸��
	��ɔ�ׂ�悤�ȁA���������߂܂��B

	�n�ʂ̈ʒu���啂�y�̍���KOMOCHOTEN��菬�����Ƃ��́A
	�啂��ǂ����蔲���Ă����܂��B
	����Ȕz�u���Ȃ��悤�ɖ]�݂܂��B
*/
float Koumori::DetermineShosoku(float rRaiseForce)
{
	// �n�ʂ̈ʒu�𒲂ׂ�
	int shirabe = GetAtHtPointY();

	int atari = 1;
	while( MAP_ATHT( GetAtHtPointX(), shirabe ) == 1 )
		shirabe += SP->CHSZY;

	// ������
	shirabe -= shirabe%SP->CHSZY;

	return sqrt( abs(2.0f * rRaiseForce * ( shirabe - GetAtHtPointY() - KOMOCHOTEN ) ) );
		
}

// ײĉ���
void Koumori::ResponseAka()		{ Nigeru(); }
void Koumori::ResponseAo()		{ Nigeru(); }
void Koumori::ResponseMidori()	{ Nigeru(); }
void Koumori::ResponseMushoku() { Nigeru(); }

void Koumori::RunTask(){
	Teki::RunTask();
	LightResponseAble::RunTask();
}

// ������
void Koumori::Nigeru()
{
	if( mStatus == WAIT){
		mStatus = NIGE;

		//SE
		if( !IsGamenGai() )
			GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_bat_fly.wav");
		
		// ��ʂ̒[�A�ǂ������߂��𔻒肷��
		int scp = GAMECONTROL->GetStageManager()->GetCurScrollPointer();
		float angle;

		if( GetAtHtPointX() - scp <= SP->SCRSZX/2 )
			angle = 7*D3DX_PI/6;
		else {
			angle = 11*D3DX_PI/6;
			mMuki = 1;
		}

		mSpX = cos( angle ) * KOMOSPX;
		mSpY = sin( angle );
	}
}