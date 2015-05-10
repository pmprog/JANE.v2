	.code

PostHit	proc	STDCALL

		mov	posto.AttackFunction, 0h

		mov	eax, posto.ScreenX
		add	eax, 10h
		mov	posto.ScreenX, eax

		mov	eax, posto.ScreenY
		dec	eax
		dec	eax
		dec	eax
		dec	eax
		mov	posto.ScreenY, eax

		mov	logic_switch_A, 1h

		.IF logic_switch_B == 1h
			call	LogicActivate
		.ENDIF
	ret
PostHit	endp

PostHitB	proc	STDCALL

		mov	postb.AttackFunction, 0h

		mov	eax, postb.ScreenX
		sub	eax, 10h
		mov	postb.ScreenX, eax

		mov	eax, postb.ScreenY
		dec	eax
		dec	eax
		dec	eax
		dec	eax
		mov	postb.ScreenY, eax

		mov	logic_switch_B, 1h

		.IF logic_switch_A == 1h
			call	LogicActivate
		.ENDIF
	ret
PostHitB	endp

LogicActivate	proc	STDCALL
	mov	room_water.BackgroundGfx, 5		; Jumpable water
	ret
LogicActivate	endp