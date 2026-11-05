cmake_minimum_required(VERSION 3.28...3.30)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/common/bootstrap.cmake" NO_POLICY_SCOPE)

project(obs-studio VERSION ${OBS_VERSION_CANONICAL})

option(OBS_AMD_LITE "Build OBS Lite AMD Edition (AMD-only, minimal footprint)" OFF)
option(OBS_MAC_LITE "Build SiliconCast (Apple Silicon/macOS minimal footprint)" OFF)

if(OBS_MAC_LITE)
  set(OBS_PRODUCT_NAME "SiliconCast")
endif()

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
  include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/windows/architecture.cmake")
  if(NOT OBS_PARENT_ARCHITECTURE STREQUAL CMAKE_VS_PLATFORM_NAME)
    return()
  endif()
endif()

include(compilerconfig)
include(defaults)
include(helpers)

option(ENABLE_UI "Enable building with UI (requires Qt)" ON)
option(ENABLE_SCRIPTING "Enable scripting support" OFF)
option(ENABLE_HEVC "Enable HEVC encoders" ON)

add_subdirectory(libobs)
if(OS_WINDOWS)
  add_subdirectory(libobs-d3d11)
  add_subdirectory(libobs-winrt)
endif()

if(NOT OBS_AMD_LITE)
  add_subdirectory(libobs-opengl)
endif()

add_subdirectory(plugins)

if(NOT OBS_AMD_LITE AND NOT OBS_MAC_LITE)
  add_subdirectory(test/test-input)
endif()

add_subdirectory(UI)

message_configuration()
