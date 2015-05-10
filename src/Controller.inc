ControlHandler	proc	STDCALL, paramA:DWORD

	mov	ah, CurrentNinja.State

	.IF ah == NINJA_STATE_DYING
		call	AnimationIncreaseFrame
		.IF CurrentNinja.Frame == 0
			push	NINJA_STATE_DEAD
			call	SetNinjaState
		.ENDIF

	.ELSEIF ah == NINJA_STATE_DEAD

	.ELSEIF ah == NINJA_STATE_HURT
		call	AnimationIncreaseFrame
		.IF CurrentNinja.Frame == 0
			push	NINJA_STATE_STANDING
			call	SetNinjaState
		.ENDIF

	.ELSEIF ah == NINJA_STATE_JUMPING
		call	AnimationIncreaseFrame

		movzx	eax, jumpingFlags
		push	eax
		call	MoveNinja

		.IF CurrentNinja.Frame == 0
			push	NINJA_STATE_WALKING
			call	SetNinjaState
			push	0
			call	MoveNinja
		.ENDIF

	.ELSEIF ah == NINJA_STATE_SWITCHING
		call	AnimationIncreaseFrame
		.IF CurrentNinja.Frame == 0
			push	NINJA_STATE_STANDING
			call	SetNinjaState
		.ENDIF

	.ELSEIF ah == NINJA_STATE_KICKING
		call	AnimationIncreaseFrame
		.IF CurrentNinja.Frame == 0
			push	NINJA_STATE_STANDING
			call	SetNinjaState
		.ENDIF

	.ELSEIF ah == NINJA_STATE_PUNCHING
		call	AnimationIncreaseFrame
		.IF CurrentNinja.Frame == 0
			push	NINJA_STATE_STANDING
			call	SetNinjaState
		.ENDIF

	.ELSEIF ah == NINJA_STATE_SLASHING
		call	AnimationIncreaseFrame
		.IF CurrentNinja.Frame == 0
			push	NINJA_STATE_STANDING
			call	SetNinjaState
		.ENDIF

	.ELSEIF ah == NINJA_STATE_JABING
		call	AnimationIncreaseFrame
		.IF CurrentNinja.Frame == 0
			push	NINJA_STATE_STANDING
			call	SetNinjaState
		.ENDIF

	.ELSEIF ah == NINJA_STATE_PARRY
		call	AnimationIncreaseFrame
		.IF CurrentNinja.Frame == 0
			push	NINJA_STATE_STANDING
			call	SetNinjaState
		.ENDIF

	.ELSEIF ah == NINJA_STATE_SINKING

	.ELSEIF ah == NINJA_STATE_DROWNING

	.ELSE

		mov	al, CurrentNinja.Control

		.IF al == NINJA_CONTROL_FIRE
			push	NINJA_STATE_STANDING
			call	SetNinjaState
		.ELSE
			mov	bl, al
			and	bl, NINJA_CONTROL_FIRE
			.IF bl == NINJA_CONTROL_FIRE

				; User is pushing direction with fire button
				not	bl
				and	al, bl			; al == Direction without fire button flag

				.IF ah == NINJA_STATE_STANDING

					.IF al == NINJA_CONTROL_DOWN
						push	NINJA_STATE_KICKING
						call	SetNinjaState

					.ELSEIF al == NINJA_CONTROL_UP
						push	NINJA_STATE_JABING
						call	SetNinjaState

					.ELSEIF al == NINJA_CONTROL_LEFT
						.IF CurrentNinja.Facing == NINJA_FACING_NORTH
							push	NINJA_STATE_PUNCHING
							call	SetNinjaState
						.ELSEIF CurrentNinja.Facing == NINJA_FACING_EAST
							push	NINJA_STATE_PUNCHING
							call	SetNinjaState
						.ELSE
							push	NINJA_STATE_SLASHING
							call	SetNinjaState
						.ENDIF
					.ELSEIF al == NINJA_CONTROL_RIGHT
						.IF CurrentNinja.Facing == NINJA_FACING_SOUTH
							push	NINJA_STATE_PUNCHING
							call	SetNinjaState
						.ELSEIF CurrentNinja.Facing == NINJA_FACING_WEST
							push	NINJA_STATE_PUNCHING
							call	SetNinjaState
						.ELSE
							push	NINJA_STATE_SLASHING
							call	SetNinjaState
						.ENDIF

					.ELSEIF al == NINJA_CONTROL_RIGHT + NINJA_CONTROL_DOWN
							push	NINJA_STATE_PARRY
							call	SetNinjaState
					.ELSEIF al == NINJA_CONTROL_LEFT + NINJA_CONTROL_DOWN
							push	NINJA_STATE_PARRY
							call	SetNinjaState
					.ENDIF
				.ELSE

					mov	jumpingFlags, al
					push	NINJA_STATE_JUMPING
					call	SetNinjaState

				.ENDIF			

			.ELSE

				; User is pushing direction without fire button
				cmp	ah, NINJA_STATE_WALKING
				je	control_nobutton_control
				cmp	ah, NINJA_STATE_STANDING
				jne	control_nobutton_finished
control_nobutton_control:

				;;; Ignore duel directions for now
				.IF al == NINJA_CONTROL_UP
					.IF CurrentNinja.Facing != NINJA_FACING_SOUTH
						mov	CurrentNinja.Facing, NINJA_FACING_NORTH
					.ENDIF
				.ELSEIF al == NINJA_CONTROL_LEFT
					.IF CurrentNinja.Facing != NINJA_FACING_EAST
						mov	CurrentNinja.Facing, NINJA_FACING_WEST
					.ENDIF
				.ELSEIF al == NINJA_CONTROL_RIGHT
					.IF CurrentNinja.Facing != NINJA_FACING_WEST
						mov	CurrentNinja.Facing, NINJA_FACING_EAST
					.ENDIF
				.ELSEIF al == NINJA_CONTROL_DOWN
					.IF CurrentNinja.Facing != NINJA_FACING_NORTH
						mov	CurrentNinja.Facing, NINJA_FACING_SOUTH
					.ENDIF
				.ENDIF

				.IF al != 00h

					push	eax

					movzx	ecx, al
					push	ecx
					call	MoveNinja

					pop	eax

					.IF ah == NINJA_STATE_STANDING
						push	NINJA_STATE_WALKING
						call	SetNinjaState
					.ELSE
						call	AnimationIncreaseFrame
					.ENDIF
				.ENDIF

control_nobutton_finished:

			.ENDIF
		.ENDIF
	.ENDIF

	ret
ControlHandler	endp