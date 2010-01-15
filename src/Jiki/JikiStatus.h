#pragma once

class Action;

/*
	���@�̃X�e�[�^�X�B

	STATUS��ACTION�̏ꍇ�́ACurrentAction��
	���ݎ��@���s���Ă���A�N�V�����ւ̃|�C���^������܂��B
	����ȊO�̏ꍇ�͒��g������ł��B
*/
class JikiStatus
{
public:

	enum STATUS
	{
		FUTSU,
		ACTION,
		KUCHU,
		DAMAGE
	};

	JikiStatus(void);
	~JikiStatus(void);

	STATUS	GetStatus();
	Action*	GetCurrentAction();

private:
	Action* mpCurrentAction;
	STATUS	mCurrentStatus;

};
