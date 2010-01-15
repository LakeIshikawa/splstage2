#pragma once

#include "..\\Teki\\Teki.h"
#include "..\\Jiki\\Jiki.h"
#include "..\\Object\\AshibaInvisible.h"
#include "..\\Object\\AshibaMovable.h"
#include "..\\Object\\AshibaTenbin.h"

#include <list>
#include <typeinfo>

// ﾏｸﾛ
#define ISTEKI(x) (x>0 && x<0x15) /////////////////仮
bool fukaiJun(Movable *a, Movable *b);

/*
	Mobを管理する
*/
class MobManager
{
public:
	MobManager(void);
	~MobManager(void);

	void Process(); // MOBの処理を行う

	void Request(int rNo, int rXPx, int rYPx, 
		bool rTransferOwnership);				// MOBをﾘｸｴｽﾄ(主に配置から)
	void Request(Movable* rObj, 
		bool rTransferOwnership);				// 直接ﾘｸｴｽﾄ

	void Remove(Movable* rTarget);				// 削除
	
	// 複数削除
	template<class T>void RemoveAll(){
		std::list<Movable*>::iterator mob;
		for(mob = mlMobList.begin(); mob != mlMobList.end(); ++mob){
			T* cond = dynamic_cast<T*>(*mob);
			if( cond ) Remove(*mob);
		}
	}

	// ｵﾌﾞｼﾞｪｸﾄのｲﾝｽﾀﾝｽ数を取得
	template<class T> int	 GetInScreenNumOf(){
		// ｵﾌﾞｼﾞｪｸﾄｶｳﾝﾀ
		int count = 0;

		// 回す
		std::list<Movable*>::iterator mob;
		for(mob = mlMobList.begin(); mob != mlMobList.end(); ++mob){
			
			T* cond = dynamic_cast<T*>(*mob);

			// 画面内且つｸﾗｽ名一致
			if( ( cond ) == 0 && 
				!GAMECONTROL->GetStageManager()->GetCurrentStage()->GetMap()->IsGamenGai( 
				(*mob)->GetX(), (*mob)->GetY(), (*mob)->GetFrameSizeX(), (*mob)->GetFrameSizeY()))
			{
				count++;
			}
		}

		return count;
	}

	// tｸﾗｽのｵﾌﾞｼﾞｪｸﾄをﾀｰｹﾞｯﾄとしてrAddtoThisに一括登録
	template <class T> void AddAsTargetAllOf(ICollidable* rAddToThis)
	{
		// 回す
		std::list<Movable*>::iterator mob;
		for(mob = mlMobList.begin(); mob != mlMobList.end(); ++mob){
			
			ICollidable* target = dynamic_cast<ICollidable*>(*mob);
			T* cond = dynamic_cast<T*>(*mob);

			// 画面内且つｸﾗｽ名一致
			if( cond && target){
				rAddToThis->AddTarget(target);
			}
		}
	}

	// tｸﾗｽのｵﾌﾞｼﾞｪｸﾄのﾀｰｹﾞｯﾄﾘｽﾄにrAddMeを登録
	template <class T> void AddAsTargetToAllOf(ICollidable* rAddMe)
	{
		// 回す
		std::list<Movable*>::iterator mob;
		for(mob = mlMobList.begin(); mob != mlMobList.end(); ++mob){
			
			ICollidable* target = dynamic_cast<ICollidable*>(*mob);
			T* cond = dynamic_cast<T*>(*mob);

			// 画面内且つｸﾗｽ名一致
			if( cond && target){
				target->AddTarget(rAddMe);
			}
		}
	}
	
	//! tｸﾗｽのｵﾌﾞｼﾞｪｸﾄからrRemoveMeをﾀｰｹﾞｯﾄから外す
	template <class T> void RemoveFromEveryTarget(ICollidable* rRemoveMe)
	{
			// 回す
			std::list<Movable*>::iterator mob;
			for(mob = mlMobList.begin(); mob != mlMobList.end(); ++mob){
				ICollidable* from = dynamic_cast<ICollidable*>(*mob);
				T* cond = dynamic_cast<T*>(*mob);

				if( cond && from ) from->RemoveTarget( rRemoveMe );
			}

			// 足場の場合
			if( typeid(T) == typeid(Ashiba) || 
				typeid(T) == typeid(AshibaMovable) || 
				typeid(T) == typeid(AshibaInvisible) || 
				typeid(T) == typeid(AshibaTenbin) )
			{
				GAMECONTROL->GetStageManager()->GetCurrentStage()->
					GetHaichi()->RemoveAshibaTargets( rRemoveMe );
			}
	}

	void Reset();								// 全部のオブジェクトを消去する
	void InstantReset();						// 瞬時的にリストをリセットする

	list<Movable*> GetMobList() { return mlMobList; }

private:
	std::list<Movable*>	mlMobList;
	std::list<Movable*>	mlRmvList;

};
