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

		listener fooCallback = [](void* args) {
			
		};
		listener barBallback = [](void* args) {
			
		};

		emitter.on("event", fooCallback);
		emitter.on("event", barBallback);

		emitter.removeListener("event", barBallback);

		emitter.emit("event", "hellokitty");
    },
};

int main( int argc, char * argv[] )
{
    return lest::run( specification, argc, argv );
}