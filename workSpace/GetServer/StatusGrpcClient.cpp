#include "StatusGrpcClient.h"

/// <summary>
/// ���� StatusGrpcClient ���󣬲���ʼ�����ӳء�
/// </summary>
StatusGrpcClient::StatusGrpcClient()
{
	auto& gCfgMgr = ConfigMgr::Inst();
	std::string host = gCfgMgr["StatusServer"]["Host"];
	std::string port = gCfgMgr["StatusServer"]["Port"];
	///����һ�����ӳ� ����СΪ5
	pool_.reset(new StatusConPool(5, host, port));
}

/// <summary>
/// ���һ���µ�����
/// </summary>
/// <param name="uid"></param>
/// <returns></returns>


GetChatServerRsp StatusGrpcClient::GetChatServer(int uid)
{
	///�������� Զ�̹��̵���ʱ����Ҫ����Ķ���
	ClientContext context;
	GetChatServerRsp reply;
	GetChatServerReq request;
	request.set_uid(uid);
	///�����ӳ��л�ȡһ������
	auto stub = pool_->getConnection();
	/// ����rpc���ÿ���GRPC�ĵ���
	Status status = stub->GetChatServer(&context, request, &reply);
	Defer defer([&stub, this]() {
		pool_->returnConnection(std::move(stub));
		});
	if (status.ok()) {
		return reply;
	}
	else {
		reply.set_error(ErrorCodes::RPCFailed);
		return reply;
	}
}
LoginRsp StatusGrpcClient::Login(int uid, std::string token)
{
	ClientContext context;
	LoginRsp reply;
	LoginReq request;
	request.set_uid(uid);
	request.set_token(token);

	auto stub = pool_->getConnection();
	Status status = stub->Login(&context, request, &reply);
	Defer defer([&stub, this]() {
		pool_->returnConnection(std::move(stub));
		});
	if (status.ok()) {
		return reply;
	}
	else {
		reply.set_error(ErrorCodes::RPCFailed);
		return reply;
	}
}
