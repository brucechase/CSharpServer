#pragma once

#include "Service.h"

#include <server/asio/ssl_context.h>

namespace CSharpServer {

    //! SSL method
    public enum class SslMethod : char
    {
        //! Generic SSL version 2.
        SSLV2,

        //! SSL version 2 client.
        SSLV2_Client,

        //! SSL version 2 server.
        SSLV2_Server,

        //! Generic SSL version 3.
        SSLV3,

        //! SSL version 3 client.
        SSLV3_Client,

        //! SSL version 3 server.
        SSLV3_Server,

        //! Generic TLS version 1.
        TLSV1,

        //! TLS version 1 client.
        TLSV1_Client,

        //! TLS version 1 server.
        TLSV1_Server,

        //! Generic SSL/TLS.
        SSLV23,

        //! SSL/TLS client.
        SSLV23_Client,

        //! SSL/TLS server.
        SSLV23_Server,

        //! Generic TLS version 1.1.
        TLSV11,

        //! TLS version 1.1 client.
        TLSV11_Client,

        //! TLS version 1.1 server.
        TLSV11_Server,

        //! Generic TLS version 1.2.
        TLSV12,

        //! TLS version 1.2 client.
        TLSV12_client,

        //! TLS version 1.2 server.
        TLSV12_server,

        //! Generic TLS.
        TLS,

        //! TLS client.
        TLS_Client,

        //! TLS server.
        TLS_Server
    };

    //! SSL verify mode
    public enum class SslVerifyMode : char
    {
        VerifyNone,
        VerifyPeer,
        VerifyFailIfNoPeerCert,
        VerifyClientOnce
    };

    //! SSL file format
    public enum class SslFileFormat : char
    {
        //! ASN.1 file.
        ASN1,

        //! PEM file.
        PEM
    };

    ref class SslContext;

    class SslContextEx : public CppServer::Asio::SSLContext
    {
    public:
        using CppServer::Asio::SSLContext::SSLContext;

        gcroot<SslContext^> root;

        void set_password(const std::string& password);

    private:
        std::string _password;
    };

    //! SSL context
    public ref class SslContext
    {
    internal:
        //! Initialize empty SSL context
        SslContext() {}

    public:
        //! Initialize SSL context with a given SSL method
        /*!
            \param method - SSL method
        */
        SslContext(SslMethod method);
        ~SslContext() { this->!SslContext(); }

        void SetDefaultVerifyPaths();
        void SetRootCerts();
        void SetPassword(String^ password);
        void SetVerifyMode(SslVerifyMode mode);
        void SetVerifyDepth(int depth);

        void LoadVerifyFile(String^ filename);

        void UseCertificateChainFile(String^ filename);
        void UsePrivateKeyFile(String^ filename, SslFileFormat format);
        void UseTmpDHFile(String^ filename);

    protected:
        !SslContext() { _context.Release(); };

    internal:
        Embedded<std::shared_ptr<SslContextEx>> _context;
    };

}
