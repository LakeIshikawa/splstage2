#include ".\haichi.h"
#include "..\\Management\\GameControl.h"
#include "Checkpoint\\CheckpointController.h"
#include "Checkpoint\\Checkpoint.h"
#include "HaichiObjStatic.h"
#include "..\\Object\\AshibaMovable.h"
#include "..\\Object\\AshibaInvisible.h"

Haichi::Haichi(void)
{
	// ��̏������y������
	CHECKPOINT_NO = GI("CHECKPOINT_NO");
	MOVASHIBA_NO = GI("MOVASHIBA_NO");
	MOVASHIBA2_NO = GI("MOVASHIBA2_NO");
	MOVASHIBA3_NO = GI("MOVASHIBA3_NO");
	ASHIBA_NO = GI("ASHIBA_NO");
	ASHIBA2_NO = GI("ASHIBA2_NO");
	ASHIBA3_NO = GI("ASHIBA3_NO");
	INVASHIBA3_NO = GI("INVASHIBA3_NO");
	TENBIN_NO = GI("TENBIN_NO");

	mShutugenStartPoint = 0;
	SHUTSUGEN_POINTX = GI("SHUTSUGEN_POINTX");
}

Haichi::~Haichi(void)
{
}

/*
	�w�肳�ꂽ̧�ق���z�u�ް���ǂݍ��݂܂��B
	���̏�Ŕz�u���ް�̫�ϯĂ�ϊ����āA�z�u
	��޼ު�Ă����܂��B

	�z�uؽĂ̍��ڂ�XPx���Ⴂ���ɂȂ�͂��B

	�װ�̏ꍇ�A1��Ԃ��܂��B
*/
int Haichi::Load(string rFname, CheckpointController* checkpointController)
{
	// �ް���ǂݍ���
	if(Map::LoadFromFile(rFname)) return 1;

	
	// ؽĂ��쐬
	for(int x=0; x<SP->CHIPNX*mNGamen; x++)
		for(int y=0; y<SP->CHIPNY; y++)
		{
			int data = (*(mData[y]))[x];

			// �`�F�b�N�|�C���g
			if( data == CHECKPOINT_NO && checkpointController ){
				checkpointController->Add(new Checkpoint(x*SP->CHSZX, y*SP->CHSZY));
			}

			else if( IsAshiba(data ) ){
				ProcessAshiba(data, x, y);
			}
					
			// �V��
			else if( data == TENBIN_NO ){
				Tenbin* newTenbin = new Tenbin(x*SP->CHSZX, y*SP->CHSZY, -1.0f);
				HaichiObjStatic* newObj = new HaichiObjStatic(x*SP->CHSZX, y*SP->CHSZY);
				newObj->SetObject(newTenbin);
				mTenbinList.push_back( newTenbin );

				mHaichiListOrig.push_back( newObj );
				mHaichiListTemp.push_back( newObj );
			}

			// ���ʂ̓G���è���łȂ���޼ު��
			else if( data!=0 ){ // 0�ȊO
				HaichiObj* newObj = new HaichiObj(x*SP->CHSZX, y*SP->CHSZY, data);
				mHaichiListOrig.push_back( newObj );
				mHaichiListTemp.push_back( newObj );
			}
		}

	// �`�F�b�N�|�C���g�𕢂�
	if( checkpointController)
		checkpointController->ReverseList();

	return 0; //OK
}

/*
	���\�[�X���������
*/
void Haichi::UnLoad()
{
	// �f�[�^���
	vector<vector<int>*>::iterator it;
	for(it = mData.begin(); it != mData.end(); it++){
		vector<int>* sublist = *it;
		//delete sublist;
	}
	mData.clear();

	// ���X�g�����
	mHaichiListOrig.clear();
	mHaichiListTemp.clear();

	// ������A�����[�h
	for(int i=0; i<mAshibaList.size();i++) 
	{ 
		delete mAshibaList[i];
		mAshibaList[i] = NULL;
	}
	mAshibaMovList.clear();
	mAshibaList.clear();

	// �V�����A�����[�h
	mTenbinList.clear();
}

/*
	���݂̔z�uؽĂ̈�Ԗڂ�MOB�o������ׂ����ǂ�������������B
	�o���̏ꍇ�Aظ��Ă��āAؽĂ���O���Ă��܂��܂��B

	MOB���o������͈̂��݂̂ƂȂ�܂��B
*/
void Haichi::Process()
{
	// ��۰��߲������擾
	int scpx = (int)GAMECONTROL->GetStageManager()->GetCurScrollPointer();

	// ����
	while( !mHaichiListTemp.empty() && (mHaichiListTemp.front()->GetXPx() <  SHUTSUGEN_POINTX + scpx ) ){

		HaichiObj* obj = mHaichiListTemp.front();
		
		// �ÓI�I�u�W�F�N�g
		if( obj->GetNo()==-1 ){
			Movable* reqobj = ((HaichiObjStatic*)obj)->GetObject();
			GAMECONTROL->GetMobManager()->Request( reqobj, false );
			mHaichiListTemp.pop_front();
		}

		// ���I�I�u�W�F�N�g
		else{ 
			GAMECONTROL->GetMobManager()->Request( obj->GetNo(), obj->GetXPx(), obj->GetYPx(), true );
			mHaichiListTemp.pop_front();
		}
	}
}

