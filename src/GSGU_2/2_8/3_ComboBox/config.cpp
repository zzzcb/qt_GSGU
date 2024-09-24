#include "config.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

Config g_config;

void Config::load(QString path)
{
	QFile f(path);
	if (f.open(QIODevice::ReadOnly))
	{
		QJsonParseError jErr;
		QJsonDocument jDoc = QJsonDocument::fromJson(f.readAll(), &jErr);
		if (jErr.error == QJsonParseError::NoError && jDoc.isObject())
		{
			QJsonObject jObj = jDoc.object();
			if (jObj.contains("theme"))
			{
				m_tTheme = static_cast<Theme>(jObj.value("theme").toInt());
			}
		}
	}
	f.close();
}

void Config::save(QString path)
{
	QJsonObject jObj;
	jObj["theme"] = m_tTheme;

	QJsonDocument jDoc;
	jDoc.setObject(jObj);

	QFile f(path);
	if (f.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		f.write(jDoc.toJson());
	}
	f.close();
}

