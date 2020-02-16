add_library(bq_XXXXXXXXXXXX STATIC	
	XXXXXXXXXXXX.cpp		
	XXXXXXXXXXXX.h
)
# Public headers to install
set_target_properties(bq_XXXXXXXXXXXX
	PROPERTIES PUBLIC_HEADER XXXXXXXXXXXX.h
)
# Describe install locations.
install(TARGETS bq_XXXXXXXXXXXX
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER	DESTINATION 	include/bq/XXXXXXXXXXXX
)
# Use the correct include directories; dpending on the interface?
target_include_directories(bq_XXXXXXXXXXXX PUBLIC
$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/>
$<INSTALL_INTERFACE:include/>
PRIVATE ${CMAKE_SOURCE_DIR}/src/)
# Generate associated testing.
foreach(X 
	XXXXXXXXXXXX
)
	message(STATUS "ADDING ${X}_test")
	
	add_executable("${X}_test" "${X}_test.cpp" )
	add_dependencies("${X}_test" doctest)
	target_include_directories("${X}_test" PUBLIC "${DOCTEST_INCLUDE_DIR}")

	#target_link_libraries("${X}_test" PUBLIC bqpd)	
	#target_link_libraries("${X}_test" PRIVATE doctest::doctest)
	add_test("${X}_test" "${X}_test")
endforeach()
