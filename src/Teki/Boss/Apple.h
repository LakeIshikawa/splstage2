#pragma once

#include "..\\..\\Mob\\Collidable.h"
#include "..\\..\\Stage\\Map.h"

/*
	りんご
*/
class Apple : public Collidable
{
public:
	Apple(int rXPx, int rYPx);
	~Apple();

	virtual void Move();

	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);
	int GetSizeX();

	void Fall();

	bool IsHittingGround();

	void DisableCollision();
	void EnableCollision();


protected:

	static Map::HITPOINT sMapPointX;
	static Map::HITPOINT sMapPointY;
	Map::D4AR mMapKabe;
	Map::D4AR mAtari;

	int mNo;
	float mTimer;

	enum STATUS{
		NORMAL,
		BROKE
	};
	STATUS mBaseStatus;

		
	enum FRAMES{
		FR_NORMAL,
		FR_DISABLE
	};


	// メソッド
	void MapAtHt();
	void DetSpAccPos();
	virtual void Draw();


	// 設定定数
	int APPLESZX;
	int APPLESZY;

	float APPLE_BRTM;

};