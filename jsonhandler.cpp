#include "jsonhandler.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

JsonHandler::JsonHandler(QObject *parent)
    : QObject{parent}
{
}

void JsonHandler::writeColorToJson(QString r, QString g, QString b)
{
//    qDebug() << "red: " << r;
//    qDebug() << "green: " << g;
//    qDebug() << "blue: " << b;

    QFile file("color_data.json");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

    QJsonDocument JsonDocument;

    QJsonObject color;
    color["red"] = r;
    color["green"] = g;
    color["blue"] = b;

    JsonDocument.setObject(color);

    file.write(JsonDocument.toJson(QJsonDocument::Indented));
    file.close();
}

void JsonHandler::readColorFromJson()
{
    QString str_r, str_g, str_b;

    QString val;
    QFile file("color_data.json");

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = doc.object();

    if (obj.contains("red"))
            str_r = obj["red"].toString();

    if (obj.contains("green"))
            str_g = obj["green"].toString();

    if (obj.contains("blue"))
            str_b = obj["blue"].toString();

    json_r =  str_r.toInt();
    json_g = str_g.toInt();
    json_b =  str_b.toInt();

}
