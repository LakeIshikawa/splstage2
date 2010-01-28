#include ".\map.h"

#include <iostream>
#include <fstream>

#include "..\\Management\\GameControl.h"
#include "..\\Light\\Light.h"

using namespace std;

#define OVERWRITE_DOWN ((i==0) || (chip == SP->CHIP_AMHIT || chip == SP->CHIP_KGHIT || outAtari[j] == SP->CHIP_NOHIT))
#define OVERWRITE_FRONT ((i==0) || (chip == SP->CHIP_HIT || chip == SP->CHIP_KGHIT || (outAtari[j] == SP->CHIP_NOHIT)))
#define OVERWRITE_BACK ((i==0) || (chip == SP->CHIP_HIT || chip == SP->CHIP_KGHIT))

Map::Map()
{
	// 設定定数
	ALPHA_LINE = GI("ALPHA_LINE");
	BETA_LINE = GI("BETA_LINE");
	SCR_SP1 = GF("SCR_SP1");
	SCR_SP2 = GF("SCR_SP2");
	HER_SCRW = GI("HER_SCRW");


	mGamenSprites	= NULL;
	mScpx			= 0;
	mScrSp			= 0;
}

Map::~Map(void)
{
}

/*
	指定されたファイルからﾏｯﾌﾟﾃﾞｰﾀを読み込みます。
	ﾏｯﾌﾟのｻｲｽﾞがﾌｧｲﾙ内容とあわせたｻｲｽﾞとなります。

	ｴﾗｰの場合、1を返します。
*/
int Map::Load(string rFName, string rMapChipGr)
{

	//////////////////////////// ﾏｯﾌﾟﾃﾞｰﾀの読み込み ///////////////////////////
	/*///             ﾌｧｲﾙのﾃﾞｰﾀにｻｲｽﾞをあわせてﾏｯﾌﾟﾃﾞｰﾀ作成              ///*/
	///////////////////////////////////////////////////////////////////////////

	if( LoadFromFile(rFName) == 1) 
	{
		GAMECONTROL->ThrowError("ﾏｯﾌﾟﾃﾞｰﾀファイル未発見: %s",  rFName.c_str() );
		exit(1);
	}

	////////////////////////////// ｽﾌﾟﾗｲﾄ配列作成 /////////////////////////////
	/*///       処理のため、ﾏｯﾌﾟをﾛｰﾄﾞの時にｽﾌﾟﾗｲﾄ化するべきです。        ///*/
	///////////////////////////////////////////////////////////////////////////

	// ｽﾌﾟﾗｲﾄ配列を確保
	mGamenSprites = new LPDIRECT3DTEXTURE9[ mNGamen ];

	// ﾏｯﾌﾟﾁｯﾌﾟ画像をゲット
	LPDIRECT3DTEXTURE9 tx_mapchip = GAMECONTROL->GetDXController()->GetTextureOf(rMapChipGr);

	for(int gamen=0; gamen<mNGamen; gamen++){

		// ﾃｸｽﾁｬ作成
		GAMECONTROL->GetDXController()->CreateNewTexture( 1024, 	1024, 1, 0, D3DFMT_A8B8G8R8, 
			D3DPOOL_MANAGED, &mGamenSprites[gamen]);

		D3DLOCKED_RECT rc_gamen;
		mGamenSprites[gamen]->LockRect(0, &rc_gamen, NULL, 0);
		LPDWORD data_gamen;

		D3DLOCKED_RECT rc_mapchip;
		tx_mapchip->LockRect(0, &rc_mapchip, NULL, 0);
		LPDWORD data_mapchip = (LPDWORD)((LPBYTE)rc_mapchip.pBits);

		int markerx = 0; // 0～8の繰り返し
		int markery = 0; // 0～8の繰り返し

		for(DWORD i=0; i<SP->SCRSZY; i++){
			data_gamen = (LPDWORD)((LPBYTE)rc_gamen.pBits + rc_gamen.Pitch * i);

			for(DWORD j=0;j<SP->SCRSZX;j++){

				int data = (*(mData[ i/SP->CHSZY ]))[ j/SP->CHSZX + gamen*SP->CHIPNX ];
				int dx = data%SP->CHNLN;
				int dy = data/SP->CHNLN;

				data_mapchip = (LPDWORD)((LPBYTE)rc_mapchip.pBits + rc_mapchip.Pitch * (dy*SP->CHSZY+ markery));
				*data_gamen = data_mapchip[ dx*SP->CHSZX+markerx ];
				data_gamen++;
				markerx = (markerx+1)%SP->CHSZX;
			}
			markery = (markery+1)%SP->CHSZY;
			markerx=0;
		}
		mGamenSprites[gamen]->UnlockRect(0);
		tx_mapchip->UnlockRect(0);
	}
	return 0;
}

