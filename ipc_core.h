#ifndef IPC_CORE_H
#define IPC_CORE_H

#include "common.h"
#include <iostream>

class IPCCoreWork {

public:
	IPCCoreWork();
	~IPCCoreWork();
	
	static IPCCoreWork* getInstance() {
		if(s_pIPCCorework == NULL) {
			s_pIPCCorework= new IPCCoreWork();
		}
		return s_pIPCCorework;
	}
    void Init();
    static cv::Mat GetFrame(const std::string ipc_id, int task_id);
	//static int DelIPCamera(const std::string ipc_id);
	static int AddIPCamera(const char *ip, const char* username, const char* password, int channel);
	
private:

	void loadAllIPCInfo();
    void threadIPCOnline();
	
private:
	static IPCCoreWork* s_pIPCCorework;
};

#endif

