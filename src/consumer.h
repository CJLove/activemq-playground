#pragma once

#include <activemq/core/ActiveMQConnectionFactory.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <memory>
#include <spdlog/spdlog.h>

class Broker;

class Consumer: public cms::ExceptionListener,
                public cms::MessageListener
{
public:
    Consumer(Broker &broker, std::vector<std::string> &topics);

    virtual ~Consumer();

    virtual void onMessage(const cms::Message *msg) override;

    virtual void onException(const cms::CMSException &ex) override;

private:
    void cleanup();

    Broker& m_broker;
    cms::Connection &m_connection;

    std::vector<std::string> m_topics;

    std::shared_ptr<spdlog::logger> m_logger;

    cms::Session* m_session;
    
    std::vector<cms::Destination*> m_destinations;

    std::vector<cms::MessageConsumer*> m_consumers;

};