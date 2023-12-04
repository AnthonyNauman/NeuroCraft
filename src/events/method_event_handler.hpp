#pragma once

#include "event_handler.hpp"
#include <assert.h>

namespace events{

    template<typename TObject, typename ...TParams>
    class MethodEventHandler : public AbstractEventHandler<TParams...>
    {
        using TMethod = void(TObject::*)(TParams...);

        public:
            MethodEventHandler(TObject& object, TMethod method)
            : AbstractEventHandler<TParams...>()
            , m_object(object)
            , m_method(method)
            {
                assert(m_method != nullptr);
            }

            virtual void call(TParams... params) override final
            {
                (m_object.*m_method)(params...);
            }


        private:
            TObject& m_object;
            TMethod m_method;
    };

    template<typename TObject, typename ...TParams>
    AbstractEventHandler<TParams...>& createMethodHandler(TObject& obj,void(TObject::*method)(TParams...))
    {
        return *new MethodEventHandler<TObject, TParams...>(obj, method);
    }

}
#define METHOD_HANDLER(Obj, Method) ::events::createMethodHandler(Obj, Method)
#define OBJ_METHOD_HANDLER(Method) METHOD_HANDLER(*this, Method)