#include <auth.capnp.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <fmt/format.h>
#include <ghostfs/fs.h>
#include <ghostfs/ws.h>

#include <iostream>

using namespace wsclient;

WSClient::WSClient(std::string _url, std::string _user, std::string _token)
    : url(std::move(_url)), user(std::move(_user)), token(std::move(_token)) {
  // Connect to a server with encryption
  // See https://machinezone.github.io/IXWebSocket/usage/#tls-support-and-configuration
  // std::string url("ws://localhost:3444");

  ready = false;
  auth_failed = false;

  webSocket.setUrl(url);

  std::cout << "Connecting to " << url << "..." << std::endl;

  // Setup a callback to be fired (in a background thread, watch out for race conditions !)
  // when a message or an event (open, close, error) is received
  webSocket.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg) { onMessage(msg); });

  // Now that our callback is setup, we can start our background thread and receive messages
  webSocket.start();

  // Send a message to the server (default to TEXT mode)
  // webSocket.send("hello world");
}

void WSClient::send(std::string message) { webSocket.send(message, true); }
void WSClient::sendBinary(char* message) { webSocket.sendBinary(message); }

void WSClient::prompt() {
  // Display a prompt
  // std::cout << "> " << std::flush;

  std::string text;
  // Read text from the console and send messages in text mode.
  // Exit with Ctrl-D on Unix or Ctrl-Z on Windows.
  while (std::getline(std::cin, text)) {
    webSocket.send(text);
    // std::cout << "> " << std::flush;
  }
}

void WSClient::onMessage(const ix::WebSocketMessagePtr& msg) {
  if (msg->type == ix::WebSocketMessageType::Message) {
    // std::cout << "received message: " << msg->str << std::endl;
    // std::cout << "> " << std::flush;
    const char command = msg->str[0];
    std::string payload = msg->str.substr(1);

    switch (command) {
      case (char)Ops::Auth: {
        process_auth_response(payload, this);
        break;
      }
      case (char)Ops::Getattr: {
        process_getattr_response(payload);
        break;
      }
      case (char)Ops::Lookup: {
        process_lookup_response(payload);
        break;
      }
      case (char)Ops::Readdir: {
        process_readdir_response(payload);
        break;
      }
      case (char)Ops::Open: {
        process_open_response(payload);
        break;
      }
      case (char)Ops::Read: {
        process_read_response(payload);
        break;
      }
      case (char)Ops::Setattr: {
        process_setattr_response(payload);
        break;
      }
      case (char)Ops::Write: {
        process_write_response(payload);
        break;
      }
      case (char)Ops::Setxattr: {
        process_setxattr_response(payload);
        break;
      }
      case (char)Ops::Create: {
        process_create_response(payload);
        break;
      }
      case (char)Ops::Mknod: {
        process_mknod_response(payload);
        break;
      }
      case (char)Ops::Mkdir: {
        process_mkdir_response(payload);
        break;
      }
      case (char)Ops::Unlink: {
        process_unlink_response(payload);
        break;
      }
      case (char)Ops::Rmdir: {
        process_rmdir_response(payload);
        break;
      }
      case (char)Ops::Rename: {
        process_rename_response(payload);
        break;
      }
      case (char)Ops::Release: {
        process_release_response(payload);
        break;
      }
      default:
        break;
    }

  } else if (msg->type == ix::WebSocketMessageType::Close) {
    std::cout << "Connection closed with error code " << msg->closeInfo.code << ": "
              << msg->closeInfo.reason << std::endl;
  } else if (msg->type == ix::WebSocketMessageType::Open) {
    std::cout << "Connection established" << std::endl;

    ::capnp::MallocMessageBuilder message;
    Auth::Builder auth = message.initRoot<Auth>();

    auth.setUser(user);
    auth.setToken(token);

    const auto data = capnp::messageToFlatArray(message);
    const auto bytes = data.asBytes();

    std::string payload(bytes.begin(), bytes.end());
    send((char)Ops::Auth + payload);

    // std::cout << "> " << std::flush;
  } else if (msg->type == ix::WebSocketMessageType::Error) {
    // Maybe SSL is not configured properly
    std::cout << "Connection error: " << msg->errorInfo.reason << std::endl;
    // std::cout << "> " << std::flush;
  }
}
