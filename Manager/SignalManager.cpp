#include "SignalManager.h"

SignalManager::SignalManager()
{
}

void SignalManager::AddToMailer(IStatus *sent)
{
    sendersChannels.push_back(sent->channel);
    senders.push_back(sent);
}

void SignalManager::AddToSubscibed(IApply *recieved)
{
    recieversChannels.push_back(recieved->channel);
    recievers.push_back(recieved);
}

void SignalManager::Update()
{

    for(size_t i = 0; i < recievers.size(); i++)
    {
        for(size_t j = 0; j < senders.size(); j++)
        {
            if(recieversChannels.at(i) == sendersChannels.at(j))
            {
                recievers.at(i)->SetPosition(senders.at(j)->GetPosition());
                recievers.at(i)->SetValues(senders.at(j)->GetValues());
            }
        }
    }

}