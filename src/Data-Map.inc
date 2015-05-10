	.data

Jane_Map:
room_start	MapRoom	< 0, 0,0,0,0,0,0FFh,0,0,0, 0,0,0,0,0,0FFh,0,0,0, offset scenery_room1 >

room_tjunc	MapRoom	< 3, 0,0,0,0,0,0FFh,0,0,0, 0,0,0,0,0,0FFh,0,0,0, offset scenery_tjunc >
room_fight1	MapRoom	< 2, 265, 155,2,0,NINJA_STATE_WALKING,00h,NINJA_FACING_EAST,GAME_MAX_HEALTH,0, 0,0,0,0,0,0FFh,0,0,0, offset scenery_fight1 >
room_logic	MapRoom	< 0, 265, 155,2,0,NINJA_STATE_WALKING,00h,NINJA_FACING_EAST,GAME_MAX_HEALTH,0, 0,0,0,0,0,0FFh,0,0,0, offset scenery_logic >
room_sword	MapRoom	< 1, 0,0,0,0,0,0FFh,0,0,0, 0,0,0,0,0,0FFh,0,0,0, offset scenery_sword >

room_prewater	MapRoom	< 1, 380, 190,2,0,NINJA_STATE_WALKING,01h,NINJA_FACING_SOUTH,GAME_MAX_HEALTH,0, 0,0,0,0,0,0FFh,0,0,0, offset scenery_prewater >
room_water	MapRoom	< 4, 0,0,0,0,0,0FFh,0,0,0, 0,0,0,0,0,0FFh,0,0,0, offset scenery_water >

room_preduel	MapRoom	< 0, 265, 155,3,0,NINJA_STATE_WALKING,01h,NINJA_FACING_EAST,GAME_MAX_HEALTH,ENEMY_INVENTORY_SWORD, 0,0,0,0,0,0FFh,0,0,0, offset scenery_room1 >

room_duel	MapRoom	< 6, 385, 215,2,0,NINJA_STATE_WALKING,00h,NINJA_FACING_WEST,GAME_MAX_HEALTH,0, 120,195,3,0,NINJA_STATE_WALKING,00h,NINJA_FACING_NORTH,GAME_MAX_HEALTH,ENEMY_INVENTORY_SWORD, offset scenery_duel >
room_end	MapRoom	< 7, 360, 200,3,0,NINJA_STATE_WALKING,00h,NINJA_FACING_WEST,GAME_MAX_HEALTH,ENEMY_INVENTORY_SWORD, 120,195,3,0,NINJA_STATE_WALKING,00h,NINJA_FACING_NORTH,GAME_MAX_HEALTH,ENEMY_INVENTORY_SWORD, offset scenery_end  >

Jane_Map_Size		equ	(offset $ - offset Jane_Map) / MapRoom_Len


scenery_duel:
	Object		<220, -32, 0, 0, 0Bh, 1, 1, 0, 0, 0>
	Object		<270, -24, 0, 0, 0Bh, 1, 1, 0, 0, 0>
	Object		<320, -16, 0, 0, 0Bh, 1, 1, 0, 0, 0>
	Object		<370, -08, 0, 0, 0Bh, 1, 1, 0, 0, 0>
	Object		<420, 00, 0, 0, 0Bh, 1, 1, 0, 0, 0>

	Object		<10, GAME_ACTION_HEIGHT - 110, 0, 0, 0Ah, 1, 1, 0, 0, 0>
	Object		<200, GAME_ACTION_HEIGHT - 30, 0, 0, 01h, 1, 1, 0, 0, 0>
	db		00h

scenery_room1:
	Object		<40, 170, 0, 0, 5, 1, 1, 0, 0, 0>
	Object		<100, 20, 0, 0, 7, 1, 1, 0, 0, 0>
	Object		<330, 150, 0, 0, 1, 1, 1, 0, 0, 0>
	Object		<150, 40, 0, 0, 6, 1, 1, 0, 0, 0>
	Object		<10, 40, 0, 0, 0Ah, 1, 1, 0, 0, 0>
	Object		<130, 170, 0, 0, 0Ah, 1, 1, 0, 0, 0>
	db		00h

scenery_tjunc:
	Object		<20, 100, 0, 0, 03h, 1, 1, 0, 0, 0>
	Object		<15, 150, 0, 0, 01h, 1, 1, 0, 0, 0>
	Object		<50, 180, 0, 0, 01h, 1, 1, 0, 0, 0>
	Object		<360, 130, 0, 0, 0Ah, 1, 1, 0, 0, 0>
	Object		<250, 240, 0, 0, 00h, 1, 1, 0, 0, 0>
	Object		<340, 30, 0, 0, 0Bh, 1, 1, 0, 0, 0>
	Object		<130, 40, 0, 0, 06h, 1, 1, 0, 0, 0>
