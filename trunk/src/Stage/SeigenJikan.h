#pragma once


//!	制限時間
/****************************************************************//**
*	制限時間をｺﾝﾄﾛｰﾙ
*	\nosubgrouping
********************************************************************/
class SeigenJikan
{

/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
public:
	SeigenJikan();
	~SeigenJikan(void);
/*@}*/

/****************************************************************//**
*	\name 使うﾒｿｯﾄﾞ
********************************************************************/
/*@{*/
	//! 時間を経たせる
	void Process();
/*@}*/

	//ｽﾃｰｼﾞ毎のMAX時間
	void SetMaxJikan(float rSeigenjikan);

	//ｱｸｾｽ
	float GetRemainingTime();
	float GetMaxJikan();

	//制限時間ｽﾀｰﾄ(ON)
	void SeigenJikanOn();
	//制限時間ｽﾄｯﾌﾟ(OFF)
	void SeigenJikanOff();

	//制限時間ﾘｾｯﾄ
	void SeigenJikanReset();

	
protected:

	float mTimer;

	//MAX時間
	float mMax;
	//ONﾌﾗｸﾞ
	bool mTimeFl;

	//TIME UP
	float mTimeUpTimer;

};
