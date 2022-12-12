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
- [`Server::set_handler()`](#server-set_handler)
- [`Server::set_ipaddr()`](#server-set_ipaddr)
- [`Server::set_port()`](#server-set_port)
- [`Server::listen()`](#server-listen)
- [`Server::delete()`](#server-delete)

Struct `ServerReq`:
- [`ServerReq::data`](#serverreq-data)
- [`ServerReq::size`](#serverreq-size)
- [`ServerReq::addr`](#serverreq-addr)
- [`ServerReq::clientfd`](#serverreq-clientfd)

Struct `ServerRes`:
- [`ServerRes::clientfd`](#serverres-clientfd)
- [`ServerRes::writeBytes()`](#serverres-writeBytes)
- [`ServerRes::writeStr()`](#serverres-writestr)
- [`ServerRes::writeU64()`](#serverres-writeu64)
- [`ServerRes::writeI64()`](#serverres-writei64)
- [`ServerRes::writeHex()`](#serverres-writehex)
- [`ServerRes::end()`](#serverres-end)
- [`ServerRes::delete()`](#serverres-delete)

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
