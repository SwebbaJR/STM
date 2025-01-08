#ifndef MESSAGE_SYSTEM__MESSAGE_DISTRIBUTOR_PRIMS_HPP
#define MESSAGE_SYSTEM__MESSAGE_DISTRIBUTOR_PRIMS_HPP

enum class Topics : std::size_t
{
    TOPIC_A = 0,
    NUMBER_OF_TOPICS
};

enum class Service : std::size_t
{
    SERVICE_A = 0,
    NUMBER_OF_SERVICES
};

struct BaseMsg{};

struct BaseService
{
    struct Request
    {

    };
    struct Response
    {

    };
};


#endif // MESSAGE_SYSTEM__MESSAGE_DISTRIBUTOR_PRIMS_HPP