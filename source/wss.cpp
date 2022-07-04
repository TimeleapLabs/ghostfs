
#include <fmt/format.h>
#include <ghostfs/fs.h>
#include <ghostfs/wss.h>

// Cap'n'Proto

#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <getattr.capnp.h>
#include <lookup.capnp.h>
#include <readdir.capnp.h>

#include <iostream>

using namespace wsserver;

WSServer::WSServer(int _port) : port(std::move(_port)) {}

void WSServer::start() {
  // Start the server on port
  ix::WebSocketServer server(port);

  std::cout << "Starting the server on port " << port << "..." << std::endl;

  // Setup a callback to be fired (in a background thread, watch out for race conditions !)
  // when a message or an event (open, close, error) is received
  server.setOnClientMessageCallback(
      [this](std::shared_ptr<ix::ConnectionState> connectionState, ix::WebSocket& webSocket,
             const ix::WebSocketMessagePtr& msg) { onMessage(connectionState, webSocket, msg); });

  auto res = server.listen(); /*
   if (!res.first) {
     // Error handling
     return 1;
   } */

  // Per message deflate connection is enabled by default. It can be disabled
  // which might be helpful when running on low power devices such as a Rasbery Pi
  server.disablePerMessageDeflate();

  // Run the server in the background. Server can be stoped by calling server.stop()
  server.start();

  // Block until server.stop() is called.
  server.wait();
}

void WSServer::onMessage(std::shared_ptr<ix::ConnectionState> connectionState,
                         ix::WebSocket& webSocket, const ix::WebSocketMessagePtr& msg) {
  // std::cout << "Remote ip: " << connectionState->getRemoteIp() << std::endl;

  if (msg->type == ix::WebSocketMessageType::Open) {
    // std::cout << "New connection" << std::endl;

    // // A connection state object is available, and has a default id
    // // You can subclass ConnectionState and pass an alternate factory
    // // to override it. It is useful if you want to store custom
    // // attributes per connection (authenticated bool flag, attributes, etc...)
    // std::cout << "id: " << connectionState->getId() << std::endl;

    // // The uri the client did connect to.
    // std::cout << "Uri: " << msg->openInfo.uri << std::endl;

    // std::cout << "Headers:" << std::endl;
    // for (auto it : msg->openInfo.headers) {
    //   std::cout << "\t" << it.first << ": " << it.second << std::endl;
    // }
  } else if (msg->type == ix::WebSocketMessageType::Message) {
    // For an echo server, we just send back to the client whatever was received by the server
    // All connected clients are available in an std::set. See the broadcast cpp example.
    // Second parameter tells whether we are sending the message in binary or text mode.
    // Here we send it in the same mode as it was received.
    // std::cout << "Received: " << msg->str << std::endl;

    // webSocket.send(msg->str, msg->binary);

    const char command = msg->str[0];
    std::string payload = msg->str.substr(1);

    switch (command) {
      case '1': {
        const kj::ArrayPtr<const capnp::word> view(
            reinterpret_cast<const capnp::word*>(&(*std::begin(payload))),
            reinterpret_cast<const capnp::word*>(&(*std::end(payload))));

        capnp::FlatArrayMessageReader data(view);
        Getattr::Reader getattr = data.getRoot<Getattr>();

        std::cout << "Lookup: " << getattr.getIno() << std::endl;

        break;
      }

      default:
        break;
    }
  }
}