#include "gs.h"
#include "common.h"
#include "z7_common.h"
#include <string>
int privateStateEx = 0;

class Z7SigShunt isclass Z7Signal;
{
    int oldTrainPriority = 0;

    public int GetSignalType() 
    {
        return inherited();
    }

    public int IsOpen()
    {
        return inherited();
    }

    public string GetImgShuntMode(bool state) 
    {
        HTMLWindow hw = HTMLWindow;
        string s = "";
        /*
    if(state or privateStateEx==1){
        if(privateStateEx==101 or privateStateEx==102 or privateStateEx==1){
            s=hw.MakeImage("<kuid:236443:103210>",true,32,32);
        }else
        if(privateStateEx==100){
            s=hw.MakeImage("<kuid:236443:103209>",true,32,32);
        }else{
            s=hw.MakeImage("<kuid:236443:103208>",true,32,32);
        }
    }else{
        s=hw.MakeImage("<kuid:236443:103207>",true,32,32);
    }
        */
        if (privateStateEx == 101 or privateStateEx == 102 or privateStateEx == 1) 
        {
            s = hw.MakeImage"<kuid:236443:103210>", true, 32, 32); //white
        }
        else
            if (privateStateEx == 100) 
            {
                s = hw.MakeImage("<kuid:236443:103209>", true, 32, 32); //blue
            }
            else
                if (privateStateEx == 0) 
                {
                    s = hw.MakeImage("<kuid:236443:103206>", true, 32, 32); //gray-blue
                }
                else {
                    s = hw.MakeImage("<kuid:236443:103207>", true, 32, 32); //gray
                }

