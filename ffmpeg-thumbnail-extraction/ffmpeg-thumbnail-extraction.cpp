extern "C" {
	#include "core.h"
}
#pragma warning(disable:4996)

int exitOnKeyPress(int exitCode) {
	printf("Press Any Key to Exit\n");
	getch();
	return exitCode;
}

int main() {
	int result;
	char buffer[260];

	memset(buffer, 0, sizeof(buffer));
	printf("Enter filename: ");
	scanf("%s%*c", buffer);

	AVFormatContext* ctxFormat = MediaHelper::LoadFile(buffer);
	if (ctxFormat == nullptr) return exitOnKeyPress(-1);

	AVStream* video = MediaHelper::FindVideoStream(ctxFormat);
	if (video == nullptr) {
		MediaHelper::ReleaseFormatContext(ctxFormat);
		return exitOnKeyPress(-1);
	}

	AVCodecParameters* params = video->codecpar;
	LOG("%d x %d @ %.2lf fps\n", params->width, params->height, Q2D(video->r_frame_rate));
	LOG("%.2fs\n", (Double) video->duration / video->time_base.den);

	AVCodecContext* ctxCodec = MediaHelper::AllocCodecContext(params->codec_id);
	if (ctxCodec == nullptr) {
		MediaHelper::ReleaseFormatContext(ctxFormat);
		return exitOnKeyPress(-1);
	}

	AVPacket* packet = av_packet_alloc();
	AVFrame* frame = av_frame_alloc();

	Int64 seekTime = 0;
	while (av_seek_frame(ctxFormat, video->index, seekTime, AVSEEK_FLAG_FRAME)) {
		av_packet_unref(packet);
		result = av_read_frame(ctxFormat, packet);

		if (result >= 0) {
			if (packet->stream_index != video->index) continue;
			result = avcodec_send_packet(ctxCodec, packet);

			if (result >= 0) {
				av_frame_unref(frame);
				result = avcodec_receive_frame(ctxCodec, frame);

				if (result >= 0) {

					// todo
				} else {
					ERRDESCRIPTION(result);
					ERROR("Unable to receive frame (%d)\n", result);
					ERROR("\tDescription: %s\n", __description);
				}
			} else {
				ERRDESCRIPTION(result);
				ERROR("Unable to send packet (%d)\n", result);
				ERROR("\tDescription: %s\n", __description);
			}
		} else {
			ERRDESCRIPTION(result);
			ERROR("Unable to read frame (%d)\n", result);
			ERROR("\tDescription: %s\n", __description);
		}
	};

	MediaHelper::ReleaseCodecContext(ctxCodec);
	MediaHelper::ReleaseFormatContext(ctxFormat);

	return exitOnKeyPress(0);
}