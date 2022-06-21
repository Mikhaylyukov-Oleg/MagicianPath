#include "Camera.h"

Camera* Camera::s_Instance = nullptr;

void Camera::Update()
{
	if (m_Target != nullptr)
	{
		m_CameraView.x = m_Target->X - SCREEN_WIDTH / 2;
		m_CameraView.y = m_Target->Y - SCREEN_HEIGHT / 2 + 60;

		if (m_CameraView.x < 0)
		{
			m_CameraView.x = 0;
		}

		if (m_CameraView.y < 0)
		{
			m_CameraView.y = 0;
		}

		TileLayer* tileMap = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().front();
		int tileSize = tileMap->GetTileSize();
		int rowCount = tileMap->GetRowCount();
		int colCount = tileMap->GetColCount();

		if (m_CameraView.x > (tileSize * colCount - SCREEN_WIDTH))
		{
			m_CameraView.x = tileSize * colCount - SCREEN_WIDTH;
		}

		if (m_CameraView.y > (tileSize * rowCount - SCREEN_HEIGHT))
		{
			m_CameraView.y = (tileSize * rowCount - SCREEN_HEIGHT);
		}

		m_Position = Vector2D(m_CameraView.x, m_CameraView.y);
	}
}
