#include "ParticleEmitter.h"
#include "..\\Management\\GameControl.h"
#include <d3dx9.h>

inline DWORD FLOAT_TO_WORD( FLOAT f ) { return *((DWORD*)&f); }

/**
	�W���R���X�g���N�^
*/
ParticleEmitter::ParticleEmitter(int rX, int rY, int rNumParticles, string rTexture)
{
	mX = rX;
	mY = rY;
	
	mNumParticles = rNumParticles;

	// ø���
	mTexture = GAMECONTROL->GetDXController()->GetTextureOf( rTexture );

	// ���_�ޯ̧�
	CreateVertexBuffer(mNumParticles * sizeof(CUSTOMVERTEX),
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS, 
		D3DFVF_CUSTOMVERTEX );

	mStatus = STOP;

}

/**
	�W���f�X�g���N�^
*/
ParticleEmitter::~ParticleEmitter()
{}

/************************************************************//**
*	�`��
****************************************************************/
void ParticleEmitter::Render()
{
	// ���޲����擾
	LPDIRECT3DDEVICE9 device = GAMECONTROL->GetDXController()->GetDevice();

	// 3D��Ԃ̐ݒ�
	D3DXMATRIX matView, matWorld, oldView, oldWorld;
	D3DXMATRIX matProj, oldProj;
	
    D3DXMatrixPerspectiveLH( &matProj, 800, 600, 1.0f, 0.0f );

	D3DXVECTOR3 vEyePt( 0.0f, 0.0f,1.0f );
	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec( 0.0f, -1.0f, 0.0f );
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );

	D3DXMatrixTranslation( &matWorld, 
		-SP->SCRSZX/2 -GAMECONTROL->GetStageManager()->GetCurScrollPointer(), 
		-SP->SCRSZY/2, 0.0f );

	device->GetTransform( D3DTS_PROJECTION, &oldProj );
	device->GetTransform( D3DTS_WORLD, &oldWorld );
	device->GetTransform( D3DTS_VIEW, &oldView );

    device->SetTransform( D3DTS_PROJECTION, &matProj );
	device->SetTransform( D3DTS_WORLD, &matWorld );
	device->SetTransform( D3DTS_VIEW, &matView );
    device->SetRenderState( D3DRS_LIGHTING,  FALSE );

	// �ݒ�
	device->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
    device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
    device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
	device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);

	device->SetRenderState( D3DRS_POINTSPRITEENABLE, TRUE );
	device->SetRenderState( D3DRS_POINTSCALEENABLE, FALSE );

	device->SetRenderState( D3DRS_POINTSIZE, FLOAT_TO_WORD(32.0f) );
	//device->SetRenderState( D3DRS_POINTSIZE_MIN, FLOAT_TO_WORD(64.0f) );

	//device->SetRenderState( D3DRS_POINTSCALE_A, FLOAT_TO_WORD(0.0f) );
	//device->SetRenderState( D3DRS_POINTSCALE_B, FLOAT_TO_WORD(1.0f) );
	//device->SetRenderState( D3DRS_POINTSCALE_C, FLOAT_TO_WORD(0.0f) );

	// ���_�ޯ̧��ɒ��_����������
	CUSTOMVERTEX* point_vertices;

	mVertexBuffer->Lock(0, mNumParticles * sizeof(CUSTOMVERTEX),
		(void**)&point_vertices, D3DLOCK_DISCARD);

	for(int i=0; i<mNumParticles; i++)
	{
		if( GetParticle(i)->IsAlive() ){
			point_vertices->position = *(GetParticle(i)->GetPos());
			point_vertices->color = *(GetParticle(i)->GetColor());
		}
		else { // ����
			point_vertices->position = D3DXVECTOR3(-1000, -1000, 0);
		}
		point_vertices++;
	}

	mVertexBuffer->Unlock();

	// ø�����ݒ�
	device->SetTexture( 0, mTexture );
	// ��ذѿ����ݒ�
	device->SetStreamSource( 0, mVertexBuffer, 0, sizeof(CUSTOMVERTEX) );
	// fvf
	device->SetFVF( D3DFVF_CUSTOMVERTEX );
	device->DrawPrimitive( D3DPT_POINTLIST, 0, mNumParticles );

	device->SetRenderState( D3DRS_POINTSPRITEENABLE, FALSE );
    device->SetRenderState( D3DRS_POINTSCALEENABLE,  FALSE );

    device->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
    device->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );

	device->SetTransform( D3DTS_PROJECTION, &oldProj );
	device->SetTransform( D3DTS_WORLD, &oldWorld );
	device->SetTransform( D3DTS_VIEW, &oldView );
}

/************************************************************//**
*	���_�ޯ̧����쐬
****************************************************************/
void ParticleEmitter::CreateVertexBuffer(int rSize, DWORD usage, 
										 DWORD fvf)
{
	GAMECONTROL->GetDXController()->GetDevice()->CreateVertexBuffer(
		rSize, usage, fvf, D3DPOOL_DEFAULT, &mVertexBuffer, NULL);
}
