cmake_minimum_required(VERSION 2.8)

if(APPLE AND NOT DEFINED ENV{MACOSX_DEPLOYMENT_TARGET} AND NOT DEFINED ENV{SDKROOT})
  set(CMAKE_OSX_DEPLOYMENT_TARGET ${CMAKE_SYSTEM_VERSION})
endif()
project(KVSWebRTCCanary LANGUAGES C CXX)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_MACOSX_RPATH TRUE)

include(FetchContent)
FetchContent_Declare(
  webrtc
  GIT_REPOSITORY https://github.com/awslabs/amazon-kinesis-video-streams-webrtc-sdk-c
  GIT_TAG        master
)

FetchContent_GetProperties(webrtc)
if(NOT webrtc_POPULATED)
  FetchContent_Populate(webrtc)
  add_subdirectory(${webrtc_SOURCE_DIR} ${webrtc_BINARY_DIR})
endif()

# pass ca cert location to sdk
add_definitions(-DKVS_CA_CERT_PATH="${webrtc_SOURCE_DIR}/certs/cert.pem")
add_definitions(-DCMAKE_DETECTED_CACERT_PATH)

message(STATUS "source dir is ${webrtc_SOURCE_DIR}")

include_directories(${webrtc_SOURCE_DIR}/src/include)
include_directories(${webrtc_SOURCE_DIR}/open-source/include)
link_directories(${webrtc_SOURCE_DIR}/open-source/lib)

find_package(AWSSDK REQUIRED COMPONENTS monitoring events logs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(
  kvsWebRtcSampleCloudwatchMaster
  Common.c
  KvsWebRtcSampleCloudwatchMaster.c)
target_link_libraries(kvsWebRtcSampleCloudwatchMaster kvsWebrtcClient kvsWebrtcSignalingClient kvspicUtils ${AWSSDK_LINK_LIBRARIES})

