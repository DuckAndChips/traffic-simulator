I think doing documentation for commit changes in commit messages is not too good,a s I can't use tab to make things clear. And messages will be flooded, 
so I will do an update log here. 

COMMIT 23rd Nov, 2021 21:35:
  1. Node.h		added iostream
  2. Building.h		added derived class of Node
  3. Building.cpp		removed register/deregister
			(not done)change neighbor_building
  4. City.cpp		(not done)change to template
			change register/deregister
  5. AllTypeBuilding.cpp/.h	(not done)remove overide
  6. **Moved Road.h and Node.h into /buildings

As mentioned in whatsapp, to facilitate the ease of development, some changes in classes and enum types will be made, which will make eour life easier. 
1. To make load and save files easier (by casting), the enum type Building::type will be moved to Node::type, and changes will be made according to the following:
```
class Node{
  ...
  public:
    enum class Type{
      Clinic = 1,
      HOSPITAL = 2,
      SILVER_MINE = 3,
      GOLD_MINE = 4,
      HOUSE = 5,
      APARTMENT = 6,
      STREET = 7,
      APARTMENT = 8
    };
  ...
};
  ```
2. To make looping through adjacent nodes possible, I think it is good to put all the neighbouring ptrs into an array, in addition to a enum class for directions:
```
class Node{
  ...
  public:
    enum class Direction{
      NORTH,
      EAST,
      SOUTH,
      WEST
    };
  private:
    /// These four pointers are used to point at the four neighbouring building/road objects
    Node* east;
    Node* south;
    Node* west;
    Node* north;    
    Node* neighboring_buildings[4];
    neighboring_buildings[Direction::NORTH] = &north;
    neighboring_buildings[Direction::EAST] = &east;
    neighboring_buildings[Direction::South] = &south;
    neighboring_buildings[Direction::West] = &west;
}
```

---updated by Issac on 23rd Nov, 2021 21:50---
