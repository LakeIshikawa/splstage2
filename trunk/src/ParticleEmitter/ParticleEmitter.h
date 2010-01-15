#pragma once

#include <d3dx9.h>
#include <string>

using namespace std;

#include "Particle.h"

//! ﾊﾟｰﾃｨｸﾙ発生装置
/****************************************************************//**
*	万能です。
*	ﾀﾞｲﾚｸﾄXのPointSpriteのﾗｯﾌﾟを提供しています。
*	\nosubgrouping
********************************************************************/
class ParticleEmitter
{
public:

	//! 頂点のﾀｲﾌﾟ宣言
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3 position;
		D3DCOLOR color;
	};

	#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)


/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
	ParticleEmitter(int rX, int rY, int rNumParticles, string rTexture);
	virtual ~ParticleEmitter(void);
/*@}*/


public:

	//! 1ﾌﾚｰﾑ処理
	virtual void Update() = 0;
	//! 描画
	void Render();
	//! ﾊﾟｰﾃｨｸﾙの初期化
	virtual void InitParticles(D3DCOLOR rColor) = 0;

	//! 再生開始
	void Start() { mStatus = PRODUCING; }
	//! 再生停止
	void Stop() { mStatus = STOP; }

	//! ﾊﾟｰﾃｨｸﾙを取得できるｲﾝﾀｰﾌｪｰｽ
	virtual Particle* GetParticle(int rIdx) = 0;

protected:

	//! 頂点ﾊﾞｯﾌｧｰの作成
	void CreateVertexBuffer(int size, DWORD usage, DWORD fvf);



	//! 頂点ﾊﾞｯﾌｧｰ
	LPDIRECT3DVERTEXBUFFER9 mVertexBuffer;

	//! ﾃｸｽﾁｬ
	LPDIRECT3DTEXTURE9 mTexture;

	//! ﾊﾟｰﾃｨｸﾙ数
	int mNumParticles;

	//! 位置
	int mX;
	int mY;

	//! ｽﾃｰﾀｽ
	enum { PRODUCING, STOP } mStatus;

};
