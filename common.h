//
// common.gs
//
//  Copyright (C) 2003 Auran Developments Pty Ltd
//  All Rights Reserved.
//
//
// Miscellaneous utility classes and methods.
//

include "trainz.gs"
include "browser.gs"
include "world1.gs"
include "BaseIndustry.gs"
include "ConsistHelperInfo.gs"
include "Interface.gs"



//! Tracking item used in shunting so a trigger and name can be associated with a vehicle.
//
// See Also:
//     TrainUtil
//
class ShuntTrack
{
	public Vehicle vehicle;  //!< Vehicle to watch.
	public Trigger trigger;  //!< Trigger where the vehicle should be dropped off at.
	public string name;      //!< Readable user-friendly name for the vehicle.
};


//! Custom schedule command that sends a message to a train to blast its horn.
//
// See Also:
//     Command, CustomCommand, Schedule
//
class AiHornMsg isclass CustomCommand
{
	//! Method called by the scheduler.
	bool Execute(Train train, int px, int py, int pz)
	{
        train.SoundHorn();
		return true;
	}
};



//! Utility class with various miscellaneous functions.
//
// See Also:
//     ScenarioSupport, ShuntTrack
//    
final static class TrainUtil 
{

  //
  // Method definitions
  //

  //! String substitution method that replaces a sub string of a given major string with a replacement sub-string.
  //
  // In the following code example, the <b results> string would be <n "Gnomes are your enemies!">
  // because we specify via <b remove> that we want the string "friends" to be substituted with the
  // contents of <b replace>, which coincidentally is "enemies" and has the opposite meaning.
  //
  //<code>
  //string ourString = "Gnomes are your friends!";
  //string remove    = "friends";
  //string replace   = "enemies";
  //
  //string results   = TrainUtil.StrSubst(ourString, remove, replace);
  //</code>
  //
  // Param:  s        String to find the sub-string in to replace.
  // Param:  remove   Sub-string contained in <i s> that is to be replaced.  The first instance of 
  //                  this parameter in <i s> will be replaced.  For this method to work, this 
  //                  parameter must not exceed <i s> in length and must be a genuine sub-string of
  //                  <i s>.
  // Param:  replace  Replacement string that is to be inserted where <i remove> is within <i s>.
  //                  This string does not have to be the same size as <i remove> and can even be
  //                  longer than <i s> - the return string will be expanded/contracted as necessary.
  //
  // Returns:
  //     Returns a new string based on <i s> such that the sub-string defined by <i remove> is 
  //     replaced with <i replace>.  If <i s> is empty, <i remove> cannot be found as a sub-string
  //     of <i s> or <i remove> is larger than <i s>, an empty string will be returned to indicate 
  //     failure.
  //
  public string StrSubst(string s, string remove, string replace);

  //! Gets the trimmed left side of a string that doesn't contain any of the specified characters.
  //
  // In the following code example, the <b results> string would be <n "I like this string, it l">
  // because in <b cutOff>, we specify that the string is to be trimmed when either the 'x' or 'o'
  // character occurs (whichever is first).
  //
  //<code>
  //string ourString = "I like this string, it looks exciting!";
  //string cutOff    = "xo";
  //
  //string results   = TrainUtil.GetUpTo(ourString, cutOff);
  //</code>
  //
  // Param:  propertyString  String to extract the left portion of.
  // Param:  searchChars     Search string that contains the delimiter characters that define where
  //                         <i propertyString> is to be trimmed.
  //
  // Returns:
  //     Returns a trimmed <i propertyString> starting from the left side and ending at the 
  //     character just before where a character from <i searchChars> is encountered.  If none of
  //     the characters in <i searchChars> are found in <i propertyString>, an empty string is
  //     returned.
  //
  // See Also:
  //     Str
  //
  public string GetUpTo(string propertyString, string searchChars);

  //! Gets the trimmed right side of a string that doesn't contain any of the specified characters.
  //
  // In the following code example, the <b results> string would be <n "ks exciting!"> because in
  // <b cutOff>, we specify that the string is to be trimmed when either the 'l' or 'o' character
  // occurs, whichever is first when going through the string from right to left (i.e. backwards).
  //
  //<code>
  //string ourString = "I like this string, it looks exciting!";
  //string cutOff    = "lo";
  //
  //string results   = TrainUtil.GetAfter(ourString, cutOff);
  //</code>
  //
  // Param:  propertyString  String to extract the right portion of.
  // Param:  searchChars     Search string that contains the delimiter characters that define where
  //                         <i propertyString> is to be trimmed.
  //
  // Returns:
  //     Returns a trimmed <i propertyString> starting from the right side and ending at the 
  //     character just before where a character from <i searchChars> is encountered.  If none of
  //     the characters in <i searchChars> are found in <i propertyString>, an empty string is
  //     returned.
  //
  // See Also:
  //     Str
  //
  public string GetAfter(string propertyString, string searchChars);

  //! Determines if a string exists as an element in an array of strings.
  //
  // Param:  strArray   Array of strings to search in.
  // Param:  searchStr  String to search for in <i strArray>
  //
  // Returns:
  //     Returns true if an element of <i strArray> matches the string <i searchStr> exactly, false
  //     otherwise.
  //
  // See Also:
  //     Str
  //
  public bool AlreadyThereStr(string[] strArray, string searchStr);

  //! Determines if a string is prefixed with the given prefix string.
  //
  // Param:  searchStr  String to check for the existence of <i prefixStr> in at the start.
  // Param:  prefixStr  Prefix string to search for in the start of <i searchStr>.
  //
  // Returns:
  //     Returns true if <i prefixStr> is a sub-string at the start of <i searchStr>, false 
  //     otherwise.
  //
  public bool HasPrefix(string searchStr, string prefixStr);

  //! Determines if a string is suffixed with the given suffix string.
  //
  // Param:  searchStr  String to check for the existence of <i sufixStr> in at the end.
  // Param:  sufixStr   Suffix string to search for at the end of <i searchStr>.
  //
  // Returns:
  //     Returns true if <i sufixStr> is a sub-string at the end of <i searchStr>, false otherwise.
  //
  public bool HasSufix(string searchStr, string sufixStr);

  //! Compares the two given list of strings against each other.
  //
  // Param:  strListOne  First list of strings.
  // Param:  strListTwo  Second list of strings to be compared with.
  //
  // Returns:
  //     Returns true if <i strListOne> and <i strListTwo> have the same amount of strings in them
  //     and each string of the corresponding index in both arrays is equal.  If there is any 
  //     difference between the contents of <i strListOne> and <i strListTwo>, false is returned.
  //
  public bool CompareStrLists(string[] strListOne, string[] strListTwo);


  //! Random Boolean generator method.
  //
  // Returns:
  //     Returns a random Boolean value (either true or false).
  //
  public bool RandBool(void);

  //! Creates a train consist from the given Soup consist definition.
  //
  // Param:  trainSoup      Consist definition to create the train from.  This Soup must be in the 
  //                        format returned by World::GetSurveyorSavedConsist().
  // Param:  trackMarkName  Name of the track mark to create the train consist at.
  // Param:  direction      Direction to orient the train in.  If true, the train will face in the
  //                        same direction as the track mark does, otherwise false and the train 
  //                        will face in the opposite direction of the track mark.
  //
  // Returns:
  //     Returns a reference to the created Train consist, null otherwise.
  //
  // See Also:
  //     World::CreateTrain(KUID[],string,bool), World::GetSurveyorSavedConsist(), 
  //     World::GetSurveyorSavedConsistList()
  //
  public Train CreateTrainFromSoup(Soup trainSoup, string trackMarkName, bool direction);


  //! Waits until all of the vehicles tracked by the tracking array are in the train of the given loco.
  //
  // Param:  loco      Loco of the consist.
  // Param:  tracking  Tracking array.
  //
  public void WaitUntilHas(Vehicle loco, ShuntTrack[] tracking);

  //! Determines if a vehicle is in a particular train consist.
  //
  // Param:  train    Train argument.
  // Param:  vehicle  Vehicle argument.
  //
  // Returns:
  //     Returns true if vehicle is in train, false otherwise.
  //
  public bool IsInTrain(Train train, Vehicle vehicle);

  //! Determines if the vehicles in an array are in a particular train consist.
  //
  // Param:  train     Train argument.
  // Param:  vehicles  Vehicle argument.
  //
  // Returns:
  //     Returns true if all of the vehicles in the array are in the train consist, false
  //     otherwise.
  //
  public bool AreInTrain(Train train, Vehicle[] vehicles);

  //! Determines if a train is in the given trigger.
  //
  // Param:  runningThread  Thread that called this method.
  // Param:  train          Train argument.
  // Param:  trigger        Trigger argument.
  //
  // Returns:
  //     Returns true if the train is in the given trigger, false otherwise.
  //
  public bool IsTrainInTrigger(GameObject runningThread, Train train, Trigger trigger);

  //! Determines if part of the train (i.e. any vehicle) is in the given trigger.
  //
  // Param:  runningThread  Thread that called this method.
  // Param:  train          Train argument.
  // Param:  trigger        Trigger argument.
  //
  // Returns:
  //     Returns true if the train is in the given trigger, false otherwise.
  //
  public bool IsPartTrainInTrigger(GameObject runningThread, Train train, Trigger trigger);

  //! Determines if a vehicle is in a trigger.
  //
  // Note:
  //     This method doesn't work as it should as individual vehicle tracking was not supported
  //     when it was originally written.
  //
  // Param:  runningThread  Thread that called this method.
  // Param:  vehicle        Vehicle argument.
  // Param:  trigger        Trigger argument.
  //
  // Returns:
  //     Returns true if any part of the train that vehicle belongs to is in the trigger, false
  //     otherwise.
  //
  public bool IsInTrigger(GameObject runningThread, Vehicle vehicle, Trigger trigger);

  //! A generic turntable handler.  Guides train through a turntable with appropriate icons.
  //
  // Param:  runningThread  The running thread.
  // Param:  train          Train argument.
  // Param:  turntable      Name of turntable.
  //
  public void RunTurnTable(GameObject runningThread, Train train, string turntable);

