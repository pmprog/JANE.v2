mciGetDeviceIDA PROCDESC WINAPI :DWORD
mciGetDeviceID textequ <mciGetDeviceIDA>

mciSendCommandA PROCDESC WINAPI :DWORD
mciSendCommand textequ <mciSendCommandA>

MCI_SET_PARMS   struct
        mcisp_Callback          DWORD   ?
        mcisp_TimeFormat        DWORD   ?
        mcisp_Audio             DWORD   ?
MCI_SET_PARMS   ends

MCI_OPEN_PARMS   struct
        mcisp_Callback          DWORD   ?
        mcisp_DeviceID          DWORD   ?
        mcisp_DeviceType        DWORD   ?
        mcisp_ElementName       DWORD   ?
        mcisp_Alias             DWORD   ?
MCI_OPEN_PARMS   ends

MCI_OPEN                        equ     0803h
MCI_CLOSE                       equ     0804h
MCI_SET                         equ     080Dh


MCI_SET_DOOR_OPEN               equ     0100h
MCI_SET_DOOR_CLOSE              equ     0200h

MCI_ALL_DEVICE_ID               equ     -1
MCI_OPEN_TYPE                   equ     2000h
MCI_OPEN_TYPE_ID                equ     1000h
