
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
  String abc="My test String";
  
  const char *OTAName = "ESP8266";
  int n=abc.length();
  char a[n];
  abc.toCharArray(a,n+1);
  
  Serial.begin(115200);
  Serial.println("");
 Serial.println(abc);
 Serial.println(a);
 for(int m=0;m<=n;m++){
 Serial.print(m);
 Serial.print(" , ");
 Serial.print(abc[m]);
 Serial.print(" , ");
 Serial.println(abc[m], HEX);
 
 
 }
 Serial.print(a);
 Serial.print(" , ");
 n=strlen(a);
 Serial.println(n);
 Serial.print(OTAName);
 Serial.print(" , ");
 n=strlen(OTAName);
 Serial.println(n);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
