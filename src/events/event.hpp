#pragma once

#include "event_handler.hpp"
#include <functional>
#include <list>

namespace events {

    template<typename... TParams>
    class TEvent
    {
        using TEventHandler   = AbstractEventHandler<TParams...>;
        using TEventHandlerIt = typename std::list<TEventHandler*>::const_iterator;

    public:
        TEvent()
          : m_handlers()
        {}

        ~TEvent()
        {
            for (TEventHandler* handler : m_handlers) {
                delete handler;
            }
            m_handlers.clear();
        }

        //! \brief Call event handlers, which are subscribed on this event
        //! \param params Parameters for calling the handler method.
        //! They must be in accordance with the signature of the called handler method
        void operator()(TParams... params)
        {
            for (TEventHandler* handler : m_handlers) {
                handler->call(params...);
            }
        }

        //! \brief Subscribe handler on this event
        //! \param handler Subscriber event handler
        //! \return True - if there is no this handler yet, otherwise - false
        bool operator+=(TEventHandler& handler)
        {
            if (findHandler(handler) == m_handlers.end()) {
                m_handlers.push_back(&handler);
                return true;
            }
            return false;
        }

        //! \brief Unsubscribe event handler
        //! \param handler Event handler that needed to unsubscribe
        //! \return True - if unsubscribe operation successful, otherwise - false
        bool operator-=(TEventHandler& handler)
        {
            auto it = findHandler(handler);
            if (it != m_handlers.end()) {
                TEventHandler* removedHandler = *it;
                m_handlers.erase(it);
                delete removedHandler;
                return true;
            }
            return false;
        }

    private:
        inline TEventHandlerIt findHandler(TEventHandler& handler) const
        {
            // clang-format off
            return std::find_if(m_handlers.begin(), m_handlers.end(), 
            [&handler](const TEventHandler* eventHandler)
            { 
                return (*eventHandler == handler); 
            });
            // clang-format on
        }

    private:
        std::list<TEventHandler*> m_handlers;
    };
}