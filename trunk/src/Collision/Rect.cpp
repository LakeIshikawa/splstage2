#include ".\Rect.h"
#include "Collision.h"
#include "..\\Mob\\IPositionable.h"

#include <typeinfo>
#include <math.h>

Rect::Rect(Collision* rParent, int rGroupId, int rLeft, int rTop, int rRight, int rBottom) : 
	CollShape(rParent, rGroupId)
{
	mTop = rTop;
	mBottom = rBottom;
	mRight = rRight;
	mLeft = rLeft;
}

Rect::~Rect(void)
{
}

/*
	判定
*/
bool Rect::Collides(CollShape* rOperand)
{
	Circle* circle = NULL;
	Rect* rect = NULL;
	circle = dynamic_cast<Circle*>(rOperand);
	rect = dynamic_cast<Rect*>(rOperand);

	if(circle){
		return RectCircle(this, circle, 
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
		return RectRect(this, rect, 
			this->GetCollision()->GetParent()->GetX(),
			this->GetCollision()->GetParent()->GetY(),
			this->GetCollision()->GetParent()->GetMuki(),
			this->GetCollision()->GetParent()->GetFrameSizeX(),
			rect->GetCollision()->GetParent()->GetX(),
			rect->GetCollision()->GetParent()->GetY(),
			rect->GetCollision()->GetParent()->GetMuki(),
			rect->GetCollision()->GetParent()->GetFrameSizeX()
			);
	}

	return false;
}

/*
	指定された点が指定されたずれの長方形の中にいるか
*/
bool Rect::Contains(int rX, int rY, int rSlX, int rSlY)
{
	return 
		(rX > rSlX + mLeft &&
		rX < rSlX + mRight &&
		rY > rSlY + mTop &&
		rY < rSlY + mBottom);
}

/*
	長方形と長方形の当たり判定
*/
bool Rect::RectRect(Rect* rRect1, Rect* rRect2,
		int rC1PosX, int rC1PosY, bool rC1Muki, int rC1SizeX,
		int rC2PosX, int rC2PosY, bool rC2Muki, int rC2SizeX)
{
	//第一の長方形
	int r1top = rC1PosY + rRect1->Top();
	int r1bottom = rC1PosY + rRect1->Bottom();
	int r1right;
	int r1left;
	if(rC1Muki) {
		r1right = rC1PosX + (rC1SizeX - rRect1->Right());
		r1left = rC1PosX + (rC1SizeX - rRect1->Left());
	}
	else {
		r1right = rC1PosX + rRect1->Right();
		r1left = rC1PosX + rRect1->Left();
	}

	//第二の長方形
	int r2top = rC2PosY + rRect2->Top();
	int r2bottom = rC2PosY + rRect2->Bottom();
	int r2right;
	int r2left;
	if(rC2Muki) {
		r2right = rC2PosX + (rC2SizeX - rRect2->Right());
		r2left = rC2PosX + (rC2SizeX - rRect2->Left());
	}
	else {
		r2right = rC2PosX + rRect2->Right();
		r2left = rC2PosX + rRect2->Left();
	}

	//判定
	float sax = abs((r1left + r1right)/2.0 - (r2left + r2right)/2.0);
	float say = abs((r1top + r1bottom)/2.0 - (r2top + r2bottom)/2.0);
	
	bool retval = false;

	if(((sax < abs(r1right - r1left)/2.0 + abs(r2right - r2left)/2.0)) &&
		(say < abs(r1top - r1bottom)/2.0 + abs(r2top - r2bottom)/2.0)) retval = true;

	return retval;
}

/*
	円と長方形の当たり判定を行います

	その理論：
	- 円の中心が長方形の中にあった場合、衝突
	- 円が長方形に対して上下にあった場合、Y+-半径を見る
	- 円が長方形に対して左右にあった場合、X+-半径を見る
	- それ以外の場合、円と頂点の距離が（円の）半径+（長方形の）斜めより小さかったら、衝突
*/
bool Rect::RectCircle(Rect* rRect, Circle* rCircle,
		int rC1PosX, int rC1PosY, bool rC1Muki, int rC1SizeX,
		int rC2PosX, int rC2PosY, bool rC2Muki, int rC2SizeX)
{

	//長方形
	int top = rC1PosY + rRect->Top();
	int bottom = rC1PosY + rRect->Bottom();
	int right;
	int left;
	if(rC1Muki) {
		right = rC1PosX + (rC1SizeX - rRect->Left());
		left = rC1PosX + (rC1SizeX - rRect->Right());
	}
	else {
		right = rC1PosX + rRect->Right();
		left = rC1PosX + rRect->Left();
	}

	// 円
	int cx, cy, chankei;
	if(!rC2Muki) cx = rC2PosX + rCircle->X();
	else cx = rC2PosX + (rC2SizeX - rCircle->X());
	cy = rC2PosY + rCircle->Y();
	chankei = rCircle->Hankei();

	////////////
	//--判定--//
	////////////

	// 1-中心
	if(cx < right && cx > left && cy < bottom && cy > top)
		return true;

	// 2-上下にある
	if(cx < right && cx > left){
		if(cy < bottom + chankei && cy > -chankei + top)
			return true;
	}

	// 3-左右にある
	if(cy > top && cy < bottom){
		if(cx < right + chankei && cx > -chankei + left)
			return true;
	}

	// 4-隅のとこ
	int x[] = { left, left, right, right };
	int y[] = { top, bottom, top, bottom };

	for(int i=0; i<4; i++){
		if(PointDistance(x[i], y[i], cx, cy) < chankei)
			return true;
	}

	return false;

}

// 点と点の距離
float Rect::PointDistance(int x1, int y1, int x2, int y2)
{
	int sax = x1 - x2;
	int say = y1 - y2;

	float sa = sqrt((float)(sax*sax + say*say));

	return sa;
}