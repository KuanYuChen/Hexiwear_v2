REM *******************************************************
REM * Batch file to program a bin file with Segger J-Link *
REM *******************************************************

SET JLINK="C:\Program Files (x86)\SEGGER\JLink_V614b\JLink.exe"

%JLINK% -device MKW40Z160xxx4 -CommanderScript ./jlink_kw40.script
pause
