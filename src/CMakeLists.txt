add_library(bq_utils STATIC	
	WeakPtrCache.cpp
	utils.cpp	
)
# Public headers to install
set_target_properties(bq_utils
	PROPERTIES PUBLIC_HEADER 
		"WeakPtrCache.hpp;utils.h"
)
# Describe install locations.
install(TARGETS bq_utils
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER	DESTINATION 	include/bq/utils
)
# Use the correct include directories; dpending on the interface?
target_include_directories(bq_utils PUBLIC
$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/>
$<INSTALL_INTERFACE:include/>
PRIVATE ${CMAKE_SOURCE_DIR}/src/)
# Generate associated testing.
foreach(X 
	utils
	WeakPtrCache
)
	message(STATUS "ADDING ${X}_test")
	
	add_executable("${X}_test" "${X}_test.cpp" )
	add_dependencies("${X}_test" doctest)
	target_include_directories("${X}_test" PUBLIC "${DOCTEST_INCLUDE_DIR}")

	#target_link_libraries("${X}_test" PUBLIC bqpd)	
	#target_link_libraries("${X}_test" PRIVATE doctest::doctest)
	add_test("${X}_test" "${X}_test")
endforeach()

