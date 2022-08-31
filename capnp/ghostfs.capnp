@0x8c71ca72d09e0229;

using import "lookup.capnp".Lookup;
using import "lookup.response.capnp".LookupResponse;
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
  read    @1 (req :Read)    -> (res :ReadResponse);
  write   @2 (req :Write)   -> (res :WriteResponse);
  create  @3 (req :Create)  -> (res :CreateResponse);
}
