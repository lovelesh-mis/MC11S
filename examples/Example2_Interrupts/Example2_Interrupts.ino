/******************************************************************************
  Example2_Interrupts.ino
  
  Read Capacitance from MC11S sensor, print them to terminal using the alert 
  flag present in STATUS register instead of the typical channel data ready flag. 

  MIS Electronics MC11S Arduino Library
  Lovelesh Patel @ MIS Electronics
  Original Creation Date: June 13th, 2024
  https://github.com/lovelesh-mis/MC11S

  Development environment specifics:

  IDE: Arduino 1.8.19

  Hardware Connections:

  ARDUINO --> MC11S
  ADC (A2) --> VT
  INT (D2) --> INTB
  GPIO (D4) --> SD 
  SDA (A4) --> SDA
  SCL (A5) --> SCL
  3.3V --> 3.3V
  GND --> GND

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "MC11S_Arduino_Library.h"
#include <Wire.h>

#define DEBUG

MC11S_I2C mySensor;

// Change the pin number to the pin that has been chosen for your setup
int intPin = 2;

// Star the flag as false
bool volatile interruptFlag = false;

// Threshold values
uint8_t highThreshold = 72;
uint8_t lowThreshold  = 70;
float Cref, Csensor;

// ISR to set the triggered interrupt
void isr1()
{
  interruptFlag = true;
  detachInterrupt(digitalPinToInterrupt(intPin));
}

void setupSensor() {
  // Step 1: Stop Conversion
  mySensor.setConvMode(MC11S_STOP_CONV);

  // Step 2: Set INTB_EN bit
  mySensor.setIntbStatus(MC11S_INTB_ENABLE);

  // Step 3: Reset INTB_MODE bit
  mySensor.setIntbMode(MC11S_INTB_ALARM);

  // Step 4: Set conversion time to convert every second
  mySensor.setConvTime(MC11S_CONV_1S);

  // Step 5: Set High Threshold
  mySensor.setTrh(highThreshold);

  // Step 6: Set low Threshold
  mySensor.setTrl(lowThreshold);

  // Step 7: Start Continuous conversion
  mySensor.setConvMode(MC11S_CONT_CONV);

  Serial.println("Setup complete");
}

void getCapacitance(float *Cref, float* Csensor) {
  // Calculate capacitance 
  
  // Step 1: Stop Conversion
  // mc11s_conv_mode_status_t val = MC11S_STOP_CONV; 
  mySensor.setConvMode(MC11S_STOP_CONV);

  // Step 2a: get ch0 & ch1 data
  uint16_t data_ch0, data_ch1;

  mySensor.getCh0Data(&data_ch0);
  // Serial.println("Ch0 Data: " + String(data_ch0));

  mySensor.getCh1Data(&data_ch1);
  // Serial.println("Ch1 Data: " + String(data_ch1));
  // delay(200);

  // Step 2b: get Fin_div
  mc11s_fin_div_val_t Fin_div_val;
  mySensor.getFinDiv(&Fin_div_val);

  // Serial.println("Fin Div: " + String(Fin_div_val));
  // delay(200);

  if (Fin_div_val > MC11S_FIN_DIV_256)
      Fin_div_val = MC11S_FIN_DIV_256;

  //Fin_div = 2 ^ Fin_div_val;

  // Step 2c: get Fclk
  uint32_t Fclk = 2400000;    // 2.4 MHz CLK based on datasheet

  // Step 2d: get Fref_div
  uint16_t Fref_div;

  mySensor.getFrefDiv((uint8_t*) &Fref_div);
  // Serial.println("Fref: " + String(Fref_div + 1));
  // delay(200);

  //Fref_div = Fref_div + 1;    // Fref value from 1 to 256

  // Step 2e: get RCNT
  uint16_t rcnt;

  mySensor.getRcnt(&rcnt);
  // Serial.println("RCNT: " + String(rcnt));
  // delay(200);

  // Step 2f: get Idrv
  uint16_t Idrv;
  mc11s_drive_i_status_t drive_i;

  mySensor.getDriveCurrent(&drive_i);

  switch (drive_i) {
      case MC11S_DRIVE_I_200uA:
          Idrv = 200;
          break;
      
      case MC11S_DRIVE_I_400uA:
          Idrv = 400;
          break;

      case MC11S_DRIVE_I_800uA:
          Idrv = 800;
          break;

      case MC11S_DRIVE_I_1mA6:
          Idrv = 1600;
          break;

      case MC11S_DRIVE_I_2mA4:
          Idrv = 2400;
          break;
          
      case MC11S_DRIVE_I_3mA2_1:
      case MC11S_DRIVE_I_3mA2_2:
      case MC11S_DRIVE_I_3mA2_3:
          Idrv = 3200;
          break;

      default:
          Idrv = 0;
          break;
  }

  // Serial.println("Idrv: " + String(Idrv));
  // delay(200);

  // Step 3: Calculate Cref
  // C = k * Idrv /(data_chx * Fin_div * (Fclk /(Fref_div + 1))/ RCNT)
  *Cref = (float) (K * Idrv / (data_ch1 * (2 ^ Fin_div_val) * (Fclk / (Fref_div + 1)) / rcnt));

  // Step 4: Calculate Csensor
  *Csensor = (float) (K * Idrv / (data_ch0 * (2 ^ Fin_div_val) * (Fclk / (Fref_div + 1)) / rcnt));


  // Step 5: start new conversion cycle
  mySensor.setConvMode(MC11S_CONT_CONV); 
}

void setup()
{
    
    Serial.begin(115200);
    Serial.println("MC11S Example 2: Interrupts");

    // Establish communication with device 
    if (mySensor.begin() == false) {
      Serial.println("Error setting up device - please check wiring.");
      while(1);
    }

    // Set INT pin to be triggered on rising and falling edges of INT pin
    pinMode(intPin, INPUT);
    // Attach interrupt to the pin as a digital pin that triggers on a change
    attachInterrupt(digitalPinToInterrupt(intPin), isr1, CHANGE);

    // Call setup function to setup interrupt for MC11S
    setupSensor();

    delay(500);
}

void loop()
{
  // If interrupt is triggered
  if(interruptFlag == true)
  {
    interruptFlag = false;
    
    mc11s_alert_status_t status;
    mySensor.getAlertStatus(&status);
    
    Serial.println("Data ready!");
    
    
    // If the flag is high, then read out the information
    if(status.alert == 1)
    {
      getCapacitance(&Cref, &Csensor);

      Serial.println("Cref: " + String(Cref) + "pF");
      Serial.println("Csensor: " + String(Csensor) + "pF");
    }
    attachInterrupt(digitalPinToInterrupt(intPin), isr1, CHANGE);
  }
}