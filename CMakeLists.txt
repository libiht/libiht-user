cmake_minimum_required(VERSION 3.10)
project(libiht
    VERSION 0.1.0
    DESCRIPTION "Intel Hardware Trace Library - Userspace Componment"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Platform detection and configuration
if(WIN32)
    add_compile_definitions(IHT_PLATFORM_WINDOWS)
elseif(LINUX)
    add_compile_definitions(IHT_PLATFORM_LINUX)
endif()

# Configurable options: build as shared or static library, build tests
option(LIBIHT_BUILD_SHARED "Build libiht as a shared library" ON)
option(LIBIHT_BUILD_TESTS  "Build tests for libiht" ON)

# Library sources configuration
set(LIBIHT_SOURCES
    src/bts.c
    src/iht-common.c
    src/lbr.c
    src/trace.c
    src/version.c
)

set(LIBIHT_LINUX_SOURCES
    src/linux/ioctl.c
)

set(LIBIHT_WIN_SOURCES
    # src/win/...
)

# Platform-specific sources
if(IHT_PLATFORM_LINUX)
    list(APPEND LIBIHT_SOURCES LIBIHT_LINUX_SRC)
elseif(IHT_PLATFORM_WINDOWS)
    # Add Windows-specific sources here when available
    list(APPEND LIBIHT_SOURCES LIBIHT_WIN_SRC)
endif()

# Decide library type
if(LIBIHT_BUILD_SHARED)
  add_library(iht SHARED ${LIBIHT_SOURCES})
  message(STATUS "Building libiht as a SHARED library")
else()
  add_library(iht STATIC ${LIBIHT_SOURCES})
  message(STATUS "Building libiht as a STATIC library")
endif()

# Include directories
target_include_directories(iht PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(iht PRIVATE -Wall -Wextra -Werror)

# Installation configuration
install(TARGETS iht
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES include/iht.h DESTINATION include)
install(DIRECTORY include/iht DESTINATION include)

# Optional: Enable testing if needed
enable_testing()
# add_subdirectory(test)  # Uncomment when tests are ready