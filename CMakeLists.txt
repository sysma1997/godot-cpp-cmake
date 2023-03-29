cmake_minimum_required(VERSION 3.16)
project(test VERSION 0.1.0)
 
set(CMAKE_CXX_STANDARD 17)
 
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()
  
string(TOLOWER "${CMAKE_SYSTEM_NAME}" SYSTEM_NAME)
string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE)
set(MY_SYSTEM_OUTPUT_PATH "win64")
 
set(BUILD_PATH ${CMAKE_SOURCE_DIR}/project/bin/${MY_SYSTEM_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")
 
set(MY_LINKER_FLAGS )
set(MY_COMPILER_FLAGS "-fPIC -Wwrite-strings")
set(LINK_DIRS )

# src
file(GLOB src 
    "src/*.h" "src/*.cpp")

add_library(${PROJECT_NAME} SHARED init.cpp ${src})

# Default build is static, build shared only if you went with step 5
if(BUILD_SHARED STREQUAL "")
	set(BUILD_SHARED False)
endif()

if(BUILD_SHARED)
    add_custom_command(TARGET ${PROJECT_NAME} PRE_LINK
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/lib/std/ ${BUILD_PATH})
    add_custom_command(TARGET ${PROJECT_NAME} PRE_LINK
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/lib/godot-cpp/bin/libgodot-cpp.${SYSTEM_NAME}.${BUILD_TYPE}.64.dll ${BUILD_PATH})
    set(LINK_DIRS "${BUILD_PATH}")
else()
    set(LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
    set(LINK_DIRS ${CMAKE_SOURCE_DIR}/lib/godot-cpp/bin/)
endif(BUILD_SHARED)
 
# that's just quick and dirty folder cleanup, actually CMake would detect what has changed
file(REMOVE_RECURSE ${BUILD_PATH})
file(MAKE_DIRECTORY  ${BUILD_PATH})

if(CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DNDEBUG)
else()
    add_definitions(-D_DEBUG)
    set(COMPILER_FLAGS "-g")
endif(CMAKE_BUILD_TYPE MATCHES Release)
 
target_include_directories(${PROJECT_NAME} PUBLIC
    lib/godot-cpp/godot-headers
    lib/godot-cpp/include
    lib/godot-cpp/include/core
    lib/godot-cpp/build/win64/release/include/gen
)
 
set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY COMPILE_FLAGS ${COMPILER_FLAGS})
set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY LINK_FLAGS ${LINKER_FLAGS})
 
target_link_directories(${PROJECT_NAME} PRIVATE ${LINK_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE "godot-cpp.${SYSTEM_NAME}.${BUILD_TYPE}.64")