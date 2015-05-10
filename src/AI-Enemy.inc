	.data

debugGargoyle		db	?
ptrEnemy		dd	?

	.code

ControlEnemy		proc	STDCALL, iEnemyNum:DWORD
	mov	al, debugGargoyle
	or	al, al
	jnz	control_gargoyleactive		;Debug mode Gargoyle


	mov	eax, CurrentNinja.ScreenID
	mov	ecx, MapRoom_Len
	mul	ecx
	add	eax, offset Jane_Map			; eax -> Screen
	mov	ecx, iEnemyNum
	.IF ecx == 1
		lea	ebx, [eax].enemy1_ScreenX
		mov	ptrEnemy, ebx
	.ELSE
		lea	ebx, [eax].enemy2_ScreenX
		mov	ptrEnemy, ebx
	.ENDIF

	push	ebx

	;;; Move/Attack/Animate!
	mov	eax, iEnemyNum
	push	eax
	call	AnimationIncreaseFrameEnemy

	pop	ebx

	.IF [ebx].enemy_State == NINJA_STATE_WALKING

		; If Ninja in attack distance, pick attack
		mov	ecx, CurrentNinja.ScreenX
		mov	edx, [ebx].enemy_ScreenX
		.IF ecx > edx
			xchg	ecx, edx
		.ENDIF
		sub	edx, ecx				; edx == X distance between

		push	edx

		mov	ecx, CurrentNinja.ScreenY
		mov	edx, [ebx].enemy_ScreenY
		.IF ecx > edx
			xchg	ecx, edx
		.ENDIF
		sub	edx, ecx				; edx == Y distance between
		pop	ecx					; ecx == X distance between

		cmp	ecx, NINJA_FRAME_WIDTH / 2
		jg	control_notcloseforattack
		cmp	edx, NINJA_FRAME_HEIGHT / 2
		jg	control_notcloseforattack

		;;; Try attack
		push	ebx
		pushfd

		push	ebx
		call	RandomNumber
		xor	edx, edx
		mov	ecx, 07h
		div	ecx

		popfd
		pop	ebx

		.IF edx == 00h
			mov	[ebx].enemy_State, NINJA_STATE_KICKING
			mov	[ebx].enemy_FrameIdx, 00h
		.ELSEIF edx == 01h
			mov	[ebx].enemy_State, NINJA_STATE_PUNCHING
			mov	[ebx].enemy_FrameIdx, 00h
		.ELSEIF edx == 02h
			mov	[ebx].enemy_State, NINJA_STATE_JABING
			mov	[ebx].enemy_FrameIdx, 00h
		.ELSEIF edx == 03h
			mov	[ebx].enemy_State, NINJA_STATE_SLASHING
			mov	[ebx].enemy_FrameIdx, 00h
		.ENDIF
		jmp	control_skipmoveenemy

control_notcloseforattack:
		; If not, move in a random direction

		push	ebx
		pushfd

		push	ebx
		call	RandomNumber

		xor	edx, edx
		mov	ecx, 20h
		div	ecx					; edx == NINJA_FACING_*

		popfd
		pop	ebx

		.IF [ebx].enemy_Facing == NINJA_FACING_NORTH
			;;; If facing ninja, keep facing that direction
			mov	ecx, CurrentNinja.ScreenX
			.IF ecx > [ebx].enemy_ScreenX
				mov	ecx, CurrentNinja.ScreenY
				.IF ecx < [ebx].enemy_ScreenY
					xor	edx, edx
				.ENDIF
			.ENDIF

			.IF edx == 1
				mov	[ebx].enemy_Facing, NINJA_FACING_EAST
			.ELSEIF edx == 2
				mov	[ebx].enemy_Facing, NINJA_FACING_WEST
			.ENDIF
		.ELSEIF [ebx].enemy_Facing == NINJA_FACING_EAST
			;;; If facing ninja, keep facing that direction
			mov	ecx, CurrentNinja.ScreenX
			.IF ecx > [ebx].enemy_ScreenX
				mov	ecx, CurrentNinja.ScreenY
				.IF ecx > [ebx].enemy_ScreenY
					xor	edx, edx
				.ENDIF
			.ENDIF

			.IF edx == 1
				mov	[ebx].enemy_Facing, NINJA_FACING_NORTH
			.ELSEIF edx == 2
				mov	[ebx].enemy_Facing, NINJA_FACING_SOUTH
			.ENDIF
		.ELSEIF [ebx].enemy_Facing == NINJA_FACING_SOUTH
			;;; If facing ninja, keep facing that direction
			mov	ecx, CurrentNinja.ScreenX
			.IF ecx < [ebx].enemy_ScreenX
				mov	ecx, CurrentNinja.ScreenY
				.IF ecx > [ebx].enemy_ScreenY
					xor	edx, edx
				.ENDIF
			.ENDIF

			.IF edx == 1
				mov	[ebx].enemy_Facing, NINJA_FACING_EAST
			.ELSEIF edx == 2
				mov	[ebx].enemy_Facing, NINJA_FACING_WEST
			.ENDIF
		.ELSEIF [ebx].enemy_Facing == NINJA_FACING_WEST
			;;; If facing ninja, keep facing that direction
			mov	ecx, CurrentNinja.ScreenX
			.IF ecx < [ebx].enemy_ScreenX
				mov	ecx, CurrentNinja.ScreenY
				.IF ecx < [ebx].enemy_ScreenY
					xor	edx, edx
				.ENDIF
			.ENDIF

			.IF edx == 1
				mov	[ebx].enemy_Facing, NINJA_FACING_NORTH
			.ELSEIF edx == 2
				mov	[ebx].enemy_Facing, NINJA_FACING_SOUTH
			.ENDIF
		.ENDIF
		push	ebx
		call	MoveEnemy
