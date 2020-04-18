# NodeMCU-RemoteController-v2
NodeMCU sketch to control IR devices

### Using

- To connect the device to the network visit: __[tzapu/WiFIManager](https://github.com/tzapu/WiFiManager)__
- Call API use a __POST__ request and use __JSON__ for the data.
  - Example
    - API:
        | Command | Description |
        | --- | --- |
        | / | To start the action described in the body |
    - Body of JSON:
       ```json
         {
           "action": "YOUR_ACTION"
         }
       ```

### Supported action
| Command | Description |
| --- | --- |
| on | Turn on or turn off |
| input | Open input menu |
| settings | Open settings menu |
| vol_up | Turn up the volume |
| vol_down | Turn down the volume |
| vol_mute | Turn off the volume |
| prog_up | Change to the next channel |
| prog_down | Change to the previous channel |
| arrow_up | Arrow up button |
| arrow_down | Arrow down button |
| arrow_left | Arrow left button |
| arrow_right | Arrow right button |
| back | Back button |
| ok | Ok button |

### Supported devices
- [x] LG TV
- [ ] Samsung TV
- [ ] Silvercrest soundbar

### Development
- [ ] Button to reset wifi
- [ ] Add more devices


