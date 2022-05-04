#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Input.h"

class Magician : public Character
{
public:
	Magician(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

private:

	Animation* m_Animation;
	RigidBody* m_RigidBody;
};

#endif MAGICIAN_H