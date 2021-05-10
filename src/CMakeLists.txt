ADD_EXECUTABLE(sir-sym main.cpp)

ADD_SUBDIRECTORY(Model)
ADD_SUBDIRECTORY(Visualizer)
ADD_SUBDIRECTORY(Parser)

TARGET_LINK_LIBRARIES(sir-sym sir-model sir-visualizer parser)

set_target_properties(
        sir-sym PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)
