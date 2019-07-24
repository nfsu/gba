cmake_minimum_required(VERSION 3.13.0)
project(gba)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_SUPPRESS_REGENERATION true)

add_subdirectory(armulator)

include_directories(include)
include_directories(armulator/include)
include_directories(armulator/core2/include)

file(GLOB_RECURSE gbaSrc
	"include/*.hpp"
	"src/*.cpp"
)

add_executable(
	gba
	${gbaSrc}
)

target_link_libraries(gba armulator ocore)

if(MSVC)
    target_compile_options(gba PRIVATE /W4 /WX /MD /MP /wd4201)
else()
    target_compile_options(gba PRIVATE -Wall -Wextra -pedantic -Werror)
endif()