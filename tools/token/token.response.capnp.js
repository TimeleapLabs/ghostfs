"use strict";
/* tslint:disable */
import capnp from "capnp-ts";

export const capnpFileId = "a637d8f1c766c1c1";

export class TokenResponse extends capnp.Struct {
  getToken() {
    return capnp.Struct.getText(0, this);
  }
  setToken(value) {
    capnp.Struct.setText(0, value, this);
  }
  toString() {
    return "TokenResponse_" + super.toString();
  }
}

TokenResponse._capnp = {
  displayName: "TokenResponse",
  id: "fac1e640cc81ca25",
  size: new capnp.ObjectSize(0, 1),
};
