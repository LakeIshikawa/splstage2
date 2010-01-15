#include ".\Zokusei.h"
#include "..\\Management\\GameControl.h"
#include "Checkpoint\\CheckpointController.h"
#include "Checkpoint\\Checkpoint.h"
#include "HaichiObjStatic.h"
#include "..\\Object\\AshibaMovable.h"

Zokusei::Zokusei(void)
{
}

Zokusei::~Zokusei(void)
{
}

/*
	�w�肳�ꂽ̧�ق���z�u�ް���ǂݍ��݂܂��B
	���̏�Ŕz�u���ް�̫�ϯĂ�ϊ����āA�z�u
	��޼ު�Ă����܂��B

	�z�uؽĂ̍��ڂ�XPx���Ⴂ���ɂȂ�͂��B

	�װ�̏ꍇ�A1��Ԃ��܂��B
*/
int Zokusei::Load(string rFname)
{
	// �ް���ǂݍ���
	if(Map::LoadFromFile(rFname)) return 1;

	// ؽĂ��쐬
	Haichi* ch = GAMECONTROL->GetStageManager()->GetCurrentStage()->GetHaichi();
	int MOVASHIBA_NO = GI("MOVASHIBA_NO");
	int TENBIN_NO = GI("TENBIN_NO");

	int tenbin_idx = 0;

	for(int x=0; x<SP->CHIPNX*mNGamen; x++)
		for(int y=0; y<SP->CHIPNY; y++)
		{
			int data = (*(mData[y]))[x];

			// ��������
			if( ISASHIBAMOV(data) && data && ch->GetData(x, y) == 0 ){
				AshibaMovable* ashiba = ch->GetAshibaMov(data/0x10);
				int card = ((data/0x10)==0) ? (data%0x10) : ((data%0x10)+1);
				ashiba->AddRoutePoint( card, x*SP->CHSZX, y*SP->CHSZY );
				if( data%0x10 == 0xF ) ashiba->SetLooping(true);
			}

			// �V��
			else if( ch->GetData(x, y) == TENBIN_NO ){
				Tenbin* tenbin = ch->GetTenbin(tenbin_idx++);
				tenbin->SetVrSpace((data/0x10 - 7) * 32);
				tenbin->SetHrSpace((data%0x10) * 32);
			}
		}
	return 0; //OK
}

/*
	���\�[�X���������
*/
void Zokusei::UnLoad()
{
	// �f�[�^���
	mData.clear();

}
