I think doing documentation for commit changes in commit messages is not too good,a s I can't use tab to make things clear. And messages will be flooded, so I will do an update log here. 

---COMMIT 23rd Nov, 2021 21:35---
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

---UPDATE 24th Nov, 2021 22:31---

Due to laziness, I decided to merge the Node class and Building class. So now building class owns enum class Type, Category, Direction. And all functions in Node are moved to Building. Second, some functions are changed to make looping easier, eg. 

```
// neighboring building
Node* get_neighboring_building(Direction direction) const;
void set_neighboring_building(Direction direcion, Building* n);
bool is_neighbor_empty(Direction direction) const;

virtual bool is_neighbor_road(Direction direcion) const;
```

Also, Road.h, Street.h and Avenue.h are created, containing things that are necessary to be compiled. So currently, the updated files can be runned perfectly inside qt with no errors, as well as additional components to be used in traffic simulation.
