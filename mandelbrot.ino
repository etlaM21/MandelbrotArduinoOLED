#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

const int buttonPin = 2;  // the number of the pushbutton pin
volatile int buttonState = 0;  // variable for reading the pushbutton status
volatile int sketchState = 0; // 0 = display full mandelbrot, 1 = display lines, 2 = display dots
// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Mandelbrot
double xMin = -2.0;
double xMax = 2.0;
double yMin = -1.0;
double yMax = 1.0;

int maxIterations = 1000;
int endIterations = 2250;
// Zoom
int num_frames = 50;
int frame = 0;
float iterationSteps = endIterations / 50;

void setup() {
  Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  attachInterrupt(digitalPinToInterrupt(buttonPin), pin_ISR, CHANGE);
  // put your setup code here, to run once:
  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  if (oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation successful"));
  }
  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display
  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.println("Happy"); // text to display
  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 30);        // position to display
  oled.println("Birthday!"); // text to display
  oled.display();               // show on OLED  
}

double map(double inputNum, double minInput, double maxInput, double minOutput, double maxOutput) {
    return (inputNum - minInput) * (maxOutput - minOutput) / (maxInput - minInput) + minOutput;
}

void loop() {
  maxIterations = iterationSteps * (frame + 1);
  Serial.print("Iterations: ");
  Serial.print(maxIterations);
  Serial.println();
  // put your main code here, to run repeatedly:
  for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            oled.drawPixel(x,y,BLACK);
            double x0 = map((double) x, 0.0, SCREEN_WIDTH, xMin, xMax);
            double y0 = map((double) y, 0.0, SCREEN_HEIGHT, yMin, yMax);
            double x1 = 0.0;
            double y1 = 0.0;
            int iteration = 0;
            double z = x1 * x1 + y1 * y1;
            while (z <= 2.0 * 2.0 && iteration < maxIterations) {
                double xtemp = x1 * x1 - y1 * y1 + x0;
                y1 = 2.0 * x1 * y1 + y0;
                x1 = xtemp;
                z = x1 * x1 + y1 * y1;
                if(z != z){ // check if z is NaN aka too little (Stack overflow)
                  break;
                }
                iteration++;
            }
            // Serial.printf( "%17.12lf", z);
            if (z < 2.0 * 2.0) {
               oled.drawPixel(x,y,WHITE);
            }
          if(sketchState == 2) oled.display();
        }
        if(sketchState == 1) oled.display();
        // oled.display(); // SEXY! Line by Line drawing, but slow as fuck
    }
    oled.display();
    Serial.print("Frame ");
    Serial.print(frame);
    Serial.print(" done !");
    Serial.println();
    if (frame >= 0) {
        double xShift = -0.25;
        double yShift = +0.637618;
        xMin += xShift;
        xMax += xShift;
        yMin += yShift;
        yMax += yShift;
    }
    double scale = 0.5;
    xMin *= scale;
    xMax *= scale;
    yMin *= scale;
    yMax *= scale;

    maxIterations += 25;
    frame++;
    if (frame >= num_frames) {
        xMin = -2.0;
        xMax = 2.0;
        yMin = -1.0;
        yMax = 1.0;
        maxIterations = 250;
        frame = 0;
    }
}

void pin_ISR() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
   if (interrupt_time - last_interrupt_time > 50) 
  {
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);
    // if(buttonState != digitalRead(buttonPin)){
      
    if(buttonState == 1){
      sketchState++;
      if(sketchState >= 3) sketchState = 0;
      Serial.println(sketchState);
    }
  }
  last_interrupt_time = interrupt_time;
}