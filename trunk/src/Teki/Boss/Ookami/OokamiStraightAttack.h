#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __OokamiStraightAttack_h__
#define __OokamiStraightAttack_h__

// #include "ActionState.h"
// #include "OokamiBaseAction.h"

class ActionState;
class OokamiBaseAction;
class OokamiStraightAttack;

class OokamiStraightAttack: public OokamiBaseAction
{

	public: void BuildState(ActionState* rPrevState);

	public: void OnEnter();

	public: bool Update();

	public: void OnExit();
};

#endif
