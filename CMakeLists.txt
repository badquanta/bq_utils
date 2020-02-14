# * [ ] TODO: cmake version
cmake_minimum_required (VERSION 3.13) 
# Prepare doctest for other targets to use

# * [ ] TODO: rename bq__XXXXXXXXXXXX 
project(bq__XXXXXXXXXXXX
	# * [ ] TODO: reversion bq__XXXXXXXXXXXX
	VERSION "0.0.0"
)

include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    doctest
    PREFIX ${CMAKE_BINARY_DIR}/lib/doctest
    GIT_REPOSITORY https://github.com/onqtam/doctest.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)
#find_package(doctest REQUIRED)

# Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir} CACHE INTERNAL "Path to include folder for doctest")
# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here   
    # Let's ensure -std=c++xx instead of -std=g++xx
    #set(CMAKE_CXX_EXTENSIONS OFF)
	# * [ ] TODO: review CXX_STANDARD 20
	set(CMAKE_CXX_STANDARD 20)
	# @note: Put cmake modules in `<bq__XXXXXXXXXXXX_ROOT>/scripts/
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/scripts/")
	#	
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
	# * [ ] TODO: review EXE_LINKER_FLAGS 
	#set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
	# * [ ] TODO: include_directories(ex: extern/glm)
    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    enable_testing( )
    
    # Testing only available if this is the main app
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    #include(CTest)
    #
    # Docs only available if this is the main app
    find_package(Doxygen)
    #
    if(Doxygen_FOUND)
    	#
		add_subdirectory(docs)
		#
    else()
    	#
		message(STATUS "Doxygen not found, not building docs")
		#
    endif()
    #
endif()
# * [ ] TODO: Review lack of independent `include` directory...
add_subdirectory(src)
#add_dependencies(src "${source_dir}")
# * [ ] TODO: move resources directive to sub-project?
# we don't want to copy if we're building in the source dir
#if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)

    # list of files for which we add a copy rule
#    set(data_SHADOW res/)

#    foreach(item IN LISTS data_SHADOW)
#        message(STATUS ${item})
#        add_custom_command(
#            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
#            COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
#            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
#        )
#    endforeach()
#endif()
# files are only copied if a target depends on them
#add_custom_target(res-data ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/res/")


install(TARGETS bq__XXXXXXXXXXXX	 
#	LIBRARY bq__XXXXXXXXXXXX
	DESTINATION bq_utils
	PUBLIC_HEADER ${BQ__XXXXXXXXXX_PUBLIC_INCLUDE_DIRECTORIES}
)



