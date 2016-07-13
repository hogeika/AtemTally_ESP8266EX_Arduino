#ifndef ATEMclient_h
#define ATEMclient_h

#include "ATEMbase.h"


class ATEMclient : public ATEMbase
{
public:
  ATEMclient();
  uint16_t getProgramInputVideoSource(uint8_t mE);
  void setProgramInputVideoSource(uint8_t mE, uint16_t videoSource);
  uint16_t getPreviewInputVideoSource(uint8_t mE);
  void setPreviewInputVideoSource(uint8_t mE, uint16_t videoSource);
  void performCutME(uint8_t mE);
  void performAutoME(uint8_t mE);

private:
  void _parseGetCommands(const char *cmdStr);
  uint16_t atemProgramInputVideoSource[2];
  uint16_t atemPreviewInputVideoSource[2];
};

#endif
    

