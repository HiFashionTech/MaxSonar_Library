/* Original simple maxbotix sonar test, no library use
 This script is designed to take several readings from the maxbotix sonar and generate a mode/median.
 original uses range Width (PW)
 changed up to use Analog
Author: Jason Lessels
Date created: 2011/June/06
License: GPL (=>2)
This work has been compileed using many sources mainly posts/wiki posts from;
Allen, Bruce (2009/July/23) and Gentles, Bill (2010/Nov/12)
*/

#define MODE_ARRAY_SIZE 9

//Set the pin to recieve the signal.
//const int pwPin = 7;
const int analogPin = 0;

//variables needed to store values
const int arraysize = MODE_ARRAY_SIZE; //quantity of values to find the median (sample size). Needs to be an odd number

//declare an array to store the samples. not necessary to zero the array values here, it just makes the code clearer
int rangevalue[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
long range;
long inches, cm;

int modE;


void setup() {

  //Open up a serial connection
  Serial.begin(115200);
  //Wait for the serial connection
  delay(500);
  Serial.println("Maxbotix Sonar test");
}

//Main loop where the action takes place
void loop() {

  //  pinMode(pwPin, INPUT);
  for (int i = 0; i < arraysize; i++)
  {
    //    range = rangeIn(pwPin, HIGH);
    //    rangevalue[i] = range/58;
    range = analogRead(analogPin);  // vcc/1024 is range in 5mm steps
    rangevalue[i] = (range * 5) / 10 ; // range in cm
    delay(10);
  }
  //  Serial.println(millis());

  //  Serial.print("Unsorted: ");
  //  printArray(rangevalue,arraysize);
  //  isort(rangevalue,arraysize);
  //  Serial.print("Sorted: ");
  //  printArray(rangevalue,arraysize);

  modE = mode(rangevalue, arraysize);
  int zone = findZone(modE);

  Serial.print("The mode/median is: "); Serial.println(modE);
  //  Serial.println();
  Serial.print("The Zone is: "); Serial.println(zone);
  delay(100);
}

const int zoneO = 30;
const int zone1 = 121;// 4ft
const int zone2 = 243;
const int zone3 = 365;
const int zone4 = 10000;

int findZone(long range)
{
  if (range <= zoneO)
    return 0;
  if (range <= zone1)
    return 1;
  if (range <= zone2)
    return 2;
  if (range <= zone3)
    return 3;
  return 4;
}

/*-----------Functions------------*/ //Function to print the arrays.
void printArray(int *a, int n) {

  for (int i = 0; i < n; i++)
  {
    Serial.print(a[i], DEC);
    Serial.print(' ');
  }
  Serial.println();
}

//Sorting function
// sort function (Author: Bill Gentles, Nov. 12, 2010)
void isort(int *a, int n) {
  // *a is an array pointer function
  for (int i = 1; i < n; ++i)
  {
    int j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--)
    {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}

//Mode function, returning the mode or median.
int mode(int *x, int n) {

  int i = 0;
  int count = 0;
  int maxCount = 0;
  int mode = 0;
  int bimodal;
  int prevCount = 0;
  while (i < (n - 1)) {
    prevCount = count;
    count = 0;
    while (x[i] == x[i + 1]) {
      count++;
      i++;
    }
    if (count > prevCount && count > maxCount) {
      mode = x[i];
      maxCount = count;
      bimodal = 0;
    }
    if (count == 0) {
      i++;
    }
    if (count == maxCount) { //If the dataset has 2 or more modes.
      bimodal = 1;
    }
    if (mode == 0 || bimodal == 1) { //Return the median if there is no mode.
      mode = x[(n / 2)];
    }
  }
  return mode;
}


