#pragma once

#include "..\\Stage.h"
#include "..\\..\\Mob\\MovieActor.h"

/*
	¶°ÃÝÛ°Ù‰æ–Ê
*/
class CurtainRollScr : public Stage
{
public:
	CurtainRollScr(string rDataFname, string rScrollBckgImg, 
		string rMapChipGr, SoundController::BGMS rBgm);
	~CurtainRollScr();

	void Process();
	void Load();
	void UnLoad();


private:
	void Init();
	void DisposeMovieActors();
	void UpdateStage();

	enum STAGE {
		FADING,
		OPENING,
		WAIT1SEC,
		THANKSPLAYING,
		WAIT1SECMORE,
		HEROINE_ENTERING,
		HEROINE_STOP1SEC,
		HEROINE_ATTACK,
		HEROINE_ATTACKEND,
		HEROINE_STOP1SECMORE,
		SEEYOUAGAIN,
		CLOSINGANDFADINGOUT
	} mStage;

	float mTimer;

	// –ðŽÒ
	MovieActor* actors[7];
	MovieActor* heroine;

	enum ANIMS {
		HERAN_WALK,
		HERAN_STOP,
		HERAN_ATT,
		HERAN_ATTEND,
		TEKI_STAND,
		TEKI_DIE
	};
};