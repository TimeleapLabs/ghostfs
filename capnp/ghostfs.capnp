@0x8c71ca72d09e0229;

using import "lookup.capnp".Lookup;
using import "lookup.response.capnp".LookupResponse;
using import "getattr.capnp".Getattr;
using import "getattr.response.capnp".GetattrResponse;
using import "setattr.capnp".Setattr;
using import "setattr.response.capnp".SetattrResponse;
using import "read.capnp".Read;
using import "read.response.capnp".ReadResponse;
using import "write.capnp".Write;
using import "write.response.capnp".WriteResponse;
using import "create.capnp".Create;
using import "create.response.capnp".CreateResponse;

interface GhostFSAuth {
  auth @0 (user :Text, token :Text) -> (ghostFs: GhostFS);
}

interface GhostFS {
  lookup  @0 (req :Lookup)  -> (res :LookupResponse);
  getattr @1 (req :Getattr) -> (res :GetattrResponse);
  setattr @2 (req :Setattr) -> (res :SetattrResponse);
  read    @3 (req :Read)    -> (res :ReadResponse);
  write   @4 (req :Write)   -> (res :WriteResponse);
  create  @5 (req :Create)  -> (res :CreateResponse);
}
