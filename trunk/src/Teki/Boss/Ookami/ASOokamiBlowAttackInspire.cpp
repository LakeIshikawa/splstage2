#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiBlowAttackInspire.h"
#include "ASOokamiBlowAttackAspire.h"
#include "OokamiHouseStraw.h"
#include "OokamiHouseRog.h"
#include "OokamiHouseBrick.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Animation\\Animation.h"

void shuffle(OokamiHouse*(*houses)[3]);

/************************************************************//**
*	�ʒu���̍쐬
****************************************************************/
void ASOokamiBlowAttackInspire::BuildAnimation(ActionState* rPrevState)
{
	if( !mAnimation ){
		mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\BlowAttackInspire.txt" );
	}
}

/************************************************************//**
*	�Ƃ������ظ��Ă���
****************************************************************/
void ASOokamiBlowAttackInspire::OnEnter() 
{
	// ���̂�
	if( brick == NULL ){

		// �Ƃ��o��������
		int stposX[3] = { GI("OOKAMI_HSPX1"), GI("OOKAMI_HSPX2"), GI("OOKAMI_HSPX3") };

		OokamiHouse* houses[3];

		straw = new OokamiHouseStraw();
		rog = new OokamiHouseRog();
		brick = new OokamiHouseBrick();

		houses[0] = straw;
		houses[1] = rog;
		houses[2] = brick;

		shuffle(&houses);

		for(int i=0; i<3; i++){
			houses[i]->SetPosX(stposX[i]);
			GAMECONTROL->GetMobManager()->Request(houses[i], true);
		}
	}
}

/************************************************************//**
*	��ʂɓ����ďI���
****************************************************************/
bool ASOokamiBlowAttackInspire::Update() {
	// �I������
	return mAnimation->GetLoopCount() == 1;
}

/************************************************************//**
*	���̽ðĂɈڂ�
****************************************************************/
void ASOokamiBlowAttackInspire::OnExit() 
{
	// ���̽ï��
	mParent->AddNextAction(new ASOokamiBlowAttackAspire());
}

/**
	�\�[�g
*/
void shuffle(OokamiHouse*(*houses)[3])
{
	OokamiHouse* shuffled[3];

    int pick = rand()%3;
	shuffled[0] = (*houses)[pick];

	int pick2 = rand()%3;
	if( (*houses)[pick2] == shuffled[0] ) {
		if( pick2<2 )pick2++;
		else pick2--;
	}

	shuffled[1] = (*houses)[pick2];

	int pick3 = 0;
	while( (*houses)[pick3] == shuffled[0] || (*houses)[pick3] == shuffled[1] ) pick3++;

	shuffled[2] = (*houses)[pick3];

	(*houses)[0] = shuffled[0];
	(*houses)[1] = shuffled[1];
	(*houses)[2] = shuffled[2];
}