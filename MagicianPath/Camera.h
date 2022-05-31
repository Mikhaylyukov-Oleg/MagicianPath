#ifndef CAMERA_H
#define CAMERA_H

#include "SDL.h"
#include "Point.h"
#include "Vector2D.h"
#include "Engine.h"

class Camera
{
public:
	void Update();
	inline static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }
	inline SDL_Rect GetCameraView() { return m_CameraView; }
	inline Vector2D GetPosition() { return m_Position; }
	inline void SetTarget(Point* target) { m_Target = target; }

private:
	Camera() { m_CameraView = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; }
	
	SDL_Rect m_CameraView;
	Vector2D m_Position;
	Point* m_Target;
	static Camera* s_Instance;
};

#endif CAMERA_H