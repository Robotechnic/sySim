# the part automaticaly create new target based on the c files in this directory

file(GLOB protocols RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/*.c)
foreach(protocol ${protocols})
	string(REPLACE ".c" "" projectName ${protocol})
	add_executable(
		${projectName}
		${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
		${CMAKE_CURRENT_SOURCE_DIR}/src/argparse/argparse.c
		${CMAKE_CURRENT_LIST_DIR}/${protocol}
	)
	target_link_libraries(
		${projectName}
		PRIVATE
			sySimLib
	)
	target_compile_options(
		${projectName}
		PRIVATE
			-Wall
			-Wextra
			-Wpedantic
			-Werror
	)
	list(APPEND protocolsNames ${projectName})
endforeach()

