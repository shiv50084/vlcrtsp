#include "ipc_core.h"


int main(int argc, char* argv[]) {
	IPCCoreWork::getInstance()->Init();
	while(1) {
		cv::Mat frame = IPCCoreWork::GetFrame("10.0.63.200", 4);
		if(!frame.empty()) {
			cv::imshow("0x0000000001", frame);
		}

		cv::Mat frame1 = IPCCoreWork::GetFrame("10.0.63.200", 8);
		if(!frame1.empty()) {
			cv::imshow("0x0000010000", frame1);
		}


//		cv::Mat frame2 = IPCCoreWork::GetFrame("10.0.63.200", 0x0100000000);
//		if(!frame2.empty()) {
//			cv::imshow("0x0100000000", frame2);
//		}
		cv::waitKey(1);
	}
}
