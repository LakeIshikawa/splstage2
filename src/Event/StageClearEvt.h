#pragma once

#include "Event.h"
#include "..\\Management\\GameControl.h"

/*
	��ʂ��t�F�[�h�A�E�g���A
	�Q�[���I�[�o�[��ʂɈڂ��܂�
*/
class StageClearEvt : public Event
{
public:
	StageClearEvt();
	~StageClearEvt();

	void Trigger();
};
