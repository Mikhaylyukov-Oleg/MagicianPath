#include "Magician.h"
#include "TextureManager.h"
#include "SDL.h"

Magician::Magician(Properties* props) : Character(props)
{
	m_RigidBody = new RigidBody();
	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 0, 5, 120);
}

void Magician::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Magician::Update(float deltaTime)
{
	
	m_Animation->SetProps("player_idle", 0, 5, 120, m_Flip);
	m_RigidBody->UnsetForce();

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
	{
		m_RigidBody->ApplyForceX(10 * BACKWARD);
		m_Animation->SetProps("player_run", 0, 5, 120, SDL_FLIP_HORIZONTAL);
		m_Flip = SDL_FLIP_HORIZONTAL;
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
	{
		m_RigidBody->ApplyForceX(10 * FORWARD);
		m_Animation->SetProps("player_run", 0, 5, 120);
		m_Flip = SDL_FLIP_NONE;
	}

	m_RigidBody->Update(deltaTime);	
	m_Transform->TranslateX(m_RigidBody->GetPosition().X);
	
	m_Animation->Update();	
}

void Magician::Clean()
{
	TextureManager::GetInstance()->Clean();
}

