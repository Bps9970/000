#include "common.h"
#include "Signal.gs"
#include "trackmark.gs"
#include "./z7_lc.gs"
#include "./z7_lmdf.gs"
#include "./z7_custom.gs#
//include "./z7_router.gs"
//

class Z7Signal is class Z7SignalCustom
{

 public Z7LightController LC	= 	null;
 public thread void MainLightLoop(Message msg);
 public void DoSetSignalStateEx(int code);
 public Train IsBusyTrack(int trainId);
 public void Setup();
 public void PostMessageToPrevSignals(int lTypeSignals,string major,string minor,float delay);
 public void PostMessageToNextSignals(int lTypeSignals,string major,string minor,float delay);
 public void PostMessageToAllNextShuntSignals(string major,string minor,float delay);
 public Z7Signal GetNextSignal(int searchTypes);
 public void ShowSControllerPage();
 public void SetupMainController();
 public int GetPrivateId();
 public bool isCtrlSignal=false;

 public Z7MrkCustom GetZMarkerById(int privateId)
 {
        Z7MrkCustom ret=null;
 	TrackMark[] tm=World.GetTrackMarkList();
 	int i=0;
 	for(;i<tm.size();i++)
    {
 		if(tm[i].isclass(Z7MrkCustom))
        {
 			Z7MrkCustom zm=(cast<Z7MrkCustom>tm[i]);
 			if(zm.GetPrivateId()==privateId and privateId!=-1)
            {
 				ret=zm;
 				break;
 			}
 		}
        else
        {
 			continue;
 		}
 	}
 	return ret;
 }

 public Z7Signal GetZ7SignalById(int privateId)
 {
        Z7Signal ret=null;
 	Signal[] tm=World.GetSignalList();
 	int i=0;
 	for(;i<tm.size();i++)
    {
 		if(tm[i].isclass(Z7Signal))
        {
 			Z7Signal zm=(cast<Z7Signal>tm[i]);
 			if(zm.GetPrivateId()==privateId and privateId!=-1)
            {
 				ret=zm;
 				break;
 			}
 		}
        else
        {
 			continue;
 		}
 	}
 	return ret;
 }

 public Z7Signal GetZ7SignalByName(string nameAtStation)
 {
        Z7Signal ret=null;
 	Signal[] tm=World.GetSignalList();
 	int i=0;
 	for(;i<tm.size();i++){
 		if(tm[i].isclass(Z7Signal))
        {
 			Z7Signal zm=(cast<Z7Signal>tm[i]);
 			if((zm.privateName+"@"+zm.stationName)==nameAtStation and privateId!=-1)
            {
 				ret=zm;
 				break;
 			}
 		}
        else
        {
 			continue;
 		}
 	}
 	return ret;
 }

 public int GetNewPrivateId(void)
 {
 	Signal[] sigs=World.GetSignalList();
 	int i=0;
 	int prId=0;
 	for(;i<sigs.size();i++)
    {
 		if(sigs[i].isclass(Z7SignalCustom))
        {
 			int prPrId=(cast<Z7SignalCustom>sigs[i]).privateId;
 			if(prPrId>prId)
            {
 				prId=prPrId;
 			}
 		}
 	}
 	privateId=prId+1;
 	return privateId;
 }

 public int GetPrivateId()
 {
        int ret=-1;
	ret= privateId;
	return ret;
 }

 public Z7SupertriggerCustom GetMController()
 {
 	if(!mController)
    {
		SetupMainController();
 	}
 	return mController;
 }

 public Z7SControllerCustom GetSController()
 {
 	return sController;
 }

 public int GetAutoOpenMode()
 {
 	if(!sController)
    {
 		return GetMController().GetAutoOpenMode();
 	}
	return GetSController().GetAutoOpenMode();
 }

 public void SetAutoOpenMode(int lMode)
 {
 	if(lMode==AOM_UNDEF)
    {
 		lMode=AOM_AUTO;
 	}
 	if(lMode!=GetAutoOpenMode())
    { 
	 	autoOpenMode=lMode;
	 	if(mn)
        {
	 		PostMessage(me,"RefreshBrowser","",0.01);
	 	}
 	}
 }

 public thread void FlashDefaultMeshVisible()
 {
 	if(flashDefaultMeshVisible)
    {
 		return;
 	}
 	flashDefaultMeshVisible=true;
 	while(flashDefaultMeshVisible)
    {
 		SetMeshVisible("default",false,1.0);
 		Sleep(1.5);
 		SetMeshVisible("default",true,1.0);
 		Sleep(1.5);
 	}
 }

 public string GetDefaultMesh()
 {
 	return "default";
 }

 public void SetDefaultMeshVisible(bool state)
 {
        
 	if(World.GetCurrentModule()==World.DRIVER_MODULE )
    {
 		if(state==false){
	 		//SetMeshVisible("default",state,0.0);
	 		SetMeshVisible(GetDefaultMesh(),state,0.0);
 		}
 	}else{
 		if(!state){
 			if(bc)
		  		bc.SetBox(-1,1);
 			//FlashDefaultMeshVisible();
 			if(GetMController())
            {
				Asset invctrl=GetMController().GetAsset().FindAsset("invisible_controller");
				SetFXAttachment("invctrl",invctrl);
			}
 		}
        else
        {
	 		//flashDefaultMeshVisible=false;
			//SetMeshVisible("default",true,0.0); 	
			SetFXAttachment("invctrl",null);
 		}
 	}
        
        //SetMeshVisible("default",state,2.0);
                /*
 		if(!state)
        {
	  		bc.SetBox(-1,1);
 			FlashDefaultMeshVisible();
 		}
        else
        {
	 		flashDefaultMeshVisible=false;
			SetMeshVisible("default",true,0.0); 	
 		}
                */

 }

 public void SetControlMode(int lMode)
 {
 	int i=-1;
 	if(lMode==CM_UNDEF)
    {
	 	if(GetSignalType()&ST_UNTYPED)
        {
 			i=CM_AUTO;
	 	}
        else
	 	if(GetSignalType()&(ST_STATION+ST_SHUNT))
        {
	 		i=CM_LOCAL;
	 	}else
	 	if(GetSignalType()&ST_PROTECT)
        {
	 		i=CM_LOCAL;
	 	}
 	}
    else
    {
 		i=lMode;
 	}
 	if(lMode!=controlMode)
    {
	 	controlMode=i;
	 	if(mn)
        {
	 		PostMessage(me,"RefreshBrowser","",0.01);
	 	}
 	}
 }

 public void SetPreIn(bool val)
 {
 	if(signalType&ST_UNTYPED)
    {
 		if(val)
        {
 			isPreInSign=1;
 			SetFXAttachment("pretabl",GetAsset().FindAsset("pretabl"));
 		}
        else
        {
 			isPreInSign=0;
 			SetFXAttachment("pretabl",null);
 		}
 	}
 }

 public void SetXTabl(int id)
 {
 	if(id<0)
    {
 		SetFXAttachment("xtabl",GetAsset().FindAsset("xtabl"));
 	}
    else
    {
 		SetFXAttachment("xtabl",null);
 	}
 }


 public int IsMacht(void)
 {
 	int ret=1;
 	string s=GetAsset().GetStringTable().GetString("is_macht");
 	if(s=="")
    {
 		return ret;
 	}
    else
    {
 		ret=Str.ToInt(s);
 	}
 	return ret;
 }
 
 void ShowTable(int idx,bool show)
 {
 	int idxTex=0;
 	int idxTexBack=0;
	Asset tex=GetAsset().FindAsset("tex_tabl");
 	if(show)
    {
 		idxTex=1;
 		idxTexBack=2;
 	}
	SetFXTextureReplacement("tabl"+idx,tex,idxTex);
 }
 void ChangeCountTables(int count)
 {
	int i=0;
	for(;i<7;i++)
    {
		ShowTable(i,false);
		//SetFXTextureReplacement("tabl"+i,tex,0);		
	}
 }

 int CountChar(string s)
 {
 	int i=0;
 	int k=0;
 	bool f=false;
 	for(;i<s.size();i++)
    {
 		string s2=s[i,i+1];
 		if(s2>="�")
        { //#208
 			i++;
 		}
 		if(s2=="(")
        {
 			f=true;
 			k++;
 		}
 		if(s2==")")
        {
 			f=false;
 			k--;
 		}
 		if(!f)
        {
			k++;
		}
 	}
 	return k;
 }
 string GetChar(string s,int idx)
 {
 	int i=0;
 	int k=-1;
 	bool f=false;
 	string ret="";
 	for(;i<s.size();i++)
    {
 		// 12(X)A
 		string s2=s[i,i+1];
 		if(!f){
			k++;
		}
 		if(s2=="(")
        {
 			f=true;
 			continue;
 		}
 		if(s2==")")
        {
 			f=false;
 			continue;
 		}
 		if(s2>="�")
        { //#208
 		        if(k==idx)
                {
 		        	if(!f)
                    {
	 		        	ret=s[i,i+2];
	 		        	break;
 		        	}
                    else
                    {
					ret=ret+s[i,i+2];
 		        	}
		        }
 			i++;
 		}
        else
        {
 			if(k==idx)
            {
 		        	if(!f){
	 		        	ret=s[i,i+1];
	 		        	break;
 		        	}
                    else
                    {
					ret=ret+s[i,i+1];
 		        	}
 			}
 		}
 	}
 	return ret;
 }
 //
public string GetDebugInfo()
{
	string s="			"+"str1"+"\n\r"+"<br>"+
		"			"+"str2"+"\n"+
		"			"+"str3"+"\n"+
		"			"+"str4";
        return s;
}

public  void ShowName(string s)
{
 	string[] tok=Str.Tokens(privateName,"-");
 	int isMacht=IsMacht();
 	int i=0;
 	int j=0;
 	if(isMacht==1)
    {             // 1 -   ?
	 	if(tok.size()>0)
        {
		 	int k=CountChar(tok[0]);
 			for(;i<k and i<5;i++)
            {
 				if(i==0 and showDebugInfo)
                {
 					SetFXNameText("name"+i,GetChar(tok[0],i)+GetDebugInfo());
 				}
                else
                {
	 				SetFXNameText("name"+i,GetChar(tok[0],i));
 				}
		 		ShowTable(i,true);
 			}
	 	}
 		for(;i<5;i++)
        {
			SetFXNameText("name"+i," ");
	 		ShowTable(i,false);
 		}
 	}
        else if (isMacht==2) 
        {    // 2 -  ? RMM   
 		i=0;
 		for(;i<6;i++)
        {
			SetFXNameText("name"+i," ");
	 		ShowTable(i,false);
 		}
	 	if(tok.size()>0)
        {
	 		i=0;
		 	int k=CountChar(tok[0]);
                        /*
 			for(;i<k and i<5;i++){
 			        if(k==2 and i==0) j=1;
					else if (k==3 and i==0) j=0;
					   else if (k==4 and i==0) j=0;
					      else if (k==3 and i==1) j=2;
						 else if (k==4 and i==1) j=2;
						    else j=i+2;
                        */
 			for(;i<k and i<5;i++)
            {
 				if(k==1){
 					j=2;
 				}else
 			        if(k==2 and i==0) j=1;
 			        else if(k==2 and i==1) j=3;
					else if (k==3 and i==0) j=0;
				      	else if (k==3 and i==1) j=2;
					else if (k==3 and i==2) j=4;
						else if (k==4 and i==0) j=0;
						else if (k==4 and i==1) j=2;
						else if (k==4 and i==2) j=4;
						else if (k==4 and i==3) j=5;
						    else j=i+2;

	 			SetFXNameText("name"+j,GetChar(tok[0],i));
			 	ShowTable(j,true);
		        }
	 	}
 	}
	else {        //    ? ?
 		i=0;
 		for(;i<7;i++)
        {
			SetFXNameText("name"+i," ");
	 		ShowTable(i,false);
 		}
	 	if(tok.size()>0)
        {
	 		i=0;
		 	int k=CountChar(tok[0]);
 			for(;i<k and i<5;i++)
            {
 				if(k==1 or k==2 or k==4)
                {
	 			        if(i==0)
                        {
	 			        	j=5;
	 			        }else
	 			        if(i==1)
                        {
	 			        	j=6;
	 			        }else
	 			        if(i==2 or i==3)
                        {
	 			        	j=i+1;
	 			        }
                        else
                        {
	 			        	j=i;
	 			        }
	 			}
                else
                {
	 				j=i;
	 			}
	 			SetFXNameText("name"+j,GetChar(tok[0],i));
			 	ShowTable(j,true);
 			}
	 	}
 	}

 }

