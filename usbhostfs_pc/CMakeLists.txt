cmake_minimum_required(VERSION 3.0)

set(CMAKE_SYSTEM_NAME "Linux")

project(usbhostfs_pc)

add_executable(${PROJECT_NAME}
        main.c
        )

target_compile_options(${PROJECT_NAME} PRIVATE
        -DREADLINE_SHELL
        )

target_include_directories(${PROJECT_NAME} PRIVATE
        ../usbhostfs
        )

target_link_libraries(${PROJECT_NAME}
        usb
        readline
        pthread
        )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)