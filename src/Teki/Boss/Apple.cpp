#include "Apple.h"
#include "..\\..\\Management\\GameControl.h"

Map::HITPOINT Apple::sMapPointX =
{
	{ 20, -1 },	//��
	{ -1 },		//��
	{ -1 },		//�O
	{ -1 }		//��
};

Map::HITPOINT Apple::sMapPointY =
{ 
	{ 36, -1 },	//��
	{ -1 },		//��
	{ -1 },		//�O
	{ -1 }		//��
};


Apple::Apple(int rXPx, int rYPx)
{

	APPLESZX = GI("APPLESZX");
	APPLESZY = GI("APPLESZY");

	APPLE_BRTM = GF("APPLE_BRTM");

	mSizeX = APPLESZX;
	mSizeY = APPLESZY;

	mX = rXPx;
	mY = rYPx;
	mZ = 1.0f;

	mNo = 0;
	mTimer = 0.0f;
	mBaseStatus = NORMAL;

	// �����蔻��
	AddFrame(FR_NORMAL);
	AddCircle(FR_NORMAL, SP->GRID_BOGYO, 20, 20, 15);

	AddFrame(FR_DISABLE);

	SetCurFrame(FR_DISABLE);

}

Apple::~Apple()
{}

/*
	���C������
*/
void Apple::Move()
{
	switch( mBaseStatus ) {
		case NORMAL:

		// ���Ƃ̓����蔻��
		DetSpAccPos();
		MapAtHt();
		Draw();
		DieIfGamenGai();
		break;

		case BROKE:
			mTimer += SP->FrameTime;
			if( mTimer >= APPLE_BRTM && mAtari[0] == SP->CHIP_AMHIT){
				GAMECONTROL->GetMobManager()->Remove(this);
			}
			DetSpAccPos();
			MapAtHt();
			Draw();
			break;
	}
}

int Apple::GetSizeX()
{
	return APPLESZX;
}

/*
	�d�͂����ė��Ƃ�
*/
void Apple::Fall()
{
	mAccY = SP->GRAVITY;
}

/*
	��񂲂��n�ʂɗ����Ă邩�ǂ������擾
*/
bool Apple::IsHittingGround()
{
	return ( mAtari[0] == SP->CHIP_HIT || mAtari[0] == SP->CHIP_AMHIT );
}

/*
	�}�b�v�Ƃ̓����蔻��
*/
void Apple::MapAtHt()
{
	MAP_SUPERATHT(mX, mY, mMuki, mSpX, mSpY, mAccX, mAccY, 
		sMapPointX, sMapPointY, APPLESZX, APPLESZY, mAtari, mMapKabe);

	if( IsHittingGround() )
	{
		mAccY = 0;
		mSpY = 0;
		mY = mMapKabe[0] - sMapPointY[0][0];
	}

}

/*
	�ʒu�A���x�Ɖ������Čv�Z����
*/
void Apple::DetSpAccPos()
{
	mSpX += mAccX;
	mSpY += mAccY;
	mX += mSpX;
	mY += mSpY;
}

/*
	�`��
*/
void Apple::Draw()
{
	DX_DRAW("graphics\\teki\\apple.png", mX, mY, mNo*APPLESZX, 0, (APPLESZX)*(mNo+1), APPLESZY);
}

/*
	���@�Ƃ̓����蔻��
*/
void Apple::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	if( mBaseStatus == BROKE ) return;

	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	if( jiki && rOpGroupId == SP->GRID_BOGYO ){
		jiki->InflictDamage();
		mNo = 1;
		mBaseStatus = BROKE;
	}
	else if ( jiki && rOpGroupId == SP->GRID_KOUGEKI ){
		mNo = 1;
		mBaseStatus = BROKE;
		// SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kougekimeityuu.wav");
	}
}

/*
	�����蔻��𖳌���
*/
void Apple::DisableCollision()
{
	SetCurFrame(FR_DISABLE);
}

/*
	�����蔻���L����
*/
void Apple::EnableCollision()
{
	SetCurFrame(FR_NORMAL);
}