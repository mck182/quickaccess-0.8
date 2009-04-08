# Project Needs a name ofcourse
project(quickaccess)

# Find the required Libaries
find_package(KDE4 REQUIRED)
include(KDE4Defaults)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )

# We add our source code here
set(quickaccess_SRCS quickaccess.cpp popupdialog.cpp itemview.cpp pluginwidget.cpp effects.cpp button.cpp
		     dirmodel.cpp label.cpp iconmanager.cpp resizedialog.cpp settings.cpp pluginmodel.cpp)

# Now make sure all files get to the right place
kde4_add_ui_files(quickaccess_SRCS quickaccessConfig.ui pluginwidgetbase.ui)
kde4_add_plugin(plasma_applet_quickaccess ${quickaccess_SRCS})
target_link_libraries(plasma_applet_quickaccess
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} kfile konq)

install(TARGETS plasma_applet_quickaccess
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES plasma-applet-quickaccess.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})