#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiBase.h"


class ASOokamiBlowAttack: public ASOokamiBase
{

	public: void OnEnter();

	public: bool Update();

	public: void OnExit();
};

