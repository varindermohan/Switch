# ElegooTutorial

## 19 � Real Time Clock Module 

<!-- [[./octocat.png|alt=octocat]] -->
[![YouTube video](https://img.youtube.com/vi/y5X2zwbO6e4/0.jpg)](https://youtu.be/h-EZ0KSqqw0)
[YouTube video](https://youtu.be/h-EZ0KSqqw0)

ZS-042 Module aka. DS3231 RTC Module with AT24C32N EEprom chip and CR2032 battery.  Demonstrate the Elegoo sketch provided in the tutorial covering the DS3231 RTC Module.  Then I show my RTC alarm clock with my custom SimpleAlarmClock Library.  A beginner's guide to the Most Complete Starter Kit by Elegoo.

Hello everyone, I'm Rick the Tech Enthusiast here with the next Elegoo Lesson.  This is the next lesson on my Arduino UNO Series covering the Most Complete Starter Kit by Elegoo.   I try to follow the included tutorial and will point out any changes or corrections as I find them.

As mentioned before, I purchased this Elegoo starter kit and Elegoo isn't sponsoring me.  I just thought it would be fun to do a video of each Lesson as I was learning the Arduino environment. 

We�ll need a few things from your Elegoo Arduino UNO kit.  I�ll list the items below.  In this lesson we�re going to check out the DS3231 RTC module, aka. ZS-042 module.  The ZS-042 module includes a DS3231 real time clock and calendar, AT24C32N EEPROM chip, and CR2032 battery.  I�ll step through the Elegoo provided tutorial and briefly explain how code makes this happen.  We�ll build and configure a simple circuit that is provided in the tutorial to demonstrate the functionality.  Then will show an alarm clock circuit, complete with snooze alarm, and new SimpleAlarmClock.h library.  I hope you enjoy it. 

## Parts you�ll need for the tutorial

* Elegoo Arduino UNO R3 board
* ZS-042 Module (aka. DS3231 RTC Module)
* Four female-to-male jumper wires

The next lesson will be Lesson 20: Sound Sensor Module

## Links

This lesson�s sketch and associated drawings can be found at [Github](https://github.com/rmorenojr/ElegooTutorial)

* [MAX7219 LED Dot Matrix Module 8 x 8 with 5pcs Dupont Line � Amazon](https://www.amazon.com/gp/product/B07775NFS1/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325)
* [DHT21 AM2301 Capacitive Digital Temperature and Humidity Sensor](https://www.amazon.com/AM2301-Capacitive-Digital-Temperature-Humidity/dp/B07543HBQ2) � amazon 
* [SODIAL(R) DHT22 AM2302 Digital Temperature and Humidity Sensor Module](https://www.amazon.com/SODIAL-Digital-Temperature-Humidity-Raspberry/dp/B0757FBWSB/ref=sr_1_19?s=industrial&ie=UTF8&qid=1520801854&sr=1-19&keywords=dht22)
* [DHT22 AM2302 Digital Temperature and Humidity Sensor Module](https://www.amazon.com/Digital-Temperature-Humidity-Arduino-Raspberry/dp/B01N6PB489/ref=sr_1_4?s=industrial&ie=UTF8&qid=1520801995&sr=1-4&keywords=dht22) - amazon 
<!-- LCD1602 Module with 3.3V Backlight 16x2 Character White on Blue Background by SunFounder -->
* <a target="_blank" href="https://www.amazon.com/gp/product/B071Y6JX3H/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B071Y6JX3H&linkCode=as2&tag=rmorenojr-20&linkId=81e6c312179be2b149bf6eeae0051f14">SunFounder LCD1602 Module with 3.3V Backlight for Arduino Uno R3 Mega2560 Raspberry Pi 16x2 Character White on Blue Background</a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rmorenojr-20&l=am2&o=1&a=B071Y6JX3H" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />
<!-- Passive Buzzers, Cylewet 10Pcs 5V 2 Terminals, Arduino (Pack of 10) on Amazon�s web site: -->
* <a target="_blank" href="https://www.amazon.com/gp/product/B01NCOXB2Q/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B01NCOXB2Q&linkCode=as2&tag=rmorenojr-20&linkId=65e4660761a54140f64e954f1770006e">Cylewet 10Pcs 5V 2 Terminals Passive Electronic Alarm Buzzer Electromagnetic Beeper AC Impedance for Arduino (Pack of 10) CYT1008</a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rmorenojr-20&l=am2&o=1&a=B01NCOXB2Q" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />
* [Elenco 350 Piece Pre-formed Jumper Wire Kit on Amazon](https://amzn.to/2z6sCCw)
<!-- Elegoo EL-KIT-001 UNO R3 Project Complete Starter Kit with Tutorial for Arduino (63 Items) on Amazon�s web site: --> 
* <a target="_blank" href="https://www.amazon.com/gp/product/B01CZTLHGE/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B01CZTLHGE&linkCode=as2&tag=rmorenojr-20&linkId=ac3601531bad9439bc32c77b0088b741">Elegoo EL-KIT-001 UNO R3 Project Complete Starter Kit with Tutorial for Arduino (63 Items)</a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rmorenojr-20&l=am2&o=1&a=B01CZTLHGE" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />
* [Elegoo�s web site](https://www.elegoo.com/) - [Complete Starter Kit](https://www.elegoo.com/product/elegoo-uno-r3-project-complete-starter-kit/)
* [Logitech M510 Wireless Mouse on Amazon](https://amzn.to/2z4FF7F)

* [Fritzing Software](http://fritzing.org/download/)

* [Arduino Language Reference (English)](https://www.arduino.cc/reference/en/)
* [HC-SR501 PIR Motion Detector - With Arduino & Raspberry Pi by DroneBot Workshop](https://www.youtube.com/watch?v=ZC_sEW3_694)
* [Why most Arduino Soil Moisture Sensors suck (incl. solution) by Andreas Spiess](https://www.youtube.com/watch?v=udmJyncDvw0)

## Affiliate Links that Help my channel:
* Try Prime Discounted Monthly Offering: https://amzn.to/2PnVgSA
* Try Amazon Prime 30-Day Free Trial: https://amzn.to/2E5Hy4O
* Prime Student 6-month Trial: https://amzn.to/2ElxwNE
* Join Amazon Prime - Watch Thousands of Movies & TV Shows Anytime - Start Free Trial Now: https://amzn.to/2PsEZvE
* Give the Gift of Amazon Prime https://amzn.to/2EkFaYG
* Kindle Unlimited Membership Plans: https://amzn.to/2QJl548
* Try Audible and Get Two Free Audiobooks: https://amzn.to/2QD2B5v
* Amazon.com - Read eBooks using the FREE Kindle Reading App on Most Devices: https://amzn.to/2Ptpdkl

* Royalty Free Music from HookSounds.com, by artist Rodrigo Vicente - [FutureBass_Full](http://www.hooksounds.com)
* Royalty Free Music from "Constance" Kevin MacLeod - [Welcome to the Show]( https://incompetech.com/music/royalty-free/music.html)

This is another video for my new Arduino tutorial series. If you like the series, be sure to rate and subscribe.

Thanks for watching
