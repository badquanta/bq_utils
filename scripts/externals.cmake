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
ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir} CACHE INTERNAL "Path to include folder for doctest")