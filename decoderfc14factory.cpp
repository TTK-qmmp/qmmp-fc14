#include "decoderfc14factory.h"
#include "decoder_fc14.h"
#include "fc14helper.h"

#include <QMessageBox>

bool DecoderFC14Factory::canDecode(QIODevice *input) const
{
    // At least 0xb80 is needed for some modules that start with machine code player.
    constexpr int peekSize = 0xb80;
    char buf[peekSize];
    if(input->peek(buf, peekSize) != peekSize)
    {
        return false;
    }

    void *ctx = fc14dec_new();
    const int v = fc14dec_detect(ctx, buf, peekSize);
    fc14dec_delete(ctx);
    return v;
}

DecoderProperties DecoderFC14Factory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("FC14 Plugin");
    properties.shortName = "fc14";
    properties.filters << "*.fc" << "*.fc3" << "*.fc4" << "*.fc13" << "*.fc14" << "*.smod";
    properties.description = "Future Composer Audio File";
    properties.protocols << "file";
    properties.noInput = true;
    properties.hasAbout = true;
    return properties;
}

Decoder *DecoderFC14Factory::create(const QString &path, QIODevice *input)
{
    Q_UNUSED(input);
    return new DecoderFC14(path);
}

QList<TrackInfo*> DecoderFC14Factory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *)
{
    TrackInfo *info = new TrackInfo(path);
    if(parts == TrackInfo::Parts())
    {
        return QList<TrackInfo*>() << info;
    }

    FC14Helper helper(path);
    if(!helper.initialize())
    {
        delete info;
        return QList<TrackInfo*>();
    }

    if(parts & TrackInfo::MetaData)
    {
        info->setValue(Qmmp::COMMENT, helper.comment());
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.sampleRate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setValue(Qmmp::BITS_PER_SAMPLE, helper.depth());
        info->setValue(Qmmp::FORMAT_NAME, "Future Composer");
        info->setDuration(helper.totalTime());
    }
    return QList<TrackInfo*>() << info;
}

MetaDataModel* DecoderFC14Factory::createMetaDataModel(const QString &path, bool readOnly)
{
    Q_UNUSED(path);
    Q_UNUSED(readOnly);
    return nullptr;
}

#if (QMMP_VERSION_INT < 0x10700) || (0x20000 <= QMMP_VERSION_INT && QMMP_VERSION_INT < 0x20200)
void DecoderFC14Factory::showSettings(QWidget *parent)
{
    Q_UNUSED(parent);
}
#else
QDialog *DecoderFC14Factory::createSettings(QWidget *parent)
{
    Q_UNUSED(parent);
    return nullptr;
}
#endif

void DecoderFC14Factory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About FC14 Reader Plugin"),
                       tr("Qmmp FC14 Reader Plugin") + "\n" +
                       tr("Written by: Greedysky <greedysky@163.com>") + "\n" +
                       tr("Based on the source code from the libfc14audiodecoder") + "\n" +
                       tr("Written by Michael Schwendt (C) 2024"));
}

QString DecoderFC14Factory::translation() const
{
    return QString();
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
#include <QtPlugin>
Q_EXPORT_PLUGIN2(fc14, DecoderFC14Factory)
#endif
