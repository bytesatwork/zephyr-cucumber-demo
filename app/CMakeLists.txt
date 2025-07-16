#-------------------------------------------------------------------------------
# Zephyr Example Application
#
# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

project(app LANGUAGES CXX)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

target_sources(app PRIVATE src/main.c)

if (CONFIG_BOARD_NATIVE_SIM_NATIVE_64)
    set(CUKE_ENABLE_GTEST ON)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../modules/cucumber cucumber)

    target_sources(app PRIVATE src/server.cpp src/steps.cpp)
    target_link_libraries(app PRIVATE cucumber-cpp-nomain)
endif()
