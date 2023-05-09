// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: open.capnp

#pragma once

#include <capnp/generated-header-support.h>
#include <kj/windows-sanity.h>
#if !CAPNP_LITE
#include <capnp/capability.h>
#endif  // !CAPNP_LITE

#if CAPNP_VERSION != 10004
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif


CAPNP_BEGIN_HEADER

namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(cd12adb290adece9);
CAPNP_DECLARE_SCHEMA(c2595540df013d9c);

}  // namespace schemas
}  // namespace capnp


struct Open {
  Open() = delete;

  class Reader;
  class Builder;
  class Pipeline;
  struct FuseFileInfo;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(cd12adb290adece9, 1, 1)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

struct Open::FuseFileInfo {
  FuseFileInfo() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(c2595540df013d9c, 12, 0)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class Open::Reader {
public:
  typedef Open Reads;

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

  inline bool hasFi() const;
  inline  ::Open::FuseFileInfo::Reader getFi() const;

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

class Open::Builder {
public:
  typedef Open Builds;

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

  inline bool hasFi();
  inline  ::Open::FuseFileInfo::Builder getFi();
  inline void setFi( ::Open::FuseFileInfo::Reader value);
  inline  ::Open::FuseFileInfo::Builder initFi();
  inline void adoptFi(::capnp::Orphan< ::Open::FuseFileInfo>&& value);
  inline ::capnp::Orphan< ::Open::FuseFileInfo> disownFi();

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Open::Pipeline {
public:
  typedef Open Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

  inline  ::Open::FuseFileInfo::Pipeline getFi();
private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

class Open::FuseFileInfo::Reader {
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

  inline  ::int64_t getFlags() const;

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

class Open::FuseFileInfo::Builder {
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

  inline  ::int64_t getFlags();
  inline void setFlags( ::int64_t value);

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
class Open::FuseFileInfo::Pipeline {
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

inline  ::uint64_t Open::Reader::getIno() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Open::Builder::getIno() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Open::Builder::setIno( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline bool Open::Reader::hasFi() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool Open::Builder::hasFi() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline  ::Open::FuseFileInfo::Reader Open::Reader::getFi() const {
  return ::capnp::_::PointerHelpers< ::Open::FuseFileInfo>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::Open::FuseFileInfo::Builder Open::Builder::getFi() {
  return ::capnp::_::PointerHelpers< ::Open::FuseFileInfo>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::Open::FuseFileInfo::Pipeline Open::Pipeline::getFi() {
  return  ::Open::FuseFileInfo::Pipeline(_typeless.getPointerField(0));
}
#endif  // !CAPNP_LITE
inline void Open::Builder::setFi( ::Open::FuseFileInfo::Reader value) {
  ::capnp::_::PointerHelpers< ::Open::FuseFileInfo>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), value);
}
inline  ::Open::FuseFileInfo::Builder Open::Builder::initFi() {
  return ::capnp::_::PointerHelpers< ::Open::FuseFileInfo>::init(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline void Open::Builder::adoptFi(
    ::capnp::Orphan< ::Open::FuseFileInfo>&& value) {
  ::capnp::_::PointerHelpers< ::Open::FuseFileInfo>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::Open::FuseFileInfo> Open::Builder::disownFi() {
  return ::capnp::_::PointerHelpers< ::Open::FuseFileInfo>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}

inline  ::int64_t Open::FuseFileInfo::Reader::getFlags() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::int64_t Open::FuseFileInfo::Builder::getFlags() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Open::FuseFileInfo::Builder::setFlags( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Open::FuseFileInfo::Reader::getWritepage() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Open::FuseFileInfo::Builder::getWritepage() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Open::FuseFileInfo::Builder::setWritepage( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Open::FuseFileInfo::Reader::getDirectIo() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Open::FuseFileInfo::Builder::getDirectIo() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}
inline void Open::FuseFileInfo::Builder::setDirectIo( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Open::FuseFileInfo::Reader::getKeepCache() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Open::FuseFileInfo::Builder::getKeepCache() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}
inline void Open::FuseFileInfo::Builder::setKeepCache( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Open::FuseFileInfo::Reader::getFlush() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Open::FuseFileInfo::Builder::getFlush() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}
inline void Open::FuseFileInfo::Builder::setFlush( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Open::FuseFileInfo::Reader::getNonseekable() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Open::FuseFileInfo::Builder::getNonseekable() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}
inline void Open::FuseFileInfo::Builder::setNonseekable( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Open::FuseFileInfo::Reader::getCacheReaddir() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Open::FuseFileInfo::Builder::getCacheReaddir() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}
inline void Open::FuseFileInfo::Builder::setCacheReaddir( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Open::FuseFileInfo::Reader::getPadding() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Open::FuseFileInfo::Builder::getPadding() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}
inline void Open::FuseFileInfo::Builder::setPadding( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Open::FuseFileInfo::Reader::getFh() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Open::FuseFileInfo::Builder::getFh() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}
inline void Open::FuseFileInfo::Builder::setFh( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Open::FuseFileInfo::Reader::getLockOwner() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Open::FuseFileInfo::Builder::getLockOwner() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}
inline void Open::FuseFileInfo::Builder::setLockOwner( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Open::FuseFileInfo::Reader::getPollEvents() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<20>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Open::FuseFileInfo::Builder::getPollEvents() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<20>() * ::capnp::ELEMENTS);
}
inline void Open::FuseFileInfo::Builder::setPollEvents( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<20>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Open::FuseFileInfo::Reader::getNoflush() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<11>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Open::FuseFileInfo::Builder::getNoflush() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<11>() * ::capnp::ELEMENTS);
}
inline void Open::FuseFileInfo::Builder::setNoflush( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<11>() * ::capnp::ELEMENTS, value);
}


CAPNP_END_HEADER

