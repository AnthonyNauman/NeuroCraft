#pragma once

namespace events {

    template<typename... TParams>
    class AbstractEventHandler
    {
        using EventHandler = AbstractEventHandler<TParams...>;

    public:
        virtual void call(TParams... params) = 0;

        bool operator==(const EventHandler& other) const { return isEquals(other); }

        bool operator!=(const EventHandler& other) const { return !(*this == other); }

    protected:
        AbstractEventHandler() {}
        virtual bool isEquals(const EventHandler& other) const = 0;
    };
}