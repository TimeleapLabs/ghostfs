// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: setattr.capnp

#pragma once

#include <capnp/generated-header-support.h>
#include <kj/windows-sanity.h>

#if CAPNP_VERSION != 10002
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif


CAPNP_BEGIN_HEADER

namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(b84ce6026075f673);
CAPNP_DECLARE_SCHEMA(a44457e54375dcde);
CAPNP_DECLARE_SCHEMA(8031379ba6928a60);
CAPNP_DECLARE_SCHEMA(f31d765ee6c1ba61);

}  // namespace schemas
}  // namespace capnp


struct Setattr {
  Setattr() = delete;

  class Reader;
  class Builder;
  class Pipeline;
  struct Attr;
  struct FuseFileInfo;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(b84ce6026075f673, 2, 3)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

struct Setattr::Attr {
  Attr() = delete;

  class Reader;
  class Builder;
  class Pipeline;
  struct TimeSpec;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(a44457e54375dcde, 9, 2)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

struct Setattr::Attr::TimeSpec {
  TimeSpec() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(8031379ba6928a60, 2, 0)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

struct Setattr::FuseFileInfo {
  FuseFileInfo() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(f31d765ee6c1ba61, 11, 0)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class Setattr::Reader {
public:
  typedef Setattr Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

  inline  ::uint64_t getIno() const;

  inline bool hasAttr() const;
  inline  ::Setattr::Attr::Reader getAttr() const;

  inline  ::int64_t getToSet() const;

  inline bool hasFi() const;
  inline  ::Setattr::FuseFileInfo::Reader getFi() const;

  inline bool hasUuid() const;
  inline  ::capnp::Text::Reader getUuid() const;

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class Setattr::Builder {
public:
  typedef Setattr Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline  ::uint64_t getIno();
  inline void setIno( ::uint64_t value);

  inline bool hasAttr();
  inline  ::Setattr::Attr::Builder getAttr();
  inline void setAttr( ::Setattr::Attr::Reader value);
  inline  ::Setattr::Attr::Builder initAttr();
  inline void adoptAttr(::capnp::Orphan< ::Setattr::Attr>&& value);
  inline ::capnp::Orphan< ::Setattr::Attr> disownAttr();

  inline  ::int64_t getToSet();
  inline void setToSet( ::int64_t value);

  inline bool hasFi();
  inline  ::Setattr::FuseFileInfo::Builder getFi();
  inline void setFi( ::Setattr::FuseFileInfo::Reader value);
  inline  ::Setattr::FuseFileInfo::Builder initFi();
  inline void adoptFi(::capnp::Orphan< ::Setattr::FuseFileInfo>&& value);
  inline ::capnp::Orphan< ::Setattr::FuseFileInfo> disownFi();

  inline bool hasUuid();
  inline  ::capnp::Text::Builder getUuid();
  inline void setUuid( ::capnp::Text::Reader value);
  inline  ::capnp::Text::Builder initUuid(unsigned int size);
  inline void adoptUuid(::capnp::Orphan< ::capnp::Text>&& value);
  inline ::capnp::Orphan< ::capnp::Text> disownUuid();

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Setattr::Pipeline {
public:
  typedef Setattr Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

  inline  ::Setattr::Attr::Pipeline getAttr();
  inline  ::Setattr::FuseFileInfo::Pipeline getFi();
private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

class Setattr::Attr::Reader {
public:
  typedef Attr Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

  inline  ::uint16_t getStDev() const;

  inline  ::uint64_t getStIno() const;

  inline  ::uint64_t getStMode() const;

  inline  ::uint16_t getStNlink() const;

  inline  ::int64_t getStUid() const;

  inline  ::int64_t getStGid() const;

  inline  ::uint16_t getStRdev() const;

  inline  ::int64_t getStSize() const;

  inline bool hasStAtime() const;
  inline  ::Setattr::Attr::TimeSpec::Reader getStAtime() const;

  inline bool hasStMtime() const;
  inline  ::Setattr::Attr::TimeSpec::Reader getStMtime() const;

  inline  ::int64_t getStCtime() const;

  inline  ::uint64_t getStBlksize() const;

  inline  ::uint64_t getStBlocks() const;

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class Setattr::Attr::Builder {
public:
  typedef Attr Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline  ::uint16_t getStDev();
  inline void setStDev( ::uint16_t value);

  inline  ::uint64_t getStIno();
  inline void setStIno( ::uint64_t value);

  inline  ::uint64_t getStMode();
  inline void setStMode( ::uint64_t value);

  inline  ::uint16_t getStNlink();
  inline void setStNlink( ::uint16_t value);

  inline  ::int64_t getStUid();
  inline void setStUid( ::int64_t value);

  inline  ::int64_t getStGid();
  inline void setStGid( ::int64_t value);

  inline  ::uint16_t getStRdev();
  inline void setStRdev( ::uint16_t value);

  inline  ::int64_t getStSize();
  inline void setStSize( ::int64_t value);

  inline bool hasStAtime();
  inline  ::Setattr::Attr::TimeSpec::Builder getStAtime();
  inline void setStAtime( ::Setattr::Attr::TimeSpec::Reader value);
  inline  ::Setattr::Attr::TimeSpec::Builder initStAtime();
  inline void adoptStAtime(::capnp::Orphan< ::Setattr::Attr::TimeSpec>&& value);
  inline ::capnp::Orphan< ::Setattr::Attr::TimeSpec> disownStAtime();

  inline bool hasStMtime();
  inline  ::Setattr::Attr::TimeSpec::Builder getStMtime();
  inline void setStMtime( ::Setattr::Attr::TimeSpec::Reader value);
  inline  ::Setattr::Attr::TimeSpec::Builder initStMtime();
  inline void adoptStMtime(::capnp::Orphan< ::Setattr::Attr::TimeSpec>&& value);
  inline ::capnp::Orphan< ::Setattr::Attr::TimeSpec> disownStMtime();

  inline  ::int64_t getStCtime();
  inline void setStCtime( ::int64_t value);

  inline  ::uint64_t getStBlksize();
  inline void setStBlksize( ::uint64_t value);

  inline  ::uint64_t getStBlocks();
  inline void setStBlocks( ::uint64_t value);

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Setattr::Attr::Pipeline {
public:
  typedef Attr Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

  inline  ::Setattr::Attr::TimeSpec::Pipeline getStAtime();
  inline  ::Setattr::Attr::TimeSpec::Pipeline getStMtime();
private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

class Setattr::Attr::TimeSpec::Reader {
public:
  typedef TimeSpec Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

  inline  ::int64_t getTvSec() const;

  inline  ::int64_t getTvNSec() const;

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class Setattr::Attr::TimeSpec::Builder {
public:
  typedef TimeSpec Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline  ::int64_t getTvSec();
  inline void setTvSec( ::int64_t value);

  inline  ::int64_t getTvNSec();
  inline void setTvNSec( ::int64_t value);

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Setattr::Attr::TimeSpec::Pipeline {
public:
  typedef TimeSpec Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

class Setattr::FuseFileInfo::Reader {
public:
  typedef FuseFileInfo Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

  inline  ::int8_t getFlags() const;

  inline  ::uint64_t getWritepage() const;

  inline  ::uint64_t getDirectIo() const;

  inline  ::uint64_t getKeepCache() const;

  inline  ::uint64_t getFlush() const;

  inline  ::uint64_t getNonseekable() const;

  inline  ::uint64_t getCacheReaddir() const;

  inline  ::uint64_t getPadding() const;

  inline  ::uint64_t getFh() const;

  inline  ::uint64_t getLockOwner() const;

  inline  ::uint32_t getPollEvents() const;

  inline  ::uint64_t getNoflush() const;

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class Setattr::FuseFileInfo::Builder {
public:
  typedef FuseFileInfo Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline  ::int8_t getFlags();
  inline void setFlags( ::int8_t value);

  inline  ::uint64_t getWritepage();
  inline void setWritepage( ::uint64_t value);

  inline  ::uint64_t getDirectIo();
  inline void setDirectIo( ::uint64_t value);

  inline  ::uint64_t getKeepCache();
  inline void setKeepCache( ::uint64_t value);

  inline  ::uint64_t getFlush();
  inline void setFlush( ::uint64_t value);

  inline  ::uint64_t getNonseekable();
  inline void setNonseekable( ::uint64_t value);

  inline  ::uint64_t getCacheReaddir();
  inline void setCacheReaddir( ::uint64_t value);

  inline  ::uint64_t getPadding();
  inline void setPadding( ::uint64_t value);

  inline  ::uint64_t getFh();
  inline void setFh( ::uint64_t value);

  inline  ::uint64_t getLockOwner();
  inline void setLockOwner( ::uint64_t value);

  inline  ::uint32_t getPollEvents();
  inline void setPollEvents( ::uint32_t value);

  inline  ::uint64_t getNoflush();
  inline void setNoflush( ::uint64_t value);

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Setattr::FuseFileInfo::Pipeline {
public:
  typedef FuseFileInfo Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

// =======================================================================================

inline  ::uint64_t Setattr::Reader::getIno() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::Builder::getIno() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Setattr::Builder::setIno( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline bool Setattr::Reader::hasAttr() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool Setattr::Builder::hasAttr() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline  ::Setattr::Attr::Reader Setattr::Reader::getAttr() const {
  return ::capnp::_::PointerHelpers< ::Setattr::Attr>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::Setattr::Attr::Builder Setattr::Builder::getAttr() {
  return ::capnp::_::PointerHelpers< ::Setattr::Attr>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::Setattr::Attr::Pipeline Setattr::Pipeline::getAttr() {
  return  ::Setattr::Attr::Pipeline(_typeless.getPointerField(0));
}
#endif  // !CAPNP_LITE
inline void Setattr::Builder::setAttr( ::Setattr::Attr::Reader value) {
  ::capnp::_::PointerHelpers< ::Setattr::Attr>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), value);
}
inline  ::Setattr::Attr::Builder Setattr::Builder::initAttr() {
  return ::capnp::_::PointerHelpers< ::Setattr::Attr>::init(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline void Setattr::Builder::adoptAttr(
    ::capnp::Orphan< ::Setattr::Attr>&& value) {
  ::capnp::_::PointerHelpers< ::Setattr::Attr>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::Setattr::Attr> Setattr::Builder::disownAttr() {
  return ::capnp::_::PointerHelpers< ::Setattr::Attr>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}

inline  ::int64_t Setattr::Reader::getToSet() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::int64_t Setattr::Builder::getToSet() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Setattr::Builder::setToSet( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline bool Setattr::Reader::hasFi() const {
  return !_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline bool Setattr::Builder::hasFi() {
  return !_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline  ::Setattr::FuseFileInfo::Reader Setattr::Reader::getFi() const {
  return ::capnp::_::PointerHelpers< ::Setattr::FuseFileInfo>::get(_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline  ::Setattr::FuseFileInfo::Builder Setattr::Builder::getFi() {
  return ::capnp::_::PointerHelpers< ::Setattr::FuseFileInfo>::get(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::Setattr::FuseFileInfo::Pipeline Setattr::Pipeline::getFi() {
  return  ::Setattr::FuseFileInfo::Pipeline(_typeless.getPointerField(1));
}
#endif  // !CAPNP_LITE
inline void Setattr::Builder::setFi( ::Setattr::FuseFileInfo::Reader value) {
  ::capnp::_::PointerHelpers< ::Setattr::FuseFileInfo>::set(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), value);
}
inline  ::Setattr::FuseFileInfo::Builder Setattr::Builder::initFi() {
  return ::capnp::_::PointerHelpers< ::Setattr::FuseFileInfo>::init(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline void Setattr::Builder::adoptFi(
    ::capnp::Orphan< ::Setattr::FuseFileInfo>&& value) {
  ::capnp::_::PointerHelpers< ::Setattr::FuseFileInfo>::adopt(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::Setattr::FuseFileInfo> Setattr::Builder::disownFi() {
  return ::capnp::_::PointerHelpers< ::Setattr::FuseFileInfo>::disown(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}

inline bool Setattr::Reader::hasUuid() const {
  return !_reader.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS).isNull();
}
inline bool Setattr::Builder::hasUuid() {
  return !_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::Text::Reader Setattr::Reader::getUuid() const {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_reader.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
inline  ::capnp::Text::Builder Setattr::Builder::getUuid() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
inline void Setattr::Builder::setUuid( ::capnp::Text::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::set(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), value);
}
inline  ::capnp::Text::Builder Setattr::Builder::initUuid(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::init(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), size);
}
inline void Setattr::Builder::adoptUuid(
    ::capnp::Orphan< ::capnp::Text>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::adopt(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::Text> Setattr::Builder::disownUuid() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::disown(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}

inline  ::uint16_t Setattr::Attr::Reader::getStDev() const {
  return _reader.getDataField< ::uint16_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::uint16_t Setattr::Attr::Builder::getStDev() {
  return _builder.getDataField< ::uint16_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Setattr::Attr::Builder::setStDev( ::uint16_t value) {
  _builder.setDataField< ::uint16_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::Attr::Reader::getStIno() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::Attr::Builder::getStIno() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Setattr::Attr::Builder::setStIno( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::Attr::Reader::getStMode() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::Attr::Builder::getStMode() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}
inline void Setattr::Attr::Builder::setStMode( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS, value);
}

inline  ::uint16_t Setattr::Attr::Reader::getStNlink() const {
  return _reader.getDataField< ::uint16_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint16_t Setattr::Attr::Builder::getStNlink() {
  return _builder.getDataField< ::uint16_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Setattr::Attr::Builder::setStNlink( ::uint16_t value) {
  _builder.setDataField< ::uint16_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t Setattr::Attr::Reader::getStUid() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}

inline  ::int64_t Setattr::Attr::Builder::getStUid() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}
inline void Setattr::Attr::Builder::setStUid( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t Setattr::Attr::Reader::getStGid() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}

inline  ::int64_t Setattr::Attr::Builder::getStGid() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}
inline void Setattr::Attr::Builder::setStGid( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS, value);
}

inline  ::uint16_t Setattr::Attr::Reader::getStRdev() const {
  return _reader.getDataField< ::uint16_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}

inline  ::uint16_t Setattr::Attr::Builder::getStRdev() {
  return _builder.getDataField< ::uint16_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}
inline void Setattr::Attr::Builder::setStRdev( ::uint16_t value) {
  _builder.setDataField< ::uint16_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t Setattr::Attr::Reader::getStSize() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}

inline  ::int64_t Setattr::Attr::Builder::getStSize() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}
inline void Setattr::Attr::Builder::setStSize( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS, value);
}

inline bool Setattr::Attr::Reader::hasStAtime() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool Setattr::Attr::Builder::hasStAtime() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline  ::Setattr::Attr::TimeSpec::Reader Setattr::Attr::Reader::getStAtime() const {
  return ::capnp::_::PointerHelpers< ::Setattr::Attr::TimeSpec>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::Setattr::Attr::TimeSpec::Builder Setattr::Attr::Builder::getStAtime() {
  return ::capnp::_::PointerHelpers< ::Setattr::Attr::TimeSpec>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::Setattr::Attr::TimeSpec::Pipeline Setattr::Attr::Pipeline::getStAtime() {
  return  ::Setattr::Attr::TimeSpec::Pipeline(_typeless.getPointerField(0));
}
#endif  // !CAPNP_LITE
inline void Setattr::Attr::Builder::setStAtime( ::Setattr::Attr::TimeSpec::Reader value) {
  ::capnp::_::PointerHelpers< ::Setattr::Attr::TimeSpec>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), value);
}
inline  ::Setattr::Attr::TimeSpec::Builder Setattr::Attr::Builder::initStAtime() {
  return ::capnp::_::PointerHelpers< ::Setattr::Attr::TimeSpec>::init(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline void Setattr::Attr::Builder::adoptStAtime(
    ::capnp::Orphan< ::Setattr::Attr::TimeSpec>&& value) {
  ::capnp::_::PointerHelpers< ::Setattr::Attr::TimeSpec>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::Setattr::Attr::TimeSpec> Setattr::Attr::Builder::disownStAtime() {
  return ::capnp::_::PointerHelpers< ::Setattr::Attr::TimeSpec>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}

inline bool Setattr::Attr::Reader::hasStMtime() const {
  return !_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline bool Setattr::Attr::Builder::hasStMtime() {
  return !_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline  ::Setattr::Attr::TimeSpec::Reader Setattr::Attr::Reader::getStMtime() const {
  return ::capnp::_::PointerHelpers< ::Setattr::Attr::TimeSpec>::get(_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline  ::Setattr::Attr::TimeSpec::Builder Setattr::Attr::Builder::getStMtime() {
  return ::capnp::_::PointerHelpers< ::Setattr::Attr::TimeSpec>::get(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::Setattr::Attr::TimeSpec::Pipeline Setattr::Attr::Pipeline::getStMtime() {
  return  ::Setattr::Attr::TimeSpec::Pipeline(_typeless.getPointerField(1));
}
#endif  // !CAPNP_LITE
inline void Setattr::Attr::Builder::setStMtime( ::Setattr::Attr::TimeSpec::Reader value) {
  ::capnp::_::PointerHelpers< ::Setattr::Attr::TimeSpec>::set(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), value);
}
inline  ::Setattr::Attr::TimeSpec::Builder Setattr::Attr::Builder::initStMtime() {
  return ::capnp::_::PointerHelpers< ::Setattr::Attr::TimeSpec>::init(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline void Setattr::Attr::Builder::adoptStMtime(
    ::capnp::Orphan< ::Setattr::Attr::TimeSpec>&& value) {
  ::capnp::_::PointerHelpers< ::Setattr::Attr::TimeSpec>::adopt(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::Setattr::Attr::TimeSpec> Setattr::Attr::Builder::disownStMtime() {
  return ::capnp::_::PointerHelpers< ::Setattr::Attr::TimeSpec>::disown(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}

inline  ::int64_t Setattr::Attr::Reader::getStCtime() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}

inline  ::int64_t Setattr::Attr::Builder::getStCtime() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}
inline void Setattr::Attr::Builder::setStCtime( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::Attr::Reader::getStBlksize() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::Attr::Builder::getStBlksize() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}
inline void Setattr::Attr::Builder::setStBlksize( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::Attr::Reader::getStBlocks() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::Attr::Builder::getStBlocks() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}
inline void Setattr::Attr::Builder::setStBlocks( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t Setattr::Attr::TimeSpec::Reader::getTvSec() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::int64_t Setattr::Attr::TimeSpec::Builder::getTvSec() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Setattr::Attr::TimeSpec::Builder::setTvSec( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t Setattr::Attr::TimeSpec::Reader::getTvNSec() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::int64_t Setattr::Attr::TimeSpec::Builder::getTvNSec() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Setattr::Attr::TimeSpec::Builder::setTvNSec( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::int8_t Setattr::FuseFileInfo::Reader::getFlags() const {
  return _reader.getDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::int8_t Setattr::FuseFileInfo::Builder::getFlags() {
  return _builder.getDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Setattr::FuseFileInfo::Builder::setFlags( ::int8_t value) {
  _builder.setDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::FuseFileInfo::Reader::getWritepage() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::FuseFileInfo::Builder::getWritepage() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Setattr::FuseFileInfo::Builder::setWritepage( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::FuseFileInfo::Reader::getDirectIo() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::FuseFileInfo::Builder::getDirectIo() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}
inline void Setattr::FuseFileInfo::Builder::setDirectIo( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::FuseFileInfo::Reader::getKeepCache() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::FuseFileInfo::Builder::getKeepCache() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}
inline void Setattr::FuseFileInfo::Builder::setKeepCache( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::FuseFileInfo::Reader::getFlush() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::FuseFileInfo::Builder::getFlush() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}
inline void Setattr::FuseFileInfo::Builder::setFlush( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::FuseFileInfo::Reader::getNonseekable() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::FuseFileInfo::Builder::getNonseekable() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}
inline void Setattr::FuseFileInfo::Builder::setNonseekable( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::FuseFileInfo::Reader::getCacheReaddir() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::FuseFileInfo::Builder::getCacheReaddir() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}
inline void Setattr::FuseFileInfo::Builder::setCacheReaddir( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::FuseFileInfo::Reader::getPadding() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::FuseFileInfo::Builder::getPadding() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}
inline void Setattr::FuseFileInfo::Builder::setPadding( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::FuseFileInfo::Reader::getFh() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::FuseFileInfo::Builder::getFh() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}
inline void Setattr::FuseFileInfo::Builder::setFh( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::FuseFileInfo::Reader::getLockOwner() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::FuseFileInfo::Builder::getLockOwner() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}
inline void Setattr::FuseFileInfo::Builder::setLockOwner( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Setattr::FuseFileInfo::Reader::getPollEvents() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Setattr::FuseFileInfo::Builder::getPollEvents() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Setattr::FuseFileInfo::Builder::setPollEvents( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Setattr::FuseFileInfo::Reader::getNoflush() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Setattr::FuseFileInfo::Builder::getNoflush() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}
inline void Setattr::FuseFileInfo::Builder::setNoflush( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS, value);
}


CAPNP_END_HEADER