        return s;
    }

    public string GetContentViewDetails(void) 
    {
        string s = "", s1 = "", s2 = "", s3 = "", s4 = "";
        HTMLWindow hw = HTMLWindow;

        s1 = hw.MakeTable(
            hw.MakeRow(
                hw.MakeCell("<b>" + ST.GetString("object_desc") + "</b>")
            ) +
            hw.MakeRow(
                hw.MakeCell(privateName + " @ " + stationName)
            )
            , "width=100% bgcolor=#777777");

        if (!(GetMController().GetAutoOpenMode() & AOM_AUTO)) 
        {
            if (triggerSemiAutoOpen) 
            {
                s3 = "да";
            }
            else 
            {
                s3 = "нет";
            }
            if (shuntMode) 
            {
                s4 = "да";
            }
            else 
            {
                s4 = "нет";
            }

            s1 = s1 + hw.MakeTable(
                hw.MakeRow(
                    hw.MakeCell("маневровый режим (" + s4 + ")", "bgcolor=#777777") +
                    hw.MakeCell(hw.MakeLink("live://ShuntMode^" + IsOpen(), GetImgShuntMode(shuntMode)), "bgcolor=#777777")
                )

                , "width=100% border=1");
        }

        s = s + hw.MakeTable(
            hw.MakeRow(
                hw.MakeCell(s1
                    , "bgcolor='#AAAAAA' border=1")
            ) +
            hw.MakeRow(
                hw.MakeCell(s2
                    , "bgcolor='#AAAAAA' border=1")
            )
            , "width=100%");
        /*
           s=s+GetCntVDTrain();
        */
        s = s + GetCntVDDebug();

        return s;
    }

    public void ChangeText(Message msg, Soup extParam) {
        string s = "";
        inherited(msg, extParam);
        string[] tok = Str.Tokens(msg.minor, "/");
        string[] tok2 = Str.Tokens(tok[1], "^");
        if (tok2.size() > 1) {
            if (tok2[0] == "ShuntMode") 
            {
                if (tok2[1] == "0") 
                {
                    PostMessage(me, "CTRL", "Update", 0.05);
                }
                else
                    if (tok2[1] == "1") 
                    {
                        PostMessage(me, "CTRL", "Close", 0.05);
                    }
            }

            PostMessage(me, "RefreshBrowser", "", 0.5);
        }
    }


    public Train GetTrainAtPrevTrack() 
    {
        Train ret = null;
        int cntPreIn = 0;
        GSTrackSearch GS = BeginTrackSearch(false);
        MapObject mo = GS.SearchNext();
        bool nextStat = false;
        while (mo) {
            if (mo.isclass(Vehicle)) 
            { //          
                Vehicle veh = cast<Vehicle>mo;
                if ((GS.GetFacingRelativeToSearchDirection() and !veh.GetDirectionRelativeToTrain())
                    or (!GS.GetFacingRelativeToSearchDirection() and veh.GetDirectionRelativeToTrain())
                    ) {
                    ret = veh.GetMyTrain();
                }
                break;
            }
            else
                if ((mo.isclass(Z7Signal))) 
                { //    
                    int stype = (cast<Z7Signal>mo).GetSignalType();
                    bool dir = GS.GetFacingRelativeToSearchDirection();
                    if (!dir and stype & ST_IN) 
                    {
                        break;
                    }
                }
            mo = GS.SearchNext();
        }
        return ret;

    }


    public int[] CheckForState()
    {
        int idxRC = -1;
        int[] ret = new int[3];
        ret[0] = -1;
        ret[1] = -1;
        ret[2] = -1; //prior number

        GSTrackSearch GS = BeginTrackSearch(true);
        MapObject mo = GS.SearchNext();
        Vehicle veh = null;
        int i = 0;
        int state = 0;
        int speed = -1;
        bool LMChecked = false;
        bool stop = false;
        // preFact

        int signalClose = factors.GetNamedTagAsInt("signalClose", -1);
        factors.Clear();

        factors.SetNamedTag("signalClose", signalClose);
        factors.SetNamedTag("orderMode", orderMode);

        Train tr = GetTrainAtPrevTrack();
        if (tr) {
            if (tr.GetTrainPriorityNumber() == 3 and tr.GetActiveDriver()) 
            {
                factors.SetNamedTag("train", tr.GetId());
                factors.SetNamedTag("trainFront", GetTrainFaceDirection(tr));
                factors.SetNamedTag("trainPriority", tr.GetTrainPriorityNumber());
            }
            ret[2] = tr.GetTrainPriorityNumber();
            currentTrainId = tr.GetId();
            if (ret[2] != 3)
                DH.SetDebugInfo("dhs-notrain", "no shunt train", "нет маневрового поезда");
            if (!tr.GetActiveDriver()) {
                DH.SetDebugInfo("dhs-nodriver", "no driver on a train", "нет машиниста в поезде");
            }


        }
        if (orderMode) 
        {
        }
        else 
        {
            DH.SetDebugInfo("dhs-notrain", "no train by sign", "нет поезда перед светофором");
            currentTrainId = -1;
        }

        if (!(GetAutoOpenMode() & (AOM_SEMIAUTO + AOM_SEMIAUTO2))) {
            factors.SetNamedTag("trainFront", true);
            shuntMode = true;
        }
        bool nextFaceSignalShunt = false;
        bool nextNoFaceSignalShunt = false;
        bool nextNoFaceSignal = false;
        while (mo) 
        {
            if (mo.isclass(Vehicle)) 
            { //           
                veh = cast<Vehicle>mo;
                //break;
            }
            else
                if ((mo.isclass(Z7Signal)) and (GS.GetFacingRelativeToSearchDirection())) 
                { //    
                    int stype = (cast<Z7Signal>mo).GetSignalType();
                    if (((stype & (ST_STATION + ST_UNTYPED)))) 
                    {
                        //factors.SetNamedTag("nextPrivateStateEx",(cast<Z7Signal>mo).privateStateEx);
                        factors.SetNamedTag("nextFaceSignal", mo.GetId());
                        break;
                    }
                    else
                        if (stype & ST_SHUNT and !nextFaceSignalShunt) 
                        {
                            nextFaceSignalShunt = true;
                            factors.SetNamedTag("nextFaceSignalShunt", mo.GetId());
                        }
                }
                else
                    if ((mo.isclass(Z7Signal)) and !(GS.GetFacingRelativeToSearchDirection())) 
                    {
                        int stype = (cast<Z7Signal>mo).GetSignalType();
                        if (((stype & (ST_STATION + ST_UNTYPED))) and !nextNoFaceSignal) 
                        {
                            nextNoFaceSignal = true;
                            factors.SetNamedTag("nextNoFaceSignal", mo.GetId());
                        }
                        else
                            if (stype & ST_SHUNT and !nextNoFaceSignalShunt) 
                            {
                                nextNoFaceSignalShunt = true;
                                factors.SetNamedTag("nextNoFaceSignalShunt", mo.GetId());
                            }
                    }
                    else
                        if ((mo.isclass(Z7MrkCustom))) 
                        {
                            Z7MrkCustom mrk = cast<Z7MrkCustom>mo;
                            string type = mrk.GetType();
                            if (type == "mrx")
                            {
                                factors.SetNamedTag("mrxLock", mrk.IsLock());
                            }
                        }
            mo = GS.SearchNext();
        }

        if (orderMode) 
        {
            factors.SetNamedTag("orderMode.SignIn", -2);
        }

        factors.SetNamedTag("shuntMode", shuntMode);
        factors.SetNamedTag("mainMode", mainMode);
        factors.SetNamedTag("autoOpenMode", GetAutoOpenMode());
        ret[0] = LC.CheckForState(0, factors);

        if ((ret[0] == 0 or ret[0] == 100) and factors.GetNamedTagAsInt("nextFaceSignal", -1) == -1)
        {
            DH.SetDebugInfo("dhs-nonextsignal", "not next signal", "нет следующего светофора");
        }
        else {
            //factors.SetNamedTag("nextFaceSignal",mo.GetId());
            if (mn) 
            {
                Z7SignalCustom sig1 = (cast<Z7Signal>(Router.GetGameObject(Str.ToInt(factors.GetNamedTag("nextFaceSignal")))));
                if (sig1) 
                {
                    string s33 = sig1.privateName;
                    DH.SetDebugInfo("dhs-nextstate", "next (" + s33 + ") trainsignal in state " + factors.GetNamedTag("nextPrivateStateEx"), 
                    "следующий светофор (" + s33 + ") в состоянии " + factors.GetNamedTag("nextPrivateStateEx"));
                }
                sig1 = (cast<Z7Signal>(Router.GetGameObject(Str.ToInt(factors.GetNamedTag("nextFaceSignalShunt")))));
                if (sig1) {
                    string s34 = sig1.privateName;
                    DH.SetDebugInfo("dhs-nextstateshunt", "next shunt (" + s34 + ") signal ", "следующий маневровый (" + s34 + ") ");
                }
            }


        }

        if ((ret[0] == 0 or ret[0] == 100) and factors.GetNamedTagAsBool("mrxLock", false)) 
        {
            DH.SetDebugInfo("dhs-mrxlock", "x-marker is locked", "x-marker заблокирован");
        }
        if (ret[0] == 101 or ret[0] == 102) {
            DH.ClearAll();
        }

        return ret;
    }

    public void DoSetShuntSignalStateEx(int lPrivateStateEx) 
    {
        int pr = factors.GetNamedTagAsInt("trainPriority", 2);
        if (pr == 3 and lPrivateStateEx == 100) {
            DoSetSignalStateEx(0);
        }
        else {
            DoSetSignalStateEx(lPrivateStateEx);
        }

    }

    public void UpdateSign(Message msg) 
    {
        int requestPrivateStateEx = -1;
        int speed = -1;
        int[] rel;
        string[] tok;
        if (msg.minor == "Update") 
        {
            factors.Clear();
            rel = CheckForState();
            requestPrivateStateEx = rel[0];
            if (oldPrivateStateEx == requestPrivateStateEx) 
            {
                if (oldTrainPriority != factors.GetNamedTagAsInt("trainPriority", 2)) 
                {
                    DoSetShuntSignalStateEx(privateStateEx);
                    oldTrainPriority = factors.GetNamedTagAsInt("trainPriority", 2);
                }
                return;
            }
            privateStateEx = requestPrivateStateEx;
            //DoSetSpeedLimit(rel[1]/3.6);
                    //PostMessageToNextSignals(ST_STATION+ST_UNTYPED,"SignalOpen","",0.2);
            if (currentTrainId != -1) 
            {
                PostMessage(me, "CTRL", "InitSpeed^" + currentTrainId, 0.01);
            }
            PostMessageToPrevSignals(ST_STATION + ST_UNTYPED, "CTRL", "Update", 0.2);
            if (GetAutoOpenMode() & AOM_AUTO) 
            {
                PostMessageToNextSignals(ST_SHUNT, "CTRL", "Update", 0.01);
            }
            else
                if (GetAutoOpenMode() & AOM_SEMIAUTO) 
                {
                    if (triggerSemiAutoOpen) 
                    {
                    }
                }

            //SetSignalStateEx(,"");
        }
        else
            if (msg.minor == "Close") 
            {
                factors.Clear();
                factors.SetNamedTag("signalClose", 1);
                rel = CheckForState();

                requestPrivateStateEx = rel[0];
                if (oldPrivateStateEx == requestPrivateStateEx) 
                {
                    return;
                }
                privateStateEx = requestPrivateStateEx;
            }
          /*
             if(shuntMode)
             {
               StateChangeShunt(msg);
              }
          */
        LC.OnLights(privateStateEx, mainMode);
        oldPrivateStateEx = privateStateEx;
        DoSetShuntSignalStateEx(privateStateEx);
        if (mn)
        {
            PostMessage(me, "RefreshBrowser", "", 1.5);
        }
        PostMessage(null, "Signal", "Updated", 2.0);
    }


    public void Enter(Message msg)
    {
        string nDriver = "";
        if (privateStateEx == 1000) 
        {
            return;
        }
        Train tr = cast<Train>(msg.src);
        if (msg.minor == "Enter") 
        {
            //PostMessageToNextSignals(ST_STATION+ST_UNTYPED,"DoSetSpeedLimitLocal",-tr.GetTrainPriorityNumber() ,0.1);
            //PostMessage(me,"DoSetSpeedLimitLocal",-tr.GetTrainPriorityNumber() ,0.01);
            int trainDirBySign = GetTrainDirectBySign(tr, true);
            if (GetMController().aomShunt & (Z7SupertriggerCustom.AOMS_AUTOALL + 
                Z7SupertriggerCustom.AOMS_AUTOSHUNT) and trainDirBySign == 1) 
            {
                PostMessageToNextSignals(ST_SHUNT, "CTRL", "Update", 0.01);
            }
        }
        if (msg.minor == "Leave") 
        {
            int trainDirBySign = GetTrainDirectBySign(tr, true);

            //PostMessage(me,"CTRL","Update",0.01);
            PostMessage(me, "CTRL", "Close", 0.01);
            Train trainLeave = (cast<Train> msg.src);
            string nameDriver = "";
            if (trainLeave) 
            {
                if (trainLeave.GetActiveDriver())
                {
                    nameDriver = trainLeave.GetActiveDriver().GetLocalisedName();
                }
            }
            if (nameDriver) 
            {
                nDriver = "null";
            }
            if (GetSignalType() & ST_STATION) 
            {
                PostMessage(null, "ST_SHUNT.Leave", nDriver + ":" + privateName + ":" + stationName, 0.01);
            }
            orderMode = false;

        }
    }

    public void Control(Message msg) 
    {
        int oldState = privateStateEx;

        if (msg.minor == "OrderOpen") 
        {
            orderMode = true;
            msg.minor = "Update";
        }
        else
            if (msg.minor == "OrderClose") 
            {
                orderMode = false;
                msg.minor = "Update";
            }


        inherited(msg);
        if (oldState != privateStateEx) 
        {
            if (GetMController().aomShuntWay) 
            {
                if (IsOpen())
                    PostMessageToNextSignals(ST_SHUNT, "CTRL", "ShuntMode.true", 0.01);
                PostMessageToNextSignals(ST_SHUNT, "CTRL", "Update", 0.01);
            }
        }
        if (orderMode != oldOrderMode) 
        {
            if (IsOpen() and orderMode) 
            {
                PostMessageToNextSignals(ST_SHUNT + ST_ROUTER, "CTRL", "OrderOpen", 0.01);
            }
            else 
            {
                PostMessageToNextSignals(ST_SHUNT + ST_ROUTER, "CTRL", "OrderClose", 0.01);
            }
            oldOrderMode = orderMode;
        }

        if (privateStateEx == 0 or privateStateEx == 100)
        {
            orderMode = false;
        }


    }

    public int prGetSignalType()
    {
        return ST_SHUNT;
    }

    public void Init(Asset self) 
    {
        inherited(self);
        shuntMode = true;
        LC.ClearLMDF();
        LC.LoadLMDF(new Z7LightMdf_BW());
        LC.LoadLMDF(new Z7LightMdf_RW());
    }
};
