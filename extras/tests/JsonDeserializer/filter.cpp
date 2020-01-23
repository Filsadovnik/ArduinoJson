// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("Filtering") {
  DynamicJsonDocument filter(256);
  DynamicJsonDocument doc(256);

  SECTION("empty") {
    DeserializationError err =
        deserializeJson(doc, "[1,2,3]", DeserializationOption::Filter(filter));

    REQUIRE(err == DeserializationError::Ok);
    REQUIRE(doc.isNull() == true);
  }

  SECTION("false") {
    filter.set(false);

    DeserializationError err =
        deserializeJson(doc, "[1,2,3]", DeserializationOption::Filter(filter));

    REQUIRE(err == DeserializationError::Ok);
    REQUIRE(doc.isNull() == true);
  }

  SECTION("true") {
    filter.set(true);

    DeserializationError err =
        deserializeJson(doc, "[1,2,3]", DeserializationOption::Filter(filter));

    REQUIRE(err == DeserializationError::Ok);
    REQUIRE(doc.as<std::string>() == "[1,2,3]");
  }
}
