#include "evenement/evenement.hpp"
#include "iostream"

using namespace evenement;

class Dog : public EventEmitter {
public:
	void bark()
	{
		std::cout << "Woof! Woof!" << std::endl;
	}
};

class Home : public EventEmitter {
	Dog _dog;
public:
	Home()
	{
		_dog.on("agression", [this](void* args) {_dog.bark(); });
	}

	void summonDog()
	{
		_dog.emit("agression");
	}
};

class Stranger {
	string _name;
public:
	Stranger(string name) :_name(name) {}

	void enter(Home home)
	{
		home.emit("enter", this);
	}

	const char* getName()
	{
		return _name.c_str();
	}
};

int main()
{
	Stranger stranger("Alice");
	Home home;

	home.on("enter", [&home](void* args) {
		auto enterer = static_cast<Stranger*>(args);
		std::cout << enterer->getName() << " just entered The Home! Summoning dog..." << std::endl;
		home.summonDog();
	});

	stranger.enter(home);

    return 0;
}

