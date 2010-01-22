#include ".\koumori.h"
#include "..\\Management\\GameControl.h"

/* ｱﾆﾒｰｼｮﾝﾃﾞｰﾀ */
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

/* ｸﾞﾗﾌｨｯｸﾃﾞｰﾀ */
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

	// 当たり判定
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
			// 自機の位置を取得して間合いと比較する
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
	地面の高さを調べ、蝙蝠がちょうどそのKOMOCHOTENﾋﾟｸｾﾙ
	上に飛べるような、初速を求めます。

	地面の位置と蝙蝠のyの差がKOMOCHOTENより小さいときは、
	蝙蝠が壁をすり抜けていきます。
	そんな配置がないように望みます。
*/
float Koumori::DetermineShosoku(float rRaiseForce)
{
	// 地面の位置を調べる
	int shirabe = GetAtHtPointY();

	int atari = 1;
	while( MAP_ATHT( GetAtHtPointX(), shirabe ) == 1 )
		shirabe += SP->CHSZY;

	// 微調整
	shirabe -= shirabe%SP->CHSZY;

	return sqrt( abs(2.0f * rRaiseForce * ( shirabe - GetAtHtPointY() - KOMOCHOTEN ) ) );
		
}

// ﾗｲﾄ応答
void Koumori::ResponseAka()		{ Nigeru(); }
void Koumori::ResponseAo()		{ Nigeru(); }
void Koumori::ResponseMidori()	{ Nigeru(); }
void Koumori::ResponseMushoku() { Nigeru(); }

void Koumori::RunTask(){
	Teki::RunTask();
	LightResponseAble::RunTask();
}

// 逃げる
void Koumori::Nigeru()
{
	if( mStatus == WAIT){
		mStatus = NIGE;

		//SE
		if( !IsGamenGai() )
			GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_bat_fly.wav");
		
		// 画面の端、どっちが近いを判定する
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