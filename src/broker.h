#pragma once

#include <activemq/core/ActiveMQConnectionFactory.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <memory>
#include <spdlog/spdlog.h>

class Broker: public cms::ExceptionListener {
public:
    Broker(const std::string &brokerUri);

    virtual ~Broker();

    virtual void onException(const cms::CMSException &ex) override;

    cms::Connection &getConnection();

    void close();

private:

    std::string m_brokerUri;

    std::shared_ptr<spdlog::logger> m_logger;

    cms::Connection* m_connection;
};