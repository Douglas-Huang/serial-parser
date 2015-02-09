void setup()
{
  Serial.begin(115200);
  randomSeed(analogRead(0));
}

void loop()
{
    uint8_t sum = 0x80 + 0x8F + 0xEA + 0x16 + 0x50 + 0x08;
    Serial.write(0x80);
    Serial.write(0x8F);
    Serial.write(0xEA);
    Serial.write(0x16);
    Serial.write(0x50);
    Serial.write(0x08);
    for(int i = 0; i < 20; i++)
    {
      uint8_t randomShit = random(0,256);
      sum += randomShit;
      Serial.write(randomShit);
    }
    Serial.write(sum % 256); 
}

  
