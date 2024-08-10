#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QFileInfo>

class FileModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit FileModel(QObject *parent = nullptr);

    int      rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void        SetFolder(const QString &folderPath);
    QStringList GetFileList() const;
    void        RefreshModel();

    void SetTotalProgress(int progress, const QString &currentFile);
private:
    QList<QFileInfo> _files;
    int              _totalProgress;
    QString          _currentFile;

private:
    void ScanFolder(const QString &folderPath);
};