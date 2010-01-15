#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ParticleGenerator.h"
#include "..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*	�j�Ђ̔��˂�o�^���܂�
*	\param rAngle ���˂̏��p�x
*	\param rSpeed ���x
*	\param rInterval ���̔��˂܂ł̎���
*	\param rGraphicScr �g�p������̨����̧�ٖ�
****************************************************************/
void ParticleGenerator::BookPartThrow(float rAngle, float rSpeed, 
			float rInterval, string rGraphicSrc)
{
	mData.push_back(PartThrow(rAngle, rSpeed, rInterval, rGraphicSrc));
}

/************************************************************//**
*	����Ӱ�ނ�ݒ肵�܂�
****************************************************************/
void ParticleGenerator::SetMode(PG_MODE rMode)
{
	mMode = rMode;
}

/************************************************************//**
*	1�ڰя���
*	�j�Ђ𑱁X�ƍ쐬���Ĕ�΂��B�j�Ђ̏�����MobController�ƂȂ�
****************************************************************/
void ParticleGenerator::Generate()
{
	// �܂����˂��Ă��Ȃ���Δ��˂���
	if( !mData[mCurPartIdx].thrown ){
		mData[mCurPartIdx].thrown = true;
		Particle* newpart = 
			new Particle(mData[mCurPartIdx].angle, mData[mCurPartIdx].speed, 
			mData[mCurPartIdx].graphic, mX, mY);

		GAMECONTROL->GetMobManager()->Request(newpart, true);
	}

	// ���̔j�Ђ܂ő҂�
	WAIT_TIMER(mTimer, mData[mCurPartIdx].interval)
		switch( mMode ){
			case PG_LINEAR:
				{
					mCurPartIdx++;
					if( mCurPartIdx >= mData.size() ) {

						//�S�j�Ѓ��Z�b�g
						for (int i=0; i<mData.size(); i++) mData[i].thrown = false;
						mCurPartIdx = 0;
					}
					break;
				}

			case PG_RANDOM:
				{
					mData[mCurPartIdx].thrown = false;
					mCurPartIdx = rand()%(mData.size());
					break;
				}
	}
	WAIT_END
}



/************************************************************//**
*	������
****************************************************************/
Particle::Particle(float rAngle, float rSpeed, string rGraphic, 
		int rStartX, int rStartY)
{
	mX = rStartX;
	mY = rStartY;
	mSpX = cos(rAngle) * rSpeed;
	mSpY = sin(rAngle) * rSpeed;
	mGraphic = rGraphic;
	mSizeX = GI("OOKAMI_HSPTSX");
	mSizeY = GI("OOKAMI_HSPTSY");
	OOKAMI_HSPTROTSP = GF("OOKAMI_HSPTROTSP")*((rand()%2)==0?1:-1);

	mRotAngle = 0.0f;

	// �����蔻��
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, 24, 24, 24);
	AddTarget(GAMECONTROL->GetJiki());

}

/************************************************************//**
*	1�ڰя���
****************************************************************/
void Particle::Move()
{
	// ��ʊO�͏��ł���
	DieIfGamenGai();

	// ����
	mSpY += SP->GRAVITY;
	mX += mSpX;
	mY += mSpY;

	// ��]
	mRotAngle += OOKAMI_HSPTROTSP;
	if( mRotAngle >= D3DX_PI*2 ) mRotAngle = 0.0f;

	//�`��
	DX_SCROLL_ROT_DRAW(mGraphic, mX, mY, 0, 0, mSizeX, mSizeY, mRotAngle);
}


/************************************************************//**
*	�����蔻�艞��
****************************************************************/
void Particle::CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);
	jiki->InflictDamage();
}
