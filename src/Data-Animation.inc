	.data

Animation_EmptyHand_Player	NinjaGraphics	< offset Animation_Ninja_Stand, offset Animation_Ninja_Kick, offset Animation_Ninja_Jump, offset Animation_Ninja_Jab, offset Animation_Ninja_EmptyHanded_Slash, offset Animation_Ninja_Pickup, offset Animation_Ninja_EmptyHanded_Punch, offset Animation_Ninja_Switch, offset Animation_Ninja_Hurt, offset Animation_Ninja_Dying, offset Animation_Ninja_Dead, offset Animation_Ninja_Climbing, offset Animation_Ninja_NorthForwards, offset Animation_Ninja_NorthBackwards, offset Animation_Ninja_EastForwards, offset Animation_Ninja_EastBackwards, offset Animation_Ninja_SouthForwards, offset Animation_Ninja_SouthBackwards, offset Animation_Ninja_WestForwards, offset Animation_Ninja_WestBackwards >

Animation_SwordHand_Player	NinjaGraphics	< offset Animation_Ninja_Stand, offset Animation_Ninja_Kick, offset Animation_Ninja_Jump, offset Animation_Ninja_Jab, offset Animation_Ninja_SwordHanded_Slash, offset Animation_Ninja_Pickup, offset Animation_Ninja_SwordHanded_Punch, offset Animation_Ninja_Switch, offset Animation_Ninja_Sword_Hurt, offset Animation_Ninja_Sword_Dying, offset Animation_Ninja_Sword_Dead, offset Animation_Ninja_Climbing, offset Animation_Ninja_NorthForwards, offset Animation_Ninja_NorthBackwards, offset Animation_Ninja_EastForwards, offset Animation_Ninja_EastBackwards, offset Animation_Ninja_SouthForwards, offset Animation_Ninja_SouthBackwards, offset Animation_Ninja_WestForwards, offset Animation_Ninja_WestBackwards >

Animation_EmptyHand_Enemy	NinjaGraphics < offset Animation_Enemy_Stand, offset Animation_Enemy_Kick, 0, offset Animation_Enemy_Jab, offset Animation_Enemy_Kick, 0, Animation_Enemy_EmptyHanded_Punch, 0, offset Animation_Enemy_Hurt, offset Animation_Enemy_Dying, offset Animation_Enemy_Dead, 0, offset Animation_Enemy_NorthForwards, offset Animation_Enemy_NorthBackwards, offset Animation_Enemy_EastForwards, offset Animation_Enemy_EastBackwards, offset Animation_Enemy_SouthForwards, offset Animation_Enemy_SouthBackwards, offset Animation_Enemy_WestForwards, offset Animation_Enemy_WestBackwards >
Animation_SwordHand_Enemy	NinjaGraphics < offset Animation_Enemy_Stand, offset Animation_Enemy_Kick, 0, offset Animation_Enemy_Jab, offset Animation_Enemy_SwordHanded_Slash, 0, Animation_Enemy_SwordHanded_Punch, 0, offset Animation_Enemy_SHurt, offset Animation_Enemy_SDying, offset Animation_Enemy_SDead, 0, offset Animation_Enemy_NorthForwards, offset Animation_Enemy_NorthBackwards, offset Animation_Enemy_EastForwards, offset Animation_Enemy_EastBackwards, offset Animation_Enemy_SouthForwards, offset Animation_Enemy_SouthBackwards, offset Animation_Enemy_WestForwards, offset Animation_Enemy_WestBackwards >

