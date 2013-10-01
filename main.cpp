#include <apgtask.h>
#include <eikenv.h>
#include <akndiscreetpopup.h>
#include <avkon.hrh>

#include <QApplication>

int main(int argc, char *argv[])
{
       QApplication app(argc, argv);
       TRAP_IGNORE(CAknDiscreetPopup::ShowGlobalPopupL((_L("Success")), (_L("Closed Maps")),KAknsIIDNone, KNullDesC));
       TFullName res;
       RProcess ph;

       TFindProcess find(_L("*[20029B6C]*"));//smart2go
       while(find.Next(res) == KErrNone)
       {
           ph.Open(find);
           ph.Kill(KErrNone);
           ph.Close();
       }

       TFindProcess find2(_L("*[20001F65]*"));//sg2variantsrv
       while(find2.Next(res) == KErrNone)
       {
           ph.Open(find2);
           ph.Kill(KErrNone);
           ph.Close();
       }

       TFindProcess find3(_L("*[20001F63]*"));//maps
       while(find3.Next(res) == KErrNone)
       {
           ph.Open(find3);
           ph.Kill(KErrNone);
           ph.Close();
       }

       TFindProcess find4(_L("*[20016BD0]*"));//syncshare
       while(find4.Next(res) == KErrNone)
       {
           ph.Open(find4);
           ph.Kill(KErrNone);
           ph.Close();
       }

       TFindProcess find5(_L("*[20029B69]*"));//drive
       while(find5.Next(res) == KErrNone)
       {
           ph.Open(find5);
           ph.Kill(KErrNone);
           ph.Close();
       }

	  TFindProcess find6(_L("*[2001a983]*"));//odnpserver
       while(find6.Next(res) == KErrNone)
       {
           ph.Open(find6);
           ph.Kill(KErrNone);
           ph.Close();
       }

    return 1;
}

