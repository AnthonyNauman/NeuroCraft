#pragma once

#include "event_handler.hpp"
#include <list>
#include <functional>



namespace events{


    template<typename ...TParams>
    class TEvent
    {
        using TEventHandler = AbstractEventHandler<TParams...>;
        public:
            TEvent() : m_handlers() {}

            ~TEvent() 
            {
                for(TEventHandler* handler : m_handlers) {
                    delete handler;
                }
                m_handlers.clear();
            }

            //! \brief Call event handlers, which are subscribed on this event
            //! \param params Parameters for calling the handler method. 
            //! They must be in accordance with the signature of the called handler method
            void operator()(TParams... params)
            {
                for(TEventHandler* handler : m_handlers) {
                    handler->call(params...);
                }
            }

            //! \brief Subscribe handler on this event
            void operator+=(TEventHandler& handler)
            {
                m_handlers.push_back(&handler);
            }

        private:
            std::list<TEventHandler*> m_handlers;
    };   
}