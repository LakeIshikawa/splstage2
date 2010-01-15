#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "ASJumpingDeath.h"
#include "ASWaitForMaku.h"
#include "ASFadeOutAndStageClear.h"
#include "..\\..\\..\\Light\\Light.h"

/************************************************************//**
*	
****************************************************************/
void ASJumpingDeath::OnEnter() 
{
	// �ެ���
	mSpX = GF("SHINIPATT_SPX");
	mAccX = 0;
	mSpY = -GF("SHINIPATT_SHOSP");
	mAccY = SP->GRAVITY;

	// �۲݂�ײĂ��Ƃ߂�
	GAMECONTROL->GetJiki()->SetSuperPause();
	GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();

	// �����ؽ�
	mParent->RemoveAllActions(this);
}


/************************************************************//**
*	��ʂɓ����ďI���
****************************************************************/
bool ASJumpingDeath::Update() 
{

	mSpY += mAccY;
	mX += mSpX;
	mY += mSpY;

	// �I������
	return mY > SP->SCRSZY*2;
}

/************************************************************//**
*	���̽ðĂɈڂ�
****************************************************************/
void ASJumpingDeath::OnExit() 
{
	// �������
	GAMECONTROL->GetMaku()->Close();
	mParent->QueueAction( new ASWaitForMaku(true) );

	// ̪��ޱ��
	mParent->QueueAction( new ASFadeOutAndStageClear() );

}
