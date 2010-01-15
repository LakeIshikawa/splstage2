#pragma once

#include "Ashiba.h"
#include <d3dx9.h>
#include <list>

using namespace std;

//! ライトを当てるときしか見えない足場
/****************************************************************//**
*	足場・照らされていないと見えないバージョン
*	\nosubgrouping
********************************************************************/
class AshibaInvisible : public virtual Ashiba
{
/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
public:
	AshibaInvisible(int rXPx, int rYPx, float Z, int sizex, int sizey);
	virtual ~AshibaInvisible(void);
/*@}*/

	//! 描画
	void Draw();

protected:
	LPDIRECT3DTEXTURE9 mDrawingTexture;
};
