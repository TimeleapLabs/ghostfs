// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: release.capnp

#pragma once

#include <capnp/generated-header-support.h>
#include <kj/windows-sanity.h>

#if CAPNP_VERSION != 10002
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif


CAPNP_BEGIN_HEADER

namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(c3731c65f8181e89);
CAPNP_DECLARE_SCHEMA(ba416eca52c1b44f);

}  // namespace schemas
}  // namespace capnp


struct Release {
  Release() = delete;

  class Reader;
  class Builder;
  class Pipeline;
  struct FuseFileInfo;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(c3731c65f8181e89, 1, 2)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

struct Release::FuseFileInfo {
  FuseFileInfo() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(ba416eca52c1b44f, 11, 0)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class Release::Reader {
public:
  typedef Release Reads;

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
  inline  ::Release::FuseFileInfo::Reader getFi() const;

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

class Release::Builder {
public:
  typedef Release Builds;

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
  inline  ::Release::FuseFileInfo::Builder getFi();
  inline void setFi( ::Release::FuseFileInfo::Reader value);
  inline  ::Release::FuseFileInfo::Builder initFi();
  inline void adoptFi(::capnp::Orphan< ::Release::FuseFileInfo>&& value);
  inline ::capnp::Orphan< ::Release::FuseFileInfo> disownFi();

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
class Release::Pipeline {
public:
  typedef Release Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

  inline  ::Release::FuseFileInfo::Pipeline getFi();
private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

class Release::FuseFileInfo::Reader {
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

class Release::FuseFileInfo::Builder {
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
class Release::FuseFileInfo::Pipeline {
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

inline  ::uint64_t Release::Reader::getIno() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Release::Builder::getIno() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Release::Builder::setIno( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline bool Release::Reader::hasFi() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool Release::Builder::hasFi() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline  ::Release::FuseFileInfo::Reader Release::Reader::getFi() const {
  return ::capnp::_::PointerHelpers< ::Release::FuseFileInfo>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::Release::FuseFileInfo::Builder Release::Builder::getFi() {
  return ::capnp::_::PointerHelpers< ::Release::FuseFileInfo>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::Release::FuseFileInfo::Pipeline Release::Pipeline::getFi() {
  return  ::Release::FuseFileInfo::Pipeline(_typeless.getPointerField(0));
}
#endif  // !CAPNP_LITE
inline void Release::Builder::setFi( ::Release::FuseFileInfo::Reader value) {
  ::capnp::_::PointerHelpers< ::Release::FuseFileInfo>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), value);
}
inline  ::Release::FuseFileInfo::Builder Release::Builder::initFi() {
  return ::capnp::_::PointerHelpers< ::Release::FuseFileInfo>::init(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline void Release::Builder::adoptFi(
    ::capnp::Orphan< ::Release::FuseFileInfo>&& value) {
  ::capnp::_::PointerHelpers< ::Release::FuseFileInfo>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::Release::FuseFileInfo> Release::Builder::disownFi() {
  return ::capnp::_::PointerHelpers< ::Release::FuseFileInfo>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}

inline bool Release::Reader::hasUuid() const {
  return !_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline bool Release::Builder::hasUuid() {
  return !_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::Text::Reader Release::Reader::getUuid() const {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline  ::capnp::Text::Builder Release::Builder::getUuid() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline void Release::Builder::setUuid( ::capnp::Text::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::set(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), value);
}
inline  ::capnp::Text::Builder Release::Builder::initUuid(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::init(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), size);
}
inline void Release::Builder::adoptUuid(
    ::capnp::Orphan< ::capnp::Text>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::adopt(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::Text> Release::Builder::disownUuid() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::disown(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}

inline  ::int8_t Release::FuseFileInfo::Reader::getFlags() const {
  return _reader.getDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::int8_t Release::FuseFileInfo::Builder::getFlags() {
  return _builder.getDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Release::FuseFileInfo::Builder::setFlags( ::int8_t value) {
  _builder.setDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Release::FuseFileInfo::Reader::getWritepage() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Release::FuseFileInfo::Builder::getWritepage() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Release::FuseFileInfo::Builder::setWritepage( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Release::FuseFileInfo::Reader::getDirectIo() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Release::FuseFileInfo::Builder::getDirectIo() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}
inline void Release::FuseFileInfo::Builder::setDirectIo( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Release::FuseFileInfo::Reader::getKeepCache() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Release::FuseFileInfo::Builder::getKeepCache() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}
inline void Release::FuseFileInfo::Builder::setKeepCache( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Release::FuseFileInfo::Reader::getFlush() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Release::FuseFileInfo::Builder::getFlush() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}
inline void Release::FuseFileInfo::Builder::setFlush( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Release::FuseFileInfo::Reader::getNonseekable() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Release::FuseFileInfo::Builder::getNonseekable() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}
inline void Release::FuseFileInfo::Builder::setNonseekable( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Release::FuseFileInfo::Reader::getCacheReaddir() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Release::FuseFileInfo::Builder::getCacheReaddir() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}
inline void Release::FuseFileInfo::Builder::setCacheReaddir( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Release::FuseFileInfo::Reader::getPadding() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Release::FuseFileInfo::Builder::getPadding() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}
inline void Release::FuseFileInfo::Builder::setPadding( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Release::FuseFileInfo::Reader::getFh() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Release::FuseFileInfo::Builder::getFh() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}
inline void Release::FuseFileInfo::Builder::setFh( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Release::FuseFileInfo::Reader::getLockOwner() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Release::FuseFileInfo::Builder::getLockOwner() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}
inline void Release::FuseFileInfo::Builder::setLockOwner( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Release::FuseFileInfo::Reader::getPollEvents() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Release::FuseFileInfo::Builder::getPollEvents() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Release::FuseFileInfo::Builder::setPollEvents( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Release::FuseFileInfo::Reader::getNoflush() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Release::FuseFileInfo::Builder::getNoflush() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}
inline void Release::FuseFileInfo::Builder::setNoflush( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS, value);
}


CAPNP_END_HEADER
