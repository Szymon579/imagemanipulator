#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QObject>
#include <QJsonObject>

class JsonHandler : public QObject
{
    Q_OBJECT


public:
    explicit JsonHandler(QObject *parent = nullptr);

    inline QJsonObject getJsonObject(){ return m_json_obj; };

    int getJsonR(){ return m_red; };
    int getJsonG(){ return m_green; };
    int getJsonB(){ return m_blue; };


public slots:
    QJsonObject makeJsonObject(QJsonObject json_obj);
    void readColorFromJsonObject(QJsonObject json_obj);

signals:


public:
    QJsonObject m_json_obj;

    static int m_red;
    static int m_green;
    static int m_blue;
};

#endif // JSONHANDLER_H
