#pragma once

#include "..\\Stage.h"


/*
	スタッフロール
*/
class StaffRoll : public Stage
{
public:
	StaffRoll();
	~StaffRoll();

	void Load();
	void UnLoad();
	void Process();

	// デバイスローストのとき
	void OnLostDevice();
	void OnRestoredDevice();

private:

	//! 初期状態にする
	void Init();

	//! 描画
	void DrawStaffWithAlphaMask();

	//! テクスチャの動的作成
	void BuildStaffTexture();

	//! D3Dリソースのロード
	void LoadResources();
	//! D3Dリソースの開放
	void ReleaseResources();

	int stage;
	float scrp;

	LPDIRECT3DTEXTURE9 mEdStr;
	LPDIRECT3DTEXTURE9 mEdStr2;
	LPD3DXRENDERTOSURFACE mRenderer;
};