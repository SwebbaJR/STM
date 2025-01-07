#ifndef MESSAGE_SYSTEM__MESSAGE_DISTRIBUTOR_PRIMS_HPP
#define MESSAGE_SYSTEM__MESSAGE_DISTRIBUTOR_PRIMS_HPP

enum class Topics : uint32_t
{
    TOPIC_A = 0
};

enum class Service : uint32_t
{
    SERVICE_A = 0
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