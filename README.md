# C Server
Simple server library in C.

## Usage
- Build with `make`.
- Copy library from `target/`.
- See [api](#api) below or [test](tests/test.c) for example.

## API
Types:
- [`ipaddr_t`](#ipaddr_t)
- [`port_t`](#port_t)
- [`sockfd_t`](#sockfd_t)

Struct types:
- [`Server`](#server)
- [`ServerReq`](#serverreq)
- [`ServerRes`](#serverres)

Struct `Server`:
- [`Server_new()`](#server_new)
- [`Server::set_handler()`](#serverset_handler)
- [`Server::set_ipaddr()`](#serverset_ipaddr)
- [`Server::set_port()`](#serverset_port)
- [`Server::listen()`](#serverlisten)
- [`Server::delete()`](#serverdelete)

Struct `ServerReq`:
- [`ServerReq::data`](#serverreqdata)
- [`ServerReq::size`](#serverreqsize)
- [`ServerReq::addr`](#serverreqaddr)
- [`ServerReq::clientfd`](#serverreqclientfd)

Struct `ServerRes`:
- [`ServerRes::clientfd`](#serverresclientfd)
- [`ServerRes::writeBytes()`](#serverreswriteBytes)
- [`ServerRes::writeStr()`](#serverreswritestr)
- [`ServerRes::writeU64()`](#serverreswriteu64)
- [`ServerRes::writeI64()`](#serverreswritei64)
- [`ServerRes::writeHex()`](#serverreswritehex)
- [`ServerRes::end()`](#serverresend)
- [`ServerRes::delete()`](#serverresdelete)

## API Description

#### ipaddr_t

#### port_t

#### sockfd_t

#### Server

#### Server_new()

#### Server::set_handler()

#### Server::set_ipaddr()

#### Server::set_port()

#### Server::listen()

#### Server::delete()

#### ServerReq

#### ServerReq::data

#### ServerReq::size

#### ServerReq::addr

#### ServerReq::clientfd

#### ServerRes

#### ServerRes::clientfd

#### ServerRes::writeBytes()

#### ServerRes::writeStr()

#### ServerRes::writeU64()

#### ServerRes::writeI64()

#### ServerRes::writeHex()

#### ServerRes::end()

#### ServerRes::delete()
