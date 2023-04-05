cd build\win64\release

cmake ../../.. -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSTEM_NAME=Windows -DBUILD_SHARED=False

cmake --build . -- -j4