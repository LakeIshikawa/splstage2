#pragma once

#include "Movable.h"

/*
	基本クラス

	ユーザーが操作するスポットライトに当たったら
	行動をとる物を象徴します。
*/
class LightResponseAble : public virtual Movable
{
public:
	LightResponseAble(void);
	virtual ~LightResponseAble(void);

	void	RunTask();

	virtual void	ResponseAka() = 0;
	virtual void	ResponseMidori() = 0;
	virtual void	ResponseAo() = 0;
	virtual void	ResponseMushoku() = 0;
	virtual void	NoLight() = 0;

	virtual int		GetAtHtPointX() = 0;
	virtual int		GetAtHtPointY() = 0;

	// インターフェース
	void			SetLightResponse(bool mOnOff);

private:

	bool mListenerOn;
};
