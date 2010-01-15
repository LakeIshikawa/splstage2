#pragma once


//!	§ŒÀŠÔ
/****************************************************************//**
*	§ŒÀŠÔ‚ğºİÄÛ°Ù
*	\nosubgrouping
********************************************************************/
class SeigenJikan
{

/****************************************************************//**
*	\name ×²ÌzŠÂ
********************************************************************/
/*@{*/
public:
	SeigenJikan();
	~SeigenJikan(void);
/*@}*/

/****************************************************************//**
*	\name g‚¤Ò¿¯ÄŞ
********************************************************************/
/*@{*/
	//! ŠÔ‚ğŒo‚½‚¹‚é
	void Process();
/*@}*/

	//½Ã°¼Ş–ˆ‚ÌMAXŠÔ
	void SetMaxJikan(float rSeigenjikan);

	//±¸¾½
	float GetRemainingTime();
	float GetMaxJikan();

	//§ŒÀŠÔ½À°Ä(ON)
	void SeigenJikanOn();
	//§ŒÀŠÔ½Ä¯Ìß(OFF)
	void SeigenJikanOff();

	//§ŒÀŠÔØ¾¯Ä
	void SeigenJikanReset();

	
protected:

	float mTimer;

	//MAXŠÔ
	float mMax;
	//ONÌ×¸Ş
	bool mTimeFl;

	//TIME UP
	float mTimeUpTimer;

};
