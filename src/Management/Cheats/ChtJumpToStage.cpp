#include "ChtJumpToStage.h"
#include "..\\GameControl.h"

ChtJumpToStage::ChtJumpToStage(int rKey) : Cheat( rKey )
{}

ChtJumpToStage::~ChtJumpToStage()
{}

void ChtJumpToStage::DoCheat()
{
	// �͈̓`�F�b�N
	if( mKey >= DIK_1 && mKey <= DIK_0 ){
		int p10 = 0;
		if( GAMECONTROL->GetDXController()->KeyHold( DIK_LSHIFT ) ) p10 = 10;
		GAMECONTROL->GetStageManager()->GoToStage( mKey - DIK_1 + p10 );
	}
}