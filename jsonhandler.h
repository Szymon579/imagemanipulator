#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QObject>
#include <QJsonObject>

class JsonHandler : public QObject
{
    Q_OBJECT


public:
    explicit JsonHandler(QObject *parent = nullptr);

    static inline int getJsonR(){ return m_red; };
    static inline int getJsonG(){ return m_green; };
    static inline int getJsonB(){ return m_blue; };


public slots:
    void readColorFromJsonObject(QJsonObject json_obj);

signals:

private:
    static int m_red;
    static int m_green;
    static int m_blue;
};

#endif // JSONHANDLER_H
