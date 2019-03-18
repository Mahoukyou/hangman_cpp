file(GLOB SRCS *.cpp)

add_executable(sample_test ${SRCS})

target_link_libraries(
	sample_test
	hangman_lib
	gtest
	gmock_main
)

if(ENABLE_COVERAGE)
	target_link_libraries(sample_test --coverage)
endif()

install(TARGETS sample_test DESTINATION bin)
add_test(UnitTests sample_test)