# - Try to find the libgit2 library
# Once done this will define
#
#  LIBGIT2_FOUND - System has libgit2
#  LIBGIT2_INCLUDE_DIR - The libgit2 include directory
#  LIBGIT2_LIBRARIES - The libraries needed to use libgit2
#  LIBGIT2_DEFINITIONS - Compiler switches required for using libgit2


FIND_PATH(LIBGIT2_INCLUDE_DIR git2.h)

FIND_LIBRARY(LIBGIT2_LIBRARIES git2)


INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(libgit2 DEFAULT_MSG LIBGIT2_LIBRARIES LIBGIT2_INCLUDE_DIR)

MARK_AS_ADVANCED(LIBGIT2_INCLUDE_DIR LIBGIT2_LIBRARIES)
