find_path(CRITERION_INCLUDE_DIR criterion/criterion.h
          PATH_SUFFIXES criterion)

find_library(CRITERION_LIBRARY NAMES criterion libcriterion)

set(CRITERION_LIBRARIES ${CRITERION_LIBRARY})
set(CRITERION_INCLUDE_DIRS ${CRITERION_INCLUDE_DIR})
