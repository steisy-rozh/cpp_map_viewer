#ifndef CORE_THREAD_POOL_H
#define CORE_THREAD_POOL_H

#include <vector>
#include <thread>
#include <mutex>
#include <future>

namespace map_generator {

    template <typename job>
    class thread_pool {
    private:
        std::vector<std::thread> _thread_pool;

        template<typename output>
        void start_thread(
                job&& executable_job,
                std::promise<output>&& promise);
    public:
        thread_pool(unsigned short thread_count);

        void push(job&& executable_job);

        template<typename input>
        void push(job&& executable_job, const input& job_input);

        template<typename output>
        void push(job&& executable_job, std::promise<output>&& promise);

        template<typename input, typename output>
        void push(job&& executable_job, const input& job_input, std::promise<output>&& promise);

        virtual ~thread_pool() noexcept;
    };

} // map_generator

#endif //CORE_THREAD_POOL_H
