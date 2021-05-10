ADD_EXECUTABLE(sir-sym-test ./sir.test.cpp)

set_target_properties(
        sir-sym-test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)

# todo link to SIR lib
#TARGET_LINK_LIBRARIES(tests)
