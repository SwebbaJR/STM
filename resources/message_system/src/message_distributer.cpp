#include "message_system/message_distributer.hpp"

MessageDistributer::MessageDistributer()
{

}

MessageDistributer::~MessageDistributer()
{

}

void MessageDistributer::publish(Topics topic, const BaseMsg& msg)
{
    for (auto& subscriber_callback : subscriber_callbacks_map[topic])
    {
        subscriber_callback->operator()(msg);
    }
}

void MessageDistributer::add_subscriber(Topics topic, std::shared_ptr<std::function<void(const BaseMsg& msg)>> subscriber_callback)
{
    subscriber_callbacks_map[topic].push_back(subscriber_callback);
}

void MessageDistributer::remove_subscriber(Topics topic, std::shared_ptr<std::function<void(const BaseMsg& msg)>> subscriber_callback)
{
    auto& topic_callbacks = subscriber_callbacks_map[topic];
    auto itterator = std::find_if(topic_callbacks.begin(), topic_callbacks.end(), 
        [&](const std::shared_ptr<std::function<void(const BaseMsg&)>>& callback) 
        {
            return callback == subscriber_callback;
        });

    if (itterator != topic_callbacks.end())
    {
        topic_callbacks.erase(itterator);
    }
}

void MessageDistributer::add_server(Service service, std::shared_ptr<std::function<void(const BaseService::Request&, BaseService::Response&)>> server_callback)
{
    if (server_callbacks_map[service] != nullptr)
    {
        std::cout << "Error: Server already exists for service" << std::endl;
        return;
    }
    server_callbacks_map[service] = server_callback;
}

void MessageDistributer::remove_server(Service service, std::shared_ptr<std::function<void(const BaseService::Request&, BaseService::Response&)>> server_callback)
{
    if(server_callbacks_map[service] == nullptr)
    {
        std::cout << "Error: Server does not exist for service" << std::endl;
        return;
    }
    if (server_callbacks_map[service] != server_callback)
    {
        std::cout << "Error: Cannot remove callback as it is incorrect" << std::endl;
        return;
    }
    server_callbacks_map[service] = nullptr;
}

void MessageDistributer::send_request(Service service, const BaseService::Request& request, BaseService::Response& response, std::shared_ptr<std::function<void(const BaseService::Response&)>> client_callback)
{
    if (server_callbacks_map[service] == nullptr)
    {
        std::cout << "Error: Server does not exist for service" << std::endl;
        return;
    }

    server_callbacks_map[service]->operator()(request, response);
    client_callback->operator()(response);
}