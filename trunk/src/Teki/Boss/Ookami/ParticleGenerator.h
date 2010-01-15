#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\Collidable.h"

//! �j�мު�ڰ�
/****************************************************************//**
*	�j�Ђ��юU�炩��
*	\nosubgrouping
********************************************************************/
class ParticleGenerator
{

	public: 
		//! �W���ݽ�׸�
		ParticleGenerator(int rX, int rY) :
		  mMode(PG_LINEAR), mTimer(0.0f), mCurPartIdx(0), mX(rX), mY(rY){}

		//! �j�Ђ̔�΂���
		enum PG_MODE {
			PG_RANDOM,	//! ���̨��ؿ��������тɎg�p
			PG_LINEAR	//! ���̨�������������ԂɎg�p
		};


		//! �j�Ђ̔��˂�\��
		void BookPartThrow(float rAngle, float rSpeed, 
			float rInterval, string rGraphicSrc);

		//! Ӱ�ނ̎w��
		void SetMode(PG_MODE rMode);


		//! ��΂�
		void Generate();

protected:

	//! �ް��Ƃ��ēo�^����锭�˗\��̵�޼ު��
	class PartThrow{
	public:
		PartThrow(float rAngle, float rSpeed, float rInterval, string rGraphic):
		  angle(rAngle), speed(rSpeed), interval(rInterval), graphic(rGraphic), thrown(false){}

		float angle;
		float speed;
		float interval;
		string graphic;
		bool thrown;
	};

	PG_MODE mMode;
	vector<PartThrow> mData;
	float mTimer;
	int mCurPartIdx;
	int mX;
	int mY;
};

//! �j��
/****************************************************************//**
*	�j��
*	\nosubgrouping
********************************************************************/
class Particle : public Collidable
{
public:
	
	//! �W���ݽ�׸�
	Particle(float rAngle, float rSpeed, string rGraphic, 
		int rStartX, int rStartY);

	//! 1�ڰя���
	void Move();

	//! �����蔻�艞��
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);

private:
	//! �p�x
	float mAngle;
	//! ��]�p�x
	float mRotAngle;
	//! ���̨��
	string mGraphic;

	// �ݒ�萔
	float OOKAMI_HSPTROTSP;

};
