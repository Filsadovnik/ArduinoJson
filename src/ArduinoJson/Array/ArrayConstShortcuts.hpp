// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#pragma once

#include <ArduinoJson/Polyfills/attributes.hpp>
#include <ArduinoJson/Polyfills/type_traits.hpp>

namespace ARDUINOJSON_NAMESPACE {

class VariantConstRef;

template <typename TArray>
class ArrayConstShortcuts {
 public:
  // Returns the element at specified index if the variant is an array.
  FORCE_INLINE VariantConstRef operator[](size_t index) const;

 private:
  const TArray *impl() const {
    return static_cast<const TArray *>(this);
  }
};
}  // namespace ARDUINOJSON_NAMESPACE
