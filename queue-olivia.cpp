#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <sstream>

using namespace std;

class Person {
public:
    string name;
    int ticketNumber;

    Person(string n, int tn) : name(n), ticketNumber(tn) {}
};

class TicketingSystem {
private:
    queue<Person> q;
    int ticketCounter;

public:
    TicketingSystem() : ticketCounter(1) {}

    void enqueue(const string& name) {
        q.push(Person(name, ticketCounter++));
        cout << name << " added to the queue with Ticket #" << ticketCounter - 1 << endl;
        cout << "Queue size: " << q.size() << endl;
    }

    void dequeue() {
        if (!q.empty()) {
            Person p = q.front();
            cout << "Dequeue: " << p.name << " received a ticket (Ticket #" << p.ticketNumber << ")" << endl;
            q.pop();
            cout << "Queue size: " << q.size() << endl;

            if (!q.empty()) {
                Person next = q.front();
                cout << "Next in line: " << next.name << " (Ticket #" << next.ticketNumber << ")" << endl;
            } else {
                cout << "No one is in line." << endl;
            }
        } else {
            cout << "The queue is empty!" << endl;
        }
    }

    int getQueueSize() const {
        return q.size();
    }

    void checkPosition(const string& identifier) {
        queue<Person> tempQueue = q;
        int position = 1;

        while (!tempQueue.empty()) {
            Person p = tempQueue.front();
            tempQueue.pop();

            if (p.name == identifier || to_string(p.ticketNumber) == identifier) {
                cout << p.name << " is currently at position " << position << " in the queue." << endl;
                return;
            }
            position++;
        }

        cout << "No person found with the name or ticket number: " << identifier << endl;
    }

    void showQueue() const {
        queue<Person> tempQueue = q;
        cout << "Current queue: ";
        if (tempQueue.empty()) {
            cout << "No one in the queue." << endl;
            return;
        }
        while (!tempQueue.empty()) {
            Person p = tempQueue.front();
            tempQueue.pop();
            cout << p.name << " (Ticket #" << p.ticketNumber << ") ";
        }
        cout << endl;
    }
};

void ticketDistribution(TicketingSystem& system, atomic<bool>& running) {
    while (running) {
        this_thread::sleep_for(chrono::minutes(1));
        system.dequeue();
    }
}

int main() {
    TicketingSystem system;
    int choice;
    string name;

    atomic<bool> running(true);

    cout << "Welcome to Olivia Rodrigo's Concert Ticketing System!" << endl;

    thread distributionThread(ticketDistribution, ref(system), ref(running));

    while (true) {
        cout << "\n1. Enqueue a person" << endl;
        cout << "2. Check your position in the queue" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the name: ";
                cin >> name;
                system.enqueue(name);
                break;

            case 2:
                cout << "Enter your name or ticket number: ";
                cin >> name;
                system.checkPosition(name);
                system.showQueue();
                break;

            case 3:
                running = false;
                cout << "Exiting..." << endl;
                distributionThread.join();
                return 0;

            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}