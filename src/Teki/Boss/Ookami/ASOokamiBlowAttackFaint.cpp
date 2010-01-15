#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiBlowAttackFaint.h"
#include "ASOokamiBlowAttackHitback.h"
#include "ASOokamiJumpingDeath.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Animation\\Animation.h"
#include "..\\..\\..\\Light\\Light.h"


/************************************************************//**
*	��Ұ��݂����o��
****************************************************************/
void ASOokamiBlowAttackFaint::BuildAnimation(ActionState* rPrevState) 
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\BlowAttackFaint.txt" );
}

/************************************************************//**
*	�T�̕W���̓����蔻��̉���
****************************************************************/
void ASOokamiBlowAttackFaint::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// �۲�
	if( jiki && !mMutekiJikan->IsMuteki() ){

		// �۲݂̍U���A�T�̖h��
		if( rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_BOGYO ){
			// HP�����
			mHp--;

			// ���S�̏ꍇ
			if( mHp <= 0 ) {
				// ����
				mParent->BreakInActionNoResume( new ASOokamiJumpingDeath() );
			}
			// ��Ұ�ނ����̏ꍇ
			else{
				// �T���ɂ�
				mParent->BreakInActionNoResume( new ASOokamiBlowAttackHitback() ); // TODO: OokamiDamage
			}
		}

		// �۲݂̖h��
		else if( rOpGroupId == SP->GRID_BOGYO ){
			// �۲݂��ɂ�
			jiki->InflictDamage();
		}
	}
}

/************************************************************//**
*	��ʂɓ����ďI���
****************************************************************/
bool ASOokamiBlowAttackFaint::Update() {
	// �I������
	return mAnimation->GetLoopCount() == 6;
}

/************************************************************//**
*	���̽ðĂɈڂ�
****************************************************************/
void ASOokamiBlowAttackFaint::OnExit() 
{
	// �����ŉƂ����̋�������ł����ƍ�蒼�����悤�A
	// ������ق��J������
	rog = NULL;
	straw = NULL;
	brick = NULL;
}
