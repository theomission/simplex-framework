#include <Simplex/Support/Adapter.h>
#include <Simplex/Support/Adaptee.h>

namespace Simplex
{

  namespace Support
  {

    Adapter::Adapter()
    {
      mAdaptee = 0;
    }

    Adapter::~Adapter()
    {
    }

    void Adapter::SetAdaptee ( Adaptee* adaptee )
    {
      mAdaptee = adaptee;
    }

    Adaptee* Adapter::GetAdaptee ()
    {
      return mAdaptee;
    }

    bool Adapter::HasAdaptee ()
    {
      return !(mAdaptee == 0);
    }
  }

}