#include "jsonhandler.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

int JsonHandler::m_red = 0;
int JsonHandler::m_green = 0;
int JsonHandler::m_blue = 0;

JsonHandler::JsonHandler(QObject *parent)
    : QObject{parent}
{
}

void JsonHandler::readColorFromJsonObject(QJsonObject json_obj)
{
    int r = 0, g = 0, b = 0;
    QJsonValue r_val, g_val, b_val;

    if (json_obj.contains("red"))
    {
        //qDebug() << "contains red";
        r_val = json_obj.find("red").value();
        r = r_val.toVariant().toInt();
    }
    if (json_obj.contains("green"))
    {
        //qDebug() << "contains green";
        g_val = json_obj.find("green").value();
        g = g_val.toVariant().toInt();
    }
    if (json_obj.contains("blue"))
    {
        //qDebug() << "contains blue";
        b_val = json_obj.find("blue").value();
        b = b_val.toVariant().toInt();
    }

    m_red = r;
    m_green = g;
    m_blue = b;

    //qDebug() << "QJsonValRef:" << r_val;
    //qDebug() << "QJsonValRef:" << g_val;
    //qDebug() << "QJsonValRef:" << b_val;

    qDebug() << "QJsonValRef int r:" << r;
    qDebug() << "QJsonValRef int g:" << g;
    qDebug() << "QJsonValRef int b:" << b;

}

