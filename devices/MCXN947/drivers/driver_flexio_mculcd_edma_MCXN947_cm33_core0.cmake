include_guard()
message("driver_flexio_mculcd_edma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_flexio_mculcd_edma.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_edma4_MCXN947_cm33_core0)

include(driver_flexio_mculcd_MCXN947_cm33_core0)

