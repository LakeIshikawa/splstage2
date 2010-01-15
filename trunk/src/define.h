///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////////////////////////////  Splendid Stage  /////////////////////////////////
////  ｹﾞｰﾑのﾊﾟﾗﾒﾀｰ編  /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#pragma once

//ﾌﾟﾛｸﾞﾗﾑ用
#define MAX_TEN	10

//ﾌﾚｰﾑﾀｲﾑ
#define FrameTime 1.0f/25;

//ﾗｲﾄ
#define LIGHT_BASE	0x77000000		/* ﾗｲﾄの明度 0xff000000=濃い */
#define KURAYAMI	0xaa000000		/* 環境の暗闇度 0xff000000=暗い */
#define USER_LIGHT_HANKEI	75

//自機
#define	HERSIZE		 120			/* ﾋﾛｲﾝのｸﾞﾗﾌｨｯｸｻｲｽﾞ */
#define	SPWALK		 1.5f			/* ﾋﾛｲﾝの歩く速度 */	//1.0f
#define	SPANI		 0.2f			/* ｱﾆﾒｰｼｮﾝ補間時間 */
#define	END_TIME	 5.0			/* ﾗｲﾄ強制終了時間 */
#define ACCKOGEKI	 4.0			/* [攻撃]時の加速。1秒間に4pix */
#define	HANTEN_TIME	 0.5f			/* [反転]するための最大照射時間 */
#define JUMP_SHOSP	-10.0f			/* [ｼﾞｬﾝﾌﾟ]初速度(跳ぶ高さ) */
#define GRAVITY		 0.2f			/* 重力 */
#define DRILL_HEIGTH 80				/* [ﾄﾞﾘﾙｷｯｸ]が使える高さ */
#define DRILL_SP	 4.0f			/* [ﾄﾞﾘﾙｷｯｸ]の速度 */
#define FUYU_SP		 1.0f			/* [浮遊]の速度 */
#define DAMAGE_SP	-3.0f			/* [ﾀﾞﾒｰｼﾞ]初速度(跳ぶ高さ) */
#define MUTEKI_TIME	 3.0f			/* [ﾀﾞﾒｰｼﾞ]無敵時間 */
#define TENMETU_TIME 0.2f			/* [ﾀﾞﾒｰｼﾞ]無敵中の点滅 */
#define HISATU_TIME	 15.0f			/* [必殺技]終了時間 */
#define HERINITX	 30				/* ヒロインの出現地 */
#define HERINITY	 400			/* ヒロインの出現地 */

//ｹﾞｰｼﾞ類
#define	LIFE_MAX	 5				/* [ﾗｲﾌ]MAX */
#define	LIFE_SHOKI	 3				/* [ﾗｲﾌ]初期値 */
#define	EMP_MAX		 10.0			/* [ｴﾝﾊﾟｼｰ]MAX */
#define	EMP_SHOKI	 7				/* [ｴﾝﾊﾟｼｰ]初期値 */
#define	EMP_UP		 5				/* [ｴﾝﾊﾟｼｰ]5体倒すと上がる数値*/
#define	EMP_DOWN	 1				/* [ｴﾝﾊﾟｼｰ]ﾀﾞﾒｰｼﾞで下がる数値 */
#define	TEN_MAX		 100.0			/* [ﾃﾝｼｮﾝ]MAX */
#define	TEN_UTIME	 5.0			/* [ﾃﾝｼｮﾝ]ﾗｲﾄでのﾃﾝｼｮﾝ増加時間 */
#define	TEN_DTIME	 2.0			/* [ﾃﾝｼｮﾝ]ﾗｲﾄでのﾃﾝｼｮﾝ減少時間 */
#define	TEN_UP1		 2				/* [ﾃﾝｼｮﾝ]TEN_TIME毎に上がる数値 */
#define	TEN_UP2		 5				/* [ﾃﾝｼｮﾝ]敵を倒して上がる数値 */
#define	TEN_UP3		 10				/* [ﾃﾝｼｮﾝ]ﾒﾘｯﾄｱｲﾃﾑで上がる数値 */
#define	TEN_DOWN1	 2				/* [ﾃﾝｼｮﾝ]TEN_TIME毎に下がる数値 */
#define	TEN_DOWN2	 10				/* [ﾃﾝｼｮﾝ]敵からの攻撃で下がる数値 */

