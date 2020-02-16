# find_packages...
##################
# all library components
set(BQ_XXXXXXXXXXXX_COMPONENTS
	XXXXXXXXXXXX
)
# Convert the list of components into three lists of files:
foreach(X ${BQ_XXXXXXXXXXXX_COMPONENTS})
	list(APPEND BQ_XXXXXXXXXXXX_SOURCES "${X}.cpp")
	list(APPEND BQ_XXXXXXXXXXXX_HEADERS "${X}.hpp")
	list(APPEND BQ_XXXXXXXXXXXX_TESTS   "${X}_test.cpp")
	message("BQ_BQ_XXXXXXXXXXXX_COMPONENT+=${X}[.cpp|.hpp|_test.cpp]")
endforeach()
# Define this library as a target
add_library(bq_XXXXXXXXXXXX STATIC ${BQ_XXXXXXXXXXXX_SOURCES})
# Add needed libraries.
#target_link_libraries(bq_XXXXXXXXXXXX ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${BQ_UTIL_LIBRARIES})
# Public headers to install
set_target_properties(bq_XXXXXXXXXXXX PROPERTIES PUBLIC_HEADER "${BQ_XXXXXXXXXXXX_HEADERS}")
# Describe install locations.
install(TARGETS bq_XXXXXXXXXXXX
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER	DESTINATION 	include/bq/XXXXXXXXXXXX
)
# Use the correct include directories; dpending on the interface?
target_include_directories(bq_XXXXXXXXXXXX 
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/>
		$<INSTALL_INTERFACE:include/>
	PRIVATE
		${CMAKE_SOURCE_DIR}/src/
		# More Include dirs...
		${CMAKE_BINARY_DIR}/include
)
if(BUILD_TESTING)
	message("Adding tests...")
	# Generate associated testing.
	foreach(X ${BQ_XXXXXXXXXXXX_COMPONENTS})
		# output each test being declared.
		message(STATUS "ADDING ${X}_test")
		# add test executable
		add_executable("${X}_test" "${X}_test.cpp" )
		# add the dependencies all tests for this project need:
		add_dependencies("${X}_test" doctest)
		#target_link_libraries("${X}_test" PUBLIC bq_...)	
		#target_link_libraries("${X}_test" PRIVATE doctest::doctest)
		# add special include directories that test files need:
		target_include_directories("${X}_test" PUBLIC "${DOCTEST_INCLUDE_DIR}")
		# register this test as a test.
		add_test("${X}_test" "${X}_test")
	endforeach()
endif()
