Recoil - Lasertag
===
# General
## Introduction
"Goliath Recoil" is Lasertag System witch use your smartphone and a wifi-access-point to provoke a Lasertag-based game.
Here the idea of reuse parts of this system to lower entry level of self implementation is realized.
Prototypes of own marker-models, communication with markers, smartphones are planed.
Pain points like additional smartphone, no possibility of charging the marker, not maintenance of smartphone app is addressed.

### Motivation - Pain of existing system
1. Powerful smartphone is needed
2. Markers are not rechargeable - battery change is cumbersome
3. No individual markers
4. Less possibility to extend markers (scope)

# Milestones and next steps

## Next steps

### Milestone 01
* [ ] Create IR-Receiver to test the hardware setup (lens, led) and software (ir-codec) and maybe reverse engineer existing protocols
	* [ ] Buy 
* [ ] Create Test Transceiver
	* [ ] Buy
* [ ] Create test mechanic model
    * [ ] import and clean template
    * [ ] Create overall model

# Documentation

## Brainstorming

**General**
* Reuse as much as possible from begin
 

**Controller**  

* Smartphone as replaced by µC + display + sound   

**Elektronic**  

* Ir Sender electronic is separate module
	* Attiny based
	* Serial interface to main controller
	* Contains constance current source based on opamp and logic level mosfet
	* Hardware switch between low- and highpower
	* Backwards compatibility to be used from original controller 

* main controller is a ESP32 
	* Wifi and BT Interface
	* Enough performance

* power source
    * lipos with battery management
    * switch regulator for 3v/5v (maybe test ordered mini dcd-dc 5V 3A SPS)
    * 

**Optics**
- use Convex lens to create a parallel beam out of a e.g. 60 degree beam
- Radius of the cavature need to be the distance to led. For 60 degree this means 
  - use [link](https://www.1728.org/angsize.htm) to calculate distance 
- The main restriction for the led/laser and lens would be the barell diameter
  

**Mechanic**   
* Use m4 caribine Hardware from thingiverse

**Software**   


## Electronic
### IR
* reuse IR-LED from original **TSAL6100** IR-LED 170 mW/sr | 10° | 940nm | tr=15ns | 100mA 1.5mA@100µs @ 1.35V [reichelt](https://www.reichelt.de/ir-led-940-nm-5-mm-t1-3-4-tsal-6100-vis-p219695.html?&trstct=pos_0&nbc=1)   
* 38KHz receiver **TSOP53338** or equivalent

### Buylist

## Mechanic
### IR-Sender

## Software
### µC
### smartphone ?

# Tools
[Simulation of Elektronic](https://www.falstad.com/circuit/circuitjs.html)

# Links

### Documentation

* [github of skyrocket](https://github.com/SkyRocketToys)
* [reddit group](https://www.reddit.com/r/recoilhacks/)
* [simple coil github](https://github.com/Dees-Troy/SimpleCoil/releases)
* [simple coil reddit group](https://www.reddit.com/r/recoilhacks/comments/7qot8u/simplecoil_open_source_android_app_for_recoil/)
* [bluettoth protocol](https://www.reddit.com/r/recoilhacks/comments/7o6kf1/understanding_bluetooth_communication_between/)
* [recoil hub wlan booster](https://www.reddit.com/r/recoilhacks/comments/8seks2/recoil_wifi_hub_mod_add_a_signal_booster/)
* [recoil hub get into it](https://www.reddit.com/r/RECOILWorld/comments/6wjw8z/recoil_reverse_engineering/)
* [Some general information](https://wiki.lazerswarm.com/wiki/Category:Recoil)

### Body and 3D print links

* [Hub to Tripod] (https://www.thingiverse.com/thing:2962447)
* [M4 with fusion model](https://www.thingiverse.com/thing:2902660/files)
* [m4 less parts](https://www.thingiverse.com/thing:3119747/files)
* [m4 single part](https://pinshape.com/items/41289-3d-printed-m4a1)

### Optics and Electronics

- [Ali express 5mm M12 CCTV Lens](https://de.aliexpress.com/item/1005005642843742.html?spm=a2g0o.productlist.main.1.56b6ae90TotYN4&algo_pvid=014536a5-c09d-47ff-a81c-9ddd0deea213&utparam-url=scene%3Asearch%7Cquery_from%3A) M12 Mounting, 5mm Focal Lenght, IR Possible, cheap

### Lasertag general
* [Lasertag rifle 01] (https://www.thingiverse.com/thing:4057897)



# "Goliath" recoil system
### RK45
* 38 Khz 3.5mm Adapter LED IR remote extender
* [Disassembly](https://imgur.com/a/XLtUN)

### IR
* TSAL6100 IR-LED 170 mW/sr | 10° | 940nm | tr=15ns | 100mA 1.5mA@100µs @ 1.35V [reichelt](https://www.reichelt.de/ir-led-940-nm-5-mm-t1-3-4-tsal-6100-vis-p219695.html?&trstct=pos_0&nbc=1)
* TSOP53338 receiver 38Khz | 0.12 mW/m² | 
* PROTOCOL_MAN20A is used for the guns

