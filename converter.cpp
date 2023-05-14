#include "converter.h"
#include "qdebug.h"

Converter::Converter()
    : meta_key({ 0x23,0x31,0x34,0x6C,0x6A,0x6B,0x5F,0x21,0x5C,0x5D,0x26,0x30,0x55,0x3C,0x27,0x28 }),
      core_key({ 0x68,0x7A,0x48,0x52,0x41,0x6D,0x73,0x6F,0x35,0x6B,0x49,0x6E,0x62,0x61,0x78,0x57 })
{

}

void Converter::ncmDecode_t(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qInfo() << "No such file:" << filename;
        return;
    }

    QDataStream stream(&file);
    stream.skipRawData(10);     // 从当前位置移动10个字节

    unsigned char buf[16];
    int len=0;
}

void Converter::ncmDecode(std::list<QString> &filelist)
{
    for (std::list<QString>::iterator it = filelist.begin(); it != filelist.end(); it++)
    {
        ncmDecode_t(*it);
    }
}
