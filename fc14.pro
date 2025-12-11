
QMAKE_CFLAGS += -std=gnu11
greaterThan(QT_MAJOR_VERSION, 5){
    QMAKE_CXXFLAGS += -std=c++17
}else{
    QMAKE_CXXFLAGS += -std=c++11
}

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

DEFINES += LIBFC_VERSION_OLD

#CONFIG += BUILD_PLUGIN_INSIDE
contains(CONFIG, BUILD_PLUGIN_INSIDE){
    include($$PWD/../../plugins.pri)
    TARGET = $$PLUGINS_PREFIX/Input/fc14

    unix{
        target.path = $$PLUGIN_DIR/Input
        INSTALLS += target
    }
}else{
    QT += widgets
    CONFIG += warn_off plugin lib thread link_pkgconfig c++11
    TEMPLATE = lib

    unix{
        equals(QT_MAJOR_VERSION, 4){
            QMMP_PKG = qmmp-0
        }else:equals(QT_MAJOR_VERSION, 5){
            QMMP_PKG = qmmp-1
        }else:equals(QT_MAJOR_VERSION, 6){
            QMMP_PKG = qmmp
        }else{
            error("No Qt version found")
        }
        
        PKGCONFIG += $${QMMP_PKG}

        PLUGIN_DIR = $$system(pkg-config $${QMMP_PKG} --variable=plugindir)/Input
        INCLUDEPATH += $$system(pkg-config $${QMMP_PKG} --variable=prefix)/include

        plugin.path = $${PLUGIN_DIR}
        plugin.files = lib$${TARGET}.so
        INSTALLS += plugin
    }
}
