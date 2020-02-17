# Each "NAME" gets translated into:
# "NAME.cpp", "NAME.hpp", "NAME_test.cpp"
# and each will be setup for the project by the TRINITY macro
# if there are sub-directories, simply `add_subdirectory(xyz)`
# and repeat the pattern.
##################
TRINITY(WeakPtrCache)
TRINITY(utils)

