#include "../include/emitter.h"
#include "../include/math.h"
#include <math.h>
#include "../include/screen.h"

Emitter::Emitter( Image * image, bool autofade )
{
	this->image = image;
	this->image->AddReference();
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

Emitter::~Emitter()
{
	image->RemoveReference();
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
			particles[ particles.Size() - 1 ]->SetColor( ( uint8 ) RandomRange( ( double ) minr, ( double ) maxr ), ( uint8 ) RandomRange( ( double ) ming, ( double ) maxg ), 
				( uint8 ) RandomRange( ( double ) minb, ( double ) maxb ), 255 );
		}
	}

	// Update particles in scene
	for ( uint32 i = 0; i < particles.Size(); i++ )
	{
		Particle & particle =  *particles[ i ];

		particle.Update( elapsed );
		
		for ( uint32 j = 0; j < affectors.Size(); j++ )
		{
			if ( affectors[ j ]->IsInsideRegion( particle.GetX(), particle.GetY() ) && !affectors[ j ]->IsParticleAffected( particle ) )
			{
				// Affect particle
				affectors[ j ]->AddParticle( &particle );
				particle.SetColor( ( uint8 ) RandomRange( ( double ) affectors[ j ]->GetMinRed(), ( double ) affectors[ j ]->GetMaxRed() ), 
					( uint8 ) RandomRange( ( double ) affectors[ j ]->GetMinGreen(), ( double ) affectors[ j ]->GetMaxGreen() ), 
					( uint8 ) RandomRange( ( double ) affectors[ j ]->GetMinBlue(), ( double ) affectors[ j ]->GetMaxBlue() ), particle.GetAlpha() );
				particle.SetAngVel( RandomRange( affectors[ j ]->GetMinAngVel(), affectors[ j ]->GetMaxAngVel() ) );
			}
		}

		if ( particle.GetLifetime() <= 0 )
		{
			bin.Add( i );
		}
	}

	// Remove death particles
	for ( int32 i = bin.Size() - 1; i >= 0; i-- )
	{
		Particle & particleref = * particles[ bin[ i ] ];

		for ( uint32 j = 0; j < affectors.Size(); j++ )
		{
			affectors[ j ]->TryRemoveParticle( particles[ bin[ i ] ] );
		}
		particles.RemoveAt( bin[ i ] );
		delete &particleref;
	}
}

void Emitter::Render() const
{
	Renderer::Instance().SetBlendMode( blendMode );
	for ( uint32 i = 0; i < particles.Size(); i++ )
	{
		particles[ i ]->Render();
	}
}