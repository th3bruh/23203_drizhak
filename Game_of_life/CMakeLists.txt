cmake_minimum_required(VERSION 3.19)
project(Game_of_life LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

qt_add_executable(Game_of_life
    WIN32 MACOSX_BUNDLE
    main.cpp



    field.h field.cpp
    window.h window.cpp window.ui
    engine.h engine.cpp



)

target_link_libraries(Game_of_life
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Game_of_life
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Game_of_life
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
