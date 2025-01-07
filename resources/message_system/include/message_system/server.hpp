#ifndef MESSAGE_SYSTEM__SERVER_HPP
#define MESSAGE_SYSTEM__SERVER_HPP

#include "message_distributer.hpp"

template<typename ServiceType>
class Server
{
public:
    explicit Server(Service service, 
                std::weak_ptr<MessageDistributer> message_distributer, 
                std::function<void(const typename ServiceType::Request&, typename ServiceType::Response&)> callback);
    ~Server();

private:
    Service service;
    std::weak_ptr<MessageDistributer> message_distributer;
    std::function<void(const typename ServiceType::Request&, typename ServiceType::Response&)> callback;
    std::shared_ptr<std::function<void(const BaseService::Request&, BaseService::Response&)>> standard_server_callback;
};

template<typename ServiceType>
Server<ServiceType>::Server(Service service, 
                std::weak_ptr<MessageDistributer> message_distributer, 
                std::function<void(const typename ServiceType::Request&, typename ServiceType::Response&)> callback) :
    service(service),
    message_distributer(message_distributer),
    callback(callback)
{
    standard_server_callback = std::make_shared<std::function<void(const BaseService::Request&, BaseService::Response&)>>(
        [this, callback](const BaseService::Request& request, BaseService::Response& response)
        {
            callback(static_cast<const typename ServiceType::Request&>(request), static_cast<typename ServiceType::Response&>(response));
        }
    );
    if(auto message_distrubter_ptr =  message_distributer.lock())
    {
        message_distrubter_ptr->add_server(service, standard_server_callback);
    }
    else
    {
        std::cout << "Error: MessageDistributer is not available" << std::endl;
    }
}

template<typename ServiceType>
Server<ServiceType>::~Server()
{
    if(auto message_distrubter_ptr =  message_distributer.lock())
    {
        message_distrubter_ptr->remove_server(service, standard_server_callback);
    }
}



#endif // MESSAGE_SYSTEM__SERVER_HPP