/*
	リソースを解放する
*/
void Map::UnLoad()
{
	// テクスチャーを解放
	for( int i=0; i<mNGamen; i++){
		mGamenSprites[i]->Release();
	}
	delete[] mGamenSprites;

	// データ解放
	vector<vector<int>*>::iterator it;
	for(it = mData.begin(); it != mData.end(); it++){
		vector<int>* sublist = *it;
		//delete sublist;
	}

	mData.clear();
}


/*
	ファイルからデータを読み込む
*/
int Map::LoadFromFile(string rFName)
{
	// ﾌｧｲﾙ展開
	ifstream map_file( rFName.c_str() );

	if( !map_file.is_open() ) return 1;  // ファイル未発見

	string line;	// 行ﾊﾞｯﾌｧｰ

	// 読み込み
	while( getline( map_file, line ) ){
		vector<int>* data_line = new vector<int>;

		char* tokp = strtok( (char*)line.c_str(), " " );
		data_line->push_back( atoi( tokp ) );

		while( tokp!=NULL ){
			tokp = strtok( NULL, " " );
			if(tokp) data_line->push_back( atoi( tokp ) );
		}// while

		mData.push_back( data_line );
	}// while
	
	map_file.close();

	mNGamen = (int)(*mData[0]).size() / SP->CHIPNX;
	mMaxScr = ( GetNGamen()-1 ) * SP->SCRSZX;

	return 0;
}

/*
	画面にﾏｯﾌﾟを描画する
*/
void Map::Draw()
{
	// まだ読み込まれていない場合
	if(mData.empty())
		return;

	// 描画の処理
	int gamen1 = mScpx/SP->SCRSZX;
	int gamen2 = gamen1+1;
	DX_DRAW( mGamenSprites[gamen1], gamen1*SP->SCRSZX - mScpx, 0, 0, 0, SP->SCRSZX, SP->SCRSZY );

	if(mScpx < mMaxScr) // 一番右までｽｸﾛｰﾙした場合、画面一個しか描画しない
		DX_DRAW( mGamenSprites[gamen2], gamen2*SP->SCRSZX - mScpx, 0, 0, 0, SP->SCRSZX, SP->SCRSZY );

}

/*
	ｽｸﾛｰﾙ処理
	1- ﾗｲﾄの操作によろｽｸﾛｰﾙ
	2- ﾋﾛｲﾝに夜ｽｸﾛｰﾙ
*/
void Map::Scroll()
{
	// ﾋﾛｲﾝが死ぬところはｽｸﾛｰﾙしない
	if( GAMECONTROL->GetJiki()->IsDying() || !GAMECONTROL->GetJiki()->IsControl() ||
		GAMECONTROL->GetJiki()->IsBusy()) return;

	// ﾗｲﾄ情報を得る
	int light_x = GAMECONTROL->GetUserLightControl()->GetControlLight()->GetX();
	int light_hk = GAMECONTROL->GetUserLightControl()->GetControlLight()->GetHankei();

	// 1- ﾗｲﾄ
	mScrSp = 0;
	if( light_x-light_hk < ALPHA_LINE ) 
		mScrSp = -SCR_SP1;
	else if( light_x+light_hk > SP->SCRSZX-ALPHA_LINE ) mScrSp = SCR_SP1;

	if( light_x-light_hk < BETA_LINE ) mScrSp = -SCR_SP2;
	else if( light_x+light_hk > SP->SCRSZX-BETA_LINE ) mScrSp = SCR_SP2;

	mScpx += mScrSp ;

	// 2- ﾋﾛｲﾝ
	int hiroin_x = GAMECONTROL->GetJiki()->GetAtHtPointX();
	if(  hiroin_x - HER_SCRW < mScpx)
		mScpx = ( hiroin_x - HER_SCRW );
	else if(  hiroin_x + HER_SCRW > mScpx + SP->SCRSZX)
		mScpx = ( hiroin_x - SP->SCRSZX + HER_SCRW );

	//-- ｽｸﾛｰﾙの最大値
	int saidai = GetMaxScrollP();
	if( mScpx > saidai ){
		mScpx = saidai;
		mScrSp = 0;
	}
	if( mScpx < 0 ){
		mScpx = 0;
		mScrSp = 0;
	}
}

