#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load()
{
	if (!Parse("level1", "Assets/Maps/map1.tmx")) {
		return false;
	}
	return true;
}

bool MapParser::Parse(std::string id, std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error())
	{
		std::cerr << "Failed to load: " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	int rowCount, colCount, tileSize;
	root->Attribute("width", &colCount);
	root->Attribute("height", &rowCount);
	root->Attribute("tilewidth", &tileSize);

	TilesetList tilesets;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			tilesets.push_back(ParseTileset(e));
		}
	}

	GameMap* gameMap = new GameMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			TileLayer* tileLayer = ParseTileLayer(e, tilesets, tileSize, rowCount, colCount);
			gameMap->m_MapLayers.push_back(tileLayer);
		}
	}

	m_MapDict[id] = gameMap;
	return true;
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
	Tileset tileset;
	tileset.Name = xmlTileset->Attribute("name");
	xmlTileset->Attribute("firstgid", &tileset.FirstID);
	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	tileset.LastID = tileset.FirstID + tileset.TileCount - 1;

	xmlTileset->Attribute("columns", &tileset.ColCount);
	tileset.RowCount = tileset.TileCount / tileset.ColCount;
	xmlTileset->Attribute("tilewidth", &tileset.TileSize);

	TiXmlElement* image = xmlTileset->FirstChildElement();
	tileset.Source = image->Attribute("source");
	return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int colCount)
{
	TiXmlElement* data = nullptr;
	for (TiXmlElement* elem = xmlLayer->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement())
	{
		if (elem->Value() == std::string("data")) {
			data = elem;
			break;
		}
	}

	std::string matrix(data->GetText());
	std::istringstream iss(matrix);
	std::string id;

	TileMap tileMap(rowCount, std::vector<int>(colCount, 0));

	for (int row = 0; row < rowCount; row++)
	{
		for (int col = 0; col < colCount; col++) 
		{
			std::getline(iss, id, ',');
			std::stringstream convertor(id);
			convertor >> tileMap[row][col];

			if (!iss.good())
			{
				break;
			}
		}
	}

	return (new TileLayer(tileSize, rowCount, colCount, tileMap, tilesets));
}

void MapParser::Clean()
{
	std::map<std::string, GameMap*>::iterator it;
	for (it = m_MapDict.begin(); it != m_MapDict.end(); it++)
	{
		it->second = nullptr;
	}
	
	m_MapDict.clear();
}