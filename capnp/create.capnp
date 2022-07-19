@0x8498de5aabb5a54e;

struct Create {
  parent @0 :UInt64;
  name   @1 :Text;
  mode   @2 :UInt64;
  fi     @3 :FuseFileInfo;
  uuid   @4 :Text;

  struct FuseFileInfo {
    flags         @0  :Int8;
    writepage     @1  :UInt64;
    directIo      @2  :UInt64;
    keepCache     @3  :UInt64;
    flush         @4  :UInt64;
    nonseekable   @5  :UInt64;
    cacheReaddir  @6  :UInt64;
    padding       @7  :UInt64;
    fh            @8  :UInt64;
    lockOwner     @9  :UInt64;
    pollEvents    @10 :UInt32;
    noflush       @11 :UInt64;
  }
}