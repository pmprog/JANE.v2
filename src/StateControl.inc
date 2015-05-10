
SetNinjaState		proc	STDCALL, NewState:DWORD
	mov	eax, NewState

	.IF al != CurrentNinja.State

		.IF eax == NINJA_STATE_DROWNING
			push	eax
			call	CalcNinjaAnimOffset
			call	CalcNinjaFrame
			movzx	eax, CurrentNinja.Frame
			add	esi, eax
			movzx	eax, byte ptr [esi]				; eax == frame number
			mov	sinkingFrame, eax
			mov	sinkingFlags, 00h
			pop	eax
		.ELSEIF eax == NINJA_STATE_SINKING
			push	eax
			call	CalcNinjaAnimOffset
			call	CalcNinjaFrame
			movzx	eax, CurrentNinja.Frame
			add	esi, eax
			movzx	eax, byte ptr [esi]				; eax == frame number
			mov	sinkingFrame, eax
			mov	sinkingFlags, 00h
			pop	eax
		.ENDIF

		mov	CurrentNinja.Frame, 00h
		mov	CurrentNinja.State, al

		.IF eax == NINJA_STATE_DEAD
			call	OnDie
		.ELSEIF eax == NINJA_STATE_TRANSITION
			call	OnExitRoom
		.ENDIF
	.ENDIF

	ret
SetNinjaState		endp

CloneState		proc	STDCALL
	mov	esi, offset CurrentNinja
	mov	edi, offset ResetToNinja
	mov	ecx, Ninja_Len
	rep	movsb
	mov	CurrentNinja.Control, 00h
	ret
CloneState		endp