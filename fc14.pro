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

#CONFIG += BUILD_PLUGIN_INSIDE
contains(CONFIG, BUILD_PLUGIN_INSIDE){
    include($$PWD/../../plugins.pri)
    TARGET = $$PLUGINS_PREFIX/Input/fc14

    unix{
        target.path = $$PLUGIN_DIR/Input
        INSTALLS += target
    }
}else{
    CONFIG += warn_off plugin lib thread link_pkgconfig c++11
    TEMPLATE = lib

    unix{
        PKGCONFIG += qmmp-1

        PLUGIN_DIR = $$system(pkg-config qmmp-1 --variable=plugindir)/Input
        INCLUDEPATH += $$system(pkg-config qmmp-1 --variable=prefix)/include

        plugin.path = $${PLUGIN_DIR}
        plugin.files = lib$${TARGET}.so
        INSTALLS += plugin
    }
}
