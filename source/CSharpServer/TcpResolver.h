#pragma once

#include "Service.h"

#include <server/asio/tcp_resolver.h>

namespace CSharpServer {

    //! TCP resolver
    /*!
        TCP resolver is used to resolve DNS while connecting TCP clients.

        Thread-safe.
    */
    public ref class TcpResolver
    {
    public:
        //! Initialize resolver with a given service
        /*!
            \param service - Service
        */
        TcpResolver(Service^ service);
        ~TcpResolver() { this->!TcpResolver(); }

        //! Get the service
        property Service^ Service { CSharpServer::Service^ get() { return _service; } }

        //! Cancel any asynchronous operations that are waiting on the resolver
        void Cancel() { return _resolver->get()->Cancel(); }

    protected:
        !TcpResolver() { _resolver.Release(); };

    internal:
        CSharpServer::Service^ _service;
        Embedded<std::shared_ptr<CppServer::Asio::TCPResolver>> _resolver;
    };

}
