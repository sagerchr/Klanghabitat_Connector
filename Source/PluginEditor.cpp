/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KlanghabitatConnectorAudioProcessorEditor::KlanghabitatConnectorAudioProcessorEditor (KlanghabitatConnectorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    Colour color = Colours::grey;
    
    //This instance is used for establishing the connection to target. It listens on port 9010
    oscReceiver.addListener(this);
    oscReceiver.connect (9010); //connect here the Reciver on startup so it will listen to the incumming DeviceInfo from Target
    
    //This instance is used for communicatiing with the target It listens on port 9002
    oscStreamer.addListener(this);
    oscStreamer.connect (9002); //connect here the Reciver on startup so it will listen to the incumming Downstream from Target
    
    waveform_left.setBounds (160, 100, 510, 100);
    addAndMakeVisible (waveform_left);
    
    waveform_right.setBounds (160, 250, 510, 100);
    addAndMakeVisible (waveform_right);
    
    Device_Incoming_Message.setBounds (10, 10, 130, 25);
    addAndMakeVisible(Device_Incoming_Message);
    
    OSCBoxDeviceInfo.setBounds(10, 520, 300, 60 );
    addAndMakeVisible (OSCBoxDeviceInfo);
    
    OSCBoxDownStream.setBounds(320, 520, 500, 60 );
    addAndMakeVisible (OSCBoxDownStream);
 
    attackAttach = new AudioProcessorValueTreeState::SliderAttachment (processor.treeState, "attack", Attack);
    Attack.setBounds(700, 80, 120, 120);
    Attack.setRange(0.1,120, 0.1f);
    Attack.setTextValueSuffix (" ms");
    Attack.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    Attack.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 20);
    addAndMakeVisible (Attack);
    AttackLabel.setText ("attack", dontSendNotification);
    AttackLabel.attachToComponent (&Attack, false);
    Attack.setColour (Slider::thumbColourId, color);
    Attack.setColour (Slider::rotarySliderFillColourId, color);
    AttackLabel.setJustificationType(Justification::horizontallyCentred);
    Attack.addListener(this);
    
    releaseAttach = new AudioProcessorValueTreeState::SliderAttachment (processor.treeState, "release", Release);
    Release.setBounds(700, 230, 120, 120);
    Release.setRange(10,500, 10.0f);
    Release.setTextValueSuffix (" ms");
    Release.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    Release.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 20);
    addAndMakeVisible (Release);
    ReleaseLabel.setText ("release", dontSendNotification);
    ReleaseLabel.attachToComponent (&Release, false);
    Release.setColour (Slider::thumbColourId, color);
    Release.setColour (Slider::rotarySliderFillColourId, color);
    ReleaseLabel.setJustificationType(Justification::horizontallyCentred);
    Release.addListener(this);
    
    ratioAttach = new AudioProcessorValueTreeState::SliderAttachment (processor.treeState, "ratio", Ratio);
    Ratio.setBounds(30, 230, 120, 120);
    Ratio.setRange(0.0,20, 1.0f);
    Ratio.setTextValueSuffix (" ");
    Ratio.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    Ratio.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 20);
    addAndMakeVisible (Ratio);
    RatioLabel.setText ("ratio", dontSendNotification);
    RatioLabel.attachToComponent (&Ratio, false);
    Ratio.setColour (Slider::thumbColourId, color);
    Ratio.setColour (Slider::rotarySliderFillColourId, color);
    RatioLabel.setJustificationType(Justification::horizontallyCentred);
    Ratio.addListener(this);
    
    thresholdAttach = new AudioProcessorValueTreeState::SliderAttachment (processor.treeState, "threshold", Threshold);
    Threshold.setBounds(30, 80, 120, 120);
    Threshold.setRange(-20.0,0, 0.1f);
    Threshold.setTextValueSuffix (" dB");
    Threshold.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    Threshold.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 20);
    addAndMakeVisible (Threshold);
    ThresholdLabel.setText ("threshold", dontSendNotification);
    ThresholdLabel.attachToComponent (&Threshold, false);
    Threshold.setColour (Slider::thumbColourId, color);
    Threshold.setColour (Slider::rotarySliderFillColourId, color);
    ThresholdLabel.setJustificationType(Justification::horizontallyCentred);
    Threshold.addListener(this);
    
    inputAttach = new AudioProcessorValueTreeState::SliderAttachment (processor.treeState, "input", InGain);
    InGain.setBounds(30, 380, 120, 120);
    InGain.setRange(0.1,255, 1.0f);
    InGain.setTextValueSuffix (" dB");
    InGain.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    InGain.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 20);
    addAndMakeVisible (InGain);
    InGainLabel.setText ("input gain", dontSendNotification);
    InGainLabel.attachToComponent (&InGain, false);
    InGain.setColour (Slider::thumbColourId, color);
    InGain.setColour (Slider::rotarySliderFillColourId, color);
    InGainLabel.setJustificationType(Justification::horizontallyCentred);
    
    outputAttach = new AudioProcessorValueTreeState::SliderAttachment (processor.treeState, "output", OutGain);
    OutGain.setBounds(700, 380, 120, 120);
    OutGain.setRange(0.1,255, 1.0f);
    OutGain.setTextValueSuffix (" dB");
    OutGain.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    OutGain.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 20);
    addAndMakeVisible (OutGain);
    OutGainLabel.setText ("output gain", dontSendNotification);
    OutGainLabel.attachToComponent (&OutGain, false);
    OutGain.setColour (Slider::thumbColourId, color);
    OutGain.setColour (Slider::rotarySliderFillColourId, color);
    OutGainLabel.setJustificationType(Justification::horizontallyCentred);
    
    MSButton.setBounds(180, 400, 120, 30);
    addAndMakeVisible (MSButton);
    MSButton.onClick = [this] { KlanghabitatConnectorAudioProcessorEditor::MSButtonClicked(); };
    MSButton.setButtonText ("MS/STERO IN (K5)");
    
    MS_SignalButton.setBounds(300, 400, 120, 30);
    addAndMakeVisible (MS_SignalButton);
    MS_SignalButton.onClick = [this] { KlanghabitatConnectorAudioProcessorEditor::MS_SignalButtonClicked(); };
    MS_SignalButton.setButtonText ("MS/STERO OUT (K6)");
    
    LeftBypassButton.setBounds(180, 450, 120, 30);
    addAndMakeVisible (LeftBypassButton);
    LeftBypassButton.onClick = [this] { KlanghabitatConnectorAudioProcessorEditor::LeftBypassButtonClicked(); };
    
    RightBypassButton.setBounds(540, 450, 120, 30);
    addAndMakeVisible (RightBypassButton);
    RightBypassButton.onClick = [this] { KlanghabitatConnectorAudioProcessorEditor::RightBypassButtonClicked(); };

    ListenMidButton.setBounds(420, 400, 120, 30);
    addAndMakeVisible (ListenMidButton);
    ListenMidButton.onClick = [this] { KlanghabitatConnectorAudioProcessorEditor::ListenMidButtonClicked(); };
    ListenMidButton.setButtonText ("MID (K8)");
    
    ListenSideButton.setBounds(540, 400, 120, 30);
    addAndMakeVisible (ListenSideButton);
    ListenSideButton.onClick = [this] { KlanghabitatConnectorAudioProcessorEditor::ListenSideButtonClicked(); };
    ListenSideButton.setButtonText ("SIDE (K7)");
    
    addAndMakeVisible (AutoConnectButton);
    AutoConnectButton.onClick = [this] { updateToggleState (&AutoConnectButton, "local"); };
    AutoConnectButton.setToggleState(true,dontSendNotification);
    
    

    //#######################Connection########################################################
    deviceList.setBounds(160,10,290,25);
    addAndMakeVisible(deviceList);
    
    deviceList.onChange = [this] { KlanghabitatConnectorAudioProcessorEditor::connectButtonClicked();}; //////////////////////
        
    connectButton.setBounds(460, 10, 200, 25);
    addAndMakeVisible(connectButton);
    connectButton.onClick = [this] { KlanghabitatConnectorAudioProcessorEditor::connectButtonClicked(); };
    connectButton.setButtonText ("connect to target");
    connectButton.setColour (TextButton::textColourOffId, Colours::darkorange);
    
    //animation.setBounds (1055, 10, 50, 50);
    //addAndMakeVisible(animation);
    //animation.changeColour(Colours::orange);
    //#########################################################################################
    
    
    
    //stringToTarget.setBounds(520, 460, 500, 25);
    //addAndMakeVisible(stringToTarget);
    
    Watchdog.setBounds(620, 460, 500, 25);
    addAndMakeVisible(Watchdog);
    
    AutoConnectButton.setColour(juce::ToggleButton::textColourId,juce::Colours::white);
    AutoConnectButton.setColour(juce::ToggleButton::tickColourId,juce::Colours::white);
    AutoConnectButton.setColour(juce::ToggleButton::tickDisabledColourId,juce::Colours::white);
    AutoConnectButton.setBounds(680, 13, 100, 20);
    
    listen = false;
    
    startTimer(1000);
    
    setResizable (true, true);
    setSize (850, 600);
}

