#include "node_system/node.hpp"

Node::Node(std::string node_name, std::weak_ptr<MessageDistributer> message_distributer) :
    message_distributer(message_distributer),
    node_name(node_name)
{

}

Node::~Node()
{

}

