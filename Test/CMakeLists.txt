
cmake_minimum_required (VERSION 3.8)

add_executable (Test "Test.cpp")

target_link_libraries(Test
    PUBLIC
    LooperLib
)

