// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bbc40.md plus retail only.
// No decoder source was consulted.
//
// ZerosBoolTreeToHuffCodes (retail 0x001BBC40, 274 bytes): turns the eight
// zero-run tree probabilities into nine weights, one per run symbol. Each
// weight is the product of branch values from the root downward, shifted
// right by 8 after every multiplication.

// RVA 0x001BBC40
extern "C" void __cdecl ZerosBoolTreeToHuffCodes(unsigned char *probabilities, int *weights)
{
	unsigned int factor = probabilities[0] * probabilities[1];
	factor >>= 8;
	unsigned int result = probabilities[2] * factor;
	result >>= 8;
	weights[0] = result;

	{
		unsigned int inverse = 0xFF - probabilities[2];
		inverse *= factor;
		inverse >>= 8;
		weights[1] = inverse;
	}

	{
		unsigned int inverse = 0xFF - probabilities[1];
		inverse *= probabilities[0];
		inverse >>= 8;
		unsigned int result = probabilities[3] * inverse;
		result >>= 8;
		weights[2] = result;
		result = (0xFF - probabilities[3]) * inverse;
		result >>= 8;
		weights[3] = result;
	}

	{
		unsigned int factor = (0xFF - probabilities[0]) * probabilities[4];
		factor >>= 8;
		factor *= probabilities[5];
		factor >>= 8;
		unsigned int result = probabilities[6] * factor;
		result >>= 8;
		weights[4] = result;
		result = (0xFF - probabilities[6]) * factor;
		result >>= 8;
		weights[5] = result;
	}

	{
		unsigned int factor = (0xFF - probabilities[0]) * probabilities[4];
		factor >>= 8;
		factor *= 0xFF - probabilities[5];
		factor >>= 8;
		unsigned int result = probabilities[7] * factor;
		result >>= 8;
		weights[6] = result;
		result = (0xFF - probabilities[7]) * factor;
		result >>= 8;
		weights[7] = result;
	}

	weights[8] = ((unsigned int)(0xFF - probabilities[0]) *
		(unsigned int)(0xFF - probabilities[4])) >> 8;
}
