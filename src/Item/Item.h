#include <exception>
using namespace std;

#include "..\\Mob\\Collidable.h"
#include "..\\MapCollision\\PointMapCollider.h"
#include "..\\Management\\GameControl.h"

#pragma once

//! ����
/****************************************************************//**
*	�۲݂����ƌ��ʂ�����
*	\nosubgrouping
********************************************************************/
class Item : public Collidable
{
public: 

	//! �W���R���X�g���N�^
	Item( int rX, int rY );
	//! �W���f�X�g���N�^
	virtual ~Item();

	//! �X�V
	void Move();

	//! ������
	void Launch(float rSpX, float rSpY, bool rMuki);
	
	//! ����
	virtual void DoEffect() = 0;

	//! ���̨��
	virtual string GetGraphic() = 0;
	virtual string GetEffectGraphic() = 0;

	//! �Ȃ�炩�̌��ʸ��̨��(����߂��Ȃ�)
	virtual void CustomEffect() {}

	//! �����蔻��
	void CollisionResponse( ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId );

protected:
	PointMapCollider* mMapCollider;

};

//! ����
/****************************************************************//**
*	��񂲁E���߼���
*	\nosubgrouping
********************************************************************/
class ItRingo : public Item
{
public:
	ItRingo( int rX, int rY ) : Item( rX, rY ){}
	~ItRingo(){}

	void DoEffect() { GAMECONTROL->GetJiki()->RestoreEmpacy(GI("ITEM_EMPUP")); }
	string GetGraphic() { return "graphics\\item\\Apple_a.png"; }
	string GetEffectGraphic() { return "graphics\\item\\enpathy_up.png"; }
};

//! ����
/****************************************************************//**
*	��񂲁E�ݼ�݁�
*	\nosubgrouping
********************************************************************/
class ItAoRingo : public Item
{
public:
	ItAoRingo( int rX, int rY ) : Item( rX, rY ){}
	~ItAoRingo(){}

	void DoEffect() { GAMECONTROL->GetJiki()->RestoreTension(GI("ITEM_TENUP")); }
	string GetGraphic() { return "graphics\\item\\Apple_b.png"; }
	string GetEffectGraphic() { return "graphics\\item\\tension_up.png"; }
};

//! ����
/****************************************************************//**
*	��񂲁E�ݼ�݁�
*	\nosubgrouping
********************************************************************/
class ItKinRingo : public Item
{
public:
	ItKinRingo( int rX, int rY ) : Item( rX, rY ), mAlpha(0.0f), mAlphaSp(0.03f){}
	~ItKinRingo(){}

	void DoEffect() { GAMECONTROL->GetJiki()->RestoreLife(1); }
	string GetGraphic() { return "graphics\\item\\Apple_c.png"; }
	string GetEffectGraphic() { return "graphics\\item\\1up.png"; }
	void CustomEffect() 
	{ 
		mAlpha += mAlphaSp;
		if( mAlpha >= 1.0f || mAlpha <= 0 ) mAlphaSp *= -1;
		DX_SCROLL_SCREEN_DRAW("graphics\\effect\\effectsample.png", mX-20, mY-50, 0, 0, 128, 128, mAlpha); 
	}

private: 
	float mAlpha;
	float mAlphaSp;
};
