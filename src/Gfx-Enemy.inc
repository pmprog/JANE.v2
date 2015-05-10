GfxDrawEnemy		proc	STDCALL, EnemyNum:DWORD

	mov	eax, CurrentNinja.ScreenID
	mov	ecx, MapRoom_Len
	mul	ecx
	add	eax, offset Jane_Map
	mov	esi, eax					; esi -> map data

	mov	eax, EnemyNum
	.IF eax == 1
		movzx	eax, [esi].enemy1_Frameset
		lea	esi, [esi].enemy1_ScreenX
	.ELSE
		movzx	eax, [esi].enemy2_Frameset
		lea	esi, [esi].enemy2_ScreenX
	.ENDIF

	push	esi
	push	eax

	shl	eax, 2h
	add	eax, offset bmp_Skins			; eax -> bitmap handle

	push	dword ptr [eax]
	push	copierDC
	call	SelectObject

	pop	eax

	.IF eax == 2h						; Unarmed
		mov	esi, offset Animation_EmptyHand_Enemy
	.ELSEIF eax == 3h					; Sword
		mov	esi, offset Animation_SwordHand_Enemy
	.ENDIF

	pop	ebx
	push	ebx

	mov	eax, EnemyNum
	movzx	ecx, [ebx].enemy_Facing
	push	ecx
	mov	eax, EnemyNum
	movzx	eax, [ebx].enemy_State
	push	eax
	call	CalcEnemyFrame

	pop	ebx

	mov	eax, EnemyNum
	movzx	eax, [ebx].enemy_FrameIdx

	add	esi, eax
	movzx	eax, byte ptr [esi]				; eax == frame number
	mov	ecx, NINJA_FRAME_WIDTH
	mul	ecx
	mov	edi, eax					; edx == Left in frames

	push	COLOURS_NINJA_TRANS
	mov	eax, NINJA_FRAME_HEIGHT
	push	eax
	push	NINJA_FRAME_WIDTH
	mov	edx, EnemyNum
	movzx	ecx, [ebx].enemy_Facing
	mul	ecx
	push	eax						; eax -> Top of frame
	push	edi
	push	copierDC
	push	NINJA_FRAME_HEIGHT
	push	NINJA_FRAME_WIDTH
	mov	edx, EnemyNum
	mov	eax, [ebx].enemy_ScreenY
	push	eax
	mov	edx, EnemyNum
	mov	eax, [ebx].enemy_ScreenX

		.IF [ebx].enemy_ActiveInventory == ENEMY_INVENTORY_SWORD
			db	10h dup (90h)

			.IF byte ptr [esi] == 09h
				.IF [ebx].enemy_Facing == NINJA_FACING_NORTH
					add	eax, 20
				.ELSEIF [ebx].enemy_Facing == NINJA_FACING_EAST
					add	eax, 20
				.ELSEIF [ebx].enemy_Facing == NINJA_FACING_SOUTH
					add	eax, -20
				.ELSEIF [ebx].enemy_Facing == NINJA_FACING_WEST
					add	eax, -20
				.ENDIF

			.ELSEIF byte ptr [esi] == 0Fh
				.IF [ebx].enemy_Facing == NINJA_FACING_NORTH
					add	eax, 20
				.ELSEIF [ebx].enemy_Facing == NINJA_FACING_EAST
					add	eax, 20
				.ELSEIF [ebx].enemy_Facing == NINJA_FACING_SOUTH
					add	eax, -20
				.ELSEIF [ebx].enemy_Facing == NINJA_FACING_WEST
					add	eax, -20
				.ENDIF

			.ELSEIF byte ptr [esi] == 10h
				.IF [ebx].enemy_Facing == NINJA_FACING_NORTH
					add	eax, 20
				.ELSEIF [ebx].enemy_Facing == NINJA_FACING_EAST
					add	eax, 20
				.ELSEIF [ebx].enemy_Facing == NINJA_FACING_SOUTH
					add	eax, -20
				.ELSEIF [ebx].enemy_Facing == NINJA_FACING_WEST
					add	eax, -20
				.ENDIF

			.ELSEIF byte ptr [esi] == 11h
				.IF [ebx].enemy_Facing == NINJA_FACING_NORTH
					add	eax, 20
				.ELSEIF [ebx].enemy_Facing == NINJA_FACING_EAST
					add	eax, 20
				.ELSEIF [ebx].enemy_Facing == NINJA_FACING_SOUTH
					add	eax, -20
				.ELSEIF [ebx].enemy_Facing == NINJA_FACING_WEST
					add	eax, -20
				.ENDIF

			.ENDIF
		.ENDIF

	push	eax
	push	actionDC
	call	TransparentBlt

	ret
GfxDrawEnemy		endp

GfxDrawEnemyBelow	proc	STDCALL, startY:DWORD
	mov	eax, CurrentNinja.ScreenID
	mov	ecx, MapRoom_Len
	mul	ecx
	add	eax, offset Jane_Map			; eax -> MapRoom structure
	mov	esi, eax				; esi -> MapRoom structure

	mov	eax, startY
	cmp	[esi].enemy1_LivesLeft, 0FFh
	je	gfxenemy_noenemyone

	mov	ebx, [esi].enemy1_ScreenY
	add	ebx, NINJA_FRAME_OFFSET_Y
	cmp	eax, ebx
	jg	gfxenemy_noenemyone

	push	esi

	push	1
	call	GfxDrawEnemy

	pop	esi
	mov	eax, [esi].enemy1_ScreenY
	add	eax, NINJA_FRAME_OFFSET_Y

gfxenemy_noenemyone:

	cmp	[esi].enemy2_LivesLeft, 0FFh
	je	gfxenemy_noenemytwo

	mov	eax, startY
	mov	ebx, [esi].enemy2_ScreenY
	add	ebx, NINJA_FRAME_OFFSET_Y
	cmp	eax, ebx
	jg	gfxenemy_noenemytwo

	push	esi

	push	2
	call	GfxDrawEnemy

	pop	esi
	mov	eax, [esi].enemy2_ScreenY
	add	eax, NINJA_FRAME_OFFSET_Y

gfxenemy_noenemytwo:

	ret
GfxDrawEnemyBelow	endp