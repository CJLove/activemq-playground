#include "broker.h"

Broker::Broker(const std::string &brokerUri):
    m_brokerUri(brokerUri),
    m_logger(spdlog::get("logger"))
    
{
    std::unique_ptr<cms::ConnectionFactory> connectionFactory(cms::ConnectionFactory::createCMSConnectionFactory(brokerUri));
    m_connection = connectionFactory->createConnection();
    m_connection->start();

}

Broker::~Broker()
{
    close();
}

void Broker::onException(const cms::CMSException &ex)
{
    m_logger->info("Caught exception {}", ex.getMessage());
}

cms::Connection& Broker::getConnection()
{
    return *m_connection;
}

void Broker::close()
{
    if (m_connection) {
        try {
            m_connection->close();
        }
        catch (cms::CMSException &e) {
            m_logger->info("Caught exception {}", e.getMessage());
        }
    }   
}