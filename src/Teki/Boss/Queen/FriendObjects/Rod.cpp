#include <string>
#include <vector>
#include <exception>
#include <d3dx9.h>
using namespace std;

#include "Rod.h"
#include "Heart.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Jiki\\Jiki.h"
#include "..\\..\\..\\..\\Collision\\Circle.h"

/************************************************************//**
*�@�ݒ�萔��ǂݍ���
****************************************************************/
Rod::Rod(float rAngle, bool rDir) : mAngle( rAngle ), mStartAngle( rAngle ), mDir( rDir )
{
	RODSPANG = GF("RODSPANG");
	STD_FADEIN_SP = GF("STD_FADEIN_SP");

	// �ʒu
	mSizeX = GI("RODSX");
	mSizeY = GI("RODSY");

	mX = GI("RODX");
	mY = GI("RODY");

	// ������
	mStatus = APPEAR;
	mAlpha = 0.0f;
	mHeartShot = 0;

	AddFrame(0);
}

/************************************************************//**
*	1�ڰя���
****************************************************************/
void Rod::Move()
{
	// �۲݂Ƃ̂����蔻��(:UGLY:)
	if( CollidesWithHeroine() ){
		CollisionResponse( GAMECONTROL->GetJiki(), 0, 0 );
	}
	
	// ����
	switch( mStatus ){
	
	case APPEAR:

		// ̪��޲�
		if( mAlpha < 1.0f ){
			mAlpha += STD_FADEIN_SP;
		}
		else{
			//����
			mStatus = ROTATE;
		}
		break;

	case ROTATE:
		{
			// ��]
			mAngle += (mDir?1.0:-1.0) * (RODSPANG*(D3DX_PI/180)) * SP->FrameTime;
			
			// ʰĂ̔���
			if( fabs( mAngle - mStartAngle ) >= (RODSPANG*(D3DX_PI/180))*mHeartShot){
				mHeartShot++;
				GAMECONTROL->GetMobManager()->Request( 
					new Heart( mX+mSizeX/2 + (mSizeY-10)*cos( mAngle-D3DX_PI/2 ), 
						mY+(mSizeY-10) + (mSizeY-10)*sin( mAngle-D3DX_PI/2 ), 
						mAngle),
					true );
				// SE
				GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_boss1_atack.wav");
			}

			// �I��
			if( fabs(mAngle - mStartAngle) >= D3DX_PI*2 ){
				mStatus = DISAPPEAR;
			}
			break;
		}

	case DISAPPEAR:
		{
			mAlpha -= 0.1f;
			if( mAlpha <= 0.0f ){
				mAlpha = 0.0f;
				mStatus = INACTIVE;
			}
			break;
		}
	}

	// �`��
	Draw();
}

/************************************************************//**
*	�۲݂Ƃ̓����蔻��
*
*	:UGLY:
*	���ې��Ȃ��A�g���܂킵���Ȃ��B�@�l�p������ŉ�]������̂�
*	���̃Q�[���̒��ŁA���̃��b�h�����Ȃ��B���������āA���b�h����
*	�̃��x���ł�����Ⴂ�܂��B�۲݂̂����蔻����d�����܂��B
*	
*	���̃��\�b�h�����A�����q�͐�΂ɐ^�����Ȃ��ŉ������B
****************************************************************/
bool Rod::CollidesWithHeroine()
{
	// �۲݂̊ۂ�����
	Jiki* jiki = GAMECONTROL->GetJiki();
	int jx = jiki->GetX();
	int jy = jiki->GetY();
	
	Circle* cl[3];

	cl[0] = new Circle(jiki->GetCurFrame(), 0, 64, 37, 16);
	cl[1] = new Circle(jiki->GetCurFrame(), 0, 67, 65, 12);
	cl[2] = new Circle(jiki->GetCurFrame(), 0, 69, 99, 20);
	
	// ���b�h�̎l�p
	Rect* thisRect;
	thisRect = new Rect(pCollision->GetCurFrame(), 0, 0, 0, mSizeX, mSizeY);

	// ��]�s��
	D3DXMATRIX rot;
	D3DXVECTOR2 center(mX+mSizeX/2, mY+(mSizeY-10));
	D3DXMatrixTransformation2D(&rot, NULL, 0.0f, NULL, &center, -mAngle, NULL);

	for( int i=0; i<3; i++ ){
		// ���W�ϊ�
		D3DXVECTOR3 res;
		D3DXVECTOR3 src(cl[i]->X() + jx, cl[i]->Y() + jy, 0.0f);
		D3DXVec3TransformCoord( &res, &src, &rot );
		cl[i]->Set(res.x, res.y, cl[i]->Hankei());
		
		// ����
		if ( Rect::RectCircle(thisRect, cl[i], mX, mY, 0, mSizeX, 0, 0, 0, 0 ) ) return true;
	}

	return false;
}

/************************************************************//**
*	�`��
****************************************************************/
void Rod::Draw()
{
	DX_CENTERROT_DRAWALPHA("graphics\\teki\\queen\\boss4_stick.png", 
		mX, mY, 0, 0, mSizeX, mSizeY, mAngle, mSizeX/2, mSizeY-10, mAlpha);
}

/************************************************************//**
*	�����蔻��̉���
****************************************************************/
void Rod::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// �۲�
	if( jiki && rOpGroupId == SP->GRID_BOGYO  || rOpGroupId == SP->GRID_KOUGEKI ){
		jiki->InflictDamage();
	}
}

/************************************************************//**
*	\return �����I����Ă��邩
****************************************************************/
bool Rod::HasFinished()
{
	return mStatus == INACTIVE;
}