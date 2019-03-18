set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(
	hangman_lib_srcs
	hangman.h
	hangman.cpp
)
add_library(hangman_lib STATIC ${hangman_lib_srcs})
set_target_properties(hangman_lib PROPERTIES LINKER_LANGUAGE CXX)

if(ENABLE_COVERAGE)
	target_link_libraries(hangman_lib --coverage)
endif()

target_include_directories(hangman_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})