ADD_EXECUTABLE(sir-test ./sir.test.cpp)

set_target_properties(
        sir-test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)

TARGET_LINK_LIBRARIES(sir-test sir-model)
