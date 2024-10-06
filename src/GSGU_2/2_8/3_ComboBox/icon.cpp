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
	icon.addPixmap(normal, QIcon::Normal);


	////禁用状态
	//QPixmap disabled(normal.size());
	//disabled.fill(Qt::transparent);

	//p.begin(&disabled);
	//p.setCompositionMode(QPainter::CompositionMode_DestinationOver);
	//p.setOpacity(0.5);
	//p.drawPixmap(0, 0, normal);
	//p.end();

	//icon.addPixmap(disabled, QIcon::Disabled);

	return icon;
}
