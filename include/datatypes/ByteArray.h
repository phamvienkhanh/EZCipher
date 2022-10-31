#ifndef _INC_BYTE_ARRAY_H_
#define _INC_BYTE_ARRAY_H_

#include "precompile.h"

class ByteArray: public QtNodes::NodeData
{

public:
    ByteArray(){}
    ~ByteArray(){}

    QtNodes::NodeDataType type() const override;

    void reset(const QByteArray& newData);

    void fromString(const QString& str);
    void fromHex(QString str, char sep = '\0');
    void fromBase64(const QString& str);

    void fromFile(const QString& filePath);

    QString toHex(char sep = '\0') const;
    QString toBase64() const;
    QString toString() const;

    QByteArray data() {return _data;}

private:
    QByteArray _data;
};

#endif