//ﾏｯﾌﾟﾁｯﾌﾟ
#define CHSZX		8				/* 横幅 */
#define CHSZY		8				/* 縦ｻｲｽﾞ */
#define CHNLN		64				/* 画像の一行の個数 */
#define CHIPNX (SCRSZX/CHSZX)		/* 一画面の一行のﾏｯﾌﾟﾁｯﾌﾟ個数 */
#define CHIPNY (SCRSZY/CHSZY)		/* 一画面の一列のﾏｯﾌﾟﾁｯﾌﾟ個数 */

#define	CHIP_HIT	0				/* 当たり判定付きのﾁｯﾌﾟ	*/
#define	CHIP_NOHIT	1				/* 当たり判定抜きのﾁｯﾌﾟ	*/
#define	CHIP_AMHIT	2				/* 足元のみが当たり判定付いているのﾁｯﾌﾟ	*/
#define	CHIP_KGHIT	3				/* 攻撃効果の当たり判定付きﾁｯﾌﾟ	*/
#define CHIP_GMNGAIDN	4				/* 画面外の例外 下 */
#define CHIP_GMNGAIUP	5				/* 画面外の例外	上 */
#define CHIP_GMNGAIRT	6				/* 画面外の例外	右 */
#define CHIP_GMNGAILT	7				/* 画面外の例外	左 */



//画面
#define	SCRSZX		800				/* 画面の横幅 */
#define SCRSZY		600				/* 画面の縦ｻｲｽﾞ */

//設定
#define FRAMERATE	40				/* ﾌﾚｰﾑﾚｰﾄ */
#define N_STAGES	5				/* ｽﾃｰｼﾞ数 */

//ｽｸﾛｰﾙ
#define	ALPHA_LINE	50				/* ﾏｳｽが画面の端っこからこれだけ離れてたらｽｸﾛｰﾙ1開始(遅) */
#define	BETA_LINE	20				/* ﾏｳｽが画面の端っこからこれだけ離れてたらｽｸﾛｰﾙ2開始(速) */
#define SCR_SP1		(80.0/FRAMERATE)	/* ｽｸﾛｰﾙ1の速度(速) */
#define SCR_SP2		(200.0/FRAMERATE)	/* ｽｸﾛｰﾙ2の速度(速) */
#define HER_SCRW	80				/* ﾋﾛｲﾝの端っこからの最小距離 */

//ｽﾃｰｼﾞ
#define STAGE1_MAP		"data\\pure_data.txt"	/* ｽﾃｰｼﾞ1のﾏｯﾌﾟﾃﾞｰﾀ */
#define STAGE1_HAICHI	"data\\pure_teki.txt"	/* ｽﾃｰｼﾞ1の配置 */
#define STAGE1_BOSS_MAP "data\\boss_data.txt"	/* ｽﾃｰｼﾞ1のﾏｯﾌﾟﾃﾞｰﾀ */
#define STAGE1_BOSS_HAICHI "data\\boss_teki.txt"/* ｽﾃｰｼﾞ1のﾏｯﾌﾟﾃﾞｰﾀ */

//配置
#define SHUTSUGEN_POINTX SCRSZX		/* 敵が出現するX座標です */

//敵
#define SHINIPATT_SHOSP	5.6f
#define SHINIPATT_SPX	(40.0/FRAMERATE)

//ヒロインの番号
#define HEROINE_NO	256				/* ヘロイン */

//敵の番号
#define KUMO_NO		1				/* 蜘蛛 */
#define KAERU_NO	2				/* 蛙	*/
#define KOMORI_NO	3				/* 蝙蝠	*/
#define KARIYUMI_NO 4				/* 狩人弓 */
#define KARIKEN_NO	5				/* 狩人剣 */
#define UGOKUKI_NO	6				/* 動く木 */
#define KOBITOA_NO	7				/* 小人A  */
#define KOBITOB_NO	8				/* 小人B  */
#define KOBITOC_NO	9				/* 小人C  */

//オブジェクトの番号
#define STGCLRDOOR_NO 0x1F			/* ステージクリアのドア */

//ｵﾌﾞｼﾞｪｸﾄの番号
#define ARROW_NO	100				/* 矢	*/

