# WORKSHOP PONG - ZEPHYR APPLICATION #

## prerequisites ##

> * 6 GB free memory
> * Python version v3.7 minimum
> * CMake version v3.20.0 minimum
> * Devicetree compiler v1.4.6 minimum

## Zephyr installation ##

### Update OS ###

>* sudo apt update
>* sudo apt upgrade

### Install dependencies ###

>* wget https://apt.kitware.com/kitware-archive.sh
> * sudo bash kitware-archive.sh
> * sudo apt install --no-install-recommends git cmake ninja-build gperf ccache dfu-util device-tree-compiler wget python3-dev python3-pip python3-setuptools python3-tk python3-wheel xz-utils file make gcc gcc-multilib g++-multilib libsdl2-dev
> * pip3 install --user -U west
> * echo 'export PATH=~/.local/bin:"$PATH"' >> ~/.bashrc
> * source ~/.bashrc

### Verify the versions of the main dependencies installed on your system by entering: ### 

> * cmake --version
> * python3 --version
> * dtc --version

### Install the toolchain ###

>1.Download and verify the latest Zephyr SDK bundle
> * cd ~
> * wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.14.0/zephyr-sdk-0.14.0_linux-x86_64.tar.gz
> * wget -O - https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.14.0/sha256.sum | shasum --check --ignore-missing

>2.Extract the Zephyr SDK bundle archive
> * tar xvf zephyr-sdk-0.14.0_linux-x86_64.tar.gz

>3.Run the Zephyr SDK bundle setup script:
> * cd zephyr-sdk-0.14.0
> * ./setup.sh

>4.Install udev rules, which allow you to flash most Zephyr boards as a regular user:
> * sudo cp ~/zephyr-sdk-0.14.0/sysroots/x86_64-pokysdk-linux/usr/share/openocd/contrib/60-openocd.rules /etc/udev/rules.d
> * sudo udevadm control --reload

## Project Quick and easy installation and build ##

> * git clone https://github.com/railnova/Pong-Workshop
> * cd Pong-Workshop/Pong_Zephyr/
> * pip3 install -r zephyr/scripts/requirements-base.txt
> * west update
> * west zephyr-export
> * west build -b nucleo_l432kc zephyr_pong/app/
> * west flash