 public string GetLastStationName()
 {
 	Signal[] sigs=World.GetSignalList ();
 	string stName="";
 	int i=0;
 	int prId=-1;
 	for(;i<sigs.size();i++)
    {
 		Z7Signal sig=cast<Z7Signal>(sigs[i]);
 		if(sig){
 			if(sig.privateId>prId and sig.stationName!="")
            {
 				stName=sig.stationName;
 				prId=sig.privateId;
 			}
 		}
 	}
 	return stName;
 }
 public void AddStationName(string sName)
 {
	stationName=sName;
 }
 public void SetPrivateName(string lPrivateName)
 {
 	if(lPrivateName=="" or !lPrivateName)
    {
 		privateName="undef-["+GetName()+"]";
 	}
    else
    {
	 	privateName=lPrivateName;
	}
	ShowName(privateName);
 }

 public void SetPrivateId(int lPrivateId)
 {
 	if(privateId==-1)
    {
	 	if(lPrivateId>-1)
        {
		 	privateId=lPrivateId;
		}
	}
 }

 public Soup InitSpeedTable(int prior)
 {
 	Soup sp=Constructors.NewSoup();
 	if(prior==1)
    {
 		sp.SetNamedTag("0",0);
 		sp.SetNamedTag("1",15);
 		sp.SetNamedTag("2",40);
 		sp.SetNamedTag("3",60);
 		sp.SetNamedTag("4",60);
 		sp.SetNamedTag("5",40);
 		sp.SetNamedTag("6",80);
 		sp.SetNamedTag("7",80);
 		sp.SetNamedTag("8",120);
 		sp.SetNamedTag("9",80);
 		sp.SetNamedTag("10",80);
 		sp.SetNamedTag("11",40);
 		sp.SetNamedTag("12",120);

 		sp.SetNamedTag("34",40);
 		sp.SetNamedTag("37",80);
 		sp.SetNamedTag("39",40);
 		sp.SetNamedTag("27",80);

 		sp.SetNamedTag("1000",0);
 		sp.SetNamedTag("100",-1);
 		sp.SetNamedTag("101",-1);
 		sp.SetNamedTag("102",-1);

 	}
 	if(prior==2)
    {
 		sp.SetNamedTag("0",0);
 		sp.SetNamedTag("1",15);
 		sp.SetNamedTag("2",40);
 		sp.SetNamedTag("3",60);
 		sp.SetNamedTag("4",60);
 		sp.SetNamedTag("5",40);
 		sp.SetNamedTag("6",80);
 		sp.SetNamedTag("7",80);
 		sp.SetNamedTag("8",80);
 		sp.SetNamedTag("9",80);
 		sp.SetNamedTag("10",80);
 		sp.SetNamedTag("11",40);
 		sp.SetNamedTag("12",80);

 		sp.SetNamedTag("34",40);
 		sp.SetNamedTag("37",80);
 		sp.SetNamedTag("39",40);
 		sp.SetNamedTag("27",80);

 		sp.SetNamedTag("1000",0);
 		sp.SetNamedTag("100",-1);
 		sp.SetNamedTag("101",-1);
 		sp.SetNamedTag("102",-1);

 	}
 	if(prior==3){
 		sp.SetNamedTag("0",0);
 		sp.SetNamedTag("1",15);
 		sp.SetNamedTag("2",20);
 		sp.SetNamedTag("3",20);
 		sp.SetNamedTag("4",20);
 		sp.SetNamedTag("5",20);
 		sp.SetNamedTag("6",20);
 		sp.SetNamedTag("7",20);
 		sp.SetNamedTag("8",20);
 		sp.SetNamedTag("9",20);
 		sp.SetNamedTag("10",20);
 		sp.SetNamedTag("11",20);
 		sp.SetNamedTag("12",20);

 		sp.SetNamedTag("34",20);
 		sp.SetNamedTag("37",20);
 		sp.SetNamedTag("39",20);
 		sp.SetNamedTag("27",20);

 		sp.SetNamedTag("1000",0);
 		sp.SetNamedTag("100",0);
 		sp.SetNamedTag("101",20);
 		sp.SetNamedTag("102",40);

 	}

 	return sp;
 }

 public void SetSnow(bool snow)
 {

 	string sn=ST.GetString("snow");
 	string snsm=ST.GetString("snow_small");
 	if(sn=="" or snsm=="")
    {
 		return;
 	}

 	if(!snow)
    {
 		string[] st=Str.Tokens(sn,",");
 		int i=0;
 		for(i=0;i<st.size();i++)
        {
 			SetFXAttachment(st[i],null);
 		}
 		st=Str.Tokens(snsm,",");
 		for(i=0;i<st.size();i++)
        {
 			SetFXAttachment(st[i],null);
 		}
 	}
    else
    {
 		string[] st=Str.Tokens(sn,",");
 		int i=0;
 		for(i=0;i<st.size();i++)
        {
 			SetFXAttachment(st[i],GetMController().GetSnowAsset(linz_type));
 		}
 		st=Str.Tokens(snsm,",");
 		for(i=0;i<st.size();i++)
        {
 			SetFXAttachment(st[i],GetMController().GetSnowSmallAsset(linz_type));
 		}
 	}
 }


 //descHTML
 public string GetCntName(void)
 {
 	string s="",s1="";
 	HTMLWindow hw=HTMLWindow;
 	if(!ST){
 		return s;
 	}
        s=s+hw.StartTable("border='1' width=90%");
        s=s+hw.StartRow();
	s=s+hw.StartCell("bgcolor='#666666'");
	s=s+hw.MakeLink("live://property/private-name",  ST.GetString("private_name"));
      	s=s+hw.EndCell();
       	s=s+hw.StartCell("bgcolor='#AAAAAA'");
       	s=s+hw.MakeLink("live://property/private-name",privateName);
       	s=s+hw.EndCell();
	s=s+hw.EndRow();
        s=s+hw.StartRow();

	s=s+hw.StartCell("bgcolor='#886666'");
	s=s+hw.MakeLink("live://property/station_name",  "станция (парк,перегон)");
	s=s+hw.EndCell();
       	s=s+hw.StartCell("bgcolor='#BBAAAA'");
       	if(stationName=="")
        {
       		AddStationName(GetLastStationName());
       	}
	s=s+hw.MakeLink("live://property/station_name",stationName);
       	s=s+hw.EndCell();
	s=s+hw.EndRow();

        s=s+hw.StartRow();
	if(privateName!="" and stationName!="")
    {
		s=s+hw.StartCell("bgcolor='#AA8888'");
		s=s+hw.MakeLink("live://property/boom", ST.GetString("init_desc")+" "+privateId);
      		s=s+hw.EndCell();
      		s=s+hw.StartCell("bgcolor='#AAAAAA'");
      		s=s+hw.EndCell();
	}
    else
    {
		s=s+hw.StartCell("bgcolor='#FF0000'");
		s=s+ST.GetString("init_desc")+" "+privateId;
      		s=s+hw.EndCell();
      		s=s+hw.StartCell("bgcolor='#AAAAAA'");
      		s=s+hw.EndCell();
	}
	s=s+hw.EndRow();
	s=s+hw.MakeRow(
		hw.MakeCell("")+
		hw.MakeCell("")
	);
 	if(FHC)
    {
 		s=s+FHC.GetSContent();
 	}
 	s=s+hw.MakeRow(
 		 hw.MakeCell(hw.MakeLink( "live://property/skin","окрас"),"bgcolor='#666666'")+
 		 hw.MakeCell(hw.MakeLink( "live://property/skin",sc.listDesc.GetNamedTag(sc.index+"-"+lang)),"bgcolor='#886666'")+
 		 hw.MakeCell(hw.MakeLink("live://property/noskin","X"))
 	);
 	if(ST.GetString("is_scbbox")=="1" and bc)
    {
 		s1="";
 		if(bc.box1)
        {
 			//s1=bc.box1.GetStringTable().GetString("name-ru");
 			s1=bc.box1.GetConfigSoup().GetNamedSoup("string-table").GetNamedTag("name-ru");
 			if(s1=="")
            {
 				s1=bc.box1.GetName();
 			}
 		}
 		if(scbboxrnd==1 and s1=="")
        {
 			s1="random";
 		}
                /*!!! SCBBOX */
	 	s=s+hw.MakeRow(
 			 hw.MakeCell(hw.MakeLink( "live://property/scbbox","шкаф СЦБ"),"bgcolor='#666666'")+
 			 hw.MakeCell(hw.MakeLink( "live://property/scbbox",s1),"bgcolor='#886666'")+
	 		 hw.MakeCell(hw.MakeLink("live://property/noscbbox","X"))
 		);
 		if(scbboxplace==1)
        {
 			s1="front";
 		}
        else
        {
 			s1="back";
 		}
	 	s=s+hw.MakeRow(
 			 hw.MakeCell(hw.MakeLink( "live://property/scbboxplace","шкаф СЦБ"),"bgcolor='#666666'")+
 			 hw.MakeCell(hw.MakeLink( "live://property/scbboxplace",s1),"bgcolor='#886666'")+
	 		 hw.MakeCell("")
 		);
                /**/
 	}
 	if(ST.GetString("is_ctrlsignal")=="1")
    {
 		if(GetMController().KC.GetParamFromKey("x2","what")=="24")
        {
	 	s=s+hw.MakeRow(
 			 hw.MakeCell(hw.MakeLink( "live://property/ctrlSignal","сигнал-контроллер"),"bgcolor='#666666'")+
 			 hw.MakeCell(hw.MakeLink( "live://property/ctrlSignal",isCtrlSignal),"bgcolor='#886666'")+
	 		 hw.MakeCell("")

 		);
 		}
 	}

	s=s+hw.EndTable()+"<br>";
	return s;
 }

 public string HoldMainModeInCnt()
 {
 	HTMLWindow hw=HTMLWindow;
        string ss=GetAsset().GetStringTable().GetString("hold_mainmode");
        string s="";
        int i=-1;
        if(ss=="")
        {
        	i=-2;
        }else
        if(ss=="PAB")
        {
        	i=3;
        }
        else
        {
        	i=Str.ToInt(ss);
        }
 	if(i==-2)
    {
                s=s+hw.StartRow();
		s=s+hw.StartCell("bgcolor='#666666'");
		s=s+hw.MakeLink("live://property/mainMode",  "режим а/б");
      	      	s=s+hw.EndCell();
       	       	s=s+hw.StartCell("bgcolor='#AAAAAA'");
       	       	if(mainMode==0){
       	       	s=s+hw.MakeLink("live://property/mainMode",ST.GetString("mainmode_0"));
       	       	}else{
       	       	s=s+hw.MakeLink("live://property/mainMode","4х значный");
       	       	}
       	       	s=s+hw.EndCell();
		s=s+hw.EndRow();
 	}
    else
 	if(i==0)
    {
                s=s+hw.StartRow();
		s=s+hw.StartCell("bgcolor='#666666'");
		s=s+"режим а/б";
      	      	s=s+hw.EndCell();
       	       	s=s+hw.StartCell("bgcolor='#AAAAAA'");
       	       	s=s+"3х значный";
       	       	s=s+hw.EndCell();
		s=s+hw.EndRow();
 	}
    else
 	if(i==1)
    {
                s=s+hw.StartRow();
		s=s+hw.StartCell("bgcolor='#666666'");
		s=s+"режим а/б";
      	      	s=s+hw.EndCell();
       	       	s=s+hw.StartCell("bgcolor='#AAAAAA'");
       	       	s=s+"4х значный";
       	       	s=s+hw.EndCell();
		s=s+hw.EndRow();
 	}
 	return s;
 }

