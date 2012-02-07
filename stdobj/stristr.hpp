//------------------------------------------------------------------------------
// Renamer - by Rich Schonthal
// This software is free to use and modify as long as you:
//     a) keep this header in tact
//     b) don't charge for this software
// Copyright (c) 2005 Rich Schonthal
//------------------------------------------------------------------------------

char* stristr(const char* pTarget, const char* pSpec)
	{
	char* pFirst;
	bool bLastMatched;
	__asm
		{
		mov dword ptr [pFirst],0			;//init variables
		mov ESI, pTarget					;
		sub ESI, 1							;//decrement target pointer cuz the loop inc's it at the top
start_at_spec_begining:
		mov byte ptr [bLastMatched], 0		;
		mov EDI, pSpec						;//start from the begining of spec
check_strings_ended:
		add ESI, 1							;//advance target
		cmp byte ptr [ESI], 0				;//end of string?
		je end_stristr						;
		cmp byte ptr [EDI], 0				;//end of string?
		je end_stristr						;
		mov AL, byte ptr [EDI]				;//get a char from spec
		and AL, 0x7f						;//make it lowercase
		mov BL, byte ptr [ESI]				;//get a char from target
		and BL, 0x7f						;//make it lowercase
		cmp AL, BL							;//compare the 2
		jne start_at_spec_begining			;
		cmp byte ptr [bLastMatched], 0		;//is bLastMatched false?
		je set_first_matched_char			;
set_matched_and_loop:
		mov byte ptr [bLastMatched], 1		;//set lastmatch
		add EDI, 1							;//advance the specstring
		jmp check_strings_ended				;
set_first_matched_char:
		mov pFirst, ESI						;//save the first matching char from target
		jmp set_matched_and_loop			;
end_stristr:;
		cmp byte ptr [EDI], 0				;//see if we reached the end of the target
		jne end_stristr_no_match			;//if so then there was no match
		cmp byte ptr [bLastMatched], 0		;//if lastmatch is false
		je end_stristr_no_match				;//then there was no match
		mov EAX, pFirst						;//there was a match so return the ptr to the 1st matching char
		jmp end_stristr_final				;
end_stristr_no_match:
		mov EAX, 0							;//no match so return null
end_stristr_final:
		};
	}


/* the original
char* stristr(const char* p2, const char* p1)
	{
	const char* pFirst = NULL;
	const char* pBase = p1;

	bool bLastMatched = false;

	while(*p1 && *p2)
		{
		if(tolower(*p1) == tolower(*p2))
			{
			if(! bLastMatched)
				pFirst = p2;
			p1++;
			bLastMatched = true;
			}
		else
			{
			bLastMatched = false;
			p1 = pBase;
			}

		p2++;
		}

	if(*p1 != 0 || ! bLastMatched)
		return NULL;

	return (char*) pFirst;
	}
*/