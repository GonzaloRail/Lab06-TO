# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\eResuelto01_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\eResuelto01_autogen.dir\\ParseCache.txt"
  "eResuelto01_autogen"
  )
endif()
