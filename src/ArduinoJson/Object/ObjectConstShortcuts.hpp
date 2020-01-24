// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#pragma once

#include <ArduinoJson/Polyfills/attributes.hpp>
#include <ArduinoJson/Polyfills/type_traits.hpp>
#include <ArduinoJson/Strings/StringAdapters.hpp>

namespace ARDUINOJSON_NAMESPACE {
class VariantConstRef;

template <typename TObject>
class ObjectConstShortcuts {
 public:
  // containsKey(const std::string&) const
  // containsKey(const String&) const
  template <typename TString>
  FORCE_INLINE typename enable_if<IsString<TString>::value, bool>::type
  containsKey(const TString &key) const;

  // containsKey(char*) const
  // containsKey(const char*) const
  // containsKey(const __FlashStringHelper*) const
  template <typename TChar>
  FORCE_INLINE typename enable_if<IsString<TChar *>::value, bool>::type
  containsKey(TChar *key) const;

  // operator[](const std::string&) const
  // operator[](const String&) const
  template <typename TString>
  FORCE_INLINE
      typename enable_if<IsString<TString>::value, VariantConstRef>::type
      operator[](const TString &key) const;

  // operator[](char*) const
  // operator[](const char*) const
  // operator[](const __FlashStringHelper*) const
  template <typename TChar>
  FORCE_INLINE
      typename enable_if<IsString<TChar *>::value, VariantConstRef>::type
      operator[](TChar *key) const;

 private:
  const TObject *impl() const {
    return static_cast<const TObject *>(this);
  }
};
}  // namespace ARDUINOJSON_NAMESPACE
