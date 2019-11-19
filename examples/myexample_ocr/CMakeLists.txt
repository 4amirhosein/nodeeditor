file(GLOB_RECURSE CPPS  ./*.cpp )

add_executable(myexample_ocr ${CPPS})

target_link_libraries(myexample_ocr nodes)
