cmake_minimum_required(VERSION 3.10)
project(ThreadingProfiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(include)

add_library(ThreadingProfiler SHARED
    core/interpose/pthread_interpose.cpp
    core/interpose/mutex_interpose.cpp
)

include(FetchContent)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

target_link_libraries(ThreadingProfiler PRIVATE nlohmann_json::nlohmann_json dl pthread)

