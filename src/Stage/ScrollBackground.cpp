#include "ScrollBackground.h"
#include "..\\Management\\GameControl.h"

/*
	グラフィック
*/
ScrollBackground::ScrollBackground(string rGraphic)
{
	mGraphic = rGraphic;
	mScpx = 0;
}

/*
	描画
*/
void ScrollBackground::Draw()
{
	//mScpx += mScrSpx;
	//if( mScpx >= SP->SCRSZX ) { mScpx = 0; }
	DX_DRAW( mGraphic, 0, 0, mScpx, 0, SP->SCRSZX, SP->SCRSZY );
	DX_DRAW( mGraphic, SP->SCRSZX - mScpx, 0, 0, 0, mScpx, SP->SCRSZY );
}

/*
	スクロール速度
*/
void ScrollBackground::SetScrollP(float rSp)
{
	mScpx= (int)rSp % (int)SP->SCRSZX;
}