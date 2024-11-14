#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "simulation.h"
#include "queueAsArray.h"

using namespace std;

void setSimulationParameters(int& sTime, int& numOfServers,
                             int& transTime,
                             int& tBetweenCArrival);
void runSimulation();

int main()
{
    runSimulation();
    return 0;
}

void setSimulationParameters(int& sTime, int& numOfServers,
                             int& transTime,
                             int& tBetweenCArrival)
{
    cout << "Enter the simulation time: ";
    cin >> sTime;
    cout << endl;
    cout << "Enter the number of servers: ";
    cin >> numOfServers;
    cout << endl;
    cout << "Enter the transaction time: ";
    cin >> transTime;
    cout << endl;
    cout << "Enter the time between customer arrivals: ";
    cin >> tBetweenCArrival;
    cout << endl;
}

void runSimulation()
{
    int simulationTime, numOfServers, transactionTime, timeBetweenCustomerArrival;
    setSimulationParameters(simulationTime, numOfServers, transactionTime, timeBetweenCustomerArrival);

    int clock = 0;
    int customerCount = 0;
    int servedCount = 0;
    int customersLeftInQueue = 0;

    queueType<int> waitingQueue;  
    serverListType servers(numOfServers);

    for (clock = 1; clock <= simulationTime; clock++)
    {
        servers.updateServers(cout);

        if (!waitingQueue.isEmptyQueue())
        {
            waitingQueue.incrementWaitingTimes();
        }

        if (clock % timeBetweenCustomerArrival == 0)
        {
            customerCount++;
            waitingQueue.addQueue(customerCount);
        }

        int freeServerID = servers.getFreeServerID();
        if (freeServerID != -1 && !waitingQueue.isEmptyQueue())
        {
            waitingQueue.deleteQueue();
            servers.setServerBusy(freeServerID, transactionTime);
            servedCount++;
        }
    }

    customersLeftInQueue = waitingQueue.getQueueCount();
    int customersWithServers = servers.getNumberOfBusyServers();

    cout << "Simulation results:" << endl;
    cout << "Total customers arrived: " << customerCount << endl;
    cout << "Customers served: " << servedCount << endl;
    cout << "Customers left in the queue: " << customersLeftInQueue << endl;
    cout << "Customers still being served: " << customersWithServers << endl;
}
