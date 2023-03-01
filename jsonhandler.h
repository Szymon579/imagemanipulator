#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QObject>

class JsonHandler : public QObject
{
    Q_OBJECT


public:
    explicit JsonHandler(QObject *parent = nullptr);

    inline int getJsonR(){ return json_r ;};
    inline int getJsonG(){ return json_g;};
    inline int getJsonB(){ return json_b;};

public slots:
    void writeColorToJson(QString r, QString g, QString b);
    void readColorFromJson();

signals:


private:
    int json_r;
    int json_g;
    int json_b;
};

#endif // JSONHANDLER_H
