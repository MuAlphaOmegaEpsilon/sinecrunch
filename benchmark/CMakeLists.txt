###############################################################################
#                                CMAKE VERSION                                #
###############################################################################
CMAKE_MINIMUM_REQUIRED (VERSION 3.11.4)




###############################################################################
#                                   PROJECT                                   #
###############################################################################
PROJECT (BM_sinecrunch
		VERSION 1.0.0 
		LANGUAGES CXX 
		DESCRIPTION "Benchmark for sinecrunch")




###############################################################################
#                                 EXECUTABLE                                  #
###############################################################################
ADD_EXECUTABLE (BM_sinecrunch "${CMAKE_CURRENT_SOURCE_DIR}/BM_sinecrunch.cpp")
SET_TARGET_PROPERTIES (BM_sinecrunch PROPERTIES 
										CXX_STANDARD 11 
										CXX_STANDARD_REQUIRED YES 
										CXX_EXTENSIONS OFF)




###############################################################################
#                             CMAKE DEPENDENCIES                              #
###############################################################################
ADD_SUBDIRECTORY (${CMAKE_CURRENT_LIST_DIR}/.. ${CMAKE_CURRENT_LIST_DIR}/sinecrunch)




###############################################################################
#                                  HEADERS                                    #
###############################################################################
TARGET_INCLUDE_DIRECTORIES (BM_sinecrunch PRIVATE ${CMAKE_CURRENT_LIST_DIR}/libs/FastTrigo)
TARGET_INCLUDE_DIRECTORIES (BM_sinecrunch PRIVATE ${CMAKE_CURRENT_LIST_DIR}/libs/sltbench/include)




###############################################################################
#                                  SOURCES                                    #
###############################################################################
file (GLOB sltbench_SRC "${CMAKE_CURRENT_LIST_DIR}/libs/sltbench/src/*.cpp")
TARGET_SOURCES (BM_sinecrunch PRIVATE ${sltbench_SRC})
TARGET_SOURCES (BM_sinecrunch PRIVATE ${CMAKE_CURRENT_LIST_DIR}/libs/FastTrigo/fasttrigo.cpp)





###############################################################################
#                                  LINKING                                    #
###############################################################################
TARGET_LINK_LIBRARIES (BM_sinecrunch sinecrunch)




###############################################################################
#                                   FLAGS                                     #
###############################################################################
IF (MSVC)
		TARGET_COMPILE_OPTIONS (BM_sinecrunch PRIVATE /Wall /WX /sdl)
	ELSE ()
		TARGET_COMPILE_OPTIONS (BM_sinecrunch PRIVATE -Wall -Wextra -Werror -Wpedantic) #-Wconversion -Wcast-align -Wunused -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces)
ENDIF ()
