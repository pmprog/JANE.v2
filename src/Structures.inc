NinjaGraphics	struct
	offsStand		dd	?
	offsKick		dd	?
	offsJump		dd	?
	offsJab		dd	?
	offsSlash		dd	?
	offsParry		dd	?
	offsPunch		dd	?
	offsSwitch		dd	?
	offsHurt		dd	?
	offsDying		dd	?
	offsDead		dd	?
	offsClimb		dd	?
	offsNorthWalkF	dd	?
	offsNorthWalkB	dd	?
	offsEastWalkF		dd	?
	offsEastWalkB		dd	?
	offsSouthWalkF	dd	?
	offsSouthWalkB	dd	?
	offsWestWalkF		dd	?
	offsWestWalkB		dd	?
NinjaGraphics	ends

Ninja		struct
	ScreenX		dd	?
	ScreenY		dd	?
	ScreenID		dd	?

	State			db	?	; NINJA_STATE_*
	Control		db	?	; NINJA_CONTROL_* mask
	Facing			db	?	; NINJA_FACING_*

	Health			dw	?	; Max = GAME_MAX_HEALTH

	ActiveInventory	db	?	; Currently held item, also source of frames

	Frame			dw	?	; Active Frame Number

	SinkCount		dd	?

Ninja		ends
Ninja_Len	equ	4+4+4 + 1+1+1 + 2 + 1 + 2 + 4

Inventory	struct
	NinjaFrameset		dw	?	; Bitmap ptr for Ninja (ADD offset bmp_Skins)
	InventoryGfx		dw	?	; Bitmap ptr for display in UI (ADD offset bmp_Inv)

	QtyHeld		db	?	; Qty / Time Left for ninja magic
	Type			db	?	; INVENTORY_TYPE_*
Inventory	ends
Inventory_Len	equ	2+2 + 1+1

Object		struct
	ScreenX		dd	?
	ScreenY		dd	?

	AttackFunction	dd	?	; Address of function to run if hit/kicked
	UpdateFunction	dd	?	; Address of function on Tick

	ObjectGfx		dw	?	; Bitmap of item (ADD offset bmp_Objects)
	Frame			dw	?	; Active Frame
	FrameWidth		dw	?	; Width of frames (height is full size)
	FrameCount		dw	?	; Number of frames in bitmap

	Collect_InvIdx	db	?
	Collect_Qty		db	?	; 0 = Not pickup
	
Object		ends
Object_Len	equ	4+4 + 4+4 + 2+2+2+2 + 1+1

Enemy		struct
	enemy_ScreenX			dd	?
	enemy_ScreenY			dd	?
	enemy_Frameset		dw	?	; Bitmap for Enemy (ADD offset bmp_Skins)
	enemy_FrameIdx		dw	?
	enemy_State			db	?	; NINJA_STATE_*
	enemy_LivesLeft		db	?	; Set to 0FFh for no enemy
	enemy_Facing			db	?	; NINJA_FACING_*
	enemy_Health			dw	?	; Max = GAME_MAX_HEALTH
	enemy_ActiveInventory	db	?	; ENEMY_INVENTORY_*
Enemy		ends
Enemy_Len	equ	4+4 + 2+2 + 1+1+1 + 2 + 1

MapRoom	struct
	BackgroundGfx			dw	?	; Background graphic

	enemy1_ScreenX		dd	?
	enemy1_ScreenY		dd	?
	enemy1_Frameset		dw	?	; Bitmap for Enemy (ADD offset bmp_Skins)
	enemy1_FrameIdx		dw	?
	enemy1_State			db	?	; NINJA_STATE_*
	enemy1_LivesLeft		db	?	; Set to 0FFh for no enemy
	enemy1_Facing			db	?	; NINJA_FACING_*
	enemy1_Health			dw	?	; Max = GAME_MAX_HEALTH
	enemy1_ActiveInventory	db	?	; ENEMY_INVENTORY_*

	enemy2_ScreenX		dd	?
	enemy2_ScreenY		dd	?
	enemy2_Frameset		dw	?	; Bitmap for Enemy (ADD offset bmp_Skins)
	enemy2_FrameIdx		dw	?
	enemy2_State			db	?	; NINJA_STATE_*
	enemy2_LivesLeft		db	?	; Set to 0FFh for no enemy
	enemy2_Facing			db	?	; NINJA_FACING_*
	enemy2_Health			dw	?	; Max = GAME_MAX_HEALTH
	enemy2_ActiveInventory	db	?	; ENEMY_INVENTORY_*

	screen_ObjectList		dd	?	; Points to list of object structures
MapRoom	ends
MapRoom_Len	equ	2 + Enemy_Len+Enemy_Len + 4