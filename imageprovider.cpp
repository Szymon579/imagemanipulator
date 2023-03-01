#include "imageprovider.h"

#include <QDebug>

ImageProvider::ImageProvider(ImageProcessor *processor)
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    qDebug() << "ImageProvider constructor called";

    //at this stage the pixmap is empty so this is useless
    //processed_pixmap = processor->getPixmap();
    //processed_pixmap.fill(QColor(Qt::blue).rgba());
}

// this has to be called every time imageProcessor::pixmap
// changes
QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
    {
       qDebug() << "requestImage called";

       int width = 100;
       int height = 50;


       qDebug() << "id:" << id;
       if (size)
          *size = QSize(width, height);

       QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                      requestedSize.height() > 0 ? requestedSize.height() : height);
       pixmap.fill(QColor(id).rgba());

       //pixmap.fill(QColor(Qt::blue).rgba());
       //pixmap.load(":/ui/assets/reflect.png");
       //pixmap = processed_pixmap;

       return pixmap;
       //return processed_pixmap;
    }
