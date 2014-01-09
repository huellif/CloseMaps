#include <AknGlobalNote.h>
#include <aknglobalmsgquery.h>


LOCAL_C TBool running()
{
    TFullName res;
    TFindProcess find;

    while(find.Next(res) == KErrNone)
    {
        RProcess ph;
        User::LeaveIfError(ph.Open(res));
        if(ph.SecureId() == 0x20029B6C)
            if (ph.ExitType() == EExitPending)
            {
                return ETrue;
                break;
            }
        ph.Close();
    }
    while(find.Next(res) == KErrNone)
    {
        RProcess ph;
        User::LeaveIfError(ph.Open(res));
        if(ph.SecureId() == 0x20001F65)
            if (ph.ExitType() == EExitPending)
            {
                return ETrue;
                break;
            }
        ph.Close();
    }
    while(find.Next(res) == KErrNone)
    {
        RProcess ph;
        User::LeaveIfError(ph.Open(res));
        if(ph.SecureId() == 0x20001F63)
            if (ph.ExitType() == EExitPending)
            {
                return ETrue;
                break;
            }
        ph.Close();
    }
    while(find.Next(res) == KErrNone)
    {
        RProcess ph;
        User::LeaveIfError(ph.Open(res));
        if(ph.SecureId() == 0x20016BD0)
            if (ph.ExitType() == EExitPending)
            {
                return ETrue;
                break;
            }
        ph.Close();
    }
    while(find.Next(res) == KErrNone)
    {
        RProcess ph;
        User::LeaveIfError(ph.Open(res));
        if(ph.SecureId() == 0x20029B69)
            if (ph.ExitType() == EExitPending)
            {
                return ETrue;
                break;
            }
        ph.Close();
    }
    while(find.Next(res) == KErrNone)
    {
        RProcess ph;
        User::LeaveIfError(ph.Open(res));
        if(ph.SecureId() == 0x2001a983)
            if (ph.ExitType() == EExitPending)
            {
                return ETrue;
                break;
            }
        ph.Close();
    }

    while(find.Next(res) == KErrNone)
    {
        RProcess ph;
        User::LeaveIfError(ph.Open(res));
        if(ph.SecureId() == 0x2001caf2)
            if (ph.ExitType() == EExitPending)
            {
                return ETrue;
                break;
            }
        ph.Close();
    }


    return EFalse;
}

LOCAL_C void ExeMainL()
{    
    if (!running())
    {
        CAknGlobalNote* note = CAknGlobalNote::NewLC();
        TRequestStatus iStatus;
        note->ShowNoteL(iStatus, EAknGlobalInformationNote, _L("No applicable processes found."));
        User::WaitForRequest(iStatus);
        CleanupStack::PopAndDestroy(note);
    }
    else
    {
        CAknGlobalMsgQuery * pDlg = CAknGlobalMsgQuery::NewL();
        CleanupStack::PushL(pDlg);
        TRequestStatus iStatus;
        pDlg->ShowMsgQueryL(iStatus,
                            _L("Do you want to close all processes which are related to Nokia Maps?\nThis will unlock compass for 3rd party apps and give you more free RAM & CPU time."),
                            R_AVKON_SOFTKEYS_YES_NO,
                            _L("CloseMaps"),
                            KNullDesC,
                            0,
                            -1,
                            CAknQueryDialog::ENoTone);

        User::WaitForRequest(iStatus);
        CleanupStack::PopAndDestroy(pDlg);
        if (iStatus.Int() == EAknSoftkeyYes)
        {
            CAknGlobalNote* note = CAknGlobalNote::NewLC();
            TRequestStatus iStatus2;
            note->ShowNoteL(iStatus2, EAknGlobalConfirmationNote, _L("Success.\nClosed all Nokia Maps related processes."));
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

            TFindProcess find7(_L("*[2001caf2]*"));//odnpserver
            while(find6.Next(res) == KErrNone)
            {
                ph.Open(find7);
                ph.Kill(KErrNone);
                ph.Close();
            }
            User::WaitForRequest(iStatus2);
            CleanupStack::PopAndDestroy(note);
        }
    }
}

TInt E32Main()
{
    CTrapCleanup* cl=CTrapCleanup::New();
    TRAPD(error, ExeMainL());
    delete cl;
}
