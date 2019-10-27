/*
	remote_server.h	- header file for the Remote Server class.
	
	Revision 0
	
	Notes:
			- This class declares the main class to be used by NymphRPC clients.
			
	2017/06/24, Maya Posch	: Initial version.	
	(c) Nyanko.ws
*/


#ifndef REMOTE_SERVER_H
#define REMOTE_SERVER_H


#include <vector>
#include <string>
#include <map>

#include <Poco/Semaphore.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>

#include "nymph_method.h"
#include "nymph_listener.h"
#include "nymph_logger.h"


class NymphRemoteServer {
	static std::map<uint32_t, Poco::Net::StreamSocket*> sockets;
	static std::map<uint32_t, Poco::Semaphore*> socketSemaphores;
	static Poco::Mutex socketsMutex;
	static uint32_t lastHandle;
	static long timeout;
	static std::string loggerName;
	static uint32_t nextMethodId;
	
	static std::map<std::string, NymphMethod>& methods();
	static std::map<uint32_t, NymphMethod*>& methodsIds();
	static Poco::Mutex& methodsMutex();
	
	static bool registerMethod(std::string name, NymphMethod method);
	
public:
	static bool init(logFnc logger, int level = NYMPH_LOG_LEVEL_TRACE, long timeout = 3000);
	static bool sync(uint32_t handle, std::string &result);
	static void setLogger(logFnc logger, int level);
	static bool shutdown();
	static bool connect(std::string host, int port, uint32_t &handle, void* data, std::string &result);
	static bool connect(std::string url, uint32_t &handle, void* data, std::string &result);
	static bool connect(Poco::Net::SocketAddress sa, uint32_t &handle, void* data, std::string &result);
	static bool disconnect(uint32_t handle, std::string &result);
	static bool callMethod(uint32_t handle, std::string name, std::vector<NymphType*> &values, 
										NymphType* &returnvalue, std::string &result);
	static bool callMethodId(uint32_t handle, uint32_t id, std::vector<NymphType*> &values, NymphType* &returnvalue, std::string &result);
	static bool removeMethod(std::string name);
	
	static bool registerCallback(std::string name, NymphCallbackMethod method, void* data);
	static bool removeCallback(std::string name);
};

#endif
