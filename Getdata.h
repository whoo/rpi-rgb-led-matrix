#include <stdio.h>
#include <unistd.h>
#include "thread.h"
#include <string.h>

class GetData : public Thread {
        public:
                GetData(char m) : running_(true),module(m) {}
                virtual ~GetData() { running_ = false; }
		void Run();
        protected:
                volatile bool running_;  // TODO: use mutex, but this is good enough for now.
		int matrix_;
		char module;
};

