# C Server
Simple server library in C.

## Usage
- Build with `make`.
- Copy library from `target/`.
- Read the api docs below.

### Demos
- [say-hello](demo/say-hello.c)
- [name-n-age](demo/name-n-age.c)

### Run test
- Start test with `make test`.
- Source code at [test](tests/test.c).

## API
Do note that `structtype::member` is just a way to document different members of a struct.

This is neither a syntax of C structs nor is this an API for a different programming language.

It is only a conceptual representation.

The difference b/w functions like `StructType_foo` and `StructType::foo` is described more specifically in the [`Server`](#server) section.

#### Types:
- [`ipaddr_t`](#ipaddr_t)
- [`port_t`](#port_t)
- [`sockfd_t`](#sockfd_t)

#### Struct types
- [`Server`](#server)
- [`ServerReq`](#serverreq)
- [`ServerRes`](#serverres)

#### Struct Server
- [`Server_new()`](#server_new)
- [`Server_delete()`](#server_delete)
- [`Server::set_handler()`](#serverset_handler)
- [`Server::set_ipaddr()`](#serverset_ipaddr)
- [`Server::set_port()`](#serverset_port)
- [`Server::listen()`](#serverlisten)
- [`handler`](#the-handler-function)

#### Struct ServerReq
- [`ServerReq::data`](#serverreqdata)
- [`ServerReq::size`](#serverreqsize)
- [`ServerReq::addr`](#serverreqaddr)
- [`ServerReq::clientfd`](#serverreqclientfd)
- [`ServerReq::readBytes()`](#serverreqreadbytes)
- [`ServerReq::readLine()`](#serverreqreadline)
- [`ServerReq::readf()`](#serverreqreadf)

#### Struct ServerRes
- [`ServerRes::clientfd`](#serverresclientfd)
- [`ServerRes::writeBytes()`](#serverreswriteBytes)
- [`ServerRes::writef()`](#serverreswritef)
- [`ServerRes::end()`](#serverresend)

#### Other functions
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
    void (*const set_handler) (Server* sv, void (*const handler)(ServerReq*, ServerRes*));
    void (*const set_ipaddr)  (Server* sv, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3);
    void (*const set_port)    (Server* sv, port_t port);
    void (*const listen)      (Server* sv, void (*const callback)(ipaddr_t, port_t));
    const void* const _;
};
```
Server struct type.

The `const void* const _` encapsulates private data members of the `Server` type.

As a convention, `const void* const _` indicates private members.
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

Note that it's a good idea to call `Server_delete` once you are done with the instance.

#### Server_delete()
```c
void Server_delete(Server** sv);
```
Deletes server instance and frees resources.
- param: `sv` Double pointer to Server. Sets instance to `NULL`.

#### Server::set_handler()
```c
void (*const set_handler)(Server* sv, void (*const handler)(ServerReq*, ServerRes*));
```
Sets handler callback. The callback is called when a request is received.
- param: `sv` Pointer to Server struct.
- param: `handler` Callback function of prototype `void (ServerReq*, ServerRes*)`.

#### The handler function
```c
void handler(ServerReq* req, ServerRes* res);
```
Handles the request and response.
- param: `req` Request instance. Is automatically freed when handler goes out of scope.
- param: `res` Response instance. Is automatically freed when handler goes out of scope.

#### Server::set_ipaddr()
```c
void (*const set_ipaddr)(Server* sv, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3);
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
void (*const set_port)(Server* sv, port_t port);
```
Sets host port
- param: `sv` Pointer to Server struct.
- param: `port`.

Note that a new server instance has a default port of `8080`.

#### Server::listen()
```c
void (*const listen)(Server* sv, void (*const callback)(ipaddr_t, port_t));
```
Listens for new connections.
Waits for all server threads to join.
Force exits threads on `^C`.
- param: `sv` Pointer to Server struct.
- param: `callback` Called once after server is started.

### ServerReq
```c
typedef struct ServerReq ServerReq;

struct ServerReq {
    char* const data;
    size_t const size;
    sockfd_t const clientfd;
    char* (*const readBytes) (ServerReq* req, size_t size);
    char* (*const readLine)  (ServerReq* req);
    bool  (*const readf)     (ServerReq* req, const char* fmt, ...);
};
```

Server request struct type.

#### ServerReq::data
**DEPRECATED** Is used internally.
Use either [`ServerReq::readBytes()`](#serverreqreadbytes),
[`ServerReq::readLine()`](#serverreqreadline) or
[`ServerReq::readf()`](#serverreqreadf).

```c
char* const data;
```
Data read from client.

**Note** that data will be `NULL` terminated.

#### ServerReq::size
```c
size_t const size;
```
Size of data received from client.

#### ServerReq::addr
```c
ipaddr_t const addr;
```
Client IPv4 address.
- type: `ipaddr_t` aka `uint8_t[4]`.

#### ServerReq::clientfd
```c
sockfd_t const clientfd;
```
Client socket file descriptor.
Is set to `0` if connection gets closed.
- type: `sockfd_t` aka `int`.

#### ServerReq::readBytes()
```c
char* (*const readBytes)(ServerReq* req, size_t size);
```
Reads raw bytes from request.
Data will be NULL terminated.
- param: `req` Pointer to server request instance.
- param: `size` Size of data to be read in bytes.
- return: `char*` Memory auto managed. DO NOT free the return value.
- return: `NULL` If connection closed.

**Note** that memory of returned data is auto freed on the next
call to [`ServerReq::readBytes()`](#serverreqreadbytes),
[`ServerReq::readLine()`](#serverreqreadline) or
[`ServerReq::readf()`](#serverreqreadf).

Make sure that the returned pointer is NOT freed manually.

#### ServerReq::readLine()
```c
char* (*const readLine)(ServerReq* req);
```
Reads a line of string from request.

A line of string is defined as a string ending with `LF` or `CR` `LF`.
Returned string will NOT contain the line endings.

Size of string is stored in [`ServerReq::size`](#serverreqsize).
- param: `req` Pointer to server request instance.
- return: `char*` Memory auto managed. DO NOT free the return value.
- return: `NULL` If connection closed.

**Note** that memory of returned data is auto freed on the next
call to [`ServerReq::readBytes()`](#serverreqreadbytes),
[`ServerReq::readLine()`](#serverreqreadline) or
[`ServerReq::readf()`](#serverreqreadf).

Make sure that the returned pointer is NOT freed manually.

#### ServerReq::readf()
```c
bool (*const readf)(ServerReq* req, const char* fmt, ...);
```
Reads formatted input from request, much like scanf.
Scans for values till an LF is encountered.

**WARNING** Using readf for strings is as unsafe as scanf.
Use [`ServerReq::readBytes()`](#serverreqreadbytes) or
[`ServerReq::readLine()`](#serverreqreadline) instead.
- param: `res` Pointer to server response instance.
- param: `fmt` Format string.
- param: `args`.
- return: `false` If connection closed.

### ServerRes
```c
typedef struct ServerRes ServerRes;

struct ServerRes {
    sockfd_t const clientfd;
    bool (*const writeBytes) (ServerRes* res, const char* data, size_t size);
    bool (*const writef)     (ServerRes* res, const char* fmt, ...);
    void (*const end)        (ServerRes* res);
};
```
Server response struct type.

Note that server response functions are called wrt a server response instance. Example:
```c
char* name = "Joe";
res->writef(res, "Hello, %s!\n", name);
res->end(res);
```

#### ServerRes::clientfd
```c
sockfd_t const clientfd;
```
Client socket file descriptor.
Is set to `0` if connection gets closed.
- type: `sockfd_t` aka `int`.

#### ServerRes::writeBytes()
```c
bool (*const writeBytes)(ServerRes* res, const char* data, size_t size);
```
Writes raw bytes to response.
- param: `res` Pointer to server response instance.
- param: `data` Data to be written.
- param: `size` Size of data in bytes.
- return: `false` If connection closed.

#### ServerRes::writef()
```c
bool (*const writef)(ServerRes* res, const char* fmt, ...);
```
Writes formatted output to response.
- param: `res` Pointer to server response instance.
- param: `fmt` Format string.
- param: `args`.
- return: `false` If connection closed.

#### ServerRes::end()
```c
void (*const end)(ServerRes* res);
```
Closes client socket file descriptor.
- param: `res` Pointer to server response instance.

### Other Functions

#### server_gettime()
```c
char* server_gettime();
```
Gets current date and time. Useful for logs.
- return: `char*` Remember to free it.
