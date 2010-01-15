#pragma once

#include <string>

using namespace std;

/*
	�X�e�[�W�N���A�A�A�N�g�X�^�[�g�Ȃǂ�
	�\�����镶���O���t�B�b�N�̊Ǘ�

	���Ɉꖇ�̕\���܂ŉ\�ƂȂ�܂��B
	�����̃O���t�B�b�N�𓯎��ɕ\���������ꍇ�A
	���̃R���g���[���[�̕����C���X�^���X����������
	���������B
	
	:UGLY:
	:UGLY:
*/
class TxtGraphicController
{
public:
	TxtGraphicController();
	~TxtGraphicController();

	enum POSITION{
		CENTER
	};

	// �A���t�@��̪��޲݂���
	void ShowWithAlphaFade(POSITION rPos, int rSx, int rSy, 
		string rGraphic, float rTime, float rSp);
	
	// �E���當���������Ă��āA��������^�񒆂Ɏ~�܂��āA���ɏo�čs��
	void ShowWithEnterFromRight( int rY, int sX, int sY, string rGraphic, float rSpX );

	// �\���͏I���������𔻒肷��
	bool IsFinished();

	// ���ݍs���Ă����Ƃ𒆒f���A������Ԃɖ߂�܂�
	void Reset();

	void Draw();

private:
	float mTimer;
	
	enum STATUS{
		FADING_IN,
		DISPLAY,
		FADING_OUT,
		ENTERING,
		ENT_STOPPING,
		EXITING
	} mStatus;

	// �����ۑ�
	float mAlpha;
	float mSp;
	float mTime;
	POSITION mPos;
	int mSx;
	int mSy;
	string mGraphic;

	int mY;
	int mX;
	float mSpX;

	bool mIsFinished;

};