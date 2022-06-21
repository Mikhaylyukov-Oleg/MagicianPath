#include "Magician.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "Input.h"

Magician::Magician(Properties* props) : Character(props)
{
	bool m_IsJumping = false;
	bool m_IsFalling = false;
	bool m_IsGrounded = false;
	bool m_IsRunning = false;
	bool m_IsAttacking = false;

	m_Flip = SDL_FLIP_NONE;

	m_JumpTime = JUMP_TIME;
	m_AttackTime = ATTACK_TIME;
	m_AttackRecharge = 0;

	m_JumpForce = JUMP_FORCE;
	m_RunForce = RUN_FORCE;
	m_Mass = UNIT_MASS;

	m_Collider = new Collider();
	m_Collider->SetBuffer(55, 25, -40, 0);

	m_RigidBody = new RigidBody(m_Mass);
	//m_RigidBody->SetGravity(0.5f);

	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 0, 5, 120);
}

void Magician::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);

	//Vector2D cam = Camera::GetInstance()->GetPosition();
	//SDL_Rect square = m_Collider->Get();
	//square.x -= cam.X;
	//square.y -= cam.Y;
	//SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &square);
}

void Magician::Update(float deltaTime)
{
	if (m_AttackRecharge > 0)
	{
		m_AttackRecharge -= deltaTime;

		if (m_AttackRecharge < 0)
			m_AttackRecharge = 0;
	}
	if ((m_AttackTime > 0) && m_IsAttacking)
	{
		m_AttackTime -= deltaTime;
	}		
	else
	{
		m_IsAttacking = false;
		m_AttackTime = ATTACK_TIME;
	}

	m_IsRunning = false;
	m_RigidBody->UnsetForce();

	if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking)
	{
		m_RigidBody->ApplyForceX(m_RunForce * FORWARD);
		m_Flip = SDL_FLIP_NONE;
		m_IsRunning = true;
	}

	if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking)
	{
		m_RigidBody->ApplyForceX(m_RunForce * BACKWARD);
		m_Flip = SDL_FLIP_HORIZONTAL;
		m_IsRunning = true;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_E) && m_IsGrounded && m_AttackRecharge == 0)
	{
		m_RigidBody->UnsetForce();
		m_IsAttacking = true;
		m_AttackRecharge = ATTACK_RECHARGE;
	}
	
	if ((Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) || 
		Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) || 
		Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP)) && m_IsGrounded)
	{
		m_IsJumping = true;
		m_IsGrounded = false;
		m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
	}

	if ((Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) || 
		Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) || 
		Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP)) && m_IsJumping && m_JumpTime > 0)
	{
		m_IsJumping = true;
		m_JumpTime -= deltaTime;
		m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
	}
	else
	{
		m_IsJumping = false;
		m_JumpTime = JUMP_TIME;
	}

	if (!m_IsGrounded)
		m_IsFalling = true;
	else
	{
		m_IsFalling = false;
	}	

	m_RigidBody->Update(deltaTime);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->GetPosition().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 75);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
		m_Transform->X = m_LastSafePosition.X;

	m_RigidBody->Update(deltaTime);
	m_LastSafePosition.Y = m_Transform->Y;	
	m_Transform->Y += m_RigidBody->GetPosition().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 75);
	

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
	{
		m_IsGrounded = true;
		m_Transform->Y = m_LastSafePosition.Y;
	}
	else
	{
		m_IsGrounded = false;
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	AnimationState();
	m_Animation->Update();		
}

void Magician::AnimationState()
{
	std::string textureId = GetTextureId();
	if (textureId == "player_idle")
		m_Animation->SetProps("player_idle", 0, 5, 200);

	if (textureId == "player_run")
		m_Animation->SetProps("player_run", 0, 5, 120);

	if (textureId == "player_fall")
		m_Animation->SetProps("player_fall", 0, 1, 1000);

	if (textureId == "player_jump")
		m_Animation->SetProps("player_jump", 0, 2, 150);	

	if (textureId == "player_attack")
		m_Animation->SetProps("player_attack", 0, 5, 100);	
}

std::string Magician::GetTextureId()
{
	std::string textureId = "player_idle";

	if (m_IsRunning)
		textureId = "player_run";

	if (m_IsFalling)
		textureId = "player_fall";

	if (m_IsJumping)
		textureId = "player_jump";

	if (m_IsAttacking)
		textureId = "player_attack";

	return textureId;
}

void Magician::Clean()
{
	TextureManager::GetInstance()->Drop(m_TextureID);
}