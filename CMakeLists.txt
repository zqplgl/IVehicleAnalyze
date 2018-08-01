cmake_minimum_required(VERSION 3.1)


set(CMAKE_CXX_FLAGS "-std=c++11")
include_directories(/home/zqp/mygithub/trackers_v2/include)
include_directories(/home/zqp/mygithub/IObjZoneDetect/include)
include_directories(./include)

file(GLOB src src/*.cpp)

find_library(track_lib TrackDP /home/zqp/mygithub/trackers_v2/lib)
find_library(detect_lib IObjZoneDetect /home/zqp/mygithub/IObjZoneDetect/lib)
find_package(OpenCV)


add_library(IVehicleAnalyze SHARED ${src})
target_link_libraries(IVehicleAnalyze ${track_lib} ${detect_lib} ${OpenCV_LIBS})