

inline char LockedByteCompareExchange(char* pSource, char nCompare, char nExchange)
	{
	__asm
		{
		mov ECX, [pSource];
		mov AL, nCompare;
		mov AH, nExchange;
		lock cmpxchg byte ptr [ECX], AH;
		};
	}
