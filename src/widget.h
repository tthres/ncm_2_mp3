#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <list>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QProgressDialog>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_openButton_clicked();

    void on_startButton_clicked();

    void on_cancelButton_clicked();

    void on_stoplButton_clicked();

private:
    std::list<QString> getNcmFiles(const QString &foldername);

    Ui::Widget        *ui;
    QString            folderName;
    std::list<QString> _list;
    QProgressDialog   *_progressDialog;
};
#endif // WIDGET_H
