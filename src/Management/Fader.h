#pragma once

/*
	�G
*/
class Fader
{
public:

	Fader();
	~Fader(void);

	int FadeOut();
	int FadeIn();

	void SetSpeed(float mSp);

	void Draw();

protected:
	float fadeFactor; // 0�`1

	// �ݒ�萔
	float FADE_INCR;
	
};
