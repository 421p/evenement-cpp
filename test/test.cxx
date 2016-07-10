#include "lest.hpp"
#include "../evenement/evenement.hpp"
#include "iostream"

using namespace std;
using namespace evenement;

const lest::test specification[] =
{
    CASE( "Callback should be added to listeners vector." )
    {
		  EventEmitter emitter;

		  emitter.on("foo", [](void* args) { });

		  EXPECT(emitter.listeners("foo").size() == 1ul);

		  for (unsigned long i = 2; i < 10; i++) {
			  emitter.on("foo", [](void* args) {});
			  EXPECT(emitter.listeners("foo").size() == i);
		  }
    },

	CASE("removeListener should remove right callback.")
    {
		EventEmitter emitter;

	    auto fooToggle = false;
	    auto barToggle = false;

		Listener fooCallback([&fooToggle](void* args) { fooToggle = true; });
		Listener barCallback([&barToggle](void* args) { barToggle = true; });

		emitter.on("event", barCallback);
		emitter.on("event", fooCallback);

		emitter.removeListener("event", barCallback);

		emitter.emit("event");

		EXPECT(fooToggle == 1);
		EXPECT(barToggle == 0);
    },
};

int main( int argc, char* argv[] )
{
    return lest::run( specification, argc, argv );
}