/************************************************************//**
* rPos����(�E)�ɔz�u���ꂽ�G���������܂��B
*	\param rPos ���̈ʒu(X)�ȍ~�͑S�Ă̓G����������
*	\note ��۰ق�ظ��Ă�����܂ŁA�G������܂���B\n
*	����ҿ��ނŁu�Ĕz�u�v����邾���ł�
****************************************************************/
void Haichi::RestoreTekiAfter(int rPos)
{
	mHaichiListTemp.clear();

	for each ( HaichiObj* obj in mHaichiListOrig ){
		if( !ISTEKI(obj->GetNo()) || obj->GetXPx() >= rPos ){
			mHaichiListTemp.push_back( obj );
		}
	}

	// ��������̈ʒu�����Z�b�g
	for each ( AshibaMovable* am in mAshibaMovList ){
		am->Reset();
	}

	// �V���̃��Z�b�g
	for each ( Tenbin* tb in mTenbinList ){
		tb->Reset();
	}
}

/************************************************************//**
* ����������擾
*	\param idx ����ԍ�(0�`9)
****************************************************************/
AshibaMovable* Haichi::GetAshibaMov(int idx)
{
	return mAshibaMovList[idx];
}

/************************************************************//**
* \return ��������̐�
****************************************************************/
int Haichi::GetAshibaMovNum()
{
	return mAshibaMovList.size();
}

/************************************************************//**
* �w�肳�ꂽCollidable�ɑS���̑���𓖂������ޯĂƂ��ēo�^����B
* \param rToThisObj ���̃I�u�W�F�N�g�ɓo�^����
****************************************************************/
void Haichi::SetAshibaTargets(Collidable* rToThisObj)
{
	for each(Ashiba* a in mAshibaList){
		a->AddTarget(rToThisObj);
	}
}

/************************************************************//**
* ����ɐݒ肳��Ă���w������ޯĂ��폜����
* \param rRemoveMe ���X�g����O������
****************************************************************/
void Haichi::RemoveAshibaTargets(ICollidable* rRemoveMe)
{
	for each(Ashiba* a in mAshibaList){
		if(a) a->RemoveTarget(rRemoveMe);
	}
}

/************************************************************//**
* �V�����擾
*	\param idx �V���ԍ�(�z�u���ꂽ����)
****************************************************************/
Tenbin* Haichi::GetTenbin(int idx)
{
	return mTenbinList[idx];
}

/************************************************************//**
* \return �V���̐�
****************************************************************/
int Haichi::GetTenbinNum()
{
	return mTenbinList.size();
}


/************************************************************//**
* �z��̃f�[�^���擾����B
* �f�[�^���z�u�f�[�^�ǂ���ɂȂ��Ă��܂��B
****************************************************************/
int Haichi::GetData(int rX, int rY)
{
	return (*(mData[rY]))[rX];
}

/************************************************************//**
* @param data �z�u�ԍ�
* @ return ���ꂾ���ǂ�����
****************************************************************/
bool Haichi::IsAshiba(int data)
{
	return (data==ASHIBA_NO || data==ASHIBA2_NO || data == ASHIBA3_NO ||
		data==MOVASHIBA_NO || data==MOVASHIBA2_NO || data == MOVASHIBA3_NO ||
		data==INVASHIBA3_NO );
}

/************************************************************//**
* ����̔z�u����������
****************************************************************/
void Haichi::ProcessAshiba(int data, int x, int y){

	string graphic;
	int sizex, sizey;
	if(data==ASHIBA_NO||data==MOVASHIBA_NO||data==INVASHIBA3_NO){
		graphic = "graphics\\object\\stage_1_asiba.png"; 
		sizex = GI("ASHIBASX");
		sizey = GI("ASHIBASY");
	}
	if(data==ASHIBA2_NO||data==MOVASHIBA2_NO){
		graphic = "graphics\\object\\stage_2_asiba.png"; 
		sizex = GI("ASHIBA2SX");
		sizey = GI("ASHIBA2SY");
	}
	if(data==ASHIBA3_NO||data==MOVASHIBA3_NO){
		graphic = "graphics\\object\\stage_4_asiba.png"; 
		sizex = GI("ASHIBA3SX");
		sizey = GI("ASHIBA3SY");
	}

	// ��������
	if( data == MOVASHIBA_NO || data == MOVASHIBA2_NO || data == MOVASHIBA3_NO ){
		AshibaMovable* newAshiba = 
			new AshibaMovable(x*SP->CHSZX, y*SP->CHSZY, 1.0f, graphic, sizex, sizey);
		
		HaichiObjStatic* newObj = new HaichiObjStatic(x*SP->CHSZX, y*SP->CHSZY);
		newObj->SetObject(newAshiba);
		mAshibaList.push_back( newAshiba );
		mAshibaMovList.push_back( newAshiba );
		
		mHaichiListOrig.push_back( newObj );
		mHaichiListTemp.push_back( newObj );
	}

	// ����
	else if( data == ASHIBA_NO || data == ASHIBA2_NO || data == ASHIBA3_NO ){
	
		Ashiba* newAshiba = 
			new Ashiba(x*SP->CHSZX, y*SP->CHSZY, 1.0f, graphic, sizex, sizey);

		HaichiObjStatic* newObj = new HaichiObjStatic(x*SP->CHSZX, y*SP->CHSZY);
		newObj->SetObject(newAshiba);
		mAshibaList.push_back( newAshiba );

		mHaichiListOrig.push_back( newObj );
		mHaichiListTemp.push_back( newObj );
	}

	// �����Ȃ�����
	else if( data == INVASHIBA3_NO ){
		AshibaInvisible* newAshiba = 
			new AshibaInvisible(x*SP->CHSZX, y*SP->CHSZY, 1.0f, sizex, sizey);
		
		HaichiObjStatic* newObj = new HaichiObjStatic(x*SP->CHSZX, y*SP->CHSZY);
		newObj->SetObject(newAshiba);
		mAshibaList.push_back( newAshiba );

		mHaichiListOrig.push_back( newObj );
		mHaichiListTemp.push_back( newObj );
	}
}