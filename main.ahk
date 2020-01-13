#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
#SingleInstance force
CoordMode, ToolTip, Screen  ; Place ToolTips at absolute screen coordinates.

; Set Lock keys permanently
SetNumlockState, AlwaysOn
; SetScrollLockState, AlwaysOff


#If GetKeyState("ScrollLock", "T")
    showToolTip("Ahk script loaded")

    ^sc0046:: ;ScrollLock scan-code
    Reload
    return

    !sc0046:: ;ScrollLock scan-code
    Edit
    return
#If 


showToolTip(txt, timeout:=2000) {
    ToolTip,  % txt
    SetTimer, RemoveToolTip, % timeout
    toolHwnd := "ahk_id" . WinExist("ahk_exe AutoHotkey.exe ahk_class tooltips_class32")
    WinGetPos, x, y, w, h, % toolHwnd
    toolX := (A_ScreenWidth - w) // 2
    toolY := (A_ScreenHeight - h) // 2
    WinMove, % toolHwnd, , % toolX, 0
}

RemoveToolTip:
ToolTip
return
