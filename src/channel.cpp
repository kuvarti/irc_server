#include "channel.hpp"

Channel::Channel(const std::string& name, Client* creator) :
    name_(name),
    creator_(creator),
    maxSize_(10)
{
    operators_.insert(creator);
}

std::string Channel::getName() const
{
    return name_;
}

bool Channel::hasClient(const Client* client) const
{
    for (const auto& c : clients_) {
        if (c == client) {
            return true;
        }
    }
    return false;
}

bool Channel::hasOperator(const Client* client) const
{
    return operators_.count(client) > 0;
}

bool Channel::addClient(Client* client)
{
    if (isFull() || hasClient(client)) {
        return false;
    }
    clients_.push_back(client);
    return true;
}

bool Channel::removeClient(Client* client)
{
    for (auto it = clients_.begin(); it != clients_.end(); ++it) {
        if (*it == client) {
            clients_.erase(it);
            return true;
        }
    }
    return false;
}

bool Channel::makeOperator(Client* client)
{
    if (!hasClient(client) || hasOperator(client)) {
        return false;
    }
    operators_.insert(client);
    return true;
}

bool Channel::removeOperator(Client* client)
{
    if (!hasOperator(client)) {
        return false;
    }
    operators_.erase(client);
    return true;
}

std::string Channel::getClientList() const
{
    std::string list;
    for (const auto& c : clients_) {
        list += c->getNickname() + " ";
    }
    return list;
}

std::string Channel::getOperatorList() const
{
    std::string list;
    for (const auto& op : operators_) {
        list += op->getNickname() + " ";
    }
    return list;
}

bool Channel::isEmpty() const
{
    return clients_.empty();
}

bool Channel::isFull() const
{
    return clients_.size() == maxSize_;
}

int Channel::getSize() const
{
    return clients_.size();
}

int Channel::getMaxSize() const
{
    return maxSize_;
}
