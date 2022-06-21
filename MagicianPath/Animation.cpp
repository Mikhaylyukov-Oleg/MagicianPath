#include "Animation.h"
#include "TextureManager.h"

void Animation::Update()
{
	//?
	int CurrentFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
	bool frameChanged = (m_PreviousFrame != CurrentFrame);
	if (frameChanged) 
	{
		m_PreviousFrame = CurrentFrame;
		m_DrawnFrame = (m_DrawnFrame + 1) % m_FrameCount;
	}
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
	TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_DrawnFrame, flip);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed)
{
	if (m_TextureID != textureID)
	{
		m_DrawnFrame = 0;
		m_PreviousFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
	}	
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frameCount;
	m_AnimSpeed = animSpeed;	
}