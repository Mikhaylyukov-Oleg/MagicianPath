#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Vector2D.h"
#include "Collider.h"

#define JUMP_TIME 12.0f
#define JUMP_FORCE 25.0f
#define RUN_FORCE 12.0f
#define UNIT_MASS 3.0f

class Magician : public Character
{
public:
	Magician(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

private:
	bool m_IsJumping;
	bool m_IsGrounded;

	float m_JumpTime;
	float m_JumpForce;
	float m_RunForce;
	float m_Mass;

	Collider* m_Collider;
	Animation* m_Animation;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition;
};

#endif MAGICIAN_H