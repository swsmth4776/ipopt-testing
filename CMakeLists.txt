cmake_minimum_required(VERSION 3.16)
project(MyExample)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyExample MyExample.cpp hs071_nlp.cpp hs071_nlp.hpp)

# Copyright (c) 2011-2019, The DART development contributors
# All rights reserved.
#
# The list of contributors can be found at:
#   https://github.com/dartsim/dart/blob/master/LICENSE
#
# This file is provided under the "BSD-style" License

# Find IPOPT
#
# This sets the following variables:
#   IPOPT_FOUND
#   IPOPT_INCLUDE_DIRS
#   IPOPT_LIBRARIES
#   IPOPT_DEFINITIONS
#   IPOPT_VERSION
#
# and the following targets:
#   IPOPT::ipopt

find_package(PkgConfig QUIET)

# Check to see if pkgconfig is installed.
pkg_check_modules(PC_IPOPT ipopt QUIET)

# Definitions
set(IPOPT_DEFINITIONS ${PC_IPOPT_CFLAGS_OTHER})

# Include directories
find_path(IPOPT_INCLUDE_DIRS
        NAMES IpIpoptNLP.hpp
        HINTS ${PC_IPOPT_INCLUDEDIR}
        PATHS "${CMAKE_INSTALL_PREFIX}/include")

# Libraries
find_library(IPOPT_LIBRARIES
        NAMES ipopt
        HINTS ${PC_IPOPT_LIBDIR})

# Version
set(IPOPT_VERSION ${PC_IPOPT_VERSION})

# Set (NAME)_FOUND if all the variables and the version are satisfied.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(IPOPT
        FAIL_MESSAGE  DEFAULT_MSG
        REQUIRED_VARS IPOPT_INCLUDE_DIRS IPOPT_LIBRARIES
        VERSION_VAR   IPOPT_VERSION)

# Include Ipopt directories and link libraries to the project
target_include_directories(MyExample PUBLIC ${IPOPT_INCLUDE_DIRS})
target_link_libraries(MyExample ${IPOPT_LIBRARIES})
