	.code

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; On Load
OnLoad	proc	STDCALL
	call	LoadResources
	ret
OnLoad	endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; On Exit
OnExit	proc	STDCALL
	ret
OnExit	endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; On KeyDown
KeyDown	proc	STDCALL, key:DWORD
	mov	eax, key
	.IF eax == NINJA_KEY_UP					; Up
		mov	al, CurrentNinja.Control
		mov	bl, NINJA_CONTROL_UP
		or	al, bl
		mov	CurrentNinja.Control, al

	.ELSEIF eax == NINJA_KEY_DOWN				; Down
		mov	al, CurrentNinja.Control
		mov	bl, NINJA_CONTROL_DOWN
		or	al, bl
		mov	CurrentNinja.Control, al

	.ELSEIF eax == NINJA_KEY_LEFT				; Left
		mov	al, CurrentNinja.Control
		mov	bl, NINJA_CONTROL_LEFT
		or	al, bl
		mov	CurrentNinja.Control, al

	.ELSEIF eax == NINJA_KEY_RIGHT				; Right
		mov	al, CurrentNinja.Control
		mov	bl, NINJA_CONTROL_RIGHT
		or	al, bl
		mov	CurrentNinja.Control, al

	.ELSEIF eax == NINJA_KEY_FIRE
		mov	al, CurrentNinja.Control
		mov	bl, NINJA_CONTROL_FIRE
		or	al, bl
		mov	CurrentNinja.Control, al

	.ELSEIF eax == NINJA_KEY_SWITCH
		push	NINJA_STATE_SWITCHING
		call	SetNinjaState

	.ELSEIF eax == NINJA_KEY_HELP				; F1 - Help/About
		push	0
		push	offset engineCLS
		push	offset versionTag
		push	0
		call	MessageBox
	.ENDIF

	.IF debugMode != 0						;;;; Debug keys
		.IF eax == NINJA_KEY_DEBUG_DROWN
			push	NINJA_STATE_DROWNING
			call	SetNinjaState
		.ELSEIF eax == NINJA_KEY_DEBUG_HURT
			push	10h
			call	OnTakeDamage
		.ELSEIF eax == NINJA_KEY_DEBUG_GARGOYLE
			mov	al, 01h
			sub	al, debugGargoyle
			mov	debugGargoyle, al
		.ELSEIF eax == NINJA_KEY_DEBUG_LOGIC
			call	LogicActivate
		.ENDIF
	.ENDIF

	.IF CurrentNinja.State == NINJA_STATE_TRANSITION
		mov	CurrentNinja.Control, 0h
	.ENDIF

	ret
KeyDown	endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; On KeyUp
KeyUp	proc	STDCALL, key:DWORD
	mov	eax, key
	.IF eax == NINJA_KEY_DEBUG					; Debug key (backtick)
		mov	al, 1
		sub	al, debugMode
		mov	debugMode, al

	.ELSEIF eax == NINJA_KEY_UP					; Up
		mov	al, CurrentNinja.Control
		mov	bl, NINJA_CONTROL_UP
		not	bl
		and	al, bl
		mov	CurrentNinja.Control, al

	.ELSEIF eax == NINJA_KEY_DOWN				; Down
		mov	al, CurrentNinja.Control
		mov	bl, NINJA_CONTROL_DOWN
		not	bl
		and	al, bl
		mov	CurrentNinja.Control, al

	.ELSEIF eax == NINJA_KEY_LEFT				; Left
		mov	al, CurrentNinja.Control
		mov	bl, NINJA_CONTROL_LEFT
		not	bl
		and	al, bl
		mov	CurrentNinja.Control, al

	.ELSEIF eax == NINJA_KEY_RIGHT				; Right
		mov	al, CurrentNinja.Control
		mov	bl, NINJA_CONTROL_RIGHT
		not	bl
		and	al, bl
		mov	CurrentNinja.Control, al

	.ELSEIF eax == NINJA_KEY_FIRE				; Right
		mov	al, CurrentNinja.Control
		mov	bl, NINJA_CONTROL_FIRE
		not	bl
		and	al, bl
		mov	CurrentNinja.Control, al
	.ENDIF
	ret
KeyUp	endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; On Paint
OnPaint	proc	STDCALL

INCLUDE Gfx-UI.inc

INCLUDE Gfx-Action.inc

	push	SRCCOPY
	push	0
	push	0
	push	bufferDC
	push	GAME_SCREEN_HEIGHT
	push	GAME_SCREEN_WIDTH
	push	0
	push	0
	push	engineDC
	call	BitBlt

	ret
OnPaint	endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; On Timer
OnTimer	proc	STDCALL, timerID:DWORD
	mov	eax, timerID
	.IF eax == TIMER_PAINTER
		call	OnPaint
	.ELSEIF eax == TIMER_ANIMATOR
		push	0
		call	ControlHandler

		mov	eax, CurrentNinja.ScreenID
		mov	ecx, MapRoom_Len
		mul	ecx
		add	eax, offset Jane_Map

		.IF [eax].enemy1_LivesLeft != 0FFh
			push	eax

			push	1
			call	ControlEnemy

			pop	eax
		.ENDIF

		.IF [eax].enemy2_LivesLeft != 0FFh
			push	2
			call	ControlEnemy
		.ENDIF

	.ENDIF
	ret
OnTimer	endp