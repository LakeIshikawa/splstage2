#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiDamage.h"
#include "..\\..\\..\\Animation\\Animation.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\MobDrawer\\SimpleDrawer.h"

/************************************************************//**
*	��Ұ��݂̍쐬
****************************************************************/
void ASOokamiDamage::BuildAnimation(ActionState* rPrevState)
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\Damage.txt" );
}

/************************************************************//**
*	@see ActionState
****************************************************************/
void ASOokamiDamage::OnEnter()
{
	mMutekiJikan->Start();
}

/************************************************************//**
*	���i�ړ��ƏI������
****************************************************************/
bool ASOokamiDamage::Update() 
{
	//˯��ޯ�
	// �I������
	return (mAnimation->GetLoopCount() == 2);
}

void ASOokamiDamage::OnExit() 
{}
