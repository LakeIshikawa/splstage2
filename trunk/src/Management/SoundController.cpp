#include "SoundController.h"
#include "..\\Sound\\Bgm.h"
#include "..\\Options.h"

LPTSTR SoundController::sData[] = {
	//TGS版 (ｼﾝｸﾞﾙ)
	TEXT("audio\\se\\fanfare.wav"),
	TEXT("audio\\se\\hissatu.wav"),
	////TGS版 (SE)
	//TEXT("audio\\se\\se_enpacy_up.wav"),
	//TEXT("audio\\se\\se_hiroin_damage.wav"),
	//TEXT("audio\\se\\se_hiroin_hissatu.wav"),
	//TEXT("audio\\se\\se_hiroin_junp.wav"),
	//TEXT("audio\\se\\se_hiroin_kuutyuukougeki.wav"),
	//TEXT("audio\\se\\se_hiroin_tijoukougeki.wav"),
	//TEXT("audio\\se\\se_kettei.wav"),
	//TEXT("audio\\se\\se_kougekimeityuu.wav"),
	//TEXT("audio\\se\\se_raitokirikae.wav"),
	//TEXT("audio\\se\\se_tensyon_maxn.wav"),
	//TGS版 (BGM)
	TEXT("audio\\se\\st1_a_a.wav"), //2
	TEXT("audio\\se\\st1_a_b.wav"),
	TEXT("audio\\se\\st1_boss_a.wav"),
	TEXT("audio\\se\\st1_boss_b.wav"),
	TEXT("audio\\se\\title_a.wav"),
	TEXT("audio\\se\\title_b.wav"),
	TEXT("audio\\se\\game_over.wav"),
	TEXT("audio\\se\\fanfare2.wav"),
	TEXT("audio\\se\\ending.wav"),

	//11〜 (BGM)
	TEXT("audio\\se\\st2_a_a.wav"), 
	TEXT("audio\\se\\st2_a_b.wav"),
	TEXT("audio\\se\\st2_boss_a.wav"),
	TEXT("audio\\se\\st2_boss_b.wav"),
	TEXT("audio\\se\\st3_a_a.wav"),	//15
	TEXT("audio\\se\\st3_a_b.wav"),
	TEXT("audio\\se\\st3_boss_a.wav"),
	TEXT("audio\\se\\st3_boss_b.wav"),
	//19〜 (ｼﾝｸﾞﾙ)
	TEXT("audio\\se\\st_start.wav"),
	TEXT("audio\\se\\life0_jingle.wav"), //20
	////21〜 (SE)
	//TEXT("audio\\se\\se_hiroin_hissatu_end.wav"),
	//TEXT("audio\\se\\se_bat_fly.wav"),
	//TEXT("audio\\se\\se_boss1_atack.wav"),
	//TEXT("audio\\se\\se_boss2_bress_atack.wav"),
	//TEXT("audio\\se\\se_boss2_bress_out.wav"), //35
	//TEXT("audio\\se\\se_boss2_bress_tame.wav"),
	//TEXT("audio\\se\\se_boss2_move.wav"),
	//TEXT("audio\\se\\se_boss2_house_break.wav"),
	//TEXT("audio\\se\\se_boss3_hart.wav"),
	//TEXT("audio\\se\\se_boss3_kagami1.wav"), //40
	//TEXT("audio\\se\\se_boss3_kagami2.wav"),
	//TEXT("audio\\se\\se_boss3_kettei.wav"),
	//TEXT("audio\\se\\se_boss3_syannderia.wav"),
	//TEXT("audio\\se\\se_boss3_toge.wav"),
	//TEXT("audio\\se\\se_boss3_trannp.wav"),// 45
	//TEXT("audio\\se\\se_cansel.wav"),
	//TEXT("audio\\se\\se_fire.wav"),
	//TEXT("audio\\se\\se_item_get.wav"),
	//TEXT("audio\\se\\se_kaeru_junp.wav"), //50
	//TEXT("audio\\se\\se_ken_atack.wav"),
	//TEXT("audio\\se\\se_kumo_ito.wav"),
	//TEXT("audio\\se\\se_teki_down.wav"),
	//TEXT("audio\\se\\se_tensyon_up.wav"),
	//TEXT("audio\\se\\se_ttekkyuu_hassya.wav"), //55
	//TEXT("audio\\se\\se_ttekkyuu_move.wav"),
	//TEXT("audio\\se\\se_ttekkyuu_setti.wav"),
	//TEXT("audio\\se\\se_yumi_hassya.wav"),
	//TEXT("audio\\se\\se_yumi_tame.wav"),
	//TEXT("audio\\se\\se_zanki_up.wav"), //60
	//TEXT("audio\\se\\se_team_rogo.wav"),

	NULL
};


