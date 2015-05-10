	.code

OnEnterRoom	proc	STDCALL

	;;; Process Room Entry
	push	NINJA_STATE_WALKING
	call	SetNinjaState

enterroom_sleepdraw:
	call	OnPaint
	push	1h
	call	Sleep
	cmp	rectTransition.rc_bottom, NINJA_FRAME_HEIGHT
	jne	enterroom_sleepdraw

	ret
OnEnterRoom	endp

OnExitRoom	proc	STDCALL
	;;; Process Room Exit (and which room to move to)
	mov	rectTransition.rc_bottom, NINJA_FRAME_HEIGHT + 10h

exitroom_sleepdraw:
	call	OnPaint
	push	1h
	call	Sleep
	cmp	rectTransition.rc_bottom, GAME_ACTION_HEIGHT + NINJA_FRAME_HEIGHT
	jne	exitroom_sleepdraw

	.IF CurrentNinja.ScreenID == 0
		; Start Screen
		.IF CurrentNinja.ScreenY <= GAME_ACTION_HEIGHT / 2
			mov	CurrentNinja.ScreenID, 01h
			mov	CurrentNinja.ScreenX, NINJA_FRAME_WIDTH
			mov	CurrentNinja.ScreenY, GAME_ACTION_HEIGHT - 30
			mov	CurrentNinja.Facing, NINJA_FACING_NORTH
		.ELSE
			mov	CurrentNinja.ScreenID, 05h
			mov	CurrentNinja.ScreenX, NINJA_FRAME_WIDTH
			mov	CurrentNinja.ScreenY, NINJA_FRAME_HEIGHT
			mov	CurrentNinja.Facing, NINJA_FACING_EAST
		.ENDIF
	.ELSEIF CurrentNinja.ScreenID == 1
		.IF CurrentNinja.ScreenX >= GAME_ACTION_WIDTH / 2
			; Top Right
			mov	CurrentNinja.ScreenID, 02h
			mov	CurrentNinja.ScreenX, NINJA_FRAME_WIDTH
			mov	CurrentNinja.ScreenY, GAME_ACTION_HEIGHT - 50
			mov	CurrentNinja.Facing, NINJA_FACING_NORTH
		.ELSEIF CurrentNinja.ScreenY >= GAME_ACTION_HEIGHT / 2
			mov	CurrentNinja.ScreenID, 00h
			mov	CurrentNinja.ScreenX, GAME_ACTION_WIDTH
			mov	CurrentNinja.ScreenY, NINJA_FRAME_HEIGHT
			mov	CurrentNinja.Facing, NINJA_FACING_SOUTH
		.ELSE
			; Top Left
			mov	CurrentNinja.ScreenID, 03h
			mov	CurrentNinja.ScreenX, GAME_ACTION_WIDTH
			mov	CurrentNinja.ScreenY, GAME_ACTION_HEIGHT - 20
			mov	CurrentNinja.Facing, NINJA_FACING_WEST
		.ENDIF
	.ELSEIF CurrentNinja.ScreenID == 2
		.IF CurrentNinja.ScreenX >= GAME_ACTION_WIDTH / 2
			mov	CurrentNinja.ScreenID, 04h
			mov	CurrentNinja.ScreenX, NINJA_FRAME_WIDTH
			mov	CurrentNinja.ScreenY, GAME_ACTION_HEIGHT - 30
			mov	CurrentNinja.Facing, NINJA_FACING_NORTH
		.ELSE
			mov	CurrentNinja.ScreenID, 01h
			mov	CurrentNinja.ScreenX, GAME_ACTION_WIDTH - 10
			mov	CurrentNinja.ScreenY, (GAME_ACTION_HEIGHT / 2) + 20
			mov	CurrentNinja.Facing, NINJA_FACING_SOUTH
		.ENDIF
	.ELSEIF CurrentNinja.ScreenID == 3
		.IF CurrentNinja.ScreenY <= GAME_ACTION_HEIGHT / 2
			mov	CurrentNinja.ScreenID, 04h
			mov	CurrentNinja.ScreenX, NINJA_FRAME_WIDTH
			mov	CurrentNinja.ScreenY, NINJA_FRAME_HEIGHT
			mov	CurrentNinja.Facing, NINJA_FACING_EAST
		.ELSE
			mov	CurrentNinja.ScreenID, 01h
			mov	CurrentNinja.ScreenX, NINJA_FRAME_WIDTH
			mov	CurrentNinja.ScreenY, NINJA_FRAME_HEIGHT - 20
			mov	CurrentNinja.Facing, NINJA_FACING_EAST
		.ENDIF
	.ELSEIF CurrentNinja.ScreenID == 4
		.IF CurrentNinja.ScreenY <= GAME_ACTION_HEIGHT / 2
			mov	CurrentNinja.ScreenID, 03h
			mov	CurrentNinja.ScreenX, GAME_ACTION_WIDTH
			mov	CurrentNinja.ScreenY, NINJA_FRAME_HEIGHT
			mov	CurrentNinja.Facing, NINJA_FACING_SOUTH
		.ELSE
			mov	CurrentNinja.ScreenID, 02h
			mov	CurrentNinja.ScreenX, GAME_ACTION_WIDTH
			mov	CurrentNinja.ScreenY, (GAME_ACTION_HEIGHT / 2) - 20
			mov	CurrentNinja.Facing, NINJA_FACING_SOUTH
		.ENDIF

	.ELSEIF CurrentNinja.ScreenID == 5
		.IF CurrentNinja.ScreenY <= GAME_ACTION_HEIGHT / 2
			mov	CurrentNinja.ScreenID, 00h
			mov	CurrentNinja.ScreenX, GAME_ACTION_WIDTH
			mov	CurrentNinja.ScreenY, GAME_ACTION_HEIGHT - 20
			mov	CurrentNinja.Facing, NINJA_FACING_WEST
		.ELSE
			mov	CurrentNinja.ScreenID, 06h
			mov	CurrentNinja.ScreenX, GAME_ACTION_WIDTH
			mov	CurrentNinja.ScreenY, (GAME_ACTION_HEIGHT / 2) + 20
			mov	CurrentNinja.Facing, NINJA_FACING_SOUTH
		.ENDIF
	.ELSEIF CurrentNinja.ScreenID == 6
		.IF CurrentNinja.ScreenX >= GAME_ACTION_WIDTH / 2
			mov	CurrentNinja.ScreenID, 05h
			mov	CurrentNinja.ScreenX, NINJA_FRAME_WIDTH
			mov	CurrentNinja.ScreenY, GAME_ACTION_HEIGHT - 30
			mov	CurrentNinja.Facing, NINJA_FACING_NORTH
		.ELSE
			mov	CurrentNinja.ScreenID, 07h
			mov	CurrentNinja.ScreenX, GAME_ACTION_WIDTH
			mov	CurrentNinja.ScreenY, NINJA_FRAME_HEIGHT
			mov	CurrentNinja.Facing, NINJA_FACING_SOUTH
		.ENDIF
	.ELSEIF CurrentNinja.ScreenID == 7
		.IF CurrentNinja.ScreenY <= GAME_ACTION_HEIGHT / 2
			mov	CurrentNinja.ScreenID, 06h
			mov	CurrentNinja.ScreenX, NINJA_FRAME_WIDTH
			mov	CurrentNinja.ScreenY, GAME_ACTION_HEIGHT - 30
			mov	CurrentNinja.Facing, NINJA_FACING_NORTH
		.ELSE
			mov	CurrentNinja.ScreenID, 08h
			mov	CurrentNinja.ScreenX, NINJA_FRAME_WIDTH
			mov	CurrentNinja.ScreenY, NINJA_FRAME_HEIGHT / 2
			mov	CurrentNinja.Facing, NINJA_FACING_EAST
		.ENDIF
	.ELSEIF CurrentNinja.ScreenID == 8
		.IF CurrentNinja.ScreenX <= GAME_ACTION_WIDTH / 2
			mov	CurrentNinja.ScreenID, 07h
			mov	CurrentNinja.ScreenX, GAME_ACTION_WIDTH
			mov	CurrentNinja.ScreenY, GAME_ACTION_HEIGHT - 20
			mov	CurrentNinja.Facing, NINJA_FACING_WEST
		.ELSE
			mov	CurrentNinja.ScreenID, 09h
			mov	CurrentNinja.ScreenX, NINJA_FRAME_WIDTH
			mov	CurrentNinja.ScreenY, NINJA_FRAME_HEIGHT
			mov	CurrentNinja.Facing, NINJA_FACING_EAST
		.ENDIF
	.ELSEIF CurrentNinja.ScreenID == 9
		.IF CurrentNinja.ScreenX <= GAME_ACTION_WIDTH / 2
			mov	CurrentNinja.ScreenID, 08h
			mov	CurrentNinja.ScreenX, GAME_ACTION_WIDTH
			mov	CurrentNinja.ScreenY, GAME_ACTION_HEIGHT - 20
			mov	CurrentNinja.Facing, NINJA_FACING_WEST
		.ENDIF
	.ENDIF
	call	CloneState

	call	OnEnterRoom
	ret
