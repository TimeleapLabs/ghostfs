@0xef3cbdc7f570b4f3;

struct Getattr {
  ino   @0 :UInt64;
  fi    @1 :FuseFileInfo;

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
