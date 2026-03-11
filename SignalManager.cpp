#include "SignalManager.h"

SignalManager::SignalManager()
{

}

void SignalManager::AddToMailer(IStatus* sent)
{
    sendersChannels.push_back(sent->channel);
    senders.push_back(sent);    
}

void SignalManager::AddToSubscibed(IApply* recieved)
{
    recieversChannels.push_back(recieved->channel);
    recievers.push_back(recieved);
}

void SignalManager::Update()
{
    for(int channelS : sendersChannels)
    {
        for(int channelR : recieversChannels)
        {
            if(channelS != channelR)
            {
                return;
            }

            recievers.at(channelR)->SetPosition(senders.at(channelS)->GetPosition());
            recievers.at(channelR)->SetValues(senders.at(channelS)->GetValues());           

        }
    }   
}