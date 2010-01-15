#include ".\Collision.h"
#include "..\\Mob\\ICollidable.h"

#include "Circle.h"
#include "Rect.h"

using namespace std;

/************************************************************//**
*	\param parent 移動・向きが可能な親
*	おやの位置や向きによって判定が異なりますので、
*	Collisionオブジェクトをお持ちのクラスはIPositionable
*	インターフェースを実装しなければなりません。
****************************************************************/
Collision::Collision(IPositionable* rParent)
{
	mParent = rParent;
}

Collision::~Collision(void)
{
	for each( CollShape* shape in mlShapeLst ){
		delete shape;
	}
}

/*
	ｼｪｰﾌﾟを追加する
*/
void Collision::AddShape(CollShape* rNewShape)
{
	mlShapeLst.push_back( rNewShape );
}

/*
	番号付きｼｪｰﾌﾟを追加する
*/
void Collision::AddIndexedShape(CollShape* rNewShape, int rIdx)
{
	// 既に存在していたら上書き
	if( mmIdxToShape[rIdx] != NULL ) 
		mmIdxToShape[rIdx] = NULL;

	mlShapeLst.push_back( rNewShape );
	mmIdxToShape[rIdx] = rNewShape;
}

/*
	当たり判定用の円を追加する
*/
void Collision::AddCircle(int rGroupId, int rX, int rY, int rHankei)
{
	AddShape(new Circle(this, rGroupId, rX, rY, rHankei));
}

/*
	番号つきの長方形の追加
*/
void Collision::AddIndexedRect(int rGroupId, int rShapeIdx, int rLeft, int rTop, int rRight, int rBottom)
{
	AddIndexedShape(new Rect(this, rGroupId, rLeft, rTop, rRight, rBottom),rShapeIdx);
}

/*
	当たり判定用の円を追加する
	位置を後で変えられるように、この図形の番号を指定する
*/
void Collision::AddMovableCircle(int rGroupId, int rShapeIdx, int rX, int rY, int rHankei)
{
	AddIndexedShape(new Circle(this, rGroupId, rX, rY, rHankei),rShapeIdx);
}

/*
	番号付きの円を再設定する
*/
void Collision::SetCircle(int rShapeIdx, int rX, int rY, int rHankei)
{
	CollShape* collshape = GetIndexedShape(rShapeIdx);

	Circle* circle = dynamic_cast<Circle*>(collshape);

	if(circle){
		circle->Set(rX, rY, rHankei);
	}
}


/*
	当たり判定用の長方形を追加する
*/
void Collision::AddRect(int rGroupId, int rLeft, int rTop, int rRight, int rBottom)
{
	AddShape(new Rect(this, rGroupId, rLeft, rTop, rRight, rBottom));
}



/*
	番号つきの図形を取得する
*/
CollShape* Collision::GetIndexedShape(int rIdx)
{
	return mmIdxToShape[rIdx];
}

/*
	他のCollisionとの当たり判定を行う
*/
bool Collision::Hantei(Collision* rOperand, ICollidable* rCallback, ICollidable* rCallbackOp)
{
	// 自分の図形と他方
	bool res = false;
	list<CollShape*>::iterator th_it = mlShapeLst.begin(), th_en = mlShapeLst.end();
	for( ; th_it!=th_en; th_it++ ){
		if(rOperand->Collides(*th_it, rCallback, rCallbackOp)) 
			res = true;
	}

	return res;
}

/*
	Collisionと図形との当たり判定
*/
bool Collision::Collides(CollShape* rShape, ICollidable* rCallback, ICollidable* rCallbackOp)
{
	bool retval = false;
	list<CollShape*>::iterator th_it = mlShapeLst.begin(), th_en = mlShapeLst.end();
	for( ; th_it!=th_en; th_it++ ){
		if((*th_it)->Collides(rShape)) 
		{	
			//ｸﾞﾙｰﾌﾟIDを設定
			mThisGroupId = (*th_it)->GetGroupId();
			mOperandGroupId = rShape->GetGroupId();

			rCallback->CollisionResponse(rCallbackOp, mOperandGroupId, mThisGroupId); //ｺｰﾙﾊﾞｯｸ
			retval = true;
		}
	}
	return retval;
}

/**
	\return IPositionable親
*/
IPositionable* Collision::GetParent()
{
	return mParent;
}