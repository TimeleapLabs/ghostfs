@0x8c71ca72d09e0229;

using import "write.capnp".Write;
using import "write.response.capnp".WriteResponse;
using import "read.capnp".Read;
using import "read.response.capnp".ReadResponse;

interface GhostFS {
  write @0 (req :Write) -> (res :WriteResponse);
  read  @1 (req :Read)  -> (res :ReadResponse);
}