  //! Couple up two consists.
  //
  // Param:  train     Train argument.
  // Param:  coupleTo  Train argument.
  //
  // Returns:
  //     Returns the newly coupled up consist.
  //
  public Train DoCoupleUp(Train train, Train coupleTo);

  //! Waits for a decoupling operation to be performed on the given train at on the specified vehicle.
  //
  // Note: 
  //     It is assumed the train is stopped and already in position.
  //
  // Param:  train   Train where uncoupling is going to occur (i.e. split into two consists).
  // Param:  wagons  Offset into train where uncoupling will take place (i.e. 1 for rear most 
  //                 wagon, 2 for 2nd rear most etc.)
  //
  // Returns:
  //     Returns the decoupled consist if successful, null otherwise.
  //
  public Train DoDecouple(Train train, int wagons);


  //
  // Method implementations
  // 

  //
  // String substitution
  //
  public string StrSubst(string s, string remove, string replace)
  {
    if (!s  or  (s.size() < 1))
      return "";

    string[] stringArray = Str.Tokens(s, remove);
    string returnStr = "";
    int i, subsize = stringArray.size()-1;
    for (i = 0; i < subsize; i++)
      returnStr = returnStr + stringArray[i] + replace;

    returnStr = returnStr + stringArray[subsize]; 
    return returnStr;
  }


  //
  // Gets the portion of the string up to the given character
  //
  public string GetUpTo(string propertyString, string searchChars)
  {
    int i, p;
    for (i = 0; i < propertyString.size(); i++)
      for (p = 0; p < searchChars.size(); p++)
        if (propertyString[i] == searchChars[p])
          return propertyString[,i];

    return "";
  }

  //
  // Gets the rear portion of the string up to the given character(s).  Right-to-left reverse
  // version of GetUpTo()
  // 
  public string GetAfter(string propertyString, string searchChars)
  {
    int i, p;
    int rearIndex = 0;

    for (i = 0; i < propertyString.size(); i++)
      for (p = 0; p < searchChars.size(); p++)
        if (propertyString[i] == searchChars[p])
          rearIndex = i;
    
    if (rearIndex)
      return propertyString[rearIndex+1,];

    return "";
  }


  //
  // Searches for a string in the string array
  //
  public bool AlreadyThereStr(string[] strArray, string searchStr)
  {
    int i;
    for (i = 0; i < strArray.size(); i++)
      if (searchStr == strArray[i])
        return true;

    return false;
  }

  //
  // Determines if a string is prefixed with the given prefix string.
  //
  public bool HasPrefix(string searchStr, string prefixStr)
  {
    if (searchStr  and  prefixStr)
      if (searchStr.size() >= prefixStr.size())
        if (prefixStr == searchStr[,prefixStr.size()])
          return true;

    return false;
  }
  
  //
  // Determines if a string is sufixedwith the given sufix string.
  //
  public bool HasSufix(string searchStr, string sufixStr)
  {
    if (searchStr  and  sufixStr)
      if (searchStr.size() >= sufixStr.size())
        if (sufixStr == searchStr[searchStr.size()-sufixStr.size(),])
          return true;

    return false;
  }


  public bool CompareStrLists(string[] strListOne, string[] strListTwo)
  {
    if (!strListOne  or  !strListTwo)
      return false;

    if (strListOne.size() != strListTwo.size())
      return false;

    int i;
    for (i = 0; i < strListOne.size(); i++)
      if (strListOne[i] != strListTwo[i])
        return false;

    return true;
  }



  //
  // Random Boolean method. Returns a random Boolean value.
  //
  public bool RandBool(void)
  {
    return (bool) Math.Rand(0, 2);
  }


  //
  // Creates a train consist from the given soup consist definition.
  //
  public Train CreateTrainFromSoup(Soup trainSoup, string trackMarkName, bool direction)
  {
    ConsistHelperInfo trainToCreate = new ConsistHelperInfo();
    trainToCreate.SetProperties(trainSoup);

    int trainLength = trainToCreate.vehicles.size();
    int p;

    KUID[] vehicleKUID = new KUID[trainLength];

    for (p = 0; p < trainLength; p++)
    {
//      Interface.Log("TrainUtil.CreateTrainFromSoup> - Assigning vehicle #" + p + " " + trainToCreate.vehicles[p].vehicle.GetName() + " : " + trainToCreate.vehicles[p].vehicle.GetHTMLString());
      vehicleKUID[p] = new KUID();
      vehicleKUID[p] = trainToCreate.vehicles[p].vehicle;
//      Interface.Log("TrainUtil.CreateTrainFromSoup> - Vehicle found is " + vehicleKUID[p].GetName());
    }


    Train newTrain = World.CreateTrain(vehicleKUID, trackMarkName, direction);

    if (!newTrain)
      return null;

    // reverse any vehicles that need to be reversed
    Vehicle[] trainVehicles = newTrain.GetVehicles();
    for (p = 0; p < trainLength; p++)
    {
      if (!trainToCreate.vehicles[p].facing)
      {
        Interface.Log("TrainUtil.CreateTrainFromSoup> - Reversing vehicle " + p); // temp/debug
        trainVehicles[p].Reverse();
      }
    }

    return newTrain;
  }


  //
  // Waits until all of the vehicles tracked by the tracking array are in the given train.
  //
  public void WaitUntilHas(Vehicle loco, ShuntTrack[] tracking)
  {
    int i;
    bool pickupDone = false;
    Train train;
    Message msg;

    Interface.Log("Start of WaitUntilHas(), array is " + tracking.size() + " elements big!"); // test/debug

    // wait until consist has all the vehicles from the tracking array.
    while (!pickupDone)
    {
      on "Vehicle", "Coupled", msg:
      {
//        Interface.Print("Coupling occurred in WaitUntilHas()");
        pickupDone = true;
        train = loco.GetMyTrain();

        // verify that all are in the shunting consist
        for (i = 0; i < tracking.size(); i++)
        {
          if(train != tracking[i].vehicle.GetMyTrain())
          {
            pickupDone = false;
            break;
          }
        }
      }
    }

    Interface.Log("End of WaitUntilHas()"); // test/debug
  }


  //
  // Determines if a vehicle is in a particular train consist.
  //
  public bool IsInTrain(Train train, Vehicle vehicle)
  {
    return (vehicle.GetMyTrain() == train);
  }


  //
  // Determines if the vehicles in an array are in a particular train consist.
  //
  public bool AreInTrain(Train train, Vehicle[] vehicles)
  {
    int i;  // array index/loop counter

    for (i = 0; i < vehicles.size(); i++)
    {
      if (vehicles[i].GetMyTrain() != train)
        return false;
    }

    return true;
  }


  //
  // Determines if a train is in a trigger (i.e. all of its vehicles)
  //
  public bool IsTrainInTrigger(GameObject runningThread, Train train, Trigger trigger)
  {
    return (trigger.ReEnter(train.GetId()));
  }


  //
  // Determines if part of the train (i.e. any vehicle) is in the given trigger
  //
  public bool IsPartTrainInTrigger(GameObject runningThread, Train train, Trigger trigger)
  {
    return (trigger.ReEnter(train.GetId()));
  }


  //
  // Determines if a vehicle is in the given trigger.
  //
  public bool IsInTrigger(GameObject runningThread, Vehicle vehicle, Trigger trigger)
  {
    return (trigger.ReEnter(vehicle.GetMyTrain().GetId()));
  }


  //
  // A generic turntable handler. (exit/entry point triggers to be added)
  //
  //  train     -  Train of loco that is to be turned around (it is assumed that it will fit and
  //               isn't attached to rollingstock).
  //  turntable -  Name of trigger in center of the turntable.
  //
  public void RunTurnTable(GameObject runningThread, Train train, string turntable)
  {
    Trigger tgTurntable = cast<Trigger> Router.GetGameObject(turntable);
    Message msg;

    Interface.Log("Start of RunTurnTable()"); // test/debug

    // enable trigger sniffing on the turntable
    runningThread.Sniff(tgTurntable, "Object", "Enter", true);

//    Interface.Log("waiting for object-enter for the turntable");

    // wait until the loco is stopped on the turntable trigger
    wait()
    {
      on "Object", "Enter", msg :
      {
        // verify that it is the right loco on the turntable
        if (msg.src == train)
          Interface.Log("(correct train)");
        if (msg.dst == tgTurntable)
          Interface.Log("(correct turntable)");

        if ((msg.src == train) and (msg.dst == tgTurntable))
          // get out of here, as it is the loco on the turntable
          break;

        // wasn't the loco stopping on turntable, keep waiting
        continue;
      }
    }
  
    Interface.Log("waiting for trigger-stopped 'Trig TurnTable'");
    // wait for loco to stop on turntable
    Navigate.OnTrigger(runningThread, train, "Trig TurnTable", Navigate.TRIGGER_STOPPED);
//    Interface.SetObjective("Turn the locomotive around.", "turn.tga");
    //Interface.SetObjectiveIcon("turn.tga");

    Interface.Log("waiting for trigger-leave 'Trig TurnTable'");

    // wait for turntable to turn.(checkpoint)
    Navigate.OnTrigger(runningThread, train, "Trig TurnTable", Navigate.TRIGGER_LEAVE);

    // disable trigger sniffing on turntable
    runningThread.Sniff(tgTurntable, "Object", "Enter", false);

    Interface.Log("End of RunTurnTable()"); // test/debug
  }


