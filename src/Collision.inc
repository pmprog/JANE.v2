	.data
tmpCollision		dd	?
tmpCollection		dd	?

	.code

CollisionType		proc	STDCALL, locationX:DWORD, locationY:DWORD

	mov	eax, CurrentNinja.ScreenID
	mov	ecx, MapRoom_Len
	mul	ecx
	add	eax, offset Jane_Map			; eax -> MapRoom structure

	movzx	eax, [eax].BackgroundGfx
	shl	eax, 2h
	add	eax, offset bmp_MapScreens		; eax -> bitmap handle

	push	dword ptr [eax]
	push	copierDC
	call	SelectObject

	mov	eax, locationY
	add	eax, GAME_ACTION_HEIGHT
	sub	eax, NINJA_FRAME_HEIGHT
	add	eax, NINJA_FRAME_OFFSET_Y
	mov	ebx, locationX
	sub	ebx, NINJA_FRAME_WIDTH
	add	ebx, NINJA_FRAME_OFFSET_X
	push	eax
	push	ebx
	push	copierDC
	call	GetPixel

	ret
CollisionType		endp

MoveNinja		proc	STDCALL, direction:DWORD
	mov	eax, direction
	pusha

	mov	edx, CurrentNinja.ScreenX
	mov	ebx, CurrentNinja.ScreenY

	.IF eax == NINJA_CONTROL_UP
		sub	ebx, 02h
		add	edx, 08h
	.ELSEIF eax == NINJA_CONTROL_RIGHT
		add	ebx, 02h
		add	edx, 08h
	.ELSEIF eax == NINJA_CONTROL_LEFT
		sub	ebx, 02h
		sub	edx, 08h
	.ELSEIF eax == NINJA_CONTROL_DOWN
		add	ebx, 02h
		sub	edx, 08h
	.ELSEIF eax == NINJA_CONTROL_DOWN + NINJA_CONTROL_LEFT
		.IF CurrentNinja.Facing == NINJA_FACING_NORTH
			add	ebx, 01h
			sub	edx, 08h
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_EAST
			sub	ebx, 01h
			sub	edx, 08h
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_SOUTH
			add	ebx, 01h
			sub	edx, 08h
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_WEST
			sub	ebx, 01h
			sub	edx, 08h
		.ENDIF
	.ELSEIF eax == NINJA_CONTROL_UP + NINJA_CONTROL_RIGHT
		.IF CurrentNinja.Facing == NINJA_FACING_NORTH
			sub	ebx, 01h
			add	edx, 08h
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_EAST
			add	ebx, 01h
			add	edx, 08h
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_SOUTH
			sub	ebx, 01h
			add	edx, 08h
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_WEST
			add	ebx, 01h
			add	edx, 08h
		.ENDIF
	.ELSEIF eax == NINJA_CONTROL_DOWN + NINJA_CONTROL_RIGHT
		.IF CurrentNinja.Facing == NINJA_FACING_NORTH
			add	ebx, 04h
			sub	edx, 08h
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_EAST
			add	ebx, 04h
			add	edx, 08h
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_SOUTH
			add	ebx, 04h
			sub	edx, 08h
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_WEST
			add	ebx, 04h
			add	edx, 08h
		.ENDIF
	.ELSEIF eax == NINJA_CONTROL_UP + NINJA_CONTROL_LEFT
		.IF CurrentNinja.Facing == NINJA_FACING_NORTH
			sub	ebx, 04h
			add	edx, 08h
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_EAST
			sub	ebx, 04h
			sub	edx, 08h
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_SOUTH
			sub	ebx, 04h
			add	edx, 08h
		.ELSEIF CurrentNinja.Facing == NINJA_FACING_WEST
			sub	ebx, 04h
			sub	edx, 08h
		.ENDIF
	.ENDIF

	pusha
	push	ebx
	push	edx
	call	CollisionType
	mov	tmpCollision, eax
	popa

	.IF tmpCollision != COLOURS_MAP_NOWALK
		.IF tmpCollision == COLOURS_MAP_TRANSITION
			push	NINJA_STATE_TRANSITION
			call	SetNinjaState
		.ELSEIF tmpCollision == COLOURS_MAP_WATER
			.IF CurrentNinja.State != NINJA_STATE_JUMPING
				push	NINJA_STATE_DROWNING
				call	SetNinjaState
			.ELSE
				mov	CurrentNinja.ScreenX, edx
				mov	CurrentNinja.ScreenY, ebx
			.ENDIF
		.ELSE
			mov	CurrentNinja.ScreenX, edx
			mov	CurrentNinja.ScreenY, ebx
		.ENDIF
	.ENDIF

	popa
	ret
MoveNinja		endp


