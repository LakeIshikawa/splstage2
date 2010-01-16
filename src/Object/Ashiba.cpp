#include "Ashiba.h"
#include "..\\Management\\GameControl.h"
#include "..\\Mob\\IRideCapable.h"

/**
	�W���R���X�g���N�^
*/
Ashiba::Ashiba(int rXPx, int rYPx, float rZ, string rGraphic, int rSizeX, int rSizeY)
{
	ASHIBASX = rSizeX;
	ASHIBASY = rSizeY;

	mGraphic = rGraphic;

	mX = rXPx;
	mY = rYPx - ASHIBASY + SP->CHSZY;
	mZ = rZ;

	AddTarget(GAMECONTROL->GetJiki());

	AddFrame(0);
	AddIndexedRect(0, SP->GRID_BOUND, 0, 0, 0, ASHIBASX, 1);
}

/**
	�W���f�X�g���N�^
*/
Ashiba::~Ashiba()
{}

/************************************************************//**
*	\return ����̕�
****************************************************************/
int Ashiba::GetFrameSizeX()
{
	return ASHIBASX;
}

/************************************************************//**
*	\return ����̏c��
****************************************************************/
int Ashiba::GetFrameSizeY()
{
	return ASHIBASY;
}


/************************************************************//**
*	1�ڰя���
****************************************************************/
void Ashiba::Move()
{
	UpdateRiders();
	Draw();

	//���ޯ��
	if(mDrawer){
		mDrawer->SetCollision(pCollision->GetCurFrame());
		mDrawer->Draw();
	}
}

/************************************************************//**
*	��q�̑��x�ɑ���̑��x�𑫂�����
****************************************************************/
void Ashiba::UpdateRiders()
{
	// �폜�\��̏�q���폜����
	for each (IRideCapable* delrider in mDelRiders){
		mRiders.remove(delrider);
	}
	mDelRiders.clear();

	// ��q���X�V
	for each (IRideCapable* rider in mRiders){

		// ����̈ʒu�ɍ��킹�āA���x�𑫂�����
		rider->AddSpX(mSpX);
		rider->SetY(mY+ mSpY + GetCollRect()->Top() - rider->GetRideRect()->Bottom());

		// ���E�ɏ�q�����E�ɏo�Ă��Ă��܂�����~�낷
		int aleft  = mX + GetCollRect()->Left();
		int aright = mX + GetCollRect()->Right();
		int rleft  = rider->GetX() + rider->GetRideRect()->Left();
		int rright = rider->GetX() + rider->GetRideRect()->Right();

		// �������ꂩ��O�ꂽ��~���
		if( rleft >= aright || rright < aleft )
		{
			GetOff(rider);
			rider->GetOffResponse(this);
		}
	}
}

/************************************************************//**
*	���
*	\param rRider ��낤�����
*	���ɏ���Ă���ꍇ�͉������Ȃ�
****************************************************************/
void Ashiba::GetOn(IRideCapable* rRider)
{
	for each(IRideCapable* rider in mRiders){
		if ( rider == rRider ) return;
	}
	mRiders.push_back(rRider);
}

/************************************************************//**
*	�~���
*	\param rRider �~��悤�����
****************************************************************/
void Ashiba::GetOff(IRideCapable* rRider)
{
	mDelRiders.push_back(rRider);
}

/************************************************************//**
*	�`��
****************************************************************/
void Ashiba::Draw()
{
	DX_SCROLL_DRAW(mGraphic, mX, mY, 0, 0, ASHIBASX, ASHIBASY);
}

/************************************************************//**
*	�W���̓����蔻��\n
*
*	�q���C��������Ώۂ���B�G�Ƒ���̓����艞���́A�G���S������B
*	
*	\param rCollObject	����������̵�޼ު��(��F�۲�)
*	\param rThisGroupId	��������GROUPID(���X�ɂ���ĈႤ)
*	\param rOpGroupId	����������̵�޼ު�Ă�GROUPID(���X�ɂ���ĈႤ)
*
****************************************************************/
void Ashiba::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	IRideCapable* rider = dynamic_cast<IRideCapable*>(rCollObject);

	if( rider && rOpGroupId == SP->GRID_BOUND ){
		float ashiba_x = mX;
		float ashiba_y = mY;

		Rect* jbound = rider->GetRideRect(); //�۲݂��޳�ިݸ��ޯ��
		Rect* abound = GetCollRect();

		float sax = (ashiba_x + abound->Left()) + (abound->Right()-abound->Left())/2 - ((rider->GetX() + jbound->Left())+ (jbound->Right()-jbound->Left())/2);
		float say = (ashiba_y + abound->Top()) + (abound->Bottom()-abound->Top())/2 - ((rider->GetY() + jbound->Top()) + (jbound->Bottom()-jbound->Top())/2);

		float merix = (sax>0) ? (rider->GetX() + (rider->GetFrameSizeX() - jbound->Left()) - (ashiba_x + abound->Left())) : (ashiba_x + abound->Right() - (rider->GetX()+jbound->Left()));
		float meriy = (say>0) ? (rider->GetY() + jbound->Bottom() - (ashiba_y + abound->Top())) : (ashiba_y + abound->Bottom() - (rider->GetY()+jbound->Top()));

		// ���E����
		if( merix < meriy )
		{
			// �ʒu�C��
			if( sax<0 )		// �E
				RespRight(rider, jbound);
			else			// ��
				RespLeft(rider, jbound);

			// ���x�C��
			//if( (sax<0 && rider->GetSpX()<0) || (sax>0 && rider->GetSpX()>0)) {rider->SetSpX(0);}
		}

		// �㉺����
		else
		{
			if( say>0 ){	// ��
				RespUp(rider, jbound);
			}
			else			// ��
				RespDown(rider, jbound);
		}
	}
}

/************************************************************//**
*	�����艞���E��
****************************************************************/
void Ashiba::RespLeft(IRideCapable* rider, Rect* jbound)
{
	//rider->SetX(mX + GetCollRect()->Left() - (rider->GetFrameSizeX()- jbound->Left()));
}

/************************************************************//**
*	�����艞���E�E
****************************************************************/
void Ashiba::RespRight(IRideCapable* rider, Rect* jbound)
{
	//rider->SetX(mX + GetCollRect()->Right() - jbound->Left());
}

/************************************************************//**
*	�����艞���E��
****************************************************************/
void Ashiba::RespUp(IRideCapable* rider, Rect* jbound)
{
	// ���x�C��
	if(rider->GetSpY()>0) {
		rider->SetY(mY + mSpY + GetCollRect()->Top() - jbound->Bottom());
		rider->SetSpY(0);

		// �����
		GetOn(rider);
		rider->RideResponse(this);
	}
}

/************************************************************//**
*	�����艞���E��
****************************************************************/
void Ashiba::RespDown(IRideCapable* rider, Rect* jbound)
{
	//rider->SetY(mY + mSpY + GetCollRect()->Bottom() - jbound->Top());

	// ���x�C��
	//if(rider->GetSpY()<0) rider->SetSpY(0);
}

/*

*/
float Ashiba::GetSpX()
{
	return mSpX;
}

/*

*/
float Ashiba::GetSpY()
{
	return mSpY;
}

/*

*/
Rect* Ashiba::GetCollRect()
{
	return (Rect*)pCollision->GetFrame(0)->GetIndexedShape(0);
}

