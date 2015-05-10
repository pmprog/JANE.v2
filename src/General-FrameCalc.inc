CalcNinjaAnimOffset	proc	STDCALL
	mov	ecx, Inventory_Len
	movzx	eax, CurrentNinja.ActiveInventory
	mul	ecx
	add	eax, offset InventoryList			; eax -> Current Inventory item
	movzx	eax, [eax].NinjaFrameset

	.IF eax == 0
		mov	esi, offset Animation_EmptyHand_Player
	.ELSEIF eax == 1
		mov	esi, offset Animation_SwordHand_Player
	.ELSE							; Catch Errors
		mov	esi, offset Animation_EmptyHand_Player
	.ENDIF

	ret
CalcNinjaAnimOffset	endp

CalcNinjaFrame	proc	STDCALL
	.IF CurrentNinja.State == NINJA_STATE_STANDING
		mov	esi, [esi].offsStand
;	.ELSEIF CurrentNinja.State == NINJA_STATE_TRANSITION
;		mov	esi, [esi].offsStand
	.ELSEIF CurrentNinja.State == NINJA_STATE_JUMPING
		mov	esi, [esi].offsJump
	.ELSEIF CurrentNinja.State == NINJA_STATE_PUNCHING
		mov	esi, [esi].offsPunch
	.ELSEIF CurrentNinja.State == NINJA_STATE_SLASHING
		mov	esi, [esi].offsSlash
	.ELSEIF CurrentNinja.State == NINJA_STATE_JABING
		mov	esi, [esi].offsJab
	.ELSEIF CurrentNinja.State == NINJA_STATE_KICKING
		mov	esi, [esi].offsKick
	.ELSEIF CurrentNinja.State == NINJA_STATE_PARRY
		mov	esi, [esi].offsParry
	.ELSEIF CurrentNinja.State == NINJA_STATE_HURT
		mov	esi, [esi].offsHurt
	.ELSEIF CurrentNinja.State == NINJA_STATE_DYING
		mov	esi, [esi].offsDying
	.ELSEIF CurrentNinja.State == NINJA_STATE_SWITCHING
		mov	esi, [esi].offsSwitch
	.ELSEIF CurrentNinja.State == NINJA_STATE_WALKING

		.IF CurrentNinja.Facing == NINJA_FACING_NORTH
			mov	al, CurrentNinja.Control
			and	al, NINJA_CONTROL_DOWN
			.IF al == 0
				mov	esi, [esi].offsNorthWalkF
			.ELSE
				mov	esi, [esi].offsNorthWalkB
			.ENDIF
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_EAST
			mov	al, CurrentNinja.Control
			and	al, NINJA_CONTROL_LEFT
			.IF al == 0
				mov	esi, [esi].offsEastWalkF
			.ELSE
				mov	esi, [esi].offsEastWalkB
			.ENDIF
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_SOUTH
			mov	al, CurrentNinja.Control
			and	al, NINJA_CONTROL_UP
			.IF al == 0
				mov	esi, [esi].offsSouthWalkF
			.ELSE
				mov	esi, [esi].offsSouthWalkB
			.ENDIF
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_WEST
			mov	al, CurrentNinja.Control
			and	al, NINJA_CONTROL_RIGHT
			.IF al == 0
				mov	esi, [esi].offsWestWalkF
			.ELSE
				mov	esi, [esi].offsWestWalkB
			.ENDIF
		.ENDIF

	.ENDIF
	ret
CalcNinjaFrame	endp

CalcEnemyAnimOffset	proc	STDCALL, iEnemy:DWORD
	mov	eax, CurrentNinja.ScreenID
	mov	ecx, MapRoom_Len
	mul	eax
	add	eax, offset Jane_Map				; eax -> Map Data
	mov	ebx, iEnemy
	.IF ebx == 2
		mov	esi, offset Animation_EmptyHand_Enemy
	.ELSEIF ebx == 2
		mov	esi, offset Animation_SwordHand_Enemy
	.ELSE							; Catch Errors
		mov	esi, offset Animation_EmptyHand_Enemy
	.ENDIF

	ret
CalcEnemyAnimOffset	endp

CalcEnemyFrame	proc	STDCALL, EnemyState:DWORD, EnemyFacing:DWORD
	mov	ebx, EnemyFacing
	mov	eax, EnemyState
	.IF eax == NINJA_STATE_STANDING
		mov	esi, [esi].offsStand
	.ELSEIF eax == NINJA_STATE_PUNCHING
		mov	esi, [esi].offsPunch
	.ELSEIF eax == NINJA_STATE_SLASHING
		mov	esi, [esi].offsSlash
	.ELSEIF eax == NINJA_STATE_JABING
		mov	esi, [esi].offsJab
	.ELSEIF eax == NINJA_STATE_KICKING
		mov	esi, [esi].offsKick
	.ELSEIF eax == NINJA_STATE_PARRY
		mov	esi, [esi].offsParry
	.ELSEIF eax == NINJA_STATE_HURT
		mov	esi, [esi].offsHurt
	.ELSEIF eax == NINJA_STATE_DYING
		mov	esi, [esi].offsDying
	.ELSEIF eax == NINJA_STATE_DEAD
		mov	esi, [esi].offsDead
	.ELSEIF eax == NINJA_STATE_WALKING
		.IF ebx == NINJA_FACING_NORTH
			mov	esi, [esi].offsNorthWalkF
		.ELSEIF ebx == NINJA_FACING_EAST
			mov	esi, [esi].offsEastWalkF
		.ELSEIF ebx == NINJA_FACING_SOUTH
			mov	esi, [esi].offsSouthWalkF
		.ELSEIF ebx == NINJA_FACING_WEST
			mov	esi, [esi].offsWestWalkF
		.ENDIF
	.ENDIF
	ret
CalcEnemyFrame	endp