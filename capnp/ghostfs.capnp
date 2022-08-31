@0x8c71ca72d09e0229;

using import "lookup.capnp".Lookup;
using import "lookup.response.capnp".LookupResponse;
using import "getattr.capnp".Getattr;
using import "getattr.response.capnp".GetattrResponse;
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
  read    @2 (req :Read)    -> (res :ReadResponse);
  write   @3 (req :Write)   -> (res :WriteResponse);
  create  @4 (req :Create)  -> (res :CreateResponse);
}
