cmake_minimum_required(VERSION 3.5)
project(xarm_sdk)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE CC_SRC ${PROJECT_SOURCE_DIR}/*.cc )
add_library (${PROJECT_NAME} ${CC_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

add_executable(xarm_main main.cpp)
target_link_libraries(xarm_main ${PROJECT_NAME})

install(
        TARGETS ${PROJECT_NAME}
        EXPORT export_${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)