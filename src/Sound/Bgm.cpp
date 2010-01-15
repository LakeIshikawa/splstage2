#include "Bgm.h"
#include "..\\Management\\GameControl.h"

Bgm::Bgm(CSound* rIntro, CSound* rLoop)
{
	mIntro = rIntro;
	mLoop = rLoop;

	isLoopPassed = mIntro==NULL?true:false;
	isPlaying = false;
}

Bgm::~Bgm()
{}

/*
	再生
*/
void Bgm::KeepPlaying()
{
	if( isPlaying && mIntro && !mIntro->IsSoundPlaying() && mLoop && !isLoopPassed)
	{
		isLoopPassed = true;
		mLoop->Play(0, DSBPLAY_LOOPING ,0, -1, 0);
	}
}

/*
	停止
*/
void Bgm::Stop()
{
	isPlaying = false;
	if( isLoopPassed && mLoop ){
		mLoop->Stop();
	}
	else if( mIntro ){
		mIntro->Stop();
	}
}

/*
	再生開始
*/
void Bgm::Play()
{
	isPlaying = true;
	if( mIntro && !isLoopPassed ){
		mIntro->Play();
	}
	else if( mLoop ){
		mLoop->Play(0, DSBPLAY_LOOPING ,0, -1, 0);
	}
}

/*
	リセット
*/
void Bgm::Reset()
{
	isLoopPassed = mIntro==NULL?true:false;
	isPlaying = false;
	if( mIntro ) mIntro->Reset();
	if( mLoop ) mLoop->Reset();
}

/*
	再生中か
*/
bool Bgm::IsPlaying()
{
	return ( (mLoop && mLoop->IsSoundPlaying()) ||
		(!mLoop && mIntro && mIntro->IsSoundPlaying()) );
}