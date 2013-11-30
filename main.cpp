//popups
#include <AknGlobalNote.h>
#include <avkon.mbg>

//UI:
#include <coemain.h>

LOCAL_C void ExeMainL()
{
    CAknGlobalNote* note = CAknGlobalNote::NewLC();
    note->SetGraphic(16584,16585);
    TInt id = note->ShowNoteL(EAknGlobalPermanentNote, _L("Success.\nClosed all Nokia Maps related processes."));

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

    User::After(2000000);
    note->CancelNoteL(id);
    CleanupStack::PopAndDestroy(note);

}

TInt E32Main()
{
    CCoeEnv* coe = new CCoeEnv;
    TRAPD(err, coe->ConstructL());

    _LIT(KTxtLine1,"CloseMaps\n");
    _LIT(KTxtLine2,"Do you want to close all processes which are related to Nokia Maps?\nThis will unlock compass for 3rd party apps and give you more free RAM & CPU time.");
    _LIT(KButt1,"Kill");
    _LIT(KButt2,"Cancel");
    TInt whichbutton(-1);
    TRequestStatus stat;
    RNotifier notifier;
    User::LeaveIfError(notifier.Connect());
    notifier.Notify(KTxtLine1,KTxtLine2,KButt1,KButt2,whichbutton,stat);
    User::WaitForRequest(stat);
    if (whichbutton==0)
    {
        TRAPD(error, ExeMainL());
    }
    notifier.Close();

    coe->DestroyEnvironment();
    return 0;
}
