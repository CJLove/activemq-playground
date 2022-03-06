#include <activemq/library/ActiveMQCPP.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <iostream>
#include <vector>
#include "broker.h"
#include "consumer.h"

void usage()
{
    std::cerr << "Usage:\n"
              << "mq [-l <logLevel>][-b <broker>][-c <topic>][-p <topic>]\n";
}


int main(int argc, char**argv)
{
    int logLevel = spdlog::level::trace;
    std::vector<std::string> consumerTopics;
    std::vector<std::string> producerTopics;
    std::string broker = "tcp://localhost:61616";
    int c;
    while ((c = getopt(argc, argv, "l:b:p:c:?")) != EOF)
    {
        switch (c)
        {
        case 'l':
            logLevel = std::stoi(optarg);
            break;
        case 'b':
            broker = optarg;
            break;
        case 'c':
            consumerTopics.push_back(optarg);
            break;
        case 'p':
            producerTopics.push_back(optarg);
            break;
        case '?':
            usage();
            exit(1);
            break;
        default:
            break;
        }
    }

    // Create the main logger named "logger" and configure it
    auto logger = spdlog::stdout_logger_mt("logger");
    // Log format:
    // 2018-10-08 21:08:31.633|020288|I|Thread Worker thread 3 doing something
    logger->set_pattern("%Y-%m-%d %H:%M:%S.%e|%t|%L|%v");
    // Set the log level for filtering
    spdlog::set_level(static_cast<spdlog::level::level_enum>(logLevel));

    logger->info("mq logging started");

    activemq::library::ActiveMQCPP::initializeLibrary();
    Broker theBroker(broker);
    Consumer consumer(theBroker,consumerTopics);


    // Command loop
    while (true) {
        sleep(1);
    }
}