  //
  // Couple up two consists
  //
  public Train DoCoupleUp(Train train, Train coupleTo)
  {
    int trainsize, coupletosize, tempTrainSize;
    Message msg;
    Vehicle tempVehicle;
    Train tempTrain;

    Interface.Log("Start of DoCoupleUp()");

    // Initialize some values
    trainsize = train.GetVehicles().size();
    coupletosize = coupleTo.GetVehicles().size();

    // enable coupling masks so the consists can be coupled up
    train.SetCouplingMask(Vehicle.COUPLE_BOTH);
    coupleTo.SetCouplingMask(Vehicle.COUPLE_BOTH);


    // go into cycle until a consist that consists of the train and couple up train is detected
    wait()
    {
      on "Vehicle", "Coupled", msg :
      {
        // get access to the vehicle and train that generated the coupling message
        tempVehicle = cast <Vehicle> msg.src;
        tempTrain = tempVehicle.GetMyTrain();
        tempTrainSize = tempTrain.GetVehicles().size();

        // verify coupling was on the right consist - this is done by checking the vehicle that the
        // message was generated by is part of the a train that contains all vehicles from both 
        // 'train' & 'coupleTo' and nothing else
        if (AreInTrain(tempTrain, train.GetVehicles()) and AreInTrain(tempTrain, coupleTo.GetVehicles()) and
            ((trainsize + coupletosize) == tempTrainSize))
        {
          // block off coupling and decoupling on the new coupled up consist
          tempTrain.SetCouplingMask(Vehicle.COUPLE_NONE);
          tempTrain.SetDecouplingMask(Vehicle.COUPLE_NONE);

          // coupled on consists we wanted, so break out of here
          break;
        }
        else
        {
          // wrong consist being coupled up, go on and await next coupled message...
          continue;
        }
      }
    }

    Interface.Log("End of DoCoupleUp()");
    return train;
  }


  //
  // Waits for a decoupling operation to be performed on the given train at on the specified vehicle.
  // It is assumed the train is stopped and already in position.
  //
  // Returns the decoupled consist if successful, null otherwise.
  //
  //  train  -  Train where uncoupling is going to occur (i.e. split into two consists)
  //  offset -  Offset into train where uncoupling will take place (i.e. 1 for rear most wagon, 2 for 
  //            2nd rear most etc.)
  //
  public Train DoDecouple(Train train, int wagons)
  {
    int trainsize, decoupledoffset;
    Message msg;
    Vehicle rearVehicle, decoupledVehicle;
    Train decoupledConsist = null;
    Vehicle[] trainVehicles;


    Interface.Log("Start of DoDecouple()");

    // Initialize various variables
    trainVehicles = train.GetVehicles();
    trainsize = trainVehicles.size();
    rearVehicle = trainVehicles[trainsize-1];
    decoupledoffset = trainsize - wagons;
    decoupledVehicle = trainVehicles[decoupledoffset];


    // Setup decoupling masks so uncoupling can take place
    // being careful here - vehicles may not always be oriented towards train's direction
    if (!trainVehicles[decoupledoffset-1].GetDirectionRelativeToTrain())
      trainVehicles[decoupledoffset-1].SetDecouplingMask(Vehicle.COUPLE_FRONT);
    else
      trainVehicles[decoupledoffset-1].SetDecouplingMask(Vehicle.COUPLE_BACK);

    if (!trainVehicles[decoupledoffset].GetDirectionRelativeToTrain())
      trainVehicles[decoupledoffset].SetDecouplingMask(Vehicle.COUPLE_BACK);
    else
      trainVehicles[decoupledoffset].SetDecouplingMask(Vehicle.COUPLE_FRONT);

//    trainVehicles[decoupledoffset-1].SetDecouplingMask(Vehicle.COUPLE_FRONT);
//    trainVehicles[decoupledoffset].SetDecouplingMask(Vehicle.COUPLE_BACK);


    // wait for messages
    wait()
    {
      // Wait for the user to do decouple
      on "Vehicle", "Decoupled", msg :
      {
        // verify the uncoupling takes place on the actual train between the required vehicles
        if (msg.src == trainVehicles[decoupledoffset-1])
        {
          decoupledConsist = rearVehicle.GetMyTrain();

          // lock off the seperated consists 
          train.SetCouplingMask(Vehicle.COUPLE_NONE);
          train.SetDecouplingMask(Vehicle.COUPLE_NONE);
          decoupledConsist.SetCouplingMask(Vehicle.COUPLE_NONE);
          decoupledConsist.SetDecouplingMask(Vehicle.COUPLE_NONE);

          break;
        }
        else
        {
          continue;
        }
      }
    }

    Interface.Log("End of DoDecouple()");
    return decoupledConsist;
  }

};


//! Utility class with methods to generate HTML code suitable for use in the %Trainz.
//
// This static class provides many methods to generate HTML code that can be used in the Browser
// and <l PropertyObject::GetDescriptionHTML() property window>.  In most case, these methods return
// a string with HTML code in it.  All methods are implemented in the <b \Trainz\scripts\common.gs> 
// script file and can be viewed for those who are curious to what the methods actually do.
//
// As well as generic HTML methods, several methods are defined that are specifically used by the 
// BaseIndustry class to generate HTML for an industry's properties window.
//
// Link methods:
//  - public string  <b StartLink>  (string link, string tooltip, string extraParams)
//  - public string  <b StartLink>  (string link, string tooltip)
//  - public string  <b StartLink>  (string link)
//  - public string  <b EndLink>    ()
//  - public string  <b MakeLink>   (string link, string text, string tooltip, string extraParams)
//  - public string  <b MakeLink>   (string link, string text, string tooltip)
//  - public string  <b MakeLink>   (string link, string text)
//
// Image methods:
//  - public string  <b MakeImage>  (string image, bool isKuid, int width, int height, string image_over, string extraParams)
//  - public string  <b MakeImage>  (string image, bool isKuid, int width, int height, string image_over)
//  - public string  <b MakeImage>  (string image, bool isKuid, int width, int height)
//  - public string  <b MakeImage>  (string image)
//  - public string  <b MakeImage>  (string image, bool isKuid)
//  - public string  <b MakeImage>  (string image, bool isKuid, int width)
//
// Font formatting methods:
//  - public string  <b MakeBold>             (string text)
//  - public string  <b MakeItalic>           (string text)
//  - public string  <b MakeFontSizeTiny>     (string text)
//  - public string  <b MakeFontSizeSmall>    (string text)
//  - public string  <b MakeFontSizeMedium>   (string text)
//  - public string  <b MakeFontSizeLarge>    (string text)
//  - public string  <b StartFontColor>       (string fontColor)
//  - public string  <b StartFontColorBlack>  ()
//  - public string  <b StartFontColorWhite>  ()
//  - public string  <b EndFontColor>         ()
//  - public string  <b MakeFontColor>        (string text, string fontColor)
//  - public string  <b MakeFontColorBlack>   (string text)
//  - public string  <b MakeFontColorWhite>   (string text)
//
// Table methods:
//  - public string  <b StartTable>  (string extraParams)
//  - public string  <b StartTable>  ()
//  - public string  <b EndTable>    ()
//
// Table cell and row methods:
//  - public string  <b StartRow>        (string extraParams)
//  - public string  <b StartRow>        ()
//  - public string  <b EndRow>          ()
//  - public string  <b StartCell>       (string extraParams)
//  - public string  <b StartCell>       ()
//  - public string  <b EndCell>         ()
//  - public string  <b MakeCell>        (string text, string extraParams)
//  - public string  <b MakeCell>        (string text)
//  - public string  <b MakeSpacerCell>  (int width)
//  - public string  <b MakeRow>         (string text, string extraParams)
//  - public string  <b MakeRow>         (string text)
//  - public string  <b MakeTable>       (string text, string extraParams)
//  - public string  <b MakeTable>       (string text)
//
// Time conversion methods:
//  - public string  <b GetFloatAsTimeString>  (float time)
//  - public float   <b GetTimeStringAsFloat>  (string time)
//  - public string  <b PadZerosOnFront>       (string value, int maxSize)
//  - public string  <b GetCleanTimeString>    (string time)
//  - public string  <b GetCleanFloatString>   (float val)
//  - public int     <b GetSecondsFromFloat>   (float time)
//  - public int     <b GetMinutesFromFloat>   (float time)
//  - public int     <b GetHoursFromFloat>     (float time)
//
// String and number conversion methods:
//  - public float   <b ConvertUnitsToValue>  (float units, float mass, string format)
//  - public float   <b ConvertValueToUnits>  (float other, float mass, string format)
//  - public string  <b UnitsToString>        (float units, float mass, string format)
//  - public float   <b StringToUnits>        (string str, string format)
//
// Button and page formatting methods:
//  - public string  <b RadioButton>  (string urlString, bool active)
//  - public string  <b CheckBox>     (string urlString, bool active)
//  - public string  <b HelpButton>   (string urlString)
//  - public string  <b StartIndent>  (int width)
//  - public string  <b EndIndent>    ()
//  - public string  <b StartBorder>  (string extraParams)
//  - public string  <b EndBorder>    ()
//
// See Also:
//     Browser, BaseIndustry, PropertyObject, TrainUtil
//
static class HTMLWindow
{
	// Function declarations:

	// table methods
	public string StartTable(string extraParams);
	public string StartTable() { return StartTable(""); }
	public string EndTable();

	// link methods
	public string StartLink(string link, string tooltip, string extraParams);
	public string StartLink(string link, string tooltip);
	public string StartLink(string link);
	public string EndLink();
	public string MakeLink(string link, string text, string tooltip, string extraParams);
	public string MakeLink(string link, string text, string tooltip);
	public string MakeLink(string link, string text);

	// image methods
	public string MakeImage(string image, bool isKuid, int width, int height, string image_over, string extraParams);
	public string MakeImage(string image, bool isKuid, int width, int height, string image_over) { return MakeImage(image, isKuid, width, height, image_over, ""); }
	public string MakeImage(string image, bool isKuid, int width, int height) { return MakeImage(image, isKuid, width, height, "", ""); }
	public string MakeImage(string image) { return MakeImage(image, false, -1, -1, "", ""); }
	public string MakeImage(string image, bool isKuid) { return MakeImage(image, isKuid, -1, -1, "", ""); }
	public string MakeImage(string image, bool isKuid, int width) { return MakeImage(image, isKuid, width, -1, "", ""); }

	// font formatting methods
	public string MakeBold(string text);
	public string MakeItalic(string text);
	public string MakeFontSizeTiny(string text);
	public string MakeFontSizeSmall(string text);
	public string MakeFontSizeMedium(string text);
	public string MakeFontSizeLarge(string text);
	public string StartFontColor(string fontColor);
	public string StartFontColorBlack();
	public string StartFontColorWhite();
	public string EndFontColor();
	public string MakeFontColor(string text, string fontColor);
	public string MakeFontColorBlack(string text);
	public string MakeFontColorWhite(string text);

