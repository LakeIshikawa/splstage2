#pragma once

#include <list>
#include <vector>

#include "Map.h"
#include "HaichiObj.h"
#include "..\\Object\\AshibaMovable.h"
#include "..\\Object\\Tenbin.h"

using namespace std;

class CheckpointController;

/*
	�G�̔z�u�ް�
*/
class Haichi : public Map
{
public:
	Haichi(void);
	~Haichi(void);

	int	Load(string rFname, CheckpointController* checkpointController);
	void UnLoad();
	void Process();

	//! �G�𕜊�������
	void RestoreTekiAfter( int rPos );

	//! ����������Q�b�g
	AshibaMovable* GetAshibaMov(int idx);

	//! ��������̐�
	int GetAshibaMovNum();

	//! �����������^�[�Q�b�g�Ƃ��Đݒ肷��
	void SetAshibaTargets( Collidable* rToThisObj );
	//! ����ɐݒ肳��Ă������ޯĂ𖢐ݒ肷��
	void RemoveAshibaTargets( ICollidable* rRemoveMe );

	//! �V���̐�
	int GetTenbinNum();

	//! �V�����Q�b�g
	Tenbin* GetTenbin(int idx);

	//! ���f�[�^���Q��
	int GetData(int rX, int rY);

private:

	// ����p�̓��ʂȏ���
	bool IsAshiba(int data);
	void ProcessAshiba(int data, int x, int y);

	list< HaichiObj* > mHaichiListOrig; // mXPx���ŕ��ёւ��Ă��邪�z��
	list< HaichiObj* > mHaichiListTemp; // mXPx���ŕ��ёւ��Ă��邪�z��

	vector< AshibaMovable* > mAshibaMovList; // ��������
	vector< Ashiba* > mAshibaList; // ��������ȊO�̑���
	vector< Tenbin* > mTenbinList; // �V��

	int mShutugenStartPoint;

	// �ݒ�萔
	int SHUTSUGEN_POINTX;

	// ��̏������y������
	int CHECKPOINT_NO;
	int MOVASHIBA_NO;
	int MOVASHIBA2_NO;
	int MOVASHIBA3_NO;
	int ASHIBA_NO;
	int ASHIBA2_NO;
	int ASHIBA3_NO;
	int INVASHIBA3_NO;
	int TENBIN_NO;

};
