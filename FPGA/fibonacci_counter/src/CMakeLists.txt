include(Quartus)

configure_file(top.qsf top.qsf)
configure_file(top.srf top.srf)
configure_file(top.sdc top.sdc)

set(FPGA_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/alien_debouncer.v
    ${CMAKE_CURRENT_SOURCE_DIR}/clicker.v
    ${CMAKE_CURRENT_SOURCE_DIR}/clk_div.v
    ${CMAKE_CURRENT_SOURCE_DIR}/counter.v
    ${CMAKE_CURRENT_SOURCE_DIR}/fib_counter.v
    ${CMAKE_CURRENT_SOURCE_DIR}/hex_display.v
    ${CMAKE_CURRENT_SOURCE_DIR}/top.v)

message("-- CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("-- FPGA_SOURCES: ${FPGA_SOURCES}")

add_fpga(PROJECT top
         FAMILY "Cyclone IV E"
         PART "EP4CE6E22C8"
         SOURCES ${FPGA_SOURCES})

add_custom_command(OUTPUT __program__
                   COMMAND ${QUARTUS_PGM_EXECUTABLE} --mode=jtag -o \"P\;top.sof\"
                   DEPENDS top.sof)

add_custom_target(synthesis DEPENDS top.sta.rpt)
add_custom_target(program DEPENDS __program__)

