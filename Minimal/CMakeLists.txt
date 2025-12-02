# Setup the project
cmake_minimum_required(VERSION 3.16)
project(Minimal)

# Find Geant4 package, activating all available UI and Vis drivers by default
find_package(Geant4 REQUIRED ui_all vis_all)

# Locate sources and headers for this project
file(GLOB sources src/*.cc)
file(GLOB headers include/*.hh)

# Add the executable, use our local headers, and link it to the Geant4 libraries
add_executable(Minimal Minimal.cc ${sources} ${headers})
target_include_directories(Minimal PRIVATE include)
target_link_libraries(Minimal ${Geant4_LIBRARIES})

file(COPY vis.mac DESTINATION ${PROJECT_BINARY_DIR})
