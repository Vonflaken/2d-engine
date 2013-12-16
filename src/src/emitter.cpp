#include "../include/emitter.h"
#include "../include/math.h"
#include <math.h>

Emitter::Emitter( Image * image, bool autofade )
{
	this->image = image;
	this->autofade = autofade;
	blendMode = Renderer::ADDITIVE;
	x = y = 0.00;
	minrate = 5;
	maxrate = 15;
	minvelx = maxvelx = 0;
	minvely = maxvely = 0;
	minangvel = maxangvel = 0;
	minlifetime = 1;
	maxlifetime = 5;
	minr = ming = minb = 0;
	maxr = maxg = maxb = 255;
	emitting = false;
	particles = 0;
}

void Emitter::Update( double elapsed )
{
	Array< uint32 > bin;

	if ( emitting )
	{
		// Generate new particles
		uint32 numParticlesToGen = ( uint32 ) ( RandomRange( minrate, maxrate ) * elapsed );
		for ( uint32 i = 0; i <= numParticlesToGen; i++ )
		{
			particles.Add(  new Particle( image, RandomRange( minvelx, maxvelx ), RandomRange( minvely, maxvely ), RandomRange( minangvel, maxangvel ), RandomRange( minlifetime, maxlifetime ), autofade ) );
			particles[ particles.Size() - 1 ]->SetBlendMode( blendMode );
			particles[ particles.Size() - 1 ]->SetPosition( x, y );
			particles[ particles.Size() - 1 ]->SetColor( ( uint8 ) RandomRange( minr, maxr ), ( uint8 ) RandomRange( ming, maxg ), ( uint8 ) RandomRange( minb, minb ) );
		}
	}

	// Update particles in scene
	for ( uint32 i = 0; i < particles.Size(); i++ )
	{
		particles[ i ]->Update( elapsed );
		
		if ( particles[ i ]->GetLifetime() <= 0 )
		{
			bin.Add( i );
		}
	}

	// Remove death particles
	for ( uint32 i = 0; i < bin.Size(); i++ )
	{
		particles.RemoveAt( bin[ i ] );
	}
}

void Emitter::Render() const
{
	for ( uint32 i = 0; i < particles.Size(); i++ )
	{
		particles[ i ]->Render();
	}
}