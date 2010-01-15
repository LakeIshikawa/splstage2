#include "LightManager.h"
#include "Light.h"
#include "..\\Management\\GameControl.h"

// コンストラクタ
LightManager::LightManager()
{
	KURAYAMI = GI("KURAYAMI");
	ZeroMemory(mLights, sizeof(mLights));
	LoadResources();

}

// デストラクタ
LightManager::~LightManager()
{
}

/*
	ライトを追加する。

	注意その①：
	指定された場所に既にライトが入っている場合は
	上書きしてしまいますので、番号の管理を外でやってください。

	注意その②：
	番号がMAX_LIGHTS-1より大きい場合は何もしない
*/
void LightManager::AddLight(Light* rLight, int rBango)
{
	if( rBango<= MAX_LIGHTS-1 )
		mLights[rBango] = rLight;
}

/*
	指定されたライトを削除する。

	注意:
	オブジェクトが消去されません。　
	メモリの管理は外でやってください。
*/
void LightManager::RemoveLight(int rBango)
{
		mLights[rBango] = NULL;
}

/*
	ライトを取得します
*/
Light* LightManager::GetLight(int rBango)
{
	return mLights[rBango];
}

/*
	まず半透明の黒な枠を準備してある前提で、
	ライトがあるとこをを透明にする。
*/
void LightManager::Move()
{
	// ライトたちを動かす
	for(int cnt=0; cnt<MAX_LIGHTS; cnt++){
		if( mLights[cnt] && mLights[cnt]->IsOn() )
		{
			mLights[cnt]->Move();
		}
	}
}

/*
	描画
	ｱﾙﾌｧﾏｽｸをしようし、黒い幕を描画する
*/
void LightManager::Draw()
{	
	// ﾃﾞﾊﾞｲｽとｽﾌﾟﾗｲﾄを宅に使えるために取得する
	LPDIRECT3DDEVICE9 dev = GAMECONTROL->GetDXController()->GetDevice();
	LPD3DXSPRITE spr = GAMECONTROL->GetDXController()->GetMainSprite();
	LPDIRECT3DTEXTURE9 alphamask = GAMECONTROL->GetDXController()->GetTextureOf("_LightMap");

	spr->Begin(D3DXSPRITE_ALPHABLEND);
	dev->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	dev->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_INVSRCALPHA );
	dev->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_SRCALPHA );
	spr->Draw(alphamask, NULL, NULL, &D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1,1,1,1));
	spr->End();

	dev->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	dev->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// ﾗｲﾄを描画する
	for( int i=0; mLights[i]!=NULL && i<MAX_LIGHTS; i++){
		mLights[i]->Draw();
	}


}

/**
	アルファマスクのテクスチャの作成
*/
void LightManager::BuildAlphaMask()
{
	// ﾃﾞﾊﾞｲｽとｽﾌﾟﾗｲﾄを宅に使えるために取得する
	LPDIRECT3DDEVICE9 dev = GAMECONTROL->GetDXController()->GetDevice();
	LPD3DXSPRITE spr = GAMECONTROL->GetDXController()->GetMainSprite();

	// ｱﾙﾌｧﾏｽｸをﾚﾝﾀﾞﾘﾝｸﾞﾀｰｹﾞｯﾄとして指定する
	IDirect3DSurface9* oldsurf, *newsurf;
	LPDIRECT3DTEXTURE9 alphamask = GAMECONTROL->GetDXController()->GetTextureOf("_LightMap");
	alphamask->GetSurfaceLevel(0, &newsurf);

	dev->GetRenderTarget(0, &oldsurf);
	dev->SetRenderTarget(0, newsurf);

	// ﾃｸｽﾁｬをｱﾙﾌｧ0で埋める
	dev->Clear(0,
               NULL,
               D3DCLEAR_TARGET,
			   D3DCOLOR_ARGB(KURAYAMI, 0,0,0),
               1.0f,
               0);

	// ｼｰﾝ開始
	dev->BeginScene();
	spr->Begin(D3DXSPRITE_ALPHABLEND);

	// 格ﾗｲﾄに対して
	for( int i=0; mLights[i]!=NULL && i<MAX_LIGHTS; i++ ){
		Light* curLt = mLights[i];

		// ﾗｲﾄの位置を取得し
		RECT border;
		SetRect(&border, 0, 0, curLt->GetHankei()*2, curLt->GetHankei()*2);
		D3DXVECTOR3 trans(curLt->GetX() - curLt->GetHankei(), 
			curLt->GetY() - curLt->GetHankei(), 0.0f);

		// ﾗｲﾄがいる場所にﾗｲﾄのﾃｸｽﾁｬを描画する
		spr->Draw(GAMECONTROL->GetDXController()->GetTextureOf("graphics\\Light.png"), 
			&border, NULL, &trans,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// ｼｰﾝ終了
	spr->End();
	dev->EndScene();

	// ﾚﾝﾀﾞﾘﾝｸﾞﾀｰｹﾞｯﾄを戻す
	dev->SetRenderTarget(0, oldsurf);

	// 取得されたﾃｸｽﾁｬを開放する
	oldsurf->Release();
	newsurf->Release();
}

/**
 *	リソースをロードします
 */
void LightManager::LoadResources()
{
	// アルファマスク
	GAMECONTROL->GetDXController()->CreateNewTexture( "_LightMap", 1024, 1024, 
		1, D3DUSAGE_RENDERTARGET, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT );
}