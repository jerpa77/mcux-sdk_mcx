# Add set(CONFIG_USE_middleware_rtcesl_cm33nodsp true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_CORE STREQUAL cm33) AND (CONFIG_FPU STREQUAL NO_FPU))

if(CONFIG_TOOLCHAIN STREQUAL iar)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_IAR/AMCLIB/Include
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_IAR/GDFLIB/Include
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_IAR/GFLIB/Include
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_IAR/GMCLIB/Include
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_IAR/MLIB/Include
)
endif()

if(CONFIG_TOOLCHAIN STREQUAL mdk)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_KEIL/AMCLIB/Include
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_KEIL/GDFLIB/Include
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_KEIL/GFLIB/Include
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_KEIL/GMCLIB/Include
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_KEIL/MLIB/Include
)
endif()

if((CONFIG_TOOLCHAIN STREQUAL mcux OR CONFIG_TOOLCHAIN STREQUAL armgcc))
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_MCUX/AMCLIB/Include
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_MCUX/GDFLIB/Include
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_MCUX/GFLIB/Include
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_MCUX/GMCLIB/Include
  ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_MCUX/MLIB/Include
)
endif()

if(CONFIG_TOOLCHAIN STREQUAL iar)
  target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
    -Wl,--start-group
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_IAR/AMCLIB/AMCLIB.a
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_IAR/GFLIB/GFLIB.a
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_IAR/GDFLIB/GDFLIB.a
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_IAR/GMCLIB/GMCLIB.a
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_IAR/MLIB/MLIB.a
      -Wl,--end-group
  )
endif()

if(CONFIG_TOOLCHAIN STREQUAL mdk)
  target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
    -Wl,--start-group
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_KEIL/AMCLIB/AMCLIB.lib
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_KEIL/GFLIB/GFLIB.lib
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_KEIL/GDFLIB/GDFLIB.lib
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_KEIL/GMCLIB/GMCLIB.lib
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_KEIL/MLIB/MLIB.lib
      -Wl,--end-group
  )
endif()

if((CONFIG_TOOLCHAIN STREQUAL mcux OR CONFIG_TOOLCHAIN STREQUAL armgcc))
  target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
    -Wl,--start-group
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_MCUX/AMCLIB/libAMCLIB.a
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_MCUX/GFLIB/libGFLIB.a
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_MCUX/GDFLIB/libGDFLIB.a
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_MCUX/GMCLIB/libGMCLIB.a
      ${CMAKE_CURRENT_LIST_DIR}/CM33NODSP_RTCESL_4.7.1_MCUX/MLIB/libMLIB.a
      -Wl,--end-group
  )
endif()

else()

message(SEND_ERROR "middleware_rtcesl_cm33nodsp dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()