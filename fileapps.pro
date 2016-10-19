SOURCES	+= \
		src/fileApps_base.cpp \
		src/file_config.cpp \
		src/file_data_out.cpp \
		src/file_log.cpp \
		src/file_log_errors.cpp \
		src/file_extract_xlsx.cpp \

HEADERS	+= \
		include/fileApps_base.h \
		include/file_config.h \
		include/file_data_out.h \
		include/file_log.h \
		include/file_log_errors.h \
		include/file_extract_xlsx.h \

FORMS	+= \

TEMPLATE	= lib
LANGUAGE	= C++

TARGET = fileapps_rv1
DESTDIR        = bin
OBJECTS_DIR    = obj
MOC_DIR        = moc
UI_HEADERS_DIR = uic/include
UI_SOURCES_DIR = uic/src
RCC_DIR        = rcc
CONFIG	+= qt_release dynamic warn_on debug plugin thread exceptions rtti stl
QT +=
DEPENDPATH += include
DEFINES +=
QMAKE_LIBPATH += /data0/qt/qt/lib
LIBS	+=
INCLUDEPATH += /usr/X11R6/include include /data0/ncpv/lib/include


target.path += /data0/ncpv/lib
INSTALLS += target

