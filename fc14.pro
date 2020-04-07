
include($$PWD/common/common.pri)

HEADERS += decoderfc14factory.h \
           decoder_fc14.h \
           fc14helper.h \
           Dump.h \
           FC.h \
           fc14audiodecoder.h \
           LamePaula.h \
           MyEndian.h \
           MyTypes.h \
           Paula.h \
           SmartPtr.h

SOURCES += decoderfc14factory.cpp \
           decoder_fc14.cpp \
           fc14helper.cpp \
           Dump.cpp \
           FC.cpp \
           FC_Data.cpp \
           fc14audiodecoder.cpp \
           LamePaulaMixer.cpp \
           LamePaulaVoice.cpp \
           Paula.cpp

CONFIG += warn_on plugin link_pkgconfig c++11

TEMPLATE = lib

QMAKE_CLEAN += lib$${TARGET}.so

unix {
  CONFIG += link_pkgconfig
  PKGCONFIG += qmmp

  QMMP_PREFIX = $$system(pkg-config qmmp --variable=prefix)
  PLUGIN_DIR = $$system(pkg-config qmmp --variable=plugindir)/Input
  LOCAL_INCLUDES = $${QMMP_PREFIX}/include
  LOCAL_INCLUDES -= $$QMAKE_DEFAULT_INCDIRS
  INCLUDEPATH += $$LOCAL_INCLUDES

  plugin.path = $${PLUGIN_DIR}
  plugin.files = lib$${TARGET}.so
  INSTALLS += plugin
}
