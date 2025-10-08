#pragma once
#include "const.h"
class HttpConnection :public std::enable_shared_from_this<HttpConnection>
{
public:
	//������Ԫ
	friend class LogicSystem;
	//���캯��
	HttpConnection(boost::asio::io_context &ioc);
	void Start(); //������д�¼�

	tcp::socket& GetSocket()
	{
		return _socket;
	}

	


private:
	//��ʱ���
	void CheckDeadLine();
	//��Ӧ����
	void WriteResponse();
	void HandelReq();
	void PreParseGetParam();
	tcp::socket _socket;
	//�������Ĵ�С
	beast::flat_buffer _bufffer{8192};
	http::request<http::dynamic_body> _request;
	http::response<http::dynamic_body> _response;
	//����һ����ʱ��
	net::steady_timer deadLine_{ _socket.get_executor(),std::chrono::seconds(60) };

	std::string _get_url;
	std::unordered_map<std::string, std::string> _get_params;

};

