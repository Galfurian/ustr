# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/enrico/repository/personal/fsmlib/build/_deps/doxygenawesome-src"
  "/home/enrico/repository/personal/fsmlib/build/_deps/doxygenawesome-build"
  "/home/enrico/repository/personal/fsmlib/build/_deps/doxygenawesome-subbuild/doxygenawesome-populate-prefix"
  "/home/enrico/repository/personal/fsmlib/build/_deps/doxygenawesome-subbuild/doxygenawesome-populate-prefix/tmp"
  "/home/enrico/repository/personal/fsmlib/build/_deps/doxygenawesome-subbuild/doxygenawesome-populate-prefix/src/doxygenawesome-populate-stamp"
  "/home/enrico/repository/personal/fsmlib/build/_deps/doxygenawesome-subbuild/doxygenawesome-populate-prefix/src"
  "/home/enrico/repository/personal/fsmlib/build/_deps/doxygenawesome-subbuild/doxygenawesome-populate-prefix/src/doxygenawesome-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/enrico/repository/personal/fsmlib/build/_deps/doxygenawesome-subbuild/doxygenawesome-populate-prefix/src/doxygenawesome-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/enrico/repository/personal/fsmlib/build/_deps/doxygenawesome-subbuild/doxygenawesome-populate-prefix/src/doxygenawesome-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
