#ifndef AUDIO_DECODER_H
#define AUDIO_DECODER_H

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>

}

#include <QString>

class AudioDecoder
{
public:
	static bool decode(const QString& filePath);
};

#endif 