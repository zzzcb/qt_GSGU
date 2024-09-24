#include "icon.h"

#include "config.h"
#include <QPainter>

QIcon createIconFromSVG(const QString& svgFile)
{
	QPixmap normal(svgFile);
	
	QPainter p;
	if (g_config.m_tTheme == Theme::LIGHT)
	{
		p.begin(&normal);
		p.setCompositionMode(QPainter::CompositionMode_SourceIn);
		p.fillRect(normal.rect(), QColor(32,32,32));
		p.end();
	}

	QIcon icon;
	icon.addPixmap(normal);
	return icon;
}
