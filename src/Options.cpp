#include "Options.h"

Options* Options::mInstance = new Options();

/**
	�W���R���X�g���N�^
	�����I�ɌĂ΂�܂�
*/
Options::Options()
{
}

/**
	�W���f�X�g���N�^
*/
Options::~Options()
{}

/************************************************************//**
*	�I�v�V������ǉ�����
*	\param rKey �I�v�V������ID(�B��)
*	\param rVal �I�v�V�����̒l
*	see Option
****************************************************************/
void Options::Add(string key, Option val)
{
	mMapOptions[key] = val;
}

/************************************************************//**
*	�I�v�V�������Q�Ƃ���
*	\param rKey �I�v�V������ID(�B��)
*	\return �I�v�V�����̒l
****************************************************************/
Options::Option Options::GetOption(string key)
{
	return mMapOptions[key];
}

/************************************************************//**
*	�I�v�V���������݂��邩��q�˂�
*	\param rKey �I�v�V������ID(�B��)
*	\return �w��̃I�v�V���������݂��邩
****************************************************************/
bool Options::IsOptionSet(string key)
{
	return (mMapOptions.find(key) != mMapOptions.end());
}