add_library(bq_utils STATIC	
	WeakPtrCache.cpp utils.cpp	
	utils.h WeakPtrCache.hpp
	
)
foreach(X 
	utils
	WeakPtrCache
)
	message(STATUS "ADDING ${X}_test")
	

	add_executable("${X}_test" "${X}_test.cpp")

	add_dependencies("${X}_test" doctest)
	target_include_directories("${X}_test" PUBLIC "${DOCTEST_INCLUDE_DIR}")
	
	#target_link_libraries("${X}_test" PUBLIC bqpd)	
	#target_link_libraries("${X}_test" PRIVATE doctest::doctest)
	add_test("${X}_test" "${X}_test")
endforeach()