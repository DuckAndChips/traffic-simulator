## Traffic Simulator

#### How to run the project
Open `SimpleCity.pro` in Qt Creator and run it. The project is designed to work with Qt 5.15.1.    
Reconfigure the build directory if necessary.


If you are using Qt version 5.12.11 (or older), `menuwindow.cpp` may not compile.    
To fix this, change lines **26-28** of `menuwindow.cpp` from
```c++
QPixmap p = ui->label_logo->pixmap(Qt::ReturnByValue);
const int SCALE = 4;
ui->label_logo->setPixmap(p.scaled(p.width() * SCALE, p.height() * SCALE));
```
to
```c++
const QPixmap *p = ui->label_logo->pixmap();
const int SCALE = 4;
ui->label_logo->setPixmap(p->scaled(p->width() * SCALE, p->height() * SCALE));
```

#### Credit
Modified from COMP2012H PA4 (Simple City), which original code and UI design are by COMP2012H Teaching Team.    
Building icons / images by pixel32@opengameart.org ( https://opengameart.org/content/pixel-city-municipal-buildings ).    
Avenue & Street images modified by TSE, Hoi Chun, with original images from KUBI Games (https://kubigames.itch.io/road-tiles).

#### Screenshot
![screenshot](https://user-images.githubusercontent.com/29478296/144034122-9cd5c1ae-7065-4ba2-b224-8cb18938e94e.jpeg)

---

This project is created by group H20 (members YIN Junyu, LUK Pak Him, TSE Hoi Chun and MOK Nga Yiu) in fulfillment of COMP2012H, CSE, HKUST.
