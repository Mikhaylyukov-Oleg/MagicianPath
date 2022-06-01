#include "CollisionHandler.h"
#include "Engine.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
    m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().back();
    m_CollisionTilemap = m_CollisionLayer->GetTilemap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool xOverlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool yOverlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (xOverlaps && yOverlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    int tileSize = m_CollisionLayer->GetTileSize();
    int rowCount = m_CollisionLayer->GetRowCount();
    int colCount = m_CollisionLayer->GetColCount();

    if (a.x < 0) return true;
    if (a.x + a.w >= colCount * tileSize) return true;

    if (a.y < 0) return true;
    if (a.y + a.h >= rowCount * tileSize) return true;

    int leftTile = a.x / tileSize;
    int rightTile = (a.x + a.w) / tileSize;

    int topTile = a.y / tileSize;
    int bottomTile = (a.y + a.h) / tileSize;   

    for (int i = leftTile; i <= rightTile; ++i)
    {
        for (int j = topTile; j <= bottomTile; ++j)
        {
            if (m_CollisionTilemap[j][i] > 0) return true;
        }
    }
    return false;
}