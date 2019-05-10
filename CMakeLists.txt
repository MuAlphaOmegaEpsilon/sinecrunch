###############################################################################
#                                CMAKE VERSION                                #
###############################################################################
CMAKE_MINIMUM_REQUIRED (VERSION 3.9.2)




###############################################################################
#                                   PROJECT                                   #
###############################################################################
PROJECT (sinecrunch 
		VERSION 1.0.0 
		LANGUAGES CXX 
		DESCRIPTION "A C++ repository to test different algorithms to sample sinewaves as fast as possible, taking into account precision loss.")




###############################################################################
#                       GOOGLE BENCMHMARK VAR OVERRIDES                       #
###############################################################################
SET (BENCHMARK_DOWNLOAD_DEPENDENCIES ON CACHE BOOL "Enable dependencies download" FORCE)
SET (BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disabling Google Benchmark's GTest tests" FORCE)
SET (BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing Google Benchmark's tests" FORCE)
SET (BENCHMARK_ENABLE_EXCEPTIONS OFF CACHE BOOL "Suppressing Google Benchmark's exceptions" FORCE)
SET (BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Disabling Google Benchmark's installation" FORCE)




###############################################################################
#                             CMAKE DEPENDENCIES                              #
###############################################################################
ADD_SUBDIRECTORY (libs/benchmark)




###############################################################################
#                                 EXECUTABLE                                  #
###############################################################################
ADD_EXECUTABLE (sinecrunch "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/main.cpp")
SET_TARGET_PROPERTIES (sinecrunch PROPERTIES
            						CXX_STANDARD 11
            						CXX_EXTENSIONS OFF)




###############################################################################
#                                  HEADERS                                    #
###############################################################################
TARGET_INCLUDE_DIRECTORIES (sinecrunch PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/benchmark/include)




###############################################################################
#                                  LINKAGE                                    #
###############################################################################
TARGET_LINK_LIBRARIES (sinecrunch benchmark)
