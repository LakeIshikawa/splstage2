#pragma once

/*
	“–‚½‚è”»’è‚Ì´Ø±(}Œ`)‚ÌŠî–{¸×½
*/
class CollisionShape
{
public:
	CollisionShape(void);
	virtual ~CollisionShape(void);

	virtual bool Collide(CollisionShape* rOperand) = 0;

	// “–‚½‚è”»’è‚ÌŒvZ
	//static bool 
};
