#include "EventManager.h"

EventManager::EventManager()
{}

EventManager::~EventManager()
{}

/*
	���X�g�ɂ͂����Ă���C�x���g��S��
	���s���A���̌ナ�X�g����ɂ��܂�

	�C�x���g����������܂�
*/
void EventManager::Process()
{
	for each (Event* ev in lstEvents){
		if( ev->ElapseTime() ){
			lstDelEvents.push_back( ev );
		}
	}

	// �s�v�ɂȂ����C�x���g���폜
	for each (Event* rev in lstDelEvents){
		lstEvents.remove( rev );
		delete rev;
	}

	lstDelEvents.clear();
}

/*
	���N�G�X�g�F�@�C�x���g�����X�g�ɓ���܂�
*/
void EventManager::Request(Event *rEvent)
{
	lstEvents.push_back( rEvent );
}
