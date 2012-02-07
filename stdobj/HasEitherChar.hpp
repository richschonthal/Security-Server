#pragma once

// misc cool objects and functions

BOOL _fastcall HasEitherChar(LPCTSTR p, char c1, char c2)
	{
	__asm
		{
		mov ESI, p				;
		mov AL, c1				;
		mov AH, c2				;
compare:
		cmp AL, byte ptr [ESI]	; // is it c1?
		je exit_func			; //yes - al already has matching char so just return
		cmp AH, byte ptr [ESI]	; // is it c2?
		je exit_match_c2		; //yes
		add ESI, 1				; //inc string pointer
		cmp byte ptr [ESI], 0	; // get out if end of string
		je exit_no_match		;
		jmp compare				;
exit_match_c2:
		mov AL, c2				;// move the matching char to a1 for return
		jmp exit_func			;
exit_no_match:
		mov EAX, 0				;// no match - move 0 to a1 for return
		jmp exit_func
		};
exit_func:;
	}

inline BOOL IsEitherChar(char cCheck, char c1, char c2)
	{
	__asm
		{
		mov AL, c1					;
		cmp AL, cCheck				;
		je is_either_char_ret_true	;
		mov AL, c2					;
		cmp AL, cCheck				;
		je is_either_char_ret_true	;
		mov EAX, 0					;
		jmp is_either_char_done		;
is_either_char_ret_true:
		mov EAX, 1					;
is_either_char_done:
		};
	}
