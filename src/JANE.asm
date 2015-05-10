	.486p
	.model flat

UNICODE equ     0
INCLUDE ..\win32\Win32.INC
INCLUDELIB ..\win32\Win32.LIB
INCLUDELIB ..\win32\GDI32.LIB
INCLUDELIB ..\win32\MSImg32.LIB

INCLUDE	Constants.inc
INCLUDE	Structures.inc

	.data
engine_count_data:
versionTag	db	'Just Another Ninja Engine v2',0Dh,0Ah,0Dh,0Ah
		db	'Written by Marq Watkin',0Dh,0Ah
		db	'http://www.pmprog.co.uk',0

INCLUDE	Data-Animation.inc
INCLUDE	Data-Game.inc
INCLUDE	Data-Globals.inc
INCLUDE	Data-Inventory.inc

TOTAL_ENGINE_DATA_SIZE	equ	offset $ - engine_count_data

	.code
engine_count_code:
INCLUDE	Windows.inc


INCLUDE	Events-Win.inc
INCLUDE	Events-Ninja.inc

INCLUDE	Resource.inc

INCLUDE	StateControl.inc

INCLUDE	Controller.inc
INCLUDE	Animator.inc

INCLUDE	General-FrameCalc.inc
INCLUDE	Gfx-Scenery.inc
INCLUDE	Gfx-Enemy.inc

INCLUDE	Collision.inc

INCLUDE	Object-Code.inc

INCLUDE	AI-Enemy.inc


TOTAL_ENGINE_CODE_SIZE	equ	offset $ - engine_count_code
	end	start
