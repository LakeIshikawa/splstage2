#include "CheatsController.h"
#include "..\\GameControl.h"
#include "Cheat.h"
#include "..\\..\\Options.h"

/**
	標準コンストラクタ
	自動的に呼ばれます
*/
CheatsController::CheatsController()
{
	mActive = Options::GetOptions()->IsOptionSet("cheats");
}

/**
	標準デストラクタ
*/
CheatsController::~CheatsController()
{}

/************************************************************//**
*	チートを追加します。\n
*	このチートがアクティブになり、トリッガーされるようになります。
*	\param rAddMe 追加するチート
****************************************************************/
void CheatsController::Add(Cheat *rAddMe)
{
	lstCheats.push_back( rAddMe );
}

/************************************************************//**
*	\param rOnOff true->チート有効 false->チート無効
****************************************************************/
void CheatsController::SetActive(bool rOnOff)
{
	mActive = rOnOff;
}

/************************************************************//**
*	チートがトリッガーされているかをチェックし、必要に応じて
*	実行します。
****************************************************************/
void CheatsController::CheckAndTrigger()
{
	if( mActive ){
		for each (Cheat* cheat in lstCheats ){
			if( GAMECONTROL->GetDXController()->KeyPush(cheat->GetKey())){
				cheat->DoCheat();
			}
		}
	}
}