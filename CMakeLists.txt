cmake_minimum_required(VERSION 3.20)

project(sySim)

set(CMAKE_C_STANDARD 11)
set(EXPORT_COMPILE_COMMANDS ON)

include_directories(
	src
	lib
)

include(lib/CMakeLists.txt)

# remove compiler warnings from argparse.c
set_source_files_properties(
	src/argparse/argparse.c
	PROPERTIES
		COMPILE_FLAGS "-w"
)

include(protocols/CMakeLists.txt)

# clang-format support
find_program(CLANG_FORMAT_EXE NAMES "clang-format")
if(CLANG_FORMAT_EXE)
	add_custom_target(
		format
		COMMAND ${CLANG_FORMAT_EXE} -i -style=file
			${PROJECT_SOURCE_DIR}/src/*.c
			${PROJECT_SOURCE_DIR}/src/*/*.c
			${PROJECT_SOURCE_DIR}/src/*/*.h 
			${PROJECT_SOURCE_DIR}/lib/*/*.c
			${PROJECT_SOURCE_DIR}/lib/*/*.h
			${PROJECT_SOURCE_DIR}/protocols/*.c
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
			--conf-parser 
			--input=${PROJECT_SOURCE_DIR}/src/sySim.ggo 
			--file-name=argparse
			--output-dir=${PROJECT_SOURCE_DIR}/src/argparse
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		DEPENDS ${PROJECT_SOURCE_DIR}/src/sySim.ggo
		SOURCES ${PROJECT_SOURCE_DIR}/src/sySim.ggo
	)
	foreach(pro ${protocolsNames})
		add_dependencies(${pro} genopt)
	endforeach()
else()
	message(STATUS "gengetopt not found.")
endif()

