#include "channel.hpp"

Channel::Channel(const std::string& name, Clients* creator) :
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

bool Channel::hasClient(const Clients* client) const
{
    for (const auto& c : clients_) {
        if (c == client) {
            return true;
        }
    }
    return false;
}

bool Channel::hasOperator(const Clients* client) const {
    return operators_.count(const_cast<Clients*>(client)) > 0;
}


bool Channel::addClient(Clients* client)
{
    if (isFull() || hasClient(client)) {
        return false;
    }
    clients_.push_back(client);
    return true;
}

bool Channel::removeClient(Clients* client)
{
    for (auto it = clients_.begin(); it != clients_.end(); ++it) {
        if (*it == client) {
            clients_.erase(it);
            return true;
        }
    }
    return false;
}

bool Channel::makeOperator(Clients* client)
{
    if (!hasClient(client) || hasOperator(client)) {
        return false;
    }
    operators_.insert(client);
    return true;
}

bool Channel::removeOperator(Clients* client)
{
    if (!hasOperator(client)) {
        return false;
    }
    operators_.erase(client);
    return true;
}

bool Channel::kickClient(Clients* client)
{
    if (!hasClient(client) || hasOperator(client)) {
        return false;
    }
    removeClient(client);
    return true;
}

bool Channel::joinChannel(Clients* client)
{
    if (isFull() || hasClient(client)) {
        return false;
    }
    clients_.push_back(client);
    if (clients_.size() == 1) {
        operators_.insert(client);
    }
    return true;
}


std::string Channel::getClientList() const
{
    std::string list;
    for (const auto& c : clients_) {
        list += c->getnickname() + " ";
    }
    return list;
}

std::string Channel::getOperatorList() const
{
    std::string list;
    for (const auto& op : operators_) {
        list += op->getnickname() + " ";
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
