cmake_minimum_required(VERSION 3.10)
project(ThreadingProfiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(include)

add_library(ThreadingProfiler SHARED
    src/interpose/threads_interpose.cxx
    src/interpose/mutex_interpose.cxx
    # src/wrappers.cxx
    # src/logger.cxx
    # src/utils.cxx
)

target_link_libraries(ThreadingProfiler dl pthread)
