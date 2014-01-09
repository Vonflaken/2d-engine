#include "../include/isometricscene.h"

IsometricScene::IsometricScene( IsometricMap* map, Image* imageBack, Image* imageFront ) : MapScene( ( Map* ) map, imageBack, imageFront )
{
	map->GenerateLayerSprites( const_cast< IsometricScene* >( this ) );
}

IsometricSprite* IsometricScene::CreateSprite( Image* image, Layer layer )
{
	IsometricSprite* sprite = new IsometricSprite( image );
	AddSprite( sprite, layer );

	return sprite;
}

void IsometricScene::Update( double elapsed, Map* map )
{
	Scene::Update( elapsed, map );

	for ( int i = 0; i < LAYER_COUNT; i++ )
	{
		Array< Sprite* > sprites = GetSprites( ( Layer ) i );
		sprites.Sort( CompareSprites );
	}
}