cmake_minimum_required(VERSION 3.16.0)

#====================================#

 project(server)
# project(client)

#====================================#

  add_library( HEADER_FILES INTERFACE )

#====================================#

  set( SOURCE_FILES main.cpp )
#  set( SOURCE_FILES client.cpp )
  set( CMAKE_CXX_STANDARD 17 )

#====================================#

  add_executable(server ${SOURCE_FILES})
#  add_executable(client ${SOURCE_FILES})

#====================================#

target_include_directories(

  HEADER_FILES

  INTERFACE

  ${CMAKE_CURRENT_SOURCE_DIR}/lib

)

#====================================#

target_link_libraries(

  server PRIVATE
#  client PRIVATE

  HEADER_FILES

)

#====================================#
