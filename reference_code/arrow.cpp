// Core root framework
#include "TROOT.h"

// Arrow class
#include "TArrow.h"

// Standalone root application
#include "TApplication.h"

int main(int argc, char** argv)
{
   TApplication theApp("App", &argc, argv);
   TArrow ar1(0.1,0.1,0.1,0.7);
   ar1.Draw();
   TArrow ar2(0.5,0.3,0.5,0.8);
   ar2.Draw();
   theApp.Run();
   return 0;
}
