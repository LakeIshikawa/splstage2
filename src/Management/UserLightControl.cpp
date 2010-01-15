#include ".\UserLightControl.h"
#include "..\\Light\\Light.h"
#include "GameControl.h"

UserLightControl::UserLightControl(void)
{
	mpControlLight = new Light(GF("USER_LIGHT_HANKEI"));

	ZeroMemory( &mZXC, sizeof(int)*3 );
}

UserLightControl::~UserLightControl(void)
{
}

Light* UserLightControl::GetControlLight()
{
	return mpControlLight;
}

// マウスの動きに従ってユーザー操作ライトを動かします
void UserLightControl::Move()
{
	DXController* controller = GAMECONTROL->GetDXController();
	// マウスを更新
	controller->UpdateMouseState();

	// ライトを動かす
	mpControlLight->SetSpX( controller->GetMouseState().lX );
	mpControlLight->SetSpY( controller->GetMouseState().lY );

	// キーボード更新
	controller->UpdateKeyboardState();

	// 色の操作を取得
	for(int i=0; i<3; i++){
		if(controller->KeyPush( DIK_Z+i ))
		{
			int max = mZXC[0];
			if(mZXC[1]>mZXC[0]) max = mZXC[1];
			if(mZXC[2]>mZXC[1]) max = mZXC[2];

			mZXC[i] = max+1;
			// SE
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_raitokirikae.wav");
		}
		else if( controller->KeyPull( DIK_Z+i ) )
			mZXC[i] = 0;
	}
	
	// ZXCの最大値の位置を検出
	int maxidx = 0;
	for(int i=0; i<3; i++)
	{
		if( mZXC[i] > mZXC[maxidx] ) maxidx = i;
	}

	// ZXCが全部0の場合は無色
	if( mZXC[maxidx] == 0 )
		mpControlLight->SetColor( COLOR::MUSHOKU );

	// ZXCの一番値が大きいキーの色に設定
	else {
		mpControlLight->SetColor( (COLOR)maxidx );
	}

}

/* 
	ライトを強制的に無色に戻し、もう一回キーを押さないと
	色が変わらない状態にします
*/
void UserLightControl::EndEffect(){
	ZeroMemory(&mZXC, sizeof(int)*3);
}
