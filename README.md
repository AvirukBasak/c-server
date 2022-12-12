# C Server
Simple server library in C.

## Usage
- Build with `make`.
- Copy library from `target/`.
- See [api](#api) below or [test](tests/test.c) for example.
- Start demo server with `make test`.

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
```c
typedef uint8_t ipaddr_t[4];
```
Datatype for IPv4 address.

#### port_t
```c
typedef uint16_t port_t;
```
Datatype for port.

#### sockfd_t
```c
typedef int sockfd_t;
```
Datatype for socket file descriptor.
You'll rarely need to directly use a socket file descriptor.

#### Server
```c
typedef struct Server Server;

struct Server {
    void (*set_handler) (Server* sv, void (*handler)(ServerReq*, ServerRes*));
    void (*set_ipaddr)  (Server* sv, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3);
    void (*set_port)    (Server* sv, port_t port);
    void (*listen)      (Server* sv, void (*callback)(ipaddr_t, port_t));
    void (*delete)      (Server** sv);
    void* __;
};
```
Server struct type.

Note that server functions are called wrt a server instance. Example:
```c
Server* sv = Server_new();
sv->set_ipaddr(sv, 127, 0, 0, 1);
sv->set_port(sv, 42069);
```

See below for declarations of the above server functions.

#### Server_new()
```c
Server* Server_new();
```
Create new server instance.
- return: `Server*` Pointer to new server instance.

#### Server::set_handler()
```c
void (*set_handler)(Server* sv, void (*handler)(ServerReq*, ServerRes*));
```
Sets handler callback. The callback is called when a request is received.
- param: `sv` Pointer to Server struct.
- param: `handler` Callback function of prototype `void (ServerReq*, ServerRes*)`.

#### Server::set_ipaddr()
```c
void (*set_ipaddr)(Server* sv, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3);
```
Sets host address. Example:
```c
sv->set_addr(sv, 127, 0, 0, 1);
```
- param: `sv` Pointer to Server struct.
- param: `a0`.
- param: `a1`.
- param: `a2`.
- param: `a3`.

#### Server::set_port()
```c
void (*set_port)(Server* sv, port_t port);
```
Sets host port
- param: `sv` Pointer to Server struct.
- param: `port`.

#### Server::listen()
```c
void (*listen)(Server* sv, void (*callback)(ipaddr_t, port_t));
```
Listens for new connections.
Waits for all server threads to join.
Force exits threads on `^C`.
- param: `sv` Pointer to Server struct.
- param: `callback` Called once after server is started.

#### Server::delete()
```c
void (*delete)(Server** sv);
```
Deletes server resources.
- param: `sv` Double pointer to Server.

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
