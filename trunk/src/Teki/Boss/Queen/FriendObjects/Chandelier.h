#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Object\\Ashiba.h"

//! ¼¬İÃŞØ±
/****************************************************************//**
*	“ª‚É‹C‚ğ‚Â‚¯‚é‚×‚µ
*	\nosubgrouping
********************************************************************/
class Chandelier : public Ashiba
{

public:

	//! •W€ºİ½Ä×¸À
	Chandelier();

	//! @see Movable
	void Move();
	//! @see Ashiba
	void Draw();
	
	//! ¸Û°İ
	Chandelier* Clone();

	//! “®ì‚ªI‚í‚Á‚½‚©
	bool IsStopped();


	//! İ’è’è”‚ğİ’è‚·‚é
	void SetStage(bool rStrong);


	//! —‚Æ‚·
	void Drop();
	//! ˆø‚«–ß‚·
	void PickUp();

	//! “–‚½‚è‘Î‰
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);

	//! µ°ÊŞ°×²ÄŞ
	void RespDown(IRideCapable* rider, Rect* jbound){}
	void RespLeft(IRideCapable* rider, Rect* jbound){}
	void RespRight(IRideCapable* rider, Rect* jbound){}

private:

	// Ò¿¯ÄŞ
	void Fall();
	void Floor();
	void Raise();

	// ½Ã°À½
	enum {
		STOP,
		FALL,
		FLOOR,
		RAISE
	} mStatus;

	float mTimer;

	// İ’è’è”
	int CHANDCHAINDX;
	int CHANDCHAINDY;
	int CHANDCHAINSX;
	int CHANDCHAINSY;

	float CHANDRAISESP;
	float CHANDWTTIME;
	
	int FLOORY;
	float GRAVITY;
};
