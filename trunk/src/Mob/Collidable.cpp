#include ".\collidable.h"
#include "..\\Collision\\Circle.h"
#include "..\\Collision\\Rect.h"
#include "..\\Collision\\Collision.h"
#include "..\\Management\\GameControl.h"

Collidable::Collidable(void)
{
	pCollision = new CollisionSet( );
	mDrawer = new CollisionDrawer();
	AddTask(this);

}

Collidable::~Collidable(void)
{
	delete pCollision;
	delete mDrawer;

	// すべての鉄球から自分というﾀｰｹﾞｯﾄを排除する
	GAMECONTROL->GetStageManager()->GetCurrentStage()->
		GetHaichi()->RemoveAshibaTargets(this);

	// すべての鉄球から自分というﾀｰｹﾞｯﾄを排除する
	REMOVE_FROM_TARGET_LIST( ICollidable );
}

/*
	あたり判定応答ﾘｽﾄをｽｷｬﾝして、
	当たり判定のﾁｪｯｸを行います。

	あたったとき応答ｺｰﾙﾊﾞｯｸを呼ぶ

	図形のﾍﾟｱひとつに大して一回ｺｰﾙﾊﾞｯｸ関数が呼ばれます。
	重複回避の処理は外でやってください。
	例：ｽﾃｰﾀｽを使って、一回あたった場合はあたっても何も起こらないようにするとか

*/
void Collidable::RunTask()
{
	//あたり判定ﾁｪｯｸ
	Collision* cur_frame = pCollision->GetCurFrame();
	if(cur_frame){
		list<ICollidable*>::iterator it = mlTargets.begin(), en = mlTargets.end();
		for( ; it!=en; it++ ){
			ICollidable* item = (*it);
			Collision* coll_frame = item->GetCurFrame();
			//coll_frame = item->GetCurFrame();
			cur_frame->Hantei(coll_frame, this, *it);
		}
	}
}

/*
	当たり判定のﾀｰｹﾞｯﾄを追加する
*/
void Collidable::AddTarget(ICollidable* rTarget)
{
	mlTargets.push_back(rTarget);
}

/*
	当たり判定のﾀｰｹﾞｯﾄを削除する
*/
void Collidable::RemoveTarget(ICollidable* rTarget)
{
	mlTargets.remove(rTarget);
}


//////////////////////////protected//////////////////////////////
/*
	当たり判定用の円を追加する
*/
void Collidable::AddCircle(int rFrameIdx, int rGroupId, int rX, int rY, int rHankei)
{
	pCollision->GetFrame(rFrameIdx)->AddCircle( rGroupId, rX, rY, rHankei );
}

/*
	番号つきの長方形の追加
*/
void Collidable::AddIndexedRect(int rFrameIdx, int rGroupId, int rShapeIdx, int rLeft, int rTop, int rRight, int rBottom)
{
	pCollision->GetFrame(rFrameIdx)->AddIndexedRect(rGroupId, rShapeIdx, rLeft, rTop, rRight, rBottom);
}

/*
	当たり判定用の円を追加する
	位置を後で変えられるように、この図形の番号を指定する
*/
void Collidable::AddMovableCircle(int rFrameIdx, int rGroupId, int rShapeIdx, int rX, int rY, int rHankei)
{
	pCollision->GetFrame(rFrameIdx)->AddMovableCircle( rGroupId, rShapeIdx, rX, rY, rHankei);
}

/*
	番号付きの円を再設定する
*/
void Collidable::SetCircle(int rFrameIdx, int rShapeIdx, int rX, int rY, int rHankei)
{
	CollShape* collshape = pCollision->GetCurFrame()->GetIndexedShape(rShapeIdx);

	Circle* circle = dynamic_cast<Circle*>(collshape);

	if(circle){
		circle->Set(rX, rY, rHankei);
	}
}


/*
	当たり判定用の長方形を追加する
*/
void Collidable::AddRect(int rFrameIdx, int rGroupId, int rLeft, int rTop, int rRight, int rBottom)
{
	pCollision->GetFrame(rFrameIdx)->AddShape(
		new Rect(pCollision->GetFrame(rFrameIdx), rGroupId, rLeft, rTop, rRight, rBottom)
		);
}

// ﾌﾚｰﾑ追加
void Collidable::AddFrame(int rBango)
{
	Collision* newcoll = new Collision( this );
	pCollision->AddFrame(rBango, newcoll);
	
}

// ﾌﾚｰﾑ設定
void Collidable::SetCurFrame(int rBango)
{
	pCollision->SetFrame(rBango);
}

// 現ﾌﾚｰﾑを取得
Collision* Collidable::GetCurFrame()
{
	return pCollision->GetCurFrame();
}