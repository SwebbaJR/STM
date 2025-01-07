/*
#include <iostream>
#include <vector>
#include <functional>
#include <memory>

#include "message_system/message_distributer.hpp"
#include "message_system/subscriber.hpp"
#include "message_system/publisher.hpp"
#include "message_system/server.hpp"
#include "message_system/client.hpp"

// Define different message types (structs)
struct MessageA : BaseMsg
{
    std::string valueA;
};

struct MessageB : BaseMsg
{
    int valueB;
};

struct MessageC : BaseMsg
{
    float valueC;
};

struct ServiceA : BaseService
{
    struct Request : public BaseService::Request
    {
        std::string data;
    };

    struct Response : public BaseService::Response
    {
        std::string data;
    };
};

class TestClass
{
    public:
        TestClass(){};
        ~TestClass(){};

        void callback_meesageA(const MessageA& msg)
        {
            std::cout << "Message A called with string: " << msg.valueA << std::endl;
        }

        void callback_messageB(const MessageB& msg)
        {
            std::cout << "Message B called with integer: " << msg.valueB << std::endl;
        }

        void callback_messageC(const MessageC& msg)
        {
            std::cout << "Message C called with float: " << msg.valueC << std::endl;
        }

        void server_callback_serviceA(const ServiceA::Request& request, ServiceA::Response& response)
        {
            std::cout << "Service A called with string: " << request.data << std::endl;
            response.data = "Response from Service A";
        }

        void client_callback_serviceA(const ServiceA::Response& response)
        {
            std::cout << "Client callback called with string: " << response.data << std::endl;
        }
};


int main() 
{
    std::shared_ptr<MessageDistributer> message_distributer = std::make_shared<MessageDistributer>();

    TestClass test_class;

    std::shared_ptr<Subscriber<MessageA>> subscriberA = std::make_shared<Subscriber<MessageA>>(Topics::TOPIC_A, 
                                                                            message_distributer, 
                                                                            std::bind(&TestClass::callback_meesageA, &test_class, std::placeholders::_1));

    std::shared_ptr<Subscriber<MessageA>> subscriberA2 = std::make_shared<Subscriber<MessageA>>(Topics::TOPIC_A, 
                                                                            message_distributer, 
                                                                            std::bind(&TestClass::callback_meesageA, &test_class, std::placeholders::_1));
                                                    
    std::shared_ptr<Subscriber<MessageB>> subscriberB = std::make_shared<Subscriber<MessageB>>(Topics::TOPIC_B, 
                                                                            message_distributer, 
                                                                            std::bind(&TestClass::callback_messageB, &test_class, std::placeholders::_1));

    std::shared_ptr<Publisher<MessageA>> publisherA = std::make_shared<Publisher<MessageA>>(Topics::TOPIC_A, message_distributer);

    std::shared_ptr<Publisher<MessageB>> publisherB = std::make_shared<Publisher<MessageB>>(Topics::TOPIC_B, message_distributer);

    std::shared_ptr<Publisher<MessageC>> publisherC = std::make_shared<Publisher<MessageC>>(Topics::TOPIC_C, message_distributer);

    MessageA msg_A = {.valueA = "Hello World"};
    MessageB msg_B = {.valueB = 100};
    MessageC msg_C = {.valueC = 3.14};
    
    publisherA->publish(msg_A);
    publisherB->publish(msg_B);
    publisherC->publish(msg_C);

    std::shared_ptr<Subscriber<MessageC>> subscriberC = std::make_shared<Subscriber<MessageC>>(Topics::TOPIC_C, 
                                                                            message_distributer, 
                                                                            std::bind(&TestClass::callback_messageC, &test_class, std::placeholders::_1));

    publisherC->publish(msg_C);

    subscriberA2.reset();

    publisherA->publish(msg_A);

    ServiceA::Request requestA;
    requestA.data = "Request to Service A";

    std::shared_ptr<Client<ServiceA>> clientA = std::make_shared<Client<ServiceA>>(Service::SERVICE_A, 
                                                                            message_distributer, 
                                                                            std::bind(&TestClass::client_callback_serviceA, &test_class, std::placeholders::_1));

    clientA->send_request(requestA);

    std::shared_ptr<Server<ServiceA>> serverA = std::make_shared<Server<ServiceA>>(Service::SERVICE_A, 
                                                                            message_distributer, 
                                                                            std::bind(&TestClass::server_callback_serviceA, &test_class, std::placeholders::_1, std::placeholders::_2));

    clientA->send_request(requestA);

    return 0;
}
*/