	.data

res_UserInterface	db	'UI',0

res_Skins:
res_NinjaEmpty	db	'NINJA_EMPTY',0
res_NinjaSword	db	'NINJA_SWORD',0
res_EnemyEmpty	db	'ENEMY_EMPTY',0
res_EnemySword	db	'ENEMY_SWORD',0
		db	00h

res_Objects:
res_objBushL	db	'SCENERY_BUSH_L',0
res_objBushS	db	'SCENERY_BUSH_S',0
res_objPost	db	'SCENERY_POST',0
res_objRockH	db	'SCENERY_ROCK_H',0
res_objRockL	db	'SCENERY_ROCK_L',0
res_objRockM	db	'SCENERY_ROCK_M',0
res_objRockS	db	'SCENERY_ROCK_S',0
res_objRockT	db	'SCENERY_ROCK_T',0
res_objTreeB	db	'SCENERY_TREE_B',0
res_objTreeH	db	'SCENERY_TREE_H',0
res_objTreeL	db	'SCENERY_TREE_L',0
res_objTreeM	db	'SCENERY_TREE_M',0
res_objTreeS	db	'SCENERY_TREE_S',0
res_objSword	db	'PICKUP_SWORD',0
		db	00h

res_MapScreens:
res_mapL1	db	'MAP_L1',0
res_mapL2	db	'MAP_L2',0
res_mapST	db	'MAP_STR',0
res_mapT1	db	'MAP_T1',0
res_mapW1	db	'MAP_WATER1',0
res_mapW2	db	'MAP_WATER2',0
res_mapD1	db	'MAP_DUEL',0
res_mapC	db	'MAP_COMPLETE',0
		db	00h

res_Inventory:
res_invNone	db	'INV_NONE',0
res_invSword	db	'INV_SWORD',0
res_invKeySlv	db	'INV_KEYSLV',0
		db	00h

	.data?
bmp_UserInterface	dd	?

bmp_Skins:
bmp_NinjaEmpty	dd	?
bmp_NinjaSword	dd	?
bmp_EnemyEmpty	dd	?
bmp_EnemySword	dd	?

bmp_Objects:
bmp_objBushL		dd	?
bmp_objBushS		dd	?
bmp_objPost		dd	?
bmp_objRockH		dd	?
bmp_objRockL		dd	?
bmp_objRockM		dd	?
bmp_objRockS		dd	?
bmp_objRockT		dd	?
;bmp_objRockW		dd	?
bmp_objTreeB		dd	?
bmp_objTreeH		dd	?
bmp_objTreeL		dd	?
bmp_objTreeM		dd	?
bmp_objTreeS		dd	?
bmp_objSword		dd	?

bmp_MapScreens:
bmp_mapL1		dd	?
bmp_mapL2		dd	?
bmp_mapST		dd	?
bmp_mapT1		dd	?
bmp_mapW1		dd	?
bmp_mapW2		dd	?
bmp_mapD1		dd	?
bmp_mapC		dd	?

bmp_Inventory:
bmp_invNone		dd	?
bmp_invSword		dd	?
bmp_invKeySlv		dd	?

height_Objects:
height_objBushL	dd	?
height_objBushS	dd	?
height_objPost	dd	?
height_objRockH	dd	?
height_objRockL	dd	?
height_objRockM	dd	?
height_objRockS	dd	?
height_objRockT	dd	?
;height_objRockW	dd	?
height_objTreeB	dd	?
height_objTreeH	dd	?
height_objTreeL	dd	?
height_objTreeM	dd	?
height_objTreeS	dd	?
height_objSword	dd	?


	.code

LoadResources		proc	STDCALL
	push	0
	push	0
	push	0
	push	IMAGE_BITMAP
	push	offset res_UserInterface
	push	engineInstance
	call	LoadImage
	mov	bmp_UserInterface, eax

	push	0
	push	offset bmp_Skins
	push	offset res_Skins
	call	ResourceLockAndLoad

	push	offset height_Objects
	push	offset bmp_Objects
	push	offset res_Objects
	call	ResourceLockAndLoad

	push	0
	push	offset bmp_MapScreens
	push	offset res_MapScreens
	call	ResourceLockAndLoad

	push	0
	push	offset bmp_Inventory
	push	offset res_Inventory
	call	ResourceLockAndLoad

	ret
LoadResources		endp

ResourceLockAndLoad	proc	STDCALL, res_Start:DWORD, bmp_Start:DWORD, height_Start:DWORD
	mov	esi, res_Start
	mov	edi, bmp_Start
	mov	edx, height_Start

lockandload_loop:
	cmp	byte ptr [esi], 00h
	je	lockandload_finish

	push	edx

	push	0
	push	0
	push	0
	push	IMAGE_BITMAP
	push	esi
	push	engineInstance
	call	LoadImage
	stosd

	pop	edx

	.IF edx != 0
		push	edx

		push	offset bitmapDimensions
		push	BITMAP_
		push	eax
		call	GetObject

		pop	edx
		mov	eax, bitmapDimensions.bm_bmHeight
		mov	[edx], eax
		add	edx, 4h
	.ENDIF

lockandload_nextchk:
	inc	esi
	cmp	byte ptr [esi], 00h
	jne	lockandload_nextchk
	inc	esi

	jmp	lockandload_loop

lockandload_finish:
	ret
ResourceLockAndLoad	endp