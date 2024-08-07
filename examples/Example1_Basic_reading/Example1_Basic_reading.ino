/******************************************************************************
  Example1_BasicReadings.ino
  
  Read values from the MC11S sensor, print them
  to terminal. 

  MIS Electronics MC11S Arduino Library
  Lovelesh Patel @ MIS Electronics
  Original Creation Date: June 13th, 2024
  https://github.com/lovelesh-mis/MC11S

  Development environment specifics:

  IDE: Arduino 1.8.19

  Hardware Connections:

  ARDUINO --> MC11S
  ADC (A2) --> VT
  INT (A0) --> INTB
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

void setup()
{
    
    Serial.begin(115200);
    Serial.println("MC11S Example 1: Basic Readings");

    // Establish communication with device 
    if (mySensor.begin() == false) {
      Serial.println("Error setting up device - please check wiring.");
      while(1);
    }

    mySensor.reset();
    delay(500);
}

void loop()
{
  mc11s_drdy_ch0_status_t ch0DataReady;
  mc11s_drdy_ch1_status_t ch1DataReady;

  mySensor.getCh0DataReady(&ch0DataReady);
  mySensor.getCh1DataReady(&ch1DataReady);

   if (ch0DataReady.drdy_ch0 && ch1DataReady.drdy_ch1 == 1) {
        // Calculate capacitance 
        
        // Step 1: Stop Conversion
        // mc11s_conv_mode_status_t val = MC11S_STOP_CONV; 
        mySensor.setConvMode(MC11S_STOP_CONV);

        // Step 2a: get ch0 & ch1 data
        uint16_t data_ch0, data_ch1;

        mySensor.getCh0Data(&data_ch0);
        Serial.println("Ch0 Data: " + String(data_ch0));

        mySensor.getCh1Data(&data_ch1);
        Serial.println("Ch1 Data: " + String(data_ch1));
        delay(200);

        // Step 2b: get Fin_div
        mc11s_fin_div_val_t Fin_div_val;
        mySensor.getFinDiv(&Fin_div_val);

        Serial.println("Fin Div: " + String(Fin_div_val));
        delay(200);

        if (Fin_div_val > MC11S_FIN_DIV_256)
            Fin_div_val = MC11S_FIN_DIV_256;

        //Fin_div = 2 ^ Fin_div_val;

        // Step 2c: get Fclk
        uint32_t Fclk = 2400000;    // 2.4 MHz CLK based on datasheet

        // Step 2d: get Fref_div
        uint16_t Fref_div;

        mySensor.getFrefDiv((uint8_t*) &Fref_div);
        Serial.println("Fref: " + String(Fref_div + 1));
        delay(200);

        //Fref_div = Fref_div + 1;    // Fref value from 1 to 256

        // Step 2e: get RCNT
        uint16_t rcnt;

        mySensor.getRcnt(&rcnt);
        Serial.println("RCNT: " + String(rcnt));
        delay(200);

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

        Serial.println("Idrv: " + String(Idrv));
        delay(200);

        // Step 3: Calculate Cref
        // C = k * Idrv /(data_chx * Fin_div * (Fclk /(Fref_div + 1))/ RCNT)
        float Cref, Csensor;
        Cref = (float) (K * Idrv / (data_ch1 * (2 ^ Fin_div_val) * (Fclk / (Fref_div + 1)) / rcnt));
        Serial.println("Cref: " + String(Cref) + " pF");

        // Step 4: Calculate Csensor
        Csensor = (float) (K * Idrv / (data_ch0 * (2 ^ Fin_div_val) * (Fclk / (Fref_div + 1)) / rcnt));
        Serial.println("Csensor: " + String(Csensor) + " pF");

        // Step 5: start new conversion cycle
        mySensor.setConvMode(MC11S_CONT_CONV); 

        float voltage = (analogRead(A2) * 5.0) / 1023;
        Serial.println("Voltage: " + String(voltage) + " mV");
        float temp = (-560.0 * voltage) + 386.3;

        Serial.println("Temp: " + String(temp) + " C");
   } 
   Serial.println("------------------------");
   delay(2000);
}

