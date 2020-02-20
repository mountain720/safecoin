// Copyright (c) 2017 The Zen Core developers
// Copyright (c) 2018 The Safecoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

namespace safe
{
typedef enum { SSL_ACCEPT,
               SSL_CONNECT,
               SSL_SHUTDOWN } SSLConnectionRoutine;
typedef enum { CLIENT_CONTEXT,
               SERVER_CONTEXT } TLSContextType;
}