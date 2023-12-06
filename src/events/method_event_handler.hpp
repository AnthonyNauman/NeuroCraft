#pragma once

#include "event_handler.hpp"
#include <assert.h>

namespace events {

    template<typename TObject, typename... TParams>
    class MethodEventHandler : public AbstractEventHandler<TParams...>
    {

    public:
        using TMethod      = void (TObject::*)(TParams...);
        using EventHandler = AbstractEventHandler<TParams...>;
        MethodEventHandler(TObject& object, TMethod method)
          : AbstractEventHandler<TParams...>()
          , m_object(object)
          , m_method(method)
        {
            assert(m_method != nullptr);
        }

        virtual void call(TParams... params) override final { (m_object.*m_method)(params...); }

    protected:
        virtual bool isEquals(const EventHandler& other) const override
        {
            const MethodEventHandler* _other = dynamic_cast<const MethodEventHandler*>(&other);
            return (_other != nullptr && &m_object == &_other->m_object && m_method == _other->m_method);
        }

    private:
        TObject& m_object;
        TMethod  m_method;
    };

    template<typename TObject, typename... TParams>
    AbstractEventHandler<TParams...>& createMethodHandler(TObject& obj, void (TObject::*method)(TParams...))
    {
        return *new MethodEventHandler<TObject, TParams...>(obj, method);
    }

}
#define METHOD_HANDLER(Obj, Method) ::events::createMethodHandler(Obj, Method)
#define OBJ_METHOD_HANDLER(Method) METHOD_HANDLER(*this, Method)