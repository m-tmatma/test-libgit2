set platform=%1
set configuration=%2

set BUILDDIR=%~dp0build\%platform%
cmake --build %BUILDDIR%  --config %configuration%
