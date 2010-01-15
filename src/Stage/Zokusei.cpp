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
	指定されたﾌｧｲﾙから配置ﾃﾞｰﾀを読み込みます。
	この場で配置のﾃﾞｰﾀﾌｫｰﾏｯﾄを変換して、配置
	ｵﾌﾞｼﾞｪｸﾄを作ります。

	配置ﾘｽﾄの項目がXPxが低い順になるはず。

	ｴﾗｰの場合、1を返します。
*/
int Zokusei::Load(string rFname)
{
	// ﾃﾞｰﾀを読み込む
	if(Map::LoadFromFile(rFname)) return 1;

	// ﾘｽﾄを作成
	Haichi* ch = GAMECONTROL->GetStageManager()->GetCurrentStage()->GetHaichi();
	int MOVASHIBA_NO = GI("MOVASHIBA_NO");
	int TENBIN_NO = GI("TENBIN_NO");

	int tenbin_idx = 0;

	for(int x=0; x<SP->CHIPNX*mNGamen; x++)
		for(int y=0; y<SP->CHIPNY; y++)
		{
			int data = (*(mData[y]))[x];

			// 動く足場
			if( ISASHIBAMOV(data) && data && ch->GetData(x, y) == 0 ){
				AshibaMovable* ashiba = ch->GetAshibaMov(data/0x10);
				int card = ((data/0x10)==0) ? (data%0x10) : ((data%0x10)+1);
				ashiba->AddRoutePoint( card, x*SP->CHSZX, y*SP->CHSZY );
				if( data%0x10 == 0xF ) ashiba->SetLooping(true);
			}

			// 天秤
			else if( ch->GetData(x, y) == TENBIN_NO ){
				Tenbin* tenbin = ch->GetTenbin(tenbin_idx++);
				tenbin->SetVrSpace((data/0x10 - 7) * 32);
				tenbin->SetHrSpace((data%0x10) * 32);
			}
		}
	return 0; //OK
}

/*
	リソースを解放する
*/
void Zokusei::UnLoad()
{
	// データ解放
	mData.clear();

}
