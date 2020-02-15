# PROJECT/CMakeList.txt
# - started in bq_TEMPLATE++
cmake_minimum_required (VERSION 3.13) 
project(bq_utils
	VERSION "0.0.0"
)
# Externals & Settings 
include("scripts/external_projects.cmake")
include("scripts/project_settings.cmake")
# Sub directories
add_subdirectory(src)
# Installation configuration
install(TARGETS bq_utils	 
	DESTINATION bq_utils
)
target_include_directories(bq_utils PUBLIC src)

