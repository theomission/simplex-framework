#ifndef SIMPLEX_SUPPORT_ADAPTER_H
#define SIMPLEX_SUPPORT_ADAPTER_H

namespace Simplex
{
  namespace Support
  {
    class Adaptee;
    class Adapter
    {

    public:

      void SetAdaptee ( Adaptee* adaptee );
      Adaptee* GetAdaptee();
      bool HasAdaptee ();

      Adapter();
      ~Adapter();

    private:
      Adaptee* mAdaptee;

    };
  }
}

#endif