include_guard()
message("device_MCXN947_system component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/system_MCXN947_cm33_core1.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(device_MCXN947_CMSIS_MCXN947_cm33_core1)
