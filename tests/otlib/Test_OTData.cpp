#include <gtest/gtest.h>
#include <otlib/OTData.hpp>

namespace
{

struct Default_OTData : public ::testing::Test
{
  OTData data_;
};

} // namespace

TEST_F(Default_OTData, accessors)
{
  ASSERT_TRUE(data_.GetPointer() == 0);
  ASSERT_TRUE(data_.GetSize() == 0);
}
