#pragma once

/*
	2D��Ұ��ݗp��޼ު�ĸ׽
*/
class Animator
{
public:
	Animator(void);
	~Animator(void);

	// �o��
	int GetFrame();
	bool IsFinished();

	// ����
	void SetAnim(int rBango);
	int GetCurAnim();

	// ����
	void Start();
	void Stop();
	void Rewind();

};
