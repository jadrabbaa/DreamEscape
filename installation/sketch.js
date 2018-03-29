var serial;          // variable to hold an instance of the serialport library
var portName = '/dev/cu.usbmodem1461';  // fill in your serial port name here
var inData;                             // for incoming serial data

var xPos = 0;                           // x position of the graph

var song;

function preload(){
  song=loadSound("file.mp3");
}
 
function setup() {
  createCanvas(400, 300);
  background('black');
  serial = new p5.SerialPort();       // make a new instance of the serialport library
  serial.on('connected', serverConnected); // callback for connecting to the server
  serial.on('open', portOpen);        // callback for the port opening
  serial.on('data', serialEvent);     // callback for when new data arrives
  serial.on('error', serialError);    // callback for errors
  serial.on('close', portClose);      // callback for the port closing
 
  serial.list();                      // list the serial ports
  serial.open(portName);              // open a serial port

  song.loop();

}

function draw() {
  graphData(inData);
  song.setVolume(inData,1,0);

}

function graphData(newData) {

  // map the range of the input to the window height:
  var yPos = map(newData, 1, 100, 0, height);
  // draw the line in a pretty color:
  stroke('magenta');
  line(xPos, height, xPos, height - yPos);
  // at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 0;
    // clear the screen by resetting the background:
    background('black');
  } else {
    // increment the horizontal position for the next reading:
    xPos++;
  }
}



function serverConnected() {
  console.log('connected to server.');
}
 
function portOpen() {
  console.log('the serial port opened.')
}
 
function serialEvent() {
  // read a string from the serial port:
  var inString = serial.readLine();
  console.log('data: ' + inString);
  // check to see that there's actually a string there:
  if (inString.length > 0 ) {
  // convert it to a number:
    inData = Number(inString);
    
  }
}


 
function serialError(err) {
  console.log('Something went wrong with the serial port. ' + err);
}
 
function portClose() {
  console.log('The serial port closed.');
}