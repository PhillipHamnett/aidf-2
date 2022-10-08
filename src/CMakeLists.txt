cmake_minimum_required(VERSION 3.23)
project(escrowtest)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( escrowtest escrowtest escrowtest.cpp )
target_include_directories( escrowtest PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( escrowtest ${CMAKE_SOURCE_DIR}/../ricardian )
