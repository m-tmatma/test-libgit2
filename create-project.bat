set platform=%1
set configuration=%2

set BUILDDIR=%~dp0build\%platform%
mkdir "%BUILDDIR%"
cmake -H. -B"%BUILDDIR%"
