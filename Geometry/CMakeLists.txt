# Setup the project
cmake_minimum_required(VERSION 3.16)
project(Geometry)

# Find Geant4 package, activating all available UI and Vis drivers by default
find_package(Geant4 REQUIRED ui_all vis_all)

# Locate sources and headers for this project
file(GLOB sources src/*.cc)
file(GLOB headers include/*.hh)

# Add the executable, use our local headers, and link it to the Geant4 libraries
add_executable(Geometry Geometry.cc ${sources} ${headers})
target_include_directories(Geometry PRIVATE include)
target_link_libraries(Geometry ${Geant4_LIBRARIES})

file(COPY vis.mac DESTINATION ${PROJECT_BINARY_DIR})
