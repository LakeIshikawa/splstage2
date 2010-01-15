#pragma once

#include <d3dx9.h>
#include <string>

using namespace std;

#include "Particle.h"

//! �߰è�ٔ������u
/****************************************************************//**
*	���\�ł��B
*	�޲ڸ�X��PointSprite��ׯ�߂�񋟂��Ă��܂��B
*	\nosubgrouping
********************************************************************/
class ParticleEmitter
{
public:

	//! ���_�����ߐ錾
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3 position;
		D3DCOLOR color;
	};

	#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)


/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
	ParticleEmitter(int rX, int rY, int rNumParticles, string rTexture);
	virtual ~ParticleEmitter(void);
/*@}*/


public:

	//! 1�ڰя���
	virtual void Update() = 0;
	//! �`��
	void Render();
	//! �߰è�ق̏�����
	virtual void InitParticles(D3DCOLOR rColor) = 0;

	//! �Đ��J�n
	void Start() { mStatus = PRODUCING; }
	//! �Đ���~
	void Stop() { mStatus = STOP; }

	//! �߰è�ق��擾�ł������̪��
	virtual Particle* GetParticle(int rIdx) = 0;

protected:

	//! ���_�ޯ̧��̍쐬
	void CreateVertexBuffer(int size, DWORD usage, DWORD fvf);



	//! ���_�ޯ̧�
	LPDIRECT3DVERTEXBUFFER9 mVertexBuffer;

	//! ø���
	LPDIRECT3DTEXTURE9 mTexture;

	//! �߰è�ِ�
	int mNumParticles;

	//! �ʒu
	int mX;
	int mY;

	//! �ð��
	enum { PRODUCING, STOP } mStatus;

};