Animation_Ninja_Stand				db	08h, 0FFh
Animation_Ninja_EmptyHanded_Punch			db	09h, 09h, 09h, 09h, 09h, 09h, 0FFh
Animation_Ninja_SwordHanded_Punch			db	17h, 17h, 17h, 17h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 17h, 0FFh
Animation_Ninja_Jab					db	09h, 09h, 09h, 0FFh
Animation_Ninja_EmptyHanded_Slash			db	09h, 09h, 09h, 09h, 09h, 09h, 0FFh
Animation_Ninja_SwordHanded_Slash			db	15h, 15h, 15h, 15h, 16h, 16h, 16h, 16h, 0FFh
Animation_Ninja_Kick					db	0Ah, 0Ah, 0Bh, 0Bh, 0Bh, 0Ah, 0Ah, 0FFh
Animation_Ninja_Jump					db	0Ch, 0Dh, 0Dh, 0Eh, 0Eh, 0Eh, 0Fh, 0Fh, 0Ch, 0FFh
Animation_Ninja_Switch				db	11h, 12h, 13h, 14h, 15h, 0FFh
Animation_Ninja_Pickup				db	10h, 10h, 10h, 10h, 10h, 10h, 10h, 10h, 10h, 10h, 0FFh
Animation_Ninja_Hurt					db	16h, 16h, 16h, 16h, 0FFh
Animation_Ninja_Sword_Hurt				db	1Ah, 1Ah, 1Ah, 1Ah, 0FFh
Animation_Ninja_Dying				db	16h, 16h, 16h, 17h, 17h, 17h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 0FFh
Animation_Ninja_Sword_Dying				db	1Ah, 1Ah, 1Ah, 1Bh, 1Bh, 1Bh, 1Ch, 1Ch, 1Ch, 1Ch, 1Ch, 1Ch, 1Ch, 1Ch, 0FFh
Animation_Ninja_Climbing				db	19h, 1Bh, 1Ah, 1Bh, 0FFh
Animation_Ninja_NorthForwards			db	00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 0FFh
Animation_Ninja_NorthBackwards			db	07h, 06h, 05h, 04h, 03h, 02h, 01h, 00h, 0FFh
Animation_Ninja_SouthForwards			db	00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 0FFh
Animation_Ninja_SouthBackwards			db	07h, 06h, 05h, 04h, 03h, 02h, 01h, 00h, 0FFh
Animation_Ninja_EastForwards			db	07h, 06h, 05h, 04h, 03h, 02h, 01h, 00h, 0FFh
Animation_Ninja_EastBackwards			db	00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 0FFh
Animation_Ninja_WestForwards			db	07h, 06h, 05h, 04h, 03h, 02h, 01h, 00h, 0FFh
Animation_Ninja_WestBackwards			db	00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 0FFh
Animation_Ninja_Dead					db	18h, 0FFh
Animation_Ninja_Sword_Dead				db	1Ch, 0FFh

Animation_Enemy_Stand				db	08h, 0FFh
Animation_Enemy_EmptyHanded_Punch			db	09h, 09h, 09h, 09h, 09h, 09h, 08h, 08h, 0FFh
Animation_Enemy_SwordHanded_Punch			db	0Fh, 0Fh, 10h, 10h, 10h, 11h, 11h, 11h, 10h, 10h, 0Fh, 08h, 08h, 0FFh
Animation_Enemy_Jab					db	09h, 09h, 09h, 08h, 08h, 0FFh
;Animation_Enemy_EmptyHanded_Slash			db	09h, 09h, 09h, 09h, 09h, 09h, 0FFh
Animation_Enemy_SwordHanded_Slash			db	0Ch, 0Ch, 0Ch, 0Dh, 0Dh, 0Dh, 0Eh, 0Eh, 0Eh, 08h, 08h, 0FFh
Animation_Enemy_Kick					db	0Ah, 0Ah, 0Bh, 0Bh, 0Bh, 0Ah, 0Ah, 08h, 08h, 0FFh
Animation_Enemy_Hurt					db	0Ch, 0Ch, 0FFh
Animation_Enemy_Dying				db	0Ch, 0Ch, 0Ch, 0Dh, 0Dh, 0Dh, 0Eh, 0FFh
Animation_Enemy_Dead					db	0Eh, 0FFh
Animation_Enemy_SHurt				db	12h, 12h, 0FFh
Animation_Enemy_SDying				db	12h, 12h, 12h, 13h, 13h, 13h, 14h, 0FFh
Animation_Enemy_SDead				db	14h, 0FFh
Animation_Enemy_NorthForwards			db	00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 0FFh
Animation_Enemy_NorthBackwards			db	07h, 06h, 05h, 04h, 03h, 02h, 01h, 00h, 0FFh
Animation_Enemy_SouthForwards			db	00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 0FFh
Animation_Enemy_SouthBackwards			db	07h, 06h, 05h, 04h, 03h, 02h, 01h, 00h, 0FFh
Animation_Enemy_EastForwards			db	07h, 06h, 05h, 04h, 03h, 02h, 01h, 00h, 0FFh
Animation_Enemy_EastBackwards			db	00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 0FFh
Animation_Enemy_WestForwards			db	07h, 06h, 05h, 04h, 03h, 02h, 01h, 00h, 0FFh
Animation_Enemy_WestBackwards			db	00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 0FFh
