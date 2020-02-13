#ifndef DRONES_MANAGER_HPP
#define DRONES_MANAGER_HPP

#include <string>

using namespace std;

// PURPOSE: Models a container that stores individual drone records
class DronesManager {
protected:
    struct DroneRecord {
        // CONSTRUCTORS
        // empty/default constructor
        DroneRecord() : droneID(0), range(0), yearBought(0), prev(nullptr), next(nullptr) {};

        // droneID-only constructor
        DroneRecord(unsigned int newDroneID) : droneID(newDroneID), range(0), yearBought(0), prev(nullptr),
                                               next(nullptr) {};

        // full parametric constructor
        DroneRecord(unsigned int newDroneID, unsigned int newRange,
                    unsigned int newYearBought, string newDroneType,
                    string newManufacturer, string newDescription, string newBatteryType) :
                droneID(newDroneID), range(newRange), yearBought(newYearBought),
                droneType(newDroneType), manufacturer(newManufacturer), description(newDescription),
                batteryType(newBatteryType),
                prev(nullptr), next(nullptr) {}

        // drone ID, range, and year bought stored as unsigned ints
        unsigned int droneID, range, yearBought;
        // drone type, manufacturer, description, and battery type stored as strings
        string droneType, manufacturer, description, batteryType;

        // pointers to the prev and next nodes
        DroneRecord *prev;
        DroneRecord *next;

        void print() const {
            printf("DroneRecord{droneID: %d, range: %d, yearBought: %d, droneType: '%s', manufacturer: '%s', description: '%s', batterType: '%s'}",
                   droneID, range, yearBought, droneType.c_str(), manufacturer.c_str(), description.c_str(),
                   batteryType.c_str());
        };
    };

    // a pointer to the first node in the list
    DroneRecord *first{nullptr};
    // a pointer to the last node in the list
    DroneRecord *last{nullptr};
    // the number of elements in the list
    unsigned int size{0};

    void replace_items(const vector<DroneRecord>& drones);
public:

    // PURPOSE: Comparison operator to compare two DroneRecord instances
    friend bool operator==(const DronesManager::DroneRecord &lhs, const DronesManager::DroneRecord &rhs);

    // PURPOSE: Setup DronesManagerTest as friend so tests have access to private variables
    friend class DronesManagerTest;

    // ACCESSORS
    // PURPOSE: Returns the number of elements in the list
    [[nodiscard]] unsigned int get_size() const;

    // PURPOSE: Checks if the list is empty; returns true if the list is empty, false otherwise
    [[nodiscard]] bool empty() const;

    // PURPOSE: Returns the value at the given index in the list
    // if index is invalid, returns last element; if the list is empty, returns DroneRecord(0)
    [[nodiscard]] DroneRecord select(unsigned int index) const;

    // PURPOSE: Searches for the given value, and returns the index of this value if found
    // if not found, returns the size of the list; if the list is empty, returns 0
    [[nodiscard]] unsigned int search(const DroneRecord value) const;

    // PURPOSE: Prints all the elements in the list to the console
    void print() const;

    // MUTATORS
    // PURPOSE: Inserts a value into the list at a given index; the list is not sorted
    // if the index is invalid, insertion is rejected
    bool insert(DroneRecord val, unsigned int index);

    // PURPOSE: Inserts a value at the beginning of the list; the list is not sorted
    bool insert_front(DroneRecord val);

    // PURPOSE: Inserts a value at the end of the list; the list is not sorted
    bool insert_back(DroneRecord val);

    // PURPOSE: Deletes a value from the list at the given index
    bool remove(unsigned int index);

    // PURPOSE: Deletes a value from the beginning of the list
    bool remove_front();

    // PURPOSE: Deletes a value at the end of the list
    bool remove_back();

    // PURPOSE: Replaces value at the given index with the given value; the list is not sorted
    // if the index is invalid, replacement is rejected
    bool replace(unsigned int index, DroneRecord val);

    // PURPOSE: Reverses the linked list
    bool reverse_list();
};

// PURPOSE: Allows record storage in sorted ascending or descending order based on drone ID value
class DronesManagerSorted : public DronesManager {
public:
    // ACCESSORS
    // PURPOSE: Returns true if the list is sorted in ascending (non-descending) order
    [[nodiscard]] bool is_sorted_asc() const;

    // PURPOSE: Returns true if the list is sorted in descending (non-ascending) order
    [[nodiscard]] bool is_sorted_desc() const;

    // MUTATORS
    // PURPOSE: Inserts a value so that the list remains sorted in ascending order
    // if the list is not sorted in appropriate order, insertion is rejected
    bool insert_sorted_asc(DroneRecord val);

    // PURPOSE: Inserts a value so that the list remains sorted in descending order
    // if the list is not sorted in appropriate order, insertion is rejected
    bool insert_sorted_desc(DroneRecord val);

    // PURPOSE: Sorts the list into ascending (non-descending) order
    void sort_asc();

    // PURPOSE: Sorts the list into descending (non-ascending) order
    void sort_desc();
};

#endif
