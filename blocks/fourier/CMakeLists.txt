add_library(gr-fourier INTERFACE)
target_link_libraries(gr-fourier INTERFACE gnuradio-core gnuradio-algorithm)
target_include_directories(gr-fourier INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/> $<INSTALL_INTERFACE:include/>)

if (ENABLE_TESTING)
    add_subdirectory(test)
endif ()
