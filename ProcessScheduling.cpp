#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

int main() {
    cout<< "----Shortest Job Process Example Implenetation---- \n";
    int numProcesses;
    cout << "Please enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);
    vector<int> completionTime(numProcesses);
    vector<int> waitTime(numProcesses);

    cout << "\nEnter arrival and burst time for each process:\n";
    for (int i = 0; i < numProcesses; ++i) {
        cout << "Process " << i + 1 << " arrival time: ";
        cin >> processes[i].arrivalTime;
        cout << "Process " << i + 1 << " burst time: ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].id = i + 1;
    }

    int currentTime = 0;
    int completedProcesses = 0;
    cout << "\nTime-Line is as follows (Vertical View):\n\n";
    while (completedProcesses < numProcesses) {
        int selectedProcess = -1;
        for (int i = 0; i < numProcesses; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (selectedProcess == -1 || processes[i].remainingTime < processes[selectedProcess].remainingTime) {
                    selectedProcess = i;
                }
            }
        }
        if (selectedProcess == -1) {
            cout << currentTime << " ----------- Idle\n";
            currentTime++;
        } else {
            cout << currentTime << " ----------- P" << processes[selectedProcess].id << endl;
            processes[selectedProcess].remainingTime--;
            if (processes[selectedProcess].remainingTime == 0) {
                completionTime[selectedProcess] = currentTime + 1;
                waitTime[selectedProcess] = completionTime[selectedProcess] - processes[selectedProcess].arrivalTime - processes[selectedProcess].burstTime;
                completedProcesses++;
            }
            currentTime++;
        }
    }

    cout << currentTime << " -----------\n";
    cout << "\nTable of Shortest Job Process:\n";
    cout << "\nProcess\tArrival\tCompletion\tWait\n";
    for (int i = 0; i < numProcesses; ++i) {
        cout << "P" << processes[i].id << "\t" << processes[i].arrivalTime << "\t" << completionTime[i] << "\t\t" << waitTime[i] << endl;
    }

    double averageWaitTime = 0;
    for (int i = 0; i < numProcesses; ++i) {
        averageWaitTime += waitTime[i];
    }
    averageWaitTime /= numProcesses;
    cout << "\nAverage Wait Time = " << averageWaitTime << endl;

    return 0;
}