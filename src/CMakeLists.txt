ADD_EXECUTABLE(sir-sym main.cpp)

ADD_SUBDIRECTORY(Model)

TARGET_LINK_LIBRARIES(sir-sym sir-model)
TARGET_LINK_LIBRARIES(sir-sym sfml-graphics)
