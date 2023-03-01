// Need G4P library
import g4p_controls.*;
import processing.serial.*;
// You can remove the PeasyCam import if you are not using


Serial connexion;;
int bgcol = 15;

public void setup(){
  String portName = Serial.list()[2];
  connexion = new Serial(this, portName, 9600);
  size(1000, 500, JAVA2D);
  createGUI();
  customGUI();
  // Place your setup code here
  
}

public void draw(){
  background(230);
  while(connexion.available() > 0){
   int input = connexion.read();
    println(input);
  }
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){

}
