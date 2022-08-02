#pragma once

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXUserAgent.h>
#include <ixwebsocket/IXWebSocket.h>

#include <iostream>
#include <string>

namespace wsclient {

  /**
   * @brief A class for connecting to the GhostFS WS server
   */
  class WSClient {
    std::string url;
    std::string user;
    std::string token;
    ix::WebSocket webSocket;

  public:
    /**
     * @brief Creates a new wsclient
     * @param url to connect to
     */
    WSClient(std::string url, std::string user, std::string token);

    /**
     * @brief Sends a message to the connected to ghostfs server
     * @param message the message to send
     */
    void send(std::string message);
    void sendBinary(char* message);

    void prompt();

    bool ready;
    bool auth_failed;

  private:
    void onMessage(const ix::WebSocketMessagePtr& msg);
  };

}  // namespace wsclient
