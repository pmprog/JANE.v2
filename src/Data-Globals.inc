	.data

rectPlyHealth	RECT	<GAME_HEALTH_PLY_LEFT, GAME_HEALTH_PLY_TOP, GAME_HEALTH_PLY_LEFT + GAME_HEALTH_PLY_WIDTH, GAME_HEALTH_PLY_TOP + GAME_HEALTH_PLY_HEIGHT>

rectEn1Health	RECT	<GAME_HEALTH_E1_LEFT, GAME_HEALTH_E1_TOP, GAME_HEALTH_E1_LEFT + GAME_HEALTH_E1_WIDTH, GAME_HEALTH_E1_TOP + GAME_HEALTH_E1_HEIGHT>
rectEn2Health	RECT	<GAME_HEALTH_E2_LEFT, GAME_HEALTH_E2_TOP, GAME_HEALTH_E2_LEFT + GAME_HEALTH_E2_WIDTH, GAME_HEALTH_E2_TOP + GAME_HEALTH_E2_HEIGHT>

rectTransition	RECT	<NINJA_FRAME_WIDTH, NINJA_FRAME_HEIGHT, NINJA_FRAME_WIDTH + GAME_ACTION_WIDTH, NINJA_FRAME_HEIGHT>

	.data?

engineDC		dd	?

bufferDC		dd	?
bufferBMP		dd	?

actionDC		dd	?
actionBMP		dd	?

copierDC		dd	?

userintBMP		dd	?

bitmapDimensions	BITMAP	?

debugMode		db	?

brushTmp		dd	?

jumpingFlags		db	?
sinkingFlags		dd	?

sinkingFrame		dd	?


randomSeed		dd	?

logic_switch_A	db	?
logic_switch_B	db	?