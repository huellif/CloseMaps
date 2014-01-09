symbian:{
TARGET.UID3 = 0xE690E897
LIBS += -laknnotify
TARGET.CAPABILITY += PowerMgmt
vendorinfo = "%{\"huellifSoft\"}" ":\"huellifSoft\""
my_deployment.pkg_prerules = vendorinfo
DEPLOYMENT += my_deployment
DEPLOYMENT.display_name += CloseMaps
VERSION = 1.3.0
ICON = Icon.svg
default_deployment.pkg_prerules -= pkg_depends_webkit
default_deployment.pkg_prerules -= pkg_depends_qt
}

SOURCES += main.cpp


include(deployment.pri)
qtcAddDeployment()

CONFIG -= qt

INCLUDEPATH += C:\QtSDK\Symbian\SDKs\Symbian3Qt474\epoc32\include\mw\
INCLUDEPATH += C:\QtSDK\Symbian\SDKs\Symbian3Qt474\epoc32\include\platform\
INCLUDEPATH += C:\QtSDK\Symbian\SDKs\Symbian3Qt474\epoc32\include\platform\mw\
