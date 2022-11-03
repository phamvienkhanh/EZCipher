cmake_minimum_required(VERSION 3.5)

project(ezcipher VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGL)

add_subdirectory(${CMAKE_SOURCE_DIR}/vendors/nodeeditor)

set(PROJECT_SOURCES
        main.cpp
        source/widget.cpp include/widget.h

        include/typedefs.h
        include/scenemgr.h source/scenemgr.cpp

        include/datatypes/ByteArray.h source/datatypes/ByteArray.cpp
        include/components/TextInput.h source/components/TextInput.cpp
        include/components/TextView.h source/components/TextView.cpp
        include/components/NodeEncoder.h source/components/NodeEncoder.cpp
        include/components/NodeDecoder.h source/components/NodeDecoder.cpp
        include/components/NodeCompare.h source/components/NodeCompare.cpp
        include/components/FileInput.h source/components/FileInput.cpp
        include/components/NodeAES.h source/components/NodeAES.cpp

        include/ciphers/AES.h source/ciphers/AES.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ezcipher
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(ezcipher
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(ezcipher PRIVATE Qt${QT_VERSION_MAJOR}::Widgets nodes -lcrypto)

set_target_properties(ezcipher PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# target_compile_definitions(ezcipher
#   PUBLIC
#     NODE_EDITOR_SHARED
#   PRIVATE
#     NODE_EDITOR_EXPORTS
#     #NODE_DEBUG_DRAWING
#     QT_NO_KEYWORDS
# )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ezcipher)
endif()
