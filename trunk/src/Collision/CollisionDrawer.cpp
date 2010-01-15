#include ".\collisiondrawer.h"
#include "Circle.h"
#include "Rect.h"
#include "..\\Management\\GameControl.h"

CollisionDrawer::CollisionDrawer()
{
	mCollision = NULL;
}

CollisionDrawer::~CollisionDrawer(void)
{
}

/*
	�ؼޮ݂�ݒ肷��
*/
void CollisionDrawer::SetCollision(Collision* rCollision)
{
	mCollision = rCollision;
}

/*
	�`��
*/
void CollisionDrawer::Draw()
{
	if(mCollision){

		// �����̐}�`�Ƒ���
		list<CollShape*>::iterator th_it = mCollision->mlShapeLst.begin(), th_en = mCollision->mlShapeLst.end();
		for( ; th_it!=th_en; th_it++ ){

			// �ꎞ�I�ȃp�����[�^�[
			int cx = mCollision->GetParent()->GetX();
			int cy = mCollision->GetParent()->GetY();
			bool cm = mCollision->GetParent()->GetMuki();
			int csx = mCollision->GetParent()->GetFrameSizeX();
			int csy = mCollision->GetParent()->GetFrameSizeY();

			//�~
			Circle* circle = dynamic_cast<Circle*>(*th_it);
			if(circle){
				int drawx;
				if(cm)
					drawx = cx + (csx - circle->X()) - GAMECONTROL->GetStageManager()->GetCurScrollPointer();
				else
					drawx = cx + circle->X() - GAMECONTROL->GetStageManager()->GetCurScrollPointer();

				int drawy = cy + circle->Y();
				DX_DRAW_CIRCLE(drawx, drawy, circle->Hankei());
			}

			//�����`
			Rect* rect = dynamic_cast<Rect*>(*th_it);
			if(rect){
				int top, right, left, bottom;
				if(cm){
					right = cx + (csx - rect->Right()) - GAMECONTROL->GetStageManager()->GetCurScrollPointer();
					left = cx + (csx - rect->Left()) - GAMECONTROL->GetStageManager()->GetCurScrollPointer();
				}
				else{
					right = cx + rect->Right() - GAMECONTROL->GetStageManager()->GetCurScrollPointer();
					left = cx + rect->Left() - GAMECONTROL->GetStageManager()->GetCurScrollPointer();
				}

				top = cy + rect->Top();
				bottom = cy + rect->Bottom();
				
				DX_DRAW_RECT(right, top, left, bottom);
			} // if( rect )
		} // for
	} // if (mCollision)
}
