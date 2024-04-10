#include "mprpccontroller.h"

MprpcController::MprpcController()
{
    m_failed = false;
    m_errmsg = "";
}

void MprpcController::Reset()
{
    m_failed = false;
    m_errmsg = "";
}

bool MprpcController::Failed() const
{
    return m_failed;
}

std::string MprpcController::ErrorText() const
{
    return m_errmsg;
}

void MprpcController::SetFailed(const std::string& reason)
{
    m_failed = true;
    m_errmsg = reason;
}

void MprpcController::StartCancel() {}
bool MprpcController::IsCanceled() const { return false; }
void MprpcController::NotifyOnCancel(google::protobuf::Closure* callback) {}