MoveEnemy		proc	STDCALL, enemyPtr:DWORD
	mov	eax, enemyPtr
	pusha

	mov	edx, [eax].enemy_ScreenX
	mov	ebx, [eax].enemy_ScreenY

	.IF [eax].enemy_Facing == NINJA_FACING_NORTH
		sub	ebx, 02h
		add	edx, 08h
	.ELSEIF [eax].enemy_Facing == NINJA_FACING_EAST
		add	ebx, 02h
		add	edx, 08h
	.ELSEIF [eax].enemy_Facing == NINJA_FACING_WEST
		sub	ebx, 02h
		sub	edx, 08h
	.ELSEIF [eax].enemy_Facing == NINJA_FACING_SOUTH
		add	ebx, 02h
		sub	edx, 08h
	.ENDIF

	pusha
	push	ebx
	push	edx
	call	CollisionType
	mov	tmpCollision, eax
	popa

	.IF tmpCollision == COLOURS_MAP_WALK
		mov	[eax].enemy_ScreenX, edx
		mov	[eax].enemy_ScreenY, ebx
	.ELSE
		.IF [eax].enemy_Facing == NINJA_FACING_NORTH
			mov	[eax].enemy_Facing, NINJA_FACING_SOUTH
		.ELSEIF [eax].enemy_Facing == NINJA_FACING_EAST
			mov	[eax].enemy_Facing, NINJA_FACING_WEST
		.ELSEIF [eax].enemy_Facing == NINJA_FACING_WEST
			mov	[eax].enemy_Facing, NINJA_FACING_EAST
		.ELSEIF [eax].enemy_Facing == NINJA_FACING_SOUTH
			mov	[eax].enemy_Facing, NINJA_FACING_NORTH
		.ENDIF
	.ENDIF

	popa
	ret
MoveEnemy		endp


AttackCollisionNinja		proc	STDCALL

	mov	eax, CurrentNinja.ScreenID
	mov	ecx, MapRoom_Len
	mul	ecx
	add	eax, offset Jane_Map			; eax -> screen data
	mov	ecx, [eax].screen_ObjectList	; ecx -> list of scenery

	mov	esi, CurrentNinja.ScreenX
	sub	esi, NINJA_FRAME_WIDTH
	mov	edi, CurrentNinja.ScreenY
	.IF CurrentNinja.State == NINJA_STATE_JABING
		sub	edi, NINJA_FRAME_HEIGHT
	.ELSE
		sub	edi, NINJA_FRAME_HEIGHT / 2
	.ENDIF

	.IF CurrentNinja.Facing == NINJA_FACING_NORTH
		add	esi, NINJA_FRAME_WIDTH - 10
	.ELSEIF CurrentNinja.Facing == NINJA_FACING_EAST
		add	esi, NINJA_FRAME_WIDTH - 10
	.ELSEIF CurrentNinja.Facing == NINJA_FACING_SOUTH
		add	esi, 10
	.ELSEIF CurrentNinja.Facing == NINJA_FACING_WEST
		add	esi, 10
	.ENDIF

attackcollision_rescan:
	pusha

	push	edi
	push	esi
	push	ecx
	call	IsObjectInColiision
	or	eax,eax
	jz	attackcollision_none

	popa

	.IF [ecx].AttackFunction != 0

		mov	eax, [ecx].AttackFunction
		pusha
		call	eax
		popa

	.ENDIF
	pusha

attackcollision_none:
	popa
	add	ecx, Object_Len
	cmp	byte ptr [ecx], 00h
	jne	attackcollision_rescan

attackcollision_leave:
	mov	eax, CurrentNinja.ScreenID
	mov	ecx, MapRoom_Len
	mul	ecx
	add	eax, offset Jane_Map
	push	eax
	lea	ebx, [eax].enemy1_ScreenX

	.IF [ebx].enemy_LivesLeft != 0FFh
		push	ebx
		call	IsEnemyCollision
	.ENDIF

	pop	eax
	lea	ebx, [eax].enemy2_ScreenX

	.IF [ebx].enemy_LivesLeft != 0FFh
		push	ebx
		call	IsEnemyCollision
	.ENDIF

	ret
AttackCollisionNinja		endp

PickupCollisionNinja		proc	STDCALL

	mov	eax, CurrentNinja.ScreenID
	mov	ecx, MapRoom_Len
	mul	ecx
	add	eax, offset Jane_Map			; eax -> screen data
	mov	ecx, [eax].screen_ObjectList	; ecx -> list of scenery

	mov	esi, CurrentNinja.ScreenX
	sub	esi, NINJA_FRAME_WIDTH
	mov	edi, CurrentNinja.ScreenY
	sub	edi, NINJA_FRAME_HEIGHT / 2

	.IF CurrentNinja.Facing == NINJA_FACING_NORTH
		add	esi, NINJA_FRAME_WIDTH - 10
	.ELSEIF CurrentNinja.Facing == NINJA_FACING_EAST
		add	esi, NINJA_FRAME_WIDTH - 10
	.ELSEIF CurrentNinja.Facing == NINJA_FACING_SOUTH
		add	esi, 10
	.ELSEIF CurrentNinja.Facing == NINJA_FACING_WEST
		add	esi, 10
	.ENDIF

