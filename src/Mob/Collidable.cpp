#include ".\collidable.h"
#include "..\\Collision\\Circle.h"
#include "..\\Collision\\Rect.h"
#include "..\\Collision\\Collision.h"
#include "..\\Management\\GameControl.h"

Collidable::Collidable(void)
{
	pCollision = new CollisionSet( );
	mDrawer = new CollisionDrawer();
	AddTask(this);

}

Collidable::~Collidable(void)
{
	delete pCollision;
	delete mDrawer;

	// ���ׂĂ̓S�����玩���Ƃ������ޯĂ�r������
	GAMECONTROL->GetStageManager()->GetCurrentStage()->
		GetHaichi()->RemoveAshibaTargets(this);

	// ���ׂĂ̓S�����玩���Ƃ������ޯĂ�r������
	REMOVE_FROM_TARGET_LIST( ICollidable );
}

/*
	�����蔻�艞��ؽĂ𽷬݂��āA
	�����蔻����������s���܂��B

	���������Ƃ���������ޯ����Ă�

	�}�`���߱�ЂƂɑ債�Ĉ����ޯ��֐����Ă΂�܂��B
	�d������̏����͊O�ł���Ă��������B
	��F�ð�����g���āA��񂠂������ꍇ�͂������Ă������N����Ȃ��悤�ɂ���Ƃ�

*/
void Collidable::RunTask()
{
	//�����蔻������
	Collision* cur_frame = pCollision->GetCurFrame();
	if(cur_frame){
		list<ICollidable*>::iterator it = mlTargets.begin(), en = mlTargets.end();
		for( ; it!=en; it++ ){
			ICollidable* item = (*it);
			Collision* coll_frame = item->GetCurFrame();
			//coll_frame = item->GetCurFrame();
			cur_frame->Hantei(coll_frame, this, *it);
		}
	}
}

/*
	�����蔻������ޯĂ�ǉ�����
*/
void Collidable::AddTarget(ICollidable* rTarget)
{
	mlTargets.push_back(rTarget);
}

/*
	�����蔻������ޯĂ��폜����
*/
void Collidable::RemoveTarget(ICollidable* rTarget)
{
	mlTargets.remove(rTarget);
}


//////////////////////////protected//////////////////////////////
/*
	�����蔻��p�̉~��ǉ�����
*/
void Collidable::AddCircle(int rFrameIdx, int rGroupId, int rX, int rY, int rHankei)
{
	pCollision->GetFrame(rFrameIdx)->AddCircle( rGroupId, rX, rY, rHankei );
}

/*
	�ԍ����̒����`�̒ǉ�
*/
void Collidable::AddIndexedRect(int rFrameIdx, int rGroupId, int rShapeIdx, int rLeft, int rTop, int rRight, int rBottom)
{
	pCollision->GetFrame(rFrameIdx)->AddIndexedRect(rGroupId, rShapeIdx, rLeft, rTop, rRight, rBottom);
}

/*
	�����蔻��p�̉~��ǉ�����
	�ʒu����ŕς�����悤�ɁA���̐}�`�̔ԍ����w�肷��
*/
void Collidable::AddMovableCircle(int rFrameIdx, int rGroupId, int rShapeIdx, int rX, int rY, int rHankei)
{
	pCollision->GetFrame(rFrameIdx)->AddMovableCircle( rGroupId, rShapeIdx, rX, rY, rHankei);
}

/*
	�ԍ��t���̉~���Đݒ肷��
*/
void Collidable::SetCircle(int rFrameIdx, int rShapeIdx, int rX, int rY, int rHankei)
{
	CollShape* collshape = pCollision->GetCurFrame()->GetIndexedShape(rShapeIdx);

	Circle* circle = dynamic_cast<Circle*>(collshape);

	if(circle){
		circle->Set(rX, rY, rHankei);
	}
}


/*
	�����蔻��p�̒����`��ǉ�����
*/
void Collidable::AddRect(int rFrameIdx, int rGroupId, int rLeft, int rTop, int rRight, int rBottom)
{
	pCollision->GetFrame(rFrameIdx)->AddShape(
		new Rect(pCollision->GetFrame(rFrameIdx), rGroupId, rLeft, rTop, rRight, rBottom)
		);
}

// �ڰђǉ�
void Collidable::AddFrame(int rBango)
{
	Collision* newcoll = new Collision( this );
	pCollision->AddFrame(rBango, newcoll);
	
}

// �ڰѐݒ�
void Collidable::SetCurFrame(int rBango)
{
	pCollision->SetFrame(rBango);
}

// ���ڰт��擾
Collision* Collidable::GetCurFrame()
{
	return pCollision->GetCurFrame();
}