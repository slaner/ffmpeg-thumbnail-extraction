#ifndef _MEDIA_DEFINED_
#define _MEDIA_DEFINED_

#include "core.h"

class MediaHelper {
public:
	static AVFormatContext* LoadFile(const char* fileName) {
		AVFormatContext* context = nullptr;
		int result = avformat_open_input(&context, fileName, nullptr, nullptr);
		if (result < 0) {
			ERRDESCRIPTION(result);
			ERROR("Unable to open input file! (%d)\n", result);
			ERROR("\tFile Name  : %s\n", fileName);
			ERROR("\tDescription: %s\n", __description);
			return nullptr;
		}

		return context;
	}

	static AVStream* FindVideoStream(AVFormatContext* context) {
		if (context == nullptr) return nullptr;
		UInt32 i;
		for (i = 0; i < context->nb_streams; i++) {
			AVStream* currentStream = context->streams[i];
			AVCodecParameters* params = currentStream->codecpar;

			if (params->codec_type == AVMEDIA_TYPE_VIDEO)
				return currentStream;
		}

		return nullptr;
	}

	static BOOL CopyCodecParameters(AVCodecContext* context, AVCodecParameters* params) {
		if (context == nullptr) return FALSE;
		int result = avcodec_parameters_to_context(context, params);
		if (result < 0) {
			ERRDESCRIPTION(result);
			ERROR("Unable to copy parameters to context! (%d)\n", result);
			ERROR("\tDescription: %s\n", __description);
			return FALSE;
		}
		return TRUE;
	}

	static AVCodecContext* AllocCodecContext(AVCodecID codecId) {
		AVCodec* videoCodec = avcodec_find_decoder(codecId);
		if (videoCodec == nullptr) {
			ERROR("Unable to find decoder for id: %d\n", codecId);
			return nullptr;
		}

		AVCodecContext* context = avcodec_alloc_context3(videoCodec);
		if (context == nullptr) {
			ERROR("Unable to allocate codec context!\n");
			return nullptr;
		}

		int result = avcodec_open2(context, videoCodec, nullptr);
		if (result < 0) {
			ERRDESCRIPTION(result);
			ERROR("Unable to open codec context! (%d)\n", result);
			ERROR("\tDescription: %s\n", __description);
			avcodec_free_context(&context);
			return nullptr;
		}

		return context;
	}

	static void ReleaseCodecContext(AVCodecContext* context) {
		if (context == nullptr) return;
		avcodec_free_context(&context);
	}
	static void ReleaseFormatContext(AVFormatContext* context) {
		if (context == nullptr) return;
		avformat_close_input(&context);
	}
};

#endif