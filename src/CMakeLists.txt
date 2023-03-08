file(GLOB_RECURSE SOURCE_FILES *.cc)

add_executable(${TARGET_NAME} ${SOURCE_FILES})
include_directories(${CMAKE_SOURCE_DIR}/include)
