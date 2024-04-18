#pragma once
#include "google/protobuf/service.h"
#include <string>


/*
    考虑到在执行一次Rpc的调用过程中，并不是每次都成功，所以有了controller
    监视Rpc的调用是否正常执行，避免做多余的结果判断

*/


class MprpcController : public google::protobuf::RpcController
{
public:
    MprpcController();
    void Reset();
    bool Failed() const;
    std::string ErrorText() const;
    void SetFailed(const std::string& reason);

    // 目前未实现具体的功能
    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure* callback);
private:
    bool m_failed;
    std::string m_errmsg;
};