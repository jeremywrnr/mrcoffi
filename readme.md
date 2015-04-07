Mr. Cof-Fi
==========

-> *(Coffee + WiFi) = (Cof-Fi)* <-

Brewing the internet @ [hackcooper][hc] 2015.

A system that uses the Yo, the [spark core][sp] and the its [command line
interface][cli] tool to turn Mr. Coffee into Mr. Cof-Fi. We also implemented a
water level detector to augment our control system and increase safety. You can
check out the submission page to hackcooper [here][hl] or check out our web
interface that pairs with Mr. Cof-Fi [here][jw].

We completed replaced the onboard microcontroller, and implemented a water
level detector to augment our control system and increase safety, while adding
the ability to track how much coffee is being brewed. It logs this usage (how
many coffee cups brewed and when) in a Firebase database, and provides a
framework for them to easily viewed, as well as receiving updates from when the
mister cof-fi is finished brewing.

### getting the ID of your core

    export sparkid=$(make getid)

### video demo

[![MRCOFFI DEMO YO](http://img.youtube.com/vi/uMjU8CY2lLY/0.jpg)](http://www.youtube.com/watch?v=uMjU8CY2lLY)

[hc]:http://hackcooper.org/
[sp]:https://spark.io/build
[cli]:http://docs.spark.io/cli/
[jw]:http://jeremywrnr.com/Mr.Cof-Fi/
[hl]:https://www.hackerleague.org/hackathons/hackcooper-2015/hacks/mr-cof-fi
