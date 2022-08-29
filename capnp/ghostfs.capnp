@0x8c71ca72d09e0229;

using import "write.capnp".Write;
using import "write.response.capnp".WriteResponse;

interface GhostFS {
  write @0 (req :Write) -> (res :WriteResponse);
}
