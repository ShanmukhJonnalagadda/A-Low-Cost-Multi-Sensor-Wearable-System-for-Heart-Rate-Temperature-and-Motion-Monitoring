# Validation plan

| Test | Procedure | Expected outcome | Status |
|---|---|---|---|
| Build | Verify sketch for classic Arduino Uno | No compilation errors | Not run |
| Memory | Record compiler flash and static RAM report | Within configured capacity | Not run |
| Temperature | Compare bench readings to reference | Record difference, no assumed accuracy | Not run |
| Disconnected sensor | Power down, disconnect DS18B20 and reboot | Temperature unavailable | Not run |
| Pulse | Use suitable bench signal or optical simulator | Record estimates and missed events | Not run |
| Motion | Orient/move sensor on bench | ADC values respond on relevant axes | Not run |
| Serial | Observe output at 9600 baud | Readable periodic reports | Not run |
| Timing | Observe concurrent temperature and pulse reporting | Record timing and missed events | Not run |

Record Arduino IDE, board core and library versions, compile output, test configuration and observed outcomes. Capture screenshots without personal data. Compilation alone does not establish physical operation, calibration or clinical accuracy. No fall-detection or medical performance test is claimed.
