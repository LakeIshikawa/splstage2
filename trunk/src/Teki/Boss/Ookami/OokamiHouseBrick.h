#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "OokamiHouse.h"

//! ‰Æ‚ÌŠî–{¸×½
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class OokamiHouseBrick: public OokamiHouse
{

public:

	//! •W€ºİ½Ä×¸À
	OokamiHouseBrick();

	//! ¸Ş×Ì¨¯¸‚Ìæ“¾•û–@
	string GetGraphicSrc() 
	{ 
		return "graphics\\teki\\ookami\\brickhouse.png"; 
	}

	//! ‰ó‚ê•û
	void Disappear();


	//! ”j•Ğ¼ŞªÈÚ°À‚Ìì¬(‚È‚µ)
	void BuildParticleGenerator() {}

	//! “–‚½‚è”»’è‰“š‚È‚µ
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);

};