 public string GetCntPrivateProperties1(void)
 {
 	string s="",sType="";
 	HTMLWindow hw=HTMLWindow;
        s=s+hw.StartTable("border='1' width=90%");

        s=s+HoldMainModeInCnt();

        if(GetSignalType() & (ST_IN+ST_ROUTER+ST_OUT+ST_UNTYPED))
        {
	        if(GetSignalType()&ST_IN)
            {
        		sType="входной";
	        }
        	if(GetSignalType()&ST_ROUTER)
            {
        		sType="маршрутный";
	        }
        	if(GetSignalType()&ST_OUT)
            {
        		sType="выходной";
	        }
        	if(GetSignalType()&ST_UNTYPED)
            {
        		sType="проходной";
	        }

	        s=s+hw.StartRow();
		s=s+hw.StartCell("bgcolor='#666666'");
		s=s+hw.MakeLink("live://property/signalType",  "тип светофора");
      		s=s+hw.EndCell();
	       	s=s+hw.StartCell("bgcolor='#AAAAAA'");
       		s=s+hw.MakeLink("live://property/signalType",sType);
	       	s=s+hw.EndCell();
		s=s+hw.EndRow();
	}

        s=s+hw.StartRow();
	s=s+hw.StartCell("bgcolor='#666666'");
	s=s+hw.MakeLink("live://property/mrft",  "маркер прямого пути (явный)");
      	s=s+hw.EndCell();
       	s=s+hw.StartCell("bgcolor='#AAAAAA'");
       	Z7MrkCustom mrk=GetZMarkerById( mainMarkerId);
       	if(mrk!=null)
        {
	       	s=s+hw.MakeLink("live://property/mrft",mrk.GetType()+" "+mrk.GetPrivateId());
	}
       	s=s+hw.EndCell();
	s=s+hw.EndRow();
	s=s+hw.EndTable()+"<br>";

 	return s;
 }

 
 public string GetCntPrivateProperties2(void)
 {
        HTMLWindow hw=HTMLWindow;
	string s=LC.GetCntPrivateProperties2();
        /*
	hw.MakeRow(
		hw.MakeCell(hw.MakeLink("live://property/currentLMDF","режим работы")
		,"bgcolor=#888888")+
		hw.MakeCell(hw.MakeLink("live://property/currentLMDF",currentLMDF.GetNamedType())
		,"bgcolor=#AAAAAA")
	);
        */

  	s=hw.MakeTable(s
  	,"border=1 width=90%");

 	return s;
 }

 public string GetCntSController()
 {
 	string s="",s1="";
 	HTMLWindow hw=HTMLWindow;
	if(sController){
		if(showPanelSController)
        {
			s1=
			hw.MakeRow(
			hw.MakeCell(
				hw.MakeTable(
					hw.MakeRow(
						hw.MakeCell(hw.MakeLink("live://property/selectSignals", sController.ST.GetString("select_signals"))
						,"bgcolor=#888888")
					)+

					hw.MakeRow(
						hw.MakeCell(hw.MakeLink("live://property/linkSignals", sController.ST.GetString("link_signals"))
						+"<br><font color=#0000AA size=-2>"+sController.aNameMySigs+"</font>"
						,"bgcolor=#888888")
					)+
					hw.MakeRow(
						hw.MakeCell(hw.MakeLink("live://property/initSignals", sController.ST.GetString("init_signals"))
						,"bgcolor=#888888")
					)
				,"bgcolor=#5555FF width=100% cellspacing=1")
			));
		}
        else
        {
			s1="";
		}
	 	s=s+hw.MakeTable(
			hw.MakeRow(
				hw.MakeCell(hw.MakeLink("live://property/showPanelSController", sController.ST.GetString1("panel_desc",stationName)+" ("+sController.GetLocalisedName()+")") 
				,"bgcolor=#555555")
			)+
			s1
		,"width=100% cellspacing=1");

                ///
		
		s=hw.MakeTable(
			hw.MakeRow(
				hw.MakeCell(s,
				"bgcolor=#888888")
			)
		,"width=100%");
		

		s=hw.MakeTable(
			hw.MakeRow(
				hw.MakeCell(s,
				"bgcolor=#FF0000")
			)
		,"width=90%");
	}
	return s;
 }

