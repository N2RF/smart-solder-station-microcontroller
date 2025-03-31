# Smart Solder Station
This repo contains the code for the microcontroller part of our project. See [Smart Solder Station Web](https://github.com/N2RF/smart-solder-web) for the web portion of the code.

## About
The Smart Solder Station project aims to solve the problem of students leaving soldering irons turned on in the soldering lab. Leaving the irons on both wastes energy, and ruins the tips of the irons.
We are using a PIR sensor, relay, and microcontroller to detect if a person is sitting at a soldering iron, and turn the power to the iron on or off a the wall. This way if a student leaves the station without turning the iron off,
it will still power down even. The irons do have a sleep feature, but this is not enough to fully solve the problem.

## How to set up a Smart Soldering Station
1. Flash an ESP32C3 microcontroller with the Smart Soldering Station Code
2. Place the PIR sensor next to the soldering iron on the bench, so it is facing where a user would it.
3. Place the screen next to the PIR sensor so users can see which station they are using.
4. Plug the microcontroller into a wall outlet using a brick which supplies USB power.
5. Using a phone or computer, connect to the WiFi hotspot that the Smart Soldering Station generates using the password `lafayette`
6. On a web browser, visit `192.168.4.1` and enter the credentials for the wifi network that you want the station to connect to. Also enter the name of the lab, a unique number for that soldering iron, and how many watts the iron is rated for.
5. Plug the soldering iron into the plug on the Smart Soldering Station. **Make sure that the Smart Soldering Station plug is not plugged into the wall**
6. Plug the Smart Soldering Station plug into the wall.
7. Setup is now complete

### Development Environent Setup
1. Install a C/C++ IDE  which supports PlatformIO (e.g. [Visual Studio Code](https://code.visualstudio.com/), [CLion](https://www.jetbrains.com/clion/)).
2. Install [PlatformIO](https://platformio.org/install/) as an extension in your IDE.
3. Open the `smart-solder-station` folder in your IDE.
4. Open the PlatformIO Home from the PlatformIO extension in your IDE.
5. Build the project using the PlatformIO build button.
6. Upload the project to the ESP32C3 board using the PlatformIO upload button.
7. Open the serial monitor to view the output of the ESP32C3 board. (If using Clion, don't use the upload and monitor button, instead use the Clion Serial Monitor Plugin)
8. Make changes to the code and test them on the ESP32C3 board.
9. If you are going to add new libraries to the project, add them to the `platformio.ini` file.
10. Make sure that you develop your changes in a separate branch in Git

### References
[Washr Code](https://github.com/Spaceona/Washr)
[Adafruit SSD1306 Sreen Example](https://registry.platformio.org/libraries/adafruit/Adafruit%20SSD1306/examples/ssd1306_128x64_i2c/ssd1306_128x64_i2c.ino)