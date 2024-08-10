#pragma once

#include <QObject>
#include <QThread>
#include <QStringList>
#include <atomic>

class Converter : public QObject
{
    Q_OBJECT
public:
    explicit Converter(QObject *parent = nullptr);
    ~Converter();

    void StartConversion(const QStringList &fileList);
    void CancelConversion();

public slots:
    void ConvertFiles();

signals:
    void ConversionProgress(int progress, const QString &currentFile);
    void ConversionFinished();

private:
    QStringList      _fileList;
    std::atomic_bool _isCancelled;

    int ConvertFile(const QString &filePath);
};