#include "lest.hpp"
#include "../evenement/evenement.hpp"

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

	CASE("removeListener should remove right listener.")
    {
		EventEmitter emitter;

	    auto fooToggle = false;
	    auto barToggle = false;

		Listener fooCallback([&fooToggle](void* args) { fooToggle = true; });
		Listener barCallback([&barToggle](void* args) { barToggle = true; });

		emitter.on("event", fooCallback);
		emitter.on("event", barCallback);

		emitter.removeListener("event", barCallback);

		emitter.emit("event");

		EXPECT(fooToggle == true);
		EXPECT(barToggle == false);
    },

	CASE("once should work once :D")
    {
		EventEmitter emitter;

		int lambdaCounter = 0;
		int listenerCounter = 0;

		Listener onceListener([&listenerCounter](void* args) {
			listenerCounter++;
		});

		emitter.once("event", onceListener);
		emitter.once("event", [&lambdaCounter](void* args) { lambdaCounter++;  });

		for (int i = 0; i < 10; i++) {
			emitter.emit("event");

			EXPECT(lambdaCounter == 1);
			EXPECT(listenerCounter == 1);
		}
    },
	
	CASE("It should be able to pass data into callback")
    {
		EventEmitter emitter;
		vector<string> outcoming;
		emitter.on("test", [&outcoming](void* args) {
			outcoming = *static_cast<vector<string>*>(args);
		});

		auto incoming = vector<string>{ "hello", "how are you?" };

		emitter.emit("test", &incoming);

		for (unsigned long i = 0; i < incoming.size(); i++) {
			EXPECT(incoming[i] == outcoming[i]);
		}
    },
};

int main( int argc, char* argv[] )
{
    return lest::run( specification, argc, argv );
}