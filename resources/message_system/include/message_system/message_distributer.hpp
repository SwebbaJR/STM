#ifndef MESSAGE_SYSTEM__MESSAGE_DISTRIBUTOR_HPP
#define MESSAGE_SYSTEM__MESSAGE_DISTRIBUTOR_HPP

#include <memory>
#include <vector>
#include <functional>
#include <iostream>

#include "message_system/message_distributer_prims.hpp"

class MessageDistributer
{
public:
    explicit MessageDistributer();
    ~MessageDistributer();

private:
    std::array<std::vector<std::shared_ptr<std::function<void(const BaseMsg&)>>>, static_cast<std::size_t>(Topics::NUMBER_OF_TOPICS)> subscriber_callbacks_map;
    std::array<std::shared_ptr<std::function<void(const BaseService::Request&, BaseService::Response&)>>, static_cast<std::size_t>(Service::NUMBER_OF_SERVICES)> server_callbacks_map;

    template<typename MsgType>
    friend class Publisher;

    template<typename MsgType>
    friend class Subscriber;

    template<typename ServiceType>
    friend class Server;

    template<typename ServiceType>
    friend class Client;

    // Publisher
    void publish(Topics topic, const BaseMsg& msg);

    // Subscriber
    void add_subscriber(Topics topic, std::shared_ptr<std::function<void(const BaseMsg& msg)>> subscriber_callback);
    void remove_subscriber(Topics topic, std::shared_ptr<std::function<void(const BaseMsg& msg)>> subscriber_callback);

    // Server
    void add_server(Service service, std::shared_ptr<std::function<void(const BaseService::Request&, BaseService::Response&)>> service_callback);
    void remove_server(Service service, std::shared_ptr<std::function<void(const BaseService::Request&, BaseService::Response&)>> server_callback);

    // Client
    void send_request(Service service, const BaseService::Request& request, BaseService::Response& response, std::shared_ptr<std::function<void(const BaseService::Response&)>> client_callback);
};



#endif // MESSAGE_SYSTEM__MESSAGE_DISTRIBUTOR_HPP