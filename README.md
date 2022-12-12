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

Other functions:
- [`server_gettime()`](#server_gettime)

### Types

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
You'll hardly ever need to directly use a socket file descriptor.

### Server
```c
typedef struct Server Server;

struct Server {
    void (*set_handler) (Server* sv, void (*handler)(ServerReq*, ServerRes*));
    void (*set_ipaddr)  (Server* sv, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3);
    void (*set_port)    (Server* sv, port_t port);
    void (*listen)      (Server* sv, void (*callback)(ipaddr_t, port_t));
    void (*delete)      (Server** sv);
    const void* _;
};
```
Server struct type.

The `const void* _` encapsulates private data members of the `Server` type.

As a convention, `const void* _` indicates private members.
They are auto managed. Modifying them may lead to undefined behaviour.

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
Sets host IPv4 address. Example:
```c
sv->set_addr(sv, 127, 0, 0, 1);
```
- param: `sv` Pointer to Server struct.
- param: `a0`.
- param: `a1`.
- param: `a2`.
- param: `a3`.

Note that a new server instance has a default IPv4 address of `127.0.0.1`.

#### Server::set_port()
```c
void (*set_port)(Server* sv, port_t port);
```
Sets host port
- param: `sv` Pointer to Server struct.
- param: `port`.

Note that a new server instance has a default port of `8080`.

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
Deletes server instance and frees resources. Sets instance to `NULL`.
- param: `sv` Double pointer to Server.

### ServerReq
```c
typedef struct ServerReq ServerReq;

struct ServerReq {
    char* data;
    size_t size;
    sockfd_t clientfd;
    void (*delete)(ServerReq** req);
};
```

Server request struct type.

#### ServerReq::data
```c
char* data;
```
Data recieved from client.

**Note** that data will be `NULL` terminated.

#### ServerReq::size
```c
size_t size;
```
Size of data received from client.

#### ServerReq::addr
```c
ipaddr_t addr;
```
Client IPv4 address.
- type: `ipaddr_t` aka `uint8_t[4]`.

#### ServerReq::clientfd
```c
sockfd_t clientfd;
```
Client socket file descriptor.
- type: `sockfd_t` aka `int`.

#### SeverReq::delete()
```c
void (*delete)(ServerReq** req);
```
Deletes ServerReq instance and frees resources.
Note that you don't need to call delete manually as it is automatically called after a response is sent.
- param: `req` Double pointer to request instance. Sets instance to `NULL`.

### ServerRes
```c
typedef struct ServerRes ServerRes;

struct ServerRes {
    sockfd_t clientfd;
    void (*writeBytes) (ServerRes* res, const char* data, size_t size);
    void (*writeStr)   (ServerRes* res, const char* str);
    void (*writeU64)   (ServerRes* res, uint64_t n);
    void (*writeI64)   (ServerRes* res, int64_t n);
    void (*writeHex)   (ServerRes* res, uint64_t n);
    void (*end)        (ServerRes* res);
};
```
Server response struct type.

Note that server response functions are called wrt a server response instance. Example:
```c
// ServerRes* res;
res->writeStr(res, "Hello, World!\n");
res->end(res);
```

#### ServerRes::clientfd
```c
sockfd_t clientfd;
```
Client socket file descriptor.
- type: `sockfd_t` aka `int`.

#### ServerRes::writeBytes()
```c
void (*writeBytes)(ServerRes* res, const char* data, size_t size);
```
Writes raw bytes to response.
- param: `res` Pointer to server response instance..
- param: `data` Data to be written.
- param: `size` Size of data in bytes.

#### ServerRes::writeStr()
```c
void (*writeStr)(ServerRes* res, const char* str);
```
Writes ASCII character string to response..
- param: `res` Pointer to server response instance.
- param: `data` String to be written.

#### ServerRes::writeU64()
```c
void (*writeU64)(ServerRes* res, uint64_t n);
```
Writes an unsigned number to response.
- param: `res` Pointer to server response instance.
- param: `n` The number itself.

#### ServerRes::writeI64()
```c
void (*writeI64)(ServerRes* res, int64_t n);
```
Writes a signed number to response.
- param: `res` Pointer to server response instance.
- param: `n` The number itself.

#### ServerRes::writeHex()
```c
void (*writeHex)(ServerRes* res, uint64_t n);
```
Writes a number to response in hex representation.
- param: `res` Pointer to server response instance.
- param: `n` The number itself.

#### ServerRes::end()
```c
void (*end)(ServerRes* res);
```
Closes client socket file descriptor.
- param: `res` Pointer to server response instance.

#### ServerRes::delete()
```c
void (*delete)(ServerRes** res);
```
Deletes ServerRes instance and frees resources.
Note that you don't need to call delete manually as it is automatically called after a response is sent.
- param: `res` Double pointer to response instance. Sets instance to `NULL`.

### Other Functions

#### server_gettime()
```c
const char* server_gettime();
```
Gets current date and time. Useful for logs.
- return: `char*` Remember to free it.
