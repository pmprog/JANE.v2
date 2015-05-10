	push	bmp_UserInterface
	push	copierDC
	call	SelectObject

	push	SRCCOPY
	push	0
	push	0
	push	copierDC
	push	GAME_SCREEN_HEIGHT
	push	GAME_SCREEN_WIDTH
	push	0
	push	0
	push	bufferDC
	call	BitBlt

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Simple Inventory Display
	movzx	eax, CurrentNinja.ActiveInventory
	shl	eax, 2					; *4
	add	eax, offset bmp_Inventory		; eax -> bitmap handle
	push	dword ptr [eax]
	push	copierDC
	call	SelectObject

	push	SRCCOPY
	push	0
	push	0
	push	copierDC
	push	GAME_INVENTORY_HEIGHT
	push	GAME_INVENTORY_WIDTH
	push	GAME_INVENTORY_TOP
	push	GAME_INVENTORY_LEFT
	push	bufferDC
	call	BitBlt


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Ninja's Health
	push	COLOURS_ENERGY_NINJA
	call	CreateSolidBrush
	mov	brushTmp, eax

	mov	ebx, GAME_HEALTH_PLY_LEFT
	mov	rectPlyHealth.rc_left, ebx
	movzx	ecx, CurrentNinja.Health
	add	ebx, ecx
	mov	rectPlyHealth.rc_right, ebx

	push	eax
	push	offset rectPlyHealth
	push	bufferDC
	call	FillRect

	push	brushTmp
	call	DeleteObject

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Enemies' Health
	push	COLOURS_ENERGY_ENEMY
	call	CreateSolidBrush
	mov	brushTmp, eax

	mov	eax, CurrentNinja.ScreenID
	mov	ecx, MapRoom_Len
	mul	ecx
	add	eax, offset Jane_Map			; eax -> MapRoom structure
	mov	esi, eax				; esi -> MapRoom structure

	cmp	[esi].enemy1_LivesLeft, 0FFh
	je	gfxui_noenemyone

	mov	ebx, rectEn1Health.rc_left
	movzx	ecx, [esi].enemy1_Health
	add	ebx, ecx
	mov	rectEn1Health.rc_right, ebx

	push	brushTmp
	push	offset rectEn1Health
	push	bufferDC
	call	FillRect

gfxui_noenemyone:
	cmp	[esi].enemy2_LivesLeft, 0FFh
	je	gfxui_noenemytwo

	mov	ebx, rectEn2Health.rc_left
	movzx	ecx, [esi].enemy2_Health
	add	ebx, ecx
	mov	rectEn2Health.rc_right, ebx

	push	brushTmp
	push	offset rectEn2Health
	push	bufferDC
	call	FillRect

gfxui_noenemytwo:
	push	brushTmp
	call	DeleteObject
