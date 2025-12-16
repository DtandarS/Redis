cmake_minimum_required(VERSION 3.16.0)

#====================================#

project(Redis.io)

#====================================#

add_library( HEADER_FILES INTERFACE )

#====================================#

set( SOURCE_FILES mainc.pp )
set( CMAKE_CXX_STANDARD 17 )

#====================================#

add_executable(Redis.io ${SOURCE_FILES})

#====================================#

target_include_directories
(

  HEADER_FILES

  INTERFACE

  ${CMAKE_CURRENT_SOURCE_DIR}/lib

)

#====================================#

target_link_libraries(

  Redis.io PRIVATE

  HEADER_FILES

)

#====================================#
