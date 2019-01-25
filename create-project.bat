set BUILDDIR=%~dp0build

mkdir "%BUILDDIR%"
cmake -H. -B"%BUILDDIR%"
