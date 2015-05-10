AnimationIncreaseFrame	proc	STDCALL
	pusha

	call	CalcNinjaAnimOffset
	call	CalcNinjaFrame			; esi -> Animation set

	movzx	eax, CurrentNinja.Frame
	inc	eax
	add	esi, eax				; eax -> new frame

	.IF byte ptr [esi] == 0FFh
		; End of Animation, for now just reset all anims
		mov	CurrentNinja.Frame, 0h
	.ELSE
		cmp	byte ptr [esi], 09h
		je	animation_attackcheck
		cmp	byte ptr [esi], 18h
		je	animation_attackcheck
		cmp	byte ptr [esi], 15h
		je	animation_attackcheck
		cmp	byte ptr [esi], 16h
		je	animation_attackcheck
		cmp	byte ptr [esi], 0Bh
		jne	animation_skipattackcheck
animation_attackcheck:
		pusha
		call	AttackCollisionNinja
		popa
animation_skipattackcheck:

		.IF byte ptr [esi] == 10h
			pusha
			call	PickupCollisionNinja
			popa
		.ELSEIF byte ptr [esi] == 14h
			push	eax

			movzx	ebx, CurrentNinja.ActiveInventory
animation_switchingweapon_rescan:
			inc	ebx

			.IF ebx == Inventory_Count
				xor	ebx, ebx
			.ELSE
				mov	eax, ebx
				mov	ecx, Inventory_Len
				mul	ecx
				add	eax, offset InventoryList
				cmp	[eax].QtyHeld, 00h
				je	animation_switchingweapon_rescan
			.ENDIF
			mov	CurrentNinja.ActiveInventory, bl
			mov	ResetToNinja.ActiveInventory, bl

			pop	eax
		.ENDIF

		mov	CurrentNinja.Frame, ax
	.ENDIF

	popa
	ret
AnimationIncreaseFrame	endp


AnimationIncreaseFrameEnemy		proc	STDCALL, iEnemy:DWORD
	mov	ebx, iEnemy
	pusha

	push	ebx

	push	ebx
	call	CalcEnemyAnimOffset			; esi -> Animation group

	pop	ebx					; ebx == Enemy

	mov	eax, CurrentNinja.ScreenID
	mov	ecx, MapRoom_Len
	mul	ecx
	add	eax, offset Jane_Map

	push	ebx
	push	eax

	.IF ebx == 1
		movzx	ecx, [eax].enemy1_FrameIdx
		push	ecx

		movzx	edi, [eax].enemy1_Facing
		push	edi
		movzx	edi, [eax].enemy1_State
		push	edi
	.ELSE
		movzx	ecx, [eax].enemy2_FrameIdx
		push	ecx

		movzx	edi, [eax].enemy2_Facing
		push	edi
		movzx	edi, [eax].enemy2_State
		push	edi
	.ENDIF
	call	CalcEnemyFrame			; esi -> Animation set

	pop	ecx
	inc	ecx
	add	esi, ecx

	pop	eax
	pop	ebx

	.IF byte ptr [esi] == 0FFh
		; End of Animation, for now just reset all anims
		.IF ebx == 1
			mov	[eax].enemy1_FrameIdx, 0
			.IF [eax].enemy1_State == NINJA_STATE_DYING
				mov	[eax].enemy1_State, NINJA_STATE_DEAD
			.ELSEIF [eax].enemy1_State != NINJA_STATE_DEAD
				mov	[eax].enemy1_State, NINJA_STATE_WALKING
			.ENDIF
		.ELSE
			mov	[eax].enemy2_FrameIdx, 0
			.IF [eax].enemy2_State == NINJA_STATE_DYING
				mov	[eax].enemy2_State, NINJA_STATE_DEAD
			.ELSEIF [eax].enemy2_State != NINJA_STATE_DEAD
				mov	[eax].enemy2_State, NINJA_STATE_WALKING
			.ENDIF
		.ENDIF
	.ELSE
		.IF ebx == 1
			mov	[eax].enemy1_FrameIdx, cx
		.ELSE
			mov	[eax].enemy2_FrameIdx, cx
		.ENDIF
	.ENDIF

	popa
	ret
AnimationIncreaseFrameEnemy		endp