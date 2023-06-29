#ifndef CONVERTER_H
#define CONVERTER_H

#include <QString>
#include <list>
#include <QFile>
#include <QByteArray>
#include <QDataStream>

class Converter
{
public:
    Converter();

    void ncmDecode(std::list<QString> &filelist);

private:

    void ncmDecode_t(const QString &filename);

    unsigned char* base64_decode(unsigned char* code, int len, int* actLen);

    const std::array<unsigned char, 16> meta_key;
    const std::array<unsigned char, 16> core_key;
};

#endif // CONVERTER_H
