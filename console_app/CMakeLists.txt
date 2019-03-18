set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(
	hangman_console_app_srcs
	main.cpp
)
add_executable(hangman_console_app ${hangman_console_app_srcs})

if(ENABLE_COVERAGE)
	target_link_libraries(hangman_console_app --coverage)
endif()

target_include_directories(hangman_console_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})