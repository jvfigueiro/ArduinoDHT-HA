# 🌡️ Arduino DHT for Home Assistant

This project integrates an **Arduino Mega** equipped with two **DHT11** temperature and humidity sensors directly into **Home Assistant** via Serial (USB) communication.

The solution was designed to reliably monitor the climatic conditions of two critical points in the physical infrastructure, without relying on Wi-Fi:
1. **Room:** The general climate of the lab/room.
2. **Rack:** The internal temperature of the server rack where the hardware is hosted.

## 🛠️ Project Architecture

The Arduino reads the analog sensors every 5 seconds and generates a formatted *string* on the Serial port. Home Assistant OS (running on a VM), through a USB *pass-through*, reads this *string* natively and uses *Templates* to parse the data and create independent entities in the dashboard.

### Hardware Used
* Arduino Mega 2560 Board (Connected via USB to the host)
* 2x DHT11 Temperature and Humidity Sensors
* Jumper Cables

### Wiring Scheme (Pinout)
| DHT11 Sensor | Arduino Pin | Function |
| :--- | :--- | :--- |
| Sensor 1 (Room) | `D2` | Data Read |
| Sensor 2 (Rack) | `D3` | Data Read |
| VCC | `5V` | Power |
| GND | `GND` | Ground |

---

## 💻 1. The Arduino Code (`DHT-ha.c`)

The C++ *sketch* uses the `DHT.h` library to read both sensors simultaneously. 
The logic formats the data in the following pattern and sends it at 9600 *baud*:
`Room_Humidity ; Room_Temp ; Rack_Humidity ; Rack_Temp`

Example of the Serial port output:
`55.00;24.50;42.00;31.20`

*To use it, simply upload the `DHT-ha.c` file to the board using the Arduino IDE.*

---

## ⚙️ 2. Home Assistant Configuration (`configuration.yaml`)

For Home Assistant to understand the data coming through the USB port (`/dev/ttyACM0`), we use the native `serial` integration combined with the powerful `template` integration.

Add the blocks below to your `configuration.yaml` file:

### A. Reading the Serial Port
First, we create a "raw" sensor that receives the entire string from the Arduino:
```yaml
sensor:
  - platform: serial
    serial_port: /dev/ttyACM0
    baudrate: 9600
    name: "Arduino Mega" # Name of the sensor that will receive the "humidity;temperature" strings