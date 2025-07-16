
function(gge_log message)
    message(STATUS ${message})
endfunction()



function(setup_third_party_common DIRNAME INCLUDEDIR)
    gge_log("(common) ${DIRNAME}")
    add_subdirectory("${GGE_THIRD_PARTY_DIR}/${DIRNAME}")

    if(NOT INCLUDEDIR STREQUAL "")
        include_directories("${GGE_THIRD_PARTY_DIR}/${DIRNAME}/${INCLUDEDIR}")
    endif()
endfunction()

function(setup_third_party_header_only DIRNAME HEADERS_DIR)
    gge_log("(header-only) ${DIRNAME}")
    include_directories(BEFORE "${GGE_THIRD_PARTY_DIR}/${DIRNAME}/${HEADERS_DIR}")
endfunction()

function(setup_third_party_complex DIRNAME CMAKEDIRNAME)
    gge_log("(complex) ${DIRNAME}")
    add_subdirectory("${GGE_THIRD_PARTY_DIR}/${DIRNAME}/${CMAKEDIRNAME}")
endfunction()



function(setup_core_library LIBNAME DIRNAME)
    gge_log("(library: ${LIBNAME}) ${DIRNAME}")
    add_subdirectory("${DIRNAME}")    
endfunction()

function(setup_core_executable EXENAME DIRNAME)
    gge_log("(executable: ${EXENAME}) ${DIRNAME}")
    add_subdirectory("${DIRNAME}")
endfunction()

