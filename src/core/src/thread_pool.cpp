#include "../include/thread_pool.h"

namespace map_generator {
    template<typename job>
    thread_pool<job>::thread_pool(unsigned short thread_count) {
        this->_thread_pool.reserve(thread_count);
    }

    template<typename job>
    thread_pool<job>::~thread_pool() noexcept
    {
        for(auto&& thread: this->_thread_pool)
            if(thread.joinable())
                thread.join();

        this->_thread_pool.clear();
    }

    template<typename job>
    void thread_pool<job>::push(job&& executable_job) {
        std::promise<void> promise;
        this->start_thread(executable_job, std::move(promise));
    }

    template<typename job>
    template<typename output>
    void thread_pool<job>::push(
            job &&executable_job,
            std::promise<output> &&promise) {
        this->start_thread(executable_job, std::move(promise));
    }

    template<typename job>
    template<typename input>
    void thread_pool<job>::push(job &&executable_job, const input &job_input) {
        auto curried_job = [=]() {
            return executable_job(job_input);
        };

        std::promise<void> promise;


    }

    template<typename job>
    template<typename input, typename output>
    void thread_pool<job>::push(job &&executable_job, const input &job_input, std::promise<output> &&promise) {
        auto curried_job = [=]() {
            return executable_job(job_input);
        };

        this->template start_thread(curried_job, std::move(promise));
    }

    template<typename job>
    template<typename output>
    void thread_pool<job>::start_thread(
            job &&executable_job,
            std::promise<output> &&promise) {
        for (auto&& thread : this->_thread_pool)
        {
            if (thread.joinable())
            {
                continue;
            }

            thread = std::thread(executable_job, std::move(promise));
            return;
        }

        for (auto&& thread: this->_thread_pool)
        {
            if (!thread.joinable())
            {
                continue;
            }

            thread.join();
            thread = std::thread(executable_job, std::move(promise));
            return;
        }
    }

} // map_generator