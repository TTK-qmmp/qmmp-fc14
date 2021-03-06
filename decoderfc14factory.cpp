#include "decoderfc14factory.h"
#include "decoder_fc14.h"
#include "fc14helper.h"

#include <QMessageBox>

bool DecoderFC14Factory::canDecode(QIODevice *) const
{
    return false;
}

DecoderProperties DecoderFC14Factory::properties() const
{
    DecoderProperties properties;
    properties.name = "FC14 Plugin";
    properties.filters << "*.fc" << "*.fc13" << "*.fc14" << "*.smod";
    properties.description = "Future Composer Audio File";
    properties.shortName = "fc14";
    properties.protocols << "file";
    properties.noInput = true;
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
        const QMap<Qmmp::MetaData, QString> metaData(helper.readMetaData());
        for(auto itr = metaData.begin(); itr != metaData.end(); ++itr)
        {
            info->setValue(itr.key(), itr.value());
        }
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.sampleRate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setValue(Qmmp::BITS_PER_SAMPLE, helper.bitsPerSample());
        info->setValue(Qmmp::FORMAT_NAME, "FC14");
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

void DecoderFC14Factory::showSettings(QWidget *parent)
{
    Q_UNUSED(parent);
}

void DecoderFC14Factory::showAbout(QWidget *parent)
{
    QMessageBox::about (parent, tr("About FC14 Reader Plugin"),
                        tr("Qmmp FC14 Reader Plugin")+"\n"+
                        tr("Written by: Greedysky <greedysky@163.com>"));
}

QString DecoderFC14Factory::translation() const
{
    return QString();
}
