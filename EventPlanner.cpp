#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Event {
protected:
    static int totalEvents; 
    string name;
    string date;
    string time;
    string location;
    string description;

public:
    Event(const string& name, const string& date, const string& time, const string& location, const string& description)
        : name(name), date(date), time(time), location(location), description(description) {
        totalEvents++;  
    }

    virtual ~Event() {
        totalEvents--;
    }

    virtual void display() const {
        cout << "Event: " << this->name << "\nDate: " << this->date << "\nTime: " << this->time
             << "\nLocation: " << this->location << "\nDescription: " << this->description << endl;
    }

    string getName() const { return this->name; }
    void setName(const string& name) { this->name = name; }

    static int getTotalEvents() { return totalEvents; }
};

int Event::totalEvents = 0;  
class BusinessEvent : public Event {
private:
    static int totalBusinessEvents;
    string organizer;

public:
    BusinessEvent(const string& name, const string& date, const string& time, const string& location, const string& description, const string& organizer)
        : Event(name, date, time, location, description), organizer(organizer) {
        totalBusinessEvents++;  
    }

    ~BusinessEvent() {
        totalBusinessEvents--;
    }

    void display() const override {
        cout << "Business Event: " << this->name << "\nDate: " << this->date << "\nTime: " << this->time
             << "\nLocation: " << this->location << "\nDescription: " << this->description
             << "\nOrganizer: " << this->organizer << endl;
    }

    static int getTotalBusinessEvents() { return totalBusinessEvents; }
};

int BusinessEvent::totalBusinessEvents = 0;  

class EventPlanner {
private:
    vector<Event*> events;

public:
    ~EventPlanner() {
        for (auto& event : this->events) {
            delete event;
        }
        this->events.clear();
    }

    void addEvent(Event* event) {
        this->events.push_back(event);
    }

    void displayEvents() const {
        for (const auto& event : this->events) {
            event->display();
            cout << "-------------------------\n";
        }
    }

    void createEvent() {
        string name, date, time, location, description, organizer;
        char eventType;

        cout << "Enter event type (B for Business, O for Other): ";
        cin >> eventType;

        cout << "Enter event name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter event date (YYYY-MM-DD): ";
        getline(cin, date);

        cout << "Enter event time: ";
        getline(cin, time);

        cout << "Enter event location: ";
        getline(cin, location);

        cout << "Enter event description: ";
        getline(cin, description);

        if (eventType == 'B' || eventType == 'b') {
            cout << "Enter organizer name: ";
            getline(cin, organizer);
            this->addEvent(new BusinessEvent(name, date, time, location, description, organizer));
        } else {
            this->addEvent(new Event(name, date, time, location, description));
        }

        cout << "Event added successfully!\n";
    }

    void eraseEvent(const string& eventName) {
        auto it = remove_if(this->events.begin(), this->events.end(), [&](Event* event) {
            if (event->getName() == eventName) {
                delete event;  
                return true;   
            }
            return false;
        });

        if (it != this->events.end()) {
            this->events.erase(it, this->events.end());
            cout << "Event \"" << eventName << "\" deleted successfully.\n";
        } else {
            cout << "Event \"" << eventName << "\" not found.\n";
        }
    }

    void displayStatistics() const {
        cout << "Total Events: " << Event::getTotalEvents() << endl;
        cout << "Total Business Events: " << BusinessEvent::getTotalBusinessEvents() << endl;
    }
};

int main() {
    EventPlanner* planner = new EventPlanner();
    char choice;
    string eventName;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Event\n";
        cout << "2. View Events\n";
        cout << "3. Delete Event\n";
        cout << "4. Display Statistics\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                planner->createEvent();
                break;
            case '2':
                cout << "\nEvents:\n";
                planner->displayEvents();
                break;
            case '3':
                cout << "Enter the name of the event to delete: ";
                cin.ignore();
                getline(cin, eventName);
                planner->eraseEvent(eventName);
                break;
            case '4':
                planner->displayStatistics();
                break;
            case '5':
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != '5');

    delete planner;
    return 0;
}
