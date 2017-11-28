cmake_minimum_required(VERSION 3.8)
project(TP2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Image2D.hpp Histogramme.hpp testGrayLevelImage2D.cpp Color.hpp testColorImage2D.cpp Image2DWriter.hpp Image2DReader.hpp invert-red-blue.cpp Accessor.hpp save-green-channel.cpp save-channels.cpp cathodic-screen.cpp generate-histogramme.cpp egaliseur-couleur.cpp testHSV.cpp)
add_executable(TP2 ${SOURCE_FILES})