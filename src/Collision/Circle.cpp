#include ".\circle.h"
#include "Collision.h"
#include "Rect.h"

#include <typeinfo>
#include <math.h>

#include "..\\Mob\\IPositionable.h"

Circle::Circle(Collision* rParent, int rGroupId, int rX, int rY, int rHankei) :
	CollShape(rParent, rGroupId)
{
	mX = rX;
	mY = rY;
	mHankei = rHankei;
}

Circle::~Circle(void)
{
}

/*
	当たり判定
*/
bool Circle::Collides(CollShape* rOperand)
{
	Circle* circle = NULL;
	Rect* rect = NULL;
	circle = dynamic_cast<Circle*>(rOperand);
	rect = dynamic_cast<Rect*>(rOperand);

	if(circle){
		return CircleCircle(this, circle, 
			this->GetCollision()->GetParent()->GetX(),
			this->GetCollision()->GetParent()->GetY(),
			this->GetCollision()->GetParent()->GetMuki(),
			this->GetCollision()->GetParent()->GetFrameSizeX(),
			circle->GetCollision()->GetParent()->GetX(),
			circle->GetCollision()->GetParent()->GetY(),
			circle->GetCollision()->GetParent()->GetMuki(),
			circle->GetCollision()->GetParent()->GetFrameSizeX()
			);
	}
	else if(rect){
		return Rect::RectCircle(rect, this,
			rect->GetCollision()->GetParent()->GetX(),
			rect->GetCollision()->GetParent()->GetY(),
			rect->GetCollision()->GetParent()->GetMuki(),
			rect->GetCollision()->GetParent()->GetFrameSizeX(),
			this->GetCollision()->GetParent()->GetX(),
			this->GetCollision()->GetParent()->GetY(),
			this->GetCollision()->GetParent()->GetMuki(),
			this->GetCollision()->GetParent()->GetFrameSizeX()
			);
	}

	return false;
}

// ｹﾞｯﾀｰ
int Circle::X(){
	return mX;
}

int Circle::Y(){
	return mY;
}

int Circle::Hankei(){
	return mHankei;
}

/*
	円と円の接触判定

	引数：
	- rCicleN			円のｵﾌﾞｼﾞｪｸﾄ
	- rCNPosX rCNPosY	ｺﾘｼﾞｮﾝの位置（絶対座標）　つまり：この敵・自機・ｱｲﾃﾑどこにいるか
	- rCNMuki			0-左向き 1-右向き(位置調整必要)
	- rCNSizeX			ｺﾘｼﾞｮﾝの幅（向きが右の時に座標がこの値に沿って変換されます
*/
bool Circle::CircleCircle(Circle* rCircle1, Circle* rCircle2, 
						  int rC1PosX, int rC1PosY, bool rC1Muki, int rC1SizeX,
						  int rC2PosX, int rC2PosY, bool rC2Muki, int rC2SizeX)
{
	// 向きにしたがって円の中心のX座標を求める
	int c1x, c2x;
	if(!rC1Muki) c1x = rC1PosX + rCircle1->mX;
	else c1x = rC1PosX + (rC1SizeX - rCircle1->mX);

	if(!rC2Muki) c2x = rC2PosX + rCircle2->mX;
	else c2x = rC2PosX + (rC2SizeX - rCircle2->mX);

	int sa_x = c1x - c2x;
	int sa_y = rCircle1->mY + rC1PosY - (rCircle2->mY + rC2PosY);

	float sa = sqrt((float)(sa_x*sa_x + sa_y*sa_y));

	bool retval = sa<(rCircle1->mHankei + rCircle2->mHankei);

	return retval;
}