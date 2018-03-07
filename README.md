# Wireless Deployment Support Network
The Wireless Deployment Support Network is a WSN Management tool for IoT Network. It allows a user to monitor custom messages coming in from the users WSN. This code base is board and purpose built for certain software and architectures however it does prove that creating a management tool for WSN's is possible.The project uses micro-controllers, like the ESP8266 board and AT MEGA RFA 1 board to monitor an IoT network in a passive way. This means that the Wireless Deployment Support Network can analyse a WSN without interfering with the WSN itself. 

## Getting started

To get started, pull this code base down to a local repo on your machine. The code base is broken down into sections. 
1) Ardunio Code: This is the code that will run on your micro-controller.
2) api: This is a directory that will act as a RESTful api for the microcontrollers to interface with.
3) js, css and index.html: This is the client side code that will sit on your server.

There is more information below on each section.  

### Ardunio Code

The Arduino Code directory contains two ino files. This code is the firmware the runs on your Microcontroller, independently from the WSN nodes. In the case of this project, this code was built to run specifically on the ESP8266 board. 

The first file, ESP8266FinalSolution, is my own implementation. Unfortunately, my code is a little error prone so I would recommend using supervisors code. My supervisors code is called SupervisorCode.ino

#### How to run the firmware

The best way to run the firmware is to open the code in the [Arduino IDE](https://www.arduino.cc/en/Main/Software). You can follow the instructions on the Arduino website on how to download and install the Arduino IDE. Once you have the Arduino IDE up and running, you might need to install custom software for the Arduino IDE to be able to create machine executable code for your microcontroller. This varys from controller to controller however, for the ESP boards, you follow this quick and easy [tutorial](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/). 

Once you have the Arduino IDE configured, you have to configure the code to work for you local Wi-Fi network. They're a few fields that you need to update: 

- ssid = your Wifi Network name i.e its ssid name
- password = the password for you Wifi Network
- host = the hostname of your server were you will locate the WDSN's server technology
- API_path = path to were you will leave the api directory on your server.
- Node_ID = this has to be an ID to identify your node, it should be unique to all other nodes.

Once you have these variables configured, you just have to compile and execute the firmware from the Arduino IDE. There should be 2 buttons up in the top left corner above your code to do this. Compile first, then Upload your code to the microcontroller.   

Once your code is uploaded and running on your microcontroller, you can disconnect you mircocontroller from your machine and attach it to a node in your WSN. 

You will then need to programme your nodes to send messages to the microcontroller. How to do this depends on the type of node you have in your WSN.

That's it. Your microcontroller should be send data from your node to your WDSN server. Now you have to set up your WDSN server.

### Mongo dB 

For the WDSN to work, you will need to set up a local Mongo db instance on your server. You can use the [Mongo db documentation](https://docs.mongodb.com/) to install MongoDB. Once you have the Mongo DB instance up and running, use the Mongo dB client to create a collection. To do this, do the following steps:

- run mongo on your server terminal to access the mongo dB client. 
- run "use < mongodb username > "
- run "db.createCollection("Collection_name")"

take note of the collection name you use as this will be required when configuring your RESTful API

### RESTful API

The api directory contains two files that act as a minimal RESTful API for your WDSN. This api directory must be stored on your server. It must be stored in an area in which you can send a HTTP POST and GET request too as this is what the GUI and microcontroller will be doing. You must also take note of this location and put it in the firmware code under the variables host and API_path. 

There is 2 php files that make up this RESTful API. The Display.php file and the Record.php file. 

The Record.php file is used to save node data to a local Mongo dB instance on the server. This file needs to be configured to work with your local Mongo dB instance. It needs to be told the Mongo db client name and the collection it should save the data to. To do this you need to do the following:

- Change $user to your mongo db username
- Change the third parameter in $collection to the name of your collection in which you will be storing data

If this is done correctly, the data the ESP sends to the RESTful API should be saved in your Mongo database.

The Display.php file is used by the GUI to get data out of the local Mongo dB that is running on the server. This file will pull data from the database based off a timestamp. The file will only get data saved to the DB since the submitted timestamp. This is file will need the same configuration as Record.php above. 

### GUI

The GUI for the WDSN consists of the index.html, js and css directory. 

In order to configure the GUI, You need to make sure that the js and css directory in the same directory as the index.html file as this is the only that the index.html file will be able to locate the client side JavaScript code and custom CSS code.

The GUI also relies on the BootStrap Framework in order to drawn dynamic cells for each node in your WSN. You dont need to download the BootStrap source code however as the BootStrap source code is being retrieved from an online vendor. 

The GUI is currently very bare so the best way to test it out is by storing some node data in your Mongo DB collection and seeing if the GUI can get it. If it cannot, please reread this document and ensure that you have done every step correctly.
