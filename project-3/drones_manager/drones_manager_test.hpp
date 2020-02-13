#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty())
		ASSERT_TRUE(manager.first == nullptr)
		ASSERT_TRUE(manager.last == nullptr)
	    return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));

		ASSERT_TRUE(manager1.first != nullptr && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != nullptr && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == nullptr && manager1.last->next == nullptr)
		ASSERT_TRUE(manager2.first->prev == nullptr && manager2.last->next == nullptr)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))		
	    return true;
	}
	
	// PURPOSE: select() and search() work properly
	bool test3() {
		DronesManager m;
        DronesManager::DroneRecord nullRecord(0);
		DronesManager::DroneRecord r(100);

	    ASSERT_TRUE(m.select(0) == nullRecord);
	    m.insert(r, 0);
	    m.insert(r, 1);
	    ASSERT_TRUE(m.get_size() == 2);
	    ASSERT_TRUE(m.select(0) == r);
	    ASSERT_TRUE(m.select(2) == r);
	    return true;
	}
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
		DronesManager m;
		DronesManager::DroneRecord r(100);

		ASSERT_TRUE(m.insert_front(r));
		ASSERT_TRUE(m.get_size() == 1);

		ASSERT_TRUE(m.remove_front());
		ASSERT_TRUE(m.empty());

		ASSERT_TRUE(m.first == nullptr && m.last == nullptr);

		ASSERT_TRUE(m.insert_front(r));
		ASSERT_TRUE(m.get_size() == 1);

		ASSERT_TRUE(m.remove_back());
		ASSERT_TRUE(m.empty());

		ASSERT_TRUE(m.first == nullptr && m.last == nullptr);
		return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
		DronesManager m;
		DronesManager::DroneRecord r2(100);
		DronesManager::DroneRecord d2(101);
		DronesManager::DroneRecord c2(102);

		m.insert_back(r2);
		m.insert_back(d2);
		m.insert_back(c2);

		ASSERT_TRUE(m.select(0) == r2);

		ASSERT_TRUE(m.replace(0, d2));
		ASSERT_TRUE(m.select(0) == d2);

		ASSERT_TRUE(m.replace(1, r2));
		ASSERT_TRUE(m.select(1) == r2);

//		ASSERT_TRUE(m.reverse_list());
//		ASSERT_TRUE(m.select(0) == c2);
//		ASSERT_TRUE(m.select(1) == r2);
//		ASSERT_TRUE(m.select(2) == d2);

		return true;
	}
	
	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
		DronesManager m;
		DronesManager::DroneRecord r2(100);
		DronesManager::DroneRecord d2(101);

		ASSERT_TRUE(m.insert_front(d2));
		ASSERT_TRUE(m.get_size() == 1);
		ASSERT_TRUE(m.insert_front(r2));
		ASSERT_TRUE(m.get_size() == 2);
		ASSERT_TRUE(m.select(0) == r2);
		ASSERT_TRUE(m.select(1) == d2);

		return true;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
		DronesManager m;
		DronesManager::DroneRecord r2(100);
		DronesManager::DroneRecord d2(101);

		ASSERT_TRUE(m.insert(r2, 0));
		ASSERT_TRUE(m.insert(r2, 1));
		ASSERT_TRUE(m.get_size() == 2);
		ASSERT_TRUE(m.insert(d2, 2));
		ASSERT_TRUE(m.get_size() == 3);

		return true;
	}
	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
	    return false;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
		return false;
	}    
	    	
	// PURPOSE: inserts into an unsorted list, then sort the list
	bool test10() {
	   return false;
	}  
	
	// PURPOSE: insert and remove into sorted manager in ascending order
	bool test11() {
	   return false;
	}
	
	// PURPOSE: insert and remove into sorted manager in descending order
	bool test12() {
	   return false;
	}  
};

#endif
