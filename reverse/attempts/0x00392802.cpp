// ?getPortTransform@BuildAssistant@@QAE_NPBUCoord3D@@PBVThingTemplate@@MPAMPAU2@@Z
// partial score=0.97 date=2026-10-13
// ?getPortTransform@BuildAssistant@@QAE_NPBUCoord3D@@PBVThingTemplate@@MPAMPAU2@@Z
// partial score=0.97 date=2026-10-12
// ?getPortTransform@BuildAssistant@@QAE_NPBUCoord3D@@PBVThingTemplate@@MPAMPAU2@@Z @0x00392802 (725B)
// FRAGMENT for Code/GameEngine/Source/Common/System/BuildAssistant.cpp (production TU, /O1 /EHs /MD /arch:SSE).
// Compiles to 730B; first diff +0xA3 (jne disp 27 vs 2c, pure +5 shift). Everything before matches.
// RESIDUE (0x392a8a..): retail does `mov eax,[ecx]` BEFORE the getGroundHeight arg pushes and does NOT
// spill xmm3 (dir.z*10) across the call; ours pushes first, spills xmm1+xmm2+xmm3, then loads eax.
// So retail's compiler sees dir.z dead after the z-sub while ours keeps it live. Tried and FAILED:
// explicit x/y/z *= + -= (same 730B), TerrainLogic* local for the call (same), _ReadWriteBarrier
// before the call (716B, much worse, reorders everything). The sub/mul cluster 392a24..392a84 matches
// exactly incl. dead spills to arg homes; the atan2 tail matches modulo shift (args ARE (dir.y,dir.x)
// Homes [ebp-0xc]/[ebp-8] hold scaled dir.x/dir.y on both paths; scale is fold-invariant in atan2).
// NEXT IDEAS: find what source shape kills z across a virtual call with 2 other live xmm (sibling
// addCoord3D loop keeps z live across isUnderwater and MATCHES - values home-resident there vs
// reg-resident here); try return-value temp for getGroundHeight; try z-sub-first ordering and check
// whether the allocator reorders subs back.
// WB identity: BuildAssistant::getPortTransform (BuildAssistant.cpp:2124). No ZH analogue (BFME2-new
// naval port placement). s_portAngleOffset=PI/2 static in .data like retail 0xdc0854.

// -- class BuildAssistant addition:
// 	Bool getPortTransform(const Coord3D *worldPos, const ThingTemplate *build, Real angle, Real *outAngle, Coord3D *outPos);

// -- TU additions (after addCoord3D):
inline void subCoord3D( Coord3D *diff, const Coord3D *a )
{
	diff->x -= a->x;
	diff->y -= a->y;
	diff->z -= a->z;
}

inline void scaleCoord3D( Coord3D *c, Real scale )
{
	c->x *= scale;
	c->y *= scale;
	c->z *= scale;
}

// -- statics (after s_maxWaterLandSampleRatio):
// static Real s_portAngleOffset = PI / 2;
// double __cdecl Rva000422A0Atan2( float y, float x );

// -- body (append after reset):
Bool BuildAssistant::getPortTransform( const Coord3D *worldPos, const ThingTemplate *build,
																 Real angle, Real *outAngle, Coord3D *outPos )
{
	Region3D terrainExtent;
	TheTerrainLogic->getExtent( &terrainExtent );

	SampleBuildData sampleData;
	TheTerrainLogic->getExtent( &sampleData.mapRegion );
	sampleData.build = build;
	sampleData.requireWaterOrLand = FALSE;
	sampleData.waterSamples = 0.0f;
	sampleData.landSamples = 0.0f;
	sampleData.landSum.x = 0.0f;
	sampleData.landSum.y = 0.0f;
	sampleData.landSum.z = 0.0f;
	sampleData.waterSum.x = 0.0f;
	sampleData.waterSum.y = 0.0f;
	sampleData.waterSum.z = 0.0f;
	sampleData.hiZ = terrainExtent.lo.z;
	sampleData.loZ = terrainExtent.hi.z;
	sampleData.terrainRestricted = FALSE;
	sampleData.playerIndex = -1;
	iterateFootprint( build, angle, worldPos, MAP_XY_FACTOR, checkSampleBuildLocation, &sampleData );

	if( sampleData.terrainRestricted || !(sampleData.landSamples > 0.0f) || !(sampleData.waterSamples > 0.0f) )
		return FALSE;

	{Real inv=1.0f/sampleData.landSamples;
	sampleData.landSum.x=*(const volatile Real*)&sampleData.landSum.x*inv;
	sampleData.landSum.y=*(const volatile Real*)&sampleData.landSum.y*inv;
	sampleData.landSum.z=*(const volatile Real*)&sampleData.landSum.z*inv;
	}
	{Real inv=1.0f/sampleData.waterSamples;
	sampleData.waterSum.x=sampleData.waterSum.x*inv;
	sampleData.waterSum.y=*(const volatile Real*)&sampleData.waterSum.y*inv;
	sampleData.waterSum.z=*(const volatile Real*)&sampleData.waterSum.z*inv;
	}
	Coord3D dir;
	dir.x = sampleData.waterSum.x - sampleData.landSum.x;
	dir.y = sampleData.waterSum.y - sampleData.landSum.y;
	dir.z = sampleData.waterSum.z - sampleData.landSum.z;
	Real dist = dir.length();
	dir.normalize();
	scaleCoord3D( &dir, 5.0f );

	*outPos = sampleData.landSum;
	for( Real t = 0.0f; t < dist; t += 5.0f )
	{
		if( TheTerrainLogic->isUnderwater( outPos->x, outPos->y ) )
		{
			dir.normalize();
			scaleCoord3D( &dir, 10.0f );
			subCoord3D( outPos, &dir );
			outPos->z = TheTerrainLogic->getGroundHeight( outPos->x, outPos->y );
			break;
		}
		addCoord3D( outPos, &dir );
	}

	*outAngle = Rva000422A0Atan2( dir.y, dir.x );
	*outAngle += s_portAngleOffset;
	return TRUE;

}  // end getPortTransform
