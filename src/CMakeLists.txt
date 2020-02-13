# 
add_library(bq__XXXXXXXXXXXX
	XXXXXXXXXXXX.h
	XXXXXXXXXXXX.cpp	
)
#target_include_directories
#Add include directories to a target.
	#- target_include_directories(<target> [SYSTEM] [BEFORE] <INTERFACE|PUBLIC|PRIVATE> 
#	 [items1...] [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
	#- target_include_directories(mylib PUBLIC $<BUILD_INTERFACE:$
#	 {CMAKE_CURRENT_SOURCE_DIR}/include/mylib> $<INSTALL_INTERFACE:include/mylib> # <prefix>/
	 #include/mylib )
# ** [ ] TODO: Review src target_include_directories
target_include_directories(bq_XXXXXXXXXXXX PUBLIC ./ $<INSTALL_INTERFACE:include/bq/XXXXXXXXXXXX)
#
# ** [ ] TODO: Review src link_libraries
#target_link_libraries(modern_library PRIVATE Boost::boost)