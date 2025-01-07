/*
#include "node_system/node.hpp"

struct MessageA : BaseMsg
{
    std::string valueA;
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

struct NonBaseMsg
{
    std::string value;
};

struct NonBaseService
{
    struct Request
    {
        std::string data;
    };

    struct Response
    {
        std::string data;
    };
};

class TestNode : private Node
{
public:
    TestNode(std::weak_ptr<MessageDistributer> message_distributer) :
        Node("Test node", message_distributer)
    {
        subscriberA = create_subscriber<MessageA>(Topics::TOPIC_A, std::bind(&TestNode::callback_meesageA, this, std::placeholders::_1));
        publisherA = create_publisher<MessageA>(Topics::TOPIC_A);
        serverA = create_server<ServiceA>(Service::SERVICE_A, std::bind(&TestNode::server_callback_serviceA, this, std::placeholders::_1, std::placeholders::_2));
        clientA = create_client<ServiceA>(Service::SERVICE_A, std::bind(&TestNode::client_callback_serviceA, this, std::placeholders::_1));

        // Cause a static assert to fail
        //std::shared_ptr<Subscriber<NonBaseMsg>> subscriberB = create_subscriber<NonBaseMsg>(Topics::TOPIC_A, [](const NonBaseMsg& msg)
        //{
        //    std::cout << "NonBaseMsg subscriber called with string: " << msg.value << std::endl;
        //});

        // Cause a static assert to fail
        //std::shared_ptr<Client<NonBaseService>> clientB = create_client<NonBaseService>(Service::SERVICE_A, [](const NonBaseService::Response& response)
        //{
        //    std::cout << "NonBaseService client callback called with string: " << response.data << std::endl;
        //});
    }
        
    void test_publish(MessageA msg)
    {
        publisherA->publish(msg);
    }

    void test_send_request(ServiceA::Request request)
    {
        clientA->send_request(request);
    }

private:
    std::shared_ptr<Subscriber<MessageA>> subscriberA;
    std::shared_ptr<Publisher<MessageA>> publisherA;
    std::shared_ptr<Server<ServiceA>> serverA;
    std::shared_ptr<Client<ServiceA>> clientA;

    void callback_meesageA(const MessageA& msg)
    {
        std::cout << "Message A called with string: " << msg.valueA << std::endl;
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

    std::shared_ptr<TestNode> test_node = std::make_shared<TestNode>(message_distributer);

    MessageA msg;

    msg.valueA = "Hello World";

    test_node->test_publish(msg);

    ServiceA::Request request;

    request.data = "Request to Service A";

    test_node->test_send_request(request);

    return 0;
}
*/