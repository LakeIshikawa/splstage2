#pragma once

#include <d3dx9.h>

#define PARTICLE_Z 0.0f

//! ﾊﾟｰﾃｨｸﾙ
/****************************************************************//**
*	\see ParticleEmitter
*	\nosubgrouping
********************************************************************/
class Particle 
{

public:
	Particle () : mCurPos(D3DXVECTOR3(0,0,0)), mCurVel(D3DXVECTOR3(0,0,0)), isAlive(false){}
	virtual ~Particle (void){}

	//! ｱｸｾｽ
	virtual D3DXVECTOR3* GetPos() { return &mCurPos; }
	//! ｱｸｾｽ
	virtual D3DCOLOR* GetColor() { return &mColor; }
	//! ｱｸｾｽ
	virtual D3DXVECTOR3* GetSpd() { return &mCurVel; }
	//! ｱｸｾｽ	
	virtual bool IsAlive() { return isAlive; }
	//! ｱｸｾｽ	
	virtual void SetAlive(bool rAlive) { isAlive = rAlive; }
	//! ｱｸｾｽ
	virtual void SetPos(int rX, int rY) { mCurPos.x = rX; mCurPos.y = rY; mCurPos.z = PARTICLE_Z; }
	//! ｱｸｾｽ
	virtual void SetSpd(float rX, float rY) { mCurVel.x = rX; mCurVel.y = rY; mCurVel.z = 0.0f; }
	//! ｱｸｾｽ
	virtual void SetColor(D3DCOLOR rColor) { mColor = rColor; }

	//! 位置に速度を足しこむ
	virtual void UpdatePos() { mCurPos += mCurVel; }

protected:
	//! 位置
	D3DXVECTOR3 mCurPos;
	//! 速度
	D3DXVECTOR3 mCurVel;
	//! 色
	D3DCOLOR mColor;
	//! 生きているか
	bool isAlive;
};
