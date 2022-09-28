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
using import "symlink.capnp".Symlink;
using import "symlink.response.capnp".SymlinkResponse;
using import "rename.capnp".Rename;
using import "rename.response.capnp".RenameResponse;
using import "open.capnp".Open;
using import "open.response.capnp".OpenResponse;
using import "read.capnp".Read;
using import "read.response.capnp".ReadResponse;
using import "write.capnp".Write;
using import "write.response.capnp".WriteResponse;
using import "release.capnp".Release;
using import "release.response.capnp".ReleaseResponse;
using import "readdir.capnp".Readdir;
using import "readdir.response.capnp".ReaddirResponse;
using import "setxattr.capnp".Setxattr;
using import "setxattr.response.capnp".SetxattrResponse;
using import "access.capnp".Access;
using import "access.response.capnp".AccessResponse;
using import "create.capnp".Create;
using import "create.response.capnp".CreateResponse;
using import "flush.capnp".Flush;
using import "flush.response.capnp".FlushResponse;
using import "fsync.capnp".Fsync;
using import "fsync.response.capnp".FsyncResponse;

interface GhostFSAuthServer {
  authorize   @0 (user :Text, token :Text, retries :Int64, expires :UInt64) -> (token :Text);
  mount       @1 (user :Text, source :Text, destination :Text) -> (success :Bool);
  mounts      @2 (user :Text) -> (mounts :List(Text));
  unmount     @3 (user :Text, destination :Text) -> (success :Bool);
  unmountAll  @4 (user :Text) -> (success :Bool);
}

interface GhostFSAuth {
  auth    @0 (user :Text, token :Text) -> (ghostFs :GhostFS, authSuccess :Bool);
}

interface GhostFS {
  lookup   @0  (req :Lookup)   -> (res :LookupResponse);
  getattr  @1  (req :Getattr)  -> (res :GetattrResponse);
  setattr  @2  (req :Setattr)  -> (res :SetattrResponse);
  mknod    @3  (req :Mknod)    -> (res :MknodResponse);
  mkdir    @4  (req :Mkdir)    -> (res :MkdirResponse);
  unlink   @5  (req :Unlink)   -> (res :UnlinkResponse);
  rmdir    @6  (req :Rmdir)    -> (res :RmdirResponse);
  symlink  @7  (req :Symlink)  -> (res :SymlinkResponse);
  rename   @8  (req :Rename)   -> (res :RenameResponse);
  open     @9  (req :Open)     -> (res :OpenResponse);
  read     @10  (req :Read)    -> (res :ReadResponse);
  write    @11 (req :Write)    -> (res :WriteResponse);
  release  @12 (req :Release)  -> (res :ReleaseResponse);
  readdir  @13 (req :Readdir)  -> (res :ReaddirResponse);
  setxattr @14 (req :Setxattr) -> (res :SetxattrResponse);
  access   @15 (req :Access)   -> (res :AccessResponse);
  create   @16 (req :Create)   -> (res :CreateResponse);
  flush    @17 (req :Flush)    -> (res :FlushResponse);
  fsync    @18 (req :Fsync)    -> (res :FsyncResponse);
  
  # Special methods (non-fuse)
  bulkWrite @19 (req :List(Write))         -> (res :List(WriteResponse));
}
