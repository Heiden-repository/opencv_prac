CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

add_compile_options(-std=c++11)

PROJECT(opencv_prac)

find_package(OpenCV 4.1.0 REQUIRED)

add_executable(opencv_prac
		src/RANSAC.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(opencv_prac
	${OpenCV_LIBS}
)