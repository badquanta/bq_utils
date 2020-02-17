# PROJECT/CMakeList.txt
# - started in bq_TEMPLATE++
# - renamed for bq_sdl
cmake_minimum_required (VERSION 3.13) 
# my projects start with bq_ to ensure I don't collide with others.
# PROJECT_SHORTNAME refers to the part that follows `bq_...`.
set(PROJECT_SHORTNAME XXXXXXXXXXXX)
##########
project("bq_${PROJECT_SHORTNAME}"
	VERSION "0.0.0"
	DESCRIPTION ""
	HOMEPAGE_URL ""
	LANGUAGES CXX
)
# many of these bq_<PROJECT_NAME> share the same cmake setup,
# most of that config is maintained in a "TEMPLATE" repo; and
# periodically I update all the repos that use that template.
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/scripts/")
# Externals Projects this project will depend on.
include("externals")
# bq_library defines the same settings I use for all of my `bq_...` C++/CMake libraries.
include("bq_library")
# find_packages... (example: find_package(SDL2 REQUIRED) )
##################
# TODO: Maybe move find_packages to external_packages?
#################
# this template is setup for a library by default, I may generalize to programs later.
# Define this library as a target.
# TODO: Review if this should be STATIC or SHARED per-project; defaulting to STATIC for template.
add_library(${PROJECT_NAME} STATIC)
#################
# add dependencies this library has.
# EXAMPLE: add_dependencies(${PROJECT_NAME} bq_utils)
# Add needed libraries.
# Example: target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${BQ_UTIL_LIBRARIES})
#################
# Describe install locations.
install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER	DESTINATION 	include/bq/${PROJECT_SHORTNAME}
)
# Install the library public header files, which are all *.hpp files.
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/src/ DESTINATION include/bq/${SHORTNAME} FILES_MATCHING PATTERN "*.hpp")
# Install the library documentation
install(DIRECTORY ${CMAKE_BINARY_DIR}/docs/ DESTINATION docs/bq/${SHORTNAME}test FILES_MATCHING PATTERN "*.*")
# Add needed include directories.
# Use the correct include directories; dpending on the interface?
target_include_directories(${PROJECT_NAME} 
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/>
		$<INSTALL_INTERFACE:include/>
	PRIVATE ${CMAKE_SOURCE_DIR}/src/ ${CMAKE_BINARY_DIR}/include ${BQ_UTILS_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} 	${SDL2_IMAGE_INCLUDE_DIRS} 	${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS}
)
###############
# Macro to avoid repetative commands for each: "TRINITY"
# (aka: "Source, Header, and Test")
macro(TRINITY compName)
	# Handle each source by adding it to the target
	target_sources(${PROJECT_NAME} PRIVATE "${compName}.cpp")
	# Handle each header by adding it to the target AND
	target_sources(${PROJECT_NAME} PUBLIC "${compName}.hpp")
	# Adding it to the target_properties (TODO: This may not be needed anymore)
	set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${compName}.hpp")
	# Add a target for each component's unit test.
	add_executable("${compName}_test" "${compName}_test.cpp" )
	# unit tests require this header-only package to compile, add it as a dependency.
	add_dependencies("${compName}_test" doctest)	
	# link each component's unit test agains the library as a whole.
	target_link_libraries("${compName}_test" ${PROJECT_NAME})
	#target_link_libraries("${X}_test" PUBLIC bqpd)	
	#target_link_libraries("${X}_test" PRIVATE doctest::doctest)
	# Setup the include directories for the tests	
	target_include_directories("${compName}_test" PUBLIC "${DOCTEST_INCLUDE_DIR}" "${CMAKE_BINARY_DIR}/include")	
	# Register each test with the test-running framework.
	add_test("${compName}_test" "${compName}_test")
	# Tell the user that we've configured this component.
	message(STATUS "TRINITY DEFINED FOR: ${PROJECT_NAME}::${compName}")
endmacro()
# Sub directories
add_subdirectory(src)



