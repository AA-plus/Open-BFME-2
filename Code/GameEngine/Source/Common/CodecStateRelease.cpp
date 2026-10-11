struct CodecState
{
	unsigned char m_unmodelled00[ 0x13c ];
	void *m_buffer;
	unsigned char m_unmodelled140[ 0x158 ];
	void *m_callback;
};

void releaseCodecMembers( CodecState *state );
void releaseCodecBuffer( void **buffer );
extern "C" void __cdecl DeletePostProcInstance( void **callback );
// The BFME1 donor's local extern freeCodecMemory resolves to the rowed helper.
void bfmeFreeOneJT( void *what );

// ?releaseCodecState@@YAXPAPAUCodecState@@@Z
void releaseCodecState( CodecState **state )
{
	if( *state )
	{
		releaseCodecMembers( *state );
		releaseCodecBuffer( &(*state)->m_buffer );
		DeletePostProcInstance( &(*state)->m_callback );
	}
	bfmeFreeOneJT( *state );
	*state = 0;
}
