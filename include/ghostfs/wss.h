#pragma once

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXUserAgent.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXWebSocketServer.h>

#include <iostream>
#include <string>

namespace wsserver {

  /**
   * @brief A class for starting the GhostFS WS server
   */
  class WSServer {
    int port;
    ix::WebSocketServer server;

  public:
    /**
     * @brief Creates a new wsserver
     * @param url to connect to
     */
    WSServer(int port);

    void start(std::string root);

  private:
    void onMessage(std::shared_ptr<ix::ConnectionState> connectionState, ix::WebSocket& webSocket,
                   const ix::WebSocketMessagePtr& msg);
  };

}  // namespace wsserver
