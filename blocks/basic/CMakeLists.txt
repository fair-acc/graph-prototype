add_library(gr-basic INTERFACE)
target_link_libraries(gr-basic INTERFACE gnuradio-core gnuradio-algorithm)
target_include_directories(gr-basic INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/> $<INSTALL_INTERFACE:include/>)

if (ENABLE_TESTING)
    add_subdirectory(test)
endif ()
