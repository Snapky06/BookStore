cmake_minimum_required(VERSION 3.19)
project(BookStoreSN LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(BookStoreSN
    main.cpp
    book.h book.cpp
    bookstore.h bookstore.cpp
)

target_link_libraries(BookStoreSN
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS BookStoreSN
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
