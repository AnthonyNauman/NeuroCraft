#pragma once

namespace events{

    template<typename ...TParams>
    class AbstractEventHandler
    {
        public:
            virtual void call(TParams... params) = 0;
        protected:
            AbstractEventHandler() {}
    };
}