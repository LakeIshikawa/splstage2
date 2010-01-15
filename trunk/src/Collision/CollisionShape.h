#pragma once

/*
	当たり判定のｴﾘｱ(図形)の基本ｸﾗｽ
*/
class CollisionShape
{
public:
	CollisionShape(void);
	virtual ~CollisionShape(void);

	virtual bool Collide(CollisionShape* rOperand) = 0;

	// 当たり判定の計算
	//static bool 
};
