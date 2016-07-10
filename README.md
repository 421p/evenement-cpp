# Evenement-cpp

Événement-cpp is a port of [igorw/evenement](https://github.com/igorw/evenement), simple event dispatching library for PHP to C++.

[![Build Status](https://travis-ci.org/421p/evenement-cpp.svg?branch=master)](https://travis-ci.org/421p/evenement-cpp)
## How to install

It's header-only library so all you need is `#include<evenement.hpp>` to your project.

You can download it via `wget https://raw.githubusercontent.com/421p/evenement-cpp/master/evenement/evenement.hpp`

## Usage

### Creating an Emitter

```c++
evenement::EventEmitter emitter;
```

or you can add EventEmitter functional to any of your classes:

```c++
class Foo : public evenement::EventEmitter {

}
```

### Adding Listeners

```c++
emitter.on("foo-event", [](void* args) {
    std::cout << "foo-event was fired!" << std::endl;
});
```

or if you want it trigger just once:

```c++
emitter.once("foo-event", [](void* args) {
    std::cout << "foo-event was fired this time!" << std::endl;
});
```

### Emitting Events

```c++
emitter.emit("foo-event");
```

### Passing data to the callback

```c++
emitter.on("greetings", [](void* args) {
    std::cout << "Hello "<< (char*)args << std::endl;
});

emitter.emit("greetings", "Bob"); // Hello Bob
```

lambda capture feature can be used here too:

```c++
std::string foo = "bar";

emitter.on("greetings", [foo](void* args) {
    std::cout << foo.c_str() << std::endl;
});

```

### Removing listeners

if you want to remove listener later you should wrap your function into `evenement::Listener` class

```c++
Listener someListener([](void* args) { });
emitter.on("event", someListener);
emitter.removeListener("event", someListener);
```

also you can remove all listeners from event:

```c++
emitter.removeAllListeners("event");
```

### Running a example

```
git clone https://github.com/421p/evenement-cpp
cd evenement-cpp
g++ example.cxx -std=c++11 -o runme && ./runme  
```

### TODO:
* add some tests

