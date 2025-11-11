cmake -B build -S .
cmake --build build

# cmake -B build-iOS \
#     -GXcode \
#     -DCMAKE_SYSTEM_NAME=iOS \
#     -DCMAKE_OSX_SYSROOT=iphoneos 
# cmake --build build-iOS