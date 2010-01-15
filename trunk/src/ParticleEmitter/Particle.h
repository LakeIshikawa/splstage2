#pragma once

#include <d3dx9.h>

#define PARTICLE_Z 0.0f

//! �߰è��
/****************************************************************//**
*	\see ParticleEmitter
*	\nosubgrouping
********************************************************************/
class Particle 
{

public:
	Particle () : mCurPos(D3DXVECTOR3(0,0,0)), mCurVel(D3DXVECTOR3(0,0,0)), isAlive(false){}
	virtual ~Particle (void){}

	//! ����
	virtual D3DXVECTOR3* GetPos() { return &mCurPos; }
	//! ����
	virtual D3DCOLOR* GetColor() { return &mColor; }
	//! ����
	virtual D3DXVECTOR3* GetSpd() { return &mCurVel; }
	//! ����	
	virtual bool IsAlive() { return isAlive; }
	//! ����	
	virtual void SetAlive(bool rAlive) { isAlive = rAlive; }
	//! ����
	virtual void SetPos(int rX, int rY) { mCurPos.x = rX; mCurPos.y = rY; mCurPos.z = PARTICLE_Z; }
	//! ����
	virtual void SetSpd(float rX, float rY) { mCurVel.x = rX; mCurVel.y = rY; mCurVel.z = 0.0f; }
	//! ����
	virtual void SetColor(D3DCOLOR rColor) { mColor = rColor; }

	//! �ʒu�ɑ��x�𑫂�����
	virtual void UpdatePos() { mCurPos += mCurVel; }

protected:
	//! �ʒu
	D3DXVECTOR3 mCurPos;
	//! ���x
	D3DXVECTOR3 mCurVel;
	//! �F
	D3DCOLOR mColor;
	//! �����Ă��邩
	bool isAlive;
};
