#include "../include/map.h"
#include "../include/rectcollision.h"
#include "../include/image.h"
#include "../include/collision.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/string.h"
#include "../lib/rapidxml.hpp"
#include <limits.h>

using namespace rapidxml;

Map::Map( const String &filename, uint16 firstColId )
{
	this->filename = filename;
	this->firstColId = firstColId;
	width = height = tileWidth = tileHeight = 0;
	valid = false;

	// Read XML
    String buffer = String::Read( filename );
	xml_document<> document;
    document.parse< 0 >( ( char* ) buffer.ToCString() );

	// Get data
	xml_node<>* mapNode = document.first_node( "map" );
	width = atoi( mapNode->first_attribute( "width" )->value() );
	height = atoi( mapNode->first_attribute( "height" )->value() );
	tileWidth = atoi( mapNode->first_attribute( "tilewidth" )->value() );
	tileHeight = atoi( mapNode->first_attribute( "tileheight" )->value() );

	xml_node<>* tilesetNode = mapNode->first_node( "tileset" );
	int firstGid = atoi( tilesetNode->first_attribute( "firstgid" )->value() );
	uint16 tilesetTileWidth = atoi( tilesetNode->first_attribute( "tilewidth" )->value() );
	uint16 tilesetTileHeight = atoi( tilesetNode->first_attribute( "tileheight" )->value() );
	int offsetX = 0, offsetY = 0;
	if ( tilesetNode->first_node( "tileoffset" ) )
	{
		offsetX = atoi( tilesetNode->first_node( "tileoffset" )->first_attribute( "x" )->value() );
		offsetY = atoi( tilesetNode->first_node( "tileoffset" )->first_attribute( "y" )->value() );
	}
    imageFile = String( tilesetNode->first_node( "image" )->first_attribute( "source" )->value() ).StripDir();
	int imageWidth = atoi( tilesetNode->first_node( "image" )->first_attribute( "width" )->value() );
	int imageHeight = atoi( tilesetNode->first_node( "image" )->first_attribute( "height" )->value() );

	// Read layer
	xml_node<>* dataNode = mapNode->first_node( "layer" )->first_node( "data" );
	if ( dataNode->first_attribute( "encoding" ) || dataNode->first_attribute( "compression" ) )
		return;
	xml_node<>* tileNode = dataNode->first_node( "tile" );
	while ( tileNode )
	{
        tileIds.Add( atoi(tileNode->first_attribute( "gid" )->value() ) - firstGid );
		tileNode = tileNode->next_sibling( "tile" );
	}

	// Load image
    image = ResourceManager::Instance().LoadImage( filename.ExtractDir() + "/" + imageFile, imageWidth / tilesetTileWidth, imageHeight / tilesetTileHeight );
	image->SetHandle( offsetX, offsetY );

	valid = true;
}

void Map::Render() const
{
	for ( uint32 y = 0; y < GetRows(); y++ )
	{
		for ( uint32 x = 0; x < GetColumns(); x++ )
		{
			if ( GetTileId( x, y ) >= 0 )
			{
				Renderer::Instance().DrawImage( image, x * GetTileWidth(), y * GetTileHeight(), GetTileId( x, y ) );
			}
		}
	}
}

bool Map::CheckCollision( const Collision* collision ) const
{
	// Add collision box
	double boxX = 0, boxY = 0, boxWidth = GetTileWidth(), boxHeight = GetTileHeight();
	RectCollision boxCol( &boxX, &boxY, &boxWidth, &boxHeight );
	
	// Check collisions
	for ( uint16 y = 0; y < GetRows(); y++ )
	{
		for ( uint16 x = 0; x < GetColumns(); x++ )
		{
			if ( GetTileId( x, y ) >= firstColId )
			{
				boxX = x * GetTileWidth();
				boxY = y * GetTileHeight();

				if ( collision->DoesCollide( &boxCol ) )
					return true;
			}
		}
	}

	return false;
}

double Map::GetGroundY( double x, double y ) const
{
	double groundY = UINT_MAX;

	if ( x < 0  ||  x >= width * tileWidth  ||  y >= height * tileHeight )
		return groundY;
	if ( y < 0 )
		y = 0;

	for ( int tiley = int( y / tileHeight ); tiley < height; tiley++ )
	{
		if ( tileIds[ tiley * width + int( x / tileWidth ) ] >= 0 )
		{
			groundY = tiley * tileHeight;
			break;
		}
	}

	return groundY;
}