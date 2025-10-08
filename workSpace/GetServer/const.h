#pragma once
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <iostream>
#include <functional>
#include <map>
#include <unordered_map>
#include "Singleton.h"
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
//��ȡ�ļ�
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "ConfigMgr.h"
#include <atomic>
#include "Singleton.h"
#include <queue>
#include <condition_variable>
#include  "hiredis/hiredis.h"
#include <cassert>
#include "RedisConPool.h"

//#include <mysqlx/xdevapi.h>
//#include <mysql/jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/exception.h>


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

enum ErrorCodes {
	Success = 0,
	Error_Json = 1001,  //Json��������
	RPCFailed = 1002,  //RPC �������
	VarifyExpired = 1003, // ��֤�����
	VarifyCodeErr = 1004, //  ��֤�����
	UserExist = 1005,       //  �û��Ѿ�������
	PasswdErr = 1006,    // �������
	EmailNotMatch = 1007,  // ���䲻ƥ��
	PasswdUpFailed = 1008,  //��������ʧ��
	PasswdInvalid = 1009,   //�������ʧ��
	TokenInvalid = 1010,   //
	UidInvalid = 1011,  //

};
class Defer {
public:
	//
	Defer(std::function<void()> func) : func_(func) {}
	// 
	~Defer() {
		func_();
	}

private:
	std::function<void()> func_;
};




#define CODEPREFIX  "code_"