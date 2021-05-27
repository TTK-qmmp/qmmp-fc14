include(../../plugins.pri)

TARGET = $$PLUGINS_PREFIX/Input/fc14

HEADERS += decoderfc14factory.h \
           decoder_fc14.h \
           fc14helper.h

SOURCES += decoderfc14factory.cpp \
           decoder_fc14.cpp \
           fc14helper.cpp \
           libfc14/Dump.cpp \
           libfc14/FC.cpp \
           libfc14/FC_Data.cpp \
           libfc14/fc14audiodecoder.cpp \
           libfc14/LamePaulaMixer.cpp \
           libfc14/LamePaulaVoice.cpp \
           libfc14/Paula.cpp

INCLUDEPATH += $$PWD/libfc14

unix {
    target.path = $$PLUGIN_DIR/Input
    INSTALLS += target
    QMAKE_CLEAN = $$PLUGINS_PREFIX/Input/libfc14.so
}
