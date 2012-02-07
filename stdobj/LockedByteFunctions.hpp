

inline char LockedCompareExchange(char* pSource, char nCompare, char nExchange)
	{
	__asm
		{
		mov ECX, [pSource];
		mov AL, nCompare;
		mov AH, nExchange;
		lock cmpxchg byte ptr [ECX], AH;
		};
	}

inline short LockedCompareExchange(short* pSource, short nCompare, short nExchange)
	{
	__asm
		{
		mov ECX, [pSource];
		mov AX, nCompare;
		mov BX, nExchange;
		lock cmpxchg word ptr [ECX], BX;
		};
	}

inline void LockedIncrement(char* pSource)
	{
	__asm
		{
		mov ECX, [pSource];
		lock inc byte ptr [ECX];
		};
	}

inline void LockedDecrement(char* pSource)
	{
	__asm
		{
		mov ECX, [pSource];
		lock dec byte ptr [ECX];
		};
	}

inline void LockedIncrement(short* pSource)
	{
	__asm
		{
		mov ECX, [pSource];
		lock inc word ptr [ECX];
		};
	}

inline void LockedDecrement(short* pSource)
	{
	__asm
		{
		mov ECX, [pSource];
		lock dec word ptr [ECX];
		};
	}

inline void LockedExchange(char* pSource, char nExchange)
	{
	__asm
		{
		mov ECX, [pSource];
		mov AL, nExchange;
		lock xchg byte ptr [ECX], AL;
		mov AH, 0;
		};
	}

inline void LockedExchange(short* pSource, short nExchange)
	{
	__asm
		{
		mov ECX, [pSource];
		mov AX, nExchange;
		lock xchg word ptr [ECX], AX;
		};
	}
