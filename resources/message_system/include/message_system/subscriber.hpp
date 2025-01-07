#ifndef MESSAGE_SYSTEM__SUBSCRIBER_HPP
#define MESSAGE_SYSTEM__SUBSCRIBER_HPP

#include <memory>
#include <functional>

#include "message_system/message_distributer.hpp"

template<typename MsgType>
class Subscriber
{
public:
    explicit Subscriber(Topics topic, std::weak_ptr<MessageDistributer> message_distributer, std::function<void(const MsgType& msg)> callback);
    ~Subscriber();

private:
    Topics topic; 
    std::weak_ptr<MessageDistributer> message_distributer;
    std::function<void(const MsgType&)> callback;
    std::shared_ptr<std::function<void(const BaseMsg&)>> standard_subscriber_callback;
};

template<typename MsgType>
Subscriber<MsgType>::Subscriber(Topics topic, std::weak_ptr<MessageDistributer> message_distributer, std::function<void(const MsgType& msg)> callback) :
    topic(topic),
    message_distributer(message_distributer),
    callback(callback)
{
    standard_subscriber_callback = std::make_shared<std::function<void(const BaseMsg&)>>(
        [this, callback](const BaseMsg& msg)
        {
            callback(static_cast<const MsgType&>(msg));
        }
    );

    if(auto message_distrubter_ptr =  message_distributer.lock())
    {
        message_distrubter_ptr->add_subscriber(topic, standard_subscriber_callback);
    }
    else
    {
        std::cout << "Error: MessageDistributer is not available" << std::endl;
    }
}

template<typename MsgType>
Subscriber<MsgType>::~Subscriber()
{
    if(auto message_distrubter_ptr =  message_distributer.lock())
    {
        message_distrubter_ptr->remove_subscriber(topic, standard_subscriber_callback);
    }
}

#endif // MESSAGE_SYSTEM__SUBSCRIBER_HPP