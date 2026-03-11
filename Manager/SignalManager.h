#pragma once
#include "Interface.h"
#include <vector>

class SignalManager
{
public:
    SignalManager();

    void AddToMailer(IStatus* sent);
    void AddToSubscibed(IApply* recieved);

    void Update();


    std::vector<IStatus*> senders;
    std::vector<IApply*> recievers;

    std::vector<int> sendersChannels;
    std::vector<int> recieversChannels;

};