KlanghabitatConnectorAudioProcessorEditor::~KlanghabitatConnectorAudioProcessorEditor()
{
    disconnectTarget();
    oscReceiver.disconnect();
}

//==============================================================================

void KlanghabitatConnectorAudioProcessorEditor::paint (Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void KlanghabitatConnectorAudioProcessorEditor::resized()
{

}

void KlanghabitatConnectorAudioProcessorEditor::timerCallback() 
      {
          OSCBoxDownStream.clear();
          if(!listen){
             oscReceiver.connect (9010); //connect here the Reciver so it will listen to the incumming DeviceInfo from Target
             listen = true;
          }
          else{
              oscReceiver.disconnect();
              listen = false;
          }
      }

void KlanghabitatConnectorAudioProcessorEditor::connectButtonClicked(){

    if(!connected){
        connectTarget(); //connect to the selected target in the list
        connectButton.setButtonText ("target connected");
        animation.changeColour(Colours::green);
        connectButton.setColour (TextButton::textColourOffId, Colours::green);
        connected = true;
        deviceList.setEnabled(false);
    }
    else {
        disconnectTarget(); //Disconnect from the current connected target
        connectButton.setButtonText ("connect to target");
        animation.changeColour(Colours::darkorange);
        connectButton.setColour (TextButton::textColourOffId, Colours::darkorange);
        connected = false;
        deviceList.setEnabled(true);
        colorChange(0);
        waveform_left.clearWaveform();
        waveform_right.clearWaveform();
    }
}


void KlanghabitatConnectorAudioProcessorEditor::connectTarget(){
    
    String myIPAdress;
    String IPAddressTargetREAD = (String)(deviceList.getItemText(deviceList.getSelectedId()-1).substring(0, 15));
   
    juce::String OS;
    juce::String IPAddressTarget;
    OS = SystemStats::getOperatingSystemName();

    juce::String IPAddressTemp;
    int position = 0;
    int eraseProtect = 0;
    if (OS == "Windows 10") {
        for (int i = 0; i < 15; i++) {

            if (IPAddressTargetREAD.substring(i, i + 1) == ".") {
                position = 0;
                eraseProtect = 0;
            }
            position++;



            if (IPAddressTargetREAD.substring(i, i + 1) != "0" || eraseProtect == 1) {
                if (IPAddressTargetREAD.substring(i, i + 1) != ".") {
                    eraseProtect = 1;
                }
                IPAddressTarget += IPAddressTargetREAD.substring(i, i + 1);
            }
        }
    }
    else {
        IPAddressTarget = IPAddressTargetREAD;
    }
    allIpAdresses = juce::IPAddress::getAllAddresses();
        //**********************Finding the all Ethernet adresses used by this mashine*******************//
        for (int i=0; i< allIpAdresses.size(); i++){
            myIPAdressesArray[i] = allIpAdresses[i].toString();
        }
       
        //******************Finding the correct Ethernet adapter and connect with this*******************//
        for(int i=0; i< allIpAdresses.size(); i++){
           
            if (IPAddressTarget.substring(0,4) == allIpAdresses[i].toString().substring(0, 4)){
                myIPAdress = allIpAdresses[i].toString();
                TargetIP = IPAddressTarget;
                sender.connect (IPAddressTarget, 9011);
                sender.send ("/connection", myIPAdress);//sending "/connection" + IPAdress will start target to send downstream
                break;
            }
        }
    sender.disconnect();
}

void KlanghabitatConnectorAudioProcessorEditor::disconnectTarget(){
    
    String myIPAdress;
    String IPAddressTargetREAD = (String)(deviceList.getItemText(deviceList.getSelectedId()-1).substring(0, 15));

    juce::String OS;
    juce::String IPAddressTarget;
    OS = SystemStats::getOperatingSystemName();

    juce::String IPAddressTemp;
    int position = 0;
    int eraseProtect = 0;
    if (OS == "Windows 10") {
        for (int i = 0; i < 15; i++) {

            if (IPAddressTargetREAD.substring(i, i + 1) == ".") {
                position = 0;
                eraseProtect = 0;
            }
            position++;



            if (IPAddressTargetREAD.substring(i, i + 1) != "0" || eraseProtect == 1) {
                if (IPAddressTargetREAD.substring(i, i + 1) != ".") {
                    eraseProtect = 1;
                }
                IPAddressTarget += IPAddressTargetREAD.substring(i, i + 1);
            }
        }
    }
    else {
        IPAddressTarget = IPAddressTargetREAD;
    }
    sender.connect (IPAddressTarget, 9011);
    sender.send ("/Disconnection", myIPAdress); //sending "/Disconnection" + IPAdress will stop target to send downstream
    sender.disconnect();
}



void KlanghabitatConnectorAudioProcessorEditor::oscMessageReceived (const OSCMessage& message){
    int colorID;

    if (message.getAddressPattern().toString() == "/klanghabitat/DeviceInfo"){
         OSCBoxDeviceInfo.addOSCMessage (message);
        for (auto* arg = message.begin(); arg != message.end(); ++arg)
            KlanghabitatConnectorAudioProcessorEditor::Device_IPAdress = arg->getString().substring(0, 31);

        bool exist = false;
        
        for (int i = 0; i<deviceListArray.size(); i++){
            if (Device_IPAdress == deviceListArray.getUnchecked(i)){
                exist = true;
            }
        }
         
        if(!exist){
           deviceListArray.add(Device_IPAdress);
            deviceList.addItem (deviceListArray.getLast(), deviceListArray.size());
        }
        Device_Incoming_Message.setText( deviceListArray.getUnchecked(0), dontSendNotification);
    }
    else{
          OSCBoxDownStream.addOSCMessage (message);
        if (message.getAddressPattern().toString() == "/VALUE/Level/CH1/RMS"){
                for (auto* arg = message.begin(); arg != message.end(); ++arg)
                waveform_left.addSample(arg->getInt32());
        }
        if (message.getAddressPattern().toString() == "/VALUE/Level/CH1/GAINREDICTION") {
            for (auto* arg = message.begin(); arg != message.end(); ++arg)
                waveform_left.addGainreduct(arg->getInt32());
        }
        
        if (message.getAddressPattern().toString() == "/VALUE/Level/CH2/RMS"){
                for (auto* arg = message.begin(); arg != message.end(); ++arg)
                waveform_right.addSample(arg->getInt32());
        }

        if (message.getAddressPattern().toString() == "/VALUE/Level/CH2/GAINREDICTION") {
            for (auto* arg = message.begin(); arg != message.end(); ++arg)
                waveform_right.addGainreduct(arg->getInt32());
        }

        if (message.getAddressPattern().toString() == "/Watchdog"){
                for (auto* arg = message.begin(); arg != message.end(); ++arg)
                animation.animate();
        }
        if (message.getAddressPattern().toString() == "/attack"){
                for (auto* arg = message.begin(); arg != message.end(); ++arg)
            Attack.setValue(arg->getFloat32());
        }
        if (message.getAddressPattern().toString() == "/release"){
                for (auto* arg = message.begin(); arg != message.end(); ++arg)
            Release.setValue(arg->getFloat32());
        }
        if (message.getAddressPattern().toString() == "/ratio"){
                for (auto* arg = message.begin(); arg != message.end(); ++arg)
            Ratio.setValue(arg->getFloat32());
        }
        if (message.getAddressPattern().toString() == "/threshold"){
                for (auto* arg = message.begin(); arg != message.end(); ++arg)
            Threshold.setValue(arg->getFloat32());
        }
        if (message.getAddressPattern().toString() == "/colour") {
            for (auto* arg = message.begin(); arg != message.end(); ++arg)
                colorID = arg->getFloat32();
                colorChange(colorID);
                waveform_left.colour(colorID);
                waveform_right.colour(colorID);
        }




        if (message.getAddressPattern().toString() == "/BypassLeft"){
                for (auto* arg = message.begin(); arg != message.end(); ++arg)
            if(arg->getFloat32() == 1){
                LeftBypassButton.setButtonText("Bypass");
                L_BYPASS = 1;
            }
            else{
                LeftBypassButton.setButtonText("active");
                L_BYPASS = 0;
            }
        }
        if (message.getAddressPattern().toString() == "/BypassRight"){
                for (auto* arg = message.begin(); arg != message.end(); ++arg)
            if(arg->getFloat32() == 1){
                RightBypassButton.setButtonText("Bypass");
                R_BYPASS = 1;
            }
            else{
                RightBypassButton.setButtonText("active");
                R_BYPASS = 0;
            }
        }
    }
    
}



void KlanghabitatConnectorAudioProcessorEditor::sliderValueChanged(juce::Slider* slider){
    
    if(slider == &Attack){
        sender.connect (TargetIP, 9001);
        sender.send ("/attack", (float)slider->getValue());
    }
    if(slider == &Release){
        sender.connect (TargetIP, 9001);
        sender.send ("/release", (float)slider->getValue());
    }
    if(slider == &Ratio){
        sender.connect (TargetIP, 9001);
        sender.send ("/ratio", (float)slider->getValue());
    }
    if(slider == &Threshold){
        sender.connect (TargetIP, 9001);
        sender.send ("/threshold", (float)slider->getValue());
    }
}


//======================Out going event handles================================

void KlanghabitatConnectorAudioProcessorEditor::MSButtonClicked(){
    sender.connect (TargetIP, 9001);
    MS_STERO_IN = !MS_STERO_IN;
    sender.send ("/MotherEngine/Relais/K5", (int)MS_STERO_IN);
    sender.disconnect();
}
void KlanghabitatConnectorAudioProcessorEditor::MS_SignalButtonClicked(){
    sender.connect (TargetIP, 9001);
    MS_STERO_OUT = !MS_STERO_OUT;
    sender.send ("/MotherEngine/Relais/K6", (int)MS_STERO_OUT);
    sender.disconnect();
}
void KlanghabitatConnectorAudioProcessorEditor::LeftBypassButtonClicked(){
    sender.connect (TargetIP, 9001);
    L_BYPASS = !L_BYPASS;
    sender.send ("/BypassLeft", (int)L_BYPASS);
    sender.disconnect();
}
void KlanghabitatConnectorAudioProcessorEditor::RightBypassButtonClicked(){
    sender.connect (TargetIP, 9001);
    R_BYPASS = !R_BYPASS;
    sender.send ("/BypassRight", (int)R_BYPASS);
    sender.disconnect();
}
void KlanghabitatConnectorAudioProcessorEditor::ListenMidButtonClicked(){
    sender.connect (TargetIP, 9001);
    MID = !MID;
    sender.send ("/MotherEngine/Relais/K8", (int)MID);
    sender.disconnect();
}
void KlanghabitatConnectorAudioProcessorEditor::ListenSideButtonClicked(){
    sender.connect (TargetIP, 9001);
    SIDE = !SIDE;
    sender.send ("/MotherEngine/Relais/K7", (int)SIDE);
    sender.disconnect();
}

void KlanghabitatConnectorAudioProcessorEditor::updateToggleState (juce::Button* button, juce::String name)
{
    auto state = button->getToggleState();
    juce::String stateString = state ? "ON" : "OFF";
    
    juce::Logger::outputDebugString (name + " Button changed to " + stateString);
}


void KlanghabitatConnectorAudioProcessorEditor::styleMenuChanged()
  {
      switch (deviceList.getSelectedId())
      {

      }

      
  }

void KlanghabitatConnectorAudioProcessorEditor::colorChange(int colorID)
{
    Colour color = Colours::grey;

    if (colorID == 0) {
        color = Colours::grey;
    }
    if (colorID == 1) {
        color = Colours::cornflowerblue;
    }
    if (colorID == 2) {
        color = Colours::lightgreen;
    }
    if (colorID == 3) {
        color = Colours::magenta;
    }

    Attack.setColour(Slider::thumbColourId, color);
    Attack.setColour(Slider::rotarySliderFillColourId, color);

    Release.setColour(Slider::thumbColourId, color);
    Release.setColour(Slider::rotarySliderFillColourId, color);

    Ratio.setColour(Slider::thumbColourId, color);
    Ratio.setColour(Slider::rotarySliderFillColourId, color);

    Threshold.setColour(Slider::thumbColourId, color);
    Threshold.setColour(Slider::rotarySliderFillColourId, color);

    InGain.setColour(Slider::thumbColourId, color);
    InGain.setColour(Slider::rotarySliderFillColourId, color);

    OutGain.setColour(Slider::thumbColourId, color);
    OutGain.setColour(Slider::rotarySliderFillColourId, color);
}
