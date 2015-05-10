	.data

InventoryList:
inv_none	Inventory	<0, 0, 1, 0>				; Empty Inventory
inv_sword	Inventory	<1, 1, 0, INVENTORY_TYPE_HANDHELD>	; Sword
inv_key_slvr	Inventory	<2, 0, 0, INVENTORY_TYPE_HANDHELD>	; Silver Key


Inventory_Count	equ	(offset $ - offset InventoryList) / Inventory_Len
