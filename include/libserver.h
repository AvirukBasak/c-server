#ifndef __LIBSERVER_H__
#define __LIBSERVER_H__

#include <stddef.h>        // size_t
#include <inttypes.h>      // uint8_t, uint16_t, uint64_t, int64_t

typedef uint8_t ipaddr_t[4];
typedef uint16_t port_t;

typedef struct Server Server;
typedef struct __server_t __server_t;

typedef struct ServerReq ServerReq;
typedef struct ServerRes ServerRes;

struct Server {
    /**
     * @brief Sets listener callback. The callback is called when a request is received.
     * @param sv Pointer to Server struct
     * @param listener Callback function of prototype void (ServerReq*, ServerRes*)
     */
    void (*set_listener)(Server* sv, void (*listener)(ServerReq*, ServerRes*));
    /**
     * @brief Sets host address. Example sv->set_addr(sv, 127, 0, 0, 1);
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
     * @brief Reallocates server resources.
     * @param sv Double pointer to Server
     */
    void (*delete)(Server** sv);
    /**
     * @brief Server data.
     * Auto managed. DO NOT modify.
     */
    __server_t* __;
};

struct ServerReq {
    char* data;
    size_t size;
};

struct ServerRes {
    void (*writeBytes) (ServerRes* res, const char* data, size_t size);
    void (*writeStr)   (ServerRes* res, const char* str);
    void (*writeU64)   (ServerRes* res, uint64_t n);
    void (*writeI64)   (ServerRes* res, int64_t n);
    void (*writeHex)   (ServerRes* res, void* p);
    void (*send)       (ServerRes* res);
};

Server* Server_new();

#endif
