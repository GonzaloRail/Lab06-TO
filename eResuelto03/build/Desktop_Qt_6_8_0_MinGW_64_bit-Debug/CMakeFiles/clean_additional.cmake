# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\eResuelto03_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\eResuelto03_autogen.dir\\ParseCache.txt"
  "eResuelto03_autogen"
  )
endif()