SoundController::SoundController()
{
	mSoundOn = !Options::GetOptions()->IsOptionSet("nosound");
}

SoundController::~SoundController()
{}

/*
	デバイスの初期化
*/
void SoundController::Init(HWND rHwnd)
{
	mpSoundManager = new CSoundManager();
	mpSoundManager->Initialize(rHwnd, DSSCL_PRIORITY);
	mpSoundManager->SetPrimaryBufferFormat(2, 44100, 16);

	ZeroMemory( arBgms, sizeof(arBgms ) );

	// あらかじめロードする
	CSound* test = NULL;
	for(int i=0; sData[i]; i++){
		mpSoundManager->Create(&test, sData[i]);
		mMapStrToSnd[sData[i]] = test;
	}

	// BGMもロード
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
	BGMの再生を常にチェックしなければならない(ループのため)
*/
void SoundController::Process()
{
	// BGMのｲﾝﾄﾛとﾙｰﾌﾟの部分を繋がせる
	if( mCurBgm ){
		mCurBgm->KeepPlaying();
	}

	// SEが再生し終わったら開放する
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
	BGMの切り替え
*/
void SoundController::SetBGM(BGMS rBgm)
{
	if( mSoundOn ){
		if( mCurBgm ) mCurBgm->Stop();
		mCurBgm = arBgms[rBgm];
		mCurBgm->Play();
	}
}

/*
	すべてのBGMをリセットする
*/
void SoundController::ResetBGMs()
{
	if( mCurBgm ) mCurBgm->Stop();
	for(int i=0; arBgms[i]; i++){
		arBgms[i]->Reset();
	}
}

/*
	BGMをポーズ
*/
void SoundController::PauseBGM()
{
	if( mCurBgm ) mCurBgm->Stop();
}

/*
	再生中か
*/
bool SoundController::IsBGMPlaying()
{
	return ( mCurBgm && mCurBgm->IsPlaying() );
}


/*
	効果音の再生
*/
void SoundController::PlaySE(string rPath)
{
	if( mSoundOn ){
		CSound* test;
		mpSoundManager->Create( &test, (LPTSTR)TEXT(rPath.c_str()) );
		
		// リストに追加
		pair<string, CSound*> p;
		p.first = rPath;
		p.second = test;
		mSELst.push_back( p );

		test->Play();
	}
}

/*
	SEをループ
*/
void SoundController::LoopSE(string rPath)
{
	if( mSoundOn ){
		CSound* test;
		mpSoundManager->Create( &test, (LPTSTR)TEXT(rPath.c_str()) );

		// リストに追加
		pair<string, CSound*> p;
		p.first = rPath;
		p.second = test;
		mSELst.push_back( p );

		test->Play( 0, DSBPLAY_LOOPING );
	}
}

/*
	SEのループを止める
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
	サウンド再生をオン・オフに設定
*/
void SoundController::SetSound(bool mOnOff)
{
	mSoundOn = mOnOff;
}

/*
	\return 以前再生されたSE
			SEのインスタンスが一個も再生中じゃなければNULL
	\note 同じファイル名のSEの何個が再生リストに入った場合は、
	　　  任意のSEｵﾌﾞｼﾞｪｸﾄが返されます。
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