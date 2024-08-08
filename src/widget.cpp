#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget), folderName(""), _list({}), _progressDialog(nullptr)
{
    ui->setupUi(this);

    this->setMaximumSize(509, 253);
    this->setMinimumSize(509, 253);

    this->setWindowTitle("NCM_2_MP3");
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
        folderName = folderPath;
        qInfo() << "打开文件 ： " << folderName;
    }
}

void Widget::on_startButton_clicked()
{
    if (folderName.isEmpty())
    {
        qInfo() << "文件打开失败";
        return;
    }
    // 解析文件
    qInfo() << "开始解析文件" << folderName;
    _list = getNcmFiles(folderName);

    int count = 0;
    for (auto it = _list.begin(); it != _list.end(); it++)
    {
        count++;
    }
    qInfo() << "共找到NCM文件[" << count << "]个";

    if (_progressDialog)
    {
        delete _progressDialog;
    }
    _progressDialog = new QProgressDialog("Converting files...", "Cancel", 0, count, this);
    _progressDialog->setWindowModality(Qt::WindowModal);
    _progressDialog->setMinimumDuration(0); // 立即显示，不使用延迟
    _progressDialog->setValue(0);

    int currentFile = 0;

    // 开始转换
    for (auto it = _list.begin(); it != _list.end(); it++)
    {
        if (_progressDialog->wasCanceled())
        {
            break;
        }

        QString qstr = *it;
        qInfo() << "transform" << *it << "....";
        QByteArray  byteArray = it->toLocal8Bit();
        const char *cstr      = byteArray.constData();
        qInfo().noquote() << "transform" << it->toUtf8().constData() << "....";

        std::string str(cstr);

        int ret = readFileData(cstr);
        if (ret != 0)
        {
            qInfo() << "error?? ret = " << ret;
        }
        else
        {
            qInfo() << "transform" << cstr << "succeed !!";
        }

        currentFile++;
        _progressDialog->setValue(currentFile);
        _progressDialog->setLabelText(QString("Converting: %1").arg(QFileInfo(*it).fileName()));
        QApplication::processEvents(); // 允许 GUI 更新
    }

    _progressDialog->hide();
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
