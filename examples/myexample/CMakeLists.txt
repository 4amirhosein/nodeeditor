file(GLOB_RECURSE CPPS  ./*.cpp )

add_executable(myexample ${CPPS})

target_link_libraries(myexample nodes)
