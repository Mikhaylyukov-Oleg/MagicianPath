#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Input.h"
#include "Collider.h"
#include "Vector2D.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f

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

	Collider* m_Collider;

	Animation* m_Animation;
	RigidBody* m_RigidBody;

	Vector2D m_LastSafePosition;
};

#endif MAGICIAN_H