#include <AknGlobalNote.h>
#include <aknglobalmsgquery.h>

LOCAL_C TBool run(int a)
{
    TBool ret = EFalse;
    TFullName res;
    TFindProcess find;
    while(find.Next(res) == KErrNone)
    {
        RProcess ph;
        User::LeaveIfError(ph.Open(res));
        if(ph.SecureId() == a)
            if (ph.ExitType() == EExitPending)
            {
                ret = ETrue;
                break;
            }
        ph.Close();
    }
    return ret;
}

LOCAL_C TBool running()
{
    if (run(0x20029B6C)) return ETrue;
    if (run(0x20001F65)) return ETrue;
    if (run(0x20001F63)) return ETrue;
    if (run(0x20016BD0)) return ETrue;
    if (run(0x20029B69)) return ETrue;
    if (run(0x2001a983)) return ETrue;
    if (run(0x2001caf2)) return ETrue;

    return EFalse;
}

LOCAL_C void kill(TInt aUid)
{
    TInt ret = KErrNone;

    TFullName pName;
    TFindProcess finder(_L("*"));

    TUid tUid = {aUid};

    while((ret = finder.Next(pName)) == KErrNone)
    {
        if (pName == KNullDesC)
            break;

        RProcess process;
        ret = process.Open(pName);
        if (ret != KErrNone)
            return;

        if (tUid == process.Type()[2])
        {
            process.Kill(0);
            process.Close();
            break;
        }

        process.Close();
    }
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

            kill(537041772);//smart2go
            kill(536878949);//sg2variantsrv
            kill(536878947);//maps
            kill(536964048);//syncshare
            kill(537041769);//drive
            kill(536979843);//odnpserver
            kill(536988402);//odnpserver

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
