#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <QImage>
#include <qqml.h>

class ImageProcessor : public QObject
{
    Q_OBJECT


    //              obj  val, slot(get), slot(set), signal(observer)
    Q_PROPERTY(QString imgUrl READ getUrl WRITE setUrl NOTIFY urlChanged)


    QML_ELEMENT

public:
    explicit ImageProcessor(QObject *parent = nullptr);

    inline QString imgUrl() { return m_url; };
    void QmlPreview();
    void setColorsDelta();


public slots: //to be called by QML
    //ui
    void loadImage();

    void rotateImage();
    void bwImage();
    void hMirrorImage();
    void vMirrorImage();
    void colorTransformImage();

    void saveImage(QString save_url);

    //util
    void setUrl(QString url);
    QString getUrl();


signals: //to be recived by QML
    void urlChanged();


private:
    QString m_url;
    QString fixed_url;
    QString preview;

    QImage image;

    int red_delta;
    int green_delta;
    int blue_delta;

    int prev_red_delta;
    int prev_green_delta;
    int prev_blue_delta;

};

#endif // IMAGEPROCESSOR_H
