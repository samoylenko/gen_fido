; Pimpscript file v1.3.0
; Copyright (C) 1999 Nullsoft Inc.
; You can comment by starting lines with ; or #.

; Variables you can use in many of the strings:
;   $PROGRAMFILES (usually c:\program files)
;   $WINDIR (usually c:\windows)
;   $SYSDIR (usually c:\windows\system)
;   $DESKTOP (the desktop directory for the current user)
;   $INSTDIR (whatever the install directory ends up being)
;   $VISDIR  (visualization plug-in directory. DO NOT USE IN DefaultDir)
;   $DSPDIR  (dsp plug-in directory. DO NOT USE IN DefaultDir)

; Name specifies what the installer will use for its name
Name PowerMike's Fido Plug-In v3.0

; Text specifies what text will appear in the dialog window
Text This will install PowerMike's Fido Plug-In v3.0 for Winamp on your computer

; OutFile specifies where to write the installer executable to
OutFile wafido30.exe

; DefaultDir lets you specify the default installation directory
; (if you omit DefaultDir, it will default to the Winamp directory,
; determined at install time)

;DefaultDir $PROGRAMFILES\MyProgram

; You can add a line that just says Silent to make the installer silent.
;Silent


; File listing section
; --------------------


; SetOutPath specifies the relative output Path
; Or, you can use any of the variables (see DefaultDir), or start with a \ to
; specify the root directory of the install drive.
; You can use
; SetOutPath -
; or
; SetOutPath $INSTDIR
; to set the output directory to the install directory
SetOutPath plugins

; Any number of AddFile's can follow. Wildcards (in limited form) can be used.
AddFile C:\gen_fido\release\gen_fido.dll
AddFile C:\gen_fido\txt\gen_fido.txt
AddFile C:\gen_fido\cfg\gen_fido.cfg

; Post-install execute section
; ----------------------------

; ExecFile will execute a command after a successful installation.
; Note that it must list an executable. You can specify a parameter,
; though. For example, to open a text file:
;ExecFile "$WINDIR\notepad.exe" readme.txt

; Path is relative unless you use a variable (see DefaultDir).
ExecFile "$WINDIR\notepad.exe" $INSTDIRplugins\gen_fido.txt

; You can use multiple ExecFile commands and they will all be executed.
; You're usually limited to around 10 commands, Makepimp will bitch
; if you do too many. Also, you can't have the pipe ('|') symbol in
; your commands.


; end
