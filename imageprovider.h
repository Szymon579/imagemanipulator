#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include "imageprocessor.h"

#include <QQuickImageProvider>
#include <QPixmap>


class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider(ImageProcessor *processor);

    QPixmap requestPixmap(const QString &id, QSize *size,
                    const QSize &requestedSize) override;

private:
    QPixmap processed_pixmap;
};

#endif // IMAGEPROVIDER_H
