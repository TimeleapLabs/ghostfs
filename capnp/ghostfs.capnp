@0x8c71ca72d09e0229;

using import "lookup.capnp".Lookup;
using import "lookup.response.capnp".LookupResponse;
using import "getattr.capnp".Getattr;
using import "getattr.response.capnp".GetattrResponse;
using import "setattr.capnp".Setattr;
using import "setattr.response.capnp".SetattrResponse;
using import "mknod.capnp".Mknod;
using import "mknod.response.capnp".MknodResponse;
using import "mkdir.capnp".Mkdir;
using import "mkdir.response.capnp".MkdirResponse;
using import "unlink.capnp".Unlink;
using import "unlink.response.capnp".UnlinkResponse;
using import "rmdir.capnp".Rmdir;
using import "rmdir.response.capnp".RmdirResponse;
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
  mknod   @3 (req :Mknod)   -> (res :MknodResponse);
  mkdir   @4 (req :Mkdir)   -> (res :MkdirResponse);
  unlink  @5 (req :Unlink)  -> (res :UnlinkResponse);
  rmdir   @6 (req :Rmdir)   -> (res :RmdirResponse);
  read    @7 (req :Read)    -> (res :ReadResponse);
  write   @8 (req :Write)   -> (res :WriteResponse);
  create  @9 (req :Create)  -> (res :CreateResponse);
}
