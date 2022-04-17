cmake_minimum_required(VERSION 3.5)
project(xarm_sdk)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
            -Wno-error-all
            -Wno-error-extra
            -Wno-error-pedantic
            -Wno-mismatched-new-delete
    )
endif()

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fPIC")

include($ENV{BCR_INSTALLATION_DIR}/cmake/sanitizers.cmake NO_POLICY_SCOPE)

find_package(ament_cmake REQUIRED)

file(GLOB_RECURSE CC_SRC ${PROJECT_SOURCE_DIR}/*.cc )
add_library (${PROJECT_NAME} ${CC_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

add_executable(main main.cpp)
target_link_libraries(main ${PROJECT_NAME})

install(
        TARGETS ${PROJECT_NAME}
        EXPORT export_${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/
        DESTINATION include
        )

ament_export_libraries(${PROJECT_NAME})
ament_export_include_directories(include)
ament_package()