cmake -DBUILD_SHARED_LIBS=OFF -S %~dp0 -B %~dp0build
cmake                         --build     %~dp0build
