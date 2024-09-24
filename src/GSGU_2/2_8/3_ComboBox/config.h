#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

enum Theme
{
	LIGHT,
	DARK
};

struct Config
{
	Theme m_tTheme;

	void load(QString path);
	void save(QString path);
};

extern Config g_config;

#endif

