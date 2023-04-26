struct Command{

  bool set_command(char id, char cmd, char arg, char crc) {
    if( id == this->id && id + cmd + arg == crc ){
      this->cmd = cmd;
      this->arg1 = arg;
      this->crc = crc;
      new_cmd = true;
      return true;
    }

    new_cmd = false;
    return false;
  }

  const char id = 0x55;
  char cmd;
  char arg1;
  char crc;
  bool new_cmd;
};

Command cmd;
const int cmd_blink = 1;
const int cmd_led_on = 2;
const int cmd_led_off = 3;

const int LedPin = 13;


void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin, HIGH);

  cmd.new_cmd = false;
}




bool led = false;

void loop() {

   if (Serial.available() >= 4) {
      
      char val = Serial.read();//readString().toInt();
      char num = Serial.read();
      char arg1 = Serial.read();
      char crc = Serial.read();

      if( cmd.set_command(val, num, arg1, crc) ){
        Serial.write("OK\n");
      }
      else{
        Serial.write("KO\n");
      }

      Serial.flush();
  }

    
   if( cmd.new_cmd ){
      
     if(cmd.cmd == cmd_blink){

      if(led){
        led = false;
        digitalWrite(LedPin, LOW);
      }
      else{
        led = true;
        digitalWrite(LedPin, HIGH);
      }

     }

     else if(cmd.cmd == cmd_led_on){
       digitalWrite(LedPin, HIGH);
     }

     else if(cmd.cmd == cmd_led_off){
       digitalWrite(LedPin, LOW);
     }

      cmd.new_cmd = false;
   }
}
