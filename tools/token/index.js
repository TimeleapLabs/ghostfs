import capnp from "capnp-ts";
import WebSocket from "ws";
import minimist from "minimist";
import { TokenRequest } from "./token.capnp.js";
import { TokenResponse } from "./token.response.capnp.js";

const { user, retries = "1" } = minimist(process.argv);

console.log({ user, retries });

const ws = new WebSocket("ws://localhost:3445", {
  perMessageDeflate: false,
});

ws.on("message", (data) => {
  const message = new capnp.Message(data, false);
  const response = message.getRoot(TokenResponse);
  console.log(response.getToken());
  process.exit(0);
});

ws.on("open", () => {
  const message = new capnp.Message();
  const request = message.getRoot(TokenRequest);
  request.setRetries(capnp.Int64.fromNumber(Number(retries)));
  request.setUser(user);

  const payload = message.toArrayBuffer();
  ws.send(payload, { binary: true });
});
