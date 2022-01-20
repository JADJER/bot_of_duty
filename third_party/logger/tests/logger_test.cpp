//
// Created by jadjer on 17.11.2021.
//

#include <catch.hpp>
#include <logger/Logger.hpp>

SCENARIO("Test logger") {
    GIVEN("Logger with INFO level") {
        auto level = logger::LEVEL_INFO;

        THEN("Logger's test with one arg") {
            auto logger = logger::Logger(level);

            REQUIRE_NOTHROW(logger << 'q');
            REQUIRE_NOTHROW(logger << "qwe");
            REQUIRE_NOTHROW(logger << 123);
            REQUIRE_NOTHROW(logger << 1.23);
            REQUIRE_NOTHROW(logger.commit());
        }

        THEN("Logger's test with several args") {
            auto logger = logger::Logger(level);

            REQUIRE_NOTHROW(logger << 'q' << 'w' << "e");
            REQUIRE_NOTHROW(logger << "qwe"
                                   << "asd");
            REQUIRE_NOTHROW(logger << 123 << 456);
            REQUIRE_NOTHROW(logger << 1.23 << 4.56);
            REQUIRE_NOTHROW(logger << "qwe" << 123);
            REQUIRE_NOTHROW(logger.commit());
        }
    }

    GIVEN("Logger with WARNING level") {
        auto level = logger::LEVEL_WARNING;

        THEN("Logger's test with one arg") {
            auto logger = logger::Logger(level);

            REQUIRE_NOTHROW(logger << 'q');
            REQUIRE_NOTHROW(logger << "qwe");
            REQUIRE_NOTHROW(logger << 123);
            REQUIRE_NOTHROW(logger << 1.23);
            REQUIRE_NOTHROW(logger.commit());
        }

        THEN("Logger's test with several args") {
            auto logger = logger::Logger(level);

            REQUIRE_NOTHROW(logger << 'q' << 'w' << "e");
            REQUIRE_NOTHROW(logger << "qwe"
                                   << "asd");
            REQUIRE_NOTHROW(logger << 123 << 456);
            REQUIRE_NOTHROW(logger << 1.23 << 4.56);
            REQUIRE_NOTHROW(logger << "qwe" << 123);
            REQUIRE_NOTHROW(logger.commit());
        }
    }

    GIVEN("Logger with ERROR level") {
        auto level = logger::LEVEL_ERROR;

        THEN("Logger's test with one arg") {
            auto logger = logger::Logger(level);

            REQUIRE_NOTHROW(logger << 'q');
            REQUIRE_NOTHROW(logger << "qwe");
            REQUIRE_NOTHROW(logger << 123);
            REQUIRE_NOTHROW(logger << 1.23);
            REQUIRE_NOTHROW(logger.commit());
        }

        THEN("Logger's test with several args") {
            auto logger = logger::Logger(level);

            REQUIRE_NOTHROW(logger << 'q' << 'w' << "e");
            REQUIRE_NOTHROW(logger << "qwe"
                                   << "asd");
            REQUIRE_NOTHROW(logger << 123 << 456);
            REQUIRE_NOTHROW(logger << 1.23 << 4.56);
            REQUIRE_NOTHROW(logger << "qwe" << 123);
            REQUIRE_NOTHROW(logger.commit());
        }
    }

    GIVEN("Logger with CRITICAL level") {
        auto level = logger::LEVEL_CRITICAL;

        THEN("Logger's test with one arg") {
            auto logger = logger::Logger(level);

            REQUIRE_NOTHROW(logger << 'q');
            REQUIRE_NOTHROW(logger << "qwe");
            REQUIRE_NOTHROW(logger << 123);
            REQUIRE_NOTHROW(logger << 1.23);
            REQUIRE_NOTHROW(logger.commit());
        }

        THEN("Logger's test with several args") {
            auto logger = logger::Logger(level);

            REQUIRE_NOTHROW(logger << 'q' << 'w' << "e");
            REQUIRE_NOTHROW(logger << "qwe"
                                   << "asd");
            REQUIRE_NOTHROW(logger << 123 << 456);
            REQUIRE_NOTHROW(logger << 1.23 << 4.56);
            REQUIRE_NOTHROW(logger << "qwe" << 123);
            REQUIRE_NOTHROW(logger.commit());
        }
    }
}