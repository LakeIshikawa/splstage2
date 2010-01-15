#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __OokamiJumpAttack_h__
#define __OokamiJumpAttack_h__

// #include "ActionState.h"
// #include "OokamiBaseAction.h"

class ActionState;
class OokamiBaseAction;
class OokamiJumpAttack;

class OokamiJumpAttack: public OokamiBaseAction
{

	public: OokamiJumpAttack(int rStartX, int rStartY);

	public: OokamiJumpAttack(ActionState* rPrevState);

	public: void BuildState(ActionState* rPrevState);

	public: void OnEnter();

	public: bool Update();

	public: void OnExit();
};

#endif