	// table, cell and row methods
	public string StartRow(string extraParams);
	public string StartRow() { return StartRow(""); }
	public string EndRow();
	public string StartCell(string extraParams);
	public string StartCell() { return StartCell(""); }
	public string EndCell();
	public string MakeCell(string text, string extraParams);
	public string MakeCell(string text) { return MakeCell(text, ""); }
	public string MakeSpacerCell(int width);
	public string MakeRow(string text, string extraParams);
	public string MakeRow(string text) { return MakeRow(text, ""); }
	public string MakeTable(string text, string extraParams);
	public string MakeTable(string text) { return MakeTable(text, ""); }

  // time conversion methods
  public string GetFloatAsTimeString(float time);
  public float GetTimeStringAsFloat(string time);
  public string PadZerosOnFront(string value, int maxSize);
  public string GetCleanTimeString(string time);
  public string GetCleanFloatString(float val);
  public int GetSecondsFromFloat(float time);
  public int GetMinutesFromFloat(float time);
  public int GetHoursFromFloat(float time);

  // string and number conversion methods
  public float ConvertUnitsToValue(float units, float mass, string format);
  public float ConvertValueToUnits(float other, float mass, string format);
  public string UnitsToString(float units, float mass, string format);
  public float StringToUnits(string str, string format);

	// button and page formatting methods
	public string RadioButton(string urlString, bool active);
	public string CheckBox(string urlString, bool active);
	public string HelpButton(string urlString);
	public string StartIndent(int width);
	public string EndIndent(void);
	public string StartBorder(string extraParams);
	public string EndBorder(void);




	string GetReadableTime(int seconds, bool returnMassTimes)
	{
    StringTable strTable = Constructors.GetTrainzStrings();
		string retString = (string)seconds;

		if (!returnMassTimes)
		{
			if (seconds < 60)
			{
				retString = strTable.GetString("common_display_time0");
			}
			else
			{
				if (seconds >= 60)
				{
					int minutes = (int)seconds / 60;
					seconds = seconds - (minutes * 60);
					retString = strTable.GetString1("common_display_time1", (string)minutes);
				}
			}
		}
		else
		{
			// starts in seconds.
			if (seconds >= 60)
			{
				int minutes = (int)seconds / 60;
				seconds = seconds - (minutes * 60);
				retString = strTable.GetString2("common_display_time2", (string)minutes, (string)seconds);

				if (minutes >= 60)
				{
					int hours = (int)minutes / 60;
					minutes = minutes - (hours * 60);
					retString = strTable.GetString3("common_display_time3", (string)hours, (string)minutes, (string)seconds);
		
					if (hours > 24)
					{
						int days = (int)hours / 24;
						hours = hours - (days * 24);
						retString = strTable.GetString4("common_display_time4", (string)days, (string)hours, (string)minutes, (string)seconds);

						if (days > 7)
						{
							int weeks = (int)days / 7;
							days = days - (weeks * 7);
							retString = strTable.GetString5("common_display_time5", (string)weeks, (string)days, (string)hours, (string)minutes, (string)seconds);

							if (weeks > 52)
							{
								int years = (int) weeks / 52;
								weeks = weeks - (years * 52);
								retString = strTable.GetString6("common_display_time6", (string)years, (string)weeks, (string)days, (string)hours, (string)minutes, (string)seconds);

								if (years > 100)
								{
									int centuries = (int)years / 100;
									years = years - (centuries * 100);
									retString = strTable.GetString7("common_display_time7", (string)centuries, (string)years, (string)weeks, (string)days, (string)hours, (string)minutes, (string)seconds);
								}
							}
						}
					}
				}
			}
		}

		return retString;
	}

	string GetReadableTime(int seconds)
	{
		return GetReadableTime(seconds, false);
	}

  // GetQueueRoundedPercent() is not documented yet.
  public string GetPercentBarCode(int width, int height, int pct)
  {
    string paramOutput = StartTable("bgcolor=#454545 border=0 width=" + (string)width + " height=" + (string)height) + StartRow();

    if (pct == 0.0)
      paramOutput = paramOutput + MakeCell("");

    if (pct == 100.0)
      paramOutput = paramOutput + MakeCell("", "bgcolor=#00FF00");

    if (pct > 0.0 and pct < 100.0)
      paramOutput = paramOutput +  MakeCell("", "bgcolor=#00FF00 width=" + (string)pct + "%") + MakeCell("");

    paramOutput = paramOutput + EndRow() + EndTable();

    return paramOutput;
  }

  // GetQueueRoundedPercent() is not documented yet.
  public int GetQueueRoundedPercent(ProductQueue queue, Asset asset)
  {
    ProductFilter pf = Constructors.NewProductFilter();
    pf.AddProduct(asset);

    float pct = 0.0;
    int roundedpct = 0;

    pct = (float)queue.CountProductMatching(pf) / (float)queue.GetQueueSize();
    roundedpct = pct * 100.0;
    if (roundedpct < 0.0)
      roundedpct = 0.0;
    if (roundedpct > 100.0)
      roundedpct = 100.0;

    return roundedpct;
  }

  // Generates HTML code that shows a percentage bar indicator on a queue for a certain product type.
  //
  // The HTML code generated by this method is all within a single table row and totally wrapped
  // up in pair of <n &lt;tr&gt;> and <n &lt;/tr&gt;> tags.  In this row, the icon of the product
  // identified by <i asset> is displayed followed by a percentage bar that indicates how many
  // products of type <i asset> are in <i queue> along with appropriate text descriptions.
  //
  // It is worth noting that the <n&lt;img&gt;> tag used to display the product icon uses the
  // special <bi TRS2004> <n kuid> option (i.e. not part of standard HTML).  %Trainz will find the
  // icon for the KUID specified and use that for the image.  For example,
  // <n &lt;img kuid='&lt;KUID:-3:1011&gt;' width=64 height=64&gt;> will display the icon for the
  // oil product.
  //
  // Param:  genIndustry  ??
  // Param:  queue        Product queue to generate the percentage bar from.
  // Param:  asset        Product asset to get the percentage of in <i queue> and where the icon to
  //                      display with the percentage can be found.  It is assumed that the product
  //                      asset has an icon, as specified by the <m icon-texture> option in its
  //                      <n config.txt> file.
  //
  // Returns:
  //     Returns the HTML code that is a table row containing the product icon and the percentage bar.
  //
  // See Also:
  //     Asset::GetLocalisedName(), KUID::GetHTMLString(), ProductQueue::GetQueueCount(), 
  //     ProductQueue::GetQueueSize() 
  //
  public string GetPercentHTMLCode(BaseIndustry genIndustry, ProductQueue queue, Asset asset)
  {
    StringTable strTable = Constructors.GetTrainzStrings();
    string paramOutput = " ";
		//BaseIndustry genIndustry = cast<BaseIndustry> industry;

    float pct = 0.0;
    int roundedpct = 0;
		int k;
		int i = 0;

    KUID kuid = asset.GetKUID();
    string icon = kuid.GetHTMLString();
    string name = asset.GetLocalisedName();

    ProductFilter pf = Constructors.NewProductFilter();
    pf.AddProduct(asset);
    
    pct = (float)queue.CountProductMatching(pf) / (float)queue.GetQueueSize();
    roundedpct = pct * 100.0;
    if (roundedpct < 0.0)
      roundedpct = 0.0;
    if (roundedpct > 100.0)
      roundedpct = 100.0;

    paramOutput = paramOutput + StartRow();
    paramOutput = paramOutput + MakeCell(MakeImage(icon, true, 64, 64), "width=64");
    paramOutput = paramOutput + StartCell("valign=middle") + name + ": ";
		
		int foundProductIndex = 0;
		if (genIndustry)
		{
      //Interface.Log(">> Industry is Valid");
			for (k = 0; k < genIndustry.industryProductInfoCollection.ipicCollection.size(); k++)
			{
 				IndustryProductInfoComplete ipic = genIndustry.industryProductInfoCollection.ipicCollection[k];
				if (ipic.GetProduct() == asset)
				{
					if (ipic.GetVehicleKUID())
					{
            //Interface.Log(">> Vehicle is Valid");
						int countOfVehicle = ((queue.GetQueueCount() + ipic.GetPerVehicleAmount() - 1) / ipic.GetPerVehicleAmount());
						KUID vehicleKuid = ipic.GetVehicleKUID();
						string vehicleIcon = vehicleKuid.GetHTMLString();
            string displayType;
            
						// DO NOT TRANSLATE THE BELOW ENGLISH STRINGS. THEY WILL GET TRANSLATED IN THE UnitsToString function.
            if (ipic.GetDisplayType() == ipic.DISPLAY_TYPE_MASS)
							displayType = "Tonnes";
						if (ipic.GetDisplayType() == ipic.DISPLAY_TYPE_VOLUME)
							displayType = "Litres";
						if (ipic.GetDisplayType() == ipic.DISPLAY_TYPE_COUNT)
							displayType = "Items";
						//if (queue.GetQueueCount() > 1)
						//	displayType = displayType + "s";

            // Perform conversion on count to translate to type.
            float massPerUnit = asset.GetConfigSoup().GetNamedTagAsFloat("mass");
            float count = queue.CountProductMatching(pf);
            string strConvCount = HTMLWindow.UnitsToString(count, massPerUnit, displayType);

            paramOutput = paramOutput + (string)countOfVehicle + " x " + MakeImage(vehicleIcon, true, 64, 32) + MakeItalic("(" + strConvCount + ")");

					}
					else
						paramOutput = paramOutput + (string)queue.CountProductMatching(pf);

					foundProductIndex = k;
					break;
				}
			}
		}
		else
			paramOutput = paramOutput + (string)queue.CountProductMatching(pf);
		
		paramOutput = paramOutput + "<br>";
		
		// Figure out how long till this queue is full/empty.
		if (genIndustry)
		{
			for (k = 0; k < genIndustry.industryProductInfoCollection.ipicCollection.size(); k++)
			{
				IndustryProductInfoComplete ipic = genIndustry.industryProductInfoCollection.ipicCollection[k];
				if (ipic.GetProduct() == asset)
				{
					int queueIndex = genIndustry.industryProductInfoCollection.GetQueueIndex(k, queue);
					if (queueIndex > -1)
					{
						for (i = 0; i < ipic.processes.size(); i++)
						{
							IndustryProductInfoProcess ipip = ipic.processes[i];

							int inNumTimes = 0;
							int outNumTimes = 0;
							if (ipip.DoesUseInput())
              {
                if (genIndustry.GetProcessInput(ipip.GetProcessName(), queue, ipic.GetProduct()) > 0)
								  inNumTimes = queue.GetQueueCount() / genIndustry.GetProcessInput(ipip.GetProcessName(), queue, ipic.GetProduct());
              }
							
							if (ipip.DoesUseOutput())
              {
                if (genIndustry.GetProcessOutput(ipip.GetProcessName(), queue, ipic.GetProduct()) > 0)
								  outNumTimes = queue.GetQueueSpace() / genIndustry.GetProcessOutput(ipip.GetProcessName(), queue, ipic.GetProduct());
              }

							if (inNumTimes > 0)
							{
								int totsecs = genIndustry.GetProcessDuration(ipip.GetProcessName()) * inNumTimes;
								Interface.Log("IN: proc dur: " + genIndustry.GetProcessDuration(ipip.GetProcessName()) + " + numTime: " + inNumTimes);
								paramOutput = paramOutput + MakeFontColorWhite(strTable.GetString1("common_percent_html_till_empty", GetReadableTime(totsecs)));
							}

							if (outNumTimes > 0)
							{
								int totsecs = genIndustry.GetProcessDuration(ipip.GetProcessName()) * outNumTimes;
								Interface.Log("OUT: proc dur: " + genIndustry.GetProcessDuration(ipip.GetProcessName()) + " + numTime: " + outNumTimes);
								paramOutput = paramOutput + MakeFontColorWhite(strTable.GetString1("common_percent_html_till_full", GetReadableTime(totsecs)));
							}
							
						}
					}
				}
			}
		}
		
		paramOutput = paramOutput + "<br>" + GetPercentBarCode(100, 8, roundedpct);
    paramOutput = paramOutput + "<BR>" + EndFontColor() + EndCell() + EndRow();

    return paramOutput;
  }
  


