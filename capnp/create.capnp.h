// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: create.capnp

#pragma once

#include <capnp/generated-header-support.h>
#include <kj/windows-sanity.h>

#if CAPNP_VERSION != 10002
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif


CAPNP_BEGIN_HEADER

namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(dcca0c7561caa35b);
CAPNP_DECLARE_SCHEMA(decbfc2f91897ac1);

}  // namespace schemas
}  // namespace capnp


struct Create {
  Create() = delete;

  class Reader;
  class Builder;
  class Pipeline;
  struct FuseFileInfo;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(dcca0c7561caa35b, 2, 3)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

struct Create::FuseFileInfo {
  FuseFileInfo() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(decbfc2f91897ac1, 11, 0)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class Create::Reader {
public:
  typedef Create Reads;

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

  inline  ::uint64_t getParent() const;

  inline bool hasName() const;
  inline  ::capnp::Text::Reader getName() const;

  inline  ::uint64_t getMode() const;

  inline bool hasFi() const;
  inline  ::Create::FuseFileInfo::Reader getFi() const;

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

class Create::Builder {
public:
  typedef Create Builds;

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

  inline  ::uint64_t getParent();
  inline void setParent( ::uint64_t value);

  inline bool hasName();
  inline  ::capnp::Text::Builder getName();
  inline void setName( ::capnp::Text::Reader value);
  inline  ::capnp::Text::Builder initName(unsigned int size);
  inline void adoptName(::capnp::Orphan< ::capnp::Text>&& value);
  inline ::capnp::Orphan< ::capnp::Text> disownName();

  inline  ::uint64_t getMode();
  inline void setMode( ::uint64_t value);

  inline bool hasFi();
  inline  ::Create::FuseFileInfo::Builder getFi();
  inline void setFi( ::Create::FuseFileInfo::Reader value);
  inline  ::Create::FuseFileInfo::Builder initFi();
  inline void adoptFi(::capnp::Orphan< ::Create::FuseFileInfo>&& value);
  inline ::capnp::Orphan< ::Create::FuseFileInfo> disownFi();

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
class Create::Pipeline {
public:
  typedef Create Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

  inline  ::Create::FuseFileInfo::Pipeline getFi();
private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

class Create::FuseFileInfo::Reader {
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

class Create::FuseFileInfo::Builder {
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
class Create::FuseFileInfo::Pipeline {
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

inline  ::uint64_t Create::Reader::getParent() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Create::Builder::getParent() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Create::Builder::setParent( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline bool Create::Reader::hasName() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool Create::Builder::hasName() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::Text::Reader Create::Reader::getName() const {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::capnp::Text::Builder Create::Builder::getName() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline void Create::Builder::setName( ::capnp::Text::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), value);
}
inline  ::capnp::Text::Builder Create::Builder::initName(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::init(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), size);
}
inline void Create::Builder::adoptName(
    ::capnp::Orphan< ::capnp::Text>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::Text> Create::Builder::disownName() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}

inline  ::uint64_t Create::Reader::getMode() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Create::Builder::getMode() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Create::Builder::setMode( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline bool Create::Reader::hasFi() const {
  return !_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline bool Create::Builder::hasFi() {
  return !_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline  ::Create::FuseFileInfo::Reader Create::Reader::getFi() const {
  return ::capnp::_::PointerHelpers< ::Create::FuseFileInfo>::get(_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline  ::Create::FuseFileInfo::Builder Create::Builder::getFi() {
  return ::capnp::_::PointerHelpers< ::Create::FuseFileInfo>::get(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::Create::FuseFileInfo::Pipeline Create::Pipeline::getFi() {
  return  ::Create::FuseFileInfo::Pipeline(_typeless.getPointerField(1));
}
#endif  // !CAPNP_LITE
inline void Create::Builder::setFi( ::Create::FuseFileInfo::Reader value) {
  ::capnp::_::PointerHelpers< ::Create::FuseFileInfo>::set(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), value);
}
inline  ::Create::FuseFileInfo::Builder Create::Builder::initFi() {
  return ::capnp::_::PointerHelpers< ::Create::FuseFileInfo>::init(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline void Create::Builder::adoptFi(
    ::capnp::Orphan< ::Create::FuseFileInfo>&& value) {
  ::capnp::_::PointerHelpers< ::Create::FuseFileInfo>::adopt(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::Create::FuseFileInfo> Create::Builder::disownFi() {
  return ::capnp::_::PointerHelpers< ::Create::FuseFileInfo>::disown(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}

inline bool Create::Reader::hasUuid() const {
  return !_reader.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS).isNull();
}
inline bool Create::Builder::hasUuid() {
  return !_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::Text::Reader Create::Reader::getUuid() const {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_reader.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
inline  ::capnp::Text::Builder Create::Builder::getUuid() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
inline void Create::Builder::setUuid( ::capnp::Text::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::set(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), value);
}
inline  ::capnp::Text::Builder Create::Builder::initUuid(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::init(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), size);
}
inline void Create::Builder::adoptUuid(
    ::capnp::Orphan< ::capnp::Text>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::adopt(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::Text> Create::Builder::disownUuid() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::disown(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}

inline  ::int8_t Create::FuseFileInfo::Reader::getFlags() const {
  return _reader.getDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::int8_t Create::FuseFileInfo::Builder::getFlags() {
  return _builder.getDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Create::FuseFileInfo::Builder::setFlags( ::int8_t value) {
  _builder.setDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Create::FuseFileInfo::Reader::getWritepage() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Create::FuseFileInfo::Builder::getWritepage() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Create::FuseFileInfo::Builder::setWritepage( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Create::FuseFileInfo::Reader::getDirectIo() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Create::FuseFileInfo::Builder::getDirectIo() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}
inline void Create::FuseFileInfo::Builder::setDirectIo( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Create::FuseFileInfo::Reader::getKeepCache() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Create::FuseFileInfo::Builder::getKeepCache() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}
inline void Create::FuseFileInfo::Builder::setKeepCache( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Create::FuseFileInfo::Reader::getFlush() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Create::FuseFileInfo::Builder::getFlush() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}
inline void Create::FuseFileInfo::Builder::setFlush( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Create::FuseFileInfo::Reader::getNonseekable() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Create::FuseFileInfo::Builder::getNonseekable() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}
inline void Create::FuseFileInfo::Builder::setNonseekable( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Create::FuseFileInfo::Reader::getCacheReaddir() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Create::FuseFileInfo::Builder::getCacheReaddir() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}
inline void Create::FuseFileInfo::Builder::setCacheReaddir( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Create::FuseFileInfo::Reader::getPadding() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Create::FuseFileInfo::Builder::getPadding() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}
inline void Create::FuseFileInfo::Builder::setPadding( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Create::FuseFileInfo::Reader::getFh() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Create::FuseFileInfo::Builder::getFh() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}
inline void Create::FuseFileInfo::Builder::setFh( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Create::FuseFileInfo::Reader::getLockOwner() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Create::FuseFileInfo::Builder::getLockOwner() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}
inline void Create::FuseFileInfo::Builder::setLockOwner( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Create::FuseFileInfo::Reader::getPollEvents() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Create::FuseFileInfo::Builder::getPollEvents() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Create::FuseFileInfo::Builder::setPollEvents( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Create::FuseFileInfo::Reader::getNoflush() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Create::FuseFileInfo::Builder::getNoflush() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}
inline void Create::FuseFileInfo::Builder::setNoflush( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS, value);
}


CAPNP_END_HEADER

