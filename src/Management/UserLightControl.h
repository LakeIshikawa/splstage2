#pragma once

class Light;

/*
	プレイヤーが操るライトの操作へのインターフェースを提供します。
*/
class UserLightControl
{
public:

	enum COLOR
	{
		AKA,
		MIDORI,
		AO,
		MUSHOKU
	};

	UserLightControl(void);
	~UserLightControl(void);

	Light*	GetControlLight();

	void	Move();

	void	EndEffect();

private:
	Light*	mpControlLight;

	// キーのz,x,cの押された順番(値が一番大きい方の優先)
	int		mZXC[3];	// 0:Z 1:X 2:C

};
