# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  message("SETTING UP ${PROJECT_NAME}")
  # * [ ] TODO: review CXX_STANDARD 17
  set(CMAKE_CXX_STANDARD 17)
  message("CMAKE_CXX_STANDARD IS ${CMAKE_CXX_STANDARD}")
    set(default_build_type "Release")
    if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
      message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
      set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
          STRING "Choose the type of build." FORCE)
      # Set the possible values of build type for cmake-gui
      set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
    endif()
    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    enable_testing( )
    # Testing only available if this is the main app
    include(CTest)
    # Packaging only available if this is the main app
    include(CPack)
    # Docs only available if this is the main app
    find_package(Doxygen)
    #
    if(Doxygen_FOUND)
    # (this will be run from the main project directory, so ./doc, not ./scripts/doc)
		add_subdirectory(docs)
		#
    else()
    #
		message(STATUS "Doxygen not found, not building docs")
		#
    endif()
    #
endif()