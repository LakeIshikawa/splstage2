#pragma once

#include "Ashiba.h"
#include <d3dx9.h>
#include <list>

using namespace std;

//! ���C�g�𓖂Ă�Ƃ����������Ȃ�����
/****************************************************************//**
*	����E�Ƃ炳��Ă��Ȃ��ƌ����Ȃ��o�[�W����
*	\nosubgrouping
********************************************************************/
class AshibaInvisible : public virtual Ashiba
{
/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
public:
	AshibaInvisible(int rXPx, int rYPx, float Z, int sizex, int sizey);
	virtual ~AshibaInvisible(void);
/*@}*/

	//! �`��
	void Draw();

	// ���[�X�g�f�o�C�X
	void OnLostDevice();
	void OnRestoredDevice();

	// ���\�[�X�̊m��(D3D�n)
	void LoadResources();
};
