#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class Light;

/*
	ライトを管理するレイヤーです。

	複数のライトを描画するのに一気に全部を描く必要があります。
	ライトマネージャーはその面倒を見てくれます。

	厳密に次の機能へインターフェースを提供します。
	- ライトを追加
	- ライトを削除
	- ライトを検出
	- すべての追加済みのライトを描画
*/
class LightManager
{
public:
	LightManager();
	~LightManager();

	void AddLight(Light* rLight, int rBango);
	void RemoveLight(int rBango);
	Light* GetLight(int rBango);

	void Draw();
	void Move();
	void BuildAlphaMask();

	void LoadResources();

private:

	bool	PointToBeDraw(int rY, int rX);
	DWORD	DetermineColor(int rY, int rX);

	static const int MAX_LIGHTS = 5;

	Light*				mLights[MAX_LIGHTS];

	// 設定定数
	int KURAYAMI;

};