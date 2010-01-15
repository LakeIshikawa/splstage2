#pragma once

#include "dsutil.h"

/*
	BGM‹È
*/
class Bgm
{
public:
	Bgm(CSound* rIntro, CSound* rLoop);
	~Bgm();

	void KeepPlaying();
	void Play();
	void Stop();
	void Reset();
	bool IsPlaying();

private:
	CSound* mIntro;
	CSound* mLoop;

	bool isLoopPassed;
	bool isPlaying;
};