@0xd00f26fee8790f3e;

struct Readdir {
  ino   @0 :UInt64;
  size  @1 :UInt64;
  off   @2 :Int64;
  fi    @3 :FuseFileInfo;

  struct FuseFileInfo {
    flags         @0  :Int64;
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
