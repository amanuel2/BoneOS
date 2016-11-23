/**
 ** This file is part of BoneOS.
 **
 **   BoneOS is free software: you can redistribute it and/or modify
 **   it under the terms of the GNU General Public License as published by
 **   the Free Software Foundation, either version 3 of the License, or
 **   (at your option) any later version.

 **   BoneOS is distributed in the hope that it will be useful,
 **   but WITHOUT ANY WARRANTY; without even the implied warranty of
 **   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **   GNU General Public License for more details.

 **   You should have received a copy of the GNU General Public License
 **   along with BoneOS.  If not, see <http://www.gnu.org/licenses/>.
 **
 **  @main_author : Amanuel Bogale
 **  
 **  @contributors:

 **     Amanuel Bogale <amanuel2> : start
 **/ 

#include <stdint.h>
#include <stddef.h>
#include <drv/driver.h>
#include <drv/pit/pit.h>
#include <drv/video/video.h>
#include <drv/ps2/kbd/kbd.h>

//Timer Driver Handler
struct device_driver pit_driver = 
{
   .name = "8253 Programmable Interval Timer",
   .init = &init_pit,
   .uninit = &uninit_pit
};

//Keyboard Driver Handler
struct device_driver kbd_driver = 
{
   .name = "8042 Keyboard PS/2 Driver",
   .init = &init_kbd,
   .uninit = &uninit_kbd,
};

//Video Driver Handler
struct device_driver video_driver = 
{
  .name = "Video Driver",
};

//All Drivers 
struct device_driver *drivers[] = 
{
    &pit_driver,
    &kbd_driver,
    &video_driver,
    0
};

//Sets Up Device Driver Handler
void setup_driver_handler()
{
  pit_driver.initalized = initalized_pit;
  kbd_driver.initalized = initalized_ps2_kbd;
  video_driver.init = video_drivers[VGA_VIDEO_DRIVER_INDEX]->init;
  video_driver.uninit = video_drivers[VGA_VIDEO_DRIVER_INDEX]->uninit;
}

//check if device is initalized
bool device_initalized(int index)
{
  return (drivers[index]->initalized);
}

//Initalize device driver
int init_device_driver(uint32_t index)
{
  drivers[index]->init();
  return 0;
}

//uninitalize device driver
int uninit_device_driver(uint32_t index)
{
  drivers[index]->uninit();
  return 0;
}

//inialize all device drivers
int init_all_drivers()
{
  for(uint32_t i=0; drivers[i]; i++)
    drivers[i]->init();
  return 0;
}

//unintalize all device drivers
int uninit_all_drivers()
{
  for(uint32_t i=0; drivers[i]; i++)
    drivers[i]->uninit();
  return 0;
}