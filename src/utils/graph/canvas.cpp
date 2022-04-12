#include "canvas.h"

namespace utils {
namespace graph {

Canvas::Canvas(QColor beginColor, QColor endColor, QwtPlot *plot)
    : QwtPlotCanvas{plot}
{
    // The backing store is important, when working with widget
    // overlays ( f.e rubberbands for zooming ).
    // Here we don't have them and the internal
    // backing store of QWidget is good enough.
    setPaintAttribute(QwtPlotCanvas::BackingStore, false);

    if (QwtPainter::isX11GraphicsSystem()) {
        // Disabling the backing store of Qt improves the performance
        // for the direct painter even more, but the canvas becomes
        // a native window of the window system, receiving paint events
        // for resize and expose operations. Those might be expensive
        // when there are many points and the backing store of
        // the canvas is disabled. So in this application
        // we better don't disable both backing stores.

        if (testPaintAttribute(QwtPlotCanvas::BackingStore)) {
            setAttribute(Qt::WA_PaintOnScreen, true);
            setAttribute(Qt::WA_NoSystemBackground, true);
        }
    }

    setupPalette(beginColor, endColor);
}

void Canvas::setupPalette(QColor beginColor, QColor endColor)
{
    QPalette pal = palette();
    QLinearGradient gradient;
    gradient.setCoordinateMode(QGradient::StretchToDeviceMode);
    gradient.setColorAt(1.0, beginColor);
    gradient.setColorAt(0.0, endColor);
    pal.setBrush(QPalette::Window, QBrush(gradient));

    // QPalette::WindowText is used for the curve color
    pal.setColor(QPalette::WindowText, Qt::green);
    setPalette(pal);
}

}
}
