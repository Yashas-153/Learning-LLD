/*

1. Inheritance : It represents a "is-a" relationship and promotes code reuse

Example Dog is a Animal
    Animal -> Base Class
    Dog  -> Derived Class



2. Association : It is a relationship between classes where each class has an independent existence, and they are loosely connected.
                It is often used to represent a simple connection between objects

Example :

    class Student(val name: String)

    class Course(val title: String)

    val student1 = Student("Alice")
    val course1 = Course("Mathematics")
    student1.courses = listOf(course1)

3. Composition : Composition represents a strong relationship where one class is composed of other classes, and the parts are essential
                 to the existence of the whole. It's used to create complex objects by combining simpler ones. 

Example :
    class Engine {
        fun start() {
            println("Engine started.")
        }
    }

    class Car {
        private val engine = Engine()

        fun drive() {
            engine.start()
            println("Car is moving.")
        }
    }

    The Car class is composed of an Engine. The Car cannot function without the Engine, and the Engine is encapsulated within the Car.


4. Aggregation : It represents a weaker relationship where one class contains other class but the parts can exist independently. 

Example :
    Class Player {
        string name;
    public:
        Player(string name) : name(name){} 
    }

    Class Team{
        vector<Player*> players;
        string teamName;
    public:
        Team(string name) : teamName(name) {}

        void addPlayers(Player p){
            players.push_back(p);
        }
    }

    Here in the above example, Team class has an aggregation relationship with Player class. Multiple players can be part of the Team and each employee can exist independently.
*/

