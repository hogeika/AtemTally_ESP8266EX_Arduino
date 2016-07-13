#include "ATEMclient.h"

ATEMclient::ATEMclient(){}

void ATEMclient::_parseGetCommands(const char *cmdStr)  {
        uint8_t mE;
  uint16_t videoSource;
  long temp;
  uint8_t readBytesForTlSr;

  if (!strcmp_P(cmdStr, PSTR("AMLv")))  {
    _readToPacketBuffer(36);
  } else if (!strcmp_P(cmdStr, PSTR("TlSr"))) {
    readBytesForTlSr = ((ATEM_packetBufferLength-2)/3)*3+2;
    _readToPacketBuffer(readBytesForTlSr);
  } else {
    _readToPacketBuffer();  // Default
  }

  if(!strcmp_P(cmdStr, PSTR("PrgI"))) {
    
    mE = _packetBuffer[0];
    if (mE<=1) {
      #if ATEM_debug
      temp = atemProgramInputVideoSource[mE];
      #endif          
      atemProgramInputVideoSource[mE] = word(_packetBuffer[2], _packetBuffer[3]);
      #if ATEM_debug
      if ((_serialOutput==0x80 && atemProgramInputVideoSource[mE]!=temp) || (_serialOutput==0x81 && !hasInitialized())) {
        Serial.print(F("atemProgramInputVideoSource[mE=")); Serial.print(mE); Serial.print(F("] = "));
        Serial.println(atemProgramInputVideoSource[mE]);
      }
      #endif
      
    }
  } else 
  if(!strcmp_P(cmdStr, PSTR("PrvI"))) {
    
    mE = _packetBuffer[0];
    if (mE<=1) {
      #if ATEM_debug
      temp = atemPreviewInputVideoSource[mE];
      #endif          
      atemPreviewInputVideoSource[mE] = word(_packetBuffer[2], _packetBuffer[3]);
      #if ATEM_debug
      if ((_serialOutput==0x80 && atemPreviewInputVideoSource[mE]!=temp) || (_serialOutput==0x81 && !hasInitialized())) {
        Serial.print(F("atemPreviewInputVideoSource[mE=")); Serial.print(mE); Serial.print(F("] = "));
        Serial.println(atemPreviewInputVideoSource[mE]);
      }
      #endif
      
    }
  }
}

  /**
   * Get Program Input; Video Source
   * mE   0: ME1, 1: ME2
   */
  uint16_t ATEMclient::getProgramInputVideoSource(uint8_t mE) {
    return atemProgramInputVideoSource[mE];
  }

  /**
   * Set Program Input; Video Source
   * mE   0: ME1, 1: ME2
   * videoSource  (See video source list)
   */
  void ATEMclient::setProgramInputVideoSource(uint8_t mE, uint16_t videoSource) {
  
      _prepareCommandPacket(PSTR("CPgI"),4,(_packetBuffer[12+_cBBO+4+4+0]==mE));

    _packetBuffer[12+_cBBO+4+4+0] = mE;
    
    _packetBuffer[12+_cBBO+4+4+2] = highByte(videoSource);
    _packetBuffer[12+_cBBO+4+4+3] = lowByte(videoSource);
    
      _finishCommandPacket();

  }

  /**
   * Get Preview Input; Video Source
   * mE   0: ME1, 1: ME2
   */
  uint16_t ATEMclient::getPreviewInputVideoSource(uint8_t mE) {
    return atemPreviewInputVideoSource[mE];
  }

  /**
   * Set Preview Input; Video Source
   * mE   0: ME1, 1: ME2
   * videoSource  (See video source list)
   */
  void ATEMclient::setPreviewInputVideoSource(uint8_t mE, uint16_t videoSource) {
  
      _prepareCommandPacket(PSTR("CPvI"),4,(_packetBuffer[12+_cBBO+4+4+0]==mE));

    _packetBuffer[12+_cBBO+4+4+0] = mE;
    
    _packetBuffer[12+_cBBO+4+4+2] = highByte(videoSource);
    _packetBuffer[12+_cBBO+4+4+3] = lowByte(videoSource);
    
      _finishCommandPacket();

  }
  
  /**
   * Set Cut; M/E
   * mE   0: ME1, 1: ME2
   */
  void ATEMclient::performCutME(uint8_t mE) {
  
      _prepareCommandPacket(PSTR("DCut"),4);

    _packetBuffer[12+_cBBO+4+4+0] = mE;
    
      _finishCommandPacket();

  }
  
  /**
   * Set Auto; M/E
   * mE   0: ME1, 1: ME2
   */
  void ATEMclient::performAutoME(uint8_t mE) {
  
      _prepareCommandPacket(PSTR("DAut"),4);

    _packetBuffer[12+_cBBO+4+4+0] = mE;
    
      _finishCommandPacket();

  }

