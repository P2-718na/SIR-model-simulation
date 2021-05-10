ADD_EXECUTABLE(sir-sym-test ./sir.test.cpp)

set_target_properties(
        sir-sym-test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)

TARGET_LINK_LIBRARIES(sir-sym-test sir-model)