OnExitRoom	endp

OnDie		proc	STDCALL
	;;; Process Room Exit (and which room to move to)
	mov	rectTransition.rc_bottom, NINJA_FRAME_HEIGHT + 10h

ondie_sleepdraw:
	call	OnPaint
	push	1h
	call	Sleep
	cmp	rectTransition.rc_bottom, GAME_ACTION_HEIGHT + NINJA_FRAME_HEIGHT
	jne	ondie_sleepdraw

	mov	ResetToNinja.State, NINJA_STATE_DEAD

	mov	esi, offset ResetToNinja
	mov	edi, offset CurrentNinja
	mov	ecx, Ninja_Len
	rep	movsb
	mov	CurrentNinja.Control, 00h
	mov	CurrentNinja.Health, GAME_MAX_HEALTH

	push	NINJA_STATE_WALKING
	call	SetNinjaState

	;;; Process Room Exit (and which room to move to)
	mov	rectTransition.rc_top, NINJA_FRAME_HEIGHT + 10h

ondie_sleepdraw2:
	call	OnPaint
	push	1h
	call	Sleep
	cmp	rectTransition.rc_top, GAME_ACTION_HEIGHT + NINJA_FRAME_HEIGHT
	jne	ondie_sleepdraw2

	ret
OnDie		endp

OnTakeDamage	proc	STDCALL, Amount:DWORD
	mov	eax, Amount
	movzx	ebx, CurrentNinja.Health

	.IF eax >= ebx
		mov	CurrentNinja.Health, 00h
		push	NINJA_STATE_DYING
		call	SetNinjaState
	.ELSE
		sub	ebx, eax
		mov	CurrentNinja.Health, bx
		push	NINJA_STATE_HURT
		call	SetNinjaState
	.ENDIF
	ret
OnTakeDamage	endp