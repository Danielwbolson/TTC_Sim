#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MinGfx::MinGfx" for configuration "Release"
set_property(TARGET MinGfx::MinGfx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MinGfx::MinGfx PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/MinGfx-1.0/MinGfx.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS MinGfx::MinGfx )
list(APPEND _IMPORT_CHECK_FILES_FOR_MinGfx::MinGfx "${_IMPORT_PREFIX}/lib/MinGfx-1.0/MinGfx.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
