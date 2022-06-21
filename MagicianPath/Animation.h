#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>
#include "SDL.h"


class Animation
{
public:
	Animation() {};

	void Update();
	void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip);
	void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed);

private:
	int m_DrawnFrame = 0;
	int m_PreviousFrame;
	int m_SpriteRow;	
	int m_AnimSpeed;
	int m_FrameCount;
	std::string m_TextureID;
};

#endif ANIMATION_H