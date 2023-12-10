cmake_minimum_required(VERSION 3.20)

project(sySym)

set(CMAKE_C_STANDARD 11)
set(EXPORT_COMPILE_COMMANDS ON)


add_executable(
	sySym
	src/argparse/argparse.c
	src/main.c
)

target_include_directories(
	sySym
	PRIVATE
		src
		lib
)

target_compile_options(
	sySym
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
			--input=${PROJECT_SOURCE_DIR}/src/sySym.ggo 
			--file-name=argparse
			--output-dir=${PROJECT_SOURCE_DIR}/src/argparse
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		SOURCES ${PROJECT_SOURCE_DIR}/src/sySym.ggo
	)
	add_dependencies(sySym genopt)
else()
	message(STATUS "gengetopt not found.")
endif()

