#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include <string>
#include <vector>
#include "TextureManager.h"

struct Tileset
{
	int FirstID, LastID;
	int RowCount, ColCount;
	int TileCount, TileSize;
	std::string Name, Source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer : public Layer
{
public:
	TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TilesetList tilesets);
	virtual void Render();
	virtual void Update();
	inline TileMap GetTilemap() { return m_TileMap; };	
	inline int GetTileSize() { return m_TileSize; };
	inline int GetRowCount() { return m_RowCount; };
	inline int GetColCount() { return m_ColCount; };

private:
	int m_TileSize;
	int m_RowCount, m_ColCount;
	TileMap m_TileMap;
	TilesetList m_Tilesets;
};

#endif TILELAYER_H

