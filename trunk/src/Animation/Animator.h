#pragma once

/*
	2D±ÆÒ°¼®İ—pµÌŞ¼Şª¸Ä¸×½
*/
class Animator
{
public:
	Animator(void);
	~Animator(void);

	// o—Í
	int GetFrame();
	bool IsFinished();

	// ¾¯À°
	void SetAnim(int rBango);
	int GetCurAnim();

	// ‘€ì
	void Start();
	void Stop();
	void Rewind();

};
