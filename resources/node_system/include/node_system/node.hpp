#ifndef NODE_SYSTEM__NODE_HPP
#define NODE_SYSTEM__NODE_HPP

#include <memory>

#include "message_system/message_distributer.hpp"
#include "message_system/publisher.hpp"
#include "message_system/subscriber.hpp"
#include "message_system/server.hpp"
#include "message_system/client.hpp"

class Node
{
public:
    Node(std::string node_name, std::weak_ptr<MessageDistributer> message_distributer);
    ~Node();

    template<typename MsgType>
    std::shared_ptr<Publisher<MsgType>> create_publisher(const Topics& topic);

    template<typename MsgType>
    std::shared_ptr<Subscriber<MsgType>> create_subscriber(const Topics& topic, std::function<void(const MsgType& msg)> callback);

    template<typename ServiceType>
    std::shared_ptr<Server<ServiceType>> create_server(Service service, std::function<void(const typename ServiceType::Request&, typename ServiceType::Response&)> callback);

    template<typename ServiceType>
    std::shared_ptr<Client<ServiceType>> create_client(Service service, std::function<void(const typename ServiceType::Response&)> callback);

private:
    std::weak_ptr<MessageDistributer> message_distributer;
    std::string node_name;
};

template<typename MsgType>
std::shared_ptr<Publisher<MsgType>> Node::create_publisher(const Topics& topic)
{
    static_assert(std::is_base_of<BaseMsg, MsgType>::value, "MsgType must derive from BaseMsg");
    return std::make_shared<Publisher<MsgType>>(topic, message_distributer);
}

template<typename MsgType>
std::shared_ptr<Subscriber<MsgType>> Node::create_subscriber(const Topics& topic, std::function<void(const MsgType& msg)> callback)
{
    static_assert(std::is_base_of<BaseMsg, MsgType>::value, "MsgType must derive from BaseMsg");
    return std::make_shared<Subscriber<MsgType>>(topic, message_distributer, callback);
}

template<typename ServiceType>
std::shared_ptr<Server<ServiceType>> Node::create_server(Service service, std::function<void(const typename ServiceType::Request&, typename ServiceType::Response&)> callback)
{
    static_assert(std::is_base_of<BaseService, ServiceType>::value, "ServiceType must derive from BaseService");
    static_assert(std::is_base_of<BaseService::Request, typename ServiceType::Request>::value, "ServiceType::Request must derive from BaseService::Request");
    static_assert(std::is_base_of<BaseService::Response, typename ServiceType::Response>::value, "ServiceType::Response must derive from BaseService::Response");

    return std::make_shared<Server<ServiceType>>(service, message_distributer, callback);
}

template<typename ServiceType>
std::shared_ptr<Client<ServiceType>> Node::create_client(Service service, std::function<void(const typename ServiceType::Response&)> callback)
{
    static_assert(std::is_base_of<BaseService, ServiceType>::value, "ServiceType must derive from BaseService");
    static_assert(std::is_base_of<BaseService::Request, typename ServiceType::Request>::value, "ServiceType::Request must derive from BaseService::Request");
    static_assert(std::is_base_of<BaseService::Response, typename ServiceType::Response>::value, "ServiceType::Response must derive from BaseService::Response");
    
    return std::make_shared<Client<ServiceType>>(service, message_distributer, callback);
}




#endif // NODE_SYSTEM__NODE_HPP