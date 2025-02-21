# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\login_window_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\login_window_autogen.dir\\ParseCache.txt"
  "login_window_autogen"
  )
endif()
