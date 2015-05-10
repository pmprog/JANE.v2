
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Draw background
	mov	eax, CurrentNinja.ScreenID
	mov	ecx, MapRoom_Len
	mul	ecx
	add	eax, offset Jane_Map
	movzx	eax, [eax].BackgroundGfx
	shl	eax, 2h				; *4
	add	eax, offset bmp_MapScreens
	push	dword ptr [eax]
	push	copierDC
	call	SelectObject

	.IF debugMode == 0
		push	SRCCOPY
		push	0
		push	0
		push	copierDC
		push	GAME_ACTION_HEIGHT
		push	GAME_ACTION_WIDTH
		push	NINJA_FRAME_HEIGHT
		push	NINJA_FRAME_WIDTH
		push	actionDC
		call	BitBlt
	.ELSE
		push	SRCCOPY
		push	GAME_ACTION_HEIGHT
		push	0
		push	copierDC
		push	GAME_ACTION_HEIGHT
		push	GAME_ACTION_WIDTH
		push	NINJA_FRAME_HEIGHT
		push	NINJA_FRAME_WIDTH
		push	actionDC
		call	BitBlt
	.ENDIF

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Draw Scenery above ninja
	push	0
	call	PaintScenery						; Draw initial scenery

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Draw Enemies above ninja
	push	0
	call	GfxDrawEnemyBelow

	push	eax							; Subsitute this for lowest enemy on screen
	call	PaintScenery						; Draw 2nd layer scenery

INCLUDE Gfx-Ninja.inc

	mov	eax, CurrentNinja.ScreenY
	add	eax, NINJA_FRAME_OFFSET_Y
	push	eax
	push	eax
	call	PaintScenery						; Paint all items below Ninja

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Draw Enemies below ninja
	call	GfxDrawEnemyBelow

	push	eax							; Subsitute this for lowest enemy on screen
	call	PaintScenery						; Draw overlayed scenery

	movzx	eax, debugMode
	or	eax,eax
	jz	drawaction_skipninjacollisionpoint

	push	0FFFFFFh
	mov	eax, CurrentNinja.ScreenY
	add	eax, NINJA_FRAME_OFFSET_Y
	push	eax
	mov	eax, CurrentNinja.ScreenX
	add	eax, NINJA_FRAME_OFFSET_X
	push	eax
	push	actionDC
	call	SetPixel

drawaction_skipninjacollisionpoint:

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Draw Room Transition
	.IF rectTransition.rc_bottom != NINJA_FRAME_HEIGHT
		push	0000000h
		call	CreateSolidBrush
		mov	brushTmp, eax

		push	eax
		push	offset rectTransition
		push	actionDC
		call	FillRect

		push	brushTmp
		call	DeleteObject

		.IF rectTransition.rc_bottom != GAME_ACTION_HEIGHT + NINJA_FRAME_HEIGHT
			mov	eax, rectTransition.rc_bottom
			add	eax, 10h
			mov	rectTransition.rc_bottom, eax
		.ELSE
			.IF rectTransition.rc_top != GAME_ACTION_HEIGHT + NINJA_FRAME_HEIGHT
				mov	eax, rectTransition.rc_top
				add	eax, 10h
				mov	rectTransition.rc_top, eax
			.ELSE
				mov	rectTransition.rc_top, NINJA_FRAME_HEIGHT
				mov	rectTransition.rc_bottom, NINJA_FRAME_HEIGHT
			.ENDIF
		.ENDIF
	.ENDIF

	push	SRCCOPY
	push	NINJA_FRAME_HEIGHT
	push	NINJA_FRAME_WIDTH
	push	actionDC
	push	GAME_ACTION_HEIGHT
	push	GAME_ACTION_WIDTH
	push	GAME_ACTION_TOP
	push	GAME_ACTION_LEFT
	push	bufferDC
	call	BitBlt