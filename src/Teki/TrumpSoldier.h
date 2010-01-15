#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\Mob\\Collidable.h"

class AnimationSet;
class SimpleDrawer;
class PointMapCollider;

//! �g�����v��
/****************************************************************//**
*	���E�����ĕǂɔ��]����
*	���ōU������
*	\nosubgrouping
********************************************************************/
class TrumpSoldier : public Collidable
{

public:

	//! �W���ݽ�׸�
	TrumpSoldier(int rX, int rY);
	//! ������(���̉��̒���ɌĂ�)
	void Build();

	//! @see Movable
	void Move();
	//! �`��
	void Draw();
	
	//! �����蔻�艞��
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

	//! ���̨���̎擾���@
	virtual string GetWalkGraphic() = 0;
	virtual string GetAttackGraphic() = 0;
	virtual string GetSasuGraphic() = 0;
	virtual string GetDieGraphic() = 0;

private:

	//! ����
	void Die();
	//! ���]����
	void KabeHanten();
	//! ����
	void Fall();


	// ��Ұ��ݾ��
	AnimationSet* mAnimSet;
	// �`��
	SimpleDrawer* mSDrawer;
	// ϯ�߂Ƃ̓����蔻��
	PointMapCollider* mMapCollider;

	// �����蔻����ڰ�
	enum FRAMES{
		FR_NONE,
		FR_ATTACK
	};

	// �ð��
	enum STATUS{
		ST_WALK,
		ST_ATTACK,
		ST_DIE
	} mStatus;

	// ��Ұ���
	enum ANIM{
		AN_WALK,
		AN_ATTACK,
		AN_SASU,
		AN_HIKU,
		AN_DIE
	} mAnims;


	// �ݒ�萔
	float TRUMPHEISP;
	int TRUMPHEIHANI;
};


//! ʰẴg�����v��
/****************************************************************//**
*	���E�����ĕǂɔ��]����
*	���ōU������
*	\nosubgrouping
********************************************************************/
class TrumpSoldierHearts : public TrumpSoldier
{
public:
	TrumpSoldierHearts(int rX, int rY) : TrumpSoldier(rX, rY){}
	
	string GetWalkGraphic() { return "graphics\\teki\\queen\\ene_tranpma1_walk.png"; }
	string GetAttackGraphic() { return "graphics\\teki\\queen\\ene_tranpman1_atk0.png"; }
	string GetSasuGraphic() { return "graphics\\teki\\queen\\ene_tranpman1_atk1.png"; }
	string GetDieGraphic() { return "graphics\\teki\\queen\\ene_tranpman1_down.png"; }
};

//! �_�C���̃g�����v��
/****************************************************************//**
*	���E�����ĕǂɔ��]����
*	���ōU������
*	\nosubgrouping
********************************************************************/
class TrumpSoldierDiamonds : public TrumpSoldier
{
public:
	TrumpSoldierDiamonds(int rX, int rY) : TrumpSoldier(rX, rY){}
	
	string GetWalkGraphic() { return "graphics\\teki\\queen\\ene_tranpma2_walk.png"; }
	string GetAttackGraphic() { return "graphics\\teki\\queen\\ene_tranpman2_atk0.png"; }
	string GetSasuGraphic() { return "graphics\\teki\\queen\\ene_tranpman2_atk1.png"; }
	string GetDieGraphic() { return "graphics\\teki\\queen\\ene_tranpman2_down.png"; }
};

//! �N���[�o�[�̃g�����v��
/****************************************************************//**
*	���E�����ĕǂɔ��]����
*	���ōU������
*	\nosubgrouping
********************************************************************/
class TrumpSoldierClovers : public TrumpSoldier
{
public:
	TrumpSoldierClovers(int rX, int rY) : TrumpSoldier(rX, rY){}
	
	string GetWalkGraphic() { return "graphics\\teki\\queen\\ene_tranpma3_walk.png"; }
	string GetAttackGraphic() { return "graphics\\teki\\queen\\ene_tranpman3_atk0.png"; }
	string GetSasuGraphic() { return "graphics\\teki\\queen\\ene_tranpman3_atk1.png"; }
	string GetDieGraphic() { return "graphics\\teki\\queen\\ene_tranpman3_down.png"; }
};

//! �N���[�o�[�̃g�����v��
/****************************************************************//**
*	���E�����ĕǂɔ��]����
*	���ōU������
*	\nosubgrouping
********************************************************************/
class TrumpSoldierSpades : public TrumpSoldier
{
public:
	TrumpSoldierSpades(int rX, int rY) : TrumpSoldier(rX, rY){}
	
	string GetWalkGraphic() { return "graphics\\teki\\queen\\ene_tranpma4_walk.png"; }
	string GetAttackGraphic() { return "graphics\\teki\\queen\\ene_tranpman4_atk0.png"; }
	string GetSasuGraphic() { return "graphics\\teki\\queen\\ene_tranpman4_atk1.png"; }
	string GetDieGraphic() { return "graphics\\teki\\queen\\ene_tranpman4_down.png"; }
};