 public string GetCntSpeedTable(void
 {
 	string s="";
 	HTMLWindow hw=HTMLWindow;
        s=s+hw.StartTable("border='1' width=90%");
        s=s+hw.StartRow();
	s=s+hw.StartCell("bgcolor='#00AA00'");

	        s=s+hw.StartTable("border='0' width=100%");
        	s=s+hw.StartRow();
		s=s+hw.StartCell("bgcolor='#444444'");

		        s=s+hw.StartTable("border='1' width=100%");
		        		s=s+hw.StartRow();
					s=s+hw.StartCell("bgcolor='#999999'");
					s=s+"показание светофора";
					s=s+hw.EndCell();

					s=s+hw.StartCell("bgcolor='#999999'");
					s=s+"пассажирский, км/ч";
					s=s+hw.EndCell();
					s=s+hw.StartCell("bgcolor='#999999'");
					s=s+"грузовой, км/ч";
					s=s+hw.EndCell();
					s=s+hw.StartCell("bgcolor='#999999'");
					s=s+"маневровый, км/ч";
					s=s+hw.EndCell();

					s=s+hw.EndRow();

                        int i=0;
                        string scode="0,1,2,3,4,5,6,7,8,9,10,11,12,27,34,37,39,1000,100,101,102";
                        string[] tok=Str.Tokens(scode,",");
                        for(;i<tok.size();i++)
                        {
                        	int code=Str.ToInt(tok[i]);
                        	if(LC.CodeIsPresent(code))
                            {
		        		s=s+hw.StartRow();
					s=s+hw.StartCell("bgcolor='#888888'");
					if(!debug)
                    {
						s=s+LC.GetCodeName(code);
					}
                    else
                    {
						s=s+hw.MakeFontColor(
					        	hw.MakeLink("live://property/stateForce^"+code,LC.GetCodeName(code)+"&nbsp;("+code+")")
					        ,"FF5555");
					}
					s=s+hw.EndCell();

					s=s+hw.StartCell("bgcolor='#888888'");
					s=s+hw.MakeLink("live://property/speed1^"+code,speed1.GetNamedTag(code));
					s=s+hw.EndCell();
					s=s+hw.StartCell("bgcolor='#888888'");
					s=s+hw.MakeLink("live://property/speed2^"+code,speed2.GetNamedTag(code));
					s=s+hw.EndCell();
					s=s+hw.StartCell("bgcolor='#888888'");
					s=s+hw.MakeLink("live://property/speed3^"+code,speed3.GetNamedTag(code));
					s=s+hw.EndCell();

					s=s+hw.EndRow();
				}
			}
                        /*
			s=s+hw.StartRow();
				s=s+hw.StartCell("bgcolor='#888888' colspan=4");
				s=s+hw.MakeLink("live://property/speed_fromprev","по предыдущему настроеному");
				s=s+hw.EndCell();
			s=s+hw.EndRow();
                        */
			s=s+hw.StartRow();
				s=s+hw.StartCell("bgcolor='#888888' colspan=4");
				s=s+hw.MakeLink("live://property/speed_init","заводские настройки");
				s=s+hw.EndCell();
			s=s+hw.EndRow();
			s=s+hw.EndTable(); 	

		s=s+hw.EndCell();
		s=s+hw.EndRow();
		s=s+hw.EndTable(); 	

	s=s+hw.EndCell();
	s=s+hw.EndRow();
	s=s+hw.EndTable(); 

 	return s;
 }

 public string GetCntHelp()
 {
 	string s="*";
 	return s;
 }
 public string GetCntDebug(void)
 {
 	string str="";
	HTMLWindow hw=HTMLWindow;
        //str=str+hw.StartTable("border=1 width='90%'");
        //str=str+hw.StartRow();
        //str=str+hw.StartCell("bgcolor='#444400'");
        
	        str=str+hw.StartTable("border='1'  width=100%");
        	str=str+hw.StartRow();
	        str=str+hw.StartCell("bgcolor=#666666");
                str=str+hw.MakeLink("live://property/help","help");
	        str=str+hw.EndCell();
        	str=str+hw.EndRow();

        	if(help)
            {
        	str=str+hw.StartRow();
	        str=str+hw.StartCell("bgcolor=#777777");
                str=str+GetCntHelp();
	        str=str+hw.EndCell();
        	str=str+hw.EndRow();
        	}
	        str=str+hw.EndTable();

        //str=str+hw.EndCell();
        //str=str+hw.EndRow();
        //str=str+hw.EndTable();
        str=str+"<br><a href='live://property/debug'>debug "+debug+"</a><br>";
        if (debug)
        {
        	str=str+"<a href='live://property/state'>state "+privateStateEx+"</a><br>";
		str=str+"station: "+stationName+"<br>";
		str=str+"preIn: "+isPreInSign+"<br>";
		str=str+"darkMode: "+darkMode+"<br>";
		str=str+"autoOpenMode: "+GetAutoOpenMode()+"<br>";
		str=str+"signalType: "+GetSignalType()+"<br>";
		
		Z7Signal ns=GetNextSignal(ST_STATION+ST_UNTYPED);
		if(ns)
        {
			str=str+"nextSignal: "+ns.privateName+"("+ns.GetName()+")<br>";
			str=str+"	type: "+ns.GetSignalType()+"<br>";
			str=str+"	prStateEx: "+ns.privateStateEx+"<br>";
		}
		ns=GetNextSignal(ST_SHUNT);
		if(ns)
        {
			str=str+"nextShuntSignal: "+ns.privateName+"("+ns.GetName()+")<br>";
			str=str+"	type: "+ns.GetSignalType()+"<br>";
			str=str+"	prStateEx: "+ns.privateStateEx+"<br>";
		}
		str=str+"---------------<br>";

		str=str+DH.GetDebugInfo();
                
	}
 	return str;
 }
 public string GetCntHeader()
 {
 	string str;
 	HTMLWindow hw=HTMLWindow;
 	/*
 	str=hw.MakeTable(
 		hw.MakeRow(
 			hw.MakeCell(hw.MakeLink("live://property/sControllerPage","sControllerPAge")
 			)
 		)
 	,"width=100%, border=2, bgcolor='#555555'");
        */
        str=str+"<font size=\"7\" color=\"#00EFBF\"><b>"+ST.GetString("object_desc")+"</b></font><br>";
        return str;
 }


 public string GetDescriptionHTML(void)
 {
 	string s="";
        s=s+"<html><body>";
 	s=s+GetCntHeader();
 	s=s+GetCntName();
 	s=s+GetCntPrivateProperties1();
 	s=s+GetCntPrivateProperties2();
 	s=s+GetCntSController();
 	s=s+GetCntSpeedTable();
 	s=s+GetCntDebug();
        s=s+"</body></html>";
 	return s;
 }
 
 public string GetPropertyType(string id)
 {
 	string s="link",ss="";
 	string[] s2=Str.Tokens(id,"^");
 	if(id=="private-name")
    {
 		s="string,0,50";
 	}else
 	if(id=="state")
    {
 		s="int,0,1000000,1";
 	}else
 	if(id=="skin")
    {
 		s="list,0";
 	}
    else
 	if(id=="noskin")
    {
 		s="link";
 	}else
 	if(id=="scbbox"){
 		s="list,0";
 	}
    else
 	if(id=="noscbbox"){
 		s="link";
 	}
    else
 	if(id=="scbboxplace")
    {
 		s="link";
 	}
    else
 	if(id=="sControllerPage")
    {
 		s="link";
 	}else
 	if(id=="getSController"){
 		s="link";
 	}
    else
 	if(id=="ctrlSignal")
    {
 		s="link";
 	}
 	else
    {
	 	string s2=LC.GetPropertyType(id);
	 	if(s2!="")
        {
	 		s=s2;
	 	}
	}
	if(s2.size()>1){
		if(s2[0]=="speed1" or s2[0]=="speed2" or s2[0]=="speed3")
        {
			s="int,0,300,1";
		}
		if(s2[0]=="stateForce")
        {
			s="link";
		}
	}
	if(id=="station_create")
    {
		s="string,0,100";
	}
	if(id=="station_name")
    {
		s="list,1";
	}

	if(FHC)
    {
		ss=FHC.GetPropertyType(id);
		if(ss!="")
        {
			s=ss;
		}
	}

 	return s;
 }

  public Soup GetAllStationsFromControllers()
  {
        allStations.Clear();
        Trigger[] allSig=World.GetTriggerList();
	int i=0;
	for(;i<allSig.size();++i)
    {
		if((allSig[i]).isclass(Z7SControllerCustom))
        {
			Z7SControllerCustom sig=cast<Z7SControllerCustom>(allSig[i]);
			if(sig.name!="")
            {
				allStations.SetNamedTag(sig.name,sig.name);
			}
		}
	}
	return allStations;
  }

 public void SetPropertyValue(string id, string val) 
 {
        inherited(id,val);
 	if(id=="private-name")
    {
 		SetPrivateName(val);
 	}
 	LC.SetPropertyValue(id, val); 
 }


 public void SetPropertyValue(string id, int val) 
 {
 	inherited(id,val);
 	string[] s2=Str.Tokens(id,"^");
 	if(s2.size()>1){
 		if(s2[0]=="speed1")
        {
 			speed1.SetNamedTag(s2[1],val);
 		}
        else
 		if(s2[0]=="speed2")
        {
 			speed2.SetNamedTag(s2[1],val);
 		}else
 		if(s2[0]=="speed3")
        {
 			speed3.SetNamedTag(s2[1],val);
 		}

 	}
 	if(id=="state")
    {
 		PostMessage(me,"CTRL","Force^"+val,0.01);
 	}
 	LC.SetPropertyValue(id, val); 
 	if(FHC)
    {
 		FHC.SetPropertyValue(id,val);
 	}
 }


 public void SetPropertyValue(string id, string val,int idx) 
 {
 	inherited(id,val,idx);
 	if(id=="station_name")
    {
 		stationName=val;
 		Trigger[] tl=World.GetTriggerList();
 		int i=0;
 		for(i=0;i<tl.size();i++)
        {
 			Z7SControllerCustom sc=cast<Z7SControllerCustom>tl[i];
 			if(sc)
            {
 				if(sc.name==val)
                {
 					sController=sc;
 					break;
 				}
 			}
 		}
 	}
 	if(id=="skin")
    {
 		if(!sc)
        {
 			return;
 		}
 		sc.SetSkin(idx);
	}
 	if(id=="scbbox")
    {
 		if(!bc)
        {
 			return;
 		}
 		bc.SetBox(idx,scbboxplace);
 		scbboxrnd=0;
 		isSCBBox=1;
	}
 }
 public void LinkPropertyValue(string id)
 {
        inherited(id);
 	if(id=="boom")
    {
 		if(privateId==-1)
        {
			SetPrivateId(GetNewPrivateId()); 
		}
		PostMessage(me,"CTRL","Update",0.1);
		SetupMainController();	
		SetXTabl(privateId);

		if(stationName)
        {
	 		Trigger[] tl=World.GetTriggerList();
 			int i=0;
 			for(i=0;i<tl.size();i++)
            {
 				Z7SControllerCustom sc=cast<Z7SControllerCustom>tl[i];
	 			if(sc)
                {
 					if(sc.name==stationName)
                    {
 						sController=sc;
 						break;
	 				}
 				}
 			}
 		}

 		{
	 		int sigType=ST_UNTYPED;
 			if(signalType&(ST_STATION+ST_UNTYPED+ST_ROUTER_MVPS+ST_PROTECT+ST_REPEAT))
 				sigType=ST_STATION+ST_UNTYPED;
	 		else
 			if(signalType&ST_SHUNT)
            {
 				sigType=ST_SHUNT;
 			}
	 		Z7Signal sig=GetNextSignal(sigType);
 			if(sig)
            {
 				PostMessage(sig,"CTRL","Select^"+sig.privateId,0.01);
 				//PostMessage(sig,"CTRL","@@",5.0);
	 		}
 		}

 	}
 	if(id=="debug")
    {
 		debug= !debug;
 	}
 	if(id=="help")
    {
 		help = !help;
 	}
 	if(id=="mainMode")
    {
 		if(mainMode==0)
        {
 			mainMode=1;
 		}else
 		if(mainMode==1)
        {
 			mainMode=0;
 		}
 		//LC.OffLights();
 		//LC.OnLights(privateStateEx,mainMode);
 		PostMessage(me,"CTRL","Force^"+privateStateEx,0.01);
 	}
  	if(id=="signalType")
    {

  		if(prGetSignalType()&ST_UNTYPED)
        {
  			if(signalType&ST_ROUTER)
            {
  				signalType=ST_UNTYPED;
  			}
            else
            {
  				signalType=ST_ROUTER;
  			}
  		}
        else
        {
	  		if(signalType & ST_IN)
            {
  				signalType=ST_ROUTER;
  			}else
	  		if(signalType & ST_ROUTER)
            {
  				signalType=ST_OUT;
  			}else
	  		if(signalType & ST_OUT)
            {
  				signalType=ST_IN;
  			}
  		}

  	}
  	if(id=="noskin")
    {
  		sc.SetSkin(-1);
  	}
  	if(id=="noscbbox")
    {
  		bc.SetBox(-1,1);
  		isSCBBox=0;
  	}
  	if(id=="scbboxplace")
    {
  		if(scbboxplace==1)
        {
  			scbboxplace=2;
  		}else{
  			scbboxplace=1;
  		}
  		bc.SetBoxPlace(scbboxplace);
  	}
  	if(id=="
  	sControllerPage")
    {
  		ShowSControllerPage();
  	}
  	if(id=="getSController")
    {

  	}
  	if(id=="showPanelSController"
    ){
  		showPanelSController = !showPanelSController;
  	}
  	if(id=="selectSignals")
    {
	  	if(!sController.selectsign)
        {
  		PostMessage(null,"CTRL","Select^"+stationName,0.01);
  		sController.selectsign=true;
		}
        else
        {
  		PostMessage(null,"CTRL","Select^@@",0.01);
  		sController.selectsign=false;
  		}
  	}
    else
  	if(id=="linkSignals")
    {
		PostMessage(sController,"Link",stationName,0.01);
  	}
    else
  	if(id=="initSignals")
    {
  		sController.RunInitSignals();
  	}

 	LC.LinkPropertyValue(id);
  	if(id=="ShuntMode.true" or id=="ShuntMode.false")
    {
  		shuntMode=!shuntMode;
  		PostMessage(me,"CTRL",id,0.01);
  	}
  	string[] s2=Str.Tokens(id,"^");
  	if(s2.size()>1)
    {
  		if(s2[0]=="stateForce")
        {
	 		PostMessage(me,"CTRL","Force^"+s2[1],0.01);
  		}
  	}
  	if(id=="mrft")
    {
  		if(mainMarkerId==-1)
        {
		 	mainMarkerId=-1;
		 	GSTrackSearch GS=BeginTrackSearch(true);
 			MapObject mo=GS.SearchNext();
			while(mo){
				bool dir=GS.GetFacingRelativeToSearchDirection();
				string nm=mo.GetName();
				if(mo.isclass(Z7MrkCustom) and dir)
                {
					string type=(cast<Z7MrkCustom>mo).GetType();
				        if(type=="mrft")
                        { 
			        		mainMarkerId=(cast<Z7MrkCustom>mo).GetPrivateId();
			        		break;
			        	}
			        }
                    else
			        if(mo.isclass(Z7Signal) and dir)
                    {
			        	int stype=(cast<Z7Signal>mo).GetSignalType();
			        	if(stype & (ST_UNTYPED+ST_STATION))
			        	{
			        		break;
			        	}
			        }
				mo=GS.SearchNext();	
			}
  			
  		}
        else
  		{
  			mainMarkerId=-1;
  		}
  	}
  	if(id=="ctrlSignal")
    {
  		isCtrlSignal= !isCtrlSignal;
  		SetDefaultMeshVisible(!isCtrlSignal);
  	}
  	if(id=="speed_init")
    {
  		speed1.Copy(InitSpeedTable(1));
		speed2.Copy(InitSpeedTable(2));
		speed3.Copy(InitSpeedTable(3));
  	}

 }


  public string[] GetPropertyElementList(string id)
  {	
        string[] ret=new string[0];
        int k=0;
 	if(id=="station_name")
    {
 		allStations=GetAllStationsFromControllers();
 		int i=0;
 		for(;i<allStations.CountTags();i++)
        {
 			ret[ret.size()]=allStations.GetNamedTag(allStations.GetIndexedTagName(i));
 		}
 	}

 	if(id=="skin")
    {
	 	int i=0;
 		for(i=0;i<sc.sizeListReskin;i++)
        {
 			ret[ret.size()]=sc.listDesc.GetNamedTag(i+"-"+lang);
	 	}
	}
 	if(id=="scbbox")
    {
	 	int i=0;
	 	Asset[] asse=new Asset[0];
	 	asse=bc.GetListHtmlReskin(bc.GetAssetMask());
 		for(i=0;i<asse.size();i++)
        {
 			Soup st=asse[i].GetConfigSoup();
 			string s1="";
 			if(st)
            {
 				s1=st.GetNamedSoup("string-table").GetNamedTag("name-ru");
 			}
			if(s1!="")
            {
				s1=asse[i].GetName();
			}
 			ret[ret.size()]=s1;
	 	}
	}

 	return ret;
  }


  public void RevalNameStation(Message msg)
  {
 	string[] s2=Str.Tokens(msg.minor,"^");//oldName^newName
 	if(s2.size()<2)
    {
 		return;
 	}
 	if(s2[0]==stationName)
    {
 		stationName=s2[1];
 		//GetPropertyHandler().SetSavesProperties(true);
 	}
  }
 public void ShowSControllerPage()
 {
 	if(stationName=="")
    {
 		return;
 	}
 }

 //end descHTML

 //brows

 public void ChangeText(Message msg,Soup extParam)
 {
 	string s="";
 	string[] t=Str.Tokens(msg.minor,"/");
 	if(t.size()>0)
    {
	 	s=t[1];
	 	if(s=="checkRedState")
        {
			PostMessage(me,"CTRL","Update",0.01);
	 	}

	}
	/*
 	string[] tok=Str.Tokens(msg.minor,"/");
 	string[] tok2=Str.Tokens(tok[1],"^");
        */
	PostMessage(me,"RefreshBrowser","",1.5);
 }


 thread void ShowBrowser(void)
 {
	Message msg;
 	while (mn)
        {
        	wait()
            {
			on "Browser-URL","",msg: 
            {
			        ChangeText(msg,null);
                        	continue;
                        }
                	on "Browser-Closed","",msg: if(msg.src==mn){mn=null;}
                }
        }
        mn=null;

 }

 public string GetCntVDDebug()
 {
	HTMLWindow hw=HTMLWindow; 	
 	string s=hw.MakeTable(
 		hw.MakeRow(
 			hw.MakeCell(""+
 			hw.MakeLink("live://checkRedState","проверить")+"<br>"+
 			DH.GetDebugInfo())
		)
 	,"bgcolor=#444444 width=100%");
 	return s;
 }

 public string GetContentViewDetails(void)
 {
 	string s="",s1="",s2="",s3="",s4="";
 	HTMLWindow hw=HTMLWindow;


        /*
 	s1=hw.MakeTable(
 		hw.MakeRow(
 			hw.MakeCell(GetCntVDControlMode(),"bgcolor=#555555 width=5%")+
 			hw.MakeCell("","bgcolor=#777777")
 		)+
 		hw.MakeRow(
 			hw.MakeCell(GetCntVDIconSign(),"bgcolor=#555555 width=5%")+
 			hw.MakeCell(GetCntVDControlSign(),"bgcolor=#555555")
 		)
 	,"width=100% border=1");
        */
 	s=s+hw.MakeTable(
 		hw.MakeRow(
 			hw.MakeCell(s1	
 			,"bgcolor='#AAAAAA' border=1")
 		)+
 		hw.MakeRow(
 			hw.MakeCell(s2
 			,"bgcolor='#AAAAAA' border=1")
 		)
 	,"width=100%");
        /*
 	s=s+GetCntVDTrain();
        */

	s=s+GetCntVDDebug();
        
 	return s;
 }

 public void ViewDetails(Message msg)
 {
 	if(!mn)
    {
	        mn=Constructors.NewBrowser();
        }
        mn.LoadHTMLString(me.GetAsset(),GetContentViewDetails());
        int x=Math.Rand(0,20);
        int y=Math.Rand(0,20);
        mn.SetWindowRect(100+x,100+y,400+x,450+y);
        ShowBrowser();
 }

 public void RefreshBrowser(Message msg)
 {
 	if(mn)
    {
        mn.LoadHTMLString(me.GetAsset(),GetContentViewDetails());
        }
 }


 //light jet

 //Rules r - r/ r-r2/ c1f-y3 /
 
 public string GetTranslateLensesRule(void)
 {
 	string ret=ST.GetString("rules_translate_lenses");
 	ret=TrainUtil.StrSubst(ret,"","");	
 	return ret;
 }


 public void AddLightCommand(string cmd,string param1,string param2,float delta)
 {
 	cntLightCommand++;
 	Soup sp=Constructors.NewSoup();
 	sp.SetNamedTag("cmd",cmd);
 	sp.SetNamedTag("param1",param1);
	sp.SetNamedTag("param2",param2);	
	sp.SetNamedTag("param3",delta);
 	lightCmd.SetNamedSoup(cntLightCommand,sp);
 	if(!mainLightLoop){
 		PostMessage(me,"AddLightCmd",cmd+":"+param1+"-"+param2,0.01);
 	}
 }

 public void RemoveNextLightCommand()
 {
 	if(lightCmd.CountTags()>0)
    {
	 	lightCmd.RemoveNamedTag(lightCmd.GetIndexedTagName(0));
 	}
 }
 
 public bool CheckNextLightCommand()
 {
        bool ret=false;
        if(lightCmd.CountTags()>0){
        	ret=true;
        }
 	return ret;
 }

 public string GetNextLightCommand(int idx)
 { //0 - command 1-param1 2-param2
 	Soup sp=lightCmd.GetNamedSoup(lightCmd.GetIndexedTagName(0));
 	string s="";
 	if(idx==0)
    {
 		s=sp.GetNamedTag("cmd");
 	}
    else
    }
 	if(idx==1)
    {
 		s=sp.GetNamedTag("param1");
 	}else
 	if(idx==2)
    {
 		s=sp.GetNamedTag("param2");
 	}
    else
 	if(idx==3)
    {
 		s=sp.GetNamedTagAsFloat("param3");
 	}
 	return s;
 }

 public Asset GetLinzAsset(string color,int opacity )
 {
 	Asset a=null;
        /*
 	if(opacity==-1)
    {
		a=GetAsset().FindAsset(color+"_"+linz_type);
	}
    else
    {
		a=GetAsset().FindAsset(color+"_"+linz_type+"-"+opacity);
	}
        */
	a=GetMController().GetLinzAsset(color,opacity,linz_type);

 	return a;
 }

 public Asset GetLBLinzAsset(string color,int opacity,int lLinz_type )
 {
 	Asset a=null;
        /*
 	if(opacity==-1)
    {
		a=GetAsset().FindAsset(color+"_"+linz_type);
	}
    else
    {
		a=GetAsset().FindAsset(color+"_"+linz_type+"-"+opacity);
	}
        */
	a=GetMController().GetLinzAsset(color,opacity,lLinz_type);

 	return a;
 }

 public Asset GetLKLinzAsset(string color, int opacity)
 {
 	Asset a=null;
	a=GetMController().GetLKLinzAsset(color,opacity,linz_type);
 	return a;
 }

 public void SetLKLinz(string linz,string clr,int opacity, bool show)
 {
 	//inherited(linz,clr,opacity,show);
 	if(lk_reflect==0)
    {
 		return;
 	}
 	string[] lkTwins=Str.Tokens(lk_reflect_twinpoint,",");
 	int i=0;
 	string lkLinzPoint="";
 	for(i=0;i<lkTwins.size();i++)
    {
	 	lkLinzPoint="";
 		string[] lkLinz=Str.Tokens(lkTwins[i],"-");
 		if(lkLinz.size()==0)
        {
 			continue;
 		}
 		if(linz==lkLinz[0])
        {
 			lkLinzPoint=lkLinz[1];
 			if(show)
            {
				SetFXAttachment(lkLinz[1],GetLKLinzAsset(clr,opacity));
	 		}
            else
            {
				SetFXAttachment(lkLinz[1],null);
	 		}       
 		}
 	}
 }

 
 public void InitFlash(string p1,string p2)
 {
        bool ret=true;
	flashing=true;
	int i=0;
	for(;i<4;i++)
    {
		//aAssetLight[i]=GetAsset().FindAsset(p2+"_"+linz_type+"-"+i);
		aAssetLight[i]=GetLinzAsset(p2,i);
	}
 }
 
 
 void FadeFlash(bool dir,float d, string p1, string p2)
 {
 	int i=0;
        if(dir)
        {
 		for(;i<4;i++)
        {
			SetFXAttachment(p1,aAssetLight[i]);
			SetLKLinz(p1,p2,i,true);
 			Sleep(d);
	        }
	}
    else
    {
		i=3;
		for(;i> -1;i--)
        {
			SetFXAttachment(p1,aAssetLight[i]);		
			SetLKLinz(p1,p2,i,true);
 			Sleep(d);
		}
	}
 }
 

 public thread void Flash(string p1,string p2)
 {
        float rnd=Math.Rand(-0.15,0.15);
 	bool fl=true;
 	bool fl1=false;	
	while(flashing)
    {
	//and startCountState==countState)
    {
		flashingInProgress=true;
       		FadeFlash(true,0.035,p1,p2);
	        //SetFXAttachment(p1,GetAsset().FindAsset(p2+"_"+linz_type));
		SetFXAttachment(p1,GetLinzAsset(p2,-1));
		SetLKLinz(p1,p2,-1,true);
		Sleep(0.7+rnd);
      		FadeFlash(false,0.055,p1,p2);
	        SetFXAttachment(p1,null);
	        SetLKLinz(p1,p2,-1,false);
		flashingInProgress=false;
	        Sleep(0.8+rnd);
	}
 }
 public void DoLightCommand(string cmd,string p1,string p2)
 {
        if(p1=="")
        {
        	//Print(" don't lighting, state:"+privateStateEx);
        	return;
        }
	string[] l=Str.Tokens(p1,",");
	string[] t=Str.Tokens(p2,",");
	int k=0;
 	if(cmd=="OnLight")
    {
 		for(;k<l.size();k++)
        {
 			if(TrainUtil.HasSufix(l[k],"f")){
 				InitFlash(l[k],t[k]);
	 			Flash(l[k],t[k]);
 				//return;
 			}
 		}
	 	int i=0;
		for(;i<4;i++)
        {
		 	k=0;
		 	for(;k<l.size();k++)
            {
				if(TrainUtil.HasSufix(l[k],"f"))
                {
					continue;
				} 	
				//SetFXAttachment(l[k],GetAsset().FindAsset(t[k]+"_"+linz_type+"-"+i));
				SetFXAttachment(l[k],GetLinzAsset(t[k],i));
				SetLKLinz(l[k],t[k],i,true);
	       		}
			Sleep(0.035);
        	}
		k=0;
		for(;k<l.size();k++)
        {
			//SetFXAttachment(l[k],GetAsset().FindAsset(t[k]+"_"+linz_type));
			SetFXAttachment(l[k],GetLinzAsset(t[k],-1));
			SetLKLinz(l[k],t[k],-1,true);
		}
 	}
 	if(cmd=="OffLight")
    {
 		k=0;
 		for(;k<l.size();k++)
        {
 			if(TrainUtil.HasSufix(l[k],"f"))
            {
 				flashing=false;
	 		}
 		}
	 	int i=3;
		for(;i>-1;i--)
        {
		 	k=0;
		        for(;k<l.size();k++)
                {
				if(TrainUtil.HasSufix(l[k],"f"))
                {
					continue;
				} 	
				//SetFXAttachment(l[k],GetAsset().FindAsset(t[k]+"_"+linz_type+"-"+i));
				SetFXAttachment(l[k],GetLinzAsset(t[k],i));
				SetLKLinz(l[k],t[k],i,true);
        		}
			Sleep(0.055);
        	}
        	k=0;
        	for(;k<l.size();k++)
            {
			SetFXAttachment(l[k],null);
			SetLKLinz(l[k],t[k],-1,false);
		}
 	}
 	
 	if(freeRepeater)
    {
	 	PostMessage(freeRepeater,"DoLightCommandFree",cmd+":"+p1+"-"+p2,0.01);
	}
        
 	//PostMessage(null,"DoLightCommandFree",cmd+":"+p1+"-"+p2,0.01);
 }
 
 
 public thread void MainLightLoop(Message msg)
 {
 	if(mainLightLoop)
    {
 		return;
 	}
 	mainLightLoop=true;
 	int cntFIP=0;
        float p3=0.0;
 		while(CheckNextLightCommand())
        {
 			int cntFIP=0;
	 		string cmd=GetNextLightCommand(0);
 			string p1 =GetNextLightCommand(1);
 			string p2 =GetNextLightCommand(2);
 			       p3 =Str.ToFloat(GetNextLightCommand(3));
	 		RemoveNextLightCommand();
	 		while(flashingInProgress and cntFIP<1000000)
            {
	 			cntFIP++;
	 			Sleep(0.01);
	 		}
 			DoLightCommand(cmd,p1,p2);

			delayNextCmd=p3;
			if(delayNextCmd==0.0)
            {
				delayNextCmd=0.5;
			}
			Sleep(delayNextCmd);
			
		}
	mainLightLoop=false;
 }
 
 public void StartMainLightLoop(Message msg)
 {
 	MainLightLoop(msg);
 }

 thread void WaitForClose(int trainDirBySign)
 {
 	while(! isStopThread1){
		if(IsBusyTrack(trainDirBySign)!=null)
        {
			PostMessage(me,"CTRL","Update",0.1);
			isStopThread1=true;
			currentSpeed=-1.0;
			currentTrainId=-1;
			if(trainDirBySign==2)
            {
				PostMessageToPrevSignals(ST_STATION+ST_UNTYPED,"CTRL","Update",0.01);
			}
			if(trainDirBySign==1 and GetSignalType()&ST_STATION and GetAutoOpenMode()&AOM_AUTO)
            {
				PostMessageToNextSignals(ST_SHUNT,"CTRL","Update",0.01);
			}
			break;
		}
 		Sleep(0.5);
 	}

 }

 public int GetTrainDirectBySign(Train tr, bool enter )
 {
 //enter or leave
 //return  0- undef, 1- enterNormal, 2-enterBack

	int ret=0;
 	if(enter)
    {
 	 	GSTrackSearch GS=me.BeginTrackSearch(false);
 	 	MapObject mo=GS.SearchNext();
                while(mo)
                {
                        if((mo.isclass(Z7Signal)) and (  GS.GetFacingRelativeToSearchDirection()))
                        { //    
                        	int stype=(cast<Z7Signal>mo).GetSignalType();
                        	if( (stype & ST_STATION+ST_UNTYPED) )
                            {
                       			break;
                        	}
                        }
                        else
                        if(mo.isclass(Vehicle))
                        {
                        	Vehicle veh=cast<Vehicle>mo;
                        	if(tr==veh.GetMyTrain())
                            {
                        		ret=1;
                        		return ret;
                        	}
                        	break;
                        }
                	mo=GS.SearchNext();
                }
 	 	GS=me.BeginTrackSearch(true);
 	 	mo=GS.SearchNext();
                while(mo)
                {
                        if((mo.isclass(Z7Signal)) and (  GS.GetFacingRelativeToSearchDirection()))
                        { //    
                        	int stype=(cast<Z7Signal>mo).GetSignalType();
                        	if( (stype & ST_STATION+ST_UNTYPED) ){
                       			break;
                        	}
                        }
                        else
                        if(mo.isclass(Vehicle))
                        {
                        	Vehicle veh=cast<Vehicle>mo;
                        	if(tr==veh.GetMyTrain())
                            {
                        		ret=2;
                        		return ret;
                        	}
                        	break;
                        }
                	mo=GS.SearchNext();
                }

 		
 	}
 	return ret;
 	
 }

 public void Enter(Message msg)
 {
	Train tr=cast<Train>(msg.src);
	if(msg.minor=="Enter")
    {
	        if(privateStateEx==1000)
            {
        		return;
	        }

	        //PostMessageToNextSignals(ST_STATION+ST_UNTYPED,"DoSetSpeedLimitLocal",-tr.GetTrainPriorityNumber() ,0.1);
	        //PostMessage(me,"DoSetSpeedLimitLocal",-tr.GetTrainPriorityNumber() ,0.01);
	        int trainDirBySign=GetTrainDirectBySign(tr,true);
	        PostMessageToNextSignals(ST_STATION+ST_UNTYPED,"CTRL","InitSpeed^"+tr.GetId(),0.01);
	        isStopThread1=false;
	        if(!shuntMode)
            {
			WaitForClose(trainDirBySign);
		}
		if(GetAutoOpenMode()&(AOM_SEMIAUTO+AOM_SEMIAUTO2))
        {
			triggerSemiAutoOpen=false;
			PostMessage(null,"Signal","Updated",2.0);
		}
	        if(GetSignalType()&(ST_STATION+ST_UNTYPED))
            {
	        	tr.PostMessage(null,"ST_TRAIN.Enter",privateName+"@"+stationName,0.01);
	        }


	}
	if(msg.minor=="Leave")
    {
	
	        if(privateStateEx!=1000)
            {
		        PostMessage(me,"CTRL","Update",0.01);
	        }

	        PostMessageToPrevSignals(ST_STATION+ST_UNTYPED,"CTRL","Update",0.01);
	        PostMessageToPrevSignals(ST_STATION+ST_UNTYPED,"CTRL","InitSpeed^"+tr.GetId(),0.5);
		    isStopThread1=true;
                Train trainLeave=(cast<Train> msg.src);
                string nameDriver="";
                if(trainLeave)
                {
                	if(trainLeave.GetActiveDriver())
                    {
                		nameDriver=trainLeave.GetActiveDriver().GetLocalisedName();
                	}
                }
                if(nameDriver)
                {
		        if(GetSignalType()&ST_STATION)
                {
		        	PostMessage(null,"ST_STATION.Leave",nameDriver+":"+privateName+"@"+stationName,0.01);
		        }
                else
		        if(GetSignalType()&ST_SHUNT)
                {
		        	PostMessage(null,"ST_SHUNT.Leave",nameDriver+":"+privateName+"@"+stationName,0.01);
		        }
		}
		if(GetSignalType()&ST_STATION and GetAutoOpenMode()&AOM_AUTO)
        {
			PostMessageToNextSignals(ST_SHUNT,"CTRL","Update",0.01);
		}
		if(GetSignalType()&ST_STATION)
        {
			shuntMode=false;
			PostMessage(null,"Signal","Updated",2.0);
		}
		if(GetAutoOpenMode()&(AOM_SEMIAUTO+AOM_SEMIAUTO2))
        {
			triggerSemiAutoOpen=false;
			PostMessage(null,"Signal","Updated",2.0);
		}
	}
 }

 //end light jet

 public Z7Signal GetNextSignal(int searchTypes)
 {
        Z7Signal ret=null;
 	GSTrackSearch GS=BeginTrackSearch(true);
 	MapObject mo=GS.SearchNext();
        while(mo)
        {
                if((mo.isclass(Z7Signal)) and (  GS.GetFacingRelativeToSearchDirection()))
                { //    
                	int stype=(cast<Z7Signal>mo).GetSignalType();
                	if( (stype & searchTypes) )
                    {
				ret=(cast<Z7Signal>mo);
               			break;
                	}
                }
		if(mo.isclass(Z7MrkRepeaterCustom) and GS.GetFacingRelativeToSearchDirection() )
        {
                          //!!!   ?
			GS=(cast<Z7MrkRepeaterCustom>mo).BeginTrackSearch(true);
		}
        	mo=GS.SearchNext();
        }
	return ret;
 }

 public bool GetTrainFaceDirection(Train tr)
 {
 	bool ret=false;
 	GSTrackSearch GS=BeginTrackSearch(false);
 	MapObject mo=GS.SearchNext();
        while(mo)
        {
		if(mo==me)
        {
			break;
		}
		if(mo.isclass(Vehicle))
        {
			Vehicle veh=cast<Vehicle>mo;
			if(veh.GetMyTrain()==tr)
            {
				/*
				F->       [>> >  false  ++
				F->       [>> <  false  --
				F->       <<] >  true   -+
				F->       <<] <  true   +-
                                */
				if(veh.GetDirectionRelativeToTrain() and !GS.GetFacingRelativeToSearchDirection())
                {
					ret=true;
				}else
				if(!veh.GetDirectionRelativeToTrain() and GS.GetFacingRelativeToSearchDirection())
                {
					ret=true;
				}
                else
				if(veh.GetDirectionRelativeToTrain() and GS.GetFacingRelativeToSearchDirection())
                {
					ret=false;
				}
                else
				if(!veh.GetDirectionRelativeToTrain() and !GS.GetFacingRelativeToSearchDirection())
                {
					ret=false;
				}
				break;
			}
		}
		if(mo.isclass(Z7MrkRepeaterCustom) and !GS.GetFacingRelativeToSearchDirection() )
        {
                              //!!!   ?
			GS=(cast<Z7MrkRepeaterCustom>mo).BeginTrackSearch(false);
		}
        	mo=GS.SearchNext();
        }	
	return ret;
 }


 public Train IsBusyTrack(int stopSignalType,bool faceDirect,int trainId,bool busyDirect)
 {
	//return null; 	
 	GSTrackSearch GS=BeginTrackSearch(busyDirect);
 	MapObject mo=GS.SearchNext();
        Train ret=null;

        while(mo)
        {
        	if(mo.isclass(Vehicle))
             { //          
                	ret=(cast<Vehicle>mo).GetMyTrain();
                	if((ret.GetId()==trainId)or(trainId==-1))
                        break;
                }
                else
                if((mo.isclass(Z7Signal)) and (GS.GetFacingRelativeToSearchDirection()==faceDirect))
                { //    
                	int stype=(cast<Z7Signal>mo).GetSignalType();
                	if( stype & stopSignalType )
                    {
                		break;
                	}
                }
		if(mo.isclass(Z7MrkRepeaterCustom) and GS.GetFacingRelativeToSearchDirection()==busyDirect )
        {
                         //!!!   ?
			GS=(cast<Z7MrkRepeaterCustom>mo).BeginTrackSearch(busyDirect);
		}
        	mo=GS.SearchNext();
        }
	return ret; 	

 }

 public Train IsBusyTrack(int trainDirBySign)
 {
        bool busyDirect=true;
 	if(trainDirBySign==1)
    {
 		busyDirect=true;
 	}
    else
    {
 		busyDirect=false;
 	}
 	return IsBusyTrack(ST_STATION+ST_UNTYPED,busyDirect,-1,busyDirect);
 }

 //[0] - state [1] - speed [2] - last free RC
 public int[] CheckForState(){
        int idxRC	=-1;
	int[] ret		= new int[3];
	ret[0]=-1;
	ret[1]=-1;
	ret[2]=-1;

 	GSTrackSearch GS=BeginTrackSearch(true);
 	MapObject mo=GS.SearchNext();
 	Vehicle veh=null;
 	int i=0;
 	int state=0;
 	int speed=-1;
 	bool LMChecked=false;
 	bool stop=false;
 	factors.Clear();
	bool train=false;
	int nextPrivateStateEx=-1;
        while(mo){
        	if(mo.isclass(Vehicle))
            { //          
        		veh=cast<Vehicle>mo;
        		train=true;
			DH.SetDebugInfo("dh-trainrear","train behind a sign","поезд за светофором");
			//DH.SetDebugInfo("dh-trainrear","поезд за светофором");
        		//break;
                }
                else
                if((mo.isclass(Z7Signal)))
                {
                	if((cast<Z7Signal>mo).GetSignalType()&ST_DEADLOCK)
                    {
                		break;
                	}
                }
                if((mo.isclass(Z7Signal)) and (GS.GetFacingRelativeToSearchDirection()))
                { //
                	int stype=(cast<Z7Signal>mo).GetSignalType();
                	if( ((stype & ST_STATION+ST_UNTYPED)) )
                    {
                		nextPrivateStateEx=(cast<Z7Signal>mo).privateStateEx;
                		factors.SetNamedTag("nextPrivateStateEx",nextPrivateStateEx);
                		factors.SetNamedTag("nextFaceSignal",mo.GetId());
                		if(stype & ST_UNTYPED)
                        {
                			factors.SetNamedTag("nextSignalType",ST_UNTYPED);
                		}
       	        		break;
                	}
                    else
                	if( ((stype & ST_PROTECT)) )
                    {
                		nextPrivateStateEx=(cast<Z7Signal>mo).privateStateEx;
                		if(nextPrivateStateEx==0)
                        {
                			factors.SetNamedTag("nextPrivateStateEx",nextPrivateStateEx);
	                		factors.SetNamedTag("nextFaceSignal",mo.GetId());
       	        			break;
       	        		}
                	}

                }
                else
                if(mo.isclass(Signal) and (GS.GetFacingRelativeToSearchDirection()) and !mo.isclass(Z7Signal))
                {
               		nextPrivateStateEx=(cast<Signal>mo).GetSignalState();
               		if(nextPrivateStateEx==1)
                    {
               			nextPrivateStateEx=4;
               		}
                    else
               		if(nextPrivateStateEx==2)
                    {
               			nextPrivateStateEx=12;
               		}
               		factors.SetNamedTag("nextPrivateStateEx",nextPrivateStateEx);
               		factors.SetNamedTag("nextFaceSignalDefault",mo.GetId());
        		    break;
                }
                else    
		if(mo.isclass(Z7MrkRepeaterCustom) and GS.GetFacingRelativeToSearchDirection()==true )
        {
            //!!!   ?
			GS=(cast<Z7MrkRepeaterCustom>mo).BeginTrackSearch(true);
		}
        	mo=GS.SearchNext();
        }
        factors.SetNamedTag("shuntMode",shuntMode);
        factors.SetNamedTag("mainMode",mainMode);
        ret[0]=LC.CheckForState(0,factors);
        if(train)
        {
        	if(ret[0]!=1000)
            {
        		ret[0]=0;
        	}
        }
        if( (nextPrivateStateEx==1) and (privateStateEx==1000) and (GetSignalType()&ST_UNTYPED) )
        {
        	DH.SetDebugInfo("dh-state1000","span locked","перегон закрыт");
         	ret[0]=1000;
        }
        if(factors.GetNamedTagAsInt("nextPrivateStateEx",-1)==-1)
        {
        	DH.SetDebugInfo("dh-nonextsignal","no next signal","нет следующего сигнала, обрыв РЦ");
        }

        if( (prGetSignalType()&ST_UNTYPED) and (GetSignalType()&ST_ROUTER))
        {
        	if((factors.GetNamedTagAsInt("nextSignalType",-1)&ST_UNTYPED) and ret[0]==1000)
            {
        		ret[0]=0;
        	}
        }

        if(ret[0]!=0 and ret[0]!=1000)
        {
        	DH.ClearAll();
        }
        if(factors.GetNamedTagAsInt("nextPrivateStateEx",-1)!=-1)
        {
        	string s33;
        	if(factors.GetNamedTagAsInt("nextFaceSignal",-1)!=-1)
            {
	        	s33=(cast<Z7Signal>(Router.GetGameObject(Str.ToInt(factors.GetNamedTag("nextFaceSignal"))))).privateName;
        	}
            else
        	if(factors.GetNamedTagAsInt("nextFaceSignalDefault",-1)!=-1)
            {
	        	s33="default "+(cast<Signal>(Router.GetGameObject(Str.ToInt(factors.GetNamedTag("nextFaceSignalDefault"))))).GetLocalisedName();        		
        	}
        	DH.SetDebugInfo("dhi-nextstate","next ("+s33+") signal in state "+factors.GetNamedTag("nextPrivateStateEx"),
            "следующий сигнал ("+s33+") в состоянии "+factors.GetNamedTag("nextPrivateStateEx"));
        }
        DH.SetDebugInfo("dhi-state","signal in state "+ret[0],"собственное состояние "+ret[0]);
        if(ret[0]==0 or ret[0]==100)
        {
        	currentTrainId=-1;
        }

 	return ret;
 }

 public void UpdateSign(Message msg)
 {
 	int requestPrivateStateEx=-1;
 	int speed=-1;
 	int[] rel;
  	string[] tok;
        if(msg.minor=="Update")
        {
        	rel=CheckForState();
		requestPrivateStateEx=rel[0];

		if(oldPrivateStateEx==requestPrivateStateEx)
        {
			return;
		}
		privateStateEx=requestPrivateStateEx;
                if(currentTrainId!=-1)
                {
	                PostMessage(me,"CTRL","InitSpeed^"+currentTrainId,0.01);
                }
       	        PostMessageToPrevSignals(ST_STATION+ST_UNTYPED,"CTRL","Update",0.2);
	}
	LC.OnLights(privateStateEx,mainMode);
	oldPrivateStateEx=privateStateEx;
	DoSetSignalStateEx(privateStateEx);
        if(currentTrainId!=-1)
        {
                PostMessage(me,"CTRL","InitSpeed^"+currentTrainId,0.01);
        }

	if(mn)
    {
		PostMessage(me,"RefreshBrowser","",1.5);
	}
	PostMessage(null,"Signal","Updated",2.0);
 }

 public void UpdateSignForce(int state)
 {
 	int requestPrivateStateEx=state;
 	int speed=-1;
 	int[] rel;
  	string[] tok;
        /*
	if(oldPrivateStateEx==requestPrivateStateEx)
    {
		return;
	}
        */
	privateStateEx=requestPrivateStateEx;
	//DoSetSpeedLimit(rel[1]/3.6);
        //PostMessageToNextSignals(ST_STATION+ST_UNTYPED,"SignalOpen","",0.2);
        if(!demoState)
        {
	        PostMessageToPrevSignals(ST_STATION+ST_UNTYPED,"CTRL","Update",0.2);
        }
	if(state>=100 and state<=102)
    {
		shuntMode=true;
	}
    else
    {
		shuntMode=false;
	}
	LC.OnLights(privateStateEx,mainMode);
	oldPrivateStateEx=privateStateEx;
	DoSetSignalStateEx(privateStateEx);
	if(mn)
    {
		PostMessage(me,"RefreshBrowser","",1.5);
	}
	if(!demoState)
		PostMessage(null,"Signal","Updated",2.0);
 }
 thread void  RunSignDemo()
 {
 	float sleep=10.0+Math.Rand(1.0,10.0);
	string scode="0,1,2,3,4,5,6,7,8,9,10,11,12,27,34,37,39,1000,100,101,102,";
        string[] tok=Str.Tokens(scode,",");
        int i=Math.Rand(0,tok.size()-1);
	int code=Str.ToInt(tok[i]);
 	while(demoState)
    {
               	code=Str.ToInt(tok[i]);
              	if(LC.CodeIsPresent(code))
                {
              		UpdateSignForce(code);
			privateName=code+"";
			ShowName("");
	 		Sleep(sleep);              		
              	}
              	i++;
              	if(i==(tok.size()))
                {
              		i=0;
              		if(LC.aLMDF.size())
                    {
	              		LC.LinkPropertyValue("currentLMDF");
		 		Sleep(sleep);              		
	              	}
              	} 		
 	}
 }
 	
 public void UpdateSignDemo(string state)
 {
 	if(state=="Demo.true")
    {
 		demoState=true;
 		RunSignDemo();
 	}else{
 		demoState=false;
 	}
 }

 public void UpdateSignStartup()
 {
	LC.OnLights(privateStateEx,mainMode);
	DoSetSignalStateEx(privateStateEx);
	if(mn)
    {
		PostMessage(me,"RefreshBrowser","",1.5);
	}
 }


 public void UpdateSignSpeed(string val)
      { //val= trainId
 	int id=Str.ToInt(val);
 	float sp=-1;
	if(id>0)
    {
	 	Train tr=cast<Train>(Router.GetGameObject(id));
	 	currentTrainId=id;
		if(!tr)
			return;
		int pr=tr.GetTrainPriorityNumber();
	 	if(pr==1)
        {
	 		sp=speed1.GetNamedTagAsInt(privateStateEx,-1)/3.6;
	 	}
	 	if(pr==2)
        {
	 		sp=speed2.GetNamedTagAsInt(privateStateEx,-1)/3.6;
	 	}
	 	if(pr==3)
        {
	 		sp=speed3.GetNamedTagAsInt(privateStateEx,-1)/3.6;
	 	}
		SetSpeedLimit(sp);
	 }
     else
     {
		SetSpeedLimit(-1.0);	
	 }
 }

 public void Control(Message msg)
 {
	string[] sm=Str.Tokens(msg.minor,"^");
	if(msg.minor=="Update" or msg.minor=="Close" or msg.minor=="UpdateGroup" or msg.minor=="CloseGroup")
    {
		//if(privateStateEx!=1000)
			UpdateSign(msg);
	}
	if(msg.minor=="Demo.true" or msg.minor=="Demo.false")
    {
		UpdateSignDemo(msg.minor);
	}
	
	if(msg.minor=="ShuntMode.true")
    {
		shuntMode=true;
		msg.minor="Update";
		UpdateSign(msg);
	}
    else
	if(msg.minor=="ShuntMode.false")
    {
		shuntMode=false;
		msg.minor="Update";
		UpdateSign(msg);
	}
    else
	if(msg.minor=="Snow.true")
    {
		SetSnow(true);
	}
    else
	if(msg.minor=="Snow.false")
    {
		SetSnow(false);
	}
	if(msg.minor=="Startup")
    {
		UpdateSignStartup();
	}
	


	if(sm.size()<2)
    {
		return;
	}
	if(sm[0]=="Force")
    {
		UpdateSignForce(Str.ToInt(sm[1]));
	}
	if(sm[0]=="Select")
    {
		if(sm[1]==stationName)
        {
			SetFXAttachment("stabl",GetAsset().FindAsset("selectsign"));
		}
        else
		if(sm[1]=="@@")
        {
			SetFXAttachment("stabl",null);
		}
        else
		if(sm[1]==""+privateId)
        {
			SetFXAttachment("stabl",GetAsset().FindAsset("selectsign"));
		}
	}
	if(sm[0]=="InitSpeed")
    {
		UpdateSignSpeed(sm[1]);
	}
	if(sm[0]=="AOMShunt")
    {
		if(signalType&ST_SHUNT)
        {
			int mode=Str.ToInt(sm[1]);
			//autoOpenMode=mode;
		}
	}
	if(GetAutoOpenMode()&AOM_SEMIAUTO)
    {
		//PostMessage(null,"Signal","StateChanged2",0.01);
	}
 }

 public void DoSetSignalStateEx(int code)
 {
        bool extended=true;
	int st=LC.GetSignalStateEx(code,extended);
	if(st==-1 or !extended)
    {
	 	SetSignalState(st,"");
	}
    else
    {
	 	SetSignalStateEx(st,"");
 	}
 }

 public void PostMessageToPrevSignals(int lTypeSignals,string major,string minor,float delay)
 {
 	GSTrackSearch GS=BeginTrackSearch(false);
 	MapObject mo=GS.SearchNext();
        while(mo)
        {
                if((mo.isclass(Z7Signal)) and ( ! GS.GetFacingRelativeToSearchDirection()))
                { //    
                	int stype=(cast<Z7Signal>mo).GetSignalType();
                	if( (stype & lTypeSignals) )
                    {
                		if(stype&ST_STATION and (cast<Z7Signal>mo).privateStateEx==100){
                			
                		}
                        else
                        {
	               			PostMessage(mo,major,minor,delay);
        	       			break;
        	       		}
                	}
                }
                else
		if(mo.isclass(Z7MrkRepeaterCustom) and !GS.GetFacingRelativeToSearchDirection() )
        {
                   //!!!   ?
			GS=(cast<Z7MrkRepeaterCustom>mo).BeginTrackSearch(false);
		}

        	mo=GS.SearchNext();
        }
 }

 public void PostMessageToAllNextShuntSignals(string major,string minor,float delay)
 {
 	GSTrackSearch GS=BeginTrackSearch(true);
 	MapObject mo=GS.SearchNext();
        while(mo)
        {
                if((mo.isclass(Z7Signal)) and (  GS.GetFacingRelativeToSearchDirection()))
                            { //    
                	int stype=(cast<Z7Signal>mo).GetSignalType();
                	if( (stype & ST_SHUNT) )
                    {
				{
	               			PostMessage(mo,major,minor,delay);
        	       		}
                	}
                	if(stype&(ST_STATION+ST_UNTYPED))
                    {
                		break;
                	}
                }
		if(mo.isclass(Z7MrkRepeaterCustom) and GS.GetFacingRelativeToSearchDirection() )
        {
//!!!   ?
			GS=(cast<Z7MrkRepeaterCustom>mo).BeginTrackSearch(true);
		}

        	mo=GS.SearchNext();
        }
 }


 public void PostMessageToNextSignals(int lTypeSignals,string major,string minor,float delay)
 {
 	GSTrackSearch GS=BeginTrackSearch(true);
 	MapObject mo=GS.SearchNext();
        while(mo)
        {
                if((mo.isclass(Z7Signal)) and (  GS.GetFacingRelativeToSearchDirection()))
                { //    
                	int stype=(cast<Z7Signal>mo).GetSignalType();
                	if( (stype & lTypeSignals) )
                    {
                		if(stype&ST_STATION and (cast<Z7Signal>mo).privateStateEx==100)
                        {
                			
                		}
                        else
                        {
	               			PostMessage(mo,major,minor,delay);
        	       			break;
        	       		}
                	}
                }
		if(mo.isclass(Z7MrkRepeaterCustom) and GS.GetFacingRelativeToSearchDirection() )
        {
//!!!   ?
			GS=(cast<Z7MrkRepeaterCustom>mo).BeginTrackSearch(true);
		}

        	mo=GS.SearchNext();
        }
 }

 public int IsOpen()
 {
        int ret=1;
 	if(privateStateEx==0 or privateStateEx==100 or privateStateEx==1000)
    {
 		ret=0;
 	}
 	return ret;
 }


 public void AddRT(string rt)
 {
 	route.SetNamedTag(route.CountTags(),rt);
 }

 public void AddPackRT(string packrt)
 {
        if(packrt=="" or packrt==null){
        	return;
        }
 	string[] s=Str.Tokens(packrt,"^");
 	int i=0;
 	route.Clear();
 	for(i=0;i<s.size();i++)
    {
 		AddRT(s[i]);
 	}
 }


 public void SetProperties(Soup db)
 {
 	inherited(db);
	KUID kd=db.GetNamedTagAsKUID("skin1");
	if(kd)
    {
		sc.SetSkin(kd);
	}
    else
    {
		sc.SetSkin(-1);
	}
	isCtrlSignal=db.GetNamedTagAsBool("isCtrlSignal",false);
	if(isCtrlSignal)
    {	
		SetDefaultMeshVisible(false);
	}
    else
    {
		SetDefaultMeshVisible(true);		
	}

	scbboxplace=db.GetNamedTagAsInt("scbboxplace",1);
	kd=null;
	kd=db.GetNamedTagAsKUID("scbbox1");
	if(kd and bc)
    {
		if(!isCtrlSignal)
        {
			bc.SetBox(kd,scbboxplace);
		}
	}

 	signalType=db.GetNamedTagAsInt("signalType",prGetSignalType());
 	lightCmd.Copy(db.GetNamedSoup("lightCmd"));
 	SetPrivateName(db.GetNamedTag("privateName"));
 	SetPrivateId(db.GetNamedTagAsInt("privateId",-1));
 	mainMarkerId=db.GetNamedTagAsInt("mainMarkerId",-1);
 	shuntMode=db.GetNamedTagAsBool("shuntMode");
 	orderMode=db.GetNamedTagAsBool("orderMode");

 	mainMode=db.GetNamedTagAsInt("mainMode",0);
 	SetControlMode(db.GetNamedTagAsInt("controlMode",CM_UNDEF));
 	//SetAutoOpenMode(db.GetNamedTagAsInt("autoOpenMode",AOM_AUTO));
        string ss=GetAsset().GetStringTable().GetString("hold_mainmode");
        int i=-1;
        if(ss=="")
        {
        	i=-2;
        }
        else
        {
        	i=Str.ToInt(ss);
        }
        if(i>-1)
        {
        	mainMode=i;
        }

 	privateStateEx=db.GetNamedTagAsInt("privateStateEx",0);
 	oldPrivateStateEx=db.GetNamedTagAsInt("oldPrivateStateEx",0);
        /*
 	if(GetSignalType() & ST_STATION){
 		privateStateEx=0;
 		oldPrivateStateEx=0;
 	}
        */
	stationName=db.GetNamedTag("stationName");

 	Soup lcSoup=db.GetNamedSoup("LCProperties");
 	if(lcSoup)
    {
	 	LC.SetProperties(lcSoup);
	}
	
	Soup fhcSoup=db.GetNamedSoup("FHC");
	if(fhcSoup and FHC)
    {
		FHC.SetProperties(fhcSoup);
	}

//!e  ?
//	LC.OnLights(privateStateEx,mainMode);
//	DoSetSignalStateEx(privateStateEx);

	speed1.Copy(db.GetNamedSoup("speed1"));
	speed2.Copy(db.GetNamedSoup("speed2"));
	speed3.Copy(db.GetNamedSoup("speed3"));
        
	if(speed1.CountTags()==0)
    {
		speed1=InitSpeedTable(1);
	}
	if(speed2.CountTags()==0){
		speed2=InitSpeedTable(2);
	}
	if(speed3.CountTags()==0)
    {
		speed3=InitSpeedTable(3);
	}
        currentSpeed=db.GetNamedTagAsFloat("currentSpeed");
        if(currentSpeed==0.0)
        	currentSpeed=-1.0;
        SetSpeedLimit(currentSpeed);

        AddPackRT(db.GetNamedTag("route"));

        SetGate(db.GetNamedTagAsInt("isGate",0));

  	Setup();
	SetPreIn(db.GetNamedTagAsInt("isPreInSign",0));
	//SetPreIn(0);
 }

 public Soup GetProperties(void)
 {
 	Soup db=inherited();
 	db.SetNamedTag("class","Z7Signal");
 	db.SetNamedTag("GetSignalType()",GetSignalType());
 	
 	db.SetNamedTag("privateName",privateName);
 	db.SetNamedTag("privateId",privateId);
 	db.SetNamedTag("privateStateEx",privateStateEx);
	db.SetNamedTag("oldPrivateStateEx",oldPrivateStateEx);
	db.SetNamedSoup("LCProperties",LC.GetProperties());
	db.SetNamedSoup("lightCmd",lightCmd);
	db.SetNamedTag("shuntMode",shuntMode);
	db.SetNamedTag("orderMode",orderMode);
	db.SetNamedTag("mainMarkerId",mainMarkerId);
	db.SetNamedTag("isCtrlSignal",isCtrlSignal);
	Soup sup1=Constructors.NewSoup();
	sup1.Copy(speed1);
	db.SetNamedSoup("speed1",sup1);
	Soup sup2=Constructors.NewSoup();
	sup2.Copy(speed2);
	db.SetNamedSoup("speed2",sup2);
	Soup sup3=Constructors.NewSoup();
	sup3.Copy(speed3);
	db.SetNamedSoup("speed3",sup3);  
	db.SetNamedTag("mainMode",mainMode);
	db.SetNamedTag("controlMode",controlMode);
	//db.SetNamedTag("autoOpenMode",autoOpenMode);
	db.SetNamedTag("stationName",stationName);
	db.SetNamedTag("signalType",signalType);
	db.SetNamedTag("isPreInSign",isPreInSign);
	db.SetNamedTag("isGate",isGate);
	db.SetNamedTag("currentSpeed",currentSpeed);
	int i=0;
	string s="";
	for(i=0;i<route.CountTags();i++)
    {
		string s1=route.GetIndexedTagName(i);
		string s2=route.GetNamedTag(s1);
		s=s+s2+"^";
		db.SetNamedTag("route",s);
	}

	if(FHC)
    {
		db.SetNamedSoup("FHC",FHC.GetProperties());
	}
	if(sc.skin1)
		db.SetNamedTag("skin1",sc.skin1.GetKUID());

	if(bc)
		if(bc.box1)
        {
			db.SetNamedTag("scbbox1",bc.box1.GetKUID());
		}
	db.SetNamedTag("scbboxplace",scbboxplace);
	return db;
 }


 public int GetSignalType()
 {
 	inherited();
 	int i=0;
 	if(LC)
    {	
 		i=LC.GetSignalType();
 	}
 	return signalType | i;
 }


 public int prGetSignalType()
 {
 	return ST_UNTYPED;
 }

 public void Setup()
 {
	if(!setupState)
    {
		return;
	}
        /*
	if(privateId==-1)
    {
		return;
	}
        */
        cntRunSetup++;
        if(cntRunSetup!=2)
        {
        	return;
        }
	PostMessage(null,"Ready",privateId,0.5);
	setupState=false;
	SetXTabl(privateId);
 }

 public void InitFreeHead()
 {
 	if(ST.GetString("is_freehead")=="1")
    {
 		FHC=new FreeHeadController();
 		FHC.Init(me);
 	}
 }

 thread void z7signend()
 {
 	int i;
 	while(isGate)
    {
 		for(i=0;i<6;i++)
        {
			SetFXAttachment("stabl",GetAsset().FindAsset("z7signend1")); 
			Sleep(0.02);
			SetFXAttachment("stabl",GetAsset().FindAsset("z7signend2")); 
			Sleep(0.02);
 		}	

		Sleep(0.75);
 	}
 }
 thread void z7signendchecktrack()
 {
 	while(isGate)
    {
	 	GSTrackSearch GS=BeginTrackSearch(true);
 		MapObject mo=GS.SearchNext();
	 	Z7Signal ret=null;
        	while(mo)
            {
                	if( !(mo.isclass(Z7Signal)) and (GS.GetFacingRelativeToSearchDirection()) and  mo.isclass(Signal) )
                    { //
	                        PostMessage(me,"CTRL","Update",0.01);
	       			break;
	                }
        		mo=GS.SearchNext();
	        }
	        Sleep(30.0);
 	}
 }

 public void SetGate(int val)
 {
 	if(isGate==val)
    {
 		return;
 	}
 	inherited(val);
 	if(! (GetSignalState()&ST_UNTYPED) )
    {
 		return;
 	}
 	if(val==1)
      { // gate to default
 		z7signend();
		z7signendchecktrack();
 	}
 }


 public void SetupMainController()
 {
		Trigger[] trlist=World.GetTriggerList();
		int i;
		bool found=false;
		for(i=0;i<trlist.size();i++)
        {
			if(trlist[i].isclass(Z7SupertriggerCustom))
            {
				found=true;
				mController=cast<Z7SupertriggerCustom>trlist[i];
				break;
			}
		}
		if(!found)
        {
			Exception("!!! Not Found MainController !!! Place MainController and repeat");
		}
 }


 public void Init(Asset self)
 {
 	inherited(self);
 	setupState=true;
 	DH.Init(me);
	ST=GetAsset().GetStringTable();
	
	string slinzt=ST.GetString("linz_type");
	if(slinzt=="")
    {
		linz_type=0;
	}
    else
    {
		linz_type=Str.ToInt(slinzt);
	}

	string slkreflect=ST.GetString("lk_reflect");
	if(slkreflect=="")
    {
		lk_reflect=0;
	}
    else
    {
		lk_reflect=Str.ToInt(slkreflect);
	}

	lk_reflect_twinpoint=ST.GetString("lk_reflect_twinpoint");
 	lk_reflect_twinpoint=TrainUtil.StrSubst(lk_reflect_twinpoint,"","");	

 	ChangeCountTables(7);
 	LC=new Z7LightController(); //ab
 	LC.Init(me);
 	LC.LoadLMDF(new Z7LightMdf_YGR());

	AddHandler(me,"MapObject","View-Details","ViewDetails");
  	AddHandler(me,"Object","Enter","Enter");
  	AddHandler(me,"Object","Leave","Enter");
  	AddHandler(me,"RefreshBrowser","","RefreshBrowser");
	AddHandler(me,"RevalNameStation","","RevalNameStation");
	AddHandler(me,"CTRL","","Control");
	AddHandler(me,"AddLightCmd","","StartMainLightLoop");
		

  	signalType=prGetSignalType();
  	InitFreeHead();
  	SetXTabl(-1);
  	sc.Init(me);
	sc.SetSkin(-1);
	if(ST.GetString("is_scbbox")=="1")
    {
		bc=new ZSCBBoxController();	  	
	  	bc.Init(me);
		//bc.SetBox(-1);
	}
 }
};