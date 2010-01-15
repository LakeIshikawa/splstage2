#pragma once

class Jiki;
class MakuController;

////ﾊﾟﾗﾒｰﾀ
#define	INDMAX	100//表示数MAX(ﾃﾝｼｮﾝ,ｴﾝﾊﾟｼｰ)

/*
	インターフェース
*/
class InterfaceView
{
public:
	InterfaceView(Jiki* rJiki, MakuController* rMaku);
	~InterfaceView(void);
	void Draw();

	void Hide() { mHidden = true; }
	void Show() { mHidden = false; }

private:
	Jiki* mJiki;
	MakuController* mMaku;

	// 表示中
	bool mHidden;

	//表示座標
	static	int	sIndData[][INDMAX];

	//制限時間
	float	mSeigenTime;
	float	mAniTimer;
	int		mAniNo;
	int		mPls;

	//関数群
	void	Jikan();
	void	Enpashi();
	void	Tenshon();
	void	Zanki();

	// 設定定数
	float EMP_MAX;
	float TEN_MAX;
	int	  DODAI_X;
	int	  DODAI_Y;
	int	  CLOKESIZE;
	int	  PINSIZE;
	int	  LIFESIZE;
	int	  EMPSIZE;
	int	  TENSIZE;

	int CHAINX;
	int CHAINY;
	int CHAINSX;
	int CHAINSY;

};
