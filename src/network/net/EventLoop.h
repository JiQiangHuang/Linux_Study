#pragma once
#include <vector>
#include <sys/epoll.h>
#include <memory>
#include <unordered_map>

namespace tmms
{
    namespace network
    {
        using EventPtr = std::shared_ptr<Event>;
        class EventLoop
        {
        private:
            bool Looping_{false};
            int epoll_fd_{-1};
            std::vector<struct epoll_event> epoll_events_;
            std::unordered_map<int, EventPtr> events_;

        public:
            EventLoop();
            ~EventLoop();

            void Loop();
            void Quit();
            
            void AddEvent(const EventPtr &event);
            void DelEvent(const EventPtr &event);
            bool EnableEventWriting(const EventPtr &event, bool enable);
            bool EnableEventReading(const EventPtr &event, bool enable);
        };

    } // namespace network

} // namespace tmms
