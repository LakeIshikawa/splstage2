#include <map>
using namespace std;

#include "Animation.h"

#pragma once

//! ��Ұ��ݾ��
/****************************************************************//**
*	�����̱�Ұ��݂ւ̲���̪����񋟂��܂�
*	\nosubgrouping
********************************************************************/
class AnimationSet
{
	public: 

		//! �W���R���X�g���N�^
		AnimationSet();
		//! �W���f�X�g���N�^
		~AnimationSet();


		//! ����E���Ԃ��o�߂�����
		void ElapseTime(float rElapsedTime);
		
		
		//! ��Ұ��݂̒ǉ�
		void AddAnimation( int rIdx, Animation* rNewAnimation );
		//! ��Ұ��݂̎擾
		Animation* GetAnimation( int rIdx );

		//! �Đ������ݱ�Ұ��݂̐ݒ�
		void SetCurAnimation( int rIdx );
		//! ���ݍĐ����̱�Ұ��݂̎擾
		Animation* GetCurAnimation();
		//! ���ݍĐ�����Ұ��݂̔ԍ��̎擾
		int GetCurAnimationIdx();

	private: 
		map< int, Animation* > mAnimations;
		int mCurIdx;
};

