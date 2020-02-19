# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(default_build_type "Release")
  if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
      "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
  endif()
  message(STATUS "SETTING UP ${PROJECT_NAME} in configuration ${CMAKE_BUILD_TYPE}")
  # * [ ] TODO: review CXX_STANDARD 17
  set(CMAKE_CXX_STANDARD 17)
  message("CMAKE_CXX_STANDARD IS ${CMAKE_CXX_STANDARD}")    
  # TODO: Do we need this?
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  # Use testing...
  enable_testing( )
  # Testing only available if this is the main app
  include(CTest)
  # Set-up CPack
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}")
  set(CPACK_GENERATOR "TGZ;DEB")
  set(CPACK_BINARY_DEB      ON) 
  set(CPACK_BINARY_TZ       OFF)
  set(CPACK_BINARY_STGZ     OFF)
  set(CPACK_STRIP_FILES     "*_test")
  set(CPACK_PACKAGE_NAME     ${PROJECT_NAME} )
  set(CPACK_PACKAGE_VERSION  ${VERSION})
  set(CPACK_PACKAGE_CONTACT  "Jon (BadQuanta) Sawyer")
  set(CPACK_PACKAGE_VENDOR   "U.F.P.")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
  set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
  set(CPACK_RESOURCE_FILE_LICENSE     ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
  set(CPACK_RESOURCE_FILE_README      ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
  set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION})
  set(CPACK_DEBIAN_PACKAGE_SECTION     "devel")
  set(CPACK_DEBIAN_PACKAGE_HOMEPAGE    ${PROJECT_HOMEPAGE_URL})
  set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS   YES) #
  #TODO:set(CPACK_DEBIAN_PACKAGE_DEPENDS    "libsdl2-dev, libsdl2-gfx-dev, libsdl2-image-dev, libsdl2-mixer-dev, libsdl2-net-dev, libsdl2-ttf-dev")
  set(CPACK_DEBIAN_PACKAGE_SUGGESTS    "")
  set(CPACK_DEBIAN_PACKAGE_CONFLICTS   "")
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER  "Jon (BadQuanta) Sawyer <badquanta@gmail.com>")
  set(CPACK_SOURCE_IGNORE_FILES "/build/*;/.vscode*")
  set(CPACK_SOURCE_GENERATOR ${CPACK_GENERATOR})
  set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
  set(CPACK_RESOURCE_FILE_README  ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
  set(CPACK_RESOURCE_FILE_WELCOME ${CMAKE_CURRENT_SOURCE_DIR}/docs/Welcome.md)
  

  # Packaging only available if this is the main app
  include(CPack)
  
  # Setup documentation
  find_package(Doxygen)
  if(Doxygen_FOUND)
  #
  add_subdirectory(docs)
  
  #
  else()
  #
  message(STATUS "Doxygen not found, not building docs")
  #
  endif()
  
endif()