cmake_minimum_required(VERSION 3.18)
cmake_policy(SET CMP0115 NEW)

project(PrettySleep
	VERSION 0.0.1
	DESCRIPTION "A prettier sleep command"
	LANGUAGES C)

include(GNUInstallDirs)
include_directories(PRIVATE includes)

add_executable(psleep
	src/main.c
	src/utils.c)

target_compile_definitions(psleep PUBLIC VERSION_MAJOR=${PROJECT_VERSION_MAJOR} VERSION_MINOR=${PROJECT_VERSION_MINOR} VERSION_PATCH=${PROJECT_VERSION_PATCH})

install(TARGETS psleep RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
