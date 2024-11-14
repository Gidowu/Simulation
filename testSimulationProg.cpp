#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "simulation.h"  // Ensure this header is included!
#include "queueAsArray.h"
#include "simulationImp.cpp"  // The implementation for the simulation

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

    queueType<int> waitingQueue;  // Queue to hold customer IDs or waiting times
    serverListType servers(numOfServers);  // Assuming this is defined in simulation.h

    for (clock = 1; clock <= simulationTime; clock++)
    {
        servers.updateServers(cout);  // Update the servers (prints the status)

        if (!waitingQueue.isEmptyQueue())
        {
            waitingQueue.incrementWaitingTimes();  // Increment the waiting times of all customers
        }

        // Every time between customer arrival
        if (clock % timeBetweenCustomerArrival == 0)
        {
            customerCount++;  // New customer arrives
            waitingQueue.addQueue(customerCount);  // Add the new customer to the queue
        }

        int freeServerID = servers.getFreeServerID();
        if (freeServerID != -1 && !waitingQueue.isEmptyQueue())  // Check if a server is free
        {
            int customer = waitingQueue.front();  // Get the customer at the front
            waitingQueue.deleteQueue();  // Remove the customer from the queue
            servers.setServerBusy(freeServerID, transactionTime);  // Assign server to the customer
            servedCount++;  // Increment the served count
        }
    }

    customersLeftInQueue = waitingQueue.getQueueCount();  // Get remaining customers in the queue
    int customersWithServers = servers.getNumberOfBusyServers();  // Get the number of busy servers

    cout << "Simulation results:" << endl;
    cout << "Total customers arrived: " << customerCount << endl;
    cout << "Customers served: " << servedCount << endl;
    cout << "Customers left in the queue: " << customersLeftInQueue << endl;
    cout << "Customers still being served: " << customersWithServers << endl;
}
