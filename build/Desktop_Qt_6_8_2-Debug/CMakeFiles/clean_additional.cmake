# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/pasman_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/pasman_autogen.dir/ParseCache.txt"
  "pasman_autogen"
  )
endif()
