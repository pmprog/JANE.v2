	.data

engineCLS	db	'JANE v2.0',0
engineICO	db	'AppIco',0

	.data?
engineClass		WNDCLASS	?
engineInstance	dd      	?
engineWnd		dd		?
engineMsg		MSG		?
enginePaint		PAINTSTRUCT	?

	.code

start:  push    0
	call	GetModuleHandleA			;Obtain the applications instance
	mov	engineInstance, eax

	push	offset engineICO
	push	engineInstance
	call	LoadIcon				;Load the Main window's icon and put it into the class struct
	mov	engineClass.w_hIcon,eax

	push	IDC_ARROW
	push	0
	call	LoadCursor				;Set standard cursors for the windows
	mov	engineClass.w_hCursor,eax

	mov	engineClass.w_style, CS_HREDRAW + CS_VREDRAW + CS_DBLCLKS
	mov	engineClass.w_lpfnWndProc, offset WndProc
	mov	engineClass.w_lpszMenuName,offset engineCLS
	mov	engineClass.w_lpszClassName,offset engineCLS
	mov	engineClass.w_hbrBackground, COLOR_WINDOW

	push	offset engineClass
	call	RegisterClassA

	push	0
	push	engineInstance
	push	0
	push	0
	push	GAME_SCREEN_HEIGHT
	push	GAME_SCREEN_WIDTH
	push	0
	push	0
	push	WS_VISIBLE + WS_SYSMENU
	push	offset engineCLS
	push	offset engineCLS
	push	0
	call	CreateWindowEx
	mov	engineWnd,eax

	push	eax
	call	GetWindowDC
	mov	engineDC, eax

	push	eax
	call	CreateCompatibleDC
	mov	bufferDC, eax

	push	GAME_SCREEN_HEIGHT
	push	GAME_SCREEN_WIDTH
	push	engineDC
	call	CreateCompatibleBitmap
	mov	bufferBMP, eax

	push	eax
	push	bufferDC
	call	SelectObject

	push	engineDC
	call	CreateCompatibleDC
	mov	actionDC, eax

	push	GAME_ACTION_HEIGHT + NINJA_FRAME_HEIGHT
	push	GAME_ACTION_WIDTH + NINJA_FRAME_WIDTH
	push	engineDC
	call	CreateCompatibleBitmap
	mov	actionBMP, eax

	push	eax
	push	actionDC
	call	SelectObject

	push	engineDC
	call	CreateCompatibleDC
	mov	copierDC, eax

	call	OnLoad

	push	0
	push	20h
	push	TIMER_PAINTER
	push	engineWnd
	call	SetTimer

	push	0
	push	20h
	push	TIMER_ANIMATOR
	push	engineWnd
	call	SetTimer

;	push	0
;	push	0
;	push	0
;;	push	offset ControlHandler
;	push	offset AnimationControl
;	push	0
;	push	0
;	call	CreateThread

Messagz:
        push    0 0 0
        push    offset engineMsg
        call    GetMessage
        cmp     ax,0
        je      finn

        push    offset engineMsg
        call    TranslateMessage

        push    offset engineMsg
        call    DispatchMessage

        jmp     Messagz

finn:   call    ExitProcess


;/////////////////////////////////////////////////////////////////////////
WndProc proc STDCALL, hwnd:DWORD, wmsg:DWORD, wparam:DWORD, lparam:DWORD

	mov	eax,wmsg
	mov	ebx, wparam

	pusha

	.IF ax==WM_DESTROY
		call	OnExit

		push	0
		call	PostQuitMessage
		ret
	.ELSEIF ax==WM_TIMER
		push	ebx
		call	OnTimer
	.ELSEIF ax==WM_KEYDOWN
		push	ebx
		call	KeyDown
	.ELSEIF ax==WM_KEYUP
		push	ebx
		call	KeyUp
;	.ELSEIF ax==WM_PAINT
;		push	offset enginePaint
;		push	hwnd
;		call	BeginPaint
;
;		push	offset enginePaint
;		push	hwnd
;		call	EndPaint
        .ELSE
		popa
		call	DefWindowProc, hwnd,wmsg,wparam,lparam
		ret
	.ENDIF

	popa

	xor eax,eax
	ret

WndProc endp
;/////////////////////////////////////////////////////////////////////////


RandomNumber	proc	STDCALL, SeedExtra:DWORD
	call	GetTickCount
	mov	ebx, SeedExtra
	xor	eax, ebx
	mov	ebx, randomSeed
	xor	eax, ebx
	rol	eax, 3h
	mov	randomSeed, eax
	ret
RandomNumber	endp