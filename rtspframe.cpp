#include "videostream.h"
#include <opencv2/opencv.hpp>
#include <thread>
#include <unistd.h>

const int WIDTH = 860;
const int HEIGHT = 640;

VVideoStream  _vlc_stream;

void* pthreadDisplayFrame(void *arg)
{	
	while(1)
	{
		//std::cout << ret << std::endl;
		if (_vlc_stream.State() != VIDEO_AVTICE) { //掉线 //网络不通
			std::cout << "ipc is disable" << std::endl;
			_vlc_stream.ReOpen();
			sleep(3);
		}
		else { //正常播放
			cv::Mat m_frame = _vlc_stream.GetFrameData(0x0000010000);
			if(!m_frame.empty()) {
				cv::imshow("RGB", m_frame);
			}
			cv::waitKey(1);
		}	
	}
}

int main(int argc, char* argv[]) {
	//
	std::string rtspAddr = "rtsp://admin:wavecamera1@10.0.63.200:554";
	memcpy(_vlc_stream.m_pVideoStream.IPC.rtsp_uri, rtspAddr.c_str(), rtspAddr.length());
	_vlc_stream.m_pVideoStream.IPC.width = WIDTH;
	_vlc_stream.m_pVideoStream.IPC.height = HEIGHT;
	int ret = _vlc_stream.Open();
	if(ret != 3) {
		std::cout << "_vlc_stream[0].Play() Failed!" << std::endl;
	}
	pthread_t thread_id[8];
	pthread_create(&thread_id[0], NULL, pthreadDisplayFrame, NULL);
	
	while(1);
	_vlc_stream.Close();
}

