#pragma once

// misc cool objects and functions

BOOL MatchTwoChars(LPCTSTR p, WORD cTwoChars)
	{
	__asm
		{
		mov ESI, p
		mov AL, byte ptr [ESI]		;
		add ESI, 1
		mov AH, byte ptr [ESI]		;
		mov BX, cTwoChars		;
;compare:
		cmp AX, BX
		je exit_match			; //yes - al already has matching char so just return
;exit_no_match:
		mov EAX, 0				;// no match - move 0 to a1 for return
		jmp exit_func
exit_match:
		mov EAX, 1				;// match - move 1 to a1 for return
		};
exit_func:;
	}