/*
	1- ﾏｯﾌﾟ表示
	2- ｽｸﾛｰﾙ処理
*/
void Map::Process()
{
	Scroll();
	Draw();
}


/*
	ｽｸﾛｰﾙﾎﾟｲﾝﾀを設定
*/
void Map::SetScrollP(int rScrlPoint)
{
	mScpx = rScrlPoint;
	if( mScpx<0 ) mScpx = 0;
}

/*
	ｽｸﾛｰﾙﾎﾟｲﾝﾀを取得
*/
int Map::GetScrollP()
{
	return mScpx;
}

/*
	スクロール速度を取得
*/
float Map::GetScrollSp()
{
	return mScrSp;
}

/*
	当たり判定
	返し値：
	0- 当たってる
	1- 当たっていない
	2- 頭がすり抜けるが、乗れる
	3- 攻撃効果のあるﾁｯﾌﾟ
	4- 画面外
*/
int Map::AtariHantei( int rX, int rY )
{
	if( rX < 0 )
		return SP->CHIP_GMNGAILT;
	if( rY < 0 )
		return SP->CHIP_GMNGAIUP;
	if( rX >= mNGamen * SP->SCRSZX )
		return SP->CHIP_GMNGAIRT;
	if( rY >= SP->SCRSZY)
		return SP->CHIP_GMNGAIDN;

	// 仮！！！！！！！！！！！！！！！！
	int data = (*(mData[(rY)/SP->CHSZY]))[(rX)/SP->CHSZX];

	if(data < SP->CHNLN) return SP->CHIP_NOHIT;			//1行目
	else if(data < SP->CHNLN*8) return SP->CHIP_AMHIT;	//2~9
	else if(data < SP->CHNLN*52) return SP->CHIP_NOHIT;	//11~60
	else if(data < SP->CHNLN*82) return SP->CHIP_HIT;	//61~110
	else if(data < SP->CHNLN*126) return SP->CHIP_KGHIT;//61~110

}