  // old calling convention
  public string GetPercentHTMLCode(ProductQueue queue, Asset asset)
	{
		return GetPercentHTMLCode(null, queue, asset);
	}


  // Generates HTML code that displays input/output information for an industry process on the given queue for a certain product type.
  //
  // The HTML code generated by this method is all within a single table row and totally wrapped
  // up in pair of <n &lt;tr&gt;> and <n &lt;/tr&gt;> tags.  In this row, the icon of the product
  // identified by <i asset> is displayed followed by its name.  After that, two property links
  // are placed.  The first one is the production/consumption rate of <i process> to/from <i queue>
  // followed by the default initial size of <i queue>.  As these are property links, a user can click
  // on and edit them in a HTML window.  See PropertyObject::GetDescriptionHTML for details on property
  // URLs.
  //
  // It is worth noting that the <n&lt;img&gt;> tag used to display the product icon uses the
  // special <bi TRS2004> <n kuid> option (i.e. not part of standard HTML).  %Trainz will find the
  // icon for the KUID specified and use that for the image.  For example,
  // <n &lt;img kuid='&lt;KUID:-3:1011&gt;' width=64 height=64&gt;> will display the icon for the
  // oil product.
  //
  // Param:  industryInfo  Industry to get the properties from.
  // Param:  process       Name of the process in <i industry> process.
  // Param:  queue         Name of the queue to get input/output properties of when used by <i process>.
  // Param:  asset         Product type to get input/output rate of for <i queue> as well as being
  //                       used for an icon.
  // Param:  propertyName  Name of the property for use for editing the consumption/production rate
  //                       of <i process> when using <i queue>.
  // Param:  input         Input/output flag.  If true, the output rate of <i process> into <i queue>
  //                       will be put into the HTML.  When the false, the opposite will be done
  //                       where the input rate of <i process> from <i queue> will be used instead.
  //
  // Returns:
  //     Returns the HTML code that is a table row that has the product icon along with property
  //     links to edit the input/output rate of the process and the initial size of queue.
  //
  // See Also:
  //     Asset::GetLocalisedName(), Industry::GetProcessInput(), Industry::GetProcessOutput(),
  //     KUID::GetHTMLString(), ProductQueue::GetQueueCount(), ProductQueue::GetQueueSize(),
  //     BaseIndustry::GetDescriptionHTML()
  //
  public string GetInputOutputPropertyHTMLCode(BaseIndustryInfo industryInfo, string process, ProductQueue queue, Asset asset, string propertyName, bool input)
  {
    string paramOutput = " ";

    string propertyType;
    int rate;
    int initialValue;
    int processIndex = -1;
		BaseIndustry genIndustry = industryInfo.industry;
    StringTable strTable = Constructors.GetTrainzStrings();

    if (asset)
    {
      KUID kuid = asset.GetKUID();
      string icon = kuid.GetHTMLString();

			// Values for determining rate per minute.
			int timeValSecs = industryInfo.industry.GetProcessDuration(process);
			float multiplier = (float)timeValSecs / (float)60.0;
			if (multiplier == 0.0f)
				multiplier = 1.0f;

      int productIndex = genIndustry.industryProductInfoCollection.GetProductIndex(asset);
      if (productIndex > -1)
        processIndex = genIndustry.industryProductInfoCollection.GetProcessIndex(productIndex, process);
      
      string countType = "";
      if (input)
      {
        propertyType = "input-amount";
        rate = industryInfo.industry.GetProcessInput(process, queue, asset) / multiplier;
        countType = "initial-count";
      }
      else
      {
        propertyType = "output-amount";
        rate = industryInfo.industry.GetProcessOutput(process, queue, asset) / multiplier;
        countType = "ouitial-count";
      }
      ProductFilter pf = Constructors.NewProductFilter();
      pf.AddProduct(asset);
      initialValue = queue.CountProductMatching(pf);

      string assetName =  BrowserInterface.Quote(asset.GetLocalisedName());

      string rateToolTip = "";
      if (input)
        rateToolTip = strTable.GetString1("interface-industryinfo-name1", assetName);
      else
        rateToolTip = strTable.GetString1("interface-industryinfo-name2", assetName);
      
      paramOutput = paramOutput + "<font color=#FFFFFF>";
      
      paramOutput = paramOutput + MakeRow(
                                    MakeCell("", "width=10")
                                    + MakeCell( MakeImage(icon, true, 64, 64) , "width=64" )
                                    + MakeCell( MakeFontColorWhite(assetName) , "width=100" )
                                    + MakeCell( MakeFontColorWhite(MakeLink(industryInfo.Link(propertyType + "/" + propertyName + "/" + (string)processIndex), rate, rateToolTip)), "align=center width=100")
                                    + MakeCell( MakeFontColorWhite(MakeLink(industryInfo.Link(countType + "/" + propertyName + "/" + (string)processIndex), initialValue, strTable.GetString1("interface-industryinfo-name0", assetName))), "align=center width=100" )
                                  );
        
      //paramOutput = paramOutput + "<tr><td width=10></td><td width=64><img kuid='" + icon + "' width=64 height=64></td><td width=100><font color=#FFFFFF>" + assetName + "</font></td><td align=center width=100><font color=#FFFFFF><a href='live://property/" + propertyType + "/" + propertyName + "/" + (string)processIndex + "'>" + rate + "</a></font></td><td align=center width=100><font color=#FFFFFF><a href='live://property/" + countType + "/" + propertyName + "/" + (string)processIndex + "'>" + initialValue + "</a></font></td></tr>";
    }
    return paramOutput;
  }

/*
	// OBSOLETE, INCLUDED FOR BACKWARD COMPATIBILITY ONLY. PLEASE USE PREVIOUS FUNCTION INSTEAD.
  public string GetInputOutputPropertyHTMLCode(Industry industry, string process, ProductQueue queue, Asset asset, string propertyName, bool input)
  {
	Interface.WarnObsolete("HTMLWindow.GetInputOutputPropertyHTMLCode> this function is obsolete");

    string paramOutput = " ";

    string propertyType;
    int rate;
    int initialValue;
    int processIndex = -1;
		BaseIndustry genIndustry = cast<BaseIndustry> industry;

    if (asset)
    {
      KUID kuid = asset.GetKUID();
      string icon = kuid.GetHTMLString();

			// Values for determining rate per minute.
			int timeValSecs = industry.GetProcessDuration(process);
			float multiplier = (float)timeValSecs / (float)60.0;
			if (multiplier == 0.0f)
				multiplier = 1.0f;

      int productIndex = genIndustry.industryProductInfoCollection.GetProductIndex(asset);
      if (productIndex > -1)
        processIndex = genIndustry.industryProductInfoCollection.GetProcessIndex(productIndex, process);
      
      string countType = "";
      if (input)
      {
        propertyType = "input-amount";
        rate = industry.GetProcessInput(process, queue, asset) / multiplier;
        countType = "initial-count";
      }
      else
      {
        propertyType = "output-amount";
        rate = industry.GetProcessOutput(process, queue, asset) / multiplier;
        countType = "ouitial-count";
      }
      ProductFilter pf = Constructors.NewProductFilter();
      pf.AddProduct(asset);
      initialValue = queue.CountProductMatching(pf);

      string assetName = asset.GetLocalisedName();

      // If it's a passenger queue, then don't allow rate...
      if (assetName == "passenger")
      {
        paramOutput = paramOutput + MakeRow(
                                      MakeCell("", "width=10")
                                      + MakeCell( MakeImage(icon, true, 64, 64) , "width=64" )
                                      + MakeCell( MakeFontColorWhite(assetName) , "width=100" )
                                      + MakeCell( MakeFontColorWhite(" "), "align=center width=100")
                                      + MakeCell( MakeFontColorWhite(MakeLink("live://property/" + countType + "/" + propertyName + "/" + (string)processIndex, initialValue)), "align=center width=100" )
                                    );
      }
      else
      {
        paramOutput = paramOutput + MakeRow(
                                      MakeCell("", "width=10")
                                      + MakeCell( MakeImage(icon, true, 64, 64) , "width=64" )
                                      + MakeCell( MakeFontColorWhite(assetName) , "width=100" )
                                      + MakeCell( MakeFontColorWhite(MakeLink("live://property/" + propertyType + "/" + propertyName + "/" + (string)processIndex, rate)), "align=center width=100")
                                      + MakeCell( MakeFontColorWhite(MakeLink("live://property/" + countType + "/" + propertyName + "/" + (string)processIndex, initialValue)), "align=center width=100" )
                                    );
      }
        
      //paramOutput = paramOutput + "<tr><td width=10></td><td width=64><img kuid='" + icon + "' width=64 height=64></td><td width=100><font color=#FFFFFF>" + assetName + "</font></td><td align=center width=100><font color=#FFFFFF><a href='live://property/" + propertyType + "/" + propertyName + "/" + (string)processIndex + "'>" + rate + "</a></font></td><td align=center width=100><font color=#FFFFFF><a href='live://property/" + countType + "/" + propertyName + "/" + (string)processIndex + "'>" + initialValue + "</a></font></td></tr>";
    }
    return paramOutput;
  }
*/

