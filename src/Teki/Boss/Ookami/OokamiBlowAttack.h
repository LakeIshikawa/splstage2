#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __OokamiBlowAttack_h__
#define __OokamiBlowAttack_h__

// #include "ActionState.h"
// #include "OokamiBaseAction.h"

class ActionState;
class OokamiBaseAction;
class OokamiBlowAttack;

class OokamiBlowAttack: public OokamiBaseAction
{

	public: OokamiBlowAttack(int rStartX, int rStartY);

	public: OokamiBlowAttack(ActionState* rPrevState);

	public: void BuildState(ActionState* rPrevState);

	public: void OnEnter();

	public: bool Update();

	public: void OnExit();
};

#endif
