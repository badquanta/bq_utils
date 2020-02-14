add_library(bq_XXXXXXXXXXXX STATIC
	XXXXXXXXXXXX.h
	XXXXXXXXXXXX.cpp	
)
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
