"use strict";
/* tslint:disable */

import capnp from "capnp-ts";
export const capnpFileId = "a8566d6a8911c127";
export class TokenRequest extends capnp.Struct {
  getUser() {
    return capnp.Struct.getText(0, this);
  }
  setUser(value) {
    capnp.Struct.setText(0, value, this);
  }
  getToken() {
    return capnp.Struct.getText(1, this);
  }
  setToken(value) {
    capnp.Struct.setText(1, value, this);
  }
  getRetries() {
    return capnp.Struct.getInt64(0, this);
  }
  setRetries(value) {
    capnp.Struct.setInt64(0, value, this);
  }
  getExpires() {
    return capnp.Struct.getUint64(8, this);
  }
  setExpires(value) {
    capnp.Struct.setUint64(8, value, this);
  }
  toString() {
    return "TokenRequest_" + super.toString();
  }
}
TokenRequest._capnp = {
  displayName: "TokenRequest",
  id: "f2d65642358a3480",
  size: new capnp.ObjectSize(16, 2),
};
