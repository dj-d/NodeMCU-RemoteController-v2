# NodeMCU-RemoteController-v2

NodeMCU sketch to control IR devices

## Using

- To connect the device to the network visit: __[tzapu/WiFIManager](https://github.com/tzapu/WiFiManager)__
- __API__
    
  | Description | Method | Endpoint | Body elements |
  | --- | --- | --- | --- |
  | To start the action described in the body | __POST__ | /rc | "*__action__*" |
  | To receive the type of device | __GET__ | /get_type | - |

- __Supported actions__

  | Action | Description |
  | --- | --- |
  | *on* | Turn on or turn off |
  | *input* | Open input menu |
  | *settings* | Open settings menu |
  | *vol_up* | Turn up the volume |
  | *vol_down* | Turn down the volume |
  | *vol_mute* | Turn off the volume |
  | *prog_up* | Change to the next channel |
  | *prog_down* | Change to the previous channel |
  | *arrow_up* | Arrow up button |
  | *arrow_down* | Arrow down button |
  | *arrow_left* | Arrow left button |
  | *arrow_right* | Arrow right button |
  | *back* | Back button |
  | *ok* | Ok button |

- __Examples__

  - Request body for "*__/rc__*":
    ```json
        {
          "action": "YOUR_ACTION"
        }
    ```
  
  - Response body for "*__/rc__*":
    ```json
        {
          "msg": "SOME_MESSAGE"
        }
    ```
  
  - Response body for "*__/get_type__*":
    ```json
        {
          "type": "remote_controller"
        }
    ```

## Supported devices

- [x] LG TV
- [ ] Samsung TV
- [ ] Sony TV
- [ ] Silvercrest soundbar
- [ ] Samsung soundbar

## Development

- [ ] Button to reset wifi
- [ ] Add more devices