posto	Object		<230, 60, offset PostHit, 0, 02h, 1, 1, 0, 0, 0>
	Object		<240, 10, 0, 0, 0Bh, 1, 1, 0, 0, 0>
	db		00h

scenery_notdefined:
	db		00h

scenery_prewater:
	Object		<370, 35, 0, 0, 0Ah, 1, 1, 0, 0, 0>
	Object		<10, 105, 0, 0, 04h, 1, 1, 0, 0, 0>
	Object		<390, 180, 0, 0, 05h, 1, 1, 0, 0, 0>
	Object		<140, 30, 0, 0, 05h, 1, 1, 0, 0, 0>
	Object		<315, 205, 0, 0, 00h, 1, 1, 0, 0, 0>
	Object		<280, 210, 0, 0, 00h, 1, 1, 0, 0, 0>
	Object		<320, 225, 0, 0, 00h, 1, 1, 0, 0, 0>
	Object		<180, 60, 0, 0, 01h, 1, 1, 0, 0, 0>
	Object		<280, 100, 0, 0, 06h, 1, 1, 0, 0, 0>
	Object		<200, 265, 0, 0, 06h, 1, 1, 0, 0, 0>
	db		00h

scenery_fight1:
	Object		<80, 40, 0, 0, 0Bh, 1, 1, 0, 0, 0>
	Object		<180, 50, 0, 0, 01h, 1, 1, 0, 0, 0>
	Object		<260, 210, 0, 0, 01h, 1, 1, 0, 0, 0>
	Object		<300, 20, 0, 0, 05h, 1, 1, 0, 0, 0>
	Object		<40, 220, 0, 0, 05h, 1, 1, 0, 0, 0>
	Object		<5, 20, 0, 0, 07h, 1, 1, 0, 0, 0>
	Object		<360, 240, 0, 0, 06h, 1, 1, 0, 0, 0>
	db		00h

scenery_sword:
	Object		<330, 80, 0, 0, 0Dh, 1, 1, 0, 1, 1>
	Object		<370, 180, 0, 0, 03h, 1, 1, 0, 0, 0>
	Object		<220, 220, 0, 0, 03h, 1, 1, 0, 0, 0>
	Object		<330, 30, 0, 0, 08h, 1, 1, 0, 0, 0>
	Object		<180, 20, 0, 0, 00h, 1, 1, 0, 0, 0>
	Object		<40, 120, 0, 0, 01h, 1, 1, 0, 0, 0>
	Object		<10, 180, 0, 0, 07h, 1, 1, 0, 0, 0>
	db		00h

scenery_water:
	Object		<260, 140, 0, 0, 02h, 1, 1, 0, 0, 0>
	Object		<380, 175, 0, 0, 02h, 1, 1, 0, 0, 0>
	Object		<185, 210, 0, 0, 02h, 1, 1, 0, 0, 0>
	Object		<60, 175, 0, 0, 02h, 1, 1, 0, 0, 0>

	Object		<10, 20, 0, 0, 03h, 1, 1, 0, 0, 0>
	Object		<310, 40, 0, 0, 05h, 1, 1, 0, 0, 0>
	Object		<220, 80, 0, 0, 06h, 1, 1, 0, 0, 0>
	Object		<350, 10, 0, 0, 0Ah, 1, 1, 0, 0, 0>
	Object		<270, 90, 0, 0, 00h, 1, 1, 0, 0, 0>
	db		00h

scenery_end:
	Object		<310, 145, 0, 0, 0Ah, 1, 1, 0, 0, 0>
	Object		<240, 20, 0, 0, 00h, 1, 1, 0, 0, 0>
	Object		<30, -30, 0, 0, 0Bh, 1, 1, 0, 0, 0>
	db		00h

scenery_logic:
	Object		<115, 100, 0, 0, 02h, 1, 1, 0, 0, 0>
postb	Object		<180, 85, offset PostHitB, 0, 02h, 1, 1, 0, 0, 0>
	Object		<255, 65, 0, 0, 02h, 1, 1, 0, 0, 0>
	Object		<330, 45, 0, 0, 02h, 1, 1, 0, 0, 0>
	Object		<40, 170, 0, 0, 0Ah, 1, 1, 0, 0, 0>
	Object		<10, 40, 0, 0, 01h, 1, 1, 0, 0, 0>
	Object		<330, 90, 0, 0, 09h, 1, 1, 0, 0, 0>
	db		00h