#include "datatypes/ByteArray.h"

#include "precompile.h"

void ByteArray::reset(const QByteArray& newData)
{
    _data = newData;
}

void ByteArray::fromString(const QString& str)
{
    _data = str.toUtf8();
}

void ByteArray::fromHex(QString str, char sep)
{
    QByteArray bytes = str.remove(sep).toUtf8();
    _data = QByteArray::fromHex(bytes);
}

void ByteArray::fromBase64(const QString& str)
{
    _data = QByteArray::fromBase64(str.toUtf8());
}

void ByteArray::fromFile(const QString& filePath)
{
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)) {
        _data = file.readAll();        
    }
}

QString ByteArray::toHex(char sep) const
{
    return _data.toHex(sep);
}

QString ByteArray::toBase64() const
{
    return _data.toBase64();
}

QString ByteArray::toString() const
{
    if(_data.isValidUtf8()) {
        return QString::fromUtf8(_data);
    }
    
    return QString("invalid UTF-8");
}

QtNodes::NodeDataType ByteArray::type() const
{
    return QtNodes::NodeDataType{"bytearray", "bytes"};
}