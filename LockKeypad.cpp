#include <Keypad.h>
#include <EEPROM.h>

//Keypad settings
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte colPins[ROWS] = {6, 7, 8, 9};
byte rowPins[COLS] = {2, 3, 4, 5};

class AccessPanel {
    public:
        AccessPanel() {
            for( int i = 0; i < 4; i++ ){
                this->accessCode[i] = EEPROM.read(i);
            }
        };

        Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
        
        void setAccessCode( char newAccessCode[4] ) {
          for( int i = 0; i < 4; i++ ) {
            this->accessCode[i] == newAccessCode[i];
            EEPROM.write(i, newAccessCode[i]);
          }
        }

        void scanForInput() {
          char key = this->keypad.getKey();
          if( key ) {
            this->processKeyPress( key );
          }
         }

         void processKeyPress( char key ) {
           if( key == '#' )  this->accessGranted = this->checkCode();
           else {
            if ( this->currentCodePosition == 4 ) {
              this->resetCurrentCode();
              this->currentCode[0] = key;
              this->currentCodePosition++;
              return;
            }
            this->currentCode[ this->currentCodePosition ] = key;
            this->currentCodePosition++;
           }
         }

         bool checkCode() {
            for( int i = 0; i < 4; i++ ) {
              if( !( this->accessCode[i] == this->currentCode[i] ) ) {
                this->resetCurrentCode();
                return false;
              }
            }
            this->resetCurrentCode();
            return true;
         }
         
         void resetCurrentCode() {
          for( int i = 0; i < 4; i++ ) currentCode[i] = 'x'; 
          this->currentCodePosition = 0;
         }

         bool requestAccess() {
          return this->accessGranted;
         }

         void resetAccess() {
          this->accessGranted = false;
          this->resetCurrentCode();
         }
         
    private:
        bool accessGranted = false;
        int currentCodePosition = 0;
        char accessCode[4] = {'0', '0', '0', '0'};
        char currentCode[4] = {'x', 'x', 'x', 'x'};
};