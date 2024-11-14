#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "simulation.h"
#include "queueAsArray.h"
using namespace std;
 
//*************** customerType ************
void customerType::setCustomerInfo(int customerNum, int arrTime, int transTime) {
    customerNumber = customerNum;
    arrivalTime = arrTime;
    transactionTime = transTime;
}

void customerType::setWaitingTime(int time) {
    waitingTime = time;
}

int customerType::getArrivalTime() const {
    return arrivalTime;
}

int customerType::getTransactionTime() const {
    return transactionTime;
}

int customerType::getCustomerNumber() const {
    return customerNumber;
}


//************** serverListType ***********
serverListType::serverListType(int num)
{
    numOfServers = num;
    servers = new serverType[num];
}
serverListType::~serverListType()
{
    delete [] servers;
}
int serverListType::getFreeServerID() const
{
    int serverID = -1;
    for (int i = 0; i < numOfServers; i++)
        if (servers[i].isFree())
        {
            serverID = i;
            break;
        }
    return serverID;
}
int serverListType::getNumberOfBusyServers() const
{
    int busyServers = 0;
    for (int i = 0; i < numOfServers; i++)
        if (!servers[i].isFree())
            busyServers++;
    return busyServers;
}
void serverListType::setServerBusy(int serverID, 
                                   customerType cCustomer, 
                                   int tTime)
{
    servers[serverID].setBusy();
    servers[serverID].setTransactionTime(tTime);
    servers[serverID].setCurrentCustomer(cCustomer);
}
void serverListType::setServerBusy(int serverID, 
                                   customerType cCustomer)
{
    int time;
    time = cCustomer.getTransactionTime();
    servers[serverID].setBusy();
    servers[serverID].setTransactionTime(time);
    servers[serverID].setCurrentCustomer(cCustomer);
}
void serverListType::updateServers(ostream& outF)
{
   for (int i = 0; i < numOfServers; i++)
       if (!servers[i].isFree())
       {
          servers[i].decreaseTransactionTime();
          if (servers[i].getRemainingTransactionTime() == 0)
          {
              outF << "From server number " << (i + 1) 
                   << " customer number "
                   << servers[i].getCurrentCustomerNumber()
                   << "\n     departed at clock unit "
                   << servers[i].getCurrentCustomerArrivalTime()
                   + servers[i].getCurrentCustomerWaitingTime() 
                   + servers[i].getCurrentCustomerTransactionTime()
                   << endl;
              servers[i].setFree();
          }
       }
}
//*************** waitQueue ************
waitingCustomerQueueType::waitingCustomerQueueType(int size)
                          :queueType<customerType>(size)
{
}
void waitingCustomerQueueType::updateWaitingQueue()
{
    customerType cust;
    cust.setWaitingTime(-1);  
    int wTime = 0;
	  
	addQueue(cust);
    while (wTime != -1)
    {
        cust = front();
        deleteQueue();
        wTime = cust.getWaitingTime();
        if (wTime == -1)
            break;
        cust.incrementWaitingTime();
        addQueue(cust);
	}
}
void runSimulation(int simulationTime, int transactionTimeLimit) {
    std::queue<customerType> customerQueue;
    serverType server;
    int currentTime = 0;

    while (currentTime < simulationTime) {
        // Example logic to simulate new customer arrivals and server transaction
        if (server.isFree() && !customerQueue.empty()) {
            server.setCurrentCustomer(customerQueue.front());
            customerQueue.pop();
        }

        // Process server's remaining transaction time
        if (!server.isFree()) {
            server.getRemainingTransactionTime()--;
            if (server.getRemainingTransactionTime() == 0) {
                server.setFree();
            }
        }

        currentTime++;
    }
}