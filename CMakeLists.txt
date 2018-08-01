cmake_minimum_required(VERSION 3.1)


set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
include_directories(/home/zqp/mygithub/trackers_v2/include)
include_directories(/home/zqp/mygithub/IObjZoneDetect/include)
include_directories(./include)
include_directories(/usr/include/python2.7)

#file(GLOB src src/VehicleAnalyze.cpp)

find_library(track_lib TrackDP /home/zqp/mygithub/trackers_v2/lib)
find_library(detect_lib IObjZoneDetect /home/zqp/mygithub/IObjZoneDetect/lib)
find_library(boost_python_LIB boost_python)
message(STATUS ${boost_python_LIB})
find_package(OpenCV)

add_library(_IVehicleAnalyze SHARED src/PyIVehicleAnalyze.cpp)
target_link_libraries(_IVehicleAnalyze IVehicleAnalyze ${boost_python_LIB})

add_library(IVehicleAnalyze SHARED src/VehicleAnalyze.cpp)
target_link_libraries(IVehicleAnalyze ${track_lib} ${detect_lib} ${OpenCV_LIBS})
