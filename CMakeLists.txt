# cmake version check
cmake_minimum_required( VERSION 3.0 )
 
# project name
project( "object-tracker-cpp" C CXX)
 
# Build configuration
set( CMAKE_BUILD_TYPE Debug )
set( CMAKE_VERBOSE_MAKEFILE true )

# opencv 
set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
find_package(OpenCV REQUIRED)
find_package(POCO REQUIRED)
find_package(JSONCPP REQUIRED)
#find_package(LIBGQLPARSER REQUIRED)

# Build custom configuration
set( DX_BUILD_ARM OFF )


#################################################3
# Build Target & source file list
set( OBJTRK_ENGINE
        "objtrack_engine"
        )

set( OBJTRK_ENGINE_TEST
        "objtrack_engine_test"
        )        

set( SRC_FILES
        # test codes
        # test/ws_client.cpp
        samples/operato_connect_test.cpp
        samples/jsoncpp_test.cpp
        # test/NotificationQueue.cpp
        # test/ObjectTrackingEngine.cpp
        # test/ObjectTrackingEngineTest

        # entry
        entry/Entry.cpp

        # opencv
        opencv/CameraCalibrationOpencv.cpp

        # connection
        connection/RoboticsConnection.cpp

        # worker
        taskbase/TaskManager.cpp

        # cameracalib
        tasks/CameraCalibrationTask.cpp
        tasks/HandEyeCalibrationTask.cpp
        )

set( TEST_FILES
        # test codes
        test/OTETestSuite.cpp
        test/TaskTest.cpp
        test/TestMain.cpp
        )

# TODO: make toolchain selections here
# set( CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc" )
# set( CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++" )
# set(CMAKE_LINKER "arm-linux-gnueabihf-ld")
# set(CMAKE_NM "arm-linux-gnueabihf-nm")
# set(CMAKE_OBJCOPY "arm-linux-gnueabihf-objcopy")
# set(CMAKE_OBJDUMP "arm-linux-gnueabihf-objdump")
# set(CMAKE_RANLIB "arm-linux-gnueabihf-gcc-ranlib")
set( CMAKE_C_COMPILER "gcc" )
set( CMAKE_CXX_COMPILER "g++" )
set(CMAKE_NM "nm")
set(CMAKE_OBJCOPY "objcopy")
set(CMAKE_OBJDUMP "objdump")
set(CMAKE_RANLIB "ranlib")

# include directories
set( OBJTRK_ENGINE_INCLUDES
        ./
        )

include_directories( ${OBJTRK_ENGINE_INCLUDES} /home/jinwon/Documents/opencv/opencv-4.2.0/include ${POCO_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS} ${JSONCPP_INCLUDE_DIR})

# common compile option
add_compile_options( -g -Wall )
# set( CMAKE_EXE_LINKER_FLAGS "-dynamic -Wl,--gc-sections" )

# compile option for libraries
link_libraries( pthread )

# library directories
link_directories(/usr/lib /usr/local/lib)
 
# debug options
set( CMAKE_C_FLAGS_DEBUG "-DDEBUG -DC_FLAGS" )
set( CMAKE_EXE_LINKER_FLAGS_DEBUG "-DDEBUG -DLINKER_FLAGS" )
 
# release options
set( CMAKE_C_FLAGS_RELEASE "-DRELEASE -DC_FLAGS" )
set( CMAKE_EXE_LINKER_FLAGS_RELEASE "-DRELEASE -DLINKER_FLAGS" )
 
# output directories
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE}/lib )
 
# add libraries if necessary,
#add_library( ${SRC_LIBRARY} STATIC ${SRC_FILES} )

# add excutable
ADD_EXECUTABLE (${OBJTRK_ENGINE} ${SRC_FILES})
TARGET_LINK_LIBRARIES (${OBJTRK_ENGINE} ${OpenCV_LIBS} ${POCO_FOUNDATION} ${POCO_NET_LIBRARY} ${POCO_JSON_LIBRARY} ${POCO_UTIL_LIBRARY} ${JSONCPP_LIBRARY})

# TODO: add unit tests
# ADD_EXECUTABLE (${OBJTRK_ENGINE_TEST} ${TEST_FILES})
# TARGET_LINK_LIBRARIES (${OBJTRK_ENGINE_TEST} ${OpenCV_LIBS} ${POCO_FOUNDATION} ${POCO_NET_LIBRARY} ${POCO_JSON_LIBRARY} ${POCO_UTIL_LIBRARY})



