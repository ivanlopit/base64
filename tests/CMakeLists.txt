
add_executable(base64_tests
        main.cpp 
        block_api_test.cpp
        simple_api_test)

target_link_libraries(base64_tests 
        gtest 
        incr4k::base64)