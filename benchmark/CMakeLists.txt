###############################################################################
#                                CMAKE VERSION                                #
###############################################################################
CMAKE_MINIMUM_REQUIRED (VERSION 3.9.2)




###############################################################################
#                                   PROJECT                                   #
###############################################################################
PROJECT (BM_sinecrunch
		VERSION 1.0.0 
		LANGUAGES CXX 
		DESCRIPTION "Benchmark for sinecrunch")




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
ADD_SUBDIRECTORY (${CMAKE_CURRENT_LIST_DIR}/.. ${CMAKE_CURRENT_LIST_DIR}/sinecrunch)
ADD_SUBDIRECTORY (libs/benchmark)




###############################################################################
#                                 EXECUTABLE                                  #
###############################################################################
ADD_EXECUTABLE (BM_sinecrunch "${CMAKE_CURRENT_SOURCE_DIR}/BM_sinecrunch.cpp")
SET_TARGET_PROPERTIES (BM_sinecrunch PROPERTIES CXX_STANDARD 11 CXX_EXTENSIONS OFF)




###############################################################################
#                                  HEADERS                                    #
###############################################################################
TARGET_INCLUDE_DIRECTORIES (BM_sinecrunch PRIVATE ${CMAKE_CURRENT_LIST_DIR}/libs/benchmark/include)
TARGET_INCLUDE_DIRECTORIES (BM_sinecrunch PRIVATE ${CMAKE_CURRENT_LIST_DIR}/libs/FastTrigo)




###############################################################################
#                                  SOURCES                                    #
###############################################################################
TARGET_SOURCES (BM_sinecrunch PRIVATE ${CMAKE_CURRENT_LIST_DIR}/libs/FastTrigo/fasttrigo.cpp)




###############################################################################
#                                  LINKING                                    #
###############################################################################
TARGET_LINK_LIBRARIES (BM_sinecrunch sinecrunch)
TARGET_LINK_LIBRARIES (BM_sinecrunch benchmark)




###############################################################################
#                                   FLAGS                                     #
###############################################################################
IF (MSVC)
		TARGET_COMPILE_OPTIONS (BM_sinecrunch PRIVATE /Wall /WX /sdl)
	ELSE ()
		TARGET_COMPILE_OPTIONS (BM_sinecrunch PRIVATE -Wall -Wextra -Werror -Wpedantic -msse3) #-Wconversion -Wcast-align -Wunused -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces)
ENDIF ()
