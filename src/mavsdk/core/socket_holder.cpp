#include "socket_holder.h"

#ifndef WINDOWS
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace mavsdk {

SocketHolder::SocketHolder(int fd) noexcept :
    _fd{fd}
{}

SocketHolder::~SocketHolder() noexcept
{
    close();
}

void SocketHolder::reset(int fd) noexcept
{
    if (_fd != fd) {
        close();
        _fd = fd;
    }
}

void SocketHolder::close() noexcept
{
    if (!empty()) {
#ifndef WINDOWS
        // This should interrupt a recv/recvfrom call.
        shutdown(_fd, SHUT_RDWR);

        // But on Mac, closing is also needed to stop blocking recv/recvfrom.
        ::close(_fd);
#else
        shutdown(_fd, SD_BOTH);
        closesocket(_fd);
        WSACleanup();
#endif
    }
    _fd = invalid_socket_fd;
}

bool SocketHolder::empty() const noexcept
{
    return _fd == invalid_socket_fd;
}

int SocketHolder::get() const noexcept
{
    return _fd;
}
    
} // namespace mavsdk