control_skipmoveenemy:
	.ELSE
		cmp	[ebx].enemy_State, NINJA_STATE_PUNCHING
		je	control_attackingmode
		cmp	[ebx].enemy_State, NINJA_STATE_SLASHING
		je	control_attackingmode
		cmp	[ebx].enemy_State, NINJA_STATE_JABING
		je	control_attackingmode
		cmp	[ebx].enemy_State, NINJA_STATE_KICKING
		jne	control_donecontrol
control_attackingmode:
		push	ptrEnemy
		call	ControlCollision
control_donecontrol:
	.ENDIF

control_gargoyleactive:
	ret
ControlEnemy		endp

ControlCollision	proc	STDCALL, enemyStruc:DWORD
	pusha
	mov	eax, enemyStruc
	mov	ebx, [eax].enemy_ScreenX
	mov	edx, [eax].enemy_ScreenY
	mov	ch, [eax].enemy_Facing
	.IF [eax].enemy_ActiveInventory == ENEMY_INVENTORY_SWORD		;Sword
		.IF ch == NINJA_FACING_NORTH
			add	ebx, 30h
			sub	edx, 0Ch
		.ELSEIF ch == NINJA_FACING_EAST
			add	ebx, 30h
			add	edx, 0Ch
		.ELSEIF ch == NINJA_FACING_WEST
			sub	ebx, 30h
			sub	edx, 0Ch
		.ELSEIF ch == NINJA_FACING_SOUTH
			sub	ebx, 30h
			add	edx, 0Ch
		.ENDIF
	.ELSE
		.IF ch == NINJA_FACING_NORTH
			add	ebx, 20h
			sub	edx, 08h
		.ELSEIF ch == NINJA_FACING_EAST
			add	ebx, 20h
			add	edx, 08h
		.ELSEIF ch == NINJA_FACING_WEST
			sub	ebx, 20h
			sub	edx, 08h
		.ELSEIF ch == NINJA_FACING_SOUTH
			sub	ebx, 20h
			add	edx, 08h
		.ENDIF
	.ENDIF

	mov	ecx, CurrentNinja.ScreenY
	sub	ecx, 08h
	.IF ecx <= edx
		add	ecx, 10h
		.IF ecx >= edx
			mov	ecx, CurrentNinja.ScreenX
			sub	ecx, 20h
			.IF ecx <= ebx
				add	ecx, 40h
				.IF ecx >= ebx

					.IF [eax].enemy_State == NINJA_STATE_KICKING
						push	04h
						call	OnTakeDamage
					.ELSEIF [eax].enemy_State == NINJA_STATE_JABING
						.IF [eax].enemy_ActiveInventory == ENEMY_INVENTORY_SWORD		;Sword
							push	04h
							call	OnTakeDamage
						.ELSE
							push	02h
							call	OnTakeDamage
						.ENDIF
					.ELSEIF [eax].enemy_State == NINJA_STATE_SLASHING
						.IF [eax].enemy_ActiveInventory == ENEMY_INVENTORY_SWORD
							push	04h
							call	OnTakeDamage
						.ELSE
							push	02h
							call	OnTakeDamage
						.ENDIF
					.ELSEIF [eax].enemy_State == NINJA_STATE_PUNCHING
						.IF [eax].enemy_ActiveInventory == ENEMY_INVENTORY_SWORD
							push	02h
							call	OnTakeDamage
						.ELSE
							push	01h
							call	OnTakeDamage
						.ENDIF
					.ENDIF

				.ENDIF
			.ENDIF

		.ENDIF
	.ENDIF
	popa
	ret
ControlCollision	endp                                                                                                                              