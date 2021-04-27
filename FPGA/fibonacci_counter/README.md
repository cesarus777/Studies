# fibonacci counter

#### Requirements
Tested with 
* __Quartus Prime 18.1__
* __Altera CycloneIV EP4CE6E22C8N__
* __cmake__ version 3.13.4 (earlier versions may be also can work)



##### Configuring synthesis
If cmake can't find Quartus you need to add to Quartus binaries to QUARTUS_PATH var in [FindQuartus.cmake](cmake/FindQuartus.cmake)
```sh
cd $PATH_TO_STUDIES/Studies/FPGA/fibonacci_counter
mkdir build
cd build
cmake ..
```


##### Sinthsizing
```sh
cmake --build synthsis
```


##### Sinthsizing and program
Before programing you need to start jtag server. You can read about it [here](https://github.com/viktor-prutyanov/drec-fpga-intro/wiki/USB-Blasterlkk).
```sh
cmake --build program
```
