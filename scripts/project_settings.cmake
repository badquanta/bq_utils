# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message("SETTING UP ${PROJECT_NAME}")
    # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here   
    # Let's ensure -std=c++xx instead of -std=g++xx
    #set(CMAKE_CXX_EXTENSIONS OFF)
	# * [ ] TODO: review CXX_STANDARD 20
	set(CMAKE_CXX_STANDARD 20)
	# @note: Put cmake modules in `<bq_XXXXXXXXXXXX_ROOT>/scripts/
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