  // GetInputOutputPropertyHTMLCode() is not documented yet.
  public string GetInputOutputPropertyHTMLCode(Industry industry, string process, ProductQueue queue, Asset asset, string propertyName, bool input)
  {
		if (cast<BaseIndustry>industry)
			Interface.Exception("HTMLWindow.GetInputOutputPropertyHTMLCode> this function is obsolete. Don't call it from BaseIndustry-derived classes");

    string paramOutput = " ";

    string propertyType;
    int rate;
    int initialValue;

    if (asset)
    {
      KUID kuid = asset.GetKUID();
      string icon = kuid.GetHTMLString();

      if (input)
      {
        propertyType = "input-amount";
        rate = industry.GetProcessInput(process, queue, asset);
      }
      else
      {
        propertyType = "output-amount";
        rate = industry.GetProcessOutput(process, queue, asset);
      }
      initialValue = queue.GetQueueCount();

      string assetName = asset.GetLocalisedName();

      paramOutput = paramOutput + "<tr><td width=10></td><td width=64><img kuid='" + icon + "' width=64 height=64></td><td width=100><font color=#FFFFFF>" + assetName + "</font></td><td align=center width=100><font color=#FFFFFF><a href='live://property/" + propertyType + "/" + propertyName + "'>" + rate + "</a></font></td><td align=center width=100><font color=#FFFFFF><a href='live://property/initial-count/" + propertyName + "'>" + initialValue + "</a></font></td></tr>";
      //paramOutput = paramOutput + "<a href='live://property/" + propertyType + "/" + propertyName + "'>" + rate + "</a> " + assetName;
    }
    return paramOutput;
  }


  // Generates HTML code that describes this industry in brief.
  //
  // This method returns HTML code displaying the icon, name and operational state of the Industry
  // specified by <i asset>.  No details specifics on queues or processes are included as part of
  // this method, only basic industry information.
  //
  // asset - Asset of the Industry to get the details of.  Use <l MeshObject::GetAsset  GetAsset>()
  //         on the Industry object to get this.
  //
  // Param:  industry                    ??
  // Param:  displayOnlineState          Indicates if the online state of the industry is to be
  //                                     displayed.  If true, <i scripletEnabled> will be processed.
  // Param:  scriptletEnabled            Flag indicating if the industry's scriplet is operational
  //                                     and running. If true, the <m "common_online_state_enabled">
  //                                     string from the <l Constructors::GetTrainzStrings  Trainz string table>
  //                                     will be appended to the HTML string indicating that the industry
  //                                     is currently operating.  Otherwise, the <m "common_online_state_disabled">
  //                                     string will be used, which indicates that the industry isn't operating.
  // Param:  displayCommodityLeve lTitle  If true, the <m "common_display_commodity_level"> string from
  //                                     the <l Constructors::GetTrainzStrings  Trainz string table> will
  //                                     be appended to the end of the string.  This is a header for the
  //                                     industry's current commodity levels.
  //
  // Returns:
  //     Returns the HTML code that is used as a header introducing this industry.
  //
  // See Also:
  //     StringTable, MeshObject::GetAsset()
  //
  public string GetAssetTitleHTMLCode(BaseIndustry industry, bool displayOnlineState, bool scriptletEnabled, bool displayCommodityLevelTitle)
  {
    KUID kuid = industry.GetAsset().GetKUID();
    string icon = kuid.GetHTMLString();
    string name = industry.GetLocalisedName();
    StringTable strTable = Constructors.GetTrainzStrings();
    
    // Print the header
    string header = "<p><b><font size=3 color=#FFFFFF>" + BrowserInterface.Quote(name) + "</font></b></p><BR>";
    header = header + "<font color=#FFFFFF><img kuid='" + icon + "' width=64 height=64> " + BrowserInterface.Quote(name);
    
    if (displayOnlineState)
      if (scriptletEnabled) 
        header = header + strTable.GetString("common_online_state_enabled");
      else
        header = header + strTable.GetString("common_online_state_disabled");
    header = header + "<BR>";
    
    if (industry.userDescription != "")
      header = header + "<i>" +  BrowserInterface.Quote(industry.userDescription) + "</i>";

    header = header + "</font>";
    if (displayCommodityLevelTitle)
      header = header + strTable.GetString("common_display_commodity_level");
    
    return header;
  }

  // Generates the code for a complete HTML page describing an industry.
  //
  // This method generates a complete page of statistics for the given BaseIndustry including
  // the industry's processes, queues and operation status.
  //
  // Param:  industry          Industry to get the complete details of.
  // Param:  scriptletEnabled  Flag indicating if the current operational state of the industry is
  //                           to be mentioned in returned HTML code.
  //
  // Returns:
  //     Returns the HTML code that shows the details of this industry in full.
  //
  // See Also:
  //     BaseIndustry::ViewDetails()
  //
  public string GetCompleteIndustryViewDetailsHTMLCode(BaseIndustry industry, bool scriptletEnabled)
  {
    string htmlCode = "";
    Asset asset = industry.GetAsset();
    int i;
    int l;
		int k;

    StringTable strTable = Constructors.GetTrainzStrings();
    if (asset)
    {
      htmlCode = htmlCode + HTMLWindow.GetAssetTitleHTMLCode(industry, true, scriptletEnabled, true);
      htmlCode = htmlCode + "<BR>";

      string productInList = "";
      string productOutList = "";
			string productDetails = "";

      int totalDisplayedItems = 0;

			for (k = 0; k < industry.industryProductInfoCollection.ipicCollection.size(); k++)
      {
				IndustryProductInfoComplete ipic = industry.industryProductInfoCollection.ipicCollection[k];
				
				for (i = 0; i < ipic.processes.size(); i++)
				{
          IndustryProductInfoQueues ipiq = ipic.processes[i].GetInputIPIQ();
					ProductQueue queue = null;
          if (ipiq)
            queue = ipiq.GetProductQueue();

          if (ipic.processes[i].DoesUseInput() and ipic.processes[i].GetVisibleInViewDetails(true) /*and ipic.processes[i].GetVisibleInSurveyor(true)*/)
					{
            if (ipic.processes[i].GetVisibleInViewDetailsProcessList(true))
            {
						  KUID kuid = ipic.GetProduct().GetKUID();
						  string icon = kuid.GetHTMLString();
						  productInList = productInList + HTMLWindow.MakeCell(
																							  HTMLWindow.MakeImage(icon, true, 32, 32)
																						  );


              totalDisplayedItems = totalDisplayedItems + 1;
              if (totalDisplayedItems >= 9)
              {
                productInList = productInList + HTMLWindow.EndRow() + HTMLWindow.StartRow();
                totalDisplayedItems = 0;
              }
            }

						// Grab information about input amounts/sizes.
						if (industry.GetProcessInput(ipic.processes[i].GetProcessName(), queue, ipic.GetProduct()) > 0)
						{
							productDetails = productDetails + HTMLWindow.GetPercentHTMLCode(industry, queue, ipic.GetProduct());
						}
					}
					
          
          ipiq = ipic.processes[i].GetOutputIPIQ();
					queue = null;
          if (ipiq)
            queue = ipiq.GetProductQueue();

					if (ipic.processes[i].DoesUseOutput() and ipic.processes[i].GetVisibleInViewDetails(false) /*and ipic.processes[i].GetVisibleInSurveyor(false)*/ )
					{
            if (ipic.processes[i].GetVisibleInViewDetailsProcessList(false))
            {
						  KUID kuid = ipic.GetProduct().GetKUID();
						  string icon = kuid.GetHTMLString();
						  productOutList = productOutList + HTMLWindow.MakeCell(
																								  HTMLWindow.MakeImage(icon, true, 32, 32)
																							  );

              totalDisplayedItems = totalDisplayedItems + 1;
              if (totalDisplayedItems >= 9)
              {
                productOutList = productOutList + HTMLWindow.EndRow() + HTMLWindow.StartRow();
                totalDisplayedItems = 0;
              }
            }

						// Grab information about output amounts/sizes.
						if (industry.GetProcessOutput(ipic.processes[i].GetProcessName(), queue, ipic.GetProduct()) > 0)
						{
							productDetails = productDetails + HTMLWindow.GetPercentHTMLCode(industry, queue, ipic.GetProduct());
						}
					}
				}

			}
      
      if (totalDisplayedItems == 0)
      {
        // Err okay fine, remove the CommodityLevelTitle...
        htmlCode = HTMLWindow.GetAssetTitleHTMLCode(industry, true, scriptletEnabled, false);
        htmlCode = htmlCode + "<BR>";
      }

			Asset core = Constructors.GetTrainzAsset();
			KUID kuid = core.LookupKUIDTable("texture-products");
			string arrowicon = kuid.GetHTMLString();
			
			if (totalDisplayedItems != 0)
        htmlCode = htmlCode + HTMLWindow.MakeTable(
															HTMLWindow.MakeRow(
																productInList 
																+ HTMLWindow.MakeCell( HTMLWindow.MakeImage( arrowicon, true, 32, 32 ) )
																+ productOutList
															)
														);

      htmlCode = htmlCode + HTMLWindow.MakeTable( HTMLWindow.MakeRow(productDetails) );


      htmlCode = htmlCode + "<BR>";
    }
    else
    {
      string header = strTable.GetString("common_view_industry_details");
    }

    return htmlCode;
  }


