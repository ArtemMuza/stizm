#include "WindowManager.h"



int WindowManager::Message(std::string _msg, std::string _title, messageTypes _type) {

	return MessageBoxA(NULL, (LPCSTR)_msg.c_str(), (LPCSTR)_title.c_str(), _type | MB_OK);
}

int WindowManager::Message(std::string _msg, messageTypes _type) {
	std::string _title;
	switch (_type) {

	case Exclamation: 
		_title = "Exclamation"; 
	break;

	case Information:
		_title = "Information";
	break;

	case Error:
		_title = "Error!"; 
	break;

	}
	return MessageBoxA(NULL, (LPCSTR)_msg.c_str(), (LPCSTR)_title.c_str(), _type | MB_OK);;
}