cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

set(NAME gli-test)

file(GLOB ROOT_SOURCE *.cpp)
file(GLOB ROOT_INLINE *.inl)
file(GLOB ROOT_HEADER *.hpp)

file(GLOB_RECURSE CORE_SOURCE ./core/*.cpp)
file(GLOB_RECURSE CORE_INLINE ./core/*.inl)
file(GLOB_RECURSE CORE_HEADER ./core/*.hpp)

source_group("Core Files" FILES ${CORE_SOURCE})
source_group("Core Files" FILES ${CORE_INLINE})
source_group("Core Files" FILES ${CORE_HEADER})

include_directories(..)
include_directories(../external/glm-0.8.4.3)

add_executable(${NAME} 
	${ROOT_SOURCE} ${ROOT_INLINE} ${ROOT_HEADER} 
	${CORE_SOURCE} ${CORE_INLINE} ${CORE_HEADER})

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
