#pragma once

class Jiki;
class MakuController;

////���Ұ�
#define	INDMAX	100//�\����MAX(�ݼ��,���߼�)

/*
	�C���^�[�t�F�[�X
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

	// �\����
	bool mHidden;

	//�\�����W
	static	int	sIndData[][INDMAX];

	//��������
	float	mSeigenTime;
	float	mAniTimer;
	int		mAniNo;
	int		mPls;

	//�֐��Q
	void	Jikan();
	void	Enpashi();
	void	Tenshon();
	void	Zanki();

	// �ݒ�萔
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
