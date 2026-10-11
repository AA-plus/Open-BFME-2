// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c5b00.md plus retail only.
// No decoder source was consulted.
//
// VP6_decodeMotionVector (retail 0x001C5B00, 539 bytes): decodes one motion
// vector (x then y, signed 16-bit) with the primary bool coder, using the
// nearest inter or golden vector as prediction for the coding mode. The long
// branch loads the next probability before combining the previous decoded
// bit; the Y output accumulates in its short destination.

extern "C" int __cdecl VP6_DecodeBool(void *coder, int prob);

extern "C" void __cdecl VP6_decodeMotionVector(void *ctxRaw, short *outMv, int mode)
{
	unsigned char *ctx = (unsigned char *)ctxRaw;
	int predX = 0;
	int predY = 0;

	if (mode == 2)
	{
		if (*(int *)(ctx + 0x44) < 2)
		{
			predX = *(short *)(ctx + 0x3c);
			predY = *(short *)(ctx + 0x3e);
		}
	}
	else
	{
		if (*(int *)(ctx + 0x50) < 2)
		{
			predX = *(short *)(ctx + 0x48);
			predY = *(short *)(ctx + 0x4a);
		}
	}

	void *coder = ctx + 0x150;

	for (unsigned int comp = 0; comp < 2; ++comp)
	{
		int delta;

		if (!VP6_DecodeBool(coder, ctx[0x706 + comp]))
		{
			if (VP6_DecodeBool(coder, ctx[comp * 7 + 0x708]))
			{
				unsigned char *base = ctx + comp * 7;
				if (VP6_DecodeBool(coder, base[0x70c]))
				{
					delta = VP6_DecodeBool(coder,
						ctx[(comp + 0x102) * 7]) + 6;
				}
				else
				{
					delta = VP6_DecodeBool(coder, base[0x70d]) + 4;
				}
			}
			else
			{
				if (VP6_DecodeBool(coder, (ctx + comp * 7)[0x709]))
				{
					delta = VP6_DecodeBool(coder,
						(ctx + comp * 7)[0x70b]) + 2;
				}
				else
				{
					delta = VP6_DecodeBool(coder, (ctx + comp * 7)[0x70a]);
				}
			}
		}
		else
		{
			delta = VP6_DecodeBool(coder, ctx[comp * 8 + 0x71c]);
			delta += VP6_DecodeBool(coder, ctx[comp * 8 + 0x71d]) * 2;
			unsigned char prob2 = ctx[comp * 8 + 0x71e];
			delta += VP6_DecodeBool(coder, prob2) * 4;
			delta += VP6_DecodeBool(coder, ctx[comp * 8 + 0x723]) << 7;
			delta += VP6_DecodeBool(coder, ctx[comp * 8 + 0x722]) << 6;
			delta += VP6_DecodeBool(coder, ctx[comp * 8 + 0x721]) << 5;
			delta += VP6_DecodeBool(coder, ctx[comp * 8 + 0x720]) << 4;
			if (delta & 0xf0)
			{
				delta += VP6_DecodeBool(coder, ctx[comp * 8 + 0x71f]) << 3;
			}
			else
			{
				delta += 8;
			}
		}

		if (delta && VP6_DecodeBool(coder, ctx[0x704 + comp]))
		{
			delta = -delta;
		}

		if (comp)
		{
			outMv[1] = (short)predY;
			outMv[1] += (short)delta;
		}
		else
		{
			outMv[0] = (short)(delta + predX);
		}
	}
}
