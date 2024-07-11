project(gifimage)

find_package(Qt6 REQUIRED COMPONENTS Gui)

add_library(gifimage
    gifimage/qgifimage.cpp
)

add_subdirectory(3rdParty)

target_link_libraries(gifimage PRIVATE Qt6::Gui)
target_link_libraries(gifimage PUBLIC 3rdParty)
