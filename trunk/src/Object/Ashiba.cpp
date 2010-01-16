#include "Ashiba.h"
#include "..\\Management\\GameControl.h"
#include "..\\Mob\\IRideCapable.h"

/**
	標準コンストラクタ
*/
Ashiba::Ashiba(int rXPx, int rYPx, float rZ, string rGraphic, int rSizeX, int rSizeY)
{
	ASHIBASX = rSizeX;
	ASHIBASY = rSizeY;

	mGraphic = rGraphic;

	mX = rXPx;
	mY = rYPx - ASHIBASY + SP->CHSZY;
	mZ = rZ;

	AddTarget(GAMECONTROL->GetJiki());

	AddFrame(0);
	AddIndexedRect(0, SP->GRID_BOUND, 0, 0, 0, ASHIBASX, 1);
}

/**
	標準デストラクタ
*/
Ashiba::~Ashiba()
{}

/************************************************************//**
*	\return 足場の幅
****************************************************************/
int Ashiba::GetFrameSizeX()
{
	return ASHIBASX;
}

/************************************************************//**
*	\return 足場の縦幅
****************************************************************/
int Ashiba::GetFrameSizeY()
{
	return ASHIBASY;
}


/************************************************************//**
*	1ﾌﾚｰﾑ処理
****************************************************************/
void Ashiba::Move()
{
	UpdateRiders();
	Draw();

	//ﾃﾞﾊﾞｯｸﾞ
	if(mDrawer){
		mDrawer->SetCollision(pCollision->GetCurFrame());
		mDrawer->Draw();
	}
}

/************************************************************//**
*	乗客の速度に足場の速度を足しこむ
****************************************************************/
void Ashiba::UpdateRiders()
{
	// 削除予定の乗客を削除する
	for each (IRideCapable* delrider in mDelRiders){
		mRiders.remove(delrider);
	}
	mDelRiders.clear();

	// 乗客を更新
	for each (IRideCapable* rider in mRiders){

		// 足場の位置に合わせて、速度を足しこむ
		rider->AddSpX(mSpX);
		rider->SetY(mY+ mSpY + GetCollRect()->Top() - rider->GetRideRect()->Bottom());

		// 左右に乗客が左右に出てってしまったら降ろす
		int aleft  = mX + GetCollRect()->Left();
		int aright = mX + GetCollRect()->Right();
		int rleft  = rider->GetX() + rider->GetRideRect()->Left();
		int rright = rider->GetX() + rider->GetRideRect()->Right();

		// 横が足場から外れたら降りる
		if( rleft >= aright || rright < aleft )
		{
			GetOff(rider);
			rider->GetOffResponse(this);
		}
	}
}

/************************************************************//**
*	乗る
*	\param rRider 乗ろうたる者
*	既に乗っている場合は何もしない
****************************************************************/
void Ashiba::GetOn(IRideCapable* rRider)
{
	for each(IRideCapable* rider in mRiders){
		if ( rider == rRider ) return;
	}
	mRiders.push_back(rRider);
}

/************************************************************//**
*	降りる
*	\param rRider 降りようたる者
****************************************************************/
void Ashiba::GetOff(IRideCapable* rRider)
{
	mDelRiders.push_back(rRider);
}

/************************************************************//**
*	描画
****************************************************************/
void Ashiba::Draw()
{
	DX_SCROLL_DRAW(mGraphic, mX, mY, 0, 0, ASHIBASX, ASHIBASY);
}

/************************************************************//**
*	標準の当たり判定\n
*
*	ヒロインだけを対象する。敵と足場の当たり応答は、敵が担当する。
*	
*	\param rCollObject	当たった先のｵﾌﾞｼﾞｪｸﾄ(例：ﾋﾛｲﾝ)
*	\param rThisGroupId	こっちのGROUPID(所々によって違う)
*	\param rOpGroupId	当たった先のｵﾌﾞｼﾞｪｸﾄのGROUPID(所々によって違う)
*
****************************************************************/
void Ashiba::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	IRideCapable* rider = dynamic_cast<IRideCapable*>(rCollObject);

	if( rider && rOpGroupId == SP->GRID_BOUND ){
		float ashiba_x = mX;
		float ashiba_y = mY;

		Rect* jbound = rider->GetRideRect(); //ﾋﾛｲﾝのﾊﾞｳﾃﾞｨﾝｸﾞﾎﾞｯｸｽ
		Rect* abound = GetCollRect();

		float sax = (ashiba_x + abound->Left()) + (abound->Right()-abound->Left())/2 - ((rider->GetX() + jbound->Left())+ (jbound->Right()-jbound->Left())/2);
		float say = (ashiba_y + abound->Top()) + (abound->Bottom()-abound->Top())/2 - ((rider->GetY() + jbound->Top()) + (jbound->Bottom()-jbound->Top())/2);

		float merix = (sax>0) ? (rider->GetX() + (rider->GetFrameSizeX() - jbound->Left()) - (ashiba_x + abound->Left())) : (ashiba_x + abound->Right() - (rider->GetX()+jbound->Left()));
		float meriy = (say>0) ? (rider->GetY() + jbound->Bottom() - (ashiba_y + abound->Top())) : (ashiba_y + abound->Bottom() - (rider->GetY()+jbound->Top()));

		// 左右決定
		if( merix < meriy )
		{
			// 位置修正
			if( sax<0 )		// 右
				RespRight(rider, jbound);
			else			// 左
				RespLeft(rider, jbound);

			// 速度修正
			//if( (sax<0 && rider->GetSpX()<0) || (sax>0 && rider->GetSpX()>0)) {rider->SetSpX(0);}
		}

		// 上下決定
		else
		{
			if( say>0 ){	// 上
				RespUp(rider, jbound);
			}
			else			// 下
				RespDown(rider, jbound);
		}
	}
}

/************************************************************//**
*	当たり応答・左
****************************************************************/
void Ashiba::RespLeft(IRideCapable* rider, Rect* jbound)
{
	//rider->SetX(mX + GetCollRect()->Left() - (rider->GetFrameSizeX()- jbound->Left()));
}

/************************************************************//**
*	当たり応答・右
****************************************************************/
void Ashiba::RespRight(IRideCapable* rider, Rect* jbound)
{
	//rider->SetX(mX + GetCollRect()->Right() - jbound->Left());
}

/************************************************************//**
*	当たり応答・上
****************************************************************/
void Ashiba::RespUp(IRideCapable* rider, Rect* jbound)
{
	// 速度修正
	if(rider->GetSpY()>0) {
		rider->SetY(mY + mSpY + GetCollRect()->Top() - jbound->Bottom());
		rider->SetSpY(0);

		// 乗った
		GetOn(rider);
		rider->RideResponse(this);
	}
}

/************************************************************//**
*	当たり応答・下
****************************************************************/
void Ashiba::RespDown(IRideCapable* rider, Rect* jbound)
{
	//rider->SetY(mY + mSpY + GetCollRect()->Bottom() - jbound->Top());

	// 速度修正
	//if(rider->GetSpY()<0) rider->SetSpY(0);
}

/*

*/
float Ashiba::GetSpX()
{
	return mSpX;
}

/*

*/
float Ashiba::GetSpY()
{
	return mSpY;
}

/*

*/
Rect* Ashiba::GetCollRect()
{
	return (Rect*)pCollision->GetFrame(0)->GetIndexedShape(0);
}

