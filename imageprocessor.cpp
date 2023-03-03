#include "imageprocessor.h"
#include "jsonhandler.h"

#include <QDebug>
#include <QTransform>
#include <QFile>
#include <QBuffer>

ImageProcessor::ImageProcessor(QObject *parent)
    : QObject{parent}
{
    m_url = "";
    fixed_url = "";
    preview = "";

    red_delta = 0;
    green_delta = 0;
    blue_delta = 0;
}

void ImageProcessor::QmlPreview()
{
      QByteArray byteArray;
      QBuffer buffer(&byteArray);
      buffer.open(QIODevice::WriteOnly);
      image.save(&buffer, "PNG");

      QString image("data:image/png;base64,");
      image.append(QString::fromLatin1(byteArray.toBase64().data()));
      m_url = image;

      emit urlChanged();
}

void ImageProcessor::setColorsDelta()
{
    red_delta = JsonHandler::getJsonR() - 128;
    green_delta = JsonHandler::getJsonG() - 128;
    blue_delta = JsonHandler::getJsonB() - 128;

    qDebug() << "red delta: " <<red_delta;
    qDebug() << "green delta: " << green_delta;
    qDebug() << "blue delta: " << blue_delta;

}

void ImageProcessor::loadImage()
{
    //qDebug() << "loadImage called for url" << m_url;

    fixed_url = m_url.remove(0,8); //get rid of "file:///" prefix
    image = QImage(fixed_url);
}

void ImageProcessor::rotateImage()
{
    //qDebug() << "rotateImage called";

    QTransform tf;
    tf.rotate(90);
    image = image.transformed(tf);

    QmlPreview();
}

void ImageProcessor::bwImage()
{
    //qDebug() << "bwImage called";

    QRgb pixel_color;
    int width = image.width();
    int height = image.height();
    int gray;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            pixel_color = image.pixel(j, i);
            gray = qGray(pixel_color);
            image.setPixel(j, i, qRgb(gray, gray, gray));
        }
    }

    QmlPreview();
}

void ImageProcessor::hMirrorImage()
{
    //qDebug() << "hMirrorImage called";

    image = image.mirrored(true, false);

    QmlPreview();
}

void ImageProcessor::vMirrorImage()
{
    //qDebug() << "vMirrorImage called";

    image = image.mirrored(false, true);

    QmlPreview();
}

void ImageProcessor::colorTransformImage()
{
    //qDebug() << "colorTransformImage called";

    QColor pixel_col;
    int width = image.width();
    int height = image.height();

    setColorsDelta();

    int new_color_val;

    if(red_delta != prev_red_val) //red_delta != 0
    {
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                pixel_col = image.pixelColor(j, i);
                new_color_val = pixel_col.red() + red_delta;

                if(new_color_val > 255)
                    new_color_val = 255;
                if(new_color_val < 0)
                    new_color_val = 0;

                pixel_col.setRed(new_color_val);
                image.setPixelColor(j, i, pixel_col);
            }
        }
    }

    if(green_delta != prev_green_val) //green_delta != 0
    {
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                pixel_col = image.pixelColor(j, i);
                new_color_val = pixel_col.green() + green_delta;

                if(new_color_val > 255)
                    new_color_val = 255;
                if(new_color_val < 0)
                    new_color_val = 0;

                pixel_col.setGreen(new_color_val);
                image.setPixelColor(j, i, pixel_col);
            }
        }
    }

    if(blue_delta != prev_blue_val) //blue_delta != 0
    {
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                pixel_col = image.pixelColor(j, i);
                new_color_val = pixel_col.blue() + blue_delta;

                if(new_color_val > 255)
                    new_color_val = 255;
                if(new_color_val < 0)
                    new_color_val = 0;

                pixel_col.setBlue(new_color_val);
                image.setPixelColor(j, i, pixel_col);
            }
        }
    }

    prev_red_val = red_delta;
    prev_green_val = green_delta;
    prev_blue_val = blue_delta;

    QmlPreview();
}

void ImageProcessor::saveImage(QString save_url)
{
    //qDebug() << "saveImage called";

    QFile file(save_url.remove(0,8));
    file.open(QIODevice::WriteOnly);
    bool saved = image.save(&file);

    qDebug() << "image saved: " << saved;
}

void ImageProcessor::setUrl(QString url)
{
    if(url == m_url)
        return;

    m_url = url;
    //qDebug() << "setUrl called: " << url;
    emit urlChanged();
}

QString ImageProcessor::getUrl()
{
    //qDebug() << "getUrl called";
    return m_url;
}


