cmake_minimum_required(VERSION 3.18)
cmake_policy(SET CMP0115 NEW)

project(PrettySleep
	DESCRIPTION "A prettier sleep command"
	LANGUAGES C)

include_directories(PRIVATE includes)


add_executable(psleep
	src/main.c
	src/utils.c)
