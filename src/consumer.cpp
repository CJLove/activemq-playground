
#include "broker.h"
#include "consumer.h"

Consumer::Consumer(Broker &broker, std::vector<std::string> &topics):
    m_broker(broker),
    m_connection(m_broker.getConnection()),
    m_topics(topics),
    m_logger(spdlog::get("logger"))
    
{

    m_session = m_connection.createSession(cms::Session::AUTO_ACKNOWLEDGE);

    for (const auto &topic: m_topics) {
        m_logger->info("Creating topic {}",topic);
        m_destinations.push_back(m_session->createTopic(topic));

        m_consumers.push_back(m_session->createConsumer(m_destinations.back()));

        m_consumers.back()->setMessageListener(this);
    }
}

Consumer::~Consumer()
{
    cleanup();
}

void Consumer::onMessage(const cms::Message *msg)
{
    auto textMessage = dynamic_cast<const cms::TextMessage*>(msg);
    if (textMessage) {
        m_logger->info("Got message {}", textMessage->getText());
    } else {
        m_logger->info("Got message");
    }
}

void Consumer::onException(const cms::CMSException &ex)
{
    m_logger->info("Caught exception {}", ex.getMessage());
}

void Consumer::cleanup()
{

    try {
        for (const auto *dest: m_destinations) {
            delete dest;
        }
        for (const auto *consumer: m_consumers) {
            delete consumer;
        }
        delete m_session;
    }
    catch (cms::CMSException &e) {
        m_logger->info("Caught exception {}", e.getMessage());
    }
}