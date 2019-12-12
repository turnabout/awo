#pragma once

// Temporarily fail a test and output message to console
#define TEMP_DEBUG(msg) GTEST_MESSAGE_(msg, ::testing::TestPartResult::kNonFatalFailure);

// Generate a unique name
#define PP_CAT(a, b) PP_CAT_I(a, b)
#define PP_CAT_I(a, b) PP_CAT_II(~, a ## b)
#define PP_CAT_II(p, res) res

#define UNIQUE_NAME(base) PP_CAT(base, __LINE__)

// Interpret macro argument as array
#define _ARR(...) __VA_ARGS__ 