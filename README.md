# Evenement-cpp
Événement-cpp is a port of [igorw/evenement](https://github.com/igorw/evenement), simple event dispatching library for PHP to C++.

## How to install

It's header-only library so all you need is `#include<evenement.hpp>` to your project: <br>
`wget https://github.com/421p/evenement-cpp/blob/master/evenement/evenement.hpp`

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

### Emitting Events

```c++
$emitter.emit("foo-event");
```

### Passing data to the callback

```c++
emitter.on("greetings", [](void* args) {
    std::cout << "Hello "<< (char*)args << std::endl;
});

$emitter.emit("greetings", "Bob"); // Hello Bob
```

lambda capture feature can be used here too:

```c++
std::string foo = "bar";

emitter.on("greetings", [foo](void* args) {
    std::cout << foo.c_str() << std::endl;
});

```

### Running a example

```
git clone https://github.com/421p/evenement-cpp
cd evenement-cpp
g++ example.cxx -std=c++11 -o runme && ./runme  
```

### TODO:
* add some tests

