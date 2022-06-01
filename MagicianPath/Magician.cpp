#include "Magician.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "Input.h"

Magician::Magician(Properties* props) : Character(props)
{
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;
	m_RunForce = RUN_FORCE;
	m_Mass = UNIT_MASS;

	m_Collider = new Collider();
	m_Collider->SetBuffer(0, 0, 7, 15);

	m_RigidBody = new RigidBody(m_Mass);
	//m_RigidBody->SetGravity(0.5f);

	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 0, 5, 120);
}

void Magician::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect square = m_Collider->Get();
	square.x -= cam.X;
	square.y -= cam.Y;
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &square);
}

void Magician::Update(float deltaTime)
{
	
	m_Animation->SetProps("player_idle", 0, 5, 120, m_Flip);
	m_RigidBody->UnsetForce();

	if ((Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LEFT)) &&
		(!(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT))))
	{
		m_RigidBody->ApplyForceX(m_RunForce * BACKWARD);
		m_Animation->SetProps("player_run", 0, 5, 120, SDL_FLIP_HORIZONTAL);
		m_Flip = SDL_FLIP_HORIZONTAL;
	}
	
	if ((Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT)) &&
		(!(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LEFT))))
	{
		m_RigidBody->ApplyForceX(m_RunForce * FORWARD);
		m_Animation->SetProps("player_run", 0, 5, 120);
		m_Flip = SDL_FLIP_NONE;
	}
	
	if ((Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) && m_IsGrounded)
	{
		m_IsJumping = true;
		m_IsGrounded = false;
		m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
	}

	if ((Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) && m_IsJumping && m_JumpTime > 0)
	{
		m_JumpTime -= deltaTime;
		m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
	}
	else
	{
		m_IsJumping = false;
		m_JumpTime = JUMP_TIME;
	}

	m_RigidBody->Update(deltaTime);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->GetPosition().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
	m_Transform->X = m_LastSafePosition.X;

	m_RigidBody->Update(deltaTime);
	m_LastSafePosition.Y = m_Transform->Y;	
	m_Transform->Y += m_RigidBody->GetPosition().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);
	

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
	m_Animation->Update();	
}

void Magician::Clean()
{
	TextureManager::GetInstance()->Clean();
	//TextureManager::GetInstance()->Drop(m_TextureID);
}

