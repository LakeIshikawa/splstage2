#include ".\mobmanager.h"
#include "..\\Management\\GameControl.h"
#include "..\\Stage\\Haichi.h"

#include "..\\teki\\Kumo.h"
#include "..\\teki\\KumoPink.h"
#include "..\\teki\\Kaeru.h"
#include "..\\teki\\KaeruKing.h"
#include "..\\teki\\Usagi.h"
#include "..\\teki\\Koumori.h"
#include "..\\teki\\KariudoYumi.h"
#include "..\\teki\\KariudoYumi2.h"
#include "..\\teki\\KariudoYumi3.h"
#include "..\\teki\\KariudoKen.h"
#include "..\\teki\\KariudoKen2.h"
#include "..\\teki\\UgokuKi.h"
#include "..\\teki\\TrumpSoldier.h"
#include "..\\teki\\boss\\Majo\\Majo.h"
#include "..\\teki\\boss\\Ookami\\Ookami.h"
#include "..\\teki\\boss\\Queen\\Queen.h"

#include "..\\object\\MikataKobito.h"

#include "..\\mob\\ActionControllable\\ActionControllable.h"
#include "..\\mob\\ICollidable.h"

#include "..\\Object\\StgClrDoor.h"
#include "..\\Object\\Ashiba.h"
#include "..\\Object\\AshibaInvisible.h"
#include "..\\Object\\AshibaMovable.h"
#include "..\\Object\\TekkyuStand.h"
#include "..\\Object\\FireStand.h"

#include "..\\Item\\Item.h"


MobManager::MobManager(void)
{
}

MobManager::~MobManager(void)
{
}


/*
	ﾘｽﾄに入っているMOBを処理する
	ついでにヒロインの処理も行ってくれます
*/
void MobManager::Process()
{
	std::list<Movable*>::iterator mob;
	// 消し予定ﾘｽﾄのｵﾌﾞｼﾞｪｸﾄを消します
	mlRmvList.sort();
	mlRmvList.unique();
	for(mob = mlRmvList.begin(); mob != mlRmvList.end(); ++mob){
		mlMobList.remove(*mob);

		if( (*mob)->IsOwnershipTransfered() )
			delete (*mob);
	}

	mlRmvList.clear();


	// Zでソート
	mlMobList.sort(fukaiJun);

	// ﾒｲﾝ処理
	for(mob = mlMobList.begin(); mob != mlMobList.end(); ++mob){
		(*mob)->Process();
	}
}

