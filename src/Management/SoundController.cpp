#include "SoundController.h"
#include "..\\Sound\\Bgm.h"
#include "..\\Options.h"

LPTSTR SoundController::sData[] = {
	//TGS�� (�ݸ��)
	TEXT("audio\\se\\fanfare.wav"),
	TEXT("audio\\se\\hissatu.wav"),
	//TGS�� (BGM)
	TEXT("audio\\se\\st1_a_a.wav"), //2
	TEXT("audio\\se\\st1_a_b.wav"),
	TEXT("audio\\se\\st1_boss_a.wav"),
	TEXT("audio\\se\\st1_boss_b.wav"),
	TEXT("audio\\se\\title_a.wav"),
	TEXT("audio\\se\\title_b.wav"),
	TEXT("audio\\se\\game_over.wav"),
	TEXT("audio\\se\\fanfare2.wav"),
	TEXT("audio\\se\\ending.wav"),

	//11�` (BGM)
	TEXT("audio\\se\\st2_a_a.wav"), 
	TEXT("audio\\se\\st2_a_b.wav"),
	TEXT("audio\\se\\st2_boss_a.wav"),
	TEXT("audio\\se\\st2_boss_b.wav"),
	TEXT("audio\\se\\st3_a_a.wav"),	//15
	TEXT("audio\\se\\st3_a_b.wav"),
	TEXT("audio\\se\\st3_boss_a.wav"),
	TEXT("audio\\se\\st3_boss_b.wav"),
	//19�` (�ݸ��)
	TEXT("audio\\se\\st_start.wav"),
	TEXT("audio\\se\\life0_jingle.wav"), //20

	NULL
};


SoundController::SoundController()
{
	mSoundOn = !Options::GetOptions()->IsOptionSet("nosound");
}

SoundController::~SoundController()
{}

/*
	�f�o�C�X�̏�����
*/
void SoundController::Init(HWND rHwnd)
{
	mpSoundManager = new CSoundManager();
	mpSoundManager->Initialize(rHwnd, DSSCL_PRIORITY);
	mpSoundManager->SetPrimaryBufferFormat(2, 44100, 16);

	ZeroMemory( arBgms, sizeof(arBgms ) );

	// ���炩���߃��[�h����
	CSound* test = NULL;
	for(int i=0; sData[i]; i++){
		mpSoundManager->Create(&test, sData[i]);
		mMapStrToSnd[sData[i]] = test;
	}

	// BGM�����[�h
	arBgms[STG1] = new Bgm(mMapStrToSnd[sData[2]], 
							mMapStrToSnd[sData[3]]);

	arBgms[BOSS1] = new Bgm(mMapStrToSnd[sData[4]], 
							mMapStrToSnd[sData[5]]);

	arBgms[TITLE] = new Bgm(mMapStrToSnd[sData[6]], 
							mMapStrToSnd[sData[7]]);

	arBgms[HISATU] = new Bgm(NULL, mMapStrToSnd[sData[1]]);

	arBgms[STGCLEAR] = new Bgm(mMapStrToSnd[sData[0]], 
							mMapStrToSnd[sData[9]]);

	arBgms[ENDING] = new Bgm(mMapStrToSnd[sData[10]], NULL);


	arBgms[STG2] = new Bgm(mMapStrToSnd[sData[11]], 
							mMapStrToSnd[sData[12]]);

	arBgms[BOSS2] = new Bgm(mMapStrToSnd[sData[13]], 
							mMapStrToSnd[sData[14]]);

	arBgms[STG3] = new Bgm(mMapStrToSnd[sData[15]], 
							mMapStrToSnd[sData[16]]);

	arBgms[BOSS3] = new Bgm(mMapStrToSnd[sData[17]], 
							mMapStrToSnd[sData[18]]);

	arBgms[STGSTART] = new Bgm(mMapStrToSnd[sData[19]], NULL);

	arBgms[LIFE0] = new Bgm(mMapStrToSnd[sData[20]], NULL);

	mCurBgm = NULL;
}

