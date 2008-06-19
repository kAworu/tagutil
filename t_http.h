#ifndef T_NET_H
#define T_NET_H
/*
 * t_http.h
 *
 * HTTP request function for tagutil.
 */

#include "config.h"


#define HTTP_GET    "GET"
#define HTTP_POST   "POST"
#define HTTP_PUT    "PUT"
#define HTTP_DELETE "DELETE"


/*
 * query the host server. arg (can be null) is the argument encoded in a HTML
 * way /index.php?foo=bar&oni=42 (note the / at the beginning. it's not optional).
 * It return the server's response.
 *
 * for example (same effect as "{fetch,wget} http://www.kaworu.ch/index.html"):
 *      http_cmd("www.kaworu.ch", "80", HTTP_GET, "/index.html");
 *
 * return value has to be freed.
 */
char* http_request(const char *__restrict__ host, const char *__restrict__ port,
        const char *__restrict__ method, const char *__restrict__ arg)
    __attribute__ ((__nonnull__ (1, 2, 3)));

#endif /* !T_NET_H */