/*
	ｵﾌﾞｼﾞｪｸﾄをﾘｸｴｽﾄ
*/
void MobManager::Request(int rNo, int rXPx, int rYPx, bool rTransferOwnership)
{
	Movable* newobj = NULL;

	//float zengo = (rNo%2)==1?1.0f:-1.0f; //奇数:前面  偶数:背面

	if( rNo == GI("HEROINE_NO"))	newobj = GAMECONTROL->GetJiki();
	if( rNo == GI("KUMO_NO"))		newobj = new Kumo( rXPx, rYPx );
	if( rNo == GI("KUMOPINK_NO"))	newobj = new KumoPink( rXPx, rYPx );
	if( rNo == GI("KAERU_NO"))		newobj = new Kaeru( rXPx, rYPx );
	if( rNo == GI("KAERU_KING_NO"))	newobj = new KaeruKing( rXPx, rYPx );
	if( rNo == GI("USAGI_NO"))		newobj = new Usagi( rXPx, rYPx );
	if( rNo == GI("KOMORI_NO"))		newobj = new Koumori( rXPx, rYPx );
	if( rNo == GI("KARIYUMI_NO"))	newobj = new KariudoYumi( rXPx, rYPx );
	if( rNo == GI("KARIYUMI2_NO"))	newobj = new KariudoYumi2( rXPx, rYPx );
	if( rNo == GI("KARIYUMI3_NO"))	newobj = new KariudoYumi3( rXPx, rYPx );
	if( rNo == GI("KARIKEN_NO")) 	newobj = new KariudoKen( rXPx, rYPx );
	if( rNo == GI("KARIKEN2_NO")) 	newobj = new KariudoKen2( rXPx, rYPx );
	if( rNo == GI("UGOKUKI_NO")) 	newobj = new UgokuKi( rXPx, rYPx );
	if( rNo == GI("BOSS_MAJO_NO") )	newobj = new Majo();
	if( rNo == GI("STGCLRDOOR_NO") )newobj = new StgClrDoor( rXPx, rYPx, 101.0f );
	if( rNo == GI("ASHIBA_NO") )	newobj = new Ashiba( rXPx, rYPx, 1.0f, "graphics\\object\\stage_1_asiba.png", GI("ASHIBASX"), GI("ASHIBASY") );
	//if( rNo == GI("INVASHIBA_NO") )	newobj = new AshibaInvisible( rXPx, rYPx, 1.0f );
	if( rNo == GI("TEKKYU_NO") )	newobj = new TekkyuStand( rXPx, rYPx, -10.0f );
	if( rNo == GI("FIREUP_NO") )	newobj = new FireStand( rXPx, rYPx, -10.0f, false );
	if( rNo == GI("FIREDN_NO") )	newobj = new FireStand( rXPx, rYPx, -10.0f, true );
	if( rNo == GI("BOSS_OOKAMI_NO")) newobj = new Ookami();
	if( rNo == GI("TRUMPHEIHEARTNO")) newobj = new TrumpSoldierHearts(rXPx, rYPx);
	if( rNo == GI("TRUMPHEIDIAMONDNO")) newobj = new TrumpSoldierDiamonds(rXPx, rYPx);
	if( rNo == GI("TRUMPHEICLOVERNO")) newobj = new TrumpSoldierClovers(rXPx, rYPx);
	if( rNo == GI("TRUMPHEISPADENO")) newobj = new TrumpSoldierSpades(rXPx, rYPx);
	if( rNo == GI("BOSS_QUEEN_NO")) newobj = new Queen();
	if( rNo == GI("ITRINGO")) newobj = new ItRingo(rXPx, rYPx);
	if( rNo == GI("ITAORINGO")) newobj = new ItAoRingo(rXPx, rYPx);
	if( rNo == GI("ITKINRINGO")) newobj = new ItKinRingo(rXPx, rYPx);
	if( rNo == GI("KOBITOA_NO") )	{
		int pick = rand()%3;

		switch( pick ){
			case 0: newobj = new MikataKobitoBlue( rXPx, rYPx ); break;
			case 1: newobj = new MikataKobitoRed( rXPx, rYPx ); break;
			case 2: newobj = new MikataKobitoGreen( rXPx, rYPx ); break;
		}
	}

	// エラー対応
	if( newobj == NULL ){
		GAMECONTROL->ThrowError("未対応の配置番号が使われた：%d", rNo );
	}

	newobj->Build();
	
	// 所属
	newobj->SetOwnershipTransfered(rTransferOwnership);

	// 敵
	Teki* newteki = dynamic_cast<Teki*>(newobj);

	if( newteki ){

		//ヒロインを追加
		newteki->AddTarget( GAMECONTROL->GetJiki() );

		Haichi* curHaichi = GAMECONTROL->GetStageManager()->GetCurrentStage()->GetHaichi();

		// 足場に敵を追加
		curHaichi->SetAshibaTargets( newteki );
	}

	// 新敵
	ActionControllable* newacteki = dynamic_cast<ActionControllable*>(newobj);
	if( newacteki ){
		newacteki->AddInitStates( rXPx, rYPx );
		newacteki->AddTarget( GAMECONTROL->GetJiki() );
	}

	mlMobList.push_back( newobj );

	// ソートをかける
	mlMobList.sort(fukaiJun);
}

/*
	ｵﾌﾞｼﾞｪｸﾄを直接にﾘｸｴｽﾄします
	前提：ｵﾌﾞｼﾞｪｸﾄのﾀｰｹﾞｯﾄ、位置などが既に設定されてあること
*/
void MobManager::Request(Movable *rObj, bool rTransferOwnership)
{
	rObj->SetOwnershipTransfered(rTransferOwnership);
	mlMobList.push_back(rObj);

	// ソートをかける
	mlMobList.sort(fukaiJun);
}

/*
	ｵﾌﾞｼﾞｪｸﾄを消す\n
	消し予定ｵﾌﾞｼﾞｪｸﾄのﾘｽﾄに入れます
*/
void MobManager::Remove(Movable *rTarget)
{
	mlRmvList.push_back( rTarget );
}

/*
	すべてのMOBを消去。\n
	メモリーは所属者の指定により削除されます
	注意：絶対にMobの処理の中で使わないこと。(敵など)
*/
void MobManager::Reset()
{
	std::list<Movable*>::iterator mob;
	
	// 一時リストにコピーしてから(所属がマネージャのmobだけ
	list<Movable*> temp;
	for each( Movable* m in mlMobList )
		if( m->IsOwnershipTransfered() ) temp.push_back(m);

	for(mob = temp.begin(); mob != temp.end(); ++mob){
		mlMobList.remove(*mob);
		delete(*mob);
	}

	InstantReset();
	
}

/**
	瞬時的にすべてのリストをリセットします。\n
	メモリは消去されません。
	注意：イベント専用。
*/
void MobManager::InstantReset()
{
	mlMobList.clear();
	mlRmvList.clear();

	// 自機を入れなおす
	mlMobList.push_back(GAMECONTROL->GetJiki());
}

bool fukaiJun(Movable *a, Movable *b)
{
	return a->Z() < b->Z();
}