pickupcollision_rescan:
	pusha

	push	edi
	push	esi
	push	ecx
	call	IsObjectInColiision
	or	eax,eax
	jz	pickupcollision_none

	popa

	;;; Is Item Pickup?! If so, collect!
	.IF [ecx].Collect_Qty > 0

		movzx	eax, [ecx].Collect_InvIdx
		mov	ebx, Inventory_Len
		mul	ebx
		add	eax, offset InventoryList	; eax -> Inventory Item

		mov	bl, [ecx].Collect_Qty 
		mov	[eax].QtyHeld, bl		; Increase held qty

		mov	[ecx].ScreenY, GAME_ACTION_HEIGHT * 2		; Remove pickup

	.ENDIF

	pusha

pickupcollision_none:
	popa
	add	ecx, Object_Len
	cmp	byte ptr [ecx], 00h
	jne	pickupcollision_rescan

pickupcollision_leave:
	ret
PickupCollisionNinja		endp

IsObjectInColiision		proc	STDCALL, offObject:DWORD, locationX:DWORD, locationY:DWORD
	mov	esi, offObject
	mov	ebx, locationX
	mov	edx, locationY

	movzx	eax, [esi].ObjectGfx
	shl	eax, 2h
	add	eax, offset bmp_Objects		; eax -> bitmap handle

	.IF edx >= [esi].ScreenY
		pusha
		push	offset bitmapDimensions
		push	BITMAP_
		push	dword ptr [eax]
		call	GetObject				; bitmapDimensions holds dimensions
		popa

		sub	edx, bitmapDimensions.bm_bmHeight

		.IF edx <= [esi].ScreenY

			; Item is within Y range, now check X range
			.IF ebx >= [esi].ScreenX
				sub	ebx, bitmapDimensions.bm_bmWidth

				.IF ebx <= [esi].ScreenX
					xor	eax, eax
					dec	eax
				.ELSE
					xor	eax, eax
				.ENDIF
			.ELSE
				xor	eax, eax
			.ENDIF

		.ELSE
			xor	eax, eax
		.ENDIF
	.ELSE
		xor	eax, eax
	.ENDIF

	ret
IsObjectInColiision		endp

GiveDamage		proc	STDCALL, enemyStruc:DWORD, Amount:DWORD
	pusha
	mov	eax, Amount
	mov	edi, enemyStruc
	movzx	ebx, [edi].enemy_Health

	.IF eax >= ebx
		mov	[edi].enemy_Health, 00h
		mov	[edi].enemy_State, NINJA_STATE_DYING
		mov	[edi].enemy_FrameIdx, 00h
	.ELSE
		sub	ebx, eax
		mov	[edi].enemy_Health, bx
		mov	[edi].enemy_State, NINJA_STATE_HURT
		mov	[edi].enemy_FrameIdx, 00h
	.ENDIF
	popa
	ret
GiveDamage		endp

IsEnemyCollision	proc	STDCALL, enemyStruc:DWORD
	pusha
	mov	ebx, CurrentNinja.ScreenX
	mov	edx, CurrentNinja.ScreenY
	mov	ch, CurrentNinja.Facing
	.IF CurrentNinja.ActiveInventory == 1		;Sword
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

	mov	eax, enemyStruc
	mov	ecx, [eax].enemy_ScreenY
	sub	ecx, 08h
	.IF ecx <= edx
		add	ecx, 10h
		.IF ecx >= edx
			mov	ecx, [eax].enemy_ScreenX
			sub	ecx, 20h
			.IF ecx <= ebx
				add	ecx, 40h
				.IF ecx >= ebx

					.IF CurrentNinja.State == NINJA_STATE_KICKING
						push	eax
						push	04h
						push	eax
						call	GiveDamage
						pop	eax
					.ELSEIF CurrentNinja.State == NINJA_STATE_JABING
						push	eax
						.IF CurrentNinja.ActiveInventory == 1		;Sword
							push	04h
							push	eax
							call	GiveDamage
						.ELSE
							push	02h
							push	eax
							call	GiveDamage
						.ENDIF
						pop	eax
					.ELSEIF CurrentNinja.State == NINJA_STATE_SLASHING
						push	eax
						.IF CurrentNinja.ActiveInventory == 1		;Sword
							push	04h
							push	eax
							call	GiveDamage
						.ELSE
							push	02h
							push	eax
							call	GiveDamage
						.ENDIF
						pop	eax
					.ELSEIF CurrentNinja.State == NINJA_STATE_PUNCHING
						push	eax
						.IF CurrentNinja.ActiveInventory == 1		;Sword
							push	02h
							push	eax
							call	GiveDamage
						.ELSE
							push	01h
							push	eax
							call	GiveDamage
						.ENDIF
						pop	eax
					.ENDIF

				.ENDIF
			.ENDIF

		.ENDIF
	.ENDIF

	popa
	ret
IsEnemyCollision	endp