  // OBSOLETE. DO NOT USE
	public string GetAssetTitleHTMLCode(Asset asset, bool displayOnlineState, bool scriptletEnabled, bool displayCommodityLevelTitle)
  {
		Interface.WarnObsolete("GetAssetTitleHTMLCode> obsolete function");

    KUID kuid = asset.GetKUID();
    string icon = kuid.GetHTMLString();
    string name = asset.GetLocalisedName();
    StringTable strTable = Constructors.GetTrainzStrings();
    
    // Print the header
    string header = "<p><b><font size=3 color=#FFFFFF>" + BrowserInterface.Quote(name) + "</font></b></p><BR>";
    header = header + "<font color=#FFFFFF><img kuid='" + icon + "' width=64 height=64> " + name;
    
    if (displayOnlineState)
      if (scriptletEnabled) 
        header = header + strTable.GetString("common_online_state_enabled");
      else
        header = header + strTable.GetString("common_online_state_disabled");

    header = header + "</font>";
    if (displayCommodityLevelTitle)
      header = header + strTable.GetString("common_display_commodity_level");
    
    return header;
  }

	
  // OBSOLETE. DO NOT USE
  public string GetCompleteIndustryViewDetailsHTMLCode(GenericIndustry industry, bool scriptletEnabled)
  {
		Interface.WarnObsolete("GetCompleteIndustryViewDetailsHTMLCode> obsolete function");

    string htmlCode = "";
    Asset asset = industry.GetAsset();
    StringTable strTable = Constructors.GetTrainzStrings();
    if (asset)
    {
      htmlCode = htmlCode + HTMLWindow.GetAssetTitleHTMLCode(asset, true, scriptletEnabled, true);
      htmlCode = htmlCode + "<BR>";
      htmlCode = htmlCode + "<table>";

      // 
      // Find products that we are outputting.
      int i;
      int l;
      for (i = 0; i < industry.industryProductList.size(); i++)
      {
        if (industry.industryProductList[i].showInViewDetails)
          if (industry.GetProcessOutput(industry.industryProductList[i].processName, industry.industryProductList[i].queue, industry.industryProductList[i].asset) > 0 or industry.GetProcessInput(industry.industryProductList[i].processName, industry.industryProductList[i].queue, industry.industryProductList[i].asset) > 0)
            htmlCode = htmlCode + HTMLWindow.GetPercentHTMLCode(industry.industryProductList[i].queue, industry.industryProductList[i].asset);
      }

      htmlCode = htmlCode + "</table>";
      htmlCode = htmlCode + "<BR>";
    }
    else
    {
      string header = strTable.GetString("common_view_industry_details");
    }

    return htmlCode;
  }



	// Helper functions for quick HTML generation:

	public string StartTable(string extraParams)
	{
		if (extraParams != "")
			return "<table " + extraParams + ">";
		else
			return "<table>";

		return "";
	}

	public string EndTable()
	{
		return "</table>";
	}

  public string StartLink(string link, string tooltip, string extraParams)
  {
    string ret = "<a href='" + link + "'";
    
    if (tooltip)
      ret = ret + " tooltip='" + tooltip + "'";

    if (extraParams)
      ret = ret + " " + extraParams;

    ret = ret + ">";

		return ret;
  }

  public string StartLink(string link, string tooltip)
  {
		return StartLink(link, tooltip, "");
  }

	public string StartLink(string link)
	{
		return StartLink(link, "", "");
	}

	public string EndLink()
	{
		return "</a>";
	}

	public string MakeLink(string link, string text, string tooltip, string extraParams)
  {
		return StartLink(link, tooltip, extraParams) + text + EndLink();
  }

	public string MakeLink(string link, string text, string tooltip)
  {
    return MakeLink(link, text, tooltip, "");
  }

  public string MakeLink(string link, string text)
	{
    return MakeLink(link, text, "", "");
	}

	public string MakeImage(string image, bool isKuid, int width, int height, string image_over, string extraParams)
	{
		string ret = "";
		if (isKuid)
			ret = ret + "<img kuid='" + image + "'";
		else
			ret = ret + "<img src='" + image + "'";

		if (width >= 0)
			ret = ret + " width=" + (string)width;
		if (height >= 0)
			ret = ret + " height=" + (string)height;

		if (image_over != "")
			ret = ret + " mouseover=" + image_over;
		
		if (extraParams != "")
			ret = ret + " " + extraParams;

		ret = ret + ">";
		return ret;
	}

	public string MakeBold(string text)
	{
		return "<b>" + text + "</b>";
	}

	public string MakeItalic(string text)
	{
		return "<i>" + text + "</i>";
	}

	public string MakeFontSizeTiny(string text)
	{
		return "<font size=1>" + text + "</font>";
	}

	public string MakeFontSizeSmall(string text)
	{
		return "<font size=2>" + text + "</font>";
	}

	public string MakeFontSizeMedium(string text)
	{
		return "<font size=3>" + text + "</font>";
	}

	public string MakeFontSizeLarge(string text)
	{
		return "<font size=4>" + text + "</font>";
	}

	public string StartRow(string extraParams)
	{
		if (extraParams != "")
			return "<tr " + extraParams + ">";
		else
			return "<tr>";

		return "";
	}

	public string EndRow()
	{
		return "</tr>";
	}

	public string StartCell(string extraParams)
	{
		if (extraParams != "")
			return "<td " + extraParams + ">";
		else
			return "<td>";

		return "";
	}

	public string EndCell()
	{
		return "</td>";
	}

	public string MakeCell(string text, string extraParams)
	{
		return StartCell(extraParams) + text + EndCell();
	}

	public string MakeSpacerCell(int width)
	{
		return StartCell("width=" + (string)width + "") + EndCell();
	}

	public string MakeRow(string text, string extraParams)
	{
		if (extraParams != "")
			return StartRow(extraParams) + text + EndRow();
		else
			return StartRow() + text + EndRow();

		return "";
	}

	public string StartFontColor(string fontColor)
	{
		return "<font color=#" + fontColor + ">";
	}

  public string StartFontColorBlack()
  {
    return StartFontColor("000000");
  }
	
  public string StartFontColorWhite()
  {
    return StartFontColor("FFFFFF");
  }
	
	public string EndFontColor()
	{
		return "</font>";
	}
	
	public string MakeFontColor(string text, string fontColor)
	{
		return StartFontColor(fontColor) + text + EndFontColor();
	}

  public string MakeFontColorBlack(string text)
  {
    return MakeFontColor(text, "000000");
  }

  public string MakeFontColorWhite(string text)
  {
    return MakeFontColor(text, "FFFFFF");
  }

	public string MakeTable(string text, string extraParams)
	{
		return StartTable(extraParams) + text + EndTable();
	}

  public float GetTimeStringAsFloat(string time)
  {
    // ensure its in the correct format.
    time = GetCleanTimeString(time);

    int hour = 0;
    int mins = 0;
    int secs = 0;
    float retTime = 0.0;

    // Passed in param is in format xx:xx:xx
    hour = Str.ToFloat(time[0,2]);
    mins = Str.ToFloat(time[3,5]);
    secs = Str.ToFloat(time[6,8]);

    // Calculate time as a value from 0 to 1, where 0 is midday and 0.5 is midnight.
    if (hour < 12)
      retTime = 0.5 + hour / 24.0 + mins / 1440.0 + secs / 86400.0;
    else
      retTime = (hour - 12) / 24.0 + mins / 1440.0 + secs / 86400.0;

    return retTime;
  }

  public string GetFloatAsTimeString(float time)
  {
    /*
  	float gametime = time;
    int hours, minutes, seconds;

		gametime = gametime - 0.5;
    if (gametime < 0.0)
      gametime = gametime + 1.0;
    gametime = gametime * 24.0;
      // add 0.5 sec for rounding
    gametime = gametime + 0.5 / 3600.0;

    hours = gametime;
    gametime = gametime - hours;
    gametime = gametime * 60.0;

    minutes = gametime;
    gametime = gametime - minutes;
    gametime = gametime * 60.0;

    seconds = gametime;
    */

    return PadZerosOnFront((string)GetHoursFromFloat(time), 2) + ":" + PadZerosOnFront((string)GetMinutesFromFloat(time), 2) + ":" + PadZerosOnFront((string)GetSecondsFromFloat(time), 2);

  }

  public int GetSecondsFromFloat(float time)
  {
  	float gametime = time;
    int hours, minutes, seconds;

		gametime = gametime - 0.5;
    if (gametime < 0.0)
      gametime = gametime + 1.0;
    gametime = gametime * 24.0;
      // add 0.5 sec for rounding
    gametime = gametime + 0.5 / 3600.0;

    hours = gametime;
    gametime = gametime - hours;
    gametime = gametime * 60.0;

    minutes = gametime;
    gametime = gametime - minutes;
    gametime = gametime * 60.0;

    seconds = gametime;

    return seconds;

  }

  public int GetMinutesFromFloat(float time)
  {
  	float gametime = time;
    int hours, minutes, seconds;

		gametime = gametime - 0.5;
    if (gametime < 0.0)
      gametime = gametime + 1.0;
    gametime = gametime * 24.0;
      // add 0.5 sec for rounding
    gametime = gametime + 0.5 / 3600.0;

    hours = gametime;
    gametime = gametime - hours;
    gametime = gametime * 60.0;

    minutes = gametime;
    gametime = gametime - minutes;
    gametime = gametime * 60.0;

    return minutes;
  }

