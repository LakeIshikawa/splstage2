#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\Collidable.h"

//! ”j•Ğ¼ŞªÈÚ°À
/****************************************************************//**
*	”j•Ğ‚ğ”ò‚ÑU‚ç‚©‚·
*	\nosubgrouping
********************************************************************/
class ParticleGenerator
{

	public: 
		//! •W€ºİ½Ä×¸À
		ParticleGenerator(int rX, int rY) :
		  mMode(PG_LINEAR), mTimer(0.0f), mCurPartIdx(0), mX(rX), mY(rY){}

		//! ”j•Ğ‚Ì”ò‚Î‚µ•û
		enum PG_MODE {
			PG_RANDOM,	//! ¸Ş×Ì¨¯¸Ø¿°½‚ğ×İÀŞÑ‚Ég—p
			PG_LINEAR	//! ¸Ş×Ì¨¯¸¿°½‚ğˆêŒÂ‚¸‚Â‡”Ô‚Ég—p
		};


		//! ”j•Ğ‚Ì”­Ë‚ğ—\–ñ
		void BookPartThrow(float rAngle, float rSpeed, 
			float rInterval, string rGraphicSrc);

		//! Ó°ÄŞ‚Ìw’è
		void SetMode(PG_MODE rMode);


		//! ”ò‚Î‚·
		void Generate();

protected:

	//! ÃŞ°À‚Æ‚µ‚Ä“o˜^‚³‚ê‚é”­Ë—\’è‚ÌµÌŞ¼Şª¸Ä
	class PartThrow{
	public:
		PartThrow(float rAngle, float rSpeed, float rInterval, string rGraphic):
		  angle(rAngle), speed(rSpeed), interval(rInterval), graphic(rGraphic), thrown(false){}

		float angle;
		float speed;
		float interval;
		string graphic;
		bool thrown;
	};

	PG_MODE mMode;
	vector<PartThrow> mData;
	float mTimer;
	int mCurPartIdx;
	int mX;
	int mY;
};

//! ”j•Ğ
/****************************************************************//**
*	”j•Ğ
*	\nosubgrouping
********************************************************************/
class Particle : public Collidable
{
public:
	
	//! •W€ºİ½Ä×¸À
	Particle(float rAngle, float rSpeed, string rGraphic, 
		int rStartX, int rStartY);

	//! 1ÌÚ°Ñˆ—
	void Move();

	//! “–‚½‚è”»’è‰“š
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);

private:
	//! Šp“x
	float mAngle;
	//! ‰ñ“]Šp“x
	float mRotAngle;
	//! ¸Ş×Ì¨¯¸
	string mGraphic;

	// İ’è’è”
	float OOKAMI_HSPTROTSP;

};
