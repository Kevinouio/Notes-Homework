# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/kevinho/Desktop/Lab10/build/gmp/src/gmp")
  file(MAKE_DIRECTORY "/Users/kevinho/Desktop/Lab10/build/gmp/src/gmp")
endif()
file(MAKE_DIRECTORY
  "/Users/kevinho/Desktop/Lab10/build/gmp/src/gmp-build"
  "/Users/kevinho/Desktop/Lab10/build/gmp"
  "/Users/kevinho/Desktop/Lab10/build/gmp/tmp"
  "/Users/kevinho/Desktop/Lab10/build/gmp/src/gmp-stamp"
  "/Users/kevinho/Desktop/Lab10/build/gmp/src"
  "/Users/kevinho/Desktop/Lab10/build/gmp/src/gmp-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/kevinho/Desktop/Lab10/build/gmp/src/gmp-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/kevinho/Desktop/Lab10/build/gmp/src/gmp-stamp${cfgdir}") # cfgdir has leading slash
endif()
