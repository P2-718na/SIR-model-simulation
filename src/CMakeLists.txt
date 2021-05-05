ADD_EXECUTABLE(sir-sym main.cpp)

ADD_SUBDIRECTORY(Model)
ADD_SUBDIRECTORY(Visualizer)

TARGET_LINK_LIBRARIES(sir-sym sir-model sir-visualizer)
TARGET_LINK_LIBRARIES(sir-sym sfml-graphics)
