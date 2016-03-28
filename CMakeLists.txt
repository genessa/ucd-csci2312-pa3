cmake_minimum_required(VERSION 3.3)
project(ucd-csci2312-pa3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Cluster.h Clustering.cpp ClusteringTests.cpp ClusteringTests.h ErrorContext.cpp ErrorContext.h Exceptions.cpp Exceptions.h KMeans.cpp KMeans.h main.cpp Point.cpp Point.h )
add_executable(ucd-csci2312-pa3 ${SOURCE_FILES})