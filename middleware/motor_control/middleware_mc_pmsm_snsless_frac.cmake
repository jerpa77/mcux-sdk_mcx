# Add set(CONFIG_USE_middleware_mc_pmsm_snsless_frac true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_CORE STREQUAL cm33) AND CONFIG_USE_middleware_motor_control_pmsm_frac_template AND (CONFIG_USE_middleware_rtcesl_cm33nodsp))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_frac/mc_algorithms/pmsm_control.c
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_frac/state_machine/state_machine.c
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_frac/mc_state_machine/m1_sm_snsless.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_frac/mc_algorithms
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_frac/state_machine
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_frac/mc_state_machine
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DPMSM_SNSLESS
  )

endif()

else()

message(SEND_ERROR "middleware_mc_pmsm_snsless_frac dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()