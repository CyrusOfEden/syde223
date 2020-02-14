#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include "drones_manager.hpp"

using namespace std;

bool operator==(const DronesManager::DroneRecord &lhs, const DronesManager::DroneRecord &rhs) {
    return lhs.droneID == rhs.droneID && lhs.range == rhs.range && lhs.yearBought == rhs.yearBought &&
           lhs.droneType == rhs.droneType && lhs.manufacturer == rhs.manufacturer &&
           lhs.description == rhs.description && lhs.batteryType == rhs.batteryType;
}

unsigned int DronesManager::get_size() const {
    return size;
}

bool DronesManager::empty() const {
    return size == 0;
}

void DronesManager::replace_items(const vector<DroneRecord> &items) {
    first = nullptr;
    last = nullptr;
    size = 0;
    for (const auto &drone : items) {
        insert_back(drone);
    }
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    if (empty()) {
        return DroneRecord(0);
    }
    if (index == 0) {
        return *first;
    }
    if (size <= index) {
        return *last;
    }
    DroneRecord *cursor = first;
    while (index > 0) {
        cursor = cursor->next;
        index -= 1;
    }
    return *cursor;
}

unsigned int DronesManager::search(const DroneRecord value) const {
    // Look for the DroneRecord and return the index if found
    auto cursor = first;
    for (int i = 0; i < size; i += 1) {
        if (*cursor == value) {
            return i;
        }
        cursor = cursor->next;
    }
    // If not found
    return size;
}

void DronesManager::print() const {
    for (auto cursor = first; cursor != nullptr; cursor = cursor->next) {
        cursor->print();
        cout << "\n";
    }
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
    if (index > size) {
        return false;
    }
    if (index == size) {
        return insert_back(value);
    }
    if (index == 0) {
        return insert_front(value);
    }
    auto *item = new DroneRecord(move(value));
    DroneRecord *prev = first;
    DroneRecord *next = prev->next;
    while (index -= 1) {
        prev = next;
        next = next->next;
    }
    prev->next = item;
    next->prev = item;
    item->prev = prev;
    item->next = next;
    size += 1;
    return true;
}

bool DronesManager::insert_front(DroneRecord value) {
    auto *item = new DroneRecord(move(value));
    if (empty()) {
        first = item;
        last = item;
        size = 1;
        return true;
    }
    item->prev = nullptr;
    item->next = first;
    first->prev = item;
    first = item;
    size += 1;
    return true;
}

bool DronesManager::insert_back(DroneRecord value) {
    auto *item = new DroneRecord(move(value));
    if (empty()) {
        first = item;
        last = item;
        size = 1;
        return true;
    }
    item->next = nullptr;
    item->prev = last;
    last->next = item;
    last = item;
    size += 1;
    return true;
}

bool DronesManager::remove(unsigned int index) {
    if (index >= size) {
        return false;
    }
    auto cursor = first; // the node before the one we want to remove
    for (int i = 1; i < index; i += 1) {
        cursor = cursor->next;
    }
    cursor->next = nullptr;
    size -= 1;
    return true;
}

bool DronesManager::remove_front() {
    if (empty()) {
        return false;
    }
    if (size == 1) {
        first = nullptr;
        last = nullptr;
        size = 0;
        return true;
    }
    first = first->next;
    first->prev = nullptr;
    size -= 1;
    return true;
}

bool DronesManager::remove_back() {
    if (empty()) {
        return false;
    }
    if (size == 1) {
        first = nullptr;
        last = nullptr;
        size = 0;
        return true;
    }
    last = last->prev;
    last->next = nullptr;
    size -= 1;
    return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
    if (index > size) {
        return false;
    }

    auto *item = new DroneRecord(std::move(value));

    if (index == 0) {
        item->next = first->next;
        first = item;
        first->next->prev = first;
        return true;
    }
    if (index == size - 1) {
        item->prev = last->prev;
        last = item;
        last->prev->next = last;
        return true;
    }

    DroneRecord *current = first;
    DroneRecord *next = current->next;

    for (int i = 0; i < index; i += 1) {
        current = next;
        next = current->next;
    }

    item->next = next;
    item->prev = current->prev;
    item->prev->next = item;

    return true;
}

bool DronesManager::reverse_list() {
    if (size < 2) {
        return true;
    }

    vector<DroneRecord> items;
    for (auto cursor = first; cursor != nullptr; cursor = cursor->next) {
        items.push_back(*cursor);
    }

    reverse(items.begin(), items.end());
    replace_items(items);

    return true;
}

bool DronesManagerSorted::is_sorted_asc() const {
    for (auto cursor = first; cursor != nullptr; cursor = cursor->next) {
        auto nextDrone = cursor->next;
        if (nextDrone == nullptr) {
            return true;
        }
        if (cursor->droneID > nextDrone->droneID) {
            return false;
        }
    }
    return true;
}

bool DronesManagerSorted::is_sorted_desc() const {
    for (auto cursor = first; cursor != nullptr; cursor = cursor->next) {
        auto nextDrone = cursor->next;
        if (nextDrone == nullptr) {
            return true;
        }
        if (cursor->droneID < nextDrone->droneID) {
            return false;
        }
    }
    return true;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord value) {
    if (empty() || (size == 1 && value.droneID < first->droneID)) {
        return insert_front(value);
    }

    auto *item = new DroneRecord(move(value));

    for (auto cursor = first; cursor != nullptr; cursor = cursor->next) {
        // TODO
    }

    return false;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord value) {
    if (empty() || (size == 1 && value.droneID > first->droneID)) {
        return insert_front(value);
    }

    auto *item = new DroneRecord(move(value));

    for (auto cursor = first; cursor != nullptr; cursor = cursor->next) {
        // TODO
    }

    return false;
}

void DronesManagerSorted::sort_asc() {
    vector<DroneRecord> drones;
    for (auto cursor = first; cursor != nullptr; cursor = cursor->next) {
        drones.push_back(*cursor);
    }
    sort(drones.begin(), drones.end(), [](const DroneRecord& a, const DroneRecord& b) {
        return a.droneID < b.droneID;
    });
    replace_items(drones);
}

void DronesManagerSorted::sort_desc() {
    vector<DroneRecord> drones;
    for (auto cursor = first; cursor != nullptr; cursor = cursor->next) {
        drones.push_back(*cursor);
    }
    sort(drones.begin(), drones.end(), [](const DroneRecord& a, const DroneRecord& b) {
        return a.droneID > b.droneID;
    });
    replace_items(drones);
}
