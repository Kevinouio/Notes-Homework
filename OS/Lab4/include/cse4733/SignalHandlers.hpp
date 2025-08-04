// SignalHandlers.hpp

#ifndef SIGNAL_HANDLERS_HPP
#define SIGNAL_HANDLERS_HPP

#include <csignal>

extern "C"
{
    // @brief Handles the SIGALRM signal
    // @param signal The signal number
    void handleSIGALRM(int signal);

    // @brief Handles the SIGUSR1 signal
    // @param signal The signal number
    void handleSIGUSR1(int signal);

    // @brief Handles the SIGINT signal
    // @param signal The signal number
    void handleSIGINT(int signal);
}

#endif // SIGNAL_HANDLERS_HPP