// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("emptr filter") {
  DynamicJsonDocument filter(256);
  DynamicJsonDocument doc(256);

  filter.set(false);

  DeserializationError err =
      deserializeJson(doc, "[1,2,3]", DeserializationOption::Filter(filter));

  REQUIRE(err == DeserializationError::Ok);
  REQUIRE(doc.isNull() == true);
  REQUIRE(doc.is<JsonArray>() == false);
}
