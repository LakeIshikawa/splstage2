#pragma once

/*
	“G
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
	float fadeFactor; // 0`1

	// İ’è’è”
	float FADE_INCR;
	
};
