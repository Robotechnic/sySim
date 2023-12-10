cmake_minimum_required(VERSION 3.20)

project(sySim)

set(CMAKE_C_STANDARD 11)
set(EXPORT_COMPILE_COMMANDS ON)

include_directories(
	src
	lib
)

include(lib/CMakeLists.txt)

add_executable(
	sySim
	src/argparse/argparse.c
	src/main.c
)

target_link_libraries(
	sySim
	PRIVATE
		sySimLib
)

target_compile_options(
	sySim
	PRIVATE
		-Wall
		-Wextra
		-Wpedantic
		-Werror
)

# remove compiler warnings from argparse.c
set_source_files_properties(
	src/argparse/argparse.c
	PROPERTIES
		COMPILE_FLAGS "-w"
)

# clang-format support
find_program(CLANG_FORMAT_EXE NAMES "clang-format")
if(CLANG_FORMAT_EXE)
	add_custom_target(
		format
		COMMAND ${CLANG_FORMAT_EXE} -i -style=file
			${PROJECT_SOURCE_DIR}/src/*.c 
			${PROJECT_SOURCE_DIR}/src/*/*.c 
			${PROJECT_SOURCE_DIR}/src/*.h 
			${PROJECT_SOURCE_DIR}/src/*/*.h 
			${PROJECT_SOURCE_DIR}/lib/*/*.h
			${PROJECT_SOURCE_DIR}/lib/*/*.h
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	)
else()
	message(STATUS "clang-format not found.")
endif()

# gengetopt support
find_program(GENGETOPT_EXE NAMES "gengetopt")
if(GENGETOPT_EXE)
	add_custom_target(
		genopt
		COMMAND ${GENGETOPT_EXE} 
			--input=${PROJECT_SOURCE_DIR}/src/sySim.ggo 
			--file-name=argparse
			--output-dir=${PROJECT_SOURCE_DIR}/src/argparse
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		SOURCES ${PROJECT_SOURCE_DIR}/src/sySim.ggo
	)
	add_dependencies(sySim genopt)
else()
	message(STATUS "gengetopt not found.")
endif()

