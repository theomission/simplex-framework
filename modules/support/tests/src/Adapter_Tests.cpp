#include <Simplex/Testing.h>
#include <Simplex/Support/Adapter.h>
#include <Simplex/Support/Adaptee.h>

using namespace Simplex::Support;

class AdapteeMock : public Simplex::Support::Adaptee
{
};

TEST ( SimplexCoreAdapter, AcceptsAnAdaptee )
{
  AdapteeMock* adaptee = new AdapteeMock();
  Adapter adapter = Adapter();

  adapter.SetAdaptee( adaptee );
  ASSERT_EQ ( adaptee, adapter.GetAdaptee() );
  delete adaptee;
}

TEST ( SimplexCoreAdapter, HasAdapteeReturnsFalseIfNoAdapteeSet )
{
  Adapter adapter = Adapter();
  ASSERT_FALSE ( adapter.HasAdaptee() );
}

TEST ( SimplexCoreAdapter, HasAdapteeReturnsTrueIfAdapteeSet )
{
  AdapteeMock* adaptee = new AdapteeMock();
  Adapter adapter = Adapter();

  adapter.SetAdaptee( adaptee );

  ASSERT_TRUE ( adapter.HasAdaptee() );
  delete adaptee;
}

//TODO: TEST ALL BAD CASES WITH EXCEPTIONS AND ALL