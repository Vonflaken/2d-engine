#include "../include/isometricmap.h"
#include "../include/isometricscene.h"
#include "../include/image.h"
#include "../include/sprite.h"
#include "../include/resourcemanager.h"
#include "../lib/rapidxml.hpp"
#include <limits.h>

using namespace rapidxml;

IsometricMap::IsometricMap( const String& filename, uint16 firstColId ) : Map( filename, firstColId )
{
	// Read XML
    String buffer = String::Read( filename );
	xml_document<> document;
    document.parse< 0 >( ( char* ) buffer.ToCString() );

	xml_node<>* mapNode = document.first_node( "map" );
	xml_node<>* tilesetNode = mapNode->first_node( "tileset" );
	int firstGid = atoi( tilesetNode->first_attribute( "firstgid" )->value() );

	// Read second layer
	xml_node<>* dataNode = mapNode->first_node( "layer" )->next_sibling()->first_node( "data" );
	if ( dataNode->first_attribute( "encoding" ) || dataNode->first_attribute( "compression" ) )
		return;
	xml_node<>* tileNode = dataNode->first_node( "tile" );
	while ( tileNode )
	{
		topLayerIds.Add( atoi(tileNode->first_attribute( "gid" )->value() ) - firstGid );
 		tileNode = tileNode->next_sibling( "tile" );
	}

	Image* image = GetImage();
	image->SetHandle( image->GetHandleX() + GetTileWidth(), image->GetHeight() - image->GetHandleY() - GetTileHeight() );
}

void IsometricMap::GenerateLayerSprites( IsometricScene* scene )
{
	double screenX = 0.0;
	double screenY = 0.0;
	int32 tileId = -1;

	for ( int y = 0; y < GetRows(); y++ )
	{
		for ( int x = 0; x < GetColumns(); x++ )
		{
			tileId = GetLayerId( x, y );
			if ( tileId >= 0 )
			{
				IsometricSprite* sprite = scene->CreateSprite( ResourceManager::Instance().LoadImage( GetImage()->GetFilename() ) );
				sprite->SetCurrentFrame( tileId );
				if ( GetFirstColId() == tileId + 1 )
					sprite->SetCollision( Sprite::COLLISION_RECT );
				TransformIsoCoords( y , x , 0.0, &screenX, &screenY );
				sprite->SetPosition( screenX * GetTileWidth(), screenY * GetTileHeight() );
			}
		}
	}
}

void IsometricMap::Render() const
{
	double screenX = 0.0;
	double screenY = 0.0;
	int32 tileId = -1;

	for ( uint32 y = 0; y < GetRows(); y++ )
	{
		for ( uint32 x = 0; x < GetColumns(); x++ )
		{
			// Render ground sprites
			tileId = GetTileId( x, y );
			if ( tileId >= 0 )
			{
				TransformIsoCoords( y, x, 0.0, &screenX, &screenY );
				Renderer::Instance().DrawImage( GetImage(), screenX * GetTileWidth(), screenY * GetTileHeight(), tileId );
			}
		}
	}
}