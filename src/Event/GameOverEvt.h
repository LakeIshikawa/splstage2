#pragma once

#include "Event.h"
#include "..\\Management\\GameControl.h"

/*
	��ʂ��t�F�[�h�A�E�g���A
	�Q�[���I�[�o�[��ʂɈڂ��܂�
*/
class GameOverEvt : public Event
{
public:
	GameOverEvt();
	~GameOverEvt();

	void Trigger();
};
