#include "widget.h"
#include "ui_widget.h"
#include "delegate/item_delegate.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , folderName("")
    , _list({})
    , _progressDialog(nullptr)
    , _fileModel(new FileModel(this))
    , _converter(new Converter(this))
{
    ui->setupUi(this);

    this->setMaximumSize(509, 253);
    this->setMinimumSize(509, 253);

    this->setWindowTitle("NCM_2_MP3");

    // set up the view
    ui->listView->setModel(_fileModel);
    ui->listView->setItemDelegate(new ItemDelegate(this));

    // connect the signals and slots
    connect(_converter, &Converter::ConversionProgress, this, &Widget::UpdateConversionProgress);
    connect(_converter, &Converter::ConversionFinished, this, &Widget::OnConversionFinished);
}

Widget::~Widget()
{
    delete ui;
}

std::list<QString> Widget::getNcmFiles(const QString &foldername)
{
    // 存放ncm文件的绝对路径
    std::list<QString> retList;

    QDir dir(foldername);
    if (!dir.exists())
    {
        qWarning("Directory does not exist: %s", qPrintable(foldername));
        return retList;
    }

    QFileInfoList fileInfoList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);

    for (const QFileInfo &fileInfo : fileInfoList)
    {
        if (fileInfo.isFile()) // 如果是文件
        {
            QString extension = fileInfo.suffix(); // 获取文件扩展名
            if (extension == "ncm")
            { // 如果扩展名是 ".ncm"
                retList.push_back(fileInfo.absoluteFilePath());
            }
        }
        else if (fileInfo.isDir())
        { // 如果是目录
            retList.splice(retList.end(), getNcmFiles(fileInfo.absoluteFilePath()));
        }
    }

    return retList;
}

void Widget::on_openButton_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Open Folder"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!folderPath.isEmpty())
    {
        ui->mainLineEdit->setText(folderPath);
        _fileModel->SetFolder(folderPath);
    }
}

void Widget::on_startButton_clicked()
{
    if (_fileModel->rowCount() == 0)
    {
        qInfo() << "No files to convert";
        return;
    }

    qInfo() << "find ncm " << _fileModel->rowCount() << " files";

    _converter->StartConversion(_fileModel->GetFileList());
}

void Widget::on_cancelButton_clicked()
{
    if (!folderName.isEmpty())
    {
        return;
    }
}

void Widget::on_stoplButton_clicked()
{
    if (!folderName.isEmpty())
    {
        return;
    }
}

void Widget::UpdateConversionProgress(int progress, const QString &currentFile)
{
    // if (_progressDialog->wasCanceled())
    // {
    //     _converter->CancelConversion();
    //     return;
    // }

    // _progressDialog->setValue(progress);
    // _progressDialog->setLabelText(QString("Converting: %1").arg(currentFile));
    _fileModel->SetTotalProgress(progress, currentFile);
}

void Widget::OnConversionFinished()
{
    // _progressDialog->close();
    // delete _progressDialog;
    // _progressDialog = nullptr;

    _fileModel->RefreshModel();
}
