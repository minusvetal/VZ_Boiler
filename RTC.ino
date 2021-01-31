int BCD2DEC(int x) { return ((x)>>4)*10+((x)&0xf); }
int DEC2BCD(int x) { return (((x)/10)<<4)+((x)%10); }

#define I2CStart(x)   Wire.beginTransmission(x)
#define I2CStop()     Wire.endTransmission()
#define I2CWrite(x)   Wire.write(x)
#define I2CRead()     Wire.read()
#define I2CReq(x,y)   Wire.requestFrom(x,y)
#define I2CReady      while(!Wire.available()) {};

#define DS_RTC_TIME    0x00
#define DS_RTC_DOW     0x03
#define DS_RTC_DATE    0x04
#define DS_RTC_MEM     0x08

//-------------------------------------
void setRTCDateTime() {
  I2CStart(rtcAddr);
  I2CWrite(DS_RTC_TIME);
  I2CWrite(DEC2BCD(second));
  I2CWrite(DEC2BCD(minute));
  I2CWrite(DEC2BCD(hour));
  I2CWrite(DEC2BCD(dayOfWeek));
  I2CWrite(DEC2BCD(day));
  I2CWrite(DEC2BCD(month));
  I2CWrite(DEC2BCD(year-2000));
  I2CStop();
}
//-------------------------------------
void getRTCDateTime(void) {
  int v;
  I2CStart(rtcAddr);
  I2CWrite(DS_RTC_TIME);
  I2CStop();
  I2CReq(rtcAddr, 7);
  I2CReady;
  v = I2CRead() & 0x7f;
  second = BCD2DEC(v);
  v = I2CRead() & 0x7f;
  minute = BCD2DEC(v);
  v = I2CRead() & 0x3f;
  hour = BCD2DEC(v);
  v = I2CRead() & 0x07;
  dayOfWeek = BCD2DEC(v);
  v = I2CRead() & 0x3f;
  day = BCD2DEC(v);
  v = I2CRead() & 0x3f;
  month = BCD2DEC(v);
  v = I2CRead() & 0xff;
  year = BCD2DEC(v) + 2000;
  I2CStop();
}
