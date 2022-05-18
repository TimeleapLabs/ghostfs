#include <fmt/format.h>
#include <ghostfs/ws.h>

#include <iostream>

using namespace wsclient;

WSClient::WSClient(std::string _url) : url(std::move(_url)) {
  // Connect to a server with encryption
  // See https://machinezone.github.io/IXWebSocket/usage/#tls-support-and-configuration
  // std::string url("ws://localhost:3444");
  webSocket.setUrl(url);

  std::cout << "Connecting to " << url << "..." << std::endl;

  // Setup a callback to be fired (in a background thread, watch out for race conditions !)
  // when a message or an event (open, close, error) is received
  webSocket.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg) { onMessage(msg); });

  // Now that our callback is setup, we can start our background thread and receive messages
  webSocket.start();

  // Send a message to the server (default to TEXT mode)
  webSocket.send("hello world");
}

void WSClient::send(std::string message) { webSocket.send(message); }

void WSClient::prompt() {
  // Display a prompt
  std::cout << "> " << std::flush;

  std::string text;
  // Read text from the console and send messages in text mode.
  // Exit with Ctrl-D on Unix or Ctrl-Z on Windows.
  while (std::getline(std::cin, text)) {
    webSocket.send(text);
    std::cout << "> " << std::flush;
  }
}

void WSClient::onMessage(const ix::WebSocketMessagePtr& msg) {
  if (msg->type == ix::WebSocketMessageType::Message) {
    std::cout << "received message: " << msg->str << std::endl;
    std::cout << "> " << std::flush;
  } else if (msg->type == ix::WebSocketMessageType::Open) {
    std::cout << "Connection established" << std::endl;
    std::cout << "> " << std::flush;
  } else if (msg->type == ix::WebSocketMessageType::Error) {
    // Maybe SSL is not configured properly
    std::cout << "Connection error: " << msg->errorInfo.reason << std::endl;
    std::cout << "> " << std::flush;
  }
}
