// Serial Protocol

struct engineData {
  float RPM;
  float MAP; 
  float TPS; 
  float ECT; 
  float IAT; 
  float O2S; 
  float SPARK; 
  float FUELPW1;
  float FUELPW2; 
  float UbAdc; 
} data;
  
const uint8_t preamble[] = {0x80, 0x8F, 0xEA, 0x16, 0x50, 0x08};
uint8_t buf[27];
uint8_t commPointer = 0;

int checkSum(){
 int sum;
 for(int i = 0; i < 26; i++) 
   sum += buf[i];
 if(sum == buf[27])
   return 1;
 else
   return 0;
}

void produceData(){
  data.RPM = (buf[6]*256 + buf[7])/4;
  data.MAP = (buf[8]*256 + buf[9])/256;
  data.TPS = (buf[10]*256 + buf[11])/655.36;
  data.ECT = (buf[12]*256 + buf[13]) - 40;
  data.IAT = (buf[14]*256 + buf[15]) - 40;
  data.O2S = (buf[16]*256 + buf[17])/204.8;
  data.SPARK = (buf[18]*256 + buf[19])/2;
  data.FUELPW1 = (buf[20]*256 + buf[21])/1000;
  data.FUELPW2 = (buf[22]*256 + buf[23])/1000;
  data.UbAdc = (buf[24]*256 + buf[25])/160;
}

void printData(){
  Serial.print("New Data\n");
  Serial.print(data.RPM);
  Serial.print("\n");
  Serial.print(data.MAP);
  Serial.print("\n");
  Serial.print(data.TPS);
  Serial.print("\n");
  Serial.print(data.ECT);
  Serial.print("\n");
  Serial.print(data.IAT);
  Serial.print("\n");
  Serial.print(data.O2S);
  Serial.print("\n");
  Serial.print(data.SPARK);
  Serial.print("\n");
  Serial.print(data.FUELPW1);
  Serial.print("\n");
  Serial.print(data.FUELPW2);
  Serial.print("\n");
  Serial.print(data.UbAdc);
  Serial.print("\n");
}

void setup()
{
  Serial.begin(115200);
}

void loop()
{
    if(Serial.available() > 0){    
        uint8_t incomingByte = Serial.read();
        if(commPointer < 6 && preamble[commPointer] == incomingByte){
          validatedData[commPointer] = incomingByte;
          commPointer++;
        }
        else if(commPointer >= 6 && commPointer < 27){
          commPointer++;
          validatedData[commPointer] = incomingByte;
        }
        else if(commPointer == 27 && checkSum()){
          produceData();
          printData();
          commPointer = 0;
        }
        else
          commPointer = 0;
    }
}
