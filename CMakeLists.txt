# PROJECT/CMakeList.txt
# - started in bq_TEMPLATE++
cmake_minimum_required (VERSION 3.13) 
project(bq_XXXXXXXXXXXX
	# * [ ] TODO: reversion bq_XXXXXXXXXXXX
	VERSION "0.0.0"
)
# Externals & Settings 
include("scripts/external_projects.cmake")
include("scripts/project_settings.cmake")
# Sub directories
add_subdirectory(src)
# Installation configuration
install(TARGETS bq_XXXXXXXXXXXX	 
#	LIBRARY bq_XXXXXXXXXXXX
	DESTINATION bq_utils
	PUBLIC_HEADER ${bq_XXXXXXXXXX_PUBLIC_INCLUDE_DIRECTORIES}
)



