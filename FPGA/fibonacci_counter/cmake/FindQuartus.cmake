include(FindPackageHandleStandardArgs)

set(QUARTUS_PATH
    ${HOME}/intel/intelFPGA_lite/18.1/quartus/bin)

find_program(QUARTUS_SH_EXECUTABLE NAMES quartus_sh
             PATH ${QUARTUS_PATH})
find_program(QUARTUS_MAP_EXECUTABLE NAMES quartus_map
             PATH ${QUARTUS_PATH})
find_program(QUARTUS_FIT_EXECUTABLE NAMES quartus_fit
             PATH ${QUARTUS_PATH})
find_program(QUARTUS_ASM_EXECUTABLE NAMES quartus_asm
             PATH ${QUARTUS_PATH})
find_program(QUARTUS_STA_EXECUTABLE NAMES quartus_sta
             PATH ${QUARTUS_PATH})
find_program(QUARTUS_PGM_EXECUTABLE NAMES quartus_pgm
             PATH ${QUARTUS_PATH})

find_package_handle_standard_args(Quartus FOUND_VAR QUARTUS_FOUND
                                  REQUIRED_VARS
                                  QUARTUS_SH_EXECUTABLE
                                  QUARTUS_MAP_EXECUTABLE
                                  QUARTUS_FIT_EXECUTABLE
                                  QUARTUS_ASM_EXECUTABLE
                                  QUARTUS_STA_EXECUTABLE
                                  QUARTUS_PGM_EXECUTABLE)
