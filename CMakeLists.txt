cmake_minimum_required(VERSION 3.20)

project(sySym)

set(CMAKE_C_STANDARD 11)
set(EXPORT_COMPILE_COMMANDS ON)

add_executable(
	sySym
	src/main.c
)

target_include_directories(
	sySym
	PRIVATE
		src
)

target_compile_options(
	sySym
	PRIVATE
		-Wall
		-Wextra
		-Wpedantic
		-Werror
)
