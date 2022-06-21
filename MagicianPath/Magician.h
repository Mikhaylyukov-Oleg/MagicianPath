#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Vector2D.h"
#include "Collider.h"
#include <iostream>

#define ATTACK_RECHARGE 0.0f

#define ATTACK_TIME 35.0f
#define JUMP_TIME 15.0f

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
	virtual void AnimationState();
	virtual std::string GetTextureId();
	bool m_IsJumping;
	bool m_IsFalling;
	bool m_IsGrounded;
	bool m_IsRunning;
	bool m_IsAttacking;


	float m_JumpTime;
	float m_JumpForce;
	float m_RunForce;
	float m_Mass;
	float m_AttackRecharge;
	float m_AttackTime;

	Collider* m_Collider;
	Animation* m_Animation;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition;
};

#endif MAGICIAN_H