//////当たり判定
#define MAX_FRAMES	10				/* 最大ﾌﾚｰﾑ数 */

////GroupIds
#define GRID_KOUGEKI 0				/* 攻撃のｸﾞﾙｰﾌﾟ */
#define GRID_BOGYO	 1				/* 防御のｸﾞﾙｰﾌﾟ */
#define GRID_ITO	 2				/* 蜘蛛の糸		*/
#define GRID_HANTEN	 3				/* 反転をさせる	*/


//////////////////////////////////敵の設定//////////////////////////////////////

//蜘蛛
#define ITO_SP		(100.0/FRAMERATE)	/* 糸の上に歩いてる状態の移動速度 */
#define TEISHI_TIME	1.0f				/* 停止時間 */
#define MOVE_DIST	200					/* 糸移動距離 */
#define ARUKI_SP	(50.0/FRAMERATE)	/* 地面で歩きまわしてるときの速度 */
#define KUMOSX		56					/* 実画像の幅	*/
#define KUMOSY		56					/* 実画像の高さ */
#define ITO_LEN		210					/* 糸の長さ(画像より伸ばせないので注意 */

//蛙
#define KAERUSX		56					/* 実画像の幅	*/
#define KAERUSY		56					/* 実画像の高さ */
#define JUMPSTART_TIME	0.1f			/* ｼﾞｬﾝﾌﾟの直前の間 */
#define TAIKI_TIME	1.0f				/* ｼﾞｬﾝﾌﾟとｼﾞｬﾝﾌﾟのｲﾝﾀｰﾊﾞﾙ */
#define JMPSPX		(100.0/FRAMERATE)	/* ｼﾞｬﾝﾌﾟの初速(X) */
#define JMPTAKASA	190					/* ｼﾞｬﾝﾌﾟの高さ(ﾋﾟｸｾﾙ) */

//蝙蝠
#define KOMOSX		56					/* 実画像の幅	*/
#define KOMOSY		56					/* 実画像の高さ */
#define MAAI_HABA	180					/* 間合いの幅	*/
#define KOMOSPX		(90.0/FRAMERATE)	/* 空中のX速度	*/
#define KOMORAISE	0.15f				/* 上昇力		*/
#define KOMOCHOTEN	55					/* 放物線の頂点	*/

//狩人弓
#define KARIYUMISX	120					/* 実画像の幅	*/
#define KARIYUMISY	120					/* 実画像の高さ */
#define KARIYUMI_WTM 5.0f				/* 待機時間		*/
#define KARIYUMI_WTM2 1.0f				/* 矢と矢の間の時間	*/
#define YUMITGT1	90					/* 自機の手前？	*/
#define YUMITGT2	-90					/* 自機の後ろ？	*/
#define KARIYUMI_NKHI 150				/* 自機との距離がこれより小さくなったら矢を撃つのをやめる */

//矢
#define ARROWSX		48					/* 矢の幅		*/
#define ARROWSY		12					/* 矢の高さ		*/
#define ARROWSPXDIV	60					/* 矢の横速度系	*/
#define ARROWMAXSPY 8					/* 矢の落ちる最大速度 */
#define ARROWSHMTTIME 2.0f				/* 矢が刺さってから消えるまでの時間 */

//狩人剣
#define KARIKENSX	120					/* 実画像の幅	*/
#define KARIKENSY	120					/* 実画像の高さ */
#define KARIKENSPX	(60.0/FRAMERATE)	/* 歩く速度　	*/
#define KARIKENKGHANI 100				/* 攻撃範囲		*/
#define	KARIKENWTM1	1.0f				/* 攻撃前のﾃﾞｨﾚｰ*/
#define	KARIKENWTM2	1.0f				/* 攻撃後のﾃﾞｨﾚｰ*/

//動く木
#define UGOKUKISX	120					/* 実画像の幅	*/
#define UGOKUKISY	184					/* 実画像の高さ */
#define UGOKUKIHANI 100					/* 発動範囲		*/
#define UGOKUKISPX	(40.0/FRAMERATE)	/* 歩く速度		*/



//////////////////////////////オブジェクトの設定//////////////////////////////////

//ステージクリアーのドアー
#define STGCLRDOORSX 162				/* 実画像の幅	*/
#define STGCLRDOORSY 98					/* 実画像の高さ */