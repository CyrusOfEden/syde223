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
        DronesManager::DroneRecord r2(100);
        DronesManager::DroneRecord d2(101);
        DronesManager::DroneRecord nullRecord(0);

	    ASSERT_TRUE(m.select(0) == nullRecord);

	    m.insert_back(r2);
	    m.insert_back(d2);
	    m.insert_back(r2);
        m.insert_back(d2);

	    ASSERT_TRUE(m.get_size() == 4);
	    ASSERT_TRUE(m.select(0) == r2);
	    ASSERT_TRUE(m.select(m.get_size() + 10) == d2);
        ASSERT_TRUE(m.search(r2) == 0);
	    ASSERT_TRUE(m.search(d2) == 1);

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

		ASSERT_TRUE(m.reverse_list());
		ASSERT_TRUE(m.select(0) == c2);
		ASSERT_TRUE(m.select(1) == r2);
		ASSERT_TRUE(m.select(2) == d2);

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
	    DronesManager m;
	    DronesManager::DroneRecord r2(100);
        DronesManager::DroneRecord d2(200);

        m.insert_back(r2);
        ASSERT_TRUE(m.remove(0));

        ASSERT_FALSE(m.remove_front());
        ASSERT_FALSE(m.remove_back());
        ASSERT_FALSE(m.remove(0));

        ASSERT_TRUE(m.insert_front(r2));
        ASSERT_TRUE(m.insert_back(d2));

	    return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
        DronesManager m;
        DronesManager::DroneRecord r2(100);
        DronesManager::DroneRecord d2(200);

        ASSERT_FALSE(m.remove(0));
        ASSERT_TRUE(m.insert_back(r2));
        ASSERT_FALSE(m.insert(d2, 12));
        ASSERT_FALSE(m.insert(d2, 8));

        ASSERT_TRUE(m.remove(0));
        ASSERT_FALSE(m.remove(0));

        return true;
	}
	    	
	// PURPOSE: inserts into an unsorted list, then sort the list
	bool test10() {
        DronesManagerSorted m;
        DronesManager::DroneRecord r2d2(100);
        DronesManager::DroneRecord cpo(200);
        DronesManager::DroneRecord skywalker(300);
        DronesManager::DroneRecord vader(400);

        m.insert_front(r2d2);
        m.insert_front(cpo);
        m.insert_front(skywalker);
        m.insert_front(vader);

        m.sort_asc();
        ASSERT_TRUE(m.is_sorted_asc());
        ASSERT_FALSE(m.is_sorted_desc());

        m.sort_desc();
        ASSERT_TRUE(m.is_sorted_desc());
        ASSERT_FALSE(m.is_sorted_asc());

        return true;
	}
	
	// PURPOSE: insert and remove into sorted manager in ascending order
	bool test11() {
        DronesManagerSorted m;
        DronesManager::DroneRecord r2d2(100);
        DronesManager::DroneRecord cpo(200);
        DronesManager::DroneRecord skywalker(300);
        DronesManager::DroneRecord vader(400);

        m.insert_sorted_asc(r2d2);
        m.insert_sorted_asc(cpo);
        m.insert_sorted_asc(vader);
        m.insert_sorted_asc(skywalker);

        m.remove(0);

        ASSERT_TRUE(m.select(0) == r2d2);
        ASSERT_TRUE(m.select(1) == cpo);
        ASSERT_TRUE(m.select(2) == vader);

        return true;
	}
	
	// PURPOSE: insert and remove into sorted manager in descending order
	bool test12() {
        DronesManagerSorted m;
        DronesManager::DroneRecord r2d2(100);
        DronesManager::DroneRecord cpo(200);
        DronesManager::DroneRecord skywalker(300);
        DronesManager::DroneRecord vader(400);

        m.insert_sorted_desc(r2d2);
        m.insert_sorted_desc(cpo);
        m.insert_sorted_desc(vader);
        m.insert_sorted_desc(skywalker);

        m.remove(0);

        ASSERT_TRUE(m.select(0) == skywalker);
        ASSERT_TRUE(m.select(1) == cpo);
        ASSERT_TRUE(m.select(2) == r2d2);

        return true;
	}
};

#endif
