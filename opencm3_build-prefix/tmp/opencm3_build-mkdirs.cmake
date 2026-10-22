# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/smorz/Desktop/LABS_PM/practice_4/libopencm3")
  file(MAKE_DIRECTORY "C:/Users/smorz/Desktop/LABS_PM/practice_4/libopencm3")
endif()
file(MAKE_DIRECTORY
  "C:/Users/smorz/Desktop/LABS_PM/practice_4/opencm3_build-prefix/src/opencm3_build-build"
  "C:/Users/smorz/Desktop/LABS_PM/practice_4/opencm3_build-prefix"
  "C:/Users/smorz/Desktop/LABS_PM/practice_4/opencm3_build-prefix/tmp"
  "C:/Users/smorz/Desktop/LABS_PM/practice_4/opencm3_build-prefix/src/opencm3_build-stamp"
  "C:/Users/smorz/Desktop/LABS_PM/practice_4/opencm3_build-prefix/src"
  "C:/Users/smorz/Desktop/LABS_PM/practice_4/opencm3_build-prefix/src/opencm3_build-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/smorz/Desktop/LABS_PM/practice_4/opencm3_build-prefix/src/opencm3_build-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/smorz/Desktop/LABS_PM/practice_4/opencm3_build-prefix/src/opencm3_build-stamp${cfgdir}") # cfgdir has leading slash
endif()
