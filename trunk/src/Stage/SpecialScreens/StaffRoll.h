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

private:

	void Init();
	void DrawStaffWithAlphaMask();
	void BuildStaffTexture();

	int stage;
	float scrp;


	LPDIRECT3DTEXTURE9	mStaffRollTx;
	
};