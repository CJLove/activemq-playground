#pragma once
#include <vector>
#include <string>
#include <memory>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <cms/ExceptionListener.h>
#include <spdlog/spdlog.h>

class Broker;

class Producer {
public:
    Producer(Broker &broker, std::vector<std::string> &topics);

    virtual ~Producer();



private:

    Broker &m_broker;

    std::vector<std::string> m_topics;

    std::shared_ptr<spdlog::logger> m_logger;

    std::vector<cms::Destination*> m_destinations;

    std::vector<cms::MessageProducer*> m_producers;

};