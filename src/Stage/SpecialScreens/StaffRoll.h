#pragma once

#include "..\\Stage.h"


/*
	�X�^�b�t���[��
*/
class StaffRoll : public Stage
{
public:
	StaffRoll();
	~StaffRoll();

	void Load();
	void UnLoad();
	void Process();

	// �f�o�C�X���[�X�g�̂Ƃ�
	void OnLostDevice();
	void OnRestoredDevice();

private:

	//! ������Ԃɂ���
	void Init();

	//! �`��
	void DrawStaffWithAlphaMask();

	//! �e�N�X�`���̓��I�쐬
	void BuildStaffTexture();

	//! D3D���\�[�X�̃��[�h
	void LoadResources();
	//! D3D���\�[�X�̊J��
	void ReleaseResources();

	int stage;
	float scrp;

	LPDIRECT3DTEXTURE9 mEdStr;
	LPDIRECT3DTEXTURE9 mEdStr2;
	LPD3DXRENDERTOSURFACE mRenderer;
};