/*
	////////////////////////////////////////////////////////////
	////////////////  ｻﾞ・ｽｰﾊﾟｰ・当たり判定関数 //////////////// 
	////////////////////////////////////////////////////////////

	- この関数はｽﾌﾟﾗｲﾄ(MOB)見たいな、速度、加速などを計算に入れ、
	  画面中に動いているもの次のﾌﾚｰﾑの位置を判定し、徹底的に当た
	  り判定を行います。

	- 入力変数:
	  rX	ｵﾌﾞｼﾞｪｸﾄの左上のX座標
	  rY	ｵﾌﾞｼﾞｪｸﾄの左上のY座標
	  rMuki	0-> 左　1-> 右
	  rSpx	X速度
	  rSpy	Y速度
	  rAccX X加速
	  rAccY Y加速
	  rMapAtHtX[方向][点]  
	  rMapAtHtY[方向][点]  
			方向-> 0:下 1:上 2:前 3:後 
			点->当たり判定の点(画像相対座標) ... -1で終了 (最大10点)

	- 出力変数
	  outAtari[方向]	
			1:当たっている　0:当たっていない
			方向-> 0:下 1:上 2:前 3:後 
      outKabeIchi[方向]	
			その方向の壁の位置(当たっている場合のみ),
			値はその軸の座標となります(上下:Y軸, 左右:X座標)
			方向-> 0:下 1:上 2:前 3:後 
	  	  
*/
void Map::SuperAtariHantei(float rX, float rY, bool rMuki, float rSpX, float rSpY,
						   float rAccX, float rAccY, HITPOINT rMapAtHtX, HITPOINT rMapAtHtY,
						   int rSizeX, int rSizeY, int *outAtari, int* outKabeIchi)
{
	int shirabe_masu[4] = { SP->CHSZY, -SP->CHSZY, SP->CHSZX*GetMukiMult(rMuki), -SP->CHSZX*GetMukiMult(rMuki) };
	float shirabe_jiku[4] = { rY, rY, rX, rX };

	for( int i=0; i < 4; i++ ){
		outAtari[i] = SP->CHIP_NOHIT;
		outKabeIchi[i] = 0;
	}

	float shirabeX[4] = { 0, 0, 0, 0 };
	float shirabeY[4] = { 0, 0, 0, 0 };
	float tugispX[4] = { 0, 0, rSpX, rSpX };
	float tugispY[4] = { rSpY, rSpY, 0, 0 };
	float tugiaccX[4] = { 0, 0, rAccX, rAccX };
	float tugiaccY[4] = { rAccY, rAccY, 0, 0 };

	for( int j = 0; j < 4; j++ ){
		for( int i = 0; rMapAtHtY[j][i] != -1; i++ ){	
			float mirai_x = rX + (!rMuki*rSizeX) + GetMukiMult(rMuki)*rMapAtHtX[j][i] + tugispX[j] + tugiaccX[j];
			float mirai_y = rY + rMapAtHtY[j][i] + tugispY[j] + tugiaccY[j];

			// 8ﾋﾟｸｾﾙずつを調べていきます。
			float spx = tugispX[j] + tugiaccX[j];
			float spy = tugispY[j] + tugiaccY[j];

			float spMAX = max(spx, spy);
			float shirabespx = spx>=spy ? 1 : spy/spx;
			float shirabespy = spy>=spx ? 1 : spx/spy;
			if(spx == 0) shirabespx = 0;
			if(spy == 0) shirabespy = 0;

			float curx = rX + (!rMuki*rSizeX) + GetMukiMult(rMuki)*rMapAtHtX[j][i] + shirabespx;
			float cury = rY + rMapAtHtY[j][i] + shirabespy;
			
			for( int srbcnt = 0; srbcnt < (int)spMAX + 1; srbcnt++ ){

				int chip = GAMECONTROL->GetStageManager()->GetCurMap()->AtariHantei(curx,cury);
				if( chip == SP->CHIP_HIT || chip == SP->CHIP_AMHIT|| chip == SP->CHIP_KGHIT || IsGamenGai(chip)){
					if( (j==0 && OVERWRITE_DOWN) || (j==2 && OVERWRITE_FRONT) || j==1 || (j==3 && OVERWRITE_BACK)){
						outAtari[j] = chip;
					}
				}
				if( chip == SP->CHIP_HIT || chip == SP->CHIP_AMHIT || chip == SP->CHIP_KGHIT || IsGamenGai(chip)){
					if( j < 2 ){
						shirabeY[j] = shirabe_jiku[j] + rMapAtHtY[j][i];
						shirabeX[j] = mirai_x;
					}else{
						shirabeX[j] = shirabe_jiku[j] + (!rMuki*rSizeX) + GetMukiMult(rMuki)*rMapAtHtX[j][i];
						shirabeY[j] = mirai_y;
					}
					while( true ){
						int chip = GAMECONTROL->GetStageManager()->GetCurMap()->AtariHantei(shirabeX[j],shirabeY[j]);
						if ( chip == SP->CHIP_AMHIT || chip == SP->CHIP_HIT || chip == SP->CHIP_KGHIT || IsGamenGai(chip))
							break;
						if( j < 2 ) shirabeY[j] += shirabe_masu[j];
						else shirabeX[j] += shirabe_masu[j];
					}
					shirabeY[j] -= (int)shirabeY[j] % shirabe_masu[j];
					shirabeX[j] -= (int)shirabeX[j] % shirabe_masu[j];	
					if((j==0 && OVERWRITE_DOWN) || (j==1))
						outKabeIchi[j] = shirabeY[j];
					else if( (j==2 && OVERWRITE_FRONT) || (j==3))
						outKabeIchi[j] = shirabeX[j];
					break;
				}

				curx += shirabespx;
				cury += shirabespy;
			}
		}//for end(i)
	}//for end(j)


}

/* 0->-1, 1->1 */
int		Map::GetMukiMult(int rMuki)
{
	if( rMuki == 0 )	return	-1;

	else
		return	1;
}

// ｹﾞｯﾀｰ
int Map::GetNGamen()
{
	return mNGamen;
}

// ｹﾞｯﾀｰ
int Map::GetMaxScrollP()
{
	return mMaxScr;
}

// 画面外
bool Map::IsGamenGai(int rChipType)
{
	return (
		rChipType == SP->CHIP_GMNGAIDN ||
		rChipType == SP->CHIP_GMNGAIUP ||
		rChipType == SP->CHIP_GMNGAIRT ||
		rChipType == SP->CHIP_GMNGAILT );

}

// Mobが画面外
bool Map::IsGamenGai(int rX, int rY, int rSx, int rSy)
{
	return ((rX+rSx<mScpx) || (rX>mScpx+SP->SCRSZX) || (rY+rSy<0) || (rY>SP->SCRSZY));
}