#pragma once

#include <map>
#include <functional>
#include <algorithm>
#include <vector>

using std::map;
using std::string;
using std::function;
using std::vector;

namespace evenement {

	typedef function<void(void*)> listener;

	class EventEmitter {
	protected:
		map<string, vector<listener>> _listeners;
	public:
		void on(string event, listener callable)
		{
			_listeners[event].push_back(callable);
		}

		void once(string event, listener callable)
		{
			listener onceListener;
			onceListener = [this, event, callable, onceListener](void* args) {
				removeListener(event, onceListener);
				callable(args);
			};

			on(event, onceListener);
		}

		void emit(string event, void* args = nullptr)
		{
			for (auto ev : listeners(event)) {
				ev(args);
			}
		}

		void removeListener(string event, listener callable)
		{
			if (_listeners.count(event) == 1) {
				auto vector = &_listeners.at(event);

				auto it = find_if(vector->begin(), vector->end(), [&callable](listener function) {
				    return callable.target<void(*)(void*)>() == function.target<void(*)(void*)>();
				});

				if (it != vector->end()) {
					vector->erase(it);
				}
			}
		}

		void removeAllListeners()
		{
			_listeners.clear();
		}

		void removeAllListeners(string event)
		{
			if (_listeners.count(event) == 1) {
				_listeners.at(event).clear();
			}
		}

		vector<listener> listeners(string event)
		{
			return _listeners.count(event) == 1 ? _listeners.at(event) : vector<listener>();
		}
	};
}