#include "CServer.h"
#include "HttpConnection.h"
#include "AsioIOServicePool.h"
CServer::CServer(boost::asio::io_context& ioc, unsigned short& port):_ioc(ioc),
_acceptor(ioc, tcp::endpoint(tcp::v4(), port))
{
	// ���캯����ʼ�� io_context �ͼ����˿�

}
void CServer::Start()
{

	//��������auto self = shared_from_this(); ���� lambda �� [self, ...]����Ŀ�ģ�
	// ����ȷ���첽����δ���ʱ��CServer ���󲻻ᱻ��ǰ������
	auto self = shared_from_this();
	auto& io_contex = AsioIOServicePool::GetInstance()->GetIOService();
	/*
	1.	std::make_shared<HttpConnection>(io_contex)
		����� HttpConnection �Ĺ��캯�������� io_contex ������
		�Զ��ڶ��Ϸ��� HttpConnection ���󣬲��������ü������ƿ顣
	*/


	std::shared_ptr<HttpConnection>new_con = std::make_shared<HttpConnection>(io_contex);
	_acceptor.async_accept(new_con->GetSocket(), [self,new_con](beast::error_code ec) {
		try
		{
			// ����д��󣬵ݹ���� Start() ��������
			if (ec)
			{
				self->Start();  //����Cerver ��start()����
				return;
			}
			// �����µ����Ӷ�����������
			new_con->Start();
			//�������м���
			self->Start();

		}
		catch (const std::exception& exp)
		{
			// �쳣�����˴�δ�����־��
			std::cout << "exception is " << exp.what() << std::endl;
			self->Start();
		}
		});

}