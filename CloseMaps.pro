symbian:{
TARGET.UID3 = 0xE690E897
LIBS += -lavkon \
        -apgrfx.lib
TARGET.CAPABILITY += PowerMgmt
vendorinfo = "%{\"huellifSoft\"}" ":\"huellifSoft\""
my_deployment.pkg_prerules = vendorinfo
DEPLOYMENT += my_deployment
DEPLOYMENT.display_name += CloseMaps
VERSION = 1.1.0
ICON = Icon.svg
}

SOURCES += main.cpp


include(deployment.pri)
qtcAddDeployment()
