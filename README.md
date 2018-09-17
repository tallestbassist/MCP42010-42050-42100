# MCP42010-42050-42100

This is my take on how to control the MCP42010 MCP42050 and MCP42100 with an encoder through an ardunio board.


  Pins:
  
  MCP42***  <->   Arduino
  
  (1.  CS    <->  10. CS) (can be assinged to any pin but mostly first one is used as pin 10 since its close to the others)
  
  (2.  SCK   <->  13. SCK)
  
  (3.  SI    <->  11. MOSI)
  
  (13. SO    <->  12. MISO)  (not actually sure if this is needed for this chip)

(Mega and some others use different pins - always check you boards connections)

NOTE: This is example how to control multiple digipots but i havent gotten it to work with multiple encoders.

By Kender Tasa 17.09.2018


Warning: My code formatting is off a little.
