/* =================================================
 * This file is part of the TTK qmmp plugin project
 * Copyright (C) 2015 - 2021 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#ifndef FC14HELPER_H
#define FC14HELPER_H

extern "C" {
#include <libfc14/fc14audiodecoder.h>
}
#include <QMap>
#include <QFile>
#include <qmmp/qmmp.h>

typedef struct {
    void *input;
    int bitrate;
} decode_info;

/*!
 * @author Greedysky <greedysky@163.com>
 */
class FC14Helper
{
public:
    explicit FC14Helper(const QString &path);
    ~FC14Helper();

    void deinit();

    bool initialize();
    int totalTime() const;
    void seek(qint64 time);

    int bitrate() const;
    int sampleRate() const;
    int channels() const;
    int bitsPerSample() const;

    int read(unsigned char *buf, int size);
    QMap<Qmmp::MetaData, QString> readMetaData() const;

private:
    QString m_path;
    decode_info *m_info;

};

#endif
