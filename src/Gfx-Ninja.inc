;;;;;;;;;;;;;;;; Ninja Gfx
;	cmp	CurrentNinja.State, NINJA_STATE_TRANSITION
;	je	gfxninja_nodrawing

	call	CalcNinjaAnimOffset

	shl	eax, 2h
	add	eax, offset bmp_Skins			; eax -> bitmap handle

	push	dword ptr [eax]
	push	copierDC
	call	SelectObject

	call	CalcNinjaFrame

	movzx	eax, CurrentNinja.Frame
	add	esi, eax
	movzx	eax, byte ptr [esi]				; eax == frame number
	mov	ecx, NINJA_FRAME_WIDTH
	mul	ecx
	mov	edi, eax					; edx == Left in frames

	cmp	CurrentNinja.State, NINJA_STATE_DROWNING
	je	gfxninja_sinking
	cmp	CurrentNinja.State, NINJA_STATE_SINKING
	jne	gfxninja_notsinking
gfxninja_sinking:
	mov	eax, sinkingFrame
	mov	ecx, NINJA_FRAME_WIDTH
	mul	ecx
	mov	edi, eax					; edx == Left in frames

	push	COLOURS_NINJA_TRANS
	mov	eax, NINJA_FRAME_OFFSET_Y
	sub	eax, sinkingFlags
	push	eax
	push	NINJA_FRAME_WIDTH
	mov	eax, NINJA_FRAME_HEIGHT
	movzx	ecx, CurrentNinja.Facing
	mul	ecx
	push	eax						; eax -> Top of frame
	push	edi
	push	copierDC
	mov	eax, NINJA_FRAME_OFFSET_Y
	sub	eax, sinkingFlags
	push	eax
	push	NINJA_FRAME_WIDTH
	mov	eax, CurrentNinja.ScreenY
	add	eax, sinkingFlags
	push	eax
	mov	eax, CurrentNinja.ScreenX
	push	eax
	push	actionDC
	call	TransparentBlt

	inc	sinkingFlags
	inc	sinkingFlags
	inc	sinkingFlags
	inc	sinkingFlags

	.IF sinkingFlags == NINJA_FRAME_HEIGHT
		.IF CurrentNinja.State == NINJA_STATE_DROWNING
			push	NINJA_STATE_DEAD
			call	SetNinjaState
		.ELSEIF CurrentNinja.State == NINJA_STATE_SINKING
			push	NINJA_STATE_TRANSITION
			call	SetNinjaState
		.ENDIF
	.ENDIF

	jmp	gfxninja_nodrawing

gfxninja_notsinking:
	push	COLOURS_NINJA_TRANS
	mov	eax, NINJA_FRAME_HEIGHT
	push	eax
	push	NINJA_FRAME_WIDTH
	movzx	ecx, CurrentNinja.Facing
	mul	ecx
	push	eax						; eax -> Top of frame
	push	edi
	push	copierDC
	push	NINJA_FRAME_HEIGHT
	push	NINJA_FRAME_WIDTH
	mov	eax, CurrentNinja.ScreenY
	push	eax
	mov	eax, CurrentNinja.ScreenX

		.IF CurrentNinja.ActiveInventory == 01h
			.IF byte ptr [esi] == 09h
				.IF CurrentNinja.Facing == NINJA_FACING_NORTH
					add	eax, 20
				.ELSEIF CurrentNinja.Facing == NINJA_FACING_EAST
					add	eax, 20
				.ELSEIF CurrentNinja.Facing == NINJA_FACING_SOUTH
					add	eax, -20
				.ELSEIF CurrentNinja.Facing == NINJA_FACING_WEST
					add	eax, -20
				.ENDIF

			.ELSEIF byte ptr [esi] == 17h
				.IF CurrentNinja.Facing == NINJA_FACING_NORTH
					add	eax, 20
				.ELSEIF CurrentNinja.Facing == NINJA_FACING_EAST
					add	eax, 20
				.ELSEIF CurrentNinja.Facing == NINJA_FACING_SOUTH
					add	eax, -20
				.ELSEIF CurrentNinja.Facing == NINJA_FACING_WEST
					add	eax, -20
				.ENDIF

			.ELSEIF byte ptr [esi] == 18h
				.IF CurrentNinja.Facing == NINJA_FACING_NORTH
					add	eax, 20
				.ELSEIF CurrentNinja.Facing == NINJA_FACING_EAST
					add	eax, 20
				.ELSEIF CurrentNinja.Facing == NINJA_FACING_SOUTH
					add	eax, -20
				.ELSEIF CurrentNinja.Facing == NINJA_FACING_WEST
					add	eax, -20
				.ENDIF

			.ENDIF
		.ENDIF

	push	eax
	push	actionDC
	call	TransparentBlt

gfxninja_nodrawing: