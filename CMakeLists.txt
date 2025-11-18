cmake_minimum_required(VERSION 3.16)

project(untitled1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#在下方添加网络模块
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if (WIN32)
    # 确保 appicon.rc 与 myicon.ico 放在 ${CMAKE_CURRENT_SOURCE_DIR} 或写相对路径
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(untitled1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${APP_ICON_RESOURCE_WINDOWS}
        logindialog.h logindialog.cpp logindialog.ui
        rc.qrc
        registerdialog.h registerdialog.cpp registerdialog.ui
        style/stylesheet.qss
        global.h
        global.cpp
        singleton.h
        httpmgr.h httpmgr.cpp
        config.ini
        timerbtn.h timerbtn.cpp
        clickedlabel.h clickedlabel.cpp
        resetdialog.h resetdialog.cpp resetdialog.ui
        tcpmgr.h tcpmgr.cpp
        usermgr.h usermgr.cpp
        chatdialog.h chatdialog.cpp chatdialog.ui
        clickedbtn.h clickedbtn.cpp
        customizeedit.h customizeedit.cpp
        chatuserlist.h chatuserlist.cpp
        chatuserwid.h chatuserwid.cpp chatuserwid.ui
        listitembase.h listitembase.cpp
        loadingdlg.h loadingdlg.cpp loadingdlg.ui
        chatpage.h chatpage.cpp chatpage.ui
        chatview.h chatview.cpp
        chatitembase.h chatitembase.cpp
        bubbleframe.h bubbleframe.cpp
        textbubble.h textbubble.cpp
        picturebubble.h picturebubble.cpp
        messagetextedit.h messagetextedit.cpp
        statewidget.h statewidget.cpp
        searchlist.h searchlist.cpp
        userdata.h userdata.cpp
        adduseritem.h adduseritem.cpp adduseritem.ui
        findsuccessdlg.h findsuccessdlg.cpp findsuccessdlg.ui
        applyfriendpage.h applyfriendpage.cpp applyfriendpage.ui
        applyfrienditem.h applyfrienditem.cpp applyfrienditem.ui
        applyfriendlist.h applyfriendlist.cpp
        contactuserlist.h contactuserlist.cpp
        conuseritem.h conuseritem.cpp conuseritem.ui
        grouptipitem.h grouptipitem.cpp grouptipitem.ui
        findfaildlg.h findfaildlg.cpp findfaildlg.ui
        applyfriend.h applyfriend.cpp applyfriend.ui
        clickedoncelabel.h clickedoncelabel.cpp
        friendlabel.h friendlabel.cpp friendlabel.ui
        authenfriend.h authenfriend.cpp authenfriend.ui



    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET untitled1 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(untitled1 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(untitled1
            ${PROJECT_SOURCES}
            ${APP_ICON_RESOURCE_WINDOWS}
        )
    endif()
endif()

target_include_directories(untitled1
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}            # 项目根（能找到 mainwindow.h 等）
        ${CMAKE_CURRENT_BINARY_DIR}            # ✅ 构建目录（生成的 ui_xxx.h 在这里）
)

#添加网络的连接器
target_link_libraries(untitled1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.untitled1)
endif()

# ---- 构建后拷贝资源 START ----
# 可执行文件输出目录
set(_RUNTIME_DIR $<TARGET_FILE_DIR:untitled1>)

# 源文件/目录
set(_CONFIG_INI "${CMAKE_CURRENT_SOURCE_DIR}/config.ini")
set(_STATIC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/static")

# 拷贝 config.ini（如果存在）
if(EXISTS "${_CONFIG_INI}")
    add_custom_command(TARGET untitled1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${_CONFIG_INI}" "${_RUNTIME_DIR}"
        COMMENT "Copying config.ini to runtime dir"
        VERBATIM
    )
endif()

# 拷贝 static 目录（如果存在）
if(EXISTS "${_STATIC_DIR}")
    add_custom_command(TARGET untitled1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
                "${_RUNTIME_DIR}/static"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${_STATIC_DIR}" "${_RUNTIME_DIR}/static"
        COMMENT "Copying static/ to runtime dir"
        VERBATIM
    )
endif()
# ---- 构建后拷贝资源 END ----


set_target_properties(untitled1 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS untitled1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(untitled1)
endif()

# MSVC: 关闭 4819 告警并使用 UTF-8 源码/执行字符集
target_compile_options(untitled1 PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/wd4819 /utf-8>
)
