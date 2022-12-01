add_executable(timer timer.cpp)
target_link_libraries(timer EvtHandleNet)

add_executable(connectionTest connectionTest.cpp)
target_link_libraries(connectionTest EvtHandleNet)

add_executable(discard discard.cpp)
target_link_libraries(discard EvtHandleNet)