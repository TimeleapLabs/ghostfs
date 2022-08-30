// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: setxattr.response.capnp

#pragma once

#include <capnp/generated-header-support.h>
#include <kj/windows-sanity.h>
#if !CAPNP_LITE
#include <capnp/capability.h>
#endif  // !CAPNP_LITE

#if CAPNP_VERSION != 10002
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif


CAPNP_BEGIN_HEADER

namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(ac7f6b5407c7357f);

}  // namespace schemas
}  // namespace capnp


struct SetxattrResponse {
  SetxattrResponse() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(ac7f6b5407c7357f, 2, 1)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class SetxattrResponse::Reader {
public:
  typedef SetxattrResponse Reads;

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

  inline bool hasUuid() const;
  inline  ::capnp::Text::Reader getUuid() const;

  inline  ::int8_t getRes() const;

  inline  ::int8_t getErrno() const;

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

class SetxattrResponse::Builder {
public:
  typedef SetxattrResponse Builds;

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

  inline bool hasUuid();
  inline  ::capnp::Text::Builder getUuid();
  inline void setUuid( ::capnp::Text::Reader value);
  inline  ::capnp::Text::Builder initUuid(unsigned int size);
  inline void adoptUuid(::capnp::Orphan< ::capnp::Text>&& value);
  inline ::capnp::Orphan< ::capnp::Text> disownUuid();

  inline  ::int8_t getRes();
  inline void setRes( ::int8_t value);

  inline  ::int8_t getErrno();
  inline void setErrno( ::int8_t value);

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class SetxattrResponse::Pipeline {
public:
  typedef SetxattrResponse Pipelines;

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

inline  ::uint64_t SetxattrResponse::Reader::getIno() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t SetxattrResponse::Builder::getIno() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void SetxattrResponse::Builder::setIno( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline bool SetxattrResponse::Reader::hasUuid() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool SetxattrResponse::Builder::hasUuid() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::Text::Reader SetxattrResponse::Reader::getUuid() const {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::capnp::Text::Builder SetxattrResponse::Builder::getUuid() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline void SetxattrResponse::Builder::setUuid( ::capnp::Text::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), value);
}
inline  ::capnp::Text::Builder SetxattrResponse::Builder::initUuid(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::init(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), size);
}
inline void SetxattrResponse::Builder::adoptUuid(
    ::capnp::Orphan< ::capnp::Text>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::Text> SetxattrResponse::Builder::disownUuid() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}

inline  ::int8_t SetxattrResponse::Reader::getRes() const {
  return _reader.getDataField< ::int8_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}

inline  ::int8_t SetxattrResponse::Builder::getRes() {
  return _builder.getDataField< ::int8_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}
inline void SetxattrResponse::Builder::setRes( ::int8_t value) {
  _builder.setDataField< ::int8_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS, value);
}

inline  ::int8_t SetxattrResponse::Reader::getErrno() const {
  return _reader.getDataField< ::int8_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}

inline  ::int8_t SetxattrResponse::Builder::getErrno() {
  return _builder.getDataField< ::int8_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}
inline void SetxattrResponse::Builder::setErrno( ::int8_t value) {
  _builder.setDataField< ::int8_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS, value);
}


CAPNP_END_HEADER

