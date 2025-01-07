#ifndef MESSAGE_SYSTEM__PUBLISHER_HPP
#define MESSAGE_SYSTEM__PUBLISHER_HPP

#include <memory>

#include "message_system/message_distributer.hpp"

template<typename MsgType>
class Publisher
{
public:
    explicit Publisher(const Topics& topic, std::weak_ptr<MessageDistributer> message_distributer);
    ~Publisher();

    void publish(const MsgType& msg);

private:
    Topics topic;
    std::weak_ptr<MessageDistributer> message_distributer;
};

template<typename MsgType>
Publisher<MsgType>::Publisher(const Topics& topic, std::weak_ptr<MessageDistributer> message_distributer) :
    topic(topic), 
    message_distributer(message_distributer)
{

}

template<typename MsgType>
Publisher<MsgType>::~Publisher(){}

template<typename MsgType>
void Publisher<MsgType>::publish(const MsgType& msg)
{
    if(auto message_distrubter_ptr =  message_distributer.lock())
    {
        message_distrubter_ptr->publish(topic, msg);
    }
    else
    {
        std::cout << "Error: MessageDistributer is not available" << std::endl;
    }
}



#endif // MESSAGE_SYSTEM__PUBLISHER_HPP