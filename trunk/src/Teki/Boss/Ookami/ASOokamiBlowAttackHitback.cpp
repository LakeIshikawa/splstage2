#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiBlowAttackHitback.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Animation\\Animation.h"


/************************************************************//**
*	�Ƃ���
****************************************************************/
void ASOokamiBlowAttackHitback::OnEnter() 
{
	mSpX = GF("OOKAMI_BKHTSPX") * mMuki?-1:1;
	mSpY = -GF("OOKAMI_BKHTSPY");
}


/************************************************************//**
*	��ʂɓ����ďI���
****************************************************************/
bool ASOokamiBlowAttackHitback::Update() {
	
	//˯��ޯ�
	mSpY += SP->GRAVITY;
	mY += mSpY;
	mX += mSpX;

	// ���n
	if( mY >= OOKAMI_STARTY ){
		mY = OOKAMI_STARTY;
		mSpY = 0;
		mSpX = 0;
	}

	// �I������
	return mAnimation->GetLoopCount() == 15;
}

/************************************************************//**
*	���̽ðĂɈڂ�
****************************************************************/
void ASOokamiBlowAttackHitback::OnExit() 
{
}
