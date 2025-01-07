#ifndef MESSAGE_SYSTEM__CLIENT_HPP
#define MESSAGE_SYSTEM__CLIENT_HPP

#include "message_system/message_distributer.hpp"

template<typename ServiceType>
class Client
{
public:
    explicit Client(Service service, 
            std::weak_ptr<MessageDistributer> message_distributer, 
            std::function<void(const typename ServiceType::Response&)> callback);
    ~Client();

    void send_request(const typename ServiceType::Request& request);

private:
    Service service;
    std::weak_ptr<MessageDistributer> message_distributer;
    std::function<void(const typename ServiceType::Response&)> callback;
    std::shared_ptr<std::function<void(const BaseService::Response&)>> standard_client_callback;
};

template<typename ServiceType>
Client<ServiceType>::Client(Service service, 
            std::weak_ptr<MessageDistributer> message_distributer, 
            std::function<void(const typename ServiceType::Response&)> callback) :
    service(service),
    message_distributer(message_distributer),
    callback(callback)
{
    standard_client_callback = std::make_shared<std::function<void(const BaseService::Response&)>>(
        [this, callback](const BaseService::Response& response)
        {
            callback(static_cast<const typename ServiceType::Response&>(response));
        }
    );
}

template<typename ServiceType>
Client<ServiceType>::~Client()
{
    
}

template<typename ServiceType>
void Client<ServiceType>::send_request(const typename ServiceType::Request& request)
{
    typename ServiceType::Response response;
    if(auto message_distrubter_ptr =  message_distributer.lock())
    {
        message_distrubter_ptr->send_request(service, request, response, standard_client_callback);
    }
    else
    {
        std::cout << "Error: MessageDistributer is not available" << std::endl;
    }
}

#endif // MESSAGE_SYSTEM__CLIENT_HPP