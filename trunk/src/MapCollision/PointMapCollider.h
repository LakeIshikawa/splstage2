#include <string>
#include <list>
#include <exception>
using namespace std;

#pragma once

#include "MapCollider.h"
#include "..\\Stage\\Map.h"

class Movable;

//! �_���w�肵����ŁA�����蔻����s��
/****************************************************************//**
*	SuperAtariHantei()�̱ٺ�ؽ�т��g�p
*	\nosubgrouping
********************************************************************/
class PointMapCollider: public MapCollider
{
	public: 

		//! �W���ݽ�׸�
		PointMapCollider( Movable* rTarget );
		//! �W���޽�׸�
		~PointMapCollider();

		//! @see MapCollider
		int GetCollision(MC_SIDE rSide);
		//! @see MapCollider
		int GetAdjustedPosition(MC_SIDE rSide);
		//! @see MapCollider
		void CollisionRecognition();

		//! �����蔻��p�̓_�̒ǉ�
		void AddCollisionPoint(MC_SIDE rSide, int rX, int rY);


	private: 
		//! �ʒu�⑬�x�A�����x���擾�\�����ޯ�
		Movable* mTarget;
		
		//! �_�̃��X�g
		Map::HITPOINT mCollisionPointsX;
		Map::HITPOINT mCollisionPointsY;

		//! ����̏o�͗p
		int mShirabe[4];  // ���������Ƃ��ɁA�ǂ̈ʒu��Ԃ��i���̎��̍��W�j
		int mAtari[4];	 // �������Ă���׸ނ�����
};
