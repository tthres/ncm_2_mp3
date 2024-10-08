#include "item_delegate.h"

#include <QPainter>
#include <QFileInfo>

ItemDelegate::ItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    int     currentFileIndex = index.data(Qt::UserRole).toInt();
    QString currentFile      = index.data(Qt::UserRole + 1).toString();
    int     totalFiles       = index.model()->rowCount();

    QRect progressRect = option.rect.adjusted(4, 4, -4, -4);
    int   maxWidth     = 200; // 设置最大宽度为200像素
    if (progressRect.width() > maxWidth)
    {
        int diff = progressRect.width() - maxWidth;
        progressRect.adjust(diff / 2, 0, -diff / 2, 0);
    }
    progressRect.setHeight(progressRect.height() / 2);

    // 绘制进度条
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::lightGray);
    painter->drawRect(progressRect);

    if (totalFiles > 0)
    {
        int progress = (currentFileIndex * 100) / totalFiles;
        painter->setBrush(Qt::blue);
        painter->drawRect(progressRect.adjusted(0, 0, -progressRect.width() * (100 - progress) / 100, 0));

        // 绘制进度文本
        painter->setPen(Qt::black);
        painter->drawText(progressRect, Qt::AlignCenter, QString("%1% (%2/%3)").arg(progress).arg(currentFileIndex).arg(totalFiles));
    }

    painter->restore();
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    return QSize(size.width(), 50); // 增加高度以容纳进度条和文件名
}