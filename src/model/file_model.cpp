#include "file_model.h"

#include <QDir>

FileModel::FileModel(QObject *parent) : QAbstractListModel(parent), _totalProgress(0)
{
}

int FileModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return _files.size();
}

QVariant FileModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole)
    {
        // return _files.at(index.row()).fileName();
    }
    else if (role == Qt::UserRole)
    {
        return _totalProgress;
    }
    else if (role == Qt::UserRole + 1)
    {
        return _currentFile;
    }
    return QVariant();
}

void FileModel::SetFolder(const QString &folderPath)
{
    beginResetModel();
    _files.clear();
    ScanFolder(folderPath);
    endResetModel();
}

QStringList FileModel::GetFileList() const
{
    QStringList fileList;
    for (const auto &file : _files)
    {
        fileList << file.absoluteFilePath();
    }
    return fileList;
}

void FileModel::RefreshModel()
{
    beginResetModel();
    endResetModel();
}

// 递归扫描文件夹
void FileModel::ScanFolder(const QString &folderPath)
{
    QDir          dir(folderPath);
    QFileInfoList fileInfoList = dir.entryInfoList(QStringList() << "*.ncm", QDir::Files | QDir::Readable, QDir::Name);

    for (const QFileInfo &fileInfo : fileInfoList)
    {
        _files.append(fileInfo);
    }

    QFileInfoList dirList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QFileInfo &dirInfo : dirList)
    {
        ScanFolder(dirInfo.absoluteFilePath());
    }
}

void FileModel::SetTotalProgress(int progress, const QString &currentFile)
{
    _totalProgress = progress;
    _currentFile   = currentFile;
    emit dataChanged(index(0), index(rowCount() - 1), {Qt::UserRole, Qt::UserRole + 1});
}