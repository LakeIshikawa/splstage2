#pragma once

/*
	��
*/
class MakuController
{
public:
	MakuController();
	~MakuController();

	void Process();
	void Draw();

	// �C���^�[�t�F�[�X
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

	// �ݒ�萔
	int MAKU_UP;
	int MAKU_DOWN;
	int MAKU_UD;

};