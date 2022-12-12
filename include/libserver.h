/*
 * This file selectively exposes certain features of libserver,
 * thus acting as a layer of abstraction. As a result, this file
 * needs to be updated everytime API changes are made.
 *
 * WARNING: `struct` definitions MUST have members ordered in the
 * exact order in which they're ordered outside libserver.h.
 *
 * For example: `struct Server` in libserver.h has exact ordering of
 * members as in the actual implementation of `struct Server` defined
 * in server.h.
 *
 * Do note that as long as members are ordered properly wrt their types,
 * it doesn't matter if member different names are used in libserver.h.
 *
 * For example `struct Server::_` in libserver.h is actually implemented
 * as`struct Server::priv` in server.h.
 *
 * As a convention, `void* _;` indicates private members. They are auto
 * managed. Modifying them may lead to undefined behaviour.
 */

#ifndef __LIBSERVER_H__
#define __LIBSERVER_H__

#include <stddef.h>        // size_t
#include <inttypes.h>      // uint8_t, uint16_t, uint64_t, int64_t

// from types.h: type definitions

/**
 * @brief Datatype for IPv4 address
 */
typedef uint8_t ipaddr_t[4];

/**
 * @brief Datatype for port
 */
typedef uint16_t port_t;

/**
 * @brief Datatype for socket file descriptor.
 * You'll hardly ever need to directly use a socket file descriptor.
 */
typedef int sockfd_t;

/**
 * @brief Server struct type
 */
typedef struct Server Server;

/**
 * @brief Server request struct type
 */
typedef struct ServerReq ServerReq;

/**
 * @brief Server response struct type
 */
typedef struct ServerRes ServerRes;

// from server.h: create a server instance

/**
 * @brief Server struct type
 */
struct Server {
    /**
     * @brief Sets handler callback. The callback is called when a request is received.
     * @param sv Pointer to Server struct
     * @param handler Callback function of prototype void (ServerReq*, ServerRes*)
     */
    void (*set_handler)(Server* sv, void (*handler)(ServerReq*, ServerRes*));
    /**
     * @brief Sets host IPv4 address. Example sv->set_addr(sv, 127, 0, 0, 1);
     * @param sv Pointer to Server struct
     * @param a0
     * @param a1
     * @param a2
     * @param a3
     */
    void (*set_ipaddr)(Server* sv, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3);
    /**
     * @brief Sets host port
     * @param sv Pointer to Server struct
     * @param port
     */
    void (*set_port)(Server* sv, port_t port);
    /**
     * @brief Listens for new connections.
     * Waits for all server threads to join. Force exits threads on ^C.
     * @param sv Pointer to Server struct
     * @param callback Called once after server is started. Callback is called on main thread, not on server threads.
     */
    void (*listen)(Server* sv, void (*callback)(ipaddr_t, port_t));
    /**
     * @brief Deletes server instance and frees resources.
     * @param sv Double pointer to Server instance. Sets instance to `NULL`.
     */
    void (*delete)(Server** sv);
    /**
     * @brief Private server data
     * Auto managed. DO NOT modify.
     */
    void* _;
};

/**
 * @brief Create new server instance
 * @return Server*
 */
Server* Server_new();

// from request.h: read request

/**
 * @brief Server request struct type
 */
struct ServerReq {
    /**
     * @brief Data recieved from client.
     * NOTE that this data will be NULL terminated.
     */
    char* data;
    /**
     * @brief Size of data received from client
     */
    size_t size;
    /**
     * @brief Client IPv4 address
     * @type ipaddr_t aka uint8_t[4]
     */
    ipaddr_t addr;
    /**
     * @brief Client socket file descriptor
     * @type sockfd_t aka int
     */
    sockfd_t clientfd;
    /**
     * @brief Deletes ServerReq instance and frees resources.
     * Note that you don't need to call delete manually as it is automatically called after a response is sent.
     * @param req Double pointer to request instance. Sets instance to `NULL`.
     */
    void (*delete)(ServerReq** req);
};

// from response.h: handle response

/**
 * @brief Server response struct type
 */
struct ServerRes {
    /**
     * @brief Client socket file descriptor
     * @type sockfd_t aka int
     */
    sockfd_t clientfd;
    /**
     * @brief Writes raw bytes to response
     * @param res Pointer to server response instance
     * @param data Data to be written
     * @param size Size of data in bytes
     */
    void (*writeBytes)(ServerRes* res, const char* data, size_t size);
    /**
     * @brief Writes ASCII character string to response
     * @param res Pointer to server response instance
     * @param data String to be written
     */
    void (*writeStr)(ServerRes* res, const char* str);
    /**
     * @brief Writes an unsigned number to response
     * @param res Pointer to server response instance
     * @param n The number itself
     */
    void (*writeU64)(ServerRes* res, uint64_t n);
    /**
     * @brief Writes a signed number to response
     * @param res Pointer to server response instance
     * @param n The number itself
     */
    void (*writeI64)(ServerRes* res, int64_t n);
    /**
     * @brief Writes a number to response in hex representation
     * @param res Pointer to server response instance
     * @param n The number itself
     */
    void (*writeHex)(ServerRes* res, uint64_t n);
    /**
     * @brief Closes client socket file descriptor
     * @param res Pointer to server response instance
     */
    void (*end)(ServerRes* res);
    /**
     * @brief Deletes ServerRes instance and frees resources.
     * Note that you don't need to call delete manually as it is automatically called after a response is sent.
     * @param res Double pointer to response instance. Sets instance to `NULL`.
     */
    void (*delete)(ServerRes** res);
};

// from apifunc.h: misc api functions

/**
 * @brief Gets current date and time. Useful for logs.
 * @return char* Remember to free it.
 */
const char* server_gettime();

#endif
