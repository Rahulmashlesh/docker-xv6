FROM ubuntu:14.04
RUN apt-get -qq update
RUN apt-get install -y git nasm build-essential qemu gdb
ADD xv6-public /home/root/xv6-public	
WORKDIR /home/root/xv6-public
CMD ["bash"]
