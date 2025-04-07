#ifndef SOCKETS_H
#define SOCKETS_H

#include <stdint.h>
#include <WebSocketsClient.h>

void webSocketEvent(WStype_t type, uint8_t* payload, size_t lenght); // handle WebSocket events
void checkWebSocket(); // check for WebSocket events

#endif