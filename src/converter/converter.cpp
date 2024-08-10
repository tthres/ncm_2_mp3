#include "converter.h"

#include <QFileInfo>
#include <QDebug>
#include <QtConcurrent>
#include "model.h"

Converter::Converter(QObject *parent) : QObject(parent), _isCancelled(false)
{
}

Converter::~Converter()
{
}

void Converter::StartConversion(const QStringList &fileList)
{
    _fileList = fileList;
    _isCancelled.store(false);

    QFuture<void> future = QtConcurrent::run([this]() { ConvertFiles(); });
}

void Converter::CancelConversion()
{
    _isCancelled.store(true);
}

void Converter::ConvertFiles()
{
    int totalFiles = _fileList.size();
    for (int i = 0; i < totalFiles; i++)
    {
        if (_isCancelled.load())
        {
            break;
        }
        QString filePath = _fileList.at(i);
        emit ConversionProgress(i + 1, QFileInfo(filePath).fileName());

        int result = ConvertFile(filePath);
        if (result != 0)
        {
            qWarning() << "Conversion failed for file:" << filePath;
        }
    }
    emit ConversionFinished();
}

int Converter::ConvertFile(const QString &filePath)
{
    if (filePath.isEmpty())
    {
        return -1;
    }
    QByteArray  byteArray = filePath.toLocal8Bit();
    const char *cstr      = byteArray.constData();
    qInfo().noquote() << "transform" << filePath.toUtf8().constData() << "....";
    return readFileData(cstr);
}