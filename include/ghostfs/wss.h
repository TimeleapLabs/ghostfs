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
    int auth_port;
    std::string host;
    std::string root;
    std::string suffix;
    ix::WebSocketServer server;
    ix::WebSocketServer auth_server;

  public:
    /**
     * @brief Creates a new wsserver
     * @param url to connect to
     */
    WSServer(int port, int auth_port, std::string host, std::string root, std::string suffix);

    int start();

  private:
    void onMessage(std::shared_ptr<ix::ConnectionState> connectionState, ix::WebSocket& webSocket,
                   const ix::WebSocketMessagePtr& msg);
    void onAuthMessage(std::shared_ptr<ix::ConnectionState> connectionState,
                       ix::WebSocket& webSocket, const ix::WebSocketMessagePtr& msg);
  };

}  // namespace wsserver
