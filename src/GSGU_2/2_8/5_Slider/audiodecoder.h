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
	AudioDecoder();
	~AudioDecoder();

	bool openFile(const QString& filePath);
	void decode();

private:
	AVFormatContext* formatContext;
	AVCodecContext* codecContext;
	SwrContext* swrContext;
	int audioStreamIndex;
};


#endif 