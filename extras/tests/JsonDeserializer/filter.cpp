// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

static void checkJsonFilterSuccess(std::string input, std::string filter_json,
                                   std::string expected_json) {
  DynamicJsonDocument filter(256);
  DynamicJsonDocument doc(256);

  deserializeJson(filter, filter_json);

  DeserializationError err = deserializeJson(
      doc, input.c_str(), DeserializationOption::Filter(filter));

  REQUIRE(err == DeserializationError::Ok);
  REQUIRE(doc.as<std::string>() == expected_json);
}

static void checkJsonFilterError(std::string input, std::string filter_json,
                                 DeserializationError expected_error) {
  DynamicJsonDocument filter(256);
  DynamicJsonDocument doc(256);

  CAPTURE(input);
  CAPTURE(filter_json);

  deserializeJson(filter, filter_json);

  DeserializationError err = deserializeJson(
      doc, input.c_str(), DeserializationOption::Filter(filter));

  REQUIRE(err == expected_error);
}

TEST_CASE("Filtering") {
  SECTION("empty") {
    checkJsonFilterSuccess("{\"hello\":\"world\"}", "null", "null");
  }

  SECTION("false") {
    checkJsonFilterSuccess("{\"hello\":\"world\"}", "false", "null");
  }

  SECTION("true") {
    checkJsonFilterSuccess("{\"hello\":\"world\"}", "true",
                           "{\"hello\":\"world\"}");
  }

  SECTION("{}") {
    checkJsonFilterSuccess("{\"hello\":\"world\"}", "{}", "{}");
  }

  SECTION("{\"key\":true}") {
    SECTION("can skip an integer") {
      checkJsonFilterSuccess("{\"an_integer\":666,answer:42}",
                             "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip a float") {
      checkJsonFilterSuccess("{\"a_float\":12.34e-6,answer:42}",
                             "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip a boolean") {
      checkJsonFilterSuccess("{\"a_bool\":false,answer:42}",
                             "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip a double-quoted string") {
      checkJsonFilterSuccess("{\"a_double_quoted_string\":\"hello\",answer:42}",
                             "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip a single-quoted string") {
      checkJsonFilterSuccess("{\"a_single_quoted_string\":'hello',answer:42}",
                             "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip an empty array") {
      checkJsonFilterSuccess("{\"an_empty_array\":[],answer:42}",
                             "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip an empty array with spaces in it") {
      checkJsonFilterSuccess("{\"an_empty_array\":[\t],answer:42}",
                             "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip an array") {
      checkJsonFilterSuccess("{\"an_array\":[1,2,3],answer:42}",
                             "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip an empty object") {
      checkJsonFilterSuccess("{\"an_empty_object\":{},answer:42}",
                             "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip an empty object with spaces in it") {
      checkJsonFilterSuccess("{\"an_empty_object\":{    },answer:42}",
                             "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip an object") {
      checkJsonFilterSuccess(
          "{\"an_empty_object\":{a:1,'b':2,\"c\":3},answer:42}",
          "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip an object with spaces in it") {
      checkJsonFilterSuccess(
          "{\"an_empty_object\" : { a : 1 , 'b' : 2 , \"c\" : 3 } ,answer:42}",
          "{\"answer\":true}", "{\"answer\":42}");
    }
  }

  SECTION("{\"level1\":{\"level2\":true}}") {
    checkJsonFilterSuccess(
        "{\"an_integer\": 0,\"answer\":{\"type\":\"int\",\"value\":42}}",
        "{\"answer\":{\"value\":true}}", "{\"answer\":{\"value\":42}}");
  }

  SECTION("[false,true]") {
    checkJsonFilterSuccess("[1,2,3]", "[false,true]", "[2]");
  }

  SECTION("[false,[false, true]]") {
    checkJsonFilterSuccess("[1,[2.1,2.2,2.3],3]", "[false,[false, true]]",
                           "[[2.2]]");
  }

  SECTION("Array: bubble up error in skipped value") {
    checkJsonFilterError("[!,2,3]", "[false,true]",
                         DeserializationError::InvalidInput);
    checkJsonFilterError("[',2,3]", "[false,true]",
                         DeserializationError::IncompleteInput);
    checkJsonFilterError("[\",2,3]", "[false,true]",
                         DeserializationError::IncompleteInput);
  }

  SECTION("Detect incomplete double quoted string") {
    checkJsonFilterError("\"ABC", "false",
                         DeserializationError::IncompleteInput);
  }

  SECTION("Detect incomplete sign quoted string") {
    checkJsonFilterError("'ABC", "false",
                         DeserializationError::IncompleteInput);
  }

  SECTION("Handle escaped quotes") {
    checkJsonFilterError("'A\\'BC'", "false", DeserializationError::Ok);
    checkJsonFilterError("\"A\\\"BC\"", "false", DeserializationError::Ok);
    checkJsonFilterError("'A\\'BC", "false",
                         DeserializationError::IncompleteInput);
    checkJsonFilterError("\"A\\\"BC", "false",
                         DeserializationError::IncompleteInput);
  }
}
