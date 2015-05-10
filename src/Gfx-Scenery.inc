PaintScenery		proc	STDCALL, greaterThanY:DWORD
	mov	eax, greaterThanY
	pusha

;;;;;;;;;;;;;;;;;;;;;;;;;;; Paint items where ScreenY + Height > greaterThanY
	mov	ebx, CurrentNinja.ScreenID
	xchg	ebx, eax				; ebx == Y start
	mov	ecx, MapRoom_Len
	mul	ecx
	add	eax, offset Jane_Map			; eax -> screen data
	mov	esi, [eax].screen_ObjectList	; esi -> list of scenery

scenery_scanloop:
	cmp	byte ptr [esi], 00h
	je	scenery_scanover			; Finish scenery

	movzx	edx, [esi].ObjectGfx
	shl	edx, 2h
	add	edx, offset height_Objects		; edx == Height of Object
	mov	eax, [esi].ScreenY
	add	eax, dword ptr [edx]
	add	eax, NINJA_FRAME_HEIGHT
	cmp	eax, ebx
	jl	scenery_dontdrawme

	mov	edi, [esi].ScreenY			; edi == Screen Y
	add	edi, NINJA_FRAME_HEIGHT
	mov	ecx, [esi].ScreenX			; ecx == Screen X
	add	ecx, NINJA_FRAME_WIDTH

	movzx	eax, [esi].ObjectGfx
	shl	eax, 2h
	add	eax, offset bmp_Objects		; eax -> bitmap handle

	pusha

	push	offset bitmapDimensions
	push	BITMAP_
	push	dword ptr [eax]
	call	GetObject				; bitmapDimensions holds dimensions

	popa
	pusha

	push	dword ptr [eax]
	push	copierDC
	call	SelectObject

	popa

scenery_debug_stuff:
	pusha
	movzx	eax, debugMode
	or	eax,eax
	jz	scenery_debug_stuff_end

	push	0FFFFFFh
	mov	eax, [esi].ScreenY
	add	eax, NINJA_FRAME_HEIGHT
	add	eax, bitmapDimensions.bm_bmHeight
	inc	eax
	push	eax
	mov	eax, bitmapDimensions.bm_bmWidth
	shr	eax, 1h
	add	eax, [esi].ScreenX
	add	eax, NINJA_FRAME_WIDTH
	push	eax
	push	actionDC
	call	SetPixel
	popa
scenery_debug_stuff_end:

	push	COLOURS_SCENERY_TRANS
	push	bitmapDimensions.bm_bmHeight
	push	bitmapDimensions.bm_bmWidth
	push	0
	push	0
	push	copierDC
	push	bitmapDimensions.bm_bmHeight
	push	bitmapDimensions.bm_bmWidth
	push	edi
	push	ecx
	push	actionDC
	call	TransparentBlt

scenery_dontdrawme:
	add	esi, Object_Len
	jmp	scenery_scanloop

scenery_scanover:
	popa
	ret
PaintScenery		endp