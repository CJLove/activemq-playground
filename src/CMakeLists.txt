cmake_minimum_required(VERSION 3.17)

project(mq)

include_directories(/usr/local/include /usr/local/include/spdlog )

set (mq_SRC
    main.cpp
    broker.cpp
    consumer.cpp
)

add_executable( mq ${mq_SRC})

target_link_libraries( mq PkgConfig::PKG_ACTIVEMQ Threads::Threads )
