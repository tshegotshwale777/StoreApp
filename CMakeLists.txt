cmake_minimum_required(VERSION 3.16)

project(storeApp_24355224 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(storeApp_24355224
  main.cpp
  mainwindow.h mainwindow.cpp
  customer.h customer.cpp
  item.h item.cpp
  transaction.h transaction.cpp
  itemtransaction.h itemtransaction.cpp
  transinterface.h transinterface.cpp
)

target_link_libraries(storeApp_24355224 PRIVATE Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS storeApp_24355224
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
