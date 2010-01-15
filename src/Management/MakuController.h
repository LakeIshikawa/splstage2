#pragma once

/*
	幕
*/
class MakuController
{
public:
	MakuController();
	~MakuController();

	void Process();
	void Draw();

	// インターフェース
	void Open();
	void Close();

	bool IsOpen();
	bool IsClosed();

	void SetOpened();
	void SetClosed();

private:
	enum STATUS{
		OPEN,
		CLOSE,
		OPENING,
		CLOSING
	};

	STATUS mStatus;

	int mPos;

	// 設定定数
	int MAKU_UP;
	int MAKU_DOWN;
	int MAKU_UD;

};