# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles\\MiniAmazonCLI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MiniAmazonCLI_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\MiniAmazonGUI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MiniAmazonGUI_autogen.dir\\ParseCache.txt"
  "MiniAmazonCLI_autogen"
  "MiniAmazonGUI_autogen"
  )
endif()
