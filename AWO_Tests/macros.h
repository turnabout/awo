#pragma once

#define TEMP_DEBUG(val) GTEST_MESSAGE_(val, ::testing::TestPartResult::kNonFatalFailure);