/*
	BGM�̍Đ�����Ƀ`�F�b�N���Ȃ���΂Ȃ�Ȃ�(���[�v�̂���)
*/
void SoundController::Process()
{
	// BGM�̲��ۂ�ٰ�߂̕������q������
	if( mCurBgm ){
		mCurBgm->KeepPlaying();
	}

	// SE���Đ����I�������J������
	list<pair<string, CSound*>> tmpLst = mSELst;

	for each( pair<string, CSound*> p in tmpLst ){
		CSound* sound = p.second;
		if( !sound->IsSoundPlaying() ){
			sound->Stop();
			sound->Reset();
			mSELst.remove(p);
			delete sound;
		}
	}
}

/*
	BGM�̐؂�ւ�
*/
void SoundController::SetBGM(BGMS rBgm)
{
	if( mSoundOn && mCurBgm != arBgms[rBgm]){
		if( mCurBgm ) mCurBgm->Stop();
		mCurBgm = arBgms[rBgm];
		mCurBgm->Play();
	}
}

/*
	���ׂĂ�BGM�����Z�b�g����
*/
void SoundController::ResetBGMs()
{
	if( mCurBgm ) mCurBgm->Stop();
	for(int i=0; arBgms[i]; i++){
		arBgms[i]->Reset();
	}
}

/*
	BGM���|�[�Y
*/
void SoundController::PauseBGM()
{
	if( mCurBgm ) mCurBgm->Stop();
}

/*
	�Đ�����
*/
bool SoundController::IsBGMPlaying()
{
	return ( mCurBgm && mCurBgm->IsPlaying() );
}


/*
	���ʉ��̍Đ�
*/
void SoundController::PlaySE(string rPath)
{
	if( mSoundOn ){
		CSound* test;
		mpSoundManager->Create( &test, (LPTSTR)TEXT(rPath.c_str()) );
		
		// ���X�g�ɒǉ�
		pair<string, CSound*> p;
		p.first = rPath;
		p.second = test;
		mSELst.push_back( p );

		test->Play();
	}
}

/*
	SE�����[�v
*/
void SoundController::LoopSE(string rPath)
{
	if( mSoundOn ){
		CSound* test;
		mpSoundManager->Create( &test, (LPTSTR)TEXT(rPath.c_str()) );

		// ���X�g�ɒǉ�
		pair<string, CSound*> p;
		p.first = rPath;
		p.second = test;
		mSELst.push_back( p );

		test->Play( 0, DSBPLAY_LOOPING );
	}
}

/*
	SE�̃��[�v���~�߂�
*/
void SoundController::StopSE(string rPath)
{
	if( mSoundOn ){
		CSound* test;
		pair<string, CSound*> p = GetSE(rPath);
		test = p.second;

		if( test ){
			test->Reset();
			test->Stop();

			mSELst.remove(p);
			delete test;
		}
	}
}

/*
	�T�E���h�Đ����I���E�I�t�ɐݒ�
*/
void SoundController::SetSound(bool mOnOff)
{
	mSoundOn = mOnOff;
}

/*
	\return �ȑO�Đ����ꂽSE
			SE�̃C���X�^���X������Đ�������Ȃ����NULL
	\note �����t�@�C������SE�̉����Đ����X�g�ɓ������ꍇ�́A
	�@�@  �C�ӂ�SE��޼ު�Ă��Ԃ���܂��B
*/
pair<string, CSound*> SoundController::GetSE(string rPath)
{
	for each( pair<string, CSound*> p in mSELst )
	{
		if( p.first.compare(rPath) == 0 ) return p;
	}

	pair<string, CSound*> p;
	p.second = NULL;
	return p;
}

/*
	SE��S�Ď~�߂�
*/
void SoundController::ResetSEs()
{
	if( mSoundOn ){
		list<pair<string, CSound*>> tmp;
		tmp = mSELst;
		for each( pair<string, CSound*> p in tmp){
			StopSE(p.first);
		}
	}

}