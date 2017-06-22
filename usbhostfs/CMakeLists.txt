cmake_minimum_required(VERSION 2.8)

project(usbhostfs)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O3 -std=gnu99 -D__PSP2__")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -D__PSP2__")

include_directories(
)

link_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/stubs
)

add_executable(${PROJECT_NAME}
        main.c
        host_driver.c
        )

target_link_libraries(${PROJECT_NAME}
        k
        SceSysmemForDriver_stub
        SceThreadmgrForDriver_stub
        SceIofilemgrForDriver_stub
        SceSysclibForDriver_stub
        SceUdcdForDriver_stub
        SceCpuForDriver_stub
        taihenForKernel_stub
        SceDebugForDriverExtra_stub
        gcc
        -nostdlib
        )
vita_create_self(${PROJECT_NAME}.skprx ${PROJECT_NAME}
        CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/exports.yml
        UNSAFE)

add_custom_target(${PROJECT_NAME}.stubs
        COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/stubs
        COMMAND ${VITASDK}/bin/vita-libs-gen ${CMAKE_CURRENT_SOURCE_DIR}/extra.yml ${CMAKE_CURRENT_BINARY_DIR}/stubs
        COMMAND VITASDK=${VITASDK} make -C ${CMAKE_CURRENT_BINARY_DIR}/stubs
        )
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}.stubs)
