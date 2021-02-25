#pragma once

namespace fr {

	class Events {

	public:
		~Events();
		Events(const Events&) = delete;
		Events& operator=(const Events&) = delete;

		static Events& Ref() {
			static Events reference;
			return reference;
		}

		void Poll();
		void Initialiaze();

	private:
		Events();

	private:

	};

	static Events& Event = Events::Ref();
}