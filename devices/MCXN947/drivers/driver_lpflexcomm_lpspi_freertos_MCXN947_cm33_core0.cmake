include_guard()
message("driver_lpflexcomm_lpspi_freertos component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_lpspi_freertos.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common_MCXN947_cm33_core0)

include(driver_lpflexcomm_MCXN947_cm33_core0)

include(driver_lpspi_MCXN947_cm33_core0)

include(middleware_freertos-kernel_MCXN947_cm33_core0)