  public int GetHoursFromFloat(float time)
  {
  	float gametime = time;
    int hours, minutes, seconds;

		gametime = gametime - 0.5;
    if (gametime < 0.0)
      gametime = gametime + 1.0;
    gametime = gametime * 24.0;
      // add 0.5 sec for rounding
    gametime = gametime + 0.5 / 3600.0;

    hours = gametime;
    gametime = gametime - hours;
    gametime = gametime * 60.0;

    return hours;
  }

  
  public string GetCleanTimeString(string time)
  {
    // Format should be 00:00:00 or 00:00

    if (time.size() > 6)
    {
      if ((time[2,3] == ":" and time[5,6] == ":") or (time[2,3] == "." and time[5,6] == ".") or (time[2,3] == "," and time[5,6] == ","))
      {
        // 00:00:00
        // Trim excess.
        if (time.size() > 8)
          time[8,time.size() + 1] = null;
      }
      else
      {
        //time = (string)Str.ToInt(time);
        if (time == "")
          time = "00:00:00";
        else
        {
          float fTime = Str.ToFloat(time);
          if (fTime > 60.0)
          {
            float fTime = Str.ToFloat(time);
            fTime = fTime / 60;
            fTime = fTime / 60;
          
            int hours = fTime;
            fTime = fTime - hours;
            fTime = fTime * 60;

            int minutes = fTime;
            fTime = fTime - minutes;
            fTime = fTime * 60;

            int seconds = fTime;

            time = PadZerosOnFront((string)hours, 2) + ":" + PadZerosOnFront((string)minutes, 2) + ":" + PadZerosOnFront((string)seconds, 2);

          }
          else
            time = "00:" + PadZerosOnFront(time, 2) + ":00";
        }
      }
    }
    else if (time.size() > 3 and time[2,3] == ":")
    {
      // 00:00
      string oldTime = time[0, 5];
      time = oldTime + ":00";
    }
    else
    {
      if (time == "")
        time = "00:00:00";
      else
      {
        if (time.size() == 4)
        {
          time = time[0,2] + ":" + time[2,4] + ":00";
        }
        else if (time.size() == 6)
        {
          // hhmmss
          string hours;
          string minutes;
          string seconds;

          hours = time[0,2];
          minutes = time[2,4];
          seconds = time[4,6];

          time = hours + ":" + minutes + ":" + seconds;
        }
        else
        {

          float fTime = Str.ToFloat(time);
          if (fTime > 60.0)
          {
            float fTime = Str.ToFloat(time);
            fTime = fTime / 60;
            fTime = fTime / 60;
          
            int hours = fTime;
            fTime = fTime - hours;
            fTime = fTime * 60;

            int minutes = fTime;
            fTime = fTime - minutes;
            fTime = fTime * 60;

            int seconds = fTime;

            time = PadZerosOnFront((string)hours, 2) + ":" + PadZerosOnFront((string)minutes, 2) + ":" + PadZerosOnFront((string)seconds, 2);

          }
          else
            time = "00:00:" + PadZerosOnFront(time, 2);
        }
      }
    }

    return time;
  }
  

  public string PadZerosOnFront(string value, int maxSize)
  {
    string retValue = "";
    if (value.size() < maxSize)
    {
      int curSize = value.size();
      int loopMax = maxSize - curSize;
      int i;
      for (i = 0; i < loopMax; i++)
      {
        retValue = retValue + "0";
      }
    }
    retValue = retValue + value;

    return retValue;
  }


	//
	// Return the specified float as a string, sanitised for human consumption.
	// Do not make assumptions about the format of the output, other than it is
	// safe for display to the user.
	//
	public string GetCleanFloatString(float val)
	{
		string ret = (string)val;
		int len = ret.size();

		while (len  and  ret[len - 1] == '0')
			len--;

		if (len  and  ret[len - 1] == '.')
			len--;

		return ret[0, len];
	}

  public float ConvertUnitsToValue(float units, float mass, string format)
  {
    float retValue = 0.0f;

    float massInKg = units * mass;

    // No conversions needed for these values
    if (format == "Litres")
      retValue = units;
    if (format == "Items")
      retValue = units;

    // Conversions needed.
    if (format == "Tonnes")
      retValue = massInKg * 0.001;
    if (format == "tons")
      retValue = massInKg * 0.00110231131;
    if (format == "kilogram")
      retValue = massInKg;
    
    return retValue;
  }

  public float ConvertValueToUnits(float other, float mass, string format)
  {
    float retValue = 0.0f;

    // No conversions needed for these values
    if (format == "Litres")
      retValue = other;
    if (format == "Items")
      retValue = other;

    // Conversions needed.
    if (format == "Tonnes")
    {
      float massInKg = other * 1000;
      retValue = massInKg / mass;
    }
    if (format == "tons")
    {
      float massInKg = other * 907.18474;
      retValue = massInKg / mass;
    }
    if (format == "kilogram")
      retValue = other / mass;
    
    return retValue;
  }

  public string UnitsToString(float units, float mass, string format)
  {
    // Get the human readable string for the specified units.
    StringTable strTable = Constructors.GetTrainzStrings();
    float value = ConvertUnitsToValue(units, mass, format);
    
    int iValue = (int)(value + 0.999f);

    if (format == "Litres")
      return strTable.GetString1("common_unitstostring_litres", (string)iValue);
    if (format == "Items")
      return strTable.GetString1("common_unitstostring_items", (string)iValue);
    if (format == "Tonnes")
      return strTable.GetString1("common_unitstostring_tonnes", (string)iValue);
    if (format == "tons")
      return strTable.GetString1("common_unitstostring_tons", (string)iValue);
    if (format == "kilogram")
      return strTable.GetString1("common_unitstostring_kg", (string)iValue);

    return strTable.GetString("common_unitstostring_unknown");
  }

  public float StringToUnits(string str, string format)
  {
    Interface.Log("Common::StringToUnits() !!!!!!!!!!!NOT IMPLEMENTED YET!!!!!!!!!!!!!!!!!");
    return 0.0f;
  }


  public string RadioButton(string urlString, bool active)
	{
		string imageStr;
		Asset asset = Constructors.GetTrainzAsset();
		KUID kuid;

		if (active)
			kuid = asset.LookupKUIDTable("radiobutton-on");
		else
			kuid = asset.LookupKUIDTable("radiobutton-off");

		imageStr = "<img kuid='" + kuid.GetHTMLString() + "' width=16 height=16>";
		if (urlString == "")
			return imageStr;

		return "<a href='" + urlString + "'>" + imageStr + "</a>";
	}


	public string CheckBox(string urlString, bool active)
	{
		string imageStr;
		Asset asset = Constructors.GetTrainzAsset();
		KUID kuid;

		if (active)
			kuid = asset.LookupKUIDTable("checkbox-on");
		else
			kuid = asset.LookupKUIDTable("checkbox-off");

		imageStr = "<img kuid='" + kuid.GetHTMLString() + "' width=16 height=16>";

		if (urlString == "")
			return imageStr;
		return "<a href='" + urlString + "'>" + imageStr + "</a>";
	}

	public string HelpButton(string urlString)
	{
		string imageStr;
		Asset asset = Constructors.GetTrainzAsset();
		KUID offKuid = asset.LookupKUIDTable("help-off");

		imageStr = "<img kuid='" + offKuid.GetHTMLString() + "' width=32 height=32>";
		
		if (urlString == "")
			return imageStr;

		return "<a href='" + urlString + "'>" + imageStr + "</a>";
	}


	public string StartIndent(int width)
	{
		return "<table inherit-font><tr><td width=" + width + "></td><td>";
	}

	public string EndIndent(void)
	{
		return "</td></tr></table>";
	}


	public string StartBorder(string extraParams)
	{
		return "<table inherit-font " + extraParams + "><tr><td>";
	}

	public string EndBorder(void)
	{
		return "</td></tr></table>";
	}

  
  public string GetHumanReadableNameFromTrackName(string trackName, string industryName)
  {

    string[] destNames;
    string[] destTracks;
    destNames = new string[0];
    destTracks = new string[0];
    
    Industry industry = cast<Industry>(Router.GetGameObject(industryName));
    if (!industry)
      return "";

    industry.AppendDriverDestinations(destNames, destTracks);
    int l;
    int out;
    for (l = 0; l < destNames.size(); l++)
    {
      if (destTracks[l] == trackName)
      {
        return destNames[l];
      }
    }
    return "";
  }

};


//! A node in a generic linked list.
//
// This class is used by the LinkedList class as a generic item.  It contains a GSObject data member
// so it can be used to contain a reference to a large variety of %Trainz objects.  What it may be
// used to store in the LinkedList is up to the programmer.
//
// See Also:
//     LinkedList
//
// \warn DO NOT ALTER LAYOUT, MEMORY MAPPINGS ARE HARD CODED IN NATIVE
class LinkedData
{
	public string text;        //!< Text data for this node.  User-defined
	public int index;          //!< Index value of item in the list.
    public GSObject gsobject;  //!< Object reference for this list item.
};


//! A simple generic linked list class.
//
// This generic linked list contains a list of LinkedData objects.  Methods to add items to the list
// and sort them are provided.
//
// Public interface methods for this class are:
//  - public void  <b Init> ()
//  - public void  <b Sort> ()
//  - public void  <b Add>  (LinkedData ld)
//  - public void  <b Add>  (LinkedData ld, bool unique)
//
// Note: 
//     This class is not a part of the core %Trainz API and isn't fully documented.  The full class definition
//     and implementation however can be found in the <b \Trainz\scripts\common.gs> script file.
//
// See Also:
//     LinkedData
//
class LinkedList
{
	public LinkedData[] data;

	public void Init()
	{
		data = new LinkedData[0];
	}
	
	public native void SortInternal(LinkedData[] self);/*
	{
		int k;
		int kx;
		for (k = 0; k < data.size(); k++)
			for (kx = k+1; kx < data.size(); kx++)
				if (data[k].text > data[kx].text)
				{
					LinkedData tmp = data[kx];
					data[kx] = data[k];
					data[k] = tmp;
				}
		
	}*/
	
	public void Sort()
	{
		SortInternal(data);
	}

  public native void AddInternal(LinkedData[] self, LinkedData ld, bool unique);
  /*
  {
    bool exists = false;
    int i = 0;
    if (unique)
    {
      for (i = 0; i < data.size(); i++)
      {
        if (data[i].text == ld.text and data[i].index == ld.index and data[i].gsobject == ld.gsobject)
        {
          exists = true;
          break;
        }
      }
    }

    if (!exists)
      data[data.size()] = ld;
  }*/

  public void Add(LinkedData ld, bool unique)
  {
    AddInternal(data, ld, unique);
  }

  public void Add(LinkedData ld)
  {
    Add(ld, true);
  }

};


