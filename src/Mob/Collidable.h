#pragma once

#include "..\\Collision\\CollisionSet.h"
#include "..\\Collision\\CollisionDrawer.h"
#include "Movable.h"
#include "ICollidable.h"

/*
	�����蔻��͈͂����´�èè
*/
class Collidable : public virtual Movable, public ICollidable
{
public:
	Collidable(void);
	virtual ~Collidable(void);

	void RunTask();

	// �����蔻��
	void AddTarget(ICollidable* rTarget);
	void RemoveTarget(ICollidable* rTarget);

	//! ���t���[���̎擾
	Collision* GetCurFrame();

	//! ���̎擾
	int GetFrameSizeX() { return Movable::GetFrameSizeX(); }

	//! �c���̎擾
	int GetFrameSizeY() { return Movable::GetFrameSizeY(); }

	//! X���W�̎�
	float GetX() { return Movable::GetX(); }

	//! Y���W���擾
	float GetY() { return Movable::GetY(); }

	//! �������擾
	bool GetMuki() { return Movable::GetMuki(); }

protected:
	//�ϐ�
	CollisionSet* pCollision;
	list<ICollidable*> mlTargets;
	CollisionDrawer* mDrawer;


	//�֐�
	void AddRect(int rFrameIdx, int rGroupId, int rLeft, int rTop, int rRight, int rBottom);
	void AddIndexedRect(int rFrameIdx, int rGroupId, int rShapeIdx, int rLeft, int rTop, int rRight, int rBottom);
	void AddCircle(int rFrameIdx, int rGroupId, int rX, int rY, int rHankei);
	void AddMovableCircle(int rFrameIdx, int rGroupId, int rShapeIdx, int rX, int rY, int rHankei);
	void SetCircle(int rFrameIdx, int rShapeIdx, int rX, int rY, int rHankei);

	void AddFrame(int rBango);
	void SetCurFrame(int rBango);
};
