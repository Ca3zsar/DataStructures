cmake_minimum_required(VERSION 3.10)

# Create the executable target
add_executable(TestSkip
    main.cpp
)

target_link_libraries(TestSkip
    PRIVATE DataStructures
)

install(
    TARGETS TestSkip
    DESTINATION bin
)

