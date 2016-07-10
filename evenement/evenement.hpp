#pragma once

#include <map>
#include <functional>
#include <algorithm>
#include <vector>
#include <utility>

using std::map;
using std::string;
using std::function;
using std::vector;
using std::pair;

namespace evenement {

	class Listener {
	public:
		Listener() {}

		explicit Listener(function<void(void*)> callable):value(callable) {}

		int key = 0;
		function<void(void*)> value;
	};

	class EventEmitter {
	private:
		int generatedId = 0;
	protected:
		map<string, vector<Listener>> _listeners;
	public:
		void on(string event, Listener& listener)
		{
			listener.key = generateId();
			_listeners[event].push_back(listener);
		}

		void on(string event, function<void(void*)> callable)
		{
			Listener listener(callable);
			listener.key = generateId();
			_listeners[event].push_back(listener);
		}

		void once(string event, Listener listener)
		{
			Listener onceListener;
			onceListener.value = [this, event, listener, onceListener](void* args) {
				removeListener(event, onceListener);
				listener.value(args);
			};

			on(event, onceListener);
		}

		void once(string event, function<void(void*)> callable)
		{
			Listener listener(callable);
			Listener onceListener;
			onceListener.value = [this, event, &listener, &onceListener](void* args) {
				removeListener(event, onceListener);
				listener.value(args);
			};

			on(event, onceListener);
		}

		void emit(string event, void* args = nullptr)
		{
			for (auto ev : listeners(event)) {
				ev.value(args);
			}
		}

		void removeListener(string event, Listener callable)
		{
			if (_listeners.count(event) == 1) {
				auto vector = &_listeners.at(event);

				auto it = find_if(vector->begin(), vector->end(), [&callable](Listener function) {
				    return callable.key == function.key;
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

		vector<Listener> listeners(string event)
		{
			return _listeners.count(event) == 1 ? _listeners.at(event) : vector<Listener>();
		}

	private:

		int generateId()
		{
			generatedId++;
			